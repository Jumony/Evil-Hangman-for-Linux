#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "generic_vector.h"
#include <ctype.h>

const int restrictedStringLength = 5;

void get_dictionary(GENERIC_VECTOR dict[], int size);
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess);

int main(int argc, char* argv[])
{
	GENERIC_VECTOR dict[30];


	get_dictionary(dict, 30);

	for (int i = 0; i < 30; i++)
	{
		printf("Words of length %d : %d\n", i, generic_vector_get_size(dict[i]));
	}

	// Destroy
	for (int i = 0; i <30;i++)
	{
		generic_vector_destroy(&(dict[i]));
	}
	return 0;
}

void get_dictionary(GENERIC_VECTOR dict[], int size)
{
	FILE* fp = fopen("dictionary.txt", "r");
	MY_STRING hWord = my_string_init_default();
	if (hWord == NULL)
	{
		printf("Could not allocate memory\n");
		exit(1);
	}

	if (fp == NULL)
	{
		printf("Could not open dictionary\n");
		exit(1);
	}

	for (int i = 0; i < size; i++)
	{
		dict[i] = generic_vector_init_default((void*)my_string_assignment, my_string_destroy);
	}

	while(my_string_extraction(hWord, fp) != FAILURE)
	{

		if (my_string_get_size(hWord) < size)
		{
			if (generic_vector_push_back(dict[my_string_get_size(hWord)], hWord) == FAILURE)
			{
				printf("Failed to allocate memory\n");
				exit(1);
			}
		}
	}
	my_string_destroy(&hWord);
	fclose(fp);
}

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
{
	if (my_string_assignment(&new_key, current_word_family) == FAILURE)
	{
		return FAILURE;
	}

	for (int i = 0; i < my_string_get_size(word); i++)
	{
		if (tolower(*my_string_at(word, i)) == tolower(guess))
		{
			*my_string_at(new_key, i) = guess;
		}
	}
	return SUCCESS;
}