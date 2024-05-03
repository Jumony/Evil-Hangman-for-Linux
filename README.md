# Evil Hangman
Evil Hangman is a challenging word-guessing game written in C where the computer constantly evades the player's guesses by dynamically changing its answers.
It utilizes a handwritten string data type and implements an AVL Tree to efficiently manage and update possible word choices, ensuring the computer always selects the word that best avoids the player's guesses.
After each guess, the computer traverses the tree to identify the word family with the most remaining words, stored in an Associative Array, maximizing its evasion strategy.
Built in Spring 2024 UMass Lowell Computing II Lab

  ## What I learned:
  - **Memory Management**: Understanding how to allocate and deallocate memory in C efficiently.
  - **Error Handling**: Dealing with memory leaks and segmentation faults, essential for robust programming.
  - **Data Structures**: Implementing an AVL Tree and an Associative Array to optimize game logic.
  - **String Manipulation**: Gaining a deeper understanding of string operations in C.
  - **System Interaction**: Executing terminal commands within the code.
  - **Version Control**: Utilizing Git for project management and collaboration.


  ## Planned Additions:
  - **Compatibility:** Expanding compatibility to other platforms for wider accessibility.
  - **Graphical User Interface (GUI)**: Implementing a user-friendly interface for a more engaging gaming experience.

  ## How to Run:

  1. Type `make clean` in the terminal to reset everything to default settings.
  2. Run the Makefile by typing `make` into the terminal.
  3. Execute the `string_driver` file to start the game.


*Note: When prompted, choosing to see the running total enables a debug mode meant for developers.*
