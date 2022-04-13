/*  
    Käyttöjärjestelmät ja systeemiohjelmointi 2022
    Santeri Hynninen
    0565519
    Project 2: Unix Utilities:ZIP
    22.2.2022
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void unzipFile(FILE * fpIn, FILE * fpOut){
    int lenght = 0;
    char last = (char) 0;
    if(!fpIn || !fpOut){printf("my-grep: cannot open file\n"); exit(1);}
    while (1)
    {
        if(1 != fread(&lenght, sizeof(int), 1, fpIn)){break;}//Read number
        if(1 != fread(&last, sizeof(char), 1, fpIn)){break;}//Read char

        for (;lenght > 0; lenght--){
            fprintf(fpOut, "%c", last);
            }
        lenght = 0;
       
    }
    fclose(fpOut);
    fclose(fpIn);
    
}
int main(int argc, char *argv[]){
    if(argc == 1){fprintf(stderr, "my-unzip: file1 [file2 ...]\n");exit(1);}
    else if (argc == 2)
    {
        unzipFile(fopen(argv[1], "r"), stdout);
    }
    else if (argc == 3){
        unzipFile(fopen(argv[1], "r"), fopen(argv[2], "w"));
    }
    else{
        fprintf(stderr, "my-zip: file1(Input) [file2(Output)]\n");
    }
    return 0;
}

