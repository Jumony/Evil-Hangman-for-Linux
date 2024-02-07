#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

const int restrictedStringLength = 5;

int main(int argc, char* argv[])
{
  MY_STRING hMy_string = NULL;
  FILE* fp;

  hMy_string = my_string_init_default();
  fp = fopen("dictionary.txt", "r");

  // While this returns SUCCESS...
  while (my_string_extraction(hMy_string, fp))
  {
    // if hMy_string is of appropriate length...
    if (my_string_get_size(hMy_string) <= restrictedStringLength)
    {
      // and if my_string_insertion function successfully inserts string into stream...
      if (my_string_insertion(hMy_string, stdout))
      {
        printf("\n");
      }
    }


    // Checks for whitespace after my_string_insertion has inserted string into stream
    if (fgetc(fp)==' ')
    {
      printf("Found a space after the string\n");
    }
  }

  my_string_destroy(&hMy_string);
  fclose(fp);
  return 0;
}
