//Last modified: 9/20/16
/*******************
Chikarmane, Akaash
avc536
Section #: 16290
EE312 - Assignment 3 - main.c
*******************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*
 * declarations of functions that are defined
 * in Lab3.c
 *
 * You only need to declare the functions that you'll
 * be accessing from inside main.c
 */
void encrypt(char s[], int sLength, int key);
int mostFrequentLetter(char s[], int sLength);
void decrypt(char s[], int sLength, int common);


/*
 * Stage 1 is writing the simpleEncrypt function
 * In this test, we try out a few obvious encryptions
 */
void testStage1(void) {
	int tests_passed = 0;
	
	/* test1: IBM rotated -1 should be HAL */
	char s[100] = "IBM";
	encrypt(s,strlen(s), 25);
	if (0 != strcmp(s, "HAL")) {
		printf("stage 1 test 1 failed (IBM->HAL)\n");
	} else {
		tests_passed += 1;
	}
	
	/* test2: anything rotated 26 should be itself */
	strcpy(s, "zebra");
	encrypt(s,strlen(s), 26);
	if (0 != strcmp(s, "zebra")) {
		printf("stage 1 test 2 failed (rotate by 26)\n");
	} else {
		tests_passed +=1;
	}
	
	/* test3: try upper and lower case */
	strcpy(s, "Antelope");
	encrypt(s,strlen(s), 2);
	if (0 != strcmp(s, "Cpvgnqrg")) {
		printf("stage1 test3 failed (upper and lower case)\n");
	} else {
		tests_passed += 1;
	}
	
	/* test4: arbitrary letters, numbers, etc. */
	strcpy(s, "Valentine's day is 2/14!");
	encrypt(s,strlen(s), 25);
	if (0 != strcmp(s, "Uzkdmshmd'r czx hr 2/14!")) {
		printf("stage1 test4 failed (punctuation and large shift)\n");
	} else {
		tests_passed += 1;
	}
	
	if (tests_passed == 4) {
		printf("Congratulations! you passed stage 1\n");
	} else {
		printf("please try to fix stage 1 before going on to stage 2\n");
	}
}

/*
 * Stage 2 is the mostCommonLetter function
 */
void testStage2(void) {
	int tests_passed = 0;
	char s[100] = "abacad";
	if (mostFrequentLetter(s,strlen(s)) != 0) {
		printf("stage 2 test 1 failed \"abacad\"\n");
	} else {
		tests_passed += 1;
	}
	strcpy(s, "IT's peanut butter and jelly");
	if (mostFrequentLetter(s,strlen(s)) != 19) {
		printf("stage 2 test 2 failed \"IT's peanut butter and jelly\"\n");
	} else {
		tests_passed += 1;
	}
	
	if (tests_passed == 2) {
		printf("Congratulations! you passed stage 2\n");
	} else {
		printf("please try to fix stage 2 before going to stage 3\n");
	}
}

char secret[] = "EE312 with Dr. Barber is fun!";
void testStage3(void) {
	int key;
	int common;

	srand((unsigned) time(0));
	key = rand() % 26;
	common = mostFrequentLetter(secret,strlen(secret));
	encrypt(secret,strlen(secret), key);
	printf("%s\n", secret);
	decrypt(secret, strlen(secret),common);
	printf("%s\n", secret);
	while (1);
}

int main(void) {
	testStage1();
	testStage2();
	testStage3();
}	

