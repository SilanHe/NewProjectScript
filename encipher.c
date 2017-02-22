/*
 ============================================================================
 Name        : CaesarShift.c
 Author      : Silan
 Version     :
 Copyright   : Your copyright notice
 Description : encrypt a file
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
    int c;

    if (file == NULL)
        return 0; //could not open file
    //allocate memory of 1000 bytes hopefully enough for the scope of the exercise
    content = malloc(1000);
    //read the contents
    while ((c = fgetc(file)) != EOF)
    {
        content[n++] = (char) c;
    }

    // terminate with the null character
    content[n] = '\0';        

    return content;
}

char calShift(int n_shift, char c){
	//handle the encryption depending on where the character is on ascii
		if ((c>=65+n_shift && c<=92) || (c>=97+n_shift && c<=122)){
			return c-n_shift;
		}else if (c>=65 && c<=65+n_shift){
			return 93-(n_shift-(c-65));
		}else if (c>=97 && c<=97+n_shift){
			return 123-(n_shift-(c-97));
		}else{
			return c;
		}
}
char *shift(char *content, int key){
	//shift the string accodring to key
	char* result;
	int i;
	int n_shift= key%25+1;//shift 1 to 25

	//allocate memory of 1000 bytes hopefully enough for the scope of the exercise
	result = malloc(1000);

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
		//handler arguments
		char* fileName = argv[1];
		int key = atoi(argv[2]);
		//read,shift,write
		char *content=readFile(fileName);
		char *shifted=shift(content,key);
		writeFile(shifted,fileName);
	}
	return EXIT_SUCCESS;
}

