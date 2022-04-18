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
#include <fcntl.h>


#define PATH "/bin"

#define ERROR_ACCESS "Could not access the command.\n"
#define ERROR_EXIT "not able to use given arguments with exit\n"
#define ERROR_CD "Give excactly one argument with cd\n"
#define ERROR_OWD "failed to get owd\n"
#define ERROR_CWD "failed to get cwd\n"
#define ERROR_MEMORY "Failed to allocate memory\n"
#define ERROR_FILE "Failed to open the file\n"
#define ERROR_EXECV "Failed to run the command\n"

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
    char str[PATH_MAX] = "PATH=";
    char ss[2] = ":";
    if(!strcmp(arguments[0], "exit")){
        if(!arguments[1]){
            printf("Exiting wish\n");
            exit(0);}
        else{
              write(STDERR_FILENO, ERROR_EXIT, strlen(ERROR_EXIT));
        }
        return 1;
    }
    else  if(!strcmp(arguments[0], "path")){
        if(arguments[1] == NULL){setenv("PATH", "", 1);}
        else{
            for (int i = 1;; i++)
            {   if(arguments[i] == NULL){break;}
                putenv(strcat(str, arguments[i]));
                strcat(str, ss);
            }
        }
        printf("New Path(s) are: %s\n", getenv("PATH"));
        return 1;}
    else  if(!strcmp(arguments[0], "cd")){
        if(!arguments[1] || arguments[2]){
            write(STDERR_FILENO, ERROR_CD, strlen(ERROR_CD));
        }
        else{
            char owd[PATH_MAX];
            char cwd[PATH_MAX];
            if (getcwd(owd, sizeof(owd))){
                printf("Old working dir: %s\n", owd);}
            else{write(STDERR_FILENO, ERROR_OWD, strlen(ERROR_OWD));}
            chdir(arguments[1]);
            if (getcwd(cwd, sizeof(cwd))) {
                printf("New working dir: %s\n", cwd);}
            else{write(STDERR_FILENO, ERROR_CWD, strlen(ERROR_CWD));}
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
int checkOutput(char ** array){
    int fd = 0;
    for (int i = 0;; i++)
    {
        if(!array[i]){return fd;}
        if(strcmp(array[i], ">") == 0){
            char path[PATH_MAX] = "./";
            strcat(path, array[i+1]);
            fd = open(path, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
            array[i] = 0;
            return fd;
        }
    }

}


int main(int argc, char *argv[]){
    setenv("PATH", PATH, 1);//Set path to only contain /bin    
    FILE * fpIn = stdin;
    FILE * fpOut = stdout;
    int fdOut;
    char *buffer;
    size_t bufsize = 0;
    int status;
    char spacer[2] = " ";
    
    buffer = (char *)malloc(bufsize * sizeof(char));

    if(buffer == NULL){
        write(STDERR_FILENO, ERROR_MEMORY, strlen(ERROR_MEMORY));
        exit(1);
    }
    if(argc == 1){
        fpIn = stdin;
    }
    else if(argc == 2){
        fpIn = fopen(argv[1], "r");

    
        if (!fpIn)
        {
            write(STDERR_FILENO, ERROR_FILE, strlen(ERROR_FILE));
     
            exit(1);
        }
    }
    else{exit(1);}

    
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
                        if ((fdOut = checkOutput(arguments))){
                            dup2(fdOut, STDOUT_FILENO);
                            dup2(fdOut, STDERR_FILENO);
                        }
                        
                        if(-1 == execvp(arguments[0],arguments)){
                            write(STDERR_FILENO, ERROR_EXECV, strlen(ERROR_EXECV));}
                        close(fdOut);
                        exit(0);}
                }
            }
            wait(&status);
            if(argc == 1){printf("wish>");}
        }
        
}

