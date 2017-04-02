#include "polynomial.hh"
#include <stdio.h>

Node::Node(double v, Node* n) {
	value = v;
	next = n;
}

Poly::Poly() {
	setHead(nullptr);
	setListLength(0);
}

Poly::Poly(const Poly &newobj) {
	setHead(nullptr);
	setListLength(0);
	Node* headold = newobj.head;
	while (headold != nullptr) {
		append(headold->value);
		headold = headold->next;
	}
}

Poly::~Poly() {
	Node* current = getHead();
	Node* nextfree = nullptr;
	setHead(nullptr);		//set head to null
	setListLength(0);
	for (current; current != nullptr; current = nextfree) {
		nextfree = current->next;
		delete current;
	}
}

Poly Poly::operator=(const Poly &newobj) {
	this->setHead(nullptr);
	this->setListLength(0);
	Node* headold = newobj.head;
	while (headold != nullptr) {
		this->append(headold->value);
		headold = headold->next;
	}
	return (*this);
}

Node* Poly::getHead(){
	return head;
}

void Poly::setHead(Node* newhead) {
	head = newhead;
}

int Poly::getListLength() {
	return ListLength;
}

void Poly::setListLength(int n) {
	ListLength = n;
}

void Poly::print(){
	Node* temp = getHead();
	while(temp!=0){
		printf("%.2f", temp->value);
		temp = temp->next;
	}
}

void Poly::append(double v) {
	Node* current = nullptr;
	Node* newnode = new Node(v, nullptr);
	if (getHead() != nullptr) {
		for (current = getHead(); current->next != nullptr; current = current->next);
		current->next = newnode;
	}
	else {
		setHead(newnode);
	}
	setListLength(getListLength() + 1);
}
