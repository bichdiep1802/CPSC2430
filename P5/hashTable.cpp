//  Bich Diep
//  hashTable.cpp
//  P5
//  11.21.14
//  Copyright (c) 2014 Bich Diep. All rights reserved.
//  supports the standard hashTable operations, defines an appropriate hash function,
//  and resolves collisions effectively and efficiently

#include "hashTable.h"
#include <iostream>
#include <string>



hashTable:: hashTable() {
    size = 11863;
    maxFre = 0;
    totalElements = 0;
    table = new Node*[size];
    createTable();

}


hashTable:: hashTable(unsigned s) {
    size = s;
    table = new Node*[size];
    createTable();

}


hashTable:: ~hashTable() {
    deleteTable();
}


/***********************************************************************/
/***************************** MAIN METHODS  ***************************/
/***********************************************************************/

/*
 * Insert key into the table
 * If collision happens, put to the linked list
 */
void hashTable::insert(string key){

    int index = hash(key);

    Node* curr = table[index];
    Node* newE = new Node(key);

        // search the data to check if it's in list at the index
    if(search(key, curr)) {
        curr->count++;
        if(curr->count > maxFre) maxFre = curr->count;
    }
    else {
        newE->next = table[index];
        table[index] = newE;
        totalElements++;
    }

}


/*
 * Check if table contain a given key
 */
bool hashTable::contain(string key) {

    unsigned int index = hash(key);

    return search(key, table[index]) != NULL;

}

/*
 * Return a copy of composites associated to a given key
 */
Node* hashTable:: getComposite(string key){
    unsigned long index = hash(key);
    return table[index];
}


/*
 * Return the frequency associate with the key
 */
int hashTable:: get(string key){

    unsigned long index = hash(key);
    Node* temp = table[index];
    temp = search(key, temp);

    if(temp) return temp->getCount();
    return -1;
}


/*
 * Return the total number of composites of the table
 */
int hashTable::getTotalElements(){
    return totalElements;
}

/*
 * Return a copy of this hash table
 */
Node** hashTable:: getTable() {
    return table;
}

/*
 * Return the max frequency
 */
int hashTable:: getMaxFrequency() {
    return maxFre;
}

/***********************************************************************/
/***************************** HELPER METHODS  ***************************/
/***********************************************************************/

/*
 * Delete hash table
 */
void hashTable::deleteTable() {

    for(int i = 0; i < size; i++)
        deleteList(table[i]);
    delete[] table;


}

/*
 * Delete all the composites of this key
 */
void hashTable::deleteList(Node* &head) {

    while(head != NULL)
    {
        Node* next = head->next;
        delete head;
        head = next;
    }
}


/*
 * Create an empty hash table
 */
void hashTable::createTable(){
    for(int i = 0; i < size; i++) {
        table[i] = NULL;
    }
}


/*
 * a hash function to locatate the index of the key
 */
int hashTable::hash(string key){

    unsigned long hash = size;
    char c;

    for(int i=0; i<key.size(); i++){
        c=key[i]<< 3;
        hash = (hash<<11)^(hash>>57)^c;
    }
    return hash % size;


}

/*
 * Return the current position of a given key
 * If key not found, return NULL
 * Pass by reference the move the pointer to the node storing the key (using for insert)
 */
Node* hashTable::search(string key, Node* &head){

    while(head) {
        // compare the key and the current elements
        if(head->word.compare(key) == 0) {
            return head;

        }
        // move on to the next node if key not found
        head = head->next;
    }

    // return NULL if word not found
    return head;
}

