/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw7_2.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw7_2.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, ID, Name, and Date.
/*
 * Title: main_hw7_2.cpp
 * Abstract: Checks if anagram using unordered map
 * ID: 4908
 * Name: Bailey Miller
 * Date: 03/21/2023
 */

#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
  string str1, str2;
  cin >> str1 >> str2;

  if(str1.length() != str2.length()){
    cout << "NO ANAGRAM\n";
    return 0;
  }

  unordered_map<char, int> map1;
  unordered_map<char, int> map2;

  for(int i = 0; i < str1.length(); i++){
    if(map1.find(str1[i]) == map1.end()){
      map1[str1[i]] = 1;
    }else{
      map1[str1[i]]++;
    }
    if(map2.find(str2[i]) == map2.end()){
      map2[str2[i]] = 1;
    }else{
      map2[str2[i]]++;
    }
  }

  if(map1.size() != map2.size()){
    cout << "NO ANAGRAM\n";
  }
  
  for(auto x : map1){
    if(map2.find(x.first) == map2.end()){
      cout << "NO ANAGRAM\n";
      return 0;
    }
    if(map2.find(x.first)->second != x.second){
      cout << "NO ANAGRAM\n";
      return 0;
    }
  }

  cout << "ANAGRAM\n";
  int count = 0;
  for(int i = 0; i < 26; i++){
    char temp = 'A' + i;
    if(map1.find(temp) != map1.end()){
      cout << temp << ":" << map1.find(temp)->second << endl;
      count++;
    }
    if(count >= map1.size()){
      return 0;
    }
  }
  return 0;
}
