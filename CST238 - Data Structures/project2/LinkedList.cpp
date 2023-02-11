/* Title: project-02.cpp* 
Abstract:
Author: Bailey Miller
Email: baimiller@csumb.edu
Estimate: 6 hours
Date: 12/06/2021 */
/**
This is base code for Project 2 for CST238 Fall 2020
This file DOES need to be modified and handed in
ONLY RECURSION can be used; any iteration will result
in a zero for the assignment
*/
#include <iostream>
#include "LinkedList.h"
using namespace std;

//==================================================================================
// class LinkedList {
// public:
//     LinkedList();
//     LinkedList(const LinkedList & source);
//     ~LinkedList();
//     LinkedList & operator=(const LinkedList & source);
//     Node * getFirst() const { return myFirst; };
//     bool empty() const;
//     bool insertAfter(int oldData, int newData);
//     bool remove(int oldData);
//     void append(int data);
//     void display() const;
//     bool search(int data) const;
// private:
//     Node * myFirst;
// };

// class Node {
// public:
//     Node();
//     Node(int data);
//     Node(const Node & source);
//     ~Node();
//     Node * getNext() const { return myNext; };
//     bool hasNext() const;
//     void append(int data);
//     bool insertAfter(int oldData, int newData);
//     bool removeNext(int data);
//     int getData () const { return myData; };
//     void display() const;
//     bool search(int data) const;
//     friend bool LinkedList::remove(int oldData);
// private:
//     int myData;
//     Node * myNext;
//     void setNext(Node * next);
// };
//==================================================================================


/**
* Implement these functions IN ORDER
*/

// implement these two first
bool Node::hasNext() const {
    return myNext != nullptr;
}

bool LinkedList::empty() const {
    return myFirst == nullptr;
}

// then these two
void Node::display() const {
  cout << "\n\tData: " << myData << "\nNext Node: ";
  if(myNext == nullptr){
    cout << "None\n";
    return;
  }else{
    myNext->display();
  }
}

void LinkedList::display() const {
    if(empty()){
      cout << "Empty!" << endl;
    }else{
      cout << "My First";
      myFirst->display();
    }
}

// then these two
// only append if this is the last node
// otherwise, recurse
void Node::append(int data) {
    if(myNext == nullptr){
      myNext = new Node(data);
    }else{
      myNext->append(data);
    }
}

void LinkedList::append(int data) {
    // this won't work after the first time!
    if(myFirst == nullptr){
      myFirst = new Node(data);
    }else{
      myFirst->append(data);
    }
}

// then these two
bool Node::search(int data) const {
    if(myData == data){
      return true;
    }else if(myNext == nullptr){
      return false;
    }else{
      return myNext->search(data);
    }
}

bool LinkedList::search(int data) const {
    if(myFirst == nullptr){
      return false;
    }else{
      return myFirst->search(data);
    }
}

// then these two
bool Node::insertAfter(int oldData, int newData) {
    if(myData == oldData){
      Node * temp = myNext;
      Node * newNode = new Node(newData);
      newNode->setNext(temp);
      myNext = newNode;
      return true;
    }else if(myNext == nullptr){
      return false;
    }else{
      return myNext->insertAfter(oldData, newData);
    }
}

bool LinkedList::insertAfter(int oldData, int newData) {
    if(empty()){
      return false;
    }else{
      return myFirst->insertAfter(oldData, newData);
    }
}

// then these two
bool Node::removeNext(int data) {
    if(myNext == nullptr){
      return false;
    }else if(myNext->getData() == data){
      Node * temp = myNext->getNext();
      myNext = temp;
      return true;
    }else{
      return myNext->removeNext(data);
    }
}

bool LinkedList::remove(int data) {
    if(empty()){
      return false;
    }else if(myFirst->getData() == data){
      Node * temp = myFirst->getNext()->getNext();
      myFirst->myData = myFirst->getNext()->getData();
      myFirst->setNext(temp);
      return true;
    }else{
      return myFirst->removeNext(data);
    }
}

// then these two
Node::~Node() {
  if(myNext != nullptr){
    delete myNext;
  }
}

LinkedList::~LinkedList() {
  delete myFirst;
}

// then these two
Node::Node(const Node & source) {
  if(source.myNext == nullptr){
    myData = source.myData;
  }else{
    myData = source.myData;
    myNext = new Node(source.myNext->getData());
  }
}

LinkedList::LinkedList(const LinkedList & source) {
  if(source.myFirst == nullptr){
    return;
  }else{
    myFirst = new Node(source.myFirst->getData());
    myFirst->append(source.myFirst->getNext()->getData());
  }
}

// then this one
LinkedList &LinkedList::operator=(const LinkedList & source) {
    if(myFirst == source.myFirst){
      cerr << "Can not self assign\n";
      return * this;
    }
    myFirst = new Node(source.myFirst->getData());
    if(source.myFirst->hasNext()){
      myFirst->append(source.myFirst->getNext()->getData());
    }
    return * this;
}

/**
* Implement the functions above, shouldn't need to change anything below,
but look at this for good examples!
*/

Node::Node(int data) {
    myData = data;
}

void Node::setNext(Node * next) {
    myNext = next;
}

LinkedList::LinkedList() {
    myFirst = nullptr; 
}

