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
    FILE* fp = fopen(filename, "r");//Tiedoston avaaminen
    if(!fp){printf("my-cat: cannot open file\n"); exit(1);}//Jos tiedostoa ei löydy/ei voi avata
    char * line = NULL;
    size_t buf = 0;
    while(getline(&line, &buf, fp) >=0){//Luetaan kunnes EOF
        fprintf(stdout, "%s", line);//tulostetaan konsoliin
    }
    fclose(fp);
    free(line);
    fprintf(stdout, "\n");//erotetaan luetut tiedostot toisistaan
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