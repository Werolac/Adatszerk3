/*
 * rope.hpp
 *
 *  Created on: 2018. nov. 28.
 *      Author: Wero
 */

#ifndef ROPE_HPP_
#define ROPE_HPP_

#include <iostream>
#include "exceptions.hpp"

using namespace std;
class Rope {
	class Node {
	public:
		Node *parent;
		Node *left;
		Node *right;
		unsigned int weight;
		char charArray[3];
		bool isLeaf;
		Node() :
				parent(nullptr), left(nullptr), right(nullptr), weight(0), isLeaf(
						false) {
		}
		Node(string input) :
				parent(nullptr), left(nullptr), right(nullptr), weight(0), isLeaf(
						false) {
			if (input.length() > 3) {
				int halfWay = input.length() / 2;
				string leftString = input.substr(0, halfWay);
				string rightString = input.substr(halfWay , input.length());
				weight = leftString.length();
				left = new Node(leftString, this);
				right = new Node(rightString, this);
			} else {
				weight = input.length();
				isLeaf = true;
				for (unsigned int j = 0; j < weight; j++) {
					charArray[j] = input[j];
				}
			}

		}
		Node(string input, Node *p) :
				parent(p), left(nullptr), right(nullptr), weight(0), isLeaf(
						false) {
			if (input.length() > 3) {
				int halfWay = input.length() / 2;
				string leftString = input.substr(0, halfWay);
				string rightString = input.substr(halfWay, input.length());
				weight = leftString.length();
				left = new Node(leftString, this);
				right = new Node(rightString, this);
			} else {
				weight = input.length();
				isLeaf = true;
				for (unsigned int j = 0; j < weight; j++) {
					charArray[j] = input[j];
				}
			}
		}

	};
	Node *root;
	unsigned int lengthOfRope;

public:
	void _remove(Node *a);
	unsigned int length() const; // visszaadja a rope súlyát(szummázva az összes csúcs súlyát)
	char index(const unsigned int) const; //visszaadja a kapott indexű karaktert.
	char helpForIndex(Node* actualNode, unsigned int) const; //segédfüggvény az indexhez.
	static Rope concat(Rope& r1, Rope& r2); // konkatál két ropeot.
	static pair<Rope, Rope> split(Rope&, const unsigned int); // Ropeot kettévág.
	string report(unsigned int from, unsigned int till) const; //Visszaadja a két index közötti stringet
	Rope() :
			root(nullptr), lengthOfRope(0) {
	}
	;
	Rope(string input) :
			root(nullptr), lengthOfRope(0) {
		lengthOfRope = input.length();
		root = new Node(input);
	}
	~Rope() {
		_remove(root);
	}
};
//Destruktor meghívva a gyökérre, bináris fa kódból átemelve
void Rope::_remove(Node *a) {
	if (a != nullptr) {
		_remove(a->left);
		_remove(a->right);
		delete a;
	}
}

unsigned int Rope::length() const {
	return lengthOfRope;
}

char Rope::helpForIndex(Node* actualNode, unsigned int indexOfChar) const {
	if (actualNode->weight <= indexOfChar) {
		return helpForIndex(actualNode->right, indexOfChar - actualNode->weight);
	}
	if (actualNode->left != nullptr) {
		return helpForIndex(actualNode->left, indexOfChar);
	}
	return actualNode->charArray[indexOfChar];
}

char Rope::index(const unsigned int indexOfChar) const {
	if (indexOfChar > lengthOfRope || indexOfChar < 0) {
		throw OutOfIndexException();
	} else {
		return helpForIndex(root, indexOfChar);
	}
}
string Rope::report(unsigned int from, unsigned int till) const {
	string resultText;
	for(unsigned int i= from; i<till; i++){
		resultText += index(i);
	}
	return resultText;
}

#endif /* ROPE_HPP_ */
