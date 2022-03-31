#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void randomise(int** arr, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            *(*(arr + i) + j) = rand() % 101;
            printf("%-2d ", *(*(arr + i) + j)); 
        }
        printf("\n");
    }
}

int main(){

    srand(time(NULL));
    int m,n;

    printf("Podaj n: ");
    scanf("%d", &n);
    printf("Podaj m: ");
    scanf("%d", &m);

    int** array;
    array = (int**)malloc(n * sizeof(int*));

    for(int i = 0; i < n; i++){
        *(array + i) = (int*)malloc(m * sizeof(int*));
    }
    randomise(array,n,m);

    for(int i = 0; i < m; i++){
        free(*(array + i));
    }

    free(array);

    return 0;
}