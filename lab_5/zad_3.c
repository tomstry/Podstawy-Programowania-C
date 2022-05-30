#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

typedef enum days {MON,TUE,WED,THU,FRI,SAT,SUN} Day;
typedef enum actions {DAY_EARLIER, DAY_LATER, TIME_EARLIER, TIME_LATER} Action;
typedef struct term_def {
    int hour;
    int minute;
    int duration;
    Day day;
}Term;
struct limit_def{
    Day min_day;
    Day max_day;
    int min_hour;
    int max_hour;
    int max_last_hour;
}Limits = {MON,FRI,8,20,17};

const char days[7][14] = {"Poniedziałek\0", "Wtorek\0", "Środa\0", "Czwartek\0", "Piątek\0", "Sobota\0", "Niedziela\0"};

const char* Day_toString(Day day){
    return (char*)days[day];
}

Day Day__nextDay(Day day){
    if(day == SUN)
        return MON;
    else
        return day + 1;
}
Day Day__prevDay(Day day){
    if(day == MON)
        return SUN;
    else
        return day - 1;
}

Action* parse(int size, char *array[]){
    Action *arr = malloc(size * sizeof(*arr));
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

void Term__init(Term *term, int hour, int minute, int duration, Day day){
    term->minute = minute;
    term->hour = hour;
    term->duration = duration;
    term->day = day;
}

Term *Term__create(int hour,int minute, int duration, Day day){
    Term *a = malloc(sizeof(sizeof(Term)));
    Term__init(a,hour,minute,duration,day);
}

void Term__destroy(Term *term){
    free(term);
}

char *Term__toString(Term *term){
    char *res = malloc((strlen(Day_toString(term->day))+13) * sizeof(*res));
    strcpy(res,Day_toString(term->day));
    char c = strlen(res);
    if(term->hour/10)
        res[c++] = '0' + (term->hour / 10);
    res[c++] = '0' + term->hour % 10;
    res[c++] = ':';
    res[c++] = '0' + term->minute / 10;
    res[c++] = '0' + term->minute % 10;
    res[c++] = ' ';
    res[c++] = '[';
    if(term->duration / 100)
        res[c++] = '0' + term->duration/100;
    if((term->duration/10) % 10)
        res[c++] = '0' + (term->duration /10 )% 10;
    res[c++] = '0' + term->duration %10;
    res[c++] = ']';
    res[c] = 0;
    return res;
}

bool Term__earlietThan(Term *term1, Term *term2){
    if(term1->hour < term2->hour)
        return true;
    else if(term1->hour == term2->hour && term1->minute < term2->minute)
        return true;
    else
        return false;
}

bool Term__laterThan(Term *term1, Term *term2){
    if(term1->hour > term2->hour)
        return true;
    else if(term1->hour == term2->hour && term1->minute > term2->minute)
        return true;
    else
        return false;
}

bool Term_equals(Term *term1, Term *term2){
    if(term1->hour == term2->hour && term1->minute == term2->minute && term1->duration == term2->duration)
        return true;
    else
        return false;
}

typedef struct lessons{
    Term *term;
    char *name;
} Lessons;

void init_lesson(Lessons *lesson, int hour, int minute, int dur, Day day, char *name){
    lesson->name = malloc(strlen(name)*sizeof(char));
    strcpy(lesson->name,name);
    Term__init(lesson->term,hour,minute,dur,day);
}

Lessons *create_lesson(int hour, int minute, int dur, Day day, char *name){
    Lessons *lesson = malloc(sizeof(lesson));
    lesson->term = Term__create(hour,minute,dur,day);
    lesson->name = malloc(strlen(name) * sizeof(*name));
    strcpy(lesson->name,name);
    return lesson;
}
void destroy_lesson(Lessons *lesson){
    free(lesson->name);
    Term__destroy(lesson->term);
    free(lesson);
}

bool lesson_possibility(Lessons *lesson){
    int endhour = lesson->term->hour + ((lesson->term->duration + lesson->term->minute) / 60);
    int endminute = (lesson->term->duration + lesson->term->minute) % 60;
    if(lesson->term->day >= MON && lesson->term->day < FRI){
        if((lesson->term->hour > 8 || (lesson->term->hour == 8 && lesson->term->minute >= 0)) && (endhour < 20 || (endhour == 20 && endminute == 0)))
            return true;
        else
            return false;
    }
    else if(lesson->term->day == FRI){
        if((lesson->term->hour > 8 || (lesson->term->hour == 8 && lesson->term->minute >= 0)) && (endhour < 17 || (endhour == 17 && endminute == 0)))
            return true;
        else
            return false;
    }
}

void Lesson__earlierDay(Lessons *lesson){
    lesson->term->day = Day__prevDay(lesson->term->day);
    printf("Dzień w tył\n");
    if(!lesson_possibility(lesson)){
        printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s\"\n",lesson->name,Term__toString(lesson->term));
        lesson->term->day = Day__nextDay(lesson->term->day);
    }
}

void Lesson__laterDay(Lessons *lesson){
    lesson->term->day = Day__nextDay(lesson->term->day);
    printf("Dzień w przód\n");
    if(!lesson_possibility(lesson)){
        printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s\"\n",lesson->name,Term__toString(lesson->term));
        lesson->term->day = Day__prevDay(lesson->term->day);
    }
}

void Lesson__earlierTime(Lessons *lesson){
    int hourdiff = lesson->term->duration / 60;
    int minutediff = lesson->term->duration % 60;
    lesson->term->hour -= hourdiff;
    lesson->term->minute -= minutediff;
    if(!lesson_possibility(lesson)){
        printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s\"\n",lesson->name,Term__toString(lesson->term));
        lesson->term->hour += hourdiff;
        lesson->term->minute += minutediff;
    }
}

void Lesson__laterTime(Lessons *lesson){
    int hourdiff = lesson->term->duration / 60;
    int minutediff = lesson->term->duration % 60;
    lesson->term->hour += hourdiff;
    lesson->term->minute += minutediff;
    if(!lesson_possibility(lesson)){
        printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s\"\n",lesson->name,Term__toString(lesson->term));
        lesson->term->hour -= hourdiff;
        lesson->term->minute -= minutediff;
                printf("Dzień w tył\n");
    }
}

char* lesson_toStr(Lessons *lesson){
    char *a = malloc(50 * sizeof(*a));
    strcpy(a,lesson->name);
    strcat(a,", ");
    strcat(a, Term__toString(lesson->term));
    return a;
}

int main(int argc, char **argv){
    Lessons *lesson = create_lesson(12,50,90,WED,"Podstawy programowania");
    printf("Przed przesunięciem:\n");
    printf("\t\"%s\"",lesson_toStr(lesson));

    Action *actions = parse(argc -2, argv +2);
    for(int i = 0; i < argc - 2; ++i){
        switch(actions[i]){
            case DAY_EARLIER:
                printf("Dzień w tył\n");
                Lesson__earlierDay(lesson);
                break;
            case DAY_LATER:
                printf("Dzień w przód\n");
                Lesson__laterDay(lesson);
                break;
            case TIME_EARLIER:
                printf("Termin w tył\n");
                Lesson__earlierTime(lesson);
                break;
            case TIME_LATER:
                printf("Termin w przód\n");
                Lesson__laterTime(lesson);
                break;
        }
    }
    printf("Po przesunięciach:\n");
    printf("\t\"%s\"\n",lesson_toStr(lesson));
}