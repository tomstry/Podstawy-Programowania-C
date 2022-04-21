#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

char* getHexAscii(char *sign){
    char *hex = malloc(2 * sizeof(char));
    sprintf(hex,"%02X",sign[0]);
    return hex;
}

char** getData(int* len){
    char **arr = calloc(3,sizeof(char*));
    char *buff = NULL;
    (*len) = 0;
    size_t ll;

    while(true){
        int read = getline(&buff, &ll,stdin);

        if(read == -1)
        break;

        if(*len > 2){
            arr = realloc(arr,(*len + 1) * sizeof(char*));
        }

        if(buff[read - 1] != '\n')
            read++;
        
        buff[read - 1] = 0;
        arr[*len] = malloc(read * sizeof(char));
        memcpy(arr[*len],buff,read * sizeof(char));
        (*len)++;
    }
    return arr;
}

int main(){
    /*char *x = NULL;
    size_t len;
    getline(&x,&len,stdin);
    x = getHexAscii(x);
    printf("%s\n", x);*/
    int len;
    char **q = getData(&len);
    for(int i=0; i<len;i++){
        printf("\n");
        printf("%s",*(q +i));
    }
    printf("\n");
    return 0;
}