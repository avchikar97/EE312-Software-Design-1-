/*******************
Chikarmane, Akaash
avc536
Section #: 16290
EE312 - Assignment 6
*******************/
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define MEM_SIZE 10000


void init_heap(char slab[]);
char *my_malloc(char slab[], int numbytes);
void my_free(char slab[], char *p);
void Test_Combine(char slab[]);		//debugging function
void Test_FreeMalloc(char slab[]);	//debugging function

int main() {
	char slab[MEM_SIZE] = { 0 }; // Memory that's being used
								 /*Your should write your own test cases to test your program */
	init_heap(slab);
	Test_Combine(slab);
	Test_FreeMalloc(slab);
	
	while (1);	 
}

void Test_Combine(char slab[]) {
	char* a = my_malloc(slab, 4);
	char* b = my_malloc(slab, 5);
	char* c = my_malloc(slab, 9);
	my_free(slab, b);
	my_free(slab, a);
	my_free(slab, c);
}

void Test_FreeMalloc(char slab[]) {
	FILE* output = NULL;
	output = fopen("output.txt", "w");	 
	if (output == NULL) {
		printf("Dun messed up");	 
		exit(1);	 
	}	 
	char* pointers[120];	 
	int i = 0;	 
	for(int s = 0; s < 10; s++) {	 
		char* p = my_malloc(slab, 4);	 
		fprintf(output, "Malloc s#%i: p = %p\n", s, p);	 
		pointers[s] = p;	 
	}	 
	for(int s = 0; s < 10; s++) {	 
		my_free(slab, pointers[s]);	 
		fprintf(output, "Free s#%i: p = %p\n", s, pointers[s]);	 
	}	 
	for(int s = 0; s < 10; s++) {	 
		char* p = my_malloc(slab, 5);	 
		fprintf(output, "Malloc s#%i: p = %p\n", s, p);	 
		pointers[s] = p;	 
	}	 
	for(int s = 0; s < 10; s++) {	 
		my_free(slab, pointers[s]);	 
		fprintf(output, "Free s#%i: p = %p\n", s, pointers[s]);	 
	}
	i = 0;
	char* smores[500] = { NULL };
	while (1) {	 
		char* p = my_malloc(slab, 9);	 
		printf("Malloc #%i: p = %p\n", i, p);	 
		smores[i] = p;
		i--;
		if (p == NULL) {
			for (i; i > 0; i--) {
				my_free(slab, smores[i]);
			}
			fclose(output);
			i--;
		}
	}
}