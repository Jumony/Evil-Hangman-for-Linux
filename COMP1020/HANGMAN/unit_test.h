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
Status test_ttran4_my_string_insertion_handles_EOF(char* buffer, int length);
Status test_ttran4_my_string_get_capacity_is_accurate(char* buffer, int length);
Status test_ttran4_my_string_get_size_is_accurate(char* buffer, int length);

#endif