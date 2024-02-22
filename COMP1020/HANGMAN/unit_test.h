#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"

Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);
Status test_ttran4_my_string_destroy_returns_nonNULL(char* buffer, int length);
Status test_ttran4_my_string_init_c_string_capacity_is_greater_than_size_by_1(char* buffer, int length);
Status test_ttran4_get_size_on_init_c_string_returns_0(char* buffer, int length);
Status test_ttran4_my_init_c_string_returns_identical_string(char* buffer, int length);
Status test_ttran4_my_string_extraction_ignores_whitespace(char* buffer, int length);
Status test_ttran4_my_string_extraction_ends_in_non_whitespace_character(char* buffer, int length);
Status test_ttran4_my_string_extraction_allocates_more_memory_if_needed(char* buffer, int length);
//Status test_ttran4_my_string_insertion_handles_EOF(char* buffer, int length);
Status test_ttran4_my_string_get_capacity_is_accurate(char* buffer, int length);
Status test_ttran4_my_string_get_size_is_accurate(char* buffer, int length);
Status test_ttran4_my_string_compare_strings_are_exact_same_handled(char* buffer, int length);
Status test_ttran4_my_string_compare_strings_are_different_handled(char* buffer, int length);
Status test_ttran4_my_string_push_back_handles_resize(char* buffer, int length);
Status test_ttran4_my_string_push_back_handles_size_and_capacity_when_resizing(char* buffer, int length);
Status test_ttran4_my_string_init_default_initial_capacity_is_correct(char* buffer, int length);
Status test_ttran4_my_string_push_back_resize_accurately_replicates_string(char* buffer, int length);
Status test_ttran4_my_string_pop_back_handles_string_size_less_than_1(char* buffer, int length);
Status test_ttran4_my_string_pop_back_size_gets_subtracted_by_1(char* buffer, int length);
Status test_ttran4_my_string_at_handles_invalid_index(char* buffer, int length);
Status test_ttran4_my_string_c_str_ends_in_null_terminator(char* buffer, int length);
Status test_ttran4_my_string_c_str_handles_string_size_0(char* buffer, int length);
Status test_ttran4_my_string_c_str_subtracts_size_by_1(char* buffer, int length);
Status test_ttran4_my_string_concat_is_accurate(char* buffer, int length);
Status test_ttran4_my_string_concat_capacity_handled_after_concatenation(char* buffer, int length);
Status test_ttran4_my_string_concat_size_handled_after_concatenation(char* buffer, int length);
Status test_ttran4_my_string_empty_is_accurate(char* buffer, int length);

#endif