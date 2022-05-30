#include "CUnit/Basic.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef enum days {MON,TUE,WED,THU,FRI,SAT,SUN} Day;
typedef enum actions {DAY_EARLIER, DAY_LATER, TIME_EARLIER, TIME_LATER} Action;

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

void toStr_test(){
    CU_ASSERT_STRING_EQUAL(Day_toString(MON), "Poniedziałek");
    CU_ASSERT_STRING_EQUAL(Day_toString(TUE), "Wtorek");
    CU_ASSERT_STRING_EQUAL(Day_toString(FRI), "Piątek");
    CU_ASSERT_STRING_EQUAL(Day_toString(SUN), "Niedziela");
}

void nextDay_test(){
    CU_ASSERT_EQUAL(Day__nextDay(MON), TUE);
    CU_ASSERT_EQUAL(Day__nextDay(SUN), MON);
    CU_ASSERT_EQUAL(Day__nextDay(FRI), SAT);
    CU_ASSERT_EQUAL(Day__nextDay(WED), THU);
}

void prevDay_test(){
    CU_ASSERT_EQUAL(Day__prevDay(MON), SUN);
    CU_ASSERT_EQUAL(Day__prevDay(FRI), THU);
    CU_ASSERT_EQUAL(Day__prevDay(TUE), MON);
    CU_ASSERT_EQUAL(Day__prevDay(SUN), SAT);
}

void parse_test(){
    char *arr[] = {"d+", "d+", "t+", "auuuu","t-","d-"};
    Action a[] = {DAY_LATER, DAY_LATER, TIME_LATER, TIME_EARLIER, DAY_EARLIER};
    Action *array = parse(6,arr);
    for(int i = 0; i < 5; i++)
        CU_ASSERT_EQUAL(array[i],a[i]);

}
int main()
{
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    pSuite = CU_add_suite("test_suite", 0, 0);

    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "toString_test", toStr_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "nextDay_test", nextDay_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "prevDay_test", prevDay_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "parse_test", parse_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);

    CU_basic_run_tests();
    return CU_get_error();
}