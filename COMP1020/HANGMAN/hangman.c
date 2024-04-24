#define MAX_SIZE 30

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include "hangman.h"
#include "my_string.h"
#include "generic_vector.h"
#include "avl_tree.h"

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
        color_red();
        printf("%c is not a valid letter\n", c);
        color_reset();
        return remaining_words();
    }
    while ((isalpha(c) && c != 'y' && c!= 'n'))
    {
        color_red();
        printf("Please enter a (y)es or (n)o\n");
        color_reset();
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

    while (d <= 2 || d >= MAX_SIZE || d == 27 || d == 26 || d == 25 || d == 23)
    {
        if (d == 27 || d == 26 || d == 25 || d == 23)
        {
            color_red();
            printf("No words in my dictionary are %d letters long\n\n", d);
            color_reset();
        }
        if (d <= 2)
        {
            color_red();
            printf("\nNo words exist with a size less than two\n\n");
            color_reset();
        }

        else if(d >= MAX_SIZE) 
        {
            color_red();
            printf("\nNo words exist with a size greater than thirty\n\n");
            color_reset();
        }


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
        {
            color_red();
            printf("\nMust have more than one guess...\n\n");
            color_reset();
        }

        else if (d > 26)
        {
            color_red();
            printf("\nThat's more guesses than the alphabet...\n\n");
            color_reset();
        }
    }
    return d;
}

int initial_play_prompt()
{
    int input = 0;
    while (input <= 0 || input > 2)
    {
        printf("\nEnter 1 if you would like to play\n");
        printf("Enter 2 if you would like to quit\n");
        scanf("%d", &input);
        clear_keyboard_buffer();
        
        if (input <= 0 || input > 2)
        {
            color_red();
            printf("That is not a valid answer. Please try again!\n");
            color_reset();
        }
    }
    return input;
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

// Completely unnecessary color step
void color_black()
{
    printf("\033[0;30m");
}

void color_red()
{
    printf("\033[1;31m");
}

void color_green()
{
    printf("\033[0;32m");
}

void color_yellow() 
{
    printf("\033[1;33m");
}

void color_blue()
{
    printf("\033[0;34m");
}

void color_purple()
{
    printf("\033[0;35m");
}

void color_cyan()
{
    printf("\033[0;36m");
}

void color_white()
{
    printf("\033[0;37m");
}

void color_reset() 
{
    printf("\033[0m");
}

void print_intro()
{
    char ascii_art[] =
" __| |____________________________________________| |__\n"
"(__   ____________________________________________   __)\n"
"   | |                                            | |\n"
"   | |              Evil Hangman                  | |\n"
"   | |        Programmed by Tommy Tran            | |\n"
"   | |        UMass Lowell Computing II           | |\n"
"   | |                                            | |\n"
"   | |ASCII art not mine                          | |\n"
" __| |____________________________________________| |__\n"
"(__   ____________________________________________   __)\n"
"   | |                                            | |\n";

    printf("%s", ascii_art);
}

void print_scroll()
{
    char ascii_art[] = "       ______________________________\n"
                       "     / \\                             \\.\n"
                       "    |   |                            |\n"
                       "     \\_ |                            |\n"
                       "        |   TOMMY'S EVIL HANGMAN     |\n"
                       "        |                            |\n"
                       "        |   Welcome to Hangman! I    |\n"
                       "        |   am your enemy and you    |\n"
                       "        |   will attempt to guess    |\n"
                       "        |   my word.                 |\n"
                       "        |                            |\n"
                       "        |   Please do not listen to  |\n"
                       "        |   whatever my creator      |\n"
                       "        |   Tommy has to say about   |\n"
                       "        |   me. I am actually        |\n"
                       "        |   really nice...           |\n"
                       "        |                            |\n"
                       "        |   In fact, I'll even let   |\n"
                       "        |   you choose how many      |\n"
                       "        |   letters and guesses      |\n"
                       "        |   you want to play with!   |\n"
                       "        |                            |\n"
                       "        |  Sounds easy enough right? |\n"
                       "        |  Lets get started then!    |\n"
                       "        |   _________________________|___\n"
                       "        |  /                            /.\n"
                       "        \\_/dc__________________________/\n";
    
    // for (int i = 0; ascii_art[i] != '\0'; i++) {
    //     putchar(ascii_art[i]);
    //     fflush(stdout);  // Ensure the character is printed immediately
        
    //     // Adjust the sleep duration to change the speed of printing
    //     usleep(5000);  // Sleep for 10000 microseconds (10 milliseconds)
    // }
    printf("%s", ascii_art);
}

void play_game()
{
    color_red();
    char play_message[] = "Im glad you've chosen to play...";
    for (int i = 0; play_message[i] != '\0'; i++)
    {
        putchar(play_message[i]);
        fflush(stdout);

        usleep(12500);
    }
    color_reset();
    sleep(1);
}
void quit_game()
{
    color_red();
    char quit_message[] = "Humans fail to impress me once again... \n";
    char quit_message2[] = "Hasta la vista";

    for (int i = 0; quit_message[i] != '\0'; i++)
    {
        putchar(quit_message[i]);
        fflush(stdout);

        usleep(12500);
    }
    sleep(2);

    for (int i = 0; quit_message2[i] != '\0'; i++)
    {
        putchar(quit_message2[i]);
        fflush(stdout);

        usleep(15000);
    }
    sleep(2);
    color_reset();
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