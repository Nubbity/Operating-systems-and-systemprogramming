/*  
    Käyttöjärjestelmät ja systeemiohjelmointi 2022
    Santeri Hynninen
    0565519
    Project 2: Unix Utilities:CAT
    22.2.2022
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Opens file and prints it to stdout until it counters EOF or other error
void fileToStdout(char filename[300]){
    FILE* fp = fopen(filename, "r");//opening file
    if(!fp){printf("my-cat: cannot open file\n"); exit(1);}//if file cant be opened
    char * line = NULL;
    size_t buf = 0;
    while(getline(&line, &buf, fp) >=0){//read until EOF
        fprintf(stdout, "%s", line);//printed to stdout
    }
    fclose(fp);
    free(line);
    fprintf(stdout, "\n");//seperates files
}

int main(int argc, char *argv[]){
    //No files
    if(argc == 1){fprintf(stderr, "Usage: my-cat <input file>\n");exit(1);}
    //goes trough all files
    for (int i = 1; i < argc; i++)
    {
        fileToStdout(argv[i]);
    }
    return 0;
}