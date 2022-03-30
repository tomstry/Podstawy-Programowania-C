#include<stdio.h>
#include<stdio.h>
#include<time.h>
#define N 8

void randomise(int array[N][N],int min,int max){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N;j++){
            array[i][j] = (rand() % (max - min +1)) + min;
        }
    }

}
void print_array(int array[N][N]){
    for(int i=0; i < N; i++){
        for(int j=0; j < N; j++){
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}
int sum(int array[N][N]){
    int przek = 0;
    int suma = 0;
    int col = 0;

    for(int i = 0; i < 8; i++){
        col = 0;
        for(int j = 0; j < 8; j++){
            suma = suma + array[i][j];
            if(i == j){
                przek = przek + array[i][j];
            }
            col = col + array[j][i];
        }
        printf("Col%d: %d ",i,col);
    }
    
}



int main(){

    srand(time(NULL));

    int tab1[N][N];
    int tab2[N][N];

    randomise(tab1[N][N],0,10);
 //   print_array(tab1[N][N]);
    
    for(int i=0; i < N; i++){
        for(int j=0; j < N; j++){
            printf("%d ", tab1[i][j]);
        }
        printf("\n");
    }




    return 0;
}