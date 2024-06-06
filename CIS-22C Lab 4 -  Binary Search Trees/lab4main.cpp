/* CIS-22C
*  Lab 4 - Binary Search Trees
*  Spencer Bledsoe
*/

#include "Currency.h"
#include "Dollar.h"
#include "BST_ADT.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

void Welcome();
void Goodbye();
void printMenu();



int main() {

    const string fileName = "file.txt";

    char userInput = NULL;
    double inputVal = NULL;
    Currency* newObj;
    Currency* tempObj;
    BSTNode* currNode;


    Welcome();

    const int arrSize = 20;
    double initValArr[arrSize] = {
    57.12,    //Index 0
    23.44,    //Index 1
    87.43,    //Index 2
    68.99,    //Index 3
    111.22,   //Index 4
    44.55,    //Index 5
    77.77,    //Index 6
    18.36,    //Index 7
    543.21,   //Index 8
    20.21,    //Index 9
    345.67,   //Index 10
    36.18,    //Index 11
    48.48,    //Index 12
    101.00,   //Index 13
    11.00,    //Index 14
    21.00,    //Index 15
    51.00,    //Index 16
    1.00,     //Index 17
    251.00,   //Index 18
    151.00 }; //Index 19

    Currency* currArray[arrSize];
    for (int i = 0; i < arrSize; i++) {
        currArray[i] = new Dollar(initValArr[i]);
    }

    // Create output file to write program output.
    ofstream outFile;
    outFile.open(fileName, ios::trunc);
    if (!outFile.is_open()) {
        cout << "Error: Output file unable to open." << endl;
        system("Pause");
        return -1;
    }
    BST_ADT* BSTree = new BST_ADT();
    for (int i = 0; i < arrSize; i++) {
       BSTree->insert(*currArray[i]);
    }
    
    ///////////////////////////// Perform traversal operations //////////////////////////////////////////////////////

    outFile << "Breadth-first traversal: " << BSTree->breadthFirst() << endl;
    outFile << "In-order traversal: " << BSTree->inOrder() << endl;
    outFile << "Pre-order traversal: " << BSTree->preOrder() << endl;
    outFile << "Post-order traversal: " << BSTree->postOrder() << endl;
    BSTree->print();

    // Provide interactivity for the user to add/search/delete nodes from the console after the data has been seeded into the application.
        // input data validation when reading data from the user into the tree 
        // - if any data item is invalid, ignore the data item and continue to next item but print a message to output (both screen and same output file) to indicate which data items were ignored.


    while (userInput != 'q') {

        printMenu();

        cin >> userInput;

        if (userInput != 'q') {
            switch (userInput) {
            case '1':
                cout << "\nWhat Currency value would you like to add to the BST?: ";
                cin >> inputVal;
                newObj = new Dollar(inputVal);
                if (BSTree->search(*newObj) == NULL) {
                    BSTree->insert(*newObj);
                }
                else {
                    delete newObj;
                }
                break;
            case '2':
                cout << "\nWhat Currency value would you like to search for?: ";
                cin >> inputVal;
                newObj = new Dollar(inputVal);
                currNode = BSTree->search(*newObj);
                if (currNode != NULL) { 
                    cout << "Currency object ";
                    currNode->data->print();
                    cout << " exists in the tree.\n";
                }
                else {
                    cout << "Currency object ";
                    newObj->print();
                    cout << " does not exist in the tree.\n";
                }
                delete newObj;
                break;
            case '3':
                cout << "\nWhat Currency value would you like to remove from the BST?: ";
                cin >> inputVal;
                newObj = new Dollar(inputVal);
                BSTree->remove(*newObj);
                delete newObj;
                break;
            default:
                cout << "\nInvalid input. Please try again.\n";
            }
        }

    }

    cout << "\nWould you like to print the traversal output? Y or N. Enter 'N' to exit the program without printing: ";
    cin >> userInput;
    if (userInput == 'Y' || userInput == 'y') {
        BSTree->print();
        outFile << "Breadth-first traversal: " << BSTree->breadthFirst() << endl;
        outFile << "In-order traversal: " << BSTree->inOrder() << endl;
        outFile << "Pre-order traversal: " << BSTree->preOrder() << endl;
        outFile << "Post-order traversal: " << BSTree->postOrder() << endl;
    }
    // Provide the user the option to print output of traversals or exit the program.
    // Once the user selects the option to print data or exits the program, 
    // - the data in the BST should be printed out to both screen and output file in all four traversal methods in the specific sequence of breadth-first, in-order, pre-order, post-order. 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    outFile.close();
    
    delete BSTree;


    for (int i = 0; i < arrSize; i++) {
        delete currArray[i];
    }
    
    Goodbye();
    system("Pause");
	return 0;
}

void Welcome() {
    cout << "Lab 4 - Binary Search Trees\n" << "Solution by Spencer Bledsoe\n" << endl;
    return;
}

void Goodbye() {
    cout << "\nExiting program..." << endl;
    return;
}

void printMenu() {
    cout << "To Exit the program, enter 'q'. \n";
    cout << "Otherwise: \n";
    cout << "Enter 1 to add a node.\n";
    cout << "Enter 2 to search for a node.\n";
    cout << "Enter 3 to delete a node.\n\n";
    cout << "Please enter your selection: ";

    return;
}