#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>

#define NEWLINE '\n'
#define IN_WORD 1

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2

#define MAX_LINE 128

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

int read_line()
{
    char line[MAX_LINE];
    int n;

    fgets(line, MAX_LINE, stdin); // to get the whole line
    sscanf(line, "%d", &n);
    return n;
}

// count number of lines (nl), number of words (nw) and number of characters
// (nc) in the text read from stdin
void wc(int *nl, int *nw, int *nc, char** arr, int len)
{
    for(int i=0; i <len;i++){
        int max = 0;
        while(*(*(arr +i) + max) != NEWLINE){
            max++;
        }
        for(int j=0; j< max;j++){
            (*nc)++;
            if(*(*(arr +i)+j) == ' ' ||*(*(arr +i)+j) == NEWLINE ||*(*(arr +i)+j) == '\t'){
            (*nw)++;
            }
        }
    }
    *(nw) += len;
}
// Count block and line comments in the text read from stdin. Set
// line_comment_counter and block_comment_counter accordingly
void find_comments(int *line_comment_counter, int *block_comment_counter)
{
}
/*******************************************************/
int main(void)
{
    int to_do;
    int nl = 0, nw = 0, nc = 0;
    int line_comment_counter, block_comment_counter;
    int len;
    to_do = read_line();
    char **txt = getData(&len);
    switch (to_do)
    {
    case 1: // wc()
        wc(&nl, &nw, &nc,txt,len);
        printf("%d %d %d\n", len, nw, nc);
        break;
    case 4:
        find_comments(&line_comment_counter, &block_comment_counter);
        printf("%d %d\n", block_comment_counter, line_comment_counter);
        break;
    default:
        printf("NOTHING TO DO FOR %d\n", to_do);
        break;
    }
    return 0;
}