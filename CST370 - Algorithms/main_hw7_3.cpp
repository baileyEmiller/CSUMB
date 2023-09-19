/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw7_3.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw7_3.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, ID, Name, and Date.
/*
 * Title: main_hw7_3.cpp
 * Abstract: Partition numbers in multiple ways
 * ID: 4908
 * Name: Bailey Miller
 * Date: 03/22/2023
 */

#include <iostream>
using namespace std;

int main() {
  int size;
  cin >> size;
  int orig[size];
  int arr[size];
  for(int i = 0; i < size; i++){
    cin >> orig[i];
    arr[i] = orig[i];
  }

  //first approach
  int i = 0, j = size-1;
  while(true){
    if(i > j){
      break;
    }
    if(arr[i] > 0){
      if(arr[j] < 0){
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        continue;
      }else{
        j--;
        continue;
      }
    }else{
      i++;
      continue;
    }
  }

  for(int i = 0; i < size; i++){
    if(i != 0){
      cout << " " << arr[i];
    }else{
      cout << arr[i];
    }
    arr[i] = orig[i];
  }
  cout << endl;

  //third approach (2nd for assignment)
  i = size-1, j = size-2;
  while(true){
    bool didUpdate = false;
    if(i < 0){
      i = size - 1;
    }
    if(j == -1 || (j == 0 && arr[j] < 0)){
      break;
    }
    if(arr[j] < 0){
      j--;
      didUpdate = true;
    }
    if(arr[i] > 0){
      i--;
      if(!didUpdate){
        j--;
      }
      didUpdate = true;
    }
      if(didUpdate){
        continue;
      }
      int temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
      continue;
  }

  for(int i = 0; i < size; i++){
    if(i != 0){
      cout << " " << arr[i];
    }else{
      cout << arr[i];
    }
  }
  cout << endl;

  
	return 0;
}
