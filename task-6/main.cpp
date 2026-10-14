#include "main.h"

int main(int argc, char* argv[])
{
    //The project is currently set up with a function to produce random numbers between
    //intervals that you specify. Modify the current solution to provide the functionality
    //requested by the document that outlines the challenges.
    
    //Here is an example just showing how you use the random(min, max) function:
    std::cout << "Here is a random number between 1 and 10: " << random(1, 10) << std::endl;
    std::cout << "And here is one between -3 and -5: " << random(-3, -5) << std::endl;

    return 0;
}