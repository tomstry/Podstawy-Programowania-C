#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void cezar(char *tekst){
    int shift = 0;
    int len = 0;
    while(tekst[shift] != ' ' && tekst[shift] != 0){
        shift ++;
    }
    while(tekst[len] != 0){
        len ++;
    }

    for(int i = 0; i < len; i++){
        if(tekst[i] != ' '){
            if(isupper(tekst[i])){
                tekst[i] = ((tekst[i] - 65 + shift) % 26) + 65;
            }
            else if(islower(tekst[i])){
                tekst[i] = ((tekst[i] - 97 + shift) % 26) + 97;
            }
        }
    }

}