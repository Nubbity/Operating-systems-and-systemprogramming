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


void grepWanted(FILE *fp, char word[300]){
    
    
    char * line = NULL;
    size_t buf = 0;
    while(getline(&line, &buf, fp) >=0){//Luetaan kunnes EOF
         if(strstr(line, word)){fprintf(stdout, "%s", line);}//tulostetaan konsoliin jos substring on rivillä
    }
    
    free(line);
    fprintf(stdout, "\n");//erotetaan luetut tiedostot toisistaan
}

int main(int argc, char *argv[]){
    //No files
    
    if(argc == 1){fprintf(stderr, "my-grep: searchterm [file ...]\n");exit(1);}
    else if (argc == 2)
    {
        grepWanted(stdin, argv[1]);
    }
    else{
    //käydään kaikki tiedostot läpi
    for (int i = 2; i < argc; i++)
    {   
        FILE* fp = fopen(argv[i], "r");//Tiedoston avaaminen
        if(!fp){printf("my-grep: cannot open file\n"); exit(1);}//Jos tiedostoa ei löydy/ei voi avata
        grepWanted(fp, argv[1]);
        fclose(fp);
    }}
    return 0;
}
