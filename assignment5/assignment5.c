/*
* assignment5.c
* SpellCheck
*/

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types
#include <stdlib.h>
#define TRUE	1
#define FALSE	0
#define MAXWORD	30
/*
* return 1 if the ASCII interpretation of
* c is an upper case letter.
* return 0 otherwise
*/
int isUpperCase(char c) {
	if (c >= 'A' && c <= 'Z') {
		return 1;
	}
	else {
		return 0;
	}
}

/*
* return 1 if the ASCII interpretation of
* c is a lower case letter.
* return 0 otherwise
*/
int isLowerCase(char c) {
	if (c >= 'a' && c <= 'z') {
		return 1;
	}
	else {
		return 0;
	}
}

/*
* return 1 c is an Alphabet.
* return 0 otherwise
*/
int isAlphabet(char c) {
	return isUpperCase(c) || isLowerCase(c);
}

char makeAlphabet(char c) {
	if (isLowerCase(c)) {
		c = c - 'a';
	}
	if (isUpperCase(c)) {
		c = c - 'A';
	}
	return c;
}

/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
*
* Many students find it helpful to declare global variables (often arrays). You are welcome to use
* globals if you find them helfpul. Global variables are by no means necessary for this project.
*/

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
* exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
* You are expected to use reasonable programming style. I strongly encourage you to avoid big functions
* (while there are always exceptions, a good rule of thumb is about 15 lines in a function).
* So, plan on implementing spellCheck by writing two or three other "support functions" that
* help make the actual spell checking easier for you.
* There are no explicit restictions on using functions from the C standard library. However,
* for this project you should avoid using functionality from the C++ standard libary. You will
* almost certainly find it easiest to just write everything you need from scratch!
*/

//TODO:
void spellCheck(char article[], char dictionary[]) {
	int i = 0, s = 0, n = 0, m = 0;		//i is a counter for the article only, dictionary is only used with s
	char currentword[MAXWORD] = { '\0' };
	char dictionarycomp[MAXWORD] = { '\0' };
	char comparison1 = '\0';
	char comparison2 = '\0';
	int wordflag = 0;
	int totaltrue = 0;
	while (article[i] != '\0') {		//runs for the length of the string
		if (isAlphabet(article[i]) && isAlphabet(article[i + 1])) { //if two consecutive letters this is a word so execute the necessary code
																	//puts letters from the word into currentword
			for (s = 0; isAlphabet(article[i]) && s < MAXWORD; i++, s++) {
				currentword[s] = article[i];
			}
			i--;		//offsets the increment at the end of the if branch
			//checks currentword against all words in dictionary
			m = 0;		//start at the beginning of the dictionary
			while (dictionary[m] != '\0') {
				n = 0;
				while (dictionary[m] != '\n' && dictionary[m] != '\0') {	//copies single word from dictionary to dictionarycomp
					dictionarycomp[n] = dictionary[m];
					m++;
					n++;
				}
				m++;	//increments m to get dictionary[m] off the \n
				for (s = 0; s < MAXWORD; s++) {		//compares the 0-25 value for each letter to determine if the word matches (allows program to disregard case)
					comparison1 = makeAlphabet(dictionarycomp[s]);
					comparison2 = makeAlphabet(currentword[s]);
					if (comparison1 == comparison2) {
						totaltrue++;		//increments everytime a character matches
					}
				}
				for (s = 0; s < MAXWORD; s++) {	//reset all characters in dictionarycomp to null
					dictionarycomp[s] = '\0';
				}
				if (totaltrue == MAXWORD) {	//if all 20 match we have a winner so stop looking through dictionary (break out of while loop)
					wordflag = TRUE;
					break;
				}
				else {
					wordflag = FALSE;
					totaltrue = 0;		//if not set totaltrue to 0 and look for the next word
				}
			}
			//stuff to do before continuing with article
			if (!wordflag) {	//if the word is not in the dictionary wordflag is FALSE, print it
				printf("%s\n", currentword);
				wordflag = FALSE;
			}
			totaltrue = 0;
			for (s = 0; s < MAXWORD; s++) {	//reset all characters in currentword to null
				currentword[s] = '\0';
				dictionarycomp[s] = '\0';
			}
		}
		i++;		//article[i] is now the next character regardless of whether or not a word was found
	}
}


