#include "CUnit/Basic.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct term_def {
    int hour;
    int minute;
    int duration;
}Term;

void Term__init(Term *term, int hour, int minute, int duration){
    term->minute = minute;
    term->hour = hour;
    term->duration = duration;
}

Term *Term__create(int hour,int minute, int duration){
    Term *a = malloc(sizeof(Term));
    Term__init(a,hour,minute,duration);
}

void Term__destroy(Term *term){
    free(term);
}

char *Term__toString(Term *term){
    char *res = malloc(13 * sizeof(*res));
    char c = 0;
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

Term *Term__endTerm(Term *term1, Term *term2){
    return Term__create(term1->hour, term1->minute, (term2->hour - term1->hour) * 60 + term2->minute - term1->minute);
}

Term **terms;

void create_test(){
    terms = malloc(3 * sizeof(*terms));
    terms[0] = Term__create(9,45,90);
    terms[1] = Term__create(10,15,90);
    CU_ASSERT_EQUAL(terms[0]->hour, 9);
    CU_ASSERT_EQUAL(terms[1]->hour, 10);
    CU_ASSERT_EQUAL(terms[0]->minute, 45);
    CU_ASSERT_EQUAL(terms[1]->minute, 15);
    CU_ASSERT_EQUAL(terms[0]->duration, 90);
    CU_ASSERT_EQUAL(terms[1]->duration, 90);
}

void init_test(){
    Term tab[2];
    Term__init(&tab[0],9,45,90);
    Term__init(&tab[1],10,15,90);
    CU_ASSERT_EQUAL(tab[1].hour,10);
    CU_ASSERT_EQUAL(tab[1].minute,15);
    CU_ASSERT_EQUAL(tab[1].duration,90);
}
void toString_test(){
    CU_ASSERT_STRING_EQUAL(Term__toString(terms[0]),"9:45 [90]");
    CU_ASSERT_STRING_EQUAL(Term__toString(terms[1]),"10:15 [90]");
}

void earlier_test(){
    CU_ASSERT_TRUE(Term__earlietThan(terms[0],terms[1]));
}

void later_test(){
    CU_ASSERT_TRUE(Term__laterThan(terms[1],terms[0]));
}

void equal_test(){
    CU_ASSERT_TRUE(Term_equals(terms[0],terms[0]));
    CU_ASSERT_TRUE(Term_equals(terms[1],terms[1]));
}

void endTerm_test(){
    Term *test = Term__endTerm(terms[0],terms[1]);
    CU_ASSERT_EQUAL(test->hour,9);
    CU_ASSERT_EQUAL(test->minute,45);
    CU_ASSERT_EQUAL(test->duration,30);
}
int main(){

    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    pSuite = CU_add_suite("test_suite", 0, 0);

    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "create_test", create_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "init_test", init_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "toString_test", toString_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "earlier_test", earlier_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "later_test", later_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "equals_test", equal_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "endTerm_test", endTerm_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_basic_set_mode(CU_BRM_VERBOSE);

    CU_basic_run_tests();
    return CU_get_error();
    return 0;
}