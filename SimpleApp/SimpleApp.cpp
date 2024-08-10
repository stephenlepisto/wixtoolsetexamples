// SimpleApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>

void PauseBeforeExit()
{
    std::cout << "Press a key to exit" << std::endl;
    int key = _getch();
    if (key == 0)
    {
        key = _getch();
    }
}

int main(int argc, char* argv[])
{
    bool pauseBeforeExit = false;

    if (argc == 2)
    {
        if (strcmp(argv[1], "--pause") == 0)
        {
            pauseBeforeExit = true;
        }
    }

    std::cout << "Hello World!" << std::endl;

    if (pauseBeforeExit)
    {
        PauseBeforeExit();
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
