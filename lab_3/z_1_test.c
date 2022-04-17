#include "CUnit/Basic.h"
#include "zad_1t.c"

void testcesar(){
    char tekst[100];

    strcpy(tekst, "to be or not to be");
    cezar(tekst);
    CU_ASSERT_STRING_EQUAL(tekst, "vq dg qt pqv vq dg");

    strcpy(tekst, "ala ma kota");
    cezar(tekst);
    CU_ASSERT_STRING_EQUAL(tekst, "dod pd nrwd");

    strcpy(tekst, "abcdefghijklmnopqrstuvwxyz");
    cezar(tekst);
    CU_ASSERT_STRING_EQUAL(tekst, "abcdefghijklmnopqrstuvwxyz");

    strcpy(tekst, "a b c d e f g h i j k l m n o p q r s t u v w x y z");
    cezar(tekst);
    CU_ASSERT_STRING_EQUAL(tekst, "b c d e f g h i j k l m n o p q r s t u v w x y z a");
}

int main()
{
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    pSuite = CU_add_suite("sum_test_suite", 0, 0);

    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "cesar_test", testcesar))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);

    CU_basic_run_tests();
    return CU_get_error();
}