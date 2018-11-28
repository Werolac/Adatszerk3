/*
 * rope.hpp
 *
 *  Created on: 2018. nov. 28.
 *      Author: Wero
 */

#ifndef ROPE_HPP_
#define ROPE_HPP_

#include<iostream>

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
		unsigned int weightOfLeftTree;
		Node() :
				parent(nullptr), left(nullptr), right(nullptr), weight(0), isLeaf(
						false), weightOfLeftTree(0) {
		}
		Node(string input) :
				parent(nullptr), left(nullptr), right(nullptr), weight(0), isLeaf(
						false), weightOfLeftTree(0) {
			if (input.length() > 3) {
				int halfWay = input.length() / 2;
				string leftString = input.substr(0, halfWay);
				string rightString = input.substr(halfWay + 1, input.length());
				weightOfLeftTree = leftString.length();
				left = new Node(leftString, this);
				right = new Node(rightString, this);
			} else {
				weight = input.length();
				isLeaf = true;
				for (int j = 0; j < weight; j++) {
					charArray[j] = input[j];
				}
			}

		}
		//NOTE talán ez mehet privátba? Ha tesztelés lesz akkor meg kell nézni
		Node(string input, Node *p) :
				parent(p), left(nullptr), right(nullptr), weight(0), isLeaf(
						false), weightOfLeftTree(0) {
			if (input.length() > 3) {
				int halfWay = input.length() / 2;
				string leftString = input.substr(0, halfWay);
				string rightString = input.substr(halfWay + 1, input.length());
				weightOfLeftTree = leftString.length();
				left = new Node(leftString, this);
				right = new Node(rightString, this);
			} else {
				weight = input.length();
				isLeaf = true;
				for (int j = 0; j < weight; j++) {
					charArray[j] = input[j];
				}
			}
		}

	};
	Node *root;
public:
	void _remove(Node *a);
	unsigned int length() const; // visszaadja a rope súlyát(szummázva az összes csúcs súlyát)
	char index(const unsigned int) const; //visszaadja a kapott indexű karaktert
	static Rope concat(Rope& r1, Rope& r2); // konkatál két ropeot
	static pair<Rope, Rope> split(Rope&, const unsigned int); // Ropeot kettévág
	string report(unsigned int from, unsigned int till) const; //Visszaadja a két index közötti stringet
	Rope() :
			root(nullptr) {
	}
	;
	~Rope() {
		_remove(root);
	}
};
//Destruktor meghívva a gyökérre
void Rope::_remove(Node *a) {
	if (a != nullptr) {
		_remove(a->left);
		_remove(a->right);
		delete a;
	}
}

unsigned int Rope::length() const {
	return 0;
}

#endif /* ROPE_HPP_ */
