#include <stdio.h> // include directive
#include <stdlib.h> // include directive
#include <ctype.h> // include directive
#include "my_string.h" // include header

struct my_string // declare known type of structure
{
    int size; // the number of characters currently in the object
    int capacity; // total capacity of the object
    char* data; // pointer to the object -malloc starts here
};
typedef struct my_string My_string; // define type

Boolean check_if_used(MY_STRING guess_list, char c) {

    My_string* pMy_string = (My_string*)guess_list;
    int i;

    for (i = 0; i < my_string_get_size(guess_list); i++) {

        if (pMy_string->data[i] == c) {

            printf("You have already guessed that letter! Try again...\n");
            return TRUE;

        }

    }

    return FALSE;

}

// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
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
    My_string* pString = malloc(sizeof(My_string));
    if (pString == NULL)
    {
        printf("Unable to allocate memory, returning NULL");
        return NULL;
    }

    pString->capacity = 7;
    pString->size = 0;
    pString->data = (char*)malloc(sizeof(char) * pString->capacity);
    if (pString->data == NULL)
    {
        free(pString); // Free the My_string structure if data allocation fails
        printf("Unable to allocate memory, returning NULL");
        return NULL;
    }
    return pString;
}

//SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
void my_string_destroy(ITEM* phItem)
{
    My_string* pMy_string = (My_string*) *phItem; // cast to the known type
    free(pMy_string->data); // release the data pointer within the object
    free(pMy_string); // release the pointer to the object itself
    *phItem = NULL; // and set it to NULL
}

//SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
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

// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
int my_string_get_capacity(MY_STRING hMy_string)
{
    My_string* pString = (My_string*) hMy_string;
    return pString->capacity;
}

// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
int my_string_get_size(MY_STRING hMy_string)
{   
    My_string* pString = (My_string*) hMy_string;
    return pString->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string) {

    My_string* pLeft_string = (My_string*)hLeft_string;
    My_string* pRight_string = (My_string*)hRight_string;
    int i;

    for (i = 0; i < pLeft_string->size && i < pRight_string->size; i++) {

        if (pLeft_string->data[i] < pRight_string->data[i])
        {
            return -1;
            //break;
        }
        else if (pLeft_string->data[i] > pRight_string->data[i]) {

            return 1;
            // break
        }

    }
    return 0;
}

//SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
    My_string* pString = (My_string*) hMy_string;
    char c;

    if (fp == NULL || pString == NULL)
    {
        return FAILURE;
    }

    // Reset string size
    pString->size = 0;

    // Allocate memory for string data if not already allocated
    if (pString->data == NULL)
    {
        pString->data = (char*)malloc(sizeof(char) * 7);
        if (pString->data == NULL)
        {
            return FAILURE;
        }
        pString->capacity = 7;
    }

    // Read characters from file until EOF or whitespace
    while ((c = fgetc(fp)) != EOF && !isspace(c))
    {
        // Resize data buffer if needed
        if (pString->size >= pString->capacity - 1) // Leave space for null terminator
        {
            char* temp = (char*)realloc(pString->data, sizeof(char) * (pString->capacity * 2));
            if (temp == NULL)
            {
                return FAILURE;
            }
            pString->data = temp;
            pString->capacity *= 2;
        }

        // Store character in string
        pString->data[pString->size++] = c;
    }

    // Null-terminate the string
    pString->data[pString->size] = '\0';

    // Handle EOF
    if (feof(fp)) // Check for end of file
    {
        return FAILURE;
    }

    // Put back the whitespace character into the stream if it's not EOF
    if (!isspace(c) && ungetc(c, fp) == EOF)
    {
        return FAILURE;
    }

    return SUCCESS;
}

// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
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

// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
Status my_string_push_back(MY_STRING hString, char item)
{
    My_string* pString = (My_string*)hString;
    int i;
      // checks to see if the size of the character exceeds the capacity.
      // if so, double the capacity of the struct, create a new string struct,
      // and then paste values of previous string struct into the new one which
      // has double the capacity of the old struct
    if (pString->size >= pString->capacity)
    {
        char* temp = (char*)malloc(sizeof(char) * pString->capacity * 2);
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

// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// Should add an automatic resize function soon.
// Resize by 1/2 after size is 1/4 of capacity
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

// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
char* my_string_at(MY_STRING hString, int index)
{
    My_string* pString = (My_string*) hString;
    if (index - 1 > pString->size || index < 0)
    {
        return NULL;
    }

    return &(pString->data[index]);
}

// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
char* my_string_c_str(MY_STRING hString)
{
    My_string* pString = (My_string*) hString;

    if (pString->size <= 0)
    {
        return NULL;
    }
    if (my_string_push_back(hString, '\0') == FAILURE)
    {
      printf("Failed to end with null terminator\n");
        return NULL;
    }

    pString->size--; // simulates a c string
    return (char*)&(pString->data[0]); // pString->data is char*
}

// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
    My_string* pResult = (My_string*) hResult;
    My_string* pAppend = (My_string*) hAppend;
    
    if (pResult->size + pAppend->size > pResult->capacity)
    {
        char* temp = (char*)malloc(sizeof(char) * (pResult->size + pAppend->size + 1));
        if (temp == NULL)
        {
            return FAILURE;
        }
        for (int i = 0; i < pResult->size; i++)
        {
            temp[i] = pResult->data[i];
        }
        free(pResult->data);
        pResult->data = temp;
        pResult->capacity = pResult->size + pAppend->size + 1;
    }

    for (int i = 0; i < pAppend->size; i++)
    {
        pResult->data[pResult->size] = pAppend->data[i];
        pResult->size++;
    }
    return SUCCESS;
}

// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
Boolean my_string_empty(MY_STRING hMy_string)
{
    My_string* pString = (My_string*) hMy_string;

    if (pString->size <= 0)
    {
        return TRUE;
    }
    return FALSE;
}

// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// May have to make changes and make it so that my_string_assignment
// copies the phLeft and puts it into hRight
// For some reason, the documentation wants us to use
//  MY_STRING hLeft even though we are supposedly not supposed to do
//  pass by reference...
Status my_string_assignment(MY_STRING* phLeft, MY_STRING hRight)
{
    My_string* pLeft = (My_string*)*phLeft;
    My_string* pRight = (My_string*)hRight;

    if (pLeft == NULL)
    {
        char* temp = my_string_c_str(hRight);
        pLeft = my_string_init_c_string(temp);
        *phLeft = pLeft;
        return SUCCESS;
    }

    if (pLeft != NULL)
    {
        pLeft->size = 0;
        for (int i = 0; i < pRight->size + 1; i++)
        {
            my_string_push_back(pLeft, pRight->data[i]);
        }

        *phLeft = pLeft;
        return SUCCESS;
    }
    return FAILURE;

}

Status get_word_key_value(MY_STRING current_key, MY_STRING new_key, MY_STRING word, char guess) {
    char letter;
    // Clear out new_key
    while (!my_string_empty(new_key))
        my_string_pop_back(new_key);
        
    // Iterate over each character in 'word' and determine whether to use 'guess' or the corresponding character from 'current_key'
    for (int i = 0; i < my_string_get_size(word); i++) 
    {   
        // If guess is correct, push character onto new_key
        if (*my_string_at(word, i) == guess)
            letter = guess;

        // If guess is wrong, push a dash to represent a blank character
        else
            letter = *my_string_at(current_key, i);

        // Push the determined character onto the new_key string
        if (!my_string_push_back(new_key, letter)) {
            return FAILURE; // Return FAILURE if the push operation fails
        }
    }
    return SUCCESS;
}
