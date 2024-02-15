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

    strncpy(buffer, "test_ttran4_my_string_extraction_ends_in_non_whitespace_character\n", length);
    my_string_destroy(&hString);

    return SUCCESS;
}

// DEFINITELY DID SOMETHING WRONG WITH THIS FUNCTION TEST
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