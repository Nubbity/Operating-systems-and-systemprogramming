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
#include<sys/wait.h>
#include <unistd.h>
#include <limits.h>

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
//Default build in commands
int defCmd(char ** arguments){//return 1 if not found and 0 if one found
    char error_message_arguments_exit[50] = "not able to use given arguments with exit\n";
    char error_message_arguments_path[50] = "Give excactly one argument with cd\n";
    char error_message_owd[50] = "failed to get owd\n";
    char error_message_cwd[50] = "failed to get cwd\n";
    if(!strcmp(arguments[0], "exit")){
        if(!arguments[1]){
            printf("Exiting wish\n");
            exit(0);}
        else{
              write(STDERR_FILENO, error_message_arguments_exit, strlen(error_message_arguments_exit));
        }
        return 1;
    }
    else  if(!strcmp(arguments[0], "path")){

        return 1;}
    else  if(!strcmp(arguments[0], "cd")){
        if(!arguments[1] || arguments[2]){
            write(STDERR_FILENO, error_message_arguments_path, strlen(error_message_arguments_path));
        }
        else{
            char owd[PATH_MAX];
            char cwd[PATH_MAX];
            if (getcwd(owd, sizeof(owd))){
                printf("Old working dir: %s\n", owd);}
            else{write(STDERR_FILENO, error_message_owd, strlen(error_message_owd));}
            chdir(arguments[1]);
            if (getcwd(cwd, sizeof(cwd))) {
                printf("New working dir: %s\n", cwd);}
            else{write(STDERR_FILENO, error_message_owd, strlen(error_message_owd));}
        }
        return 1;
    }
    else  if(!strcmp(arguments[0], "help")){
        printf("commands: exit, path, cd\n");
        return 1;
    }
    else{
        return 0;}
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

    int status;
    char spacer[2] = " ";
    if(argc == 1){printf("wish>");}
    //wish loop starts
        while(1){
            if(getline(&buffer, &bufsize, fpIn) == -1){break;
            }
            char* rest = buffer;
            char** arguments;
            char * token;
            while (token = strtok_r(rest, "&", &rest)){
                arguments = tokenize(token, spacer);
                if(!defCmd(arguments)){
                    if(fork() == 0){
                        if(-1 == execvp(arguments[0],arguments)){printf("not run\n");exit(0);}}
                }
            }
            wait(&status);
            if(argc == 1){printf("wish>");}
        }
        
}

