Program Crashes:
    Process of fixing:
    - Found out that my program was crashing because something goes wrong when I destroy the strings within the dictionary
    so I looked through the code and saw everything was fine. Thus the problem must be because I incorrectly pushed the strings
    to the vector and turns out that was the problem. I was appending null string pointers to the dictionary and obviously I
    cant free a null pointer. I fixed that hitch but now, whenever the program tries to resize a vector, it crashes most likely
    because it is incorrectly copying the string

Memory Leak:
    Process of fixing:
    - Found out that I am not correctly destroying the strings that are within the vectors. 
    This is mainly because the strings are not properly being added to the vector therefore It's like im trying to free a NULL pointer.