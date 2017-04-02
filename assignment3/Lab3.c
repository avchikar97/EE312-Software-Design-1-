/*******************
Chikarmane, Akaash
avc536
Section #: 16290
EE312 - Assignment 3 - Lab3.c
*******************/

#include <stdio.h>


/*
 * return 1 if the ASCII interpretation of 
 * c is an upper case letter.  
 * return 0 otherwise
 */
int isUpperCase(char c) {
	if (c >= 'A' && c <= 'Z') {
		return 1; 
	} else {
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
	} else {
		return 0;
	}
}

/*
 * return 1 c is an Alphabet.  
 * return 0 otherwise
 */
int isAlphabet(char c){
	return isUpperCase(c) || isLowerCase(c);
}

/*
 * if the ASCII interpretation of c is a letter, then
 * return a number between 0 and 25 indicating which letter of 
 * the alphabet c represents.  For example, if c is the ASCII
 * encoding for 'A', then we should return 0.  If c is the
 * ASCII encoding for 'e', then we should return 4.
 * if the ASCII interpretation of c is not a letter, then
 * return -1.
 */
int ASCII2Int(char c) {
	if (isUpperCase(c)) {
		return c - 'A';
	} else if (isLowerCase(c)) {
		return c - 'a';
	} else { 
		return -1;
	}
}

/*
* assumes i is between 0 and 25 inclusive
*/
char int2UpperCase(int i){
	char c = 'A'+i;
	return c;
}

/*
* assumes i is between 0 and 25 inclusive
*/
char int2LowerCase(int i){
	char c = 'a'+i;
	return c;
}

/*
* This function takes in a message and computes the frequencies of all the alphabets
*/
void buildHistogram(char message[], int messageLength, int histogram[], int histogramLength){
	int i = 0;
	for (i = 0; i < messageLength; i++) {
		if (isUpperCase(message[i])) {
			histogram[message[i] - 65]++;		//65 is offset to get 0-25 regardless of case
		}
		else if (isLowerCase(message[i])) {
			histogram[message[i] - 97]++;		//97 is offset to get 0-25 regardless of case
		}
	}
}

/*
* This function computes the maximum value in an array and returns the index location
* for which the maximum value occured
*/

int maxIndex(int myArray[], int arrayLength){
	int i = 0;
	int maxIndex = 0;
	int maxValue = myArray[maxIndex];
	for (i = 0; i < arrayLength; i++) {
		if (myArray[i] > maxValue) {		//if the current value is greater than the current maxValue, replace it as well as the maxIndex
			maxValue = myArray[i];
			maxIndex = i;
		}
	}
	for (i = 0; i < arrayLength; i++) {
		if (myArray[i] < maxValue) {		//if the current value is greater than the current maxValue, replace it as well as the maxIndex
			myArray[i] = 0;
		}
	}
	return(maxIndex);
}

/*
 * Encrypt the string s using the rotation cypher
 * Each letter in s should be shifted "shift" letters to the 
 * right.  For example, if "shift" is 2, then "a zebra" should be
 * changed to "c bgdtc".  Note that when shifting past the end
 * of the alphabet, we wrap around again to a.
 *
 * Only change the letters in s.  Do not change spaces, punctuation
 * or numbers in s.  
 * For full credit, you should keep upper case letters as 
 * upper case, and leave lower case letters as lower case.  So, if
 * s had been the string "a ZeBra", you should change s to be
 * "c BgDtc".
 */
void encrypt(char message[], int messageLength, int shift) {
	int letteroffset = 0;
	int applyShift = 0;
	for (int i = 0; i < messageLength; i++) {
		if (isUpperCase(message[i])) {
			letteroffset = 65;		//if it's an uppercase letter, the offset is set to 65
			applyShift = 1;			//allows the shift to be applied
		}
		else if (isLowerCase(message[i])) {
			letteroffset = 97;		//if it's an lowercase letter, the offset is set to 97
			applyShift = 1;			//allows the shift to be applied
		}
		else {
			letteroffset = 0;		//sets offset to 0 just in case
			applyShift = 0;			//tells function to do nothing to the character
		}
		if (applyShift) {
			message[i] = message[i] - letteroffset;		//bring the letter down to 0-25 to optiimize use of the mod function
			message[i] = message[i] + shift;	//apply shift
			message[i] = (message[i] % 26);		//mod if the shift takes the value over Z
			message[i] = message[i] + letteroffset;		//keep keep the case
		}
	}
}

/*
 * return a number between 0 and 25 indicating which letter
 * of the alphabet is most common in the string s
 */
int mostFrequentLetter(char message[], int messageLength) {
	int mostFrequent = 0;		//will be the index value not the frequency
	int temp = 0;
	int helpwithfrequency = messageLength;
	int p = 0;
	int frequencyLength = 26;
	int frequencyHistogram[26] = { 0 };
	buildHistogram(message, messageLength, frequencyHistogram, frequencyLength);
	mostFrequent = maxIndex(frequencyHistogram, frequencyLength);
	temp = frequencyHistogram[mostFrequent];		//temp is the frequency of "the most frequent letter"
	for (int i = 0; i < messageLength; i++) {		//messageLength is the top for loop because you need to check the first letter to see if it's one of the letters in question then the second one and so on
		for (int d = 0; d < frequencyLength; d++) {
			if (frequencyHistogram[d] == temp) {	//cycle through until d is the 0-25 value of one of the most frequent letters
				if ((message[i] == (d + 65)) || (message[i] == (d + 97))) {	//if the current message letter is the same as one of the most frequent letters
					frequencyHistogram[d] = frequencyHistogram[d] + helpwithfrequency;	//add an offset
					helpwithfrequency--;	//subtract from offset
				}	//this if branch essentially rigs the histogram to return the first most frequent letter once maxIndex is run again
			}
		}
	}
	mostFrequent = maxIndex(frequencyHistogram, frequencyLength);	//run maxIndex again and return the proper value
	return(mostFrequent);
}

void decrypt(char cypher[],int cypherLength, int common) {
	int mostfrequent = mostFrequentLetter(cypher, cypherLength);
	int backshift;
	if (mostfrequent < common) {
		backshift = (mostfrequent - common) + 26;
	}
	else {
		backshift = mostfrequent - common;
	}
	int letteroffset = 0;
	int applyBackShift = 0;
	for (int i = 0; i < cypherLength; i++) {
		if (isUpperCase(cypher[i])) {
			letteroffset = 65;		//if it's an uppercase letter, the offset is set to 65
			applyBackShift = 1;			//allows the shift to be applied
		}
		else if (isLowerCase(cypher[i])) {
			letteroffset = 97;		//if it's an lowercase letter, the offset is set to 97
			applyBackShift = 1;			//allows the shift to be applied
		}
		else {
			letteroffset = 0;		//sets offset to 0 just in case
			applyBackShift = 0;			//tells function to do nothing to the character
		}
		if (applyBackShift) {
			cypher[i] = cypher[i] - letteroffset;		//bring the letter down to 0-25 to optiimize use of the mod function
			cypher[i] = cypher[i] - backshift;	//apply shift
			if (cypher[i] < 0) {
				cypher[i] = 26 + cypher[i];
			}
			cypher[i] = cypher[i] + letteroffset;		//preserve the case
		}
	}
}


