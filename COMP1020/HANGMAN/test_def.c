#include <stdlib.h>
#include "unit_test.h"
#include <string.h>

Status test_init_default_returns_nonNULL(char* buffer, int length)
{
    MY_STRING hString = NULL;

    hString = my_string_init_default();

    if (hString == NULL)
    {
        strncpy(buffer, "test_init_default_returns_nonNULL\n"
                "my_string_init_default_returns NULL", length);
        return FAILURE;
    }
    else
    {
        my_string_destroy(&hString);
        strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
        return SUCCESS;
    }
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
    MY_STRING hString = NULL;
    Status status;

    hString = my_string_init_default();

    if (my_string_get_size(hString) != 0)
    {
        status = FAILURE;
        printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
        strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
                "Did not receive 0 from get_size after init_default\n", length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_get_size_on_init_default_returns_0\n", length);
    }

    my_string_destroy(&hString);
    return status;
}

Status test_ttran4_my_string_destroy_returns_nonNULL(char* buffer, int length)
{
    MY_STRING hString = my_string_init_default();
    Status status;
    my_string_destroy(&hString);
    if (hString == NULL)
    {
        status = SUCCESS;
        strncpy(buffer, "test_ttran4_my_string_destroy_returns_nonNULL\n", length);
        return status;
    }
    else
    {
        status = FAILURE;
        printf("Expected MY_STRING to be set to NULL but it has not been destroyed");
        strncpy(buffer, "test_ttran4_my_string_destroy_returns_nonNULL\n"
                "MY_STRING has not been set to NULL\n", length);
        return status;
    }
}

Status test_ttran4_my_string_init_c_string_capacity_is_greater_than_size_by_1(char* buffer, int length)
{
    char* test_string = "Dan";
    MY_STRING hString = my_string_init_c_string(test_string);
    if (my_string_get_size(hString) != my_string_get_capacity(hString) - 1)
    {
        printf("Expected my_string_init_c_string capacity to be 1 greater than the size of the string but capacity is %d, and size is %d.", my_string_get_capacity(test_string), my_string_get_size(test_string));
        strncpy(buffer, "test_ttran4_my_string_init_c_string_capacity_is_greater_than_size_by_1\n"
                "string capacity is not greater than string size by 1\n", length);
        my_string_destroy(&hString);
        return FAILURE;
    }
    else
    {
        strncpy(buffer, "test_ttran4_my_string_init_c_string_capacity_is_greater_than_size_by_1\n", length);
        my_string_destroy(&hString);
        return SUCCESS;
    }
}

Status test_ttran4_my_init_c_string_returns_identical_string(char* buffer, int length)
{
    char* test_string = " random test string ";
    MY_STRING hString = my_string_init_c_string(test_string);

    for (int i = 0; i < my_string_get_size(hString); i++)
    {
        if (*my_string_at(hString, i) != test_string[i])
        {
            printf("hString = \"%s\" and test_string = \"%s\". They are not identical\n", my_string_c_str(hString), test_string);
            strncpy(buffer, "test_ttran4_my_init_c_string_returns_identical_string\n"
                    "strings are not identical\n", length);
            my_string_destroy(&hString);
            return FAILURE;
        }
    }

    strncpy(buffer, "test_ttran4_my_init_c_string_returns_identical_string\n", length);
    my_string_destroy(&hString);
    return SUCCESS;
}

Status test_ttran4_my_string_extraction_ignores_whitespace(char* buffer, int length)
{
    char* test_string = " Jonny";
    MY_STRING hString = my_string_init_default();
    FILE* fp = fopen("test.txt", "w");
    if (fp == NULL)
    {
        printf("Could not open a file for testing for leading whitespace\n");
        return FAILURE;
    }

    fprintf(fp, "%s", test_string);
    fclose(fp);

    fp = fopen("test.txt", "r");
    if (fp == NULL)
    {
        printf("Could not open a file for testing for leading whitespace\n");
        return FAILURE;
    }
    my_string_extraction(hString, fp);
    fclose(fp);
    if (remove("test.txt") != 0)
    {
        printf("Error removing test.txt file from system\n");
        return FAILURE;
    }
    if (*my_string_at(hString, 0) == ' ')
    {
        printf("Found leading whitespace after my_string_extraction was executed \"%s\"\n", my_string_c_str(hString));
        strncpy(buffer, "test_ttran4_my_string_extraction_ignores_whitespace\n"
                "Leading whitespace was not skipped over\n", length);
        my_string_destroy(&hString);
        return FAILURE;
    }

    strncpy(buffer, "test_ttran4_my_string_extraction_ignores_whitespace\n", length);
    my_string_destroy(&hString);

    return SUCCESS;
}

Status test_ttran4_my_string_extraction_ends_in_non_whitespace_character(char* buffer, int length)
{
    char* test_string = "overwatch ";
    MY_STRING hString = my_string_init_default();
    FILE* fp = fopen("test.txt", "w");
    if (fp == NULL)
    {
        printf("Could not open a file for testing\n");
        return FAILURE;
    }

    fprintf(fp, "%s", test_string);
    fclose(fp);

    fp = fopen("test.txt", "r");
    if (fp == NULL)
    {
        printf("Could not open file for testing\n");
        return FAILURE;
    }
    my_string_extraction(hString, fp);

    if (*my_string_at(hString, my_string_get_size(hString) - 1) == ' ')
    {
        printf("my_string_extraction does not leaves whitespace at the end of extracted string \"%s\"\n", my_string_c_str(hString));
        strncpy(buffer, "test_ttran4_my_string_extraction_ends_in_non_whitespace_character\n"
                "my_string_extraction returns a string with a whitespace at the end\n", length);
        my_string_destroy(&hString);
        fclose(fp);
        return FAILURE;
    }

    if (remove("test.txt") != 0)
    {
        printf("Error removing test.txt file from system\n");
        return FAILURE;
    }

    fclose(fp);
    strncpy(buffer, "test_ttran4_my_string_extraction_ends_in_non_whitespace_character\n", length);
    my_string_destroy(&hString);

    return SUCCESS;
}

/* DEFINITELY DID SOMETHING WRONG WITH THIS FUNCTION TEST
Status test_ttran4_my_string_insertion_handles_EOF(char* buffer, int length)
{
    FILE* fp;
    MY_STRING hString = my_string_init_default();

    fp = fopen("test.txt", "w");
    if (fp == NULL)
    {
        printf("Failed to open file for testing\n");
        return FAILURE;
    }
    fputc(EOF, fp);
    fclose(fp);

    fp = fopen("test.txt", "r");
    if (fp == NULL)
    {
        printf("Failed to open file for testing\n");
        return FAILURE;
    }

    Status status = my_string_insertion(hString, fp);

    my_string_destroy(&hString);
    fclose(fp);

    if (remove("test.txt") != 0)
    {
        printf("Error removing test.txt file from system\n");
        return FAILURE;
    }

    if (status == FAILURE)
    {
        printf("my_string_insertion did not handle EOF\n");
        strncpy(buffer, "test_ttran4_my_string_insertion_handles_EOF\n"
                "EOF was not handled\n", length);
        return FAILURE;
    }
    else
    {
        strncpy(buffer, "test_ttran4_my_string_insertion_handles_EOF\n", length);
        return SUCCESS;
    }
}
*/

Status test_ttran4_my_string_get_capacity_is_accurate(char* buffer, int length)
{
    char* test_string = "4hours...";
    MY_STRING hString = my_string_init_c_string(test_string);

    int test_string_capacity = 10;
    int hString_capacity = my_string_get_capacity(hString);

    my_string_destroy(&hString);
    if (test_string_capacity == hString_capacity)
    {
        strncpy(buffer, "test_ttran4_my_string_get_capacity_is_accurate\n", length);
        return SUCCESS;
    }
    else
    {
        printf("my_string_get_capacity is not accurate. Capacity is off by %d\n", abs(test_string_capacity - hString_capacity));
        strncpy(buffer, "test_ttran4_my_string_get_capacity_is_accurate\n"
                "my_string_get_capacity is not accurate\n", length);
        return FAILURE;
    }
}

Status test_ttran4_my_string_get_size_is_accurate(char* buffer, int length)
{
    char* test_string = "eggroll";
    MY_STRING hString = my_string_init_c_string(test_string);

    int test_string_size = 7;
    int hString_size = my_string_get_size(hString);

    my_string_destroy(&hString);

    if (test_string_size == hString_size)
    {
        strncpy(buffer, "test_ttran4_my_string_get_size_is_accurate\n", length);
        return SUCCESS;
    }
    else
    {
        printf("my_string_get_size is not accurate. size is off by %d\n", abs(test_string_size - hString_size));
        strncpy(buffer, "test_ttran4_my_string_get_size_is_accurate\n"
                "my_string_get_size is not accurate\n", length);
        return FAILURE;
    }
}

Status test_ttran4_my_string_compare_strings_are_exact_same_handled(char* buffer, int length)
{
    char* test_string1 = "pear";
    char* test_string2 = "pear";

    MY_STRING hString1 = my_string_init_c_string(test_string1);
    MY_STRING hString2 = my_string_init_c_string(test_string2);

    if (my_string_compare(hString1, hString2) == 0)
    {
        my_string_destroy(&hString1);
        my_string_destroy(&hString2);
        strncpy(buffer, "test_ttran4_my_string_compare_strings_are_exact_same_handled\n", length);
        return SUCCESS;
    }
    else
    {
        my_string_destroy(&hString1);
        my_string_destroy(&hString2);
        printf("my_string_compare does not return 0 when the strings are the same\n");
        strncpy(buffer, "test_ttran4_my_string_compare_strings_are_exact_same_handled\n"
                "my_string_compare did not handle the case where the two strings are the same in length\n", length);
        return FAILURE;
    }
}

Status test_ttran4_my_string_compare_strings_are_different_handled(char* buffer, int length)
{
    char* test_string1 = "bon";
    char* test_string2 = "appetit";

    MY_STRING hString1 = my_string_init_c_string(test_string1);
    MY_STRING hString2 = my_string_init_c_string(test_string2);

    if (my_string_compare(hString1, hString2) != 0)
    {
        my_string_destroy(&hString1);
        my_string_destroy(&hString2);
        strncpy(buffer, "test_ttran4_my_string_compare_strings_are_different_handled\n", length);
        return SUCCESS;
    }
    else
    {
        my_string_destroy(&hString1);
        my_string_destroy(&hString2);
        printf("my_string_compare did not correctly handle the case where the strings are different\n");
        strncpy(buffer, "test_ttran4_my_string_compare_strings_are_different_handled\n"
                "my_string_compare returned a number != 0 when the strings were of different sizes\n", length);
        return FAILURE;
    }
}

Status test_ttran4_my_string_push_back_handles_resize(char* buffer, int length)
{
    MY_STRING hString = my_string_init_default();

    for (int i = 0; i < 10; i++)
    {
        if (my_string_push_back(hString, 'a') != SUCCESS)
        {
            my_string_destroy(&hString);
            printf("my_string_push_back did not properly make enough space for more characters\n");
            strncpy(buffer, "test_ttran4_my_string_push_back_handles_resize\n"
                    "my_string_push_back did not resize correctly\n", length);
            return FAILURE;
        }
    }
    strncpy(buffer, "test_ttran4_my_string_push_back_handles_resize\n", length);
    my_string_destroy(&hString);
    return SUCCESS;
}

Status test_ttran4_my_string_push_back_handles_size_and_capacity_when_resizing(char* buffer, int length)
{
    int initialCapacity = 7;
    MY_STRING hString = my_string_init_default();
    for (int i = 0; i < 10; i++)
    {
        my_string_push_back(hString, 'a');
    }

    if (my_string_get_capacity(hString) > initialCapacity && my_string_get_size(hString) == 10)
    {
        my_string_destroy(&hString);
        strncpy(buffer, "test_ttran4_my_string_push_back_handles_size_and_capacity_when_resizing\n", length);
        return SUCCESS;
    }
    else
    {
        printf("size and capacity are not handled correctly during resize. size is %d, and capacity is %d\n", my_string_get_size(hString), my_string_get_capacity(hString));
        strncpy(buffer, "test_ttran4_my_string_push_back_handles_size_and_capacity_when_resizing\n"
                "size and capacity are not handled correctly\n", length);
        my_string_destroy(&hString);
        return FAILURE;
    }
}

Status test_ttran4_my_string_init_default_initial_capacity_is_correct(char* buffer, int length)
{
    MY_STRING hString = my_string_init_default();
    int initialCapacity = 7;
    
    if (my_string_get_capacity(hString) == initialCapacity)
    {
        my_string_destroy(&hString);
        strncpy(buffer, "test_ttran4_my_string_init_default_initial_capacity_is_correct\n", length);   
        return SUCCESS;
    }
    else
    {
        printf("initial capacity is supposed to be 7, not %d\n", my_string_get_capacity(hString));
        strncpy(buffer, "test_ttran_my_string_init_default_initial_capacity_is_correct\n"
                "string is not initialized with proper initial capacity\n", length);
        my_string_destroy(&hString);
        return FAILURE;
    }
}

Status test_ttran4_my_string_push_back_resize_accurately_replicates_string(char* buffer, int length)
{
    char* test_string = "peter";
    char* copy = "peter";

    MY_STRING hString = my_string_init_c_string(test_string);
    MY_STRING hStringCopy = my_string_init_c_string(copy);

    for (int i = 0; i < 3; i++)
    {
        my_string_push_back(hString, 'r');
    }

    for (int i = 0; i < my_string_get_size(hStringCopy); i++)
    {
        if (*my_string_at(hString, i) != *my_string_at(hStringCopy, i))
        {
            my_string_destroy(&hString);
            my_string_destroy(&hStringCopy);

            printf("characters are not copied correctly after resize. error found at index %d\n", i);
            strncpy(buffer, "test_ttran4_my_string_push_back_resize_accurately_replicates_string\n"
                    "characters are not copied correctly after resize\n", length);
            return FAILURE;
        }
    }
    my_string_destroy(&hString);
    my_string_destroy(&hStringCopy);
    strncpy(buffer, "test_ttran4_my_string_push_back_resize_accurately_replicates_string\n", length);
    return SUCCESS;
}

Status test_ttran4_my_string_pop_back_handles_string_size_less_than_1(char* buffer, int length)
{
    MY_STRING hString = my_string_init_default();
    if (my_string_pop_back(hString) == FAILURE)
    {
        my_string_destroy(&hString);
        strncpy(buffer, "test_ttran4_my_string_pop_back_handles_string_size_less_than_1\n", length);
        return SUCCESS;
    }
    
    my_string_destroy(&hString);
    printf("tried to pop a string with size 0\n");
    strncpy(buffer, "test_ttran4_my_string_pop_back_handles_string_size_less_than_1\n"
            "cannot pop a string 0 characters\n", length);
    return FAILURE;
}

Status test_ttran4_my_string_pop_back_size_gets_subtracted_by_1(char* buffer, int length)
{
    char* test_string = "peter the horse is here";
    MY_STRING hString = my_string_init_c_string(test_string);
    int initialSize = my_string_get_size(hString);

    my_string_pop_back(hString);
    
    if (my_string_get_size(hString) == initialSize - 1)
    {
        my_string_destroy(&hString);
        strncpy(buffer, "test_ttran4_my_string_pop_back_size_gets_subtracted_by_1\n", length);
        return SUCCESS;
    }

    else
    {
        printf("did not properly subtract size by 1 after pop function\n");
        strncpy(buffer, "test_ttran4_my_string_pop_back_size_gets_subtracted_by_1\n"
                "size was not handled properly after pop function\n", length);
        my_string_destroy(&hString);
        return FAILURE;
    }
}

Status test_ttran4_my_string_at_handles_invalid_index(char* buffer, int length)
{
    char* test_string = "skibidi";
    MY_STRING hString = my_string_init_c_string(test_string);

    if (my_string_at(hString, 100) == NULL)
    {
        my_string_destroy(&hString);
        strncpy(buffer, "test_ttran4_my_string_at_handles_invalid_index\n",length);
        return SUCCESS;
    }
    else
    {
        my_string_destroy(&hString);
        printf("did not handle the case in which a valid index is entered\n");
        strncpy(buffer, "test_ttran4_my_string_at_handles_invalid_index\n"
                "should return NULL if index is invalid\n", length);
        return FAILURE;
    }
}

Status test_ttran4_my_string_c_str_ends_in_null_terminator(char* buffer, int length)
{
    char* test_string = "gentleman googoo";
    MY_STRING hString = my_string_init_c_string(test_string);

    char* c_str = my_string_c_str(hString);

    if (c_str[my_string_get_size(hString)] != '\0')
    {
        my_string_destroy(&hString);
        printf("my_string_c_str did not end the string with a null terminator \\0\n");
        strncpy(buffer, "test_ttran4_my_string_c_str_ends_in_null_terminator\n"
                "the returned string does not end with \\0\n", length);
        return FAILURE;
    }
    my_string_destroy(&hString);
    strncpy(buffer, "test_ttran4_my_string_c_str_ends_in_null_terminator\n", length);
    return SUCCESS;

}

Status test_ttran4_my_string_c_str_handles_string_size_0(char* buffer, int length)
{
    char* test_string = "";
    MY_STRING hString = my_string_init_c_string(test_string);

    
    if (my_string_c_str(hString) == NULL)
    {
        my_string_destroy(&hString);
        strncpy(buffer, "test_ttran4_my_string_c_str_handles_string_size_0\n", length);
        return SUCCESS;
    }
    else
    {
        my_string_destroy(&hString);
        printf("NULL was not returned upon a string of size zero\n");
        strncpy(buffer, "test_ttran4_my_string_c_str_handles_string_size_0\n"
                "NULL should've been returned upon encountering a string of size 0\n", length);
        return FAILURE;
    }
}

Status test_ttran4_my_string_c_str_subtracts_size_by_1(char* buffer, int length)
{
    char* test_string = "sigurd";
    MY_STRING hString1 = my_string_init_c_string(test_string);
    int initialSize = my_string_get_size(hString1);

    char* compared_string = my_string_c_str(hString1);
    MY_STRING hString2 = my_string_init_c_string(compared_string);
    int size_after_c_str = my_string_get_size(hString2);

    if (initialSize == size_after_c_str)
    {
        my_string_destroy(&hString1);
        my_string_destroy(&hString2);

        strncpy(buffer, "test_ttran4_my_string_c_str_subtracts_size_by_1", length);
        return SUCCESS;
    }
    else
    {
        my_string_destroy(&hString1);
        my_string_destroy(&hString2);

        printf("size was not subtracted by 1\n");
        strncpy(buffer, "test_ttran4_my_string_c_str_subtracts_size_by_1\n"
                "size should be subtracted by one after my_string_c_str is executed\n", length);
        return FAILURE;
    }
}

Status test_ttran4_my_string_concat_is_accurate(char* buffer, int length)
{
    char* temp_string = "kai ";
    char* to_append = "cenat";
    char* expected_result = "kai cenat";
    MY_STRING hString = my_string_init_c_string(temp_string);
    MY_STRING hAppend = my_string_init_c_string(to_append);
    MY_STRING expected_string = my_string_init_c_string(expected_result);

    my_string_concat(hString, hAppend);

    for (int i = 0; i < my_string_get_size(expected_string); i++)
    {
        if (*my_string_at(hString, i) != *my_string_at(expected_string, i))
        {
            my_string_destroy(&hAppend);
            my_string_destroy(&hString);
            my_string_destroy(&expected_string);
            printf("something went wrong when concatenating strings\n");
            strncpy(buffer, "test_ttran4_my_string_concat_is_accurate\n"
                    "string is no longer identical after concatenation\n", length);
            return FAILURE;
        }
    }
    my_string_destroy(&hAppend);
    my_string_destroy(&hString);
    my_string_destroy(&expected_string);

    strncpy(buffer, "test_ttran4_my_string_concat_is_accurate\n", length);
    return SUCCESS;
}

Status test_ttran4_my_string_concat_capacity_handled_after_concatenation(char* buffer, int length)
{
    char* temp_string = "dan ";
    char* to_append = "forehead";
    MY_STRING hString = my_string_init_c_string(temp_string);
    MY_STRING hAppend = my_string_init_c_string(to_append);

    my_string_concat(hString, hAppend);

    if (my_string_get_capacity(hString) != 13)
    {
        my_string_destroy(&hString);
        my_string_destroy(&hAppend);

        printf("capacity is not handled correctly.\n");
        strncpy(buffer, "test_ttran4_my_string_concat_capacity_handled_after_concatenation\n"
                "capacity should be 1 greater than concatenated string\n", length);
        return FAILURE;
    }
    my_string_destroy(&hString);
    my_string_destroy(&hAppend);
    strncpy(buffer, "test_ttran4_my_string_concat_capacity_handled_after_concatenation\n", length);
    return SUCCESS;
}

Status test_ttran4_my_string_concat_size_handled_after_concatenation(char* buffer, int length)
{
    char* test_string = "hideo ";
    char* to_append = "kojima";
    MY_STRING hString = my_string_init_c_string(test_string);
    MY_STRING hAppend = my_string_init_c_string(to_append);

    my_string_concat(hString, hAppend);

    if (my_string_get_size(hString) != 12)
    {
        my_string_destroy(&hString);
        my_string_destroy(&hAppend);
        printf("size is not handled correctly.\n");
        strncpy(buffer, "test_ttran4_my_string_concat_size_handled_after_concatenation\n"
                "size is inaccurate and does not match actual concatenated string\n", length);
        return FAILURE;
    }
    my_string_destroy(&hAppend);
    my_string_destroy(&hString);
    strncpy(buffer, "test_ttran4_my_string_concat_size_handled_after_concatenation\n", length);
    return SUCCESS;
}

Status test_ttran4_my_string_empty_is_accurate(char* buffer, int length)
{
    MY_STRING hString = my_string_init_default();
    if (my_string_empty(hString) == TRUE)
    {
        my_string_destroy(&hString);
        strncpy(buffer, "test_ttran4_my_string_empty_is_accurate\n", length);
        return SUCCESS;
    }
    my_string_destroy(&hString);
    printf("my_string_empty is not accurate\n");
    strncpy(buffer, "test_ttran4_my_string_empty_is_accurate\n"
            "did not return TRUE when given an empty string\n", length);
    return FAILURE;
}