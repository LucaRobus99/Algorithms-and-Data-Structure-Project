

#include "skiplist.h"

#include <string.h>
#include <time.h>

#include "stdlib.h"
#include "unity.h"



int cmp(const void *a, const void *b) {
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;

    return strcmp(str_a, str_b);
}


static struct SkipList* list;
char *item1,*item2,*item3;

void setUp(void){
    item1 = "banana";
    item2 = "apple";
    item3 = "cherry";
}
void tearDown(void){
    if(list==NULL){
        return;
    }
    clear_skiplist(&list);
}

static void test_SkipList_initialization(void){
    new_skiplist(&list, 10, cmp);
    TEST_ASSERT_NOT_NULL(list);
}

static void test_insert_and_search_elem_in_skiplist(void) {

    new_skiplist(&list, 10, cmp);

    insert_skiplist(list, &item1);
    insert_skiplist(list, &item2);
    insert_skiplist(list, &item3);

    char *search_item1 = "banana";
    const void *result1 = search_skiplist(list, (void *)&search_item1);
    TEST_ASSERT_NOT_NULL(result1);
    TEST_ASSERT_EQUAL_STRING(search_item1, *((const char**)result1));
}

static void test_insert_and_search_elem_not_in_skiplist(void) {

    new_skiplist(&list, 10, cmp);

    insert_skiplist(list, &item1);
    insert_skiplist(list, &item2);
    insert_skiplist(list, &item3);

    char *search_item1 = "cedro";
    const void *result1 = search_skiplist(list, (void *)&search_item1);
    TEST_ASSERT_NULL(result1);

}

static void test_SkipList_initialization_compare_null(void){
    new_skiplist(&list, 10, NULL);
    TEST_ASSERT_NULL(list);
}

static void test_insert_and_search_elem_in_a_not_initialized_skiplist(void) {



    insert_skiplist(list, &item1);
    insert_skiplist(list, &item2);
    insert_skiplist(list, &item3);

    char *search_item1 = "banana";
    const void *result1 = search_skiplist(list, (void *)&search_item1);
    TEST_ASSERT_NULL(result1);

}

static void test_clear_empty_skiplist(void) {

    new_skiplist(&list, 10, cmp);
    insert_skiplist(list, &item1);
    insert_skiplist(list, &item2);
    insert_skiplist(list, &item3);

    clear_skiplist(&list);


    TEST_ASSERT_NULL(list);

}

static void test_clear_not_empty_skiplist(void) {

    new_skiplist(&list, 10, cmp);

    clear_skiplist(&list);


    TEST_ASSERT_NULL(list);

}
static void test_clear_not_initialized_skiplist(void) {



    clear_skiplist(&list);


    TEST_ASSERT_NULL(list);

}






int main() {

    srand((unsigned int)time(NULL));

    UNITY_BEGIN();
    RUN_TEST(test_SkipList_initialization_compare_null);	
    RUN_TEST(test_SkipList_initialization);
    RUN_TEST(test_insert_and_search_elem_in_skiplist);
    RUN_TEST(test_insert_and_search_elem_not_in_skiplist);
    RUN_TEST(test_insert_and_search_elem_in_a_not_initialized_skiplist);
    RUN_TEST(test_clear_empty_skiplist);
    RUN_TEST(test_clear_not_empty_skiplist);
    RUN_TEST(test_clear_not_initialized_skiplist);
    return UNITY_END();

}


