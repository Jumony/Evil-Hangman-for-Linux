#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

const int restrictedStringLength = 5;

int main(int argc, char* argv[])
{
	MY_STRING arr[100];
	arr[0] = my_string_init_c_string("COPY ME!");
	for (int i = 1; i < 100; i++)
	{
		arr[i] = my_string_init_copy(arr[0]);
	}

	my_string_destroy(&arr[0]);
	arr[0] = my_string_init_c_string("FIRST FIFTY!");

	for (int i = 0; i < 50; i++)
	{
		my_string_assignment(arr[i], arr[0]);
	}

	int decrementer = 99;
	for (int i = 0; i < 50; i++)
	{
		my_string_swap(arr[i], arr[decrementer]);
		decrementer--;
	}
	printf("lab 05---------------------------/n");
	for(int i = 0; i < 100; i++)
	{
	  printf("%d ", i);
		my_string_insertion(arr[i], stdout);
		printf("\n");
		my_string_destroy(&arr[i]);
	}
	printf("lab 06-------------------");
	
	printf("\n");
	char* test_string1 = "concat ";
	char* test_string2 = "string";
	MY_STRING hString1 = my_string_init_c_string(test_string1);
	MY_STRING hString2 = my_string_init_c_string(test_string2);

	printf("String 1 is: %s\nString 2 is: %s\n", my_string_c_str(hString1), my_string_c_str(hString2));
	my_string_concat(hString1, hString2);
	printf("Concatenated string results in: %s\n", my_string_c_str(hString1));

	my_string_push_back(hString1, '!');
	printf("push_back character '!' results in: %s\n", my_string_c_str(hString1));

	my_string_pop_back(hString1);
	printf("pop_back results in: %s\n", my_string_c_str(hString1));

	printf("my_string_at index 5 is %c\n", *(my_string_at(hString1, 5)));

	if (my_string_empty(hString1) == TRUE)
	  {
	    printf("my_string_empty returns: TRUE\n");
	  }
	else
	  {
	    printf("my_string_empty returns: FALSE\n");
	  }

	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return 0;
}
