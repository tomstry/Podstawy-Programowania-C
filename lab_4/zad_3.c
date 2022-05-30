#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int get_num(FILE *file, int i){
    fseek(file,4,SEEK_SET);
    int a;
    for(int j = 0; j <= i; j++){
        fscanf(file,"%i", &a);
    }
    return a;
}
void multiply(FILE *matrix1, FILE *matrix2, FILE *matrix3, int mode){
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
	if(mode == 1){
    	for (int i = 0; i < row1; i++) {
        	for (int j = 0; j < col2; j++) {
            	int s = 0;
            	for (int k = 0; k < col1; k++){
                    if(j<=(col2-2)/2)
                	    s += get_num(matrix1, i * col1 + k) * get_num(matrix2, j + col2 * k);
            	}
                if(j<=(col2-2)/2)
            	    fprintf(matrix3, "%d\t", s);
            	}
        	fprintf(matrix3, "\n");
    		}
	}
    if(mode == 2){
    	for (int i = 0; i < row1; i++) {
        	for (int j = 0; j < col2; j++) {
            	int s = 0;
            	for (int k = 0; k < col1; k++){
                    if(j>=(col2)/2)
                	    s += get_num(matrix1, i * col1 + k) * get_num(matrix2, j + col2 * k);
            	}
                if(j >= (col2)/2 && s != 0)
            	    fprintf(matrix3, "%i\t", s);
                else
                    fprintf(matrix3," \t");
            	}
        	fprintf(matrix3, "\n");
    		}        
    }
    if(mode <=0 || mode >=3){
        printf("Zły tryb :(");
    }
}
int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Zła składnia!!!");
        exit(1);
    }
    else{
        int mode = atoi(argv[2]);
        FILE *list;
        list = fopen(argv[1],"r");
        int count = 0;
        char files1[20],files2[20],files3[20];
        char x;
        for(x = getc(list); x != EOF; x = getc(list)){
            if(x == ' ')
            count +=1;
        }
        fseek(list,0,0);
        for(int i =0; i<count;i++){
            fscanf(list,"%s",files1);
            fscanf(list,"%s",files2);
            fscanf(list,"%s",files3);
            FILE *matrix1,*matrix2,*matrix3;

            matrix1 = fopen(files1,"r");
            matrix2 = fopen(files2,"r");
            matrix3 = fopen(files3,"w");

            multiply(matrix1,matrix2,matrix3,mode);

            fclose(matrix1);
            fclose(matrix2);
            fclose(matrix3);
        }
        fclose(list);
    }
	return 0;
}