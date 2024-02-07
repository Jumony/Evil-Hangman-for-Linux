#include <stdio.h>
#include <stdlib.h>

typedef void* MY_STRING;

enum status
{
    FAILURE, SUCCESS
};
typedef enum status Status;

//Precondition: None
//Postcondition: Allocate space for a string object that represents the empty
// string. The string will have capacity 7 and size 0 by default. A copy of
// the address of the opaqu object will be returned on success and NULL on
// failure.
MY_STRING my_string_init_default(void);

//Precondition: phMy_string holds the address of a valid handle to a MY_STRING
// object.
//Postcondition: The memory used for the MY_STRING object has be reclaimed by
// the system and the handle referred to by the pointer phMy_string has been
// set to NULL.
void my_string_destroy(MY_STRING* phMy_string);

//Precondition: c_string is a valid null temrinated c-string.
//Postcondition: Allocate space for a string object that represents a string
// with the same value as the given c-string. The capacity of the string
// object will be set to be one greater than is required to hold the string.
// As an example, the string "the" would set capacity at 4 instead of 3. A
// copy of the address of the opaque object will be returned on success and
// NULL on failure.
MY_STRING my_string_init_c_string(const char* c_string);

//Precondition: hMy_string is the handle to a valid My_string object
//Postcondition: hMy_string will be the handle of a string object that contains
// the next string from the file stream fp according to the following rules
// 1): Leading whitespace will be ignored
// 2): All characters (after the first non-whitespace character is obtained
//  and included) will be added to the string until a stopping condition
//  is met. The capacity of the string will continue to grow as needed
//  until all characters are stored.
// 3): A stopping condition is met if we read a whitespace character after
//  we have read at least one non-whitespace character or if we reach
//  the end of the file
//  Function will return SUCCESS if a non-empty string is read successfully.
//  and failure otherwise. Remember that the incoming string may already 
//  contain some data and this function should replace the data but not
//  necessarily resize the array unless needed.
Status my_string_extraction(MY_STRING hMy_string, FILE* fp);

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Writes the characters contained in the string object indicated
// by the handle hMy_string to the file stream fp.
// Function will return SUCCESS if it successfully writes the string and
// FAILURE otherwise.
Status my_string_insertion(MY_STRING hMy_string, FILE* fp);

//Precondition: hMy_string is the handle of a valid My_string object.
//Postcondition: Returns a copy of the integer value of the object's capacity.
int my_string_get_capacity(MY_STRING hNy_string);

//Precondition: hMy_string is the handle of a valid My_string object.
//Postcondition: Returns a copy of the integer value of the object's size.
int my_string_get_size(MY_STRING hMy_string);

//Precondition: hLeft_string and hRight_string are valid My_string objects.
//Postcondition: returns an integer less than zero if the string represented
// by hLeft_string is lexicographically smaller than hRight_string. If
// one string is a prefix of the other string then the shorter string is
// considered to be the smaller one. (app is less than apple). Returns
// 0 if the strings are the same and returns a number greater than zero
// if the string represented by hLeft_string is bigger than hRight_string.
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string);

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: If successful, places the character item at the end of the
// string and returns SUCCESS. If the string does not have enough room and
// cannot resize to accomodate the new character then the operation fails
// and FAILURE is returned. The resize operation will attempt to amortize
// the cost of a resize by making the string capacity somewhat larger than
// it was before (up to 2 times bigger).
Status my_string_push_back(MY_STRING hMy_string, char item);

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Removes the last character of a string in a constant time.
// Guaranteed to not cause a resize operation of the internal data. Returns
// SUCCESS on success and FAILURE if the string is empty.
Status my_string_pop_back(MY_STRING hMy_string);

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Returns the address of the character located at the given
// index if the index is in bounds but otherwise returns NULL. This address
// is not usable as a c-string since the data is not NULL terminated and is
// intended to just provide access to the elemtn at that index.
char* my_string_at(MY_STRING hMy_string, int index);

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Returns the address of the first element of the string object
// for use as a c-string. The resulting c-string is guaranteed to be NULL
// terminated and the memory is still maintained by the string object though
// the NULL is not actually counted as part of the string (in size);
char* my_string_c_str(MY_STRING hMy_stirng);