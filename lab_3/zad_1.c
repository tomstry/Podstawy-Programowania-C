#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

void cezar(char *tekst){
    int shift = 0;
    int len = 0;
    while(tekst[shift] != ' ' && tekst[shift] != 0){
        shift ++;
    }
    if(tekst[shift] == 0){
        shift--;
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

char* getEncryptedLine(){

    char *txt = NULL;
    size_t len;
    int read = getline(&txt, &len, stdin);

    if(read != -1){
        cezar(txt);
        return txt;
    }
    else{
        free(txt);
        return NULL;
    }


}

int main(){

    char tekst[] = "ala ma kota testujemy szyf cezara";
    printf("%s\n", tekst);
    cezar(tekst);
    printf("%s\n", tekst);

    while(true){
        printf("Tekst jawny: ");
        char *txt = getEncryptedLine();
        if(txt == NULL){
            return 0;
        }
        printf("Szyfrogram: %s\n", txt);
        free(txt);
    }


    return 0;
}