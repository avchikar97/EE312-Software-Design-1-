/*******************
Chikarmane, Akaash
avc536
Section #: 16290
EE312 - Assignment 8
*******************/

//
//  main.cpp
//  Assignment 8
//
//  Created by Elie Antoun on 4/7/16.
//  Copyright © 2016 Elie Antoun. All rights reserved.
//

#include <stdio.h>
#include "linkedlist.cpp"
#include <cassert>

void test1() {
	int value = 1;
	int postion = 0;
	LinkedList l;
	l.addToListAtPosition(postion, value);
	assert(l.getListLength() == 1);
	printf("Test1 Passed!\n");
}

void test2() {
	int value = 1;
	int postion = 0;
	LinkedList l;
	l.addToListAtPosition(postion, value);
	assert(l.getListLength() == 1);
	assert(l.getHead()->value == 1);
	printf("Test2 Passed!\n");
}

void test3() {
	int value = 2;
	LinkedList l;
	l.addToHead(value);
	assert(l.getListLength() == 1);
	assert(l.getHead()->value == 2);
	printf("Test3 Passed!\n");
}

void test4() {
	LinkedList l;
	l.addToHead(1);
	l.addToHead(2);
	assert(l.getListLength() == 2);
	assert(l.getHead()->value == 2);
	assert(l.getHead()->next->value == 1);
	printf("Test4 Passed!\n");
}

void test5() {
	LinkedList l;
	l.addToListAtPosition(0, 1);
	l.addToListAtPosition(1, 2);
	assert(l.getListLength() == 2);
	assert(l.getHead()->value == 1);
	assert(l.getHead()->next->value == 2);
	printf("Test5 Passed!\n");
}

void test6() {
	LinkedList l;
	l.addToListAtPosition(0, 1);
	l.addToListAtPosition(1, 2);
	assert(l.find(1) == true);
	assert(l.find(2) == true);
	printf("Test6 Passed!\n");
}

void test7() {
	LinkedList l;
	l.addToListAtPosition(0, 1);
	l.addToListAtPosition(1, 2);
	l.removeFromListAtPosition(1);
	assert(l.getHead()->value == 1);
	assert(l.getHead()->next == 0);
	printf("Test7 Passed!\n");
}

void test8() {
	LinkedList l;
	l.addToListAtPosition(0, 1);
	l.addToListAtPosition(1, 2);
	l.removeFromListAtPosition(0);
	assert(l.getHead()->value == 2);
	assert(l.getHead()->next == 0);
	printf("Test8 Passed!\n");
}

void test9() {
	LinkedList l;
	l.addToListAtPosition(0, 1);
	l.addToListAtPosition(1, 2);
	l.removeFromHead();
	assert(l.getHead()->value == 2);
	assert(l.getHead()->next == 0);
	printf("Test9 Passed!\n");
}

void test10() {
	LinkedList l;
	l.addToListAtPosition(0, 1);
	l.addToListAtPosition(1, 2);
	l.removeFromEnd();
	assert(l.getHead()->value == 1);
	assert(l.getHead()->next == 0);
	printf("Test10 Passed!\n");
}

void test11() {
	LinkedList l;
	l.addToListAtPosition(0, 1);
	l.addToListAtPosition(1, 2);
	l.reverseList();
	assert(l.getHead()->value == 2);
	assert(l.getHead()->next->value == 1);
	printf("Test11 Passed!\n");
}

//void test12() {
//	LinkedList l;
//	l.addToListAtPosition(0, 1);
//	l.addToListAtPosition(1, 2);
//	l.addToListAtPosition(2, 3);
//	l.appendToList(4);
//	l.reverseList();
//	assert(l.getHead()->value == 4);
//	assert(l.getHead()->next->value == 3);
//	printf("Test12 Passed!\n");
//}

int main() {

	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();
	test11();
	while (true);
}