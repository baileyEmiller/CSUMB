/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw5_1.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw5_1.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, ID, Name, and Date.
/*
 * Title: main_hw5_1.cpp
 * Abstract: given an int, return the reverse using recursive function
 * ID: 4908
 * Name: Bailey Miller
 * Date: 02/27/2023
 */

#include <iostream>
using namespace std;

void recursiveReverse(string str, int size, bool hasStarted);

int main(){
  int numb;
  cin >> numb;
  string str = to_string(numb);

  recursiveReverse(str, str.size(), false);
  cout << "\n";

  return 0;
}

void recursiveReverse(string str, int size, bool hasStarted){
  if(size > 0){
    
    if(hasStarted || (str[size-1] != '0')){
      cout << str[size-1];
      hasStarted = true;
    }
    recursiveReverse(str, size-1, hasStarted);
  }
  return;
}