#pragma once
#include "my_string.h"
#include "generic_vector.h"
#include "avl_tree.h"

// Colors
void color_black();
void color_red();
void color_green();
void color_yellow(); 
void color_blue();
void color_purple();
void color_cyan();
void color_white();
void color_reset();

void print_scroll();

GENERIC_VECTOR* create_dictionary();
Boolean continue_game();
Boolean remaining_words();

int ask_word_length();
int ask_number_of_guesses();
int initial_play_prompt();

char get_char();

void clear_terminal();
void clear_keyboard_buffer();