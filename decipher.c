/*
 ============================================================================
 Name        : CaesarShift.c
 Author      : Silan
 Version     :
 Copyright   : Your copyright notice
 Description : decrypt a file
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readFile(char *fileName){
	//read the file into a string
    FILE *file = fopen(fileName, "r");
    char *content;
    size_t n = 0;
    int c;//counter

    if (file == NULL)
        return 0; //could not open file

    content = malloc(1000); //limitation of 1000 bytes

    //read content of file
    while ((c = fgetc(file)) != EOF)
    {
        content[n++] = (char) c;
    }

    // terminate with the null character
    content[n] = '\0';        

    return content;
}

char calShift(int n_shift, char c){
	//handle decryption depending on where character is on ascii
		if ((c>=65 && c<=92-n_shift) || (c>=97 && c<=122-n_shift)){
			return c+n_shift;
		}else if (c>=92-n_shift && c<=92){
			return 64+(n_shift+c-92);
		}else if (c>=122-n_shift && c<=122){
			return 96+(n_shift+c-122);
		}else{
			return c;
		}
}
char *shift(char *content, int key){
	//shift the string according to key
	char* result;
	int i;
	int n_shift= key%25+1;//shift 1 to 25
	//allocate memory of 1000 bytes hopefully enough for the scope of the exercise
	result = malloc(1000);
	//re shift content
	for (i = 0; i < strlen(content); i++){

		result[i] = (char) (calShift(n_shift, content[i]));
	}
	// terminate with the null character
	result[strlen(content)] = '\0';

	return result;
}
int writeFile(char *contents, char* fileName){
	//write the string into the file
    FILE *file = fopen(fileName, "w+");

    if (file == NULL)
        return 0; //could not open file
    //write into file
    fputs(contents,file);
    

    return 1;
}

int main(int argc,char *argv []) {
	//if not right amount of arguments
	if (argc!=3){
		puts("Not the right amount of arguments. Please type: CaesarShift filename key");
		return EXIT_SUCCESS;
	}else{
		//handle arguments
		char* fileName = argv[1];
		int key = atoi(argv[2]);
		//read,shift back, write
		char *content=readFile(fileName);
		char *shifted=shift(content,key);
		writeFile(shifted,fileName);

	}
	return EXIT_SUCCESS;
}


