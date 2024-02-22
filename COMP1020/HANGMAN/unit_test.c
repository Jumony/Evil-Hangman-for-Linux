#include <stdio.h>
#include "unit_test.h"

int main(int argc, char* argv[])
{
    Status (*tests[])(char*, int) =
    {
        test_init_default_returns_nonNULL,
        test_get_size_on_init_default_returns_0,
        test_ttran4_my_string_destroy_returns_nonNULL,
        test_ttran4_my_string_init_c_string_capacity_is_greater_than_size_by_1,
        test_ttran4_my_init_c_string_returns_identical_string,
        test_ttran4_my_string_extraction_ignores_whitespace,
        test_ttran4_my_string_extraction_ends_in_non_whitespace_character,
        //test_ttran4_my_string_insertion_handles_EOF,
        test_ttran4_my_string_get_capacity_is_accurate,
        test_ttran4_my_string_get_size_is_accurate,
        test_ttran4_my_string_compare_strings_are_exact_same_handled,
        test_ttran4_my_string_compare_strings_are_different_handled,
        test_ttran4_my_string_push_back_handles_resize,
        test_ttran4_my_string_push_back_handles_size_and_capacity_when_resizing,
        test_ttran4_my_string_init_default_initial_capacity_is_correct,
        test_ttran4_my_string_push_back_resize_accurately_replicates_string,
        test_ttran4_my_string_pop_back_handles_string_size_less_than_1,
        test_ttran4_my_string_pop_back_size_gets_subtracted_by_1,
        test_ttran4_my_string_at_handles_invalid_index,
        test_ttran4_my_string_c_str_ends_in_null_terminator,
        test_ttran4_my_string_c_str_handles_string_size_0,
        test_ttran4_my_string_c_str_subtracts_size_by_1,
        test_ttran4_my_string_concat_is_accurate,
        test_ttran4_my_string_concat_capacity_handled_after_concatenation,
        test_ttran4_my_string_concat_size_handled_after_concatenation,
        test_ttran4_my_string_empty_is_accurate

    };

    int number_of_functions = sizeof(tests)/sizeof(tests[0]);
    int i;
    char buffer[500];
    int success_count = 0;
    int failure_count = 0;

    for (i = 0; i < number_of_functions;i++)
    {
        if (tests[i](buffer,500) == FAILURE)
        {
            printf("FAILED: Test %d failed miserably\n", i);
            printf("\t%s\n", buffer);
            failure_count++;
        }
        else
        {
            //printf("PASS: Test %d passed\n", i);
            //printf("\t%s\n", buffer);
            success_count++;
        }
    }
    printf("Total number of tests: %d\n", number_of_functions);
    printf("%d/%d Pass, %d/%d Failure\n", success_count, number_of_functions, failure_count, number_of_functions);
    return 0;
}