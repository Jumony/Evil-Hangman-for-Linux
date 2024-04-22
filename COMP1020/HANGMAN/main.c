//------------General Notes-------------//
/*
            For my Personal Use
    We are essentially creating a generic vector
    which holds more generic vectors and within
    each of those generic vectors is a string
    organized by how big the string is. This is
    what we are going to call the dictionary 

    For every guess, we create a tree. This tree
    contains nodes and within each node is a key
    and a generic vector.
    -   The key is used as a way to locate the node.
    -   The generic vector holds multiple strings
    This creates a system where each Node can have a 
    key and hold multiple strings at a time.
    THIS TREE IS THEN ORGANIZED BY THE ALPHABETICAL
    VALUE OF THE 1ST LETTER OF EACH KEY.

    WORD FAMILY refers to a group of strings that
    share the same characteristics ie.)
    -   They are all length 10,
    -   They all have a p in the second position
    It serves as a way for the computer to know
    the largest and thus best word-family to use
    to trick the player

    In our context, a KEY refers to what the player
    has already figured out. In other words, a key
    defines the characteristics of the strings it
    holds. The computer can use a word key to
    access a family of strings to help trick the player 

    The General Loop is:
        After the player guesses a character, the computer
    creates a tree consisting of all possible options that
    the computer may take. It then looks for the tree that
    has the most choices in it and defaults the target word
    to be the first word in that vector. This is effectively
    the part where the computer changed its answer and then
    it will prompt the user to enter another guess.
        - The main principal is that the computer is always
        one step ahead of the player



*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "my_string.h"
#include "generic_vector.h"
#include "avl_tree.h"

#define MAX_SIZE 30

GENERIC_VECTOR* create_dictionary();
Boolean continue_game();
Boolean remaining_words();

int ask_word_length();
int ask_number_of_guesses();

char get_char();

void clear_terminal();
void clear_keyboard_buffer();

int main(int argc, char* argv[]) 
{
    do {
        GENERIC_VECTOR* dictionary = create_dictionary();
        TREE hTree = avl_tree_init_default();
        MY_STRING current_key = my_string_init_default();
        MY_STRING letters_guessed = my_string_init_c_string(" ");
        MY_STRING word_key = my_string_init_default();
        GENERIC_VECTOR largest_family;
        int word_length;
        int number_of_guesses;
        Boolean running_total;
        char current_guess;

        clear_terminal();
        word_length = ask_word_length();
        number_of_guesses = ask_number_of_guesses();
        running_total = remaining_words();


        for (int i = 0; i < word_length; i++)
            my_string_push_back(current_key, '-');

        // logic loop
        clear_terminal();

        do {

            printf("You have %d guesses left\n", number_of_guesses);
            printf("Used Letters: ");
            my_string_insertion(letters_guessed, stdout);

            printf("\nCurrent word: ");
            my_string_insertion(current_key, stdout);

            current_guess = get_char();
            while (check_if_used(letters_guessed, current_guess))
                current_guess = get_char();

            my_string_push_back(letters_guessed, current_guess);
            my_string_push_back(letters_guessed, ',');
            my_string_push_back(letters_guessed, ' ');

            // ISSUE MIGHT BE WITH PUSHBACK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            clear_terminal();

            if (running_total) 
                printf("Running total of the number of words remaining:\n");

            // BASICALLY adds all possible words to a tree
            for (int i = 0; i < generic_vector_get_size(dictionary[word_length]); i++) 
            {
                // Gets a word from the dictionary of a given length and puts it into word_key
                // word_key now holds a possible choice for the computer to take 
                get_word_key_value(current_key, word_key, generic_vector_at(dictionary[word_length], i), current_guess);

                // Pushes the possible choice into a tree
                // To be more specific, pushes a key that has both
                // dashes and characters thus it looks something like:
                // ---p---pp-- etc.
                avl_tree_push(hTree, word_key, generic_vector_at(dictionary[word_length], i));
                // hTree now holds all words with the same length
            }

            // Creates a new vector containing the words largest family
            //  This is what we will use to create a new dictionary
            // THIS IS HOW WE EVADE THE PLAYER
            largest_family = get_largest_family(hTree, running_total);
            generic_vector_destroy(&(dictionary[word_length]));
            dictionary[word_length] = generic_vector_init_default((void*)my_string_assignment, my_string_destroy); // dictionary now holds all possible words
            for (int i = 0; i < generic_vector_get_size(largest_family); i++)
                generic_vector_push_back(dictionary[word_length], generic_vector_at(largest_family, i));

            // Update word_key based on the character that was guessed
            // At this point, we should be within a family all containing the same characterstics with each other
            // We default to the 1st element string for simplicities sake
            // Notice that get_largest_family has already been called before this meaning that this is actually one step ahead
            //  which will allow for a more difficult game
            // ITS ALSO IMPORTANT TO NOTE THAT WE'VE ALREADY CHOSEN THE NEW LARGEST FAMILY. THAT IS WHAT WE ARE COMPARING WORD_KEY TO
            printf("dictionary[word_length], 0 is %s\n", my_string_c_str(generic_vector_at(dictionary[word_length], 0)));
            get_word_key_value(current_key, word_key, generic_vector_at(dictionary[word_length], 0), current_guess);

            // If current key matches the word_key (which represents a possible option), then that means the guessed character is not present in the word 
            // If they are not equal, it implies that the player has trapped the computer and the computer must reveal a letter
            if (my_string_compare(current_key, word_key) == 0) 
            {
                printf("\nI'm sorry, there are no %c's in the word\n\n", current_guess);
                number_of_guesses--;
            }

            if (running_total)
            printf("The computer has %d possibilities remaining\n", generic_vector_get_size(largest_family));

            // Current key now becomes word_key
            my_string_assignment(&current_key, word_key);

            // MAKE SURE TO FREE MEMORY AFTER EVERY GUESS
            // Creates a new AVL_tree or generic_vector
            generic_vector_destroy(&largest_family);
            avl_tree_destroy(&hTree);
            my_string_destroy(&word_key);

            // init for new round
            word_key = my_string_init_default();
            hTree = avl_tree_init_default();

            if (number_of_guesses == 0) {

                printf("I'm sorry, the word I was thinking about was: ");
                my_string_insertion(generic_vector_at(dictionary[word_length], 0), stdout);
                printf("\n\n");
                break;

            }

            // If everything is programmed correctly, the chosen word should be the first word
            //  in a given dictionary at "word length" and thus that is what we have to check.
            //  The dictionary should also be of size one at this point
            if (generic_vector_get_size(dictionary[word_length]) == 1)
            {
                if (my_string_compare(generic_vector_at(dictionary[word_length], 0), current_key) == 0)
                {
                    printf("You win!\nThe word was: ");
                    my_string_insertion(generic_vector_at(dictionary[word_length], 0), stdout);
                    printf("\n\n");
                    break;
                }
            }

        } while (number_of_guesses > 0);

        // Free memory after every game
        avl_tree_destroy(&hTree);
        my_string_destroy(&current_key);
        my_string_destroy(&letters_guessed);
        my_string_destroy(&word_key);
        for (int i = 0; i < MAX_SIZE; i++) 
            generic_vector_destroy(&dictionary[i]);
        free(dictionary);

    } while (continue_game());

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
			if (generic_vector_push_back(hpVector[my_string_get_size(hString)], hString) != SUCCESS)
			{
				exit(1);
			}
		}
	}

    my_string_destroy(&hString);
	fclose(fp);

	return hpVector;
}

Boolean continue_game() {

    char c;

    printf("Would you like to play again? (y/n) ");
    scanf("%c", &c);
    clear_keyboard_buffer();
    c = tolower(c);

    while (!isalpha(c))
    {
        printf("%c is not a valid letter\n", c);
        return continue_game();
    }
    while ((isalpha(c) && c != 'y' && c != 'n'))
    {
        printf("Please enter a (y)es or (n)o\n");
        return continue_game();
    }
    
    if (c == 'y')
        return TRUE;
    else if (c == 'n')
        return FALSE;
    return FALSE;

}

Boolean remaining_words() {

    char c;

    printf("Would you like a running total of the number of words remaining? (y/n) ");
    scanf("%c", &c);
    clear_keyboard_buffer();
    c = tolower(c);

    while (!isalpha(c))
    {
        printf("%c is not a valid letter\n", c);
        return remaining_words();
    }
    while ((isalpha(c) && c != 'y' && c!= 'n'))
    {
        printf("Please enter a (y)es or (n)o\n");
        return remaining_words();
    }
    if (c == 'y') 
        return TRUE;
    else if (c == 'n') 
        return FALSE;
    return FALSE;

}


int ask_word_length() {

    int d;

    printf("How many characters do you want the word to be? ");
    scanf("%d", &d);
    clear_keyboard_buffer();

    while (d <= 2 || d >= MAX_SIZE)
    {
        if (d <= 2)
            printf("\nNo words exist with a size less than two\n\n");
        else if(d >= MAX_SIZE) 
            printf("\nNo words exist with a size greater than thirty\n\n");

        printf("How many characters do you want the word to be? ");
        scanf("%d", &d);
        clear_keyboard_buffer();
    }

    return d;

}

int ask_number_of_guesses() 
{
    int d = 0;

    while ((d <= 0 || d > 26))
    {
        printf("How many guesses do you want? ");
        scanf("%d", &d);
        clear_keyboard_buffer();

        if (d <= 0)
            printf("\nMust have more than one guess...\n\n");
        else if (d > 26)
            printf("\nThat's more guesses than the alphabet...\n\n");
    }
    return d;
}

char get_char() 
{
    char c;

    printf("\nGuess a character: ");
    scanf("%c", &c);
    clear_keyboard_buffer();

    if (isalpha(c)) 
        c = tolower(c);
    else
        return get_char();

    return c;
}

void clear_keyboard_buffer() 
{
    char c;

    do 
    {
        scanf("%c", &c);
    } while (c != '\n');
    return;
}

void clear_terminal() 
{
#ifdef _WIN32
    system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    system("clear");
#else
#error "OS not supported"
#endif
}