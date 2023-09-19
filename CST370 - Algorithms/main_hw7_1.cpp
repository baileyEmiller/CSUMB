/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw7_1.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw7_1.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, ID, Name, and Date.
/*
 * Title: main_hw7_1.cpp
 * Abstract: Return minimum number in array using divide and conquer recursion technique. It's basically the example code https://repl.it/@YBYUN/sumdivNconqcpp that's been modified to do what it needs to do
 * ID: 4908
 * Name: Bailey Miller
 * Date: 03/21/2023
 */

#include <iostream>
using namespace std;

int min_div_N_conq(int A[ ], int start, int end);

int main() {
  int size;
  cin >> size;
  int arr[size];
  for(int i = 0; i < size; i++){
    cin >> arr[i];
  }
  cout << min_div_N_conq(arr, 0, size-1) << endl;
	return 0;
}

int min_div_N_conq(int A[ ], int start, int end) 
{
    if (start == end){
        return A[start];
    }
    else {
      int min1 = min_div_N_conq (A, start, (start+end)/2);
      int min2 = min_div_N_conq (A, (start+end)/2+1, end);

      if(min1 > min2){
        return min2;
      }else{
        return min1;
      }
    }
}