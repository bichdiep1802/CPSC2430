//  Bich Diep
//  unfairQ.h
//  11.06.14
//
//

#ifndef ____unfairQ__
#define ____unfairQ__

#include <fstream>
#include <stdio.h>

using namespace std;


class unfairQ {
    struct Element{
        int data;
        unsigned age;
        Element() {
            data = 0;
            age = 0;
        }
        Element(int d) {
            data = d;
            age = 0;
        }
    };
private:
    unsigned size;
    unsigned capacity;
    unsigned countCycle; // for keeping track of how many times removeMax() has been called
    Element* A;


    void copyObject(const unfairQ &other);
    void resize();
    void heapifyUp(unsigned index);
    void heapifyDown(unsigned index);
    void swap(unsigned index, unsigned parent);
    int left(unsigned index);
    int right(unsigned index);
    bool isEmpty();
    int getMax(unsigned index1, unsigned index2);
    void increaseAgeOfOdd();

public:
    unfairQ();
    ~unfairQ();
    unfairQ(const unfairQ &other);
    void operator =(const unfairQ &other);
    void insert(int n);
    int removeMax();
    int max();
    void print(ofstream &output);
    void print();

};

#endif /* defined(____unfairQ__) */
