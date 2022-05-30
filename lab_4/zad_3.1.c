#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int get_num(FILE *file, int i){
    fseek(file,0,SEEK_SET);
    int a;
    for(int j = 0; j <= i; j++){
        fscanf(file,"%i", &a);
    }
    return a;
}

int multiply(FILE *matrix1, FILE *matrix2, FILE *matrix3){
    int row1 = 0,col1 = 0,col2 = 0,row2 =0;
    char ch;
    while(!feof(matrix1)){
        ch = fgetc(matrix1);
        if(ch == '\n'){
            row1++;
        }
        if(ch == ' '){
            col1++;
        }
    }
    row1++;
    col1 = col1/row1 + 1;
    while(!feof(matrix2)){
        ch = fgetc(matrix2);
        if(ch == '\n'){
            row2++;
        }
        if(ch == ' '){
            col2++;
        }
    }
    row2++;
    col2 = col2/row2 +1;
        
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            int s = 0;
            for (int k = 0; k < col1; k++){
                s += get_num(matrix1, i * col1 + k) * get_num(matrix2, j + col2 * k);
            }
            fprintf(matrix3, "%i\t", s);
        }
        fprintf(matrix3, "\n");
    }
}


int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Wprowadź poprawne argumenty !!!!");
        exit(1);
    }
    else{
        FILE *list;
        list = fopen(argv[1],"r");

        int count = 0;
        char file1[20],file2[20],file3[20];
        char x;
        for(x = getc(list); x != EOF; x = getc(list))
            if(x ==' ')
                count ++;
        
        fseek(list,0,0);
        for(int i = 0; i < count; i++){
            fscanf(list, "%s", file1);
            fscanf(list, "%s", file2);
            fscanf(list, "%s", file3);

            FILE *matrix1 = fopen(file1,"r");
            FILE *matrix2 = fopen(file2,"r");
            FILE *matrix3 = fopen(file3,"w");

            multiply(matrix1,matrix2,matrix3);
      
            fclose(matrix1);
            fclose(matrix2);
            fclose(matrix3);
        }
        fclose(list);
    }

}