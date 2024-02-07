#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include <ctype.h>

struct my_string
{
    char* data;
    int size;
    int capacity;
};
typedef struct my_string My_string;

// IMPORTANT COMMENT!!!!
// Most of these functions define My_string* pString = (My_string*) hMyString for several reasons:
// 1. typecast so that it is way easier to reference the inputted parameter
// 2. Rather than creating a whole new struct, we are working with the same struct that was passed as a parameter.
// sure, we can create a whole new struct and rewrite our code to work around it but it would quickly become heavy
// and it would also become less easy to work with. But by declaring it as a pointer to a struct, we can just work
// with a single struct and manipulate that single struct rather than creating a whole new struct and copying
// the values from the old struct into the new struct.
// 3. WHENEVER POSSIBLE, SIZE IS INCREMENTED BY 1 AT THE END OF A FUNCTION TO PREPARE FOR THE NEXT.
// THIS IS A DESIGN CHOICE
MY_STRING my_string_init_default()
{
    My_string* pString = malloc(sizeof(My_string)); // Set as pointer to allocate space on heap
    if (pString == NULL)
    {
        printf("Unable to allocate memory, returning NULL");
        return NULL;
    }

    // Sets default values
    pString->capacity = 7;
    pString->size = 0;
    pString->data = (char*)malloc(sizeof(char) * pString->capacity);

    if (pString->data == NULL)
    {
        free(pString);
        return NULL;
    }
    return pString;
}

void my_string_destroy(MY_STRING* phMy_string)
{
  // Pass by reference (passing in a pointer)
  // Sets a My_string pointer to struct (pString) to the inputted parameter. Allows us to modify the inputted parameter directly
  // By setting two pointers equal to each other, by modifying one pointer, you are effectively modifying the entire values at the address 
    My_string* pString = (My_string*) *phMy_string; //The right side of the expression equates to My_string* phMy_string
    free(pString->data);
    free(pString);
    *phMy_string = NULL;
}

/*
  void my_string_destroy2(void* phMy_string)
{
  // Does not work because we are supposed to pass in a pointer to a void* which would allow us to modify the referenced parameter.
  // Since we want to modify pString, we need to pass in a pointer to a void*
  // IN SUMMARY: we are not even working with the referenced parameter. This is currently pass by value and not pass by reference. 
  My_string* pString = (My_string*) phMy_string;
    free(pString->data);
    free(pString);
    *phMy_string = NULL;
}
*/
MY_STRING my_string_init_c_string(const char* c_string)
{
    //Finds length of string
    int length = 0;
    while (c_string[length] != '\0')
    {
        length++;
    }
    //----------------------
    My_string* pString;
    pString = (My_string*)malloc(sizeof(My_string)); // Prepares a My_string struct on the heap by allocating just enough space for all contents of it.
    if (pString == NULL)
    {
        printf("Failed to allocate memory. Returning NULL");
        return NULL;
    }
    pString->size = length;
    pString->capacity = length + 1;
    pString->data = (char*)malloc(sizeof(char) * pString->capacity); // Data contains a string with a specified size and capacity. 
    if (pString->data == NULL)
    {
        free(pString);
        printf("Failed to allocate memory. Returning NULL");
        return NULL;
    }
    for (int i = 0; i < pString->size; i++)
    {
        pString->data[i] = c_string[i];
    }
    return pString;
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
    My_string* pString = (My_string*) hMy_string; // Typecasts hMy_string to and sets it equal to pString so its easier to reference. 
    char c;
    int character;

    pString->size = 0;

    if (fp == NULL)
    {
        return FAILURE;
    }

    // Gets character 'c' and makes sure that it is not a whitespace, if so, keep getting next character until we dont hit a whitespace
    c = fgetc(fp);
    if (c == EOF)
    {
        return FAILURE;
    }
    while(c == ' ')
    {
        c = fgetc(fp);
    }

    // puts the first character into pString's data member and then increments size to be ready for next character
    pString->data[pString->size] = c;
    pString->size++;

    // fgetc returns the character that is read as an integer value
    // finishes up gathering the rest of the characters in the string
    character = fgetc(fp);
    while(character != EOF && !isspace(character))
    {
        if (pString->size >= pString->capacity)
        {
            char* temp = (char*) malloc(sizeof(char) * pString->capacity * 2);
            if (temp == NULL)
            {
                return FAILURE;
            }

            for (int i = 0; i < pString->size; i++)
            {
                temp[i] = pString->data[i];
            }
            free(pString->data); 
            pString->data = temp;
            pString->capacity *= 2;
        }
	// finishes up with the rest of the string
        pString->data[pString->size] = character;
        pString->size++;
        character = fgetc(fp);

    }

    // if character hits a space, we've reached the end of the word so
    // we use ungetc to setup for the next string by ending right before
    // the white space.
    // ungetc puts the character back into the input stream
    if (isspace(character))
    {
      // what is this checking? 
        if (ungetc(character, fp) == EOF)
        {
            return FAILURE;
        }
    }
    return SUCCESS;
}

// The reason the parameter is a void* and not a void** is because
// we simply want to modify the values within the struct and not the
// struct itself. Making this into a void** is possible but then we
// will have to dereference which is an extra step
// CHECK THIS ONE FOR UNDERSTANDING
Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
    if (fp == NULL)
    {
        return FAILURE;
    }

    // typecast to make it easier to reference
    My_string* pString = (My_string*)hMy_string;
    for (int i = 0; i < pString->size; i++)
    {
        // checks to see if we are at the end of the file
        if (fputc(pString->data[i], fp) == EOF)
        {
            return FAILURE;
        }
    }
    return SUCCESS;
}

int my_string_get_capacity(MY_STRING hMy_string)
{
    My_string* pString = (My_string*) hMy_string;
    return pString->capacity;
}

int my_string_get_size(MY_STRING hMy_string)
{
  My_string* pString = (My_string*) hMy_string;
  return pString->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
    My_string* pLeftString = (My_string*) hLeft_string;
    My_string* pRightString = (My_string*) hRight_string;

    int i = 0;

    while (i < my_string_get_size(pLeftString) && i < my_string_get_size(pRightString) && pLeftString->data[i] == pRightString->data[i])
    {
        i++;
    }
    if (i < my_string_get_size(pLeftString) && i < my_string_get_size(pRightString) && pLeftString->data[i] != pRightString->data[i])
    {
        return pLeftString->data[i] - pRightString->data[i];
    }
    else if (i == my_string_get_size(pLeftString) && i == my_string_get_size(pRightString))
    {
        return 0;
    }
    return pLeftString->size - pRightString->size;
}

Status my_string_push_back(MY_STRING hString, char item)
{
    My_string* pString = (My_string*)hString;
    char* temp;
    int i;

      // checks to see if the size of the character exceeds the capacity.
      // if so, double the capacity of the struct, create a new string struct,
      // and then paste values of previous string struct into the new one which
      // has double the capacity of the old struct
    if (pString->size >= pString->capacity)
    {
        temp = (char*)malloc(sizeof(char) * pString->capacity * 2);
        if (temp == NULL)
        {
            printf("Unable to allocate memory");
            return FAILURE;
        }

        for (i = 0; i < pString->size; i++)
        {
            temp[i] = pString->data[i];
        }

        free(pString->data); // dont forget to free
        pString->data = temp; // temp is a c-string (pointer to beginning of string). data is ALSO a c-string
        pString->capacity *= 2;
    }

    pString->data[pString->size] = item;
    pString->size++;
    return SUCCESS;
}


Status my_string_pop_back(MY_STRING hString)
{
    My_string* pString = (My_string*) hString;

    if (pString->size == 0)
    {
        return FAILURE;
    }
    pString->size--;
    return SUCCESS;
}

char* my_string_at(MY_STRING hString, int index)
{
    My_string* pString = (My_string*) hString;
    if (index - 1 > pString->size || index < 0)
    {
        printf("Invalid Index");
        return NULL;
    }

    return &(pString->data[index]);
}

char* my_string_c_str(MY_STRING hString)
{
    My_string* pString = (My_string*) hString;

    if (pString->size == 0)
    {
        return NULL;
    }

    if (my_string_push_back((void*) pString, '\0') == FAILURE)
    {
        return NULL;
    }

    pString->size--;
    return pString->data; // pString->data is 
}
