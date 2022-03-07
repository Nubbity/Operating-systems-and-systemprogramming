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

void fileToStdout(char filename[300]){
    FILE* fp = fopen(filename, "r");
    if(!fp){printf("my-cat: cannot open file\n"); exit(1);}
    while(1){//Luetaan kunnes EOF
        char * line = malloc(100);
        if(!line){exit(0);}
        long int buf = 0;
        if(getline(&line, &buf, fp) == -1){break;}
        else{fprintf(stdout, "%s", line);}
        free(line);
    }

}

int main(int argc, char *argv[]){
    //No files
    if(argc == 1){fprintf(stderr, "Usage: my-cat <input file>\n");exit(1);}
    //käydään kaikki tiedostot läpi
    for (int i = 1; i < argc; i++)
    {
        fileToStdout(argv[i]);
    }
    return 0;
}
