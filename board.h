#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

struct position {
	int x;
	int y;
	int linearPos;
	position() {}
	position(int a, int b) : x(a), y(b) {}
	position(const position& other) : x(other.x), y(other.y) {}

	void getX() {
		x = linearPos % 3;
	}
	void getY() {
		y = linearPos / 3;
	}
	void getlinearPos() {
		linearPos = (3 * y + x);
	}

	position& operator= (const position& other) {
		x = other.x;
		y = other.y;
		linearPos = other.linearPos;
		return *this;
	}


};

struct tile {
	position pos;
	char tileNum;

	tile(){}
	tile(int x, int y, char num) : pos(x,y), tileNum(num) {}
	tile(const tile& other){
		pos = other.pos;
		tileNum = other.tileNum;
	}

	tile& operator= (const tile& other) {
		pos = other.pos;
		tileNum = other.tileNum;
		return *this;
	}

};

class board {

	// ie. 123456780
	tile blankTile;
	
	board* parent = nullptr;

public:
	string name;
	bool UDLR[4] = { 0,0,0,0 };

	/*
	*	main constructor for board:
	*	gets the blankTile
	*/
	board() {
	}

	board(string Namestate) : name(Namestate){
		getBlankTile();
	}

	// copy constructor
	board(const board& other){
		name = other.name;

		for (int n = 0; n < 4; n++) {
			UDLR[n] = other.UDLR[n];
		}

		blankTile = other.blankTile;
		parent = other.parent;
	}

	// constructor from pointer of another board
	board(const board* other) {
		blankTile = other->blankTile;
		for (int n = 0; n < 4; n++) {
			UDLR[n] = other->UDLR[n];
		}

		parent = other->parent;
		name = other->name;
	}

	// returns the pointer to this boards parent
	board * getParent() {
		return parent;
	}

	// sets *parent to the other boards address
	void setParent(board *other ) {
		parent = other;
	}

	
	// This Function prints the string variable: name in 3x3 style
	void printBoard() {
		for (int y = 0; y < 3; y++) {
			tile n;
			n.pos.y = y;

			for (int x = 0; x < 3; x++) {
				n.pos.x = x;
				n.pos.getlinearPos();
				cout << name[n.pos.linearPos] << " ";
			}
			cout << endl;
		}

		cout << endl;
;
	}

	// function to find where blank tile is located:
	void getBlankTile() {
		blankTile.tileNum = '0';

		for (int n = 0; n < 9; n++) {

			if ( name[n] == '0') {
				blankTile.pos.linearPos = n;
				blankTile.pos.getX();
				blankTile.pos.getY();
			}
		}
	}


	// Function will return 1 of 4 unique strings:
	//		* depends on the moves available to this board
	//		* returns 0 if the a move is unavailable
	// post function this.UDLR[4] will correspond to the moves available
	string getNextMove(int n) {

			char c;
			string copy = name;

			// up
			if (n == 0) {
				if (blankTile.pos.y > 0) {

					c = name[blankTile.pos.linearPos - 3];

					copy[blankTile.pos.linearPos] = c;
					copy[blankTile.pos.linearPos - 3] = blankTile.tileNum;
					UDLR[n] = 1;

				}
				else {
					UDLR[n] = 0;
				}
			}

			// down
			if (n == 1) {
				if (blankTile.pos.y < 2) {
					
					c = name[blankTile.pos.linearPos + 3];

					copy[blankTile.pos.linearPos] = c;
					copy[blankTile.pos.linearPos + 3] = blankTile.tileNum;
					UDLR[n] = 1;
				}
				else {
					UDLR[n] = 0;
				}
			}

			// left
			if (n == 2) {
				if (blankTile.pos.x > 0) {
					c = name[blankTile.pos.linearPos - 1];

					copy[blankTile.pos.linearPos] = c;
					copy[blankTile.pos.linearPos - 1] = blankTile.tileNum;
					UDLR[n] = 1;
				}
				else {
					UDLR[n] = 0;
				}
			}

			// right
			if (n == 3) {
				if (blankTile.pos.x < 2) {
					c = name[blankTile.pos.linearPos + 1];

					copy[blankTile.pos.linearPos] = c;
					copy[blankTile.pos.linearPos + 1] = blankTile.tileNum;
					UDLR[n] = 1;
				}
				else {
					UDLR[n] = 0;
				}
			}
			// send it!
			if (UDLR[n]) {
				return copy;
			}
			else {
				return "0";
			}

	}

	// copy assignment
	board& operator=(const board& other)
	{
			for (int i = 0; i < 4; i++) {
				UDLR[i] = other.UDLR[i];
			}
			blankTile = other.blankTile;
			parent = other.parent;
			name = other.name;
			return *this;
	
	}

};
