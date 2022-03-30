#include<stdio.h>
#include<stdio.h>
#include<time.h>
#define N 2

void randomise(int array[N][N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N;j++){
            array[i][j] = (random() % 11);
        }
    }

}
void print_array(int array[N][N]){
    for(int i=0; i < N; i++){
        for(int j=0; j < N; j++){
            printf("%-2d ", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int sum(int array[N][N]){
    int przek = 0;
    int suma = 0;
    int col = 0;

    for(int i = 0; i < N; i++){
        col = 0;
        for(int j = 0; j < N; j++){
            suma = suma + array[i][j];
            if(i == j){
                przek = przek + array[i][j];
            }
            col = col + array[j][i];
        }
        printf("Col%d: %d ",i+1,col);
    }
    printf("\nPrzekątna: %d", przek);
    printf("\nWszystkie: %d\n\n", suma);
}

void matrix_multiplicate(int array1[N][N], int array2[N][N]){
    int multi_array[N][N];

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            multi_array[i][j] = 0;
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                multi_array[i][j] += array1[i][k] * array2[k][j]; 
            }
        }
    }
    print_array(multi_array);
}

int main(){

    srandom(time(NULL));

    int tab1[N][N];
    int tab2[N][N];

    randomise(tab1);
    randomise(tab2);

    printf("tab1 : \n\n");
    print_array(tab1);

    printf("tab2 : \n\n");
    print_array(tab2);
    sum(tab1);
    printf("Wynik mnożenia: \n\n");
    matrix_multiplicate(tab1,tab2);



    return 0;
}