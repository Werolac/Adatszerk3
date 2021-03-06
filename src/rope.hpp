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
	//kotelezo fuggvenyek
	void _remove(Node *a);
	unsigned int length() const; // visszaadja a rope súlyát(szummázva az összes csúcs súlyát)
	char index(const unsigned int) const; //visszaadja a kapott indexű karaktert.
	void ropeLength(Node* actualNode, unsigned int &totalWeight); //visszaadja az adott rope hosszát
	static Rope concat(Rope& r1, Rope& r2); // konkatál két ropeot.
	static pair<Rope, Rope> split(Rope& motherRope, const unsigned int index); // Ropeot kettévág.
	string report(unsigned int from, unsigned int till) const; //Visszaadja a két index közötti stringet
	//segedfuggvenyek

	char helpForIndex(Node* actualNode, unsigned int) const; //segédfüggvény az indexhez.
	unsigned int helpRopeLength(Node* actualNode); //segédfüggvény a ropeLengthez
	Node* getNode(Node* actualNode, unsigned int &index); // segédfüggvény a splithez, visszaadja a nodeot
	void beforesplitNode(Node* actualNode, unsigned int index);	//splithez, splitet kesziti elo végzi
	void splitter(Rope &initialRope,Node* actualNode);

	Rope() :
			root(nullptr), lengthOfRope(0) {
	}
	;
	Rope(string input) :
			root(nullptr), lengthOfRope(0) {
		lengthOfRope = input.length();
		root = new Node(input);
	}
	Rope(Node* rootNode) :
			root(rootNode), lengthOfRope(0) {
		ropeLength(rootNode, lengthOfRope);
	}
	~Rope() {
		Rope::_remove(root);
		lengthOfRope = 0;
	}
};
//Bináris fából átemelve, rekurzívan takaritja a nodeokat ki
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
	for (unsigned int i = from; i < till; i++) {
		resultText += index(i);
	}
	return resultText;
}

Rope Rope::concat(Rope& r1, Rope& r2) {
	string textOfr1 = r1.report(0, r1.length());
	string textOfr2 = r2.report(0, r2.length());
	Node* newRootLeftChild = new Node(textOfr1);
	Node* newRootRightChild = new Node(textOfr2);
	r1.~Rope();
	r2.~Rope();
	Node* freshRoot = new Node();
	freshRoot->left = newRootLeftChild;
	freshRoot->right = newRootRightChild;
	freshRoot->left->parent = freshRoot->right->parent = freshRoot;
	freshRoot->weight = textOfr1.length();
	Rope* concatedRope = new Rope(freshRoot);
	return *concatedRope;
}
//vegigiteral a fa jobb agan es visszaadja az osszsulyt, vagyis a hosszt
void Rope::ropeLength(Node* actualNode, unsigned int &totalWeight) {
	if (actualNode != nullptr) {
		totalWeight += actualNode->weight;
		ropeLength(actualNode->right, totalWeight);
	}
}

//started doing by the proper way
//like helpofindex
Rope::Node* Rope::getNode(Node* actualNode, unsigned int &indexOfSplit){
	if (actualNode->weight <= indexOfSplit) {
		indexOfSplit -= actualNode->weight;
			return getNode(actualNode->right, indexOfSplit);
		}
		if (actualNode->left != nullptr) {
			return getNode(actualNode->left, indexOfSplit);
		}
		return actualNode;
}

void Rope::splitter(Rope &initialRope,Node* actualNode){
	if(actualNode->parent->right != nullptr && actualNode->parent->right != actualNode){
		if(actualNode->parent->parent != nullptr){
			actualNode->parent->parent->weight -= actualNode->parent->right->weight;
		}
		actualNode->parent->right->parent = nullptr;
		Rope* newRopeFromLeaf = new Rope(actualNode->parent->right);
		actualNode->parent->right = nullptr;
		Rope newRopeToPass = concat(initialRope, *newRopeFromLeaf);
		splitter(newRopeToPass, actualNode->parent);
	}
}

void Rope::beforesplitNode(Node* actualNode, unsigned int indexOfSplit) {
	unsigned int initialIndex = indexOfSplit - 1;
	//indexOfSplit vary, because of getNode function always changes it
	Node* searchedNode = getNode(actualNode, indexOfSplit);
		//we got the node, now we check if the index is before, at , or after the string
		//if the index is before and after
		if(indexOfSplit == 0 || indexOfSplit == searchedNode->weight){
			if(indexOfSplit == 0){
				//this means that if the index is at a start of a string than search for the previous leaf and make that the current node.
				actualNode = getNode(root,initialIndex);
			} else {

			}
		} else {
			// we need to split the index
			string firstHalf, secondHalf;
			for(unsigned int i=0; i<searchedNode->weight ; i++){
				if(i<indexOfSplit){
					firstHalf += searchedNode->charArray[i];
					searchedNode->charArray[i] = '0';
				} else {
					secondHalf += searchedNode->charArray[i];
					searchedNode->charArray[i] = '0';
				}
			}
			Node* leftChild = new Node(firstHalf,searchedNode);
			Node* rightChild = new Node(secondHalf,searchedNode);
			searchedNode->isLeaf = false;
			searchedNode->left = leftChild;
			searchedNode->right = rightChild;
			searchedNode->weight = firstHalf.length();
		}

}

pair<Rope, Rope> Rope::split(Rope& motherRope, const unsigned int index) {
	pair<Rope, Rope> childrenOfMotherRope;
	motherRope.beforesplitNode(motherRope.root,index);
	return childrenOfMotherRope;
}

/*
 pair<Rope, Rope> Rope::split(Rope& motherRope, const unsigned int index) {
 pair<Rope,Rope> childrenOfMotherRope;
 string firstHalf = motherRope.report(0,index);
 string secondHalf = motherRope.report(index,motherRope.length());
 childrenOfMotherRope.first = new Rope(firstHalf);
 childrenOfMotherRope.second = new Rope(secondHalf);
 motherRope.~Rope();
 return childrenOfMotherRope;

 }
 */
#endif /* ROPE_HPP_ */
