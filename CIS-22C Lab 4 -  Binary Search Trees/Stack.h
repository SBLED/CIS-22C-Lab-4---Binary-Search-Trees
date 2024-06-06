/* CIS-22C
*  Lab 4
*  Spencer Bledsoe
*/
#pragma once
#include "SinglyLinkedList.h"
class Stack : public SinglyLinkedList {
public:

	void push(Currency& currObj) {
		/*Pre: Input param must not be NULL
		Post: Adds a new currency object to the top of the stack.
		*/

		//Case 1: Empty Stack
		if (start == NULL) {
			start = new LinkNode();
		}

		//Case 2: >0 Objects in stack
		else {
			LinkNode* newNode = new LinkNode();
			newNode->next = start;
			start = newNode;
		}

		start->data = &currObj;
		count++;
		return;
	}

	Currency* pop() {
		/*Pre: Stack must not be empty.
		Post: Removes and returns the currency object from the top of the stack.
		*/
		try {

			if (start != NULL) {
				Currency* topData = start->data;
				LinkNode* currNode = start;
				start = start->next;
				delete currNode;
				count--;
				return topData;
			}

			else {
				throw std::runtime_error("pop() called on empty stack.");
			}

		}

		catch (std::runtime_error& excpt) {
			std::cout << "Error: " << excpt.what() << std::endl;
			return NULL;
		}
	}

	Currency* peek() {
		/*Pre: Stack must not be empty.
		Post: Returns a copy of the Currency object at the top of the stack.
		*/

		if (start != NULL) {
			return start->data;
		}

		else {
			return NULL;
		}
	}

	std::string printStack() {
		/*Pre: Stack must not be empty.
		Post:  Returns a string signifying the contents of the stack from top to bottom, tab spaced.
		*/
		try {

			if (count == 0) {
				throw std::runtime_error("printStack() called on empty stack.");
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



};