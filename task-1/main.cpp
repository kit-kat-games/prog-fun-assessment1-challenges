/*
    Assessment 1 - Challenge 1
    Task: ASCII Art Game Header
    Uses std::cout/cout in order to produce an ASCII boat in the terminal
*/

#include <iostream>

int main(int argc, char* argv[])
{
    // Uses a Raw String Literal in order to format the boat properly within the code
    // Shows what will be printed easier, would allow for easier changing, and is overall better for
    // formatting than a large amount of std::cout statements for each individual line in the ASCII art
    std::string myBoat = R"(
                  |
                 /|\
                / | \    a boat
               /  |  \
              / --|-- \
             /    |    \
            /-----|-----\
     |----\       |      /----|
      \- - -------------- - -/
       \ - -- - - - - - -- -/
 /\  /\ \/\  /\  /\  /\  /\/ /\  /\
/  \/  \/  \/  \/  \/  \/  \/  \/  \
        )";

    std::cout << myBoat << std::endl;
}