/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw3_1.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw3_1.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, ID, Name, and Date.
/*
 * Title: main_hw3_1.cpp
 * Abstract: Take in directed graph data and display all the edges sorted by starting vertice
 * ID: 4902
 * Name: Bailey Miller
 * Date: 02/11/2023
 */

#include <iostream>
#include <unordered_map>
using namespace std;

int main(){
  unordered_map<int, string> directions;
  int vertices; //units per row
  int edges; // rows
  cin >> vertices >> edges;
  
  for(int i = 0; i < edges; i++){
    int startingV;
    string endingV, cost;
    cin >> startingV >> endingV >> cost;
    string temp = "->" + endingV + "," + cost;
    if(directions.find(startingV) == directions.end()){ //if key is not in unordered map
      directions.insert(make_pair(startingV, temp));
    }else{
      if(directions.at(startingV)[2] < temp[2]){
        directions.at(startingV) = directions.at(startingV) + temp;
      }else{
        directions.at(startingV) = temp + directions.at(startingV);
      }
    }
  }

  unordered_map<string, double>::iterator itr;
  for(int i = 0; i < vertices; i++){
    cout << i;
    if(directions.find(i) == directions.end()){
      cout << endl;
      continue;
    }else{
      cout << directions.at(i) << endl;
    }
  }
  
  return 0;
}

