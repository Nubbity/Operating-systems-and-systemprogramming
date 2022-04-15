/*  
    Käyttöjärjestelmät ja systeemiohjelmointi 2022
    Santeri Hynninen
    0565519
    Project 3: Unix shell
    14.4.2022
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char** tokenize(char* str, char *spacer)
{
    str[strcspn(str, "\n")] = 0;//removes new line from the command
    char* token;
    char* rest = str;
    char ** array;//returned array which contains pointers to invidual tokens
    int i = 0;
    while ((token = strtok_r(rest, spacer, &rest))){//Goes trough the whole command given
        array[i++] = token;}
    array[i++] = NULL;//Null argument as the last argument for execvp
    return array;
}


int main(int argc, char *argv[]){
    FILE * fpIn;
    char *buffer;
    size_t bufsize = 3;
    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    if(argc == 1){
        fpIn = stdin;
        printf("stdin\n");

    
    }
    else if(argc == 2){
        fpIn = fopen(argv[1], "r");

    
        if (!fpIn)
        {
            fprintf(stderr, "opening file failed. Wish closes.\n");
     
            exit(1);
        }
    }
    else{exit(1);}


    //wish loop starts
        while(1){
            if(argc == 1){printf("wish>");}
            if(getline(&buffer, &bufsize, fpIn) == -1){exit(0);}
            char * token;
            char* rest = buffer;
            char** arguments;
            char spacer[2] = " ";
            while (arguments = tokenize((token = strtok_r(rest, "&", &rest)), spacer)){
                if(fork() == 0){
                if(-1 == execvp(arguments[0],arguments)){printf("not run\n");}}
            }
        }
        
}

