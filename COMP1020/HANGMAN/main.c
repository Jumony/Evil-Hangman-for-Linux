// Notes to self...
// my_string functions seem to work as intended.
// words are correctly being placed into the vector
// Maybe the problem is how these strings are being accessed?
// Is there something wrong with the given vector code?
// For some reason, all of the strings reset to size 1 when they enter the dict

#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "generic_vector.h"
#include <ctype.h>

const int restrictedStringLength = 5;

GENERIC_VECTOR* create_dictionary();
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess);

int main(int argc, char* argv[])
{

    // Creates a Vector with 30 elements filling it up with more vectors
    GENERIC_VECTOR* dict = create_dictionary();

	// Testing
	MY_STRING test_string = my_string_init_default();
	my_string_push_back(test_string, 'a');
	my_string_push_back(test_string, 'b');
	printf("test_string size is: %d\n", my_string_get_size(test_string));
	printf("test_string as c-string is %s\n", my_string_c_str(test_string));
	printf("Functions seem to work as expected\n\n");
	my_string_destroy(&test_string);
	// ----------------------------------------------------------------------------


    // Prints amount of words of given lengths
    for (int i = 0; i < 30; i++)
    {
        printf("Words of length %d : %d\n", i, generic_vector_get_size(dict[i]));
    }
	printf("\n");

    // Destroy
	for (int i = 0; i < 30; i++)
	{
		printf("Attempting to delete dict[%d]:\n", i);
		while (!generic_vector_is_empty(dict[i]))
		{
			generic_vector_pop_back(dict[i]);
		}
		printf("SUCCESS\n");
	}

	generic_vector_destroy(dict);

    return 0;
}

GENERIC_VECTOR* create_dictionary()
{
	GENERIC_VECTOR* hpVector = (GENERIC_VECTOR*)malloc(sizeof(GENERIC_VECTOR) * 30);
	MY_STRING hString;
	FILE* fp;

	fp = fopen("dictionary.txt", "r");
	if (fp == NULL)
		exit(1);
	
	for (int i = 0; i < 30; i++)
	{
		hpVector[i] = generic_vector_init_default((void*)my_string_assignment, my_string_destroy);
		if (hpVector[i] == NULL)
			exit(1);
	}



	hString = my_string_init_default();
	if (hString == NULL)
		exit(1);
	
	while (my_string_extraction(hString, fp))
	{
		if (my_string_get_size(hString) < 30)
		{
			printf("string is %s\n", my_string_c_str(hString));
			if (generic_vector_push_back(hpVector[my_string_get_size(hString)], hString) != SUCCESS)
			{
				exit(1);
			}
		}
	}

	// Testing Purposes
	MY_STRING compare_string = my_string_init_c_string("zyzzyvas");
	if (my_string_compare(hString, compare_string))
	{
		printf("------------------------\n");
		printf("Correctly read all strings\n");
		printf("------------------------\n");
	}
	my_string_destroy(&compare_string);
	// Testing Purposes

	fclose(fp);

	return hpVector;
}