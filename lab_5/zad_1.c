#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum Day {MON = 0, TUE = 1, WED = 2, THU = 3, FRI = 4, SAT = 5, SUN = 6};

enum Action {DAY_EARLIER = 0, DAY_LATER = 1, TIME_EARLIER = 2, TIME_LATER = 3};

const char days[7][14] = {"Poniedziałek\0", "Wtorek\0", "Środa\0", "Czwartek\0", "Piątek\0", "Sobota\0", "Niedziela\0"};

const char* Day_toString(enum Day day){
    return (char*)days[day];
}
enum Day Day__nextDay(enum Day day){
    if(day == SUN)
        return MON;
    else
        return day + 1;
}
enum Day Day__prevDay(enum Day day){
    if(day == MON)
        return SUN;
    else
        return day - 1;
}
enum Action* parse(int size, char *array[]){
    enum Action *arr = malloc(size * sizeof(*arr));
    int i = 0;

    for(int j = 0; j < size; j++){
        if(!strcmp(array[j],"d+"))
            arr[i++] = DAY_LATER;
        else if(!strcmp(array[j],"d-"))
            arr[i++] = DAY_EARLIER;
        else if(!strcmp(array[j],"t-"))
            arr[i++] = TIME_EARLIER;
        else if(!strcmp(array[j],"t+"))
            arr[i++] = TIME_LATER;
    }
    if(size != i)
        arr = realloc(arr, i * sizeof(*arr));

    return arr;

}

enum Day Day__fromstr(char *arr){
    if(!strcmp(arr, "Mon"))
        return MON;
    if(!strcmp(arr, "Tue"))
        return TUE;
    if(!strcmp(arr, "Wed"))
        return WED;
    if(!strcmp(arr, "Thu"))
        return THU;
    if(!strcmp(arr, "Fri"))
        return FRI;
    if(!strcmp(arr, "Sat"))
        return SAT;
    if(!strcmp(arr, "Sun"))
        return SUN;
}

int main(int argc, char**argv){
    if(argc < 2){
        printf("Wpisz dzień tygodnia i conajmniej jedno działanie d+/d-/t+/t- \n");
        return 0;
    }

    enum Day day = Day__fromstr(argv[1]);
    enum Action *action = parse(argc - 2, argv + 2);
    
    for(int i = 0; i < argc - 2; ++i){
        switch(action[i]){
            case DAY_EARLIER:
                printf("Dzień w tył\n");
                day = Day__prevDay(day);
                break;
            case DAY_LATER:
                printf("Dzień w przód\n");
                day = Day__nextDay(day);
                break;
            case TIME_EARLIER:
                printf("Termin w tył\n");
                break;
            case TIME_LATER:
                printf("Termin w przód\n");
                break;
        }
    }
    printf("Wynik przesunięcia: \"%s\"\n", Day_toString(day));
    free(action);
    return 0;
}