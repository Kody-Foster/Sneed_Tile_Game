// Tile Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "board.h"

using namespace std;
bool isSolvable(string& in, string& key);

int main(int argc, char* argv[])
{
    string start = argv[1];
    string key = argv[2];

    if (start.size() != 9 || key.size() != 9) {
        cout << "Invlaid Input" << endl;
        return 0;
    }
    else {

        /*
        string start = {
            '8','3','7',
            '5','6','1',
            '2','4','0',
        };

        string key = {
            '1','2','3',
            '4','5','6',
            '7','8','0'
        };
        */

        string  test = start;
        unordered_map <string, board> queue;
        vector <string*> todo;


        queue[test] = board{ test };
        todo.emplace_back(&queue[test].name);

        // test's if puzzle is solvable first
        if (isSolvable(test, key)) {

            // Iterate through the queue
            for (int n = 0; n < todo.size();n++) {

                test = *todo[n];

                // check if we have found the key
                // if not, get the moves test will produce
                if (test != key) {
                    for (int i = 0; i < 4; i++) {
                        string next;
                        next = queue[test].getNextMove(i);
                        if (next != "0") {
                            // if next is not already in queue
                            if (!queue.count(next)) {
                                queue[next] = board{ next };
                                queue[next].setParent(&queue[test]);
                                todo.emplace_back(&queue[next].name); // add new moves to todo
                            }

                        }
                    }
                }
                else {
                    break;
                }

            }

            // reconstruct the path to the key using the queue data structure
            // starting at queue[test] follow the chain of parents to the start
            if ((queue[test].name == key)) {
                vector <string*> path;
                path.emplace_back(&queue[test].name);

                // if test != start add the next parent to the path
                while (queue[test].getParent() != nullptr && queue[test].name != start) {
                    test = queue[test].getParent()->name;
                    path.emplace_back(&queue[test].name);
                }

                // print the board and keep track of how many boards were printed
                int movecount = 0;
                for (int i = path.size() - 1; i >= 0; i--) {
                    cout << "Move " << movecount << ":\n";
                    movecount++;
                    queue[*path[i]].printBoard();
                }
                cout << path.size() << " moves is the shortest path to victory" << endl;
            }
            else {
                cout << "Board Solution not found\n" << endl;
            }

            cout << queue.size() << " boards considered" << endl;
        }

        return 0;
    }
}
// tests for duplicates, counts number of inversions compared to key
// returns 1 if solvable, 0 if not solvable or duplicate numbers exist
bool isSolvable(string& in, string& key) {
    // tests for duplicate numbers in the string or key
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (in[i] == in[j] || key[i] == key[j]) {
                cout << "Not a valid input\n";
                cout << "Please do not enter duplicate numbers" << endl;
                return 0;
            }
        }
    }

    // counts the number of inversions compared to the key
    int numInversions = 0;
    for (int i = 0; i < 8; i++) { //for each pivot

        for (int j = i + 1; j < 9; j++) { //for each item ahead of pivot
            for (int k = 0; k < 9; k++) { //compare to every value in the key

                // note:

                 // if we reach in[i] first, break;
                if (in[i] == key[k]) {
                    break;
                
                // if we reach in[k] first, its out of order:
                if (in[j] == key[k]) {
                    numInversions++;
                }
            }
        }
    }
    if ((numInversions % 2) >= 1) {
        cout << "Not Solvable" << endl;
        return 0;
    }
    else if ((numInversions % 2) == 0) {
        cout << "Solvable" << endl;
        return 1;
    }
    else {
        cout << "No valid input" << endl;
        return 0;
    }
}
