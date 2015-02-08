//  Bich Diep
//  unfairQ.cpp
//  11.06.14
//

#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "unfairQ.h"
using namespace std;

const unsigned LIMIT = 3;


unfairQ::unfairQ(){
    capacity = 50;
    size = 0;
    countCycle = 0;
    A = new Element[capacity];
}


unfairQ::~unfairQ(){
    delete[] A;
}


unfairQ::unfairQ(const unfairQ &other){
    copyObject(other);
}


void unfairQ::operator=(const unfairQ& other){
    if(this!=&other){;
        delete [] A;
        copyObject(other);
    }
    return;
}


/***********************************************************************/
/***************************** MAIN METHODS  ***************************/
/***********************************************************************/

/**
 * Insert an element to the list
 */
void unfairQ::insert(int newValue){

    if (size == capacity)  resize();

    // increase size and add new element to the end of the list
    A[++size] = Element(newValue);
    // reorganize the list
    heapifyUp(size);

}

/**
 * Remove the max which is located at the first of the list. 
 * also, increase age of odd elements if countCycle reaches the limit
 */
int unfairQ::removeMax(){
    if(isEmpty()) return -1;

    // increase age for each 3 age cycle
    countCycle++;
    if(countCycle ==LIMIT) {
        increaseAgeOfOdd();
        countCycle = 0;
    }

    // swap the first and last elements
    // decrease the size
    int max = A[1].data;
    swap(1, size);
    size--;

    // reorganize the list
    heapifyDown(1);

    return max;
}



/**
 * Output method
 * Print all values currently stored in the output file
 */
void unfairQ::print(ofstream &output){
    for (unsigned i = 1; i<=size; i++)
        output << A[i].data << "(" << A[i].age << ")" << " ";
    output<<endl <<endl;
}

/**
 * Output method
 * Print all values currently stored in the terminal
 */
void unfairQ::print(){
    for (unsigned i = 1; i<=size; i++)
    cout << A[i].data << "(" << A[i].age << ")" << " ";
    cout<<endl <<endl;
}


/***********************************************************************/
/***************************** HELPER METHODS **************************/
/***********************************************************************/


// Deep copy object
void unfairQ::copyObject(const unfairQ &other){
    capacity=other.capacity;
    size=other.size;
    A = new Element[capacity];
    for(unsigned i=1; i<=size; i++){
        A[i]=other.A[i];
    }
}

// Resize method
// Resize the storage
void unfairQ::resize(){
    Element* temp = new Element[capacity*2];
    capacity = capacity*2;
    for(unsigned i=1;i<=size;i++){
        temp[i]=A[i];
    }
    delete[] A; // deallocate the old A
    A = temp;
}

// check if the list is empty
bool unfairQ::isEmpty(){
    return size == 0;
}


// HeapifyUp method
// Start parent of the last element
void unfairQ::heapifyUp(unsigned index){
    unsigned parent = index/2;

    while (parent > 0 && A[index].data > A[parent].data) {
        // swap
        Element temp = A[parent];
        A[parent] = A[index];
        A[index] = temp;

        index = parent;
        parent = parent/2;
    }
}


// HeapifyDown method
// Starting from the first element
void unfairQ::heapifyDown(unsigned index){
    int left;
    int right;

    while ( (left = this->left(index)) <= size ) {
        int max = getMax(left, index);

        right = this->right(index);
        if(right <=size)
            max = getMax(right, max);

        // swap child and parent
        if (index !=max) {
            swap(index, max);
            index = max;
        } else {
            index = size;
        }

    }
}

// return index of left element
int unfairQ::left(unsigned index) {
    return index << 1;
}

// return index of right element
int unfairQ::right(unsigned index) {
    return (index << 1) +1;
}

// find the max element by comparing their sum of data + age
// index1: index of 1st element
// index2: index of 2nd element// return its index
int unfairQ::getMax(unsigned index1, unsigned index2){
    int result = index1;

    if (A[index2].data + A[index2].age > A[index1].data + A[index1].age) {
        result = index2;
    }
    return result;

}

// Swap 2 elements
// index1: index of 1st element
// index2: index of 2nd element
void unfairQ::swap(unsigned index1, unsigned index2) {
    Element temp = A[index1];
    A[index1] = A[index2];
    A[index2] = temp;
}


// Increase age of odd elements
void unfairQ::increaseAgeOfOdd(){
    for (int i =1; i <=size; i++) {
        if(A[i].data % 2 !=0) {
            A[i].age++;
        }
    }
}

