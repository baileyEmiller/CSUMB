/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw9_2.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw9_2.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, ID, Name, and Date.
/*
 * Title: main_hw9_2.cpp
 * Abstract: reorder the alphabet
 * ID: 4908
 * Name: Bailey Miller
 * Date: 04/13/2023
 */
#include <iostream>
using namespace std;

bool search(char *arr, char data, int size);
void insert(char *arr, int index, char data, int size);
void orderChar(char arr[], string orig[], int size, int &orderIndex, int offset,
               int &init, int minSize);

int main() {
  int size;
  char order[26];
  int orderIndex = 0;
  int minSize = 10;
  cin >> size;
  string words[size];
  for (int i = 0; i < size; i++) {
    cin >> words[i];
    if (words[i].length() < minSize) {
      minSize = words[i].length();
    }
  }

  for(int i = 0; i < minSize; i++){
    int temp = 0;
  orderChar(order, words, size, orderIndex, i, temp, minSize);
  }

  for (int i = 0; i < orderIndex; i++) {
    cout << order[i];
    if ('a' <= order[i+1] && order[i+1] <= 'z') {
      cout << "->";
    }else{
      break;
    }
  }
  cout << endl;
  return 0;
}

bool search(char *arr, char data, int size) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == data) {
      return true;
    }
  }
  return false;
}

void insert(char *arr, int index, char data, int size) {
  for (int i = index; i < size; i++) {
    arr[i + 1] = arr[i];
  }
  arr[index] = data;
}

void orderChar(char arr[], string orig[], int size, int &orderIndex, int offset,
               int &init, int minSize) {
  for (int i = init; i < size; i++) {
    if (!search(arr, orig[i][offset], orderIndex)) {
      insert(arr, orderIndex, orig[i][offset], size);
      orderIndex++;
    } else {
      continue;
    }
  }
}