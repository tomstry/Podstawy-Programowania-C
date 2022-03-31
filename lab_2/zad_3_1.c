#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void print_array(int* array, int len){
    for(int i=0; i < len; i++){
        for(int j = 0; j < len; j++){
            printf("%-2d ", array[i * len + j]);
        }
        printf("\n");
    }
    printf("\n");
}

int lower(int* array, int len){
    for(int i = 0; i < len; i++){
        for(int j = i + 1;j < len; j++){
            if((*(array + ((i * len) + j))) != 0){
                return false;
            }
        }
    }
    return true;
}


int main(){

    int len;
    printf("Podaj rozmiar macierzy: ");
    scanf("%d", &len);

    int *array;
    array = (int*)malloc(len * len * sizeof(*array));

    for(int i = 0; i < len * len; i++){
        scanf("%d", (array + i));
    }
    print_array(array, len);

    int lower_triangle = lower(array,len);

    if(lower_triangle){
        printf("To jest tablica trójkątna dolna :)\n");
    }
    else{
        printf("To nie jest tablica tróəkątna dolna :(\n");
    }
    
    free(array);
    return 0;
}