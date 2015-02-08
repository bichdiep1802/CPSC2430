/**
 *
 *  Created by Bich Diep on 11/21/14.
 *  P5.cpp
 *
 *  Copyright (c) 2014 Bich Diep. All rights reserved.
 *  supports the standard hashTable operations, defines an appropriate hash function,
 *  and resolves collisions effectively and efficiently
 *  Reading line by line, word by word, and removing all special characters in the words
 *  or seperate phrase into 2 words if needed. Then insert to the hash table
 *  In order to find N most frequent words
 *      - Dump all the content of hash table
 *      - Having another hash table that store all the composites of the hash table
 *          + size of this hash table = max frequency
 *          + hashFunction of the 2nd hash table is the frequency of the words
 *      - Finding N most frequent words
 *          + Looping the table starting from the bottom
 *          + Getting all the words until reaching 25 words.
 *
 */


#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

#include "hashTable.h"

using namespace std;


int checkAndRemoveSpecialChar(string &s);
int createTable(hashTable &table);
int createTable(hashTable &table);
string* mostFrequentWords(int num, Node** table1, int length, int tableSize);


/**
 * CHECK AND REMOVE SPECIAL CHARACTERS METHOD
 *
 * Return -1 if the word is valid
 * Return index where non alphabet char occurs
 * ASSUMPTION:
 *      This function only deal with non alphabet in the string
 * by removing all non-alphabet chars and punctuations and quotation marks or symbols --
 *      Plural and single words are different.
 *      All strings are converted to lowercase
 *  Therefore, there would be some miss frequency due to other case that's needed to be solved with string
 * RETURN:
 *      -2 means short word ( length < 5)
 *      -1 means a valid word
 *      i means index where non-alphabet occurs
 *
 */
int checkAndRemoveSpecialChar(string &s) {

    if(s.length() < 5) return -2; // short word

    // erase the top and bottom chars if it's not alphabet
    while (s.length() > 0 && !isalpha(s[0]))
        s.erase(0,1);
    while (s.length() > 0 && !isalpha(s[s.length() - 1]))
        s.erase(s.length() - 1);


    for(int i =0; i < s.length(); i++) {
        // make the word to lowercase
        s[i] = tolower(s[i]);
    }

    char chars[] = "'";

    if(s.length() < 5) return -2; // short word after removing special chars

    // Check if this string is not a word
    // Return the index of the char where non-alphabet occur
    // In case of abc--abc and abc-abc
    for(int i =0; i < s.length()-1; i++) {
        if (!isalpha(s[i])) {
            if(s[i] == chars[0] && s[i+1] == 's') { // case of form abc's
                s.erase(i,2);
            }
            else
                return i;
        }
    }

    return -1; // -1 means true

}


/**
 * Create a table and fill the hash table with distinct words (non numberic) from the book
 */
int createTable(hashTable &table) {

    ifstream inFile("2600.txt");
    string word;
    unsigned count =0; // count total words in the book

    if (!inFile) {
        cout << "Failed to open the file" << endl;
        return 0;
    }

    // check through each line and get individual strings
    for(string line; getline(inFile, line);) {

        istringstream is(line);
        while(is >> word) {
            count++;

            // getting the index where the word fail in checking and remove special words
            int failAtIndex = checkAndRemoveSpecialChar(word);

            // if length of wod > 4
            if(failAtIndex != -2) {
                // if this is a word , or a word that has the form abc-abc, ex: ill-suited
                if( (failAtIndex < 0 || word[failAtIndex+1] != '-'))
                    table.insert(word);
                else {
                    // case string has abcd--efgh:
                    // ex: triviality--these: seperate to 2 words: triviality and these
                    //string1: abcd
                    string s1 = word.substr(0,failAtIndex);
                    // string2: efgh
                    string s2 = word.substr(failAtIndex+2, word.length()-s1.length()-2);

                    // insert only if length > 4
                    if (s1.length() >4)
                        table.insert(s1);
                    if (s2.length() >4)
                        table.insert(s2);

                }
            }
        }
    }

    inFile.close();

    return count;
}


/*
 * Get N most frequent words Method
 *
 */
string* mostFrequentWords(int num, Node** table1, int length, int tableSize) {

    Node**  allComposites = new Node*[length];

    int countKey = 0; // count how many key in total

    /*********************** Loop through each key ***********************/
    for (int i = 0; i < tableSize; i ++) {
        // getting key
        Node* curr = table1[i];

        if(curr) {
            countKey++;

            // loop through its associated composites
            while(curr) {
                // index of the composite array = its frequency
                int index = curr->getCount();

                Node* newE = new Node(curr->word);
                newE->setCount(curr->count);

                // if there's composites exisiting in the index, link to the list at this index
                // meaning there are more than words that have the same frequency
                if(allComposites[index]) {
                    newE->next = allComposites[index];
                    allComposites[index] = newE;
                }else
                    allComposites[index] = newE;

                curr = curr->next;
            }
        }
    }


    /************** Finding and store most frequent words *****************/
    string* result = new string[num];

    int count = 0;

    // Loop from the bottom (highest frequency) to the top
    // Stop when reaching n most frequent words
    for(int i = length-1; i >=0 && count < num; i--) {
        if(allComposites[i]) {
            Node* curr = allComposites[i];

            // if there're more than 1 words with the same frequency
            while(curr && count < num) {
                result[count++] = curr->getWord();

                curr = curr->next;
            }
        }
    }

    cout<< countKey << " total keys" << endl<<endl;


    return result;

}



int main() {

    clock_t begin=clock(); // using timing to find elapse time

    int size = 11987; // Size of the hash table

    ofstream output("P5Output.txt");

    cout << "Start creating an empty hash table..." << endl;
    output << "Start creating an empty hash table..." << endl;
    hashTable table(size);

    cout << "Start filling hash table..." << endl;
    output << "Start filling hash table..." << endl;
    int wordsInBook = createTable(table);

    // If file cannot open
    if(wordsInBook == 0)
        return 0;


    /***********************************************************************/
    /*********************** Get N most frequent words ***********************/
    /***********************************************************************/
    int n = 25;
    cout << "Start finding " << n << " most frequent words..." << endl << endl;
    output << "Start finding " << n << " most frequent words..." << endl << endl;


    /******************* Statistic  **************************/
    cout << "/*********** Statistic  ***************/" << endl;
    cout<< wordsInBook << " total words from the books" << endl;
    cout<< table.getTotalElements() << " total unique words stored in hash table" << endl;
    //    cout<< endl << endl;


    // Output file
    output << "/*********** Statistic  ***************/" << endl;
    output<< wordsInBook << " total words from the books" << endl;
    output<< table.getTotalElements() << " total unique words stored in hash table" << endl;
    //    output<< endl << endl;



    /******************* Print out list of most frequent words **************************/

    string* result = mostFrequentWords(n, table.getTable(), table.getMaxFrequency()+1, size);

    cout << "List of " << n << " most frequent words: " <<endl;
    output << "List of " << n << " most frequent words: " <<endl;

    for(int i = 0; i < n; i++) {
        cout << "<" << result[i] << ", " << table.get(result[i]) << ">" <<endl;
        output << "<" << result[i] << ", " << table.get(result[i]) << ">" <<endl;
        
    }
    cout<< endl << endl;
    output<< endl << endl;

    
    /******************* Finding total elapse time **************************/
    clock_t end=clock();
    float diffticks=end-begin;
    float ms=diffticks/CLOCKS_PER_SEC;
    
    cout << "It tooks " << ms << " seconds." << endl;
    output << "It tooks " << ms << " seconds." << endl;
    
    
    output.close();
    
}