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

//Zip files to contain <count of following chars><char>
void zipFile(FILE * fpIn, FILE * fpOut){
    char current = (char)0;
    char last = (char)0;
    int n = 1;

    while ((current = fgetc(fpIn))!= EOF)
    {
        if(current == last){//if same char add to counter
            n++;
        }
        else{
           fwrite(&n, sizeof(int),1, fpOut);//write 4 byte integer to file
           fwrite(&last,sizeof(char),1, fpOut);//write ascii char to file
           n = 1;
        }
        last = current;
    }
    
}
int main(int argc, char *argv[]){
    //No files
    
    if(argc == 1){fprintf(stderr, "my-zip: file1 [file2 ...]\n");exit(1);}
    else if (argc == 2)
    {
        zipFile(stdin, fopen(argv[1], "a"));
    }
    else{
    //goes trough all files
    for (int i = 2; i < argc; i++)
    {   
        FILE* fp = fopen(argv[i], "r");//opens file
        if(!fp){printf("my-zip: cannot open file\n"); exit(1);}//if file is not found
        zipFile(fp,fopen(argv[1], "a"));
        fclose(fp);
    }}
    return 0;
}

