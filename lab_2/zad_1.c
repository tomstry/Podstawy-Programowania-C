#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N1 4
#define N2 6
#define N 20
#define N3 N1 + N2


void randomize(int array[], int length, int max, int min){

    for(int i = 0; i < length; i++ ){
        array[i] = ((rand() % (max - min +1)) + min);
    }

}

void print_arr(int array[],int size){

    for(int i = 0;i < size; i++){
        printf("%.1d ", array[i]);
    }
    printf("\n");
}

void reverse(int array[],int size){
    int j = size - 1;
    for(int i = 0; i <= size / 2; i++){

        int temp = array[j];
        array[j] = array[i];
        array[i] = temp;
        --j;
    }
}

void array_sort(int array[],int size){

    for(int i = 0; i < size -1; i++){
        for(int j = 0; j < size - i - 1; j++ ){

            if(array[j] > array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

int one_two(int ar1[], int len1, int ar2[], int len2, int arr[]){
    int i = 0;
    int j = 0;
    int k = 0;

    if(ar1[i] < ar2[j]){
        arr[k] = ar1[i];
        i++;
    }
    else{
        arr[k] = ar2[j];
        j++;
    }
    k++;

    while(i < len1 && j < len2){
        if(ar1[i] < ar2[j]){
            if(arr[k-1] != ar1[i]){
                arr[k] = ar1[i];
                i++;
                k++;
            }
            else{
                i++;
            }
        }
        else{
            if(arr[k-1] != ar2[j]){
                arr[k] = ar2[j];
                j++;
                k++;
            }
            else{
                j++;
            }
        }
        
    }
    while( i < len1){
            if(arr[k-1] != ar1[i]){
                arr[k] = ar1[i];
                i++;
                k++;
            }
            else{
                i++;
            }
        }
    
    while(j < len2){
        if(arr[k-1] != ar2[j]){
            arr[k] = ar2[j];
            j++;
            k++;
        }
        else{
            j++;
        }

        }
    int size = k;
    return size;
}
void statistics(int array[], int size){
    float tab[21];
    for(int j = 0; j < 22;j++){
        tab[j] = 0;
    }
    for(int i = 0; i < size;i++){
        tab[array[i] + 10]++;
    }
    for(int k = 0; k < 22;k++){
        tab[k] = tab[k] / 21;
    }
    for(int l = 0; l < 22;l++){
        printf("%.2f%% ", tab[l] * 100);
    }
    printf("\n");
}


int main(){

    const int min = 1;
    const int max = 10;

    srand(time(NULL));


    int t1[N1];
    int t2[N2];
    int t[N];

    randomize(t1, N1, max, min);
    randomize(t2, N2, max, min);
    randomize(t,N,10,-10);
    array_sort(t1,N1);
    array_sort(t2,N2);

//    print_arr(t1, N1);
//    print_arr(t2, N2);

    int t3[N3];
    int len3 = one_two(t1,N1,t2,N2,t3);
    print_arr(t3, len3);
 //   statistics(t,N);



    return 0;
}