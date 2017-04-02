/*******************
Chikarmane, Akaash
avc536
Section #: 16290
EE312 - Assignment 4
*******************/

#include <stdio.h>
#include <string.h>
#define BEGIN_FCN		{
#define END_FCN			}
#define MAX_LINELENGTH	256
#define TRUE			1
#define FALSE			0

/**Function Prototypes + Short Descriptions**/
void LineInArray(char linearray[], int arraylength, FILE* input);		/*puts current line in FILE* input into linearray*/
void FindFunctionName(char line[], char storename[]);					/*finds the function name within line and store it in the storename array*/

int main(void) {
	/**Variable Initialization**/
	int totalfunction = 0;										//total number of functions in inputfile
	int totalsemicolon = 0;										//total lines of code in inputfiles
	char inputfilename[50] = { '\0' };							/*set aside and initialize space for the input file name*/
	FILE* inputfile;
	char outputfilename[50] = { '\0' };							//set aside and initialize space for output file name
	FILE* outputfile;
	char function[50] = { '\0' };								/*keeps the current function name*/
	char previousline[MAX_LINELENGTH] = { '\0' };				/*keeps the previous line (only used to retrieve function name)*/
	char currentline[MAX_LINELENGTH] = { '\0' };				/*keeps the current line (only look at this line when looking for semicolons)*/
	int semicolon = 0;											/*semicolon counter*/
	char c = 0;														/*current character in the input file before actually parsing file, also used for mismatched beginning and end error checking when parsing*/
	int countcolon = FALSE;											/*a flag to count semicolons - 0 to stop counting semicolons, 1 to start*/
	int checkifsemi = TRUE;											/*flag to decide whether or not to check semicolon - FALSE if comment or quote detected*/
	while (1) {		//this is only broken out of when STOP is inputted in the input file name or there is an error fopen-ing
		/**Inputting the file to analyze**/
		printf("Please input a file name to analyze: ");
		scanf("%s", inputfilename);									/*input the file name*/
		if (!strcmp(inputfilename, "STOP")) {
			break;		//stop when you see the STOP sentinel
		}
		inputfile = fopen(inputfilename, "r");						/*set the FILE* with fopen*/
		if (inputfile == NULL) {									/*check for error in fopen-ing*/
			printf("Invalid file name. Now closing function.");
			return(0);
		}
		printf("Please input a file name for output: ");
		scanf("%s", outputfilename);
		outputfile = fopen(outputfilename, "w");						/*set the FILE* with fopen*/
		if (outputfile == NULL) {									/*check for error in fopen-ing*/
			printf("Error creating and opening file.");
			return(0);
		}
		/**Pre-Parsing Outputs**/
		printf("File Counting Summary Table\n\n");					/*lines 14-17 are just printfs to make the terminal table look nice*/
		printf("Filename: %s\n\n", inputfilename);
		printf("Function Name\t\t# Lines of Code\n");
		fprintf(outputfile, "File Counting Summary Table\n\n");
		fprintf(outputfile, "Filename: %s\n\n", inputfilename);
		fprintf(outputfile, "Function Name\t\t# Lines of Code\n");

		/**Start algorithm**/
		/**Condition to stop reading the input file**/
		while (!feof(inputfile)) {									/*feof returns 0 when EOF flag is set*/
			LineInArray(currentline, MAX_LINELENGTH, inputfile);
			if (!strcmp(currentline, "BEGIN_FCN")) {				/*if you find the beginning of the function, you need to (a) Find the function name and (b) start counting semicolon*/
				if (c == TRUE) {
					printf("\nMis-matched begin-end of a function\n");		//conditional code will be hit if there is a function that has a BEGIN_FCN without an END_FCN
					fprintf(outputfile, "\nMis-matched begin-end of a function\n");
					return(0);
				}
				FindFunctionName(previousline, function);
				countcolon = TRUE;										/*set flag to start counting*/
				c = TRUE;		//sets c to 1 when BEGIN_FCN is hit and sets to 0 when matching END_FCN is hit
			}
			if (countcolon) {										/*do not count semicolons if: 1) inside comment 2) inside "" 3) outside of function declaration (taken care of by setting flag)*/
				for (int b = 0; currentline[b] != '\0'; b++) {
					if (checkifsemi == TRUE) {
						if (((currentline[b] == '/') && (currentline[b + 1] == '*')) || (currentline[b] == '"')) {
							checkifsemi = FALSE;		/*comment or literal string has just opened so stop counting util it's closed*/
						}
					}
					else {
						if (((currentline[b] == '*') && (currentline[b + 1] == '/')) || (currentline[b] == '"')) {
							checkifsemi = TRUE;			/*comment or literal has just closed so you may continue counting*/
						}
					}
					if ((currentline[b] == '/') && (currentline[b + 1] == '/')) {
						break;		//stop checking this line if you find a '//' comment
					}
					if (checkifsemi) {
						if (currentline[b] == ';') semicolon++;
					}
				}
			}
			if (!strcmp(currentline, "END_FCN")) {
				if (c == FALSE) {
					printf("\nMis-matched begin-end of a function\n");		//conditional code will be hit if there is a function that has an END_FCN without a BEGIN_FCN
					fprintf(outputfile, "\nMis-matched begin-end of a function\n");
					return(0);
				}
				printf("%s\t\t\t%i\n", function, semicolon);
				fprintf(outputfile, "%s\t\t\t%i\n", function, semicolon);
				totalfunction++;
				totalsemicolon = totalsemicolon + semicolon;
				countcolon = FALSE;
				semicolon = 0;
				memset(function, '\0', 50);	/*resets the function name*/
				c = FALSE;
			}
			memcpy(previousline, currentline, MAX_LINELENGTH);		//copies entire currentline to previousline
		}
		if (totalfunction == 0) {
			printf("\nNo functions were found in this file\n\n");
			fprintf(outputfile, "\nNo functions were found in this file\n\n");
		}
		else {
			printf("\nTotal number of functions: %i\nTotal lines of code: %i\n", totalfunction, totalsemicolon);
			fprintf(outputfile, "\nTotal number of functions: %i\nTotal lines of code: %i\n", totalfunction, totalsemicolon);
		}
		totalfunction = 0;
		totalsemicolon = 0;
		fclose(inputfile);
		fclose(outputfile);
	}
	while (1);
	return(0);
}


/**********************************************************************************************************/
//Function name: LineInArray
//Input: linearray (array that line of text is to be store in), arraylength, FILE* for line to be read from
//Output: None
//Description: copies one line of text with up to arraylength characters into linearray
/**********************************************************************************************************/
void LineInArray(char linearray[], int arraylength, FILE* input) {
	char character = 0;
	int i = 0;
	memset(linearray, '\0', arraylength);				/*clears currentline before putting next line in*/
	while ((character != '\n') && (i < arraylength) && (character != EOF)) {
		character = fgetc(input);
		if ((character != '\n') && (character != '\t')) {
			linearray[i] = character;
			i++;
		}
	}
}

/**********************************************************************************************************/
//Function name: FindFunctionName
//Input: line (in this program it is the previous line before BEGIN_FCN is found, storename (array to store the name)
//Output: None
//Description: Find the name of the function by looking at the line before BEGIN_FCN and stores it in storename array 
/**********************************************************************************************************/
void FindFunctionName(char line[], char storename[]) {
	char* startfunction = strchr(line, ' ');					/*make startfunction point to the first space which would be after the output and right before the function name*/
	startfunction++;											/*to make startfunction point to the first character of the function name*/
	char* endfunction = strchr(line, '(');
	int n = endfunction - startfunction;
	strncpy(storename, startfunction, n);						/*function now has the function name (a) is done*/
}