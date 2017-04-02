/*******************
Chikarmane, Akaash
avc536
Section #: 16290
EE312 - Assignment 7
*******************/

#include <stdio.h>
#include <string.h>

/***Helper Function Prototypes***/
void fillParen(int NL, int NR, int pos, char printarray[]);

void decomposeString(char string[], int length, char previousprint[]);

int checkPalindrome(char str[]);

/****Main function implementations****/
void generateAllMatchedParens(int n){
	//Function needs to generate all matched parens as described in the assignment
	printf("# of parenthese: %i\n", n);
	char printparen[30];
	for (int i = 0; i < 30; i++) {
		printparen[i] = '\0';
	}
	printparen[0] = '(';
	fillParen(n-1, n, 1, printparen);
}

void generateAllPalindromicDecompositions(char str[]){
	int n = strlen(str);		//length including null character
	printf("Palindrome composition of: %s\n", str);
	char basicprint[30] = { '\0' };
	decomposeString(str, n, basicprint);
}

/***Helper function implementations***/
void fillParen(int NL, int NR, int pos, char printarray[]) {
	if (NR >= NL) {
		if ((NL == 0) && (NR == 0)) {
			printf("%s\n", printarray);
			return;
		}
		if (NL > 0) {
			printarray[pos] = '(';
			fillParen((NL - 1), NR, (pos + 1), printarray);
		}
		if (NR > 0) {
			printarray[pos] = ')';
			fillParen(NL, (NR - 1), (pos + 1), printarray);
		}
	}
	return;
}

void decomposeString(char string[], int length, char previousprint[]) {
	char sOne[20] = { '\0' };		//creates space for the first part of the decomposition
	char sTwo[20] = { '\0' };		//creates space for the second part of the decomposition
	char currentprint[30];			//this array will keep the current print so that the next decompositions of string to can be checked
	int sOnePal = 0;
	memcpy(currentprint, previousprint, sizeof(currentprint));
	for(int i = 1; i <= length; i++){
		strncpy(sOne, string, i);		//decomposes and copies the first part
		strcpy(sTwo, (string + i));		//decomposes and copies the second part
		sOnePal = checkPalindrome(sOne);		//checks if the first part is a palindrome printed decomposition needs to be all palindromes
		if (sOnePal) {		//if it is a palindrome, decompose and analyze the second part
			memcpy(currentprint, previousprint, sizeof(currentprint));	//previousprint preserves the state before printing again - there may be more palindromes in the second decomposition
			strcat(currentprint, sOne);		//adds the newly found palindrome in the second decomposition
			strcat(currentprint, " ");		//adds a space after
			decomposeString(sTwo, strlen(sTwo), currentprint);
		}
		if ((sTwo[0] == '\0') && sOnePal) {
			strcat(currentprint, "\n");		//prints when (a) there is nothing else to decompose AND (b) when it has just analyzed a palindrome
			printf(currentprint);
			return;
		}
	}
}

int checkPalindrome(char str[]) {
	int isPalindrome = 0;
	char* firstchar = str;		//sets firstchar to the first character
	char* lastchar = str + strlen(str) - 1;		//sets lastchar to the last character
	while (lastchar >= str) {		//while the address of last character is greater than or equal to the beginning of the string
		if (*lastchar == *firstchar) {		//if the first character is the same as the last character
			isPalindrome = 1;		//keep the flag as true
		}
		else {
			isPalindrome = 0;		//if the first character is not the same as the last character, set the flag to false
			break;		//leave the while loop
		}
		firstchar++;		//move the firstchar pointer forward
		lastchar--;		//move the lastchar pointer backward
	}
	return(isPalindrome);
}