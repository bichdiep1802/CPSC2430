//
//  hashTable.h
//  P5
//
//  Created by Bich Diep on 11/21/14.
//  Copyright (c) 2014 Bich Diep. All rights reserved.
//

#ifndef __P5__hashTable__
#define __P5__hashTable__

#include <stdio.h>
#include <string>
#include <stack>

using namespace std;

struct Node{
    string word;
    unsigned count;
    Node* next;

    Node() {
        count = 0;
        next = NULL;
    }
    Node(string w) {
        word = w;
        count = 1;
        next = NULL;
    }

    unsigned getCount() {
        return count;
    }

    Node* getNext() {
        return next;
    }

    string getWord() {
        return word;
    }

    void setCount(int c) {
        count = c;
    }
};



class hashTable {

public:
    hashTable();
    hashTable(unsigned size);
    ~hashTable();

    void insert(string data); // insert they data to hash table
    bool contain(string key);
    int get(string key);
    int getTotalElements();
    int getMaxFrequency();
    Node* getComposite(string key);
    Node** getTable();



private:
    unsigned size; // how many indexes
    Node** table;
    int totalElements;
    int maxFre;


    void createTable();
    void deleteTable();
    void deleteList(Node* &head);
    int hash(string entry);
    Node* search(string key, Node* &curr); // return the node storing the key if found, or return null

    

};


#endif /* defined(__P5__hashTable__) */
