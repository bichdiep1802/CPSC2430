//  Bich Diep
//  P4.cpp
//  11.06.14
//  Purpose: Read an input file. Create an object type of unfairQ.
//  Insert elements from odd lines
//  Remove elements from the list with the number of times given in the even lines
//  Write output to P4OutPut.txt

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "unfairQ.h"

using namespace std;


/*
 * Generate random numbers method for odd lines
 * Odd lines contain lists of numbers to enQ
 *
 */
void generateOddLines(ofstream &write) {

    unsigned n = rand() % 15+2;

    for (unsigned i = 0; i < n; i++){
        int x = rand() % 100 + 1;
        write << x << " ";
    }
    write << endl;
}

/*
 * Reading the numbers from the line and insert to unfairQ
 *
 */
void processInserting(unfairQ &heap, istringstream &is, ofstream &output) {
    int value;

    while( is >> value )
        heap.insert(value);

    cout << "---------------------------------------------------" << endl;
    cout << "New items added" << endl;
    heap.print();

    output << "---------------------------------------------------" << endl;
    output << "New items added" << endl;
    heap.print(output);

}

/*
 * Reading the single number from the line and remove unfairQ with those times
 *
 */
void processRemoving(unfairQ &heap, istringstream &is, ofstream &output) {
    int value;

    while(is >> value) {
        cout << "Remove max " << value << " times" << endl;
        output << "Remove max " << value << " times" << endl;


        for (unsigned i =0; i< value; i++ ){
            int max = heap.removeMax();
            if (max!=-1) {
                cout << max  << " is removed" << endl;
                heap.print();

                output << max  << " is removed" << endl;
                heap.print(output);

            }
            else {
                cout<< "Empty list. No item left to remove"<<endl;
                output<< "Empty list. No item left to remove"<<endl;
                break;
            }
        }
    }
}

/*
 * Generate even lines for numbers of dequeue
 */
void generateEvenLines(ofstream &write) {
    write << rand() % 10+5<<endl;
}


int main()
{
    // Initialize variables
    int count = 1;
    unfairQ heap;

    /**************************************************************/
    /************** GENERATING INPUT AND OUTPUT FILES *************/
    /**************************************************************/


    ofstream inputFile("P4Input.txt");
    unsigned n = rand() % 15;

    for (unsigned i = 0; i < n; i++) {
        generateOddLines(inputFile);
        generateEvenLines(inputFile);
    }


    inputFile.close();

    // Open input and output files
    ifstream input("P4Input.txt");
    ofstream output("P4Output.txt");

    if(!input) {
        cout<<"Invalid input file"<<endl;
        exit(1);
    }

    if(!output) {
        cout<<"Invalid output file"<<endl;
        exit(1);
    }

    /**************************************************************/
    /********** START WORKING ON INSERTING AND REMOVING ***********/
    /**************************************************************/

    for (string line; getline(input, line); count++) {
        istringstream is(line);

        // GETTING AND INSERTING INPUTS TO THE HEAP
        // odd lines - include a list of numbers to enQ
        if(count %2 !=0) {
            processInserting(heap, is, output);
        }

        // REMOVING
        // even lines - include numbers of deQ
        else {
            processRemoving(heap, is, output);
        }
    }

    /**************************************************************/
    /**************************** CLOSING *************************/
    /**************************************************************/

    // Close the file
    input.close();
    // Close the file
    output.close();

    return 0;
}


