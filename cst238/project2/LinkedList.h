/**
This is base code for Project 2 for CST238 Fall 2020
It does not need to be modified or turned in
*/
#include<iostream>
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class Node;

class LinkedList {
public:
    LinkedList();
    LinkedList(const LinkedList & source);
    ~LinkedList();
    LinkedList & operator=(const LinkedList & source);
    Node * getFirst() const { return myFirst; };
    bool empty() const;
    bool insertAfter(int oldData, int newData);
    bool remove(int oldData);
    void append(int data);
    void display() const;
    bool search(int data) const;
private:
    Node * myFirst;
};

class Node {
public:
    Node();
    Node(int data);
    Node(const Node & source);
    ~Node();
    Node * getNext() const { return myNext; };
    bool hasNext() const;
    void append(int data);
    bool insertAfter(int oldData, int newData);
    bool removeNext(int data);
    int getData () const { return myData; };
    void display() const;
    bool search(int data) const;
    friend bool LinkedList::remove(int oldData);
private:
    int myData;
    Node * myNext;
    void setNext(Node * next);
};

#endif