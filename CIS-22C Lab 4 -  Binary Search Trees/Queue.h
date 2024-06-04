/* CIS-22C
*  Lab 4
*  Spencer Bledsoe
*/
#pragma once
#include "SinglyLinkedList.h"
#include <string>
#include <sstream>
class Queue : public SinglyLinkedList {
public:

    void enqueue(Currency& currObj) {
        /*Pre: Currency object input parameter must not be NULL.
        Post: Adds the currency object input to the end of the queue
        */

        LinkNode* newNode = new LinkNode();
        newNode->data = &currObj;

        if (count == 0) {
            start = newNode;
            end = newNode;
        }

        else {
            end->next = newNode;
            end = newNode;
        }
        count++;
        return;
    }

    Currency* dequeue() {
        /*Pre: Queue must not be empty.
        Post: Returns the currency object from the front of the queue
        */

        try {
            if (count == 0) {
                throw std::runtime_error("No_Such_Element");
            }

            Currency* temp = start->data;
            LinkNode* currNode = start;

            if (count == 1) {
                start = NULL;
                end = NULL;
                count = 0;
            }

            else {
                start = start->next;
                count--;
            }
            delete currNode;
            return temp;
        }
        catch (std::runtime_error& excpt) {
            std::cout << "Error: " << excpt.what() << std::endl;
            return NULL;
        }
    }

    //peekFront which takes no parameter and returns a copy of the Currency object at the front of the queue.
    Currency* peekFront() {
        /*Pre: Queue must not be empty.
        Post: Returns a copy of the Currency object at the front of the queue.
        */

        try {
            if (count == 0) {
                throw std::runtime_error("No_Such_Element");
            }
        }
        catch (std::runtime_error& excpt) {
            std::cout << "Error: " << excpt.what() << std::endl;
        }
        return start->data;
    }
    //peekRear which takes no parameter and returns a copy of the Currency object at the end of the queue.
    Currency* peekRear() {
        /*Pre: Queue must not be empty.
        Post: Returns a copy of the Currency object at the rear of the queue.
        */
        try {
            if (count == 0) {
                throw std::runtime_error("No_Such_Element");
            }
            return end->data;
        }

        catch (std::runtime_error& excpt) {
            std::cout << "Error: " << excpt.what() << std::endl;
            return NULL;
        }
    }

    //printQueue method which returns a string signifying the contents of the queue from front to end, tab spaced.
     /*
     * Returns the values stored in the Queue as a String, separated by a tab space
     * @return a String of Queue values
     */
    std::string printQueue() {
        /*Pre: List must not be empty.
        Post:  Returns a string signifying the contents of the List from start to end, tab spaced.
        */

        try {
            if (count == 0) {
                throw std::runtime_error("printQueue() called on empty list.");
            }

            else {
                std::stringstream ss;
                LinkNode* temp = start;
                while (temp != NULL) {
                    ss << *(temp->data) << "\t";
                    temp = temp->next;
                }
                return ss.str();
            }
        }

        catch (std::runtime_error& excpt) {
            std::cout << "Error: " << excpt.what() << std::endl;
            return NULL;
        }
    }

    bool isEmpty() {
        return count == 0;
    }

};