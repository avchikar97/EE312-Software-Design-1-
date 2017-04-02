/*******************
Chikarmane, Akaash
avc536
Section #: 16290
EE312 - Assignment 6
*******************/

#include <stdlib.h>
#include <stdio.h>
#define		TRUE	1
#define		FALSE	0
int is_initialized = FALSE;

//Initialize the starting point of the array
void init_heap(char heap[]){
	long int init_meta = 2496;
	long int* init_pt = (long int*)(&heap[0]);
	char* c = (char*)(&init_meta);
	for (int i = 0; i < 8; i++) {
		heap[i] = *(c + i);
		heap[(10000 - 8) + i] = *(c + i);
	}
	is_initialized = TRUE;
	return;
}

//Allocate requested memory
char *my_malloc(char heap[], int numbytes) {
	printf("My malloc called\n");
	if (!is_initialized) {
		init_heap(heap);
	}
	char* data_pointer = NULL;
	char* meta_pt = NULL;
	int totalbytes = 0;
	int i = 10000 - 8, allocated = FALSE;
	long int* current_meta = (long int*)(&heap[i]);		//*current_meta is always the bottom metadata
	long int numwords, temp, meta_value;	//numwords is the number of words to reserve, temp is used to get the proper number of words, meta_value = (-numwords) and is the value to put into the metadata at allocation time
	numwords = (numbytes / 4);	//after if condition below, numwords to be allocated = ceiling of (numbytes/4) + 4 words for top and bottom metadata
	temp = numbytes % 4;
	if (temp) {
		numwords++;	//round up because the number of bytes is between two multiples of 4
	}
	totalbytes = numwords * 4;		//number of bytes that will be taken up in allocation of data (add 16 to include metadata)
	while ((!allocated) && ((i - totalbytes - 8) >= 0)) {	//stop when: (1) space has been allocated (2) pointer to top metadata of possible allocated space in terms of index is less than or equal to 7 (2496 metadata)
		if ((*current_meta) > (numwords + 4)) {		//This condition means the block can be split.
			long int othersplit = ((*current_meta) - 4) - numwords;		//the free part of the split memory will have (# words in free block) + (# words in allocated block) = (previous # of words) - 4. This is the metadata
			char* free_pt = (char*)(&othersplit);
			meta_value = numwords * (-1);		//assign meta_value as negative of the number of words to allocate
			meta_pt = (char*)(&meta_value);
			for (int s = 0; s < 8; s++) {
				heap[i + s] = *(meta_pt + s);		//assigns bottom allocated metadata
				heap[(i - totalbytes - 8) + s] = *(meta_pt + s);	//assigns top allocated metadata
			}
			data_pointer = &heap[i - totalbytes];		//data_pointer is now the "top" of the data part just allocated

			current_meta = (long int*)(&heap[i]);
			i = i - totalbytes - 16;		//adjust i to change the metadata of the free part of the split. i is the where the free metadata needs to be stored
			for (int s = 0; s < 8; s++) {
				heap[i + s] = *(free_pt + s);		//assigns bottom free metadata
				heap[(i - (othersplit*4) - 8) + s] = *(free_pt + s);		//assigns top free metadata
			}
			allocated = TRUE;
		}
		else if ((*current_meta) >= numwords) {		//This condition means the entire block is needed (not greater than numwords+4 but still greater than numwords).
			totalbytes = (*current_meta) * 4;		//change totalbytes to the size of the block * 4 since you're allocating the entire block
			meta_value = (*current_meta)*-1;		//need whole block so meta_value is negative of *current_meta
			meta_pt = (char*)(&meta_value);
			for (int s = 0; s < 8; s++) {
				heap[i+s] = *(meta_pt + s);		//assigns bottom allocated metadata
				heap[(i - totalbytes - 8) + s] = *(meta_pt + s);		//assigns top allocated metadata
			}
			data_pointer = &heap[i - totalbytes];
			allocated = TRUE;
		}
		else {
			if ((*current_meta) > 0) {
				i = i - ((*current_meta) * 4);		//&heap[i] points to the top of the data when chunk is free but too small
			}
			else if ((*current_meta) < 0) {
				i = i - ((*current_meta) * -4);		//&heap[i] points to the top of the data when chunk is used and too small
			}
			i = i - 16;				//&heap[i] points to the metadata above the chunk that's just been looked at
		}
		current_meta = (long int*)(&heap[i]);
	}
	if (!allocated) {
		data_pointer = NULL;
		printf("Sorry nothing is available!\n");
	}
	return data_pointer;
}

//Deallocate requested memory
void my_free(char slab[], char *p) {
	if (!is_initialized) {
		init_heap(slab);
	}
	long int* chunkabove = NULL;
	long int* chunkbelow = NULL;
	long int newmeta = 0;
	char* bottom_meta = p;		//use bottom_meta to point to the bottom metadata
	char* top_meta = p - 8;		//use top_meta to point to the top metadata (top_meta now points to the top metadata)
	char* c = NULL;		//c will be used to put the now positive metadata into the previously negative metadata (indicates freed)
	long int* meta_words = (long int*)(p - 8);		//use meta_words to get the positive version to overwrite current metadata
	long int numwords = (*meta_words)*(-1);		//numwords has the number of words so add numwords*4 to bottom_meta
	newmeta = numwords;
	bottom_meta = bottom_meta + (numwords * 4);		//bottom_meta now points to the bottom metadata
	fprintf(output, "Before: Top: %li, Bottom: %li\n", *top_meta, *bottom_meta);
	c = (char*)(&numwords);
	for (int i = 0; i < 8; i++) {		//changes the top and bottom metadata byte by byte
		*(top_meta + i) = *(c + i);		//top metadata is now positive
		*(bottom_meta + i) = *(c + i);		//bottom metadata is now positive
	}
	if ((top_meta) > slab) {		//if the chunk of p is not the top chunk
		chunkabove = (long int*)(p - 16);		//chunkabove now points to the metadata of the chunk above p
		if ((*chunkabove) > 0) {		//basically if the memory above is free
			newmeta = (*chunkabove) + numwords + 4;		//the new metadata value of the combined chunks
			top_meta = top_meta - 8 - ((*chunkabove)*4) - 8;		//top_meta = current - (top chunk metadata) - (top chunk data) - (top chunk metadata)
			c = (char*)(&newmeta);
			for (int i = 0; i < 8; i++) {		//changes the top and bottom metadata byte by byte
				*(top_meta + i) = *(c + i);		//top metadata is now positive
				*(bottom_meta + i) = *(c + i);		//bottom metadata is now positive
			}
		}
	}
	if ((bottom_meta + 8) < (&slab[9999])) {		//if the chunk of p is not the bottom chunk
		chunkbelow = (long int*)((p + (numwords * 4) + 8));		//chunk below now points to the metadata of the chunk below p
		if ((*chunkbelow) > 0) {		//if the memory below is free
			newmeta = (*chunkbelow) + newmeta + 4;	//words in chunk below + the metadata
			bottom_meta = bottom_meta + 16 + ((*chunkbelow) * 4);	//bottom_meta = current + (two metadatas) + (the data of the bottom chunk)
			c = (char*)(&newmeta);
			for (int i = 0; i < 8; i++) {		//changes the top and bottom metadata byte by byte
				*(top_meta + i) = *(c + i);		//top metadata is now positive
				*(bottom_meta + i) = *(c + i);		//bottom metadata is now positive
			}
		}
	}
}