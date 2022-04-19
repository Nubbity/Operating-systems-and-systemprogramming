/*  
    Käyttöjärjestelmät ja systeemiohjelmointi 2022
    Santeri Hynninen
    0565519
    Project 1: Warmup to C and Unix programming
    22.2.2022
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Struct, which stores amount of lines and lines itself.
typedef struct Lines
{
    char** text;
    long int rl;
}Lines;

//reading from file
Lines* readFile(char file[], FILE *fp){
    //allocates memory to allow use of reallock
    char **text = malloc(0);
    if(!text){fprintf(stderr, "malloc failed\n");exit(1);}
    long int lr = 0;//lines read
    long int buf = 0;//buffer
    char* lptr = NULL;//line pointer
    while(1){//read until EOF
        buf = 0;
        lptr = NULL;

        if(getline(&lptr, &buf, fp) == -1){break;}
        text = realloc(text, sizeof(text) + buf);//allocates new memory if needed
        if(!text){fprintf(stderr, "malloc failed\n");exit(1);}
        text[lr] = lptr;//saves the row
        lr++;
    }
    free(lptr);
    Lines *lines = malloc(sizeof(text) + sizeof(Lines));//allocate memory for struct so it is possible to return both
    if(!lines){fprintf(stderr, "malloc failed\n");exit(1);}
    lines->text = text;
    lines->rl = lr;
    return lines;
    }
//writing to the file
void writeLine(char file[], Lines* lines, FILE* fp){
    char **text = lines->text;
    long int rl = lines->rl-1;
    int last = 1;//last row will probably not have new line character
    while(1){
        if(rl ==-1){break;}
        fprintf(fp, "%s", text[rl]);
        if(last){
            fprintf(fp, "\n");
            last = 0;
        }

        rl--;
    
    }
    return;
}
//memory management
//frees all allocated memory
void memoryManager(Lines * lines){
    
    char **text = lines->text;
    long int rl = lines->rl-1;
    while(1){
        if(rl ==-1){break;}
        free(text[rl]);
        rl--;
    }
    free(text);
    free(lines);
    return;
}
int main(int argc, char *argv[]){
    FILE* fpIn;
    FILE* fpOut;
    char input[200];
    char output[200];
    
    //no arguments
    if(argc == 1){
        fpIn = stdin;
        fpOut = stdout;
        strcpy(input, "stdin");
        strcpy(output, "stdout");
    }
    //only input
    else if(argc == 2){
        strcpy(output, "stdout");
        strcpy(input, argv[1]);
        fpIn = fopen("input.txt", "r");
        fpOut = stdout;
        
    }
    //input and output
    else if (argc == 3)
    {   
        strcpy(input, argv[1]);
        strcpy(output, argv[2]);
        fpIn = fopen(input, "r");
        fpOut = fopen(output, "w");
        //if files are match
        if(strcmp(argv[1], argv[2]) == 0){
            fprintf(stderr, "Input and output file must differ\n");
    }
    }
    else{
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
   
    if((!fpOut)){
        fprintf(stderr, "error: cannot open file '%s'\n", output);
        exit(1);
    }
    if((!fpIn)){
        fprintf(stderr, "error: cannot open file '%s'\n", input);
        exit(1);
    }
    Lines* lines = readFile(input, fpIn);
    writeLine(output, lines, fpOut);
    memoryManager(lines);
    

    fclose(fpOut);
    fclose(fpIn);
    return 0;
}
