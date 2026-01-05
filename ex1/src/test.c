

#include "libsort.h"
+#include <string.h>

#include <stdlib.h>

#include "unity.h"



int cmp_string(const void *a, const void *b) {
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;

    return strcmp(str_a, str_b);
}
int cmp_float(const void *a, const void *b) {
    const float float_a = *(const float *)a;
    const float float_b = *(const float *)b;

    if (float_a < float_b)
        return -1;
    else if (float_a > float_b)
        return 1;
    else
        return 0;
}
int cmp_int(const void *a, const void *b) {
    const int int_a = *(const int *)a;
    const int int_b = *(const int *)b;

    if (int_a < int_b)
        return -1;
    else if (int_a > int_b)
        return 1;
    else
        return 0;
}


void test_merge_binary_insertion_sort() {
    // Test con array di interi
    int arr1[] = {5, 3, 1, 4, 2};
    int sorted1[] = {1, 2, 3, 4, 5};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);

    merge_binary_insertion_sort(arr1, n1, sizeof(int), 1, cmp_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(sorted1, arr1, n1);

    // Test con array di float
    float arr2[] = {3.5, 1.2, 2.8, 5.1, 4.7};
    float sorted2[] = {1.2, 2.8, 3.5, 4.7, 5.1};
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);

    merge_binary_insertion_sort(arr2, n2, sizeof(float), 1, cmp_float);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(sorted2, arr2, n2);

    // Test con array di stringhe
    char* arr3[] = {"B", "H", "D", "A"};
    char* sorted3[] = {"A", "B", "D", "H"};
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);

    merge_binary_insertion_sort(arr3, n3, sizeof(char*), 1, cmp_string);
    TEST_ASSERT_EQUAL_STRING_ARRAY(sorted3, arr3, n3);
}
void test_empty_array() {
    int* arr = NULL;
    size_t n = 0;

    merge_binary_insertion_sort(arr, n, sizeof(int), 2, cmp_int);
    TEST_ASSERT_NULL(arr);
}

void test_empty_compare() {
    int arr[] = {1, 2, 3, 4, 5};
    
    size_t n = sizeof(arr) / sizeof(arr[0]);

    merge_binary_insertion_sort(arr, n, sizeof(int), 2, NULL);
    TEST_ASSERT_EQUAL_INT_ARRAY(arr, arr, n);
}
void test_single_element_array() {
    int arr[] = {1};
    int sorted[] = {1};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    merge_binary_insertion_sort(arr, n, sizeof(int), 2, cmp_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(sorted, arr, n);
}

void test_sorted_array() {
    int arr[] = {1, 2, 3, 4, 5};
    int sorted[] = {1, 2, 3, 4, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    merge_binary_insertion_sort(arr, n, sizeof(int), 2, cmp_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(sorted, arr, n);
}

void test_reverse_array() {
    int arr[] = {5, 4, 3, 2, 1};
    int sorted[] = {1, 2, 3, 4, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    merge_binary_insertion_sort(arr, n, sizeof(int), 2, cmp_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(sorted, arr, n);
}

void test_duplicate_elements_array() {
    int arr[] = {5, 3, 1, 4, 2, 1, 3};
    int sorted[] = {1, 1, 2, 3, 3, 4, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    merge_binary_insertion_sort(arr, n, sizeof(int), 2, cmp_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(sorted, arr, n);
}

void test_large_random_array() {
    // Genera un array di grandi dimensioni con valori casuali
    const size_t array_size = 10000;
    int arr[array_size];
    int sorted[array_size];
    for (size_t i = 0; i < array_size; i++) {
        arr[i] = rand();  // Valori casuali
        sorted[i] = arr[i];
    }
    size_t n = sizeof(arr) / sizeof(arr[0]);

    // Ordina l'array
    merge_binary_insertion_sort(arr, n, sizeof(int), 2, cmp_int);

    // Verifica che l'array ordinato sia corretto
    qsort(sorted, n, sizeof(int), cmp_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(sorted, arr, n);
}

void test_empty_string_array() {
    int* arr = NULL;
    size_t n = 0;

    merge_binary_insertion_sort(arr, n, sizeof(char*), 2, cmp_string);
    TEST_ASSERT_NULL(arr);
}

void test_single_element_string_array() {
    char* arr[] = {"Hello"};
    char* sorted[] = {"Hello"};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    merge_binary_insertion_sort(arr, n, sizeof(char*), 2, cmp_string);
    TEST_ASSERT_EQUAL_STRING_ARRAY(sorted, arr, n);
}

void test_sorted_string_array() {
    char* arr[] = {"A", "B", "C", "D"};
    char* sorted[] = {"A", "B", "C", "D"};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    merge_binary_insertion_sort(arr, n, sizeof(char*), 2, cmp_string);
    TEST_ASSERT_EQUAL_STRING_ARRAY(sorted, arr, n);
}

void test_reverse_string_array() {
    char* arr[] = {"Z", "V", "H", "E"};
    char* sorted[] = {"E", "H", "V", "Z"};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    merge_binary_insertion_sort(arr, n, sizeof(char*), 2, cmp_string);
    TEST_ASSERT_EQUAL_STRING_ARRAY(sorted, arr, n);
}
void test_duplicate_elements_float_array() {
    float arr[] = {3.5, 1.2, 2.8, 5.1, 4.7, 1.2, 2.8};
    float sorted[] = {1.2, 1.2, 2.8, 2.8, 3.5, 4.7, 5.1};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    merge_binary_insertion_sort(arr, n, sizeof(float), 2, cmp_float);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(sorted, arr, n);
}

void test_large_random_float_array() {
    // Genera un array di grandi dimensioni con numeri float casuali
    const size_t array_size = 10000;
    float arr[array_size];
    float sorted[array_size];
    for (size_t i = 0; i < array_size; i++) {
        arr[i] = (float)rand() / RAND_MAX;  // Valori casuali tra 0 e 1
        sorted[i] = arr[i];
    }
    size_t n = sizeof(arr) / sizeof(arr[0]);

    // Ordina l'array
    merge_binary_insertion_sort(arr, n, sizeof(float), 2, cmp_float);

    // Verifica che l'array ordinato sia corretto
    qsort(sorted, n, sizeof(float), cmp_float);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(sorted, arr, n);
}

void test_empty_float_array() {
    float *arr=NULL;
    size_t n =0;

    merge_binary_insertion_sort(arr, n, sizeof(float), 2, cmp_float);
    TEST_ASSERT_NULL(arr);
}

void test_single_element_float_array() {
    float arr[] = {1.5};
    float sorted[] = {1.5};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    merge_binary_insertion_sort(arr, n, sizeof(float), 2, cmp_float);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(sorted, arr, n);
}

void test_sorted_float_array() {
    float arr[] = {1.2, 2.4, 3.6, 4.8, 6.0};
    float sorted[] = {1.2, 2.4, 3.6, 4.8, 6.0};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    merge_binary_insertion_sort(arr, n, sizeof(float), 2, cmp_float);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(sorted, arr, n);
}

void test_reverse_float_array() {
    float arr[] = {6.0, 4.8, 3.6, 2.4, 1.2};
    float sorted[] = {1.2, 2.4, 3.6, 4.8, 6.0};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    merge_binary_insertion_sort(arr, n, sizeof(float), 2, cmp_float);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(sorted, arr, n);
}


int main() {
    UNITY_BEGIN();
    RUN_TEST(test_merge_binary_insertion_sort);
    RUN_TEST(test_empty_array);
    RUN_TEST(void test_empty_compare);
    RUN_TEST(test_single_element_array);
    RUN_TEST(test_sorted_array);
    RUN_TEST(test_reverse_array);
    RUN_TEST(test_large_random_array);
    RUN_TEST(test_empty_string_array);
    RUN_TEST(test_single_element_string_array);
    RUN_TEST(test_sorted_string_array);
    RUN_TEST(test_reverse_string_array);
    RUN_TEST(test_large_random_float_array);
    RUN_TEST(test_empty_float_array);
    RUN_TEST(test_duplicate_elements_float_array);
    RUN_TEST(test_single_element_float_array);
    RUN_TEST(test_reverse_float_array);
    RUN_TEST(test_sorted_float_array);
    return UNITY_END();
}


