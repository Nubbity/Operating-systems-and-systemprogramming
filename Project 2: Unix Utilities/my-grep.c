/*  
    Käyttöjärjestelmät ja systeemiohjelmointi 2022
    Santeri Hynninen
    0565519
    Project 2: Unix Utilities:GREP
    22.2.2022
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Reads file and finds all rows where word is used and prints them
void grepWanted(FILE *fp, char word[300]){
    
    
    char * line = NULL;
    size_t buf = 0;
    while(getline(&line, &buf, fp) >=0){//Read until EOF
         if(strstr(line, word)){fprintf(stdout, "%s", line);}//if word is used line is printed
    }
    
    free(line);
    fprintf(stdout, "\n");//seperates read rows
}

int main(int argc, char *argv[]){
    //No files
    
    if(argc == 1){fprintf(stderr, "my-grep: searchterm [file ...]\n");exit(1);}
    else if (argc == 2)
    {
        grepWanted(stdin, argv[1]);
    }
    else{
    //goes trough all files
    for (int i = 2; i < argc; i++)
    {   
        FILE* fp = fopen(argv[i], "r");//opens file
        if(!fp){printf("my-grep: cannot open file\n"); exit(1);}//if file cant be opened
        grepWanted(fp, argv[1]);
        fclose(fp);
    }}
    return 0;
}
