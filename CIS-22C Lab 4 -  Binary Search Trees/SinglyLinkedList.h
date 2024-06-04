/* CIS-22C
*  Lab 4
*  Spencer Bledsoe
*/
#pragma once
#include "LinkNode.h"
#include <string>
#include <sstream>
#include <stdexcept>

class SinglyLinkedList {
protected:
	int count;
	LinkNode* start;
	LinkNode* end;

public:
	SinglyLinkedList() {
		count = 0;
		start = NULL;
		end = NULL;
	}

	~SinglyLinkedList() {
		while (start != NULL) {
			LinkNode* iterator = start;
			start = start->next;
			delete iterator;
		}
	}

	//Getters
	/*Pre: Member variables must be initialized.
	Post: returns corresponding member variable value.
	*/
	int getCount() const { return count; }
	LinkNode* getStart() const { return start; } //Check this logic, or if these are needed at all
	LinkNode* getEnd() const { return end; } //Check this logic
	int countCurrency() const {
		int counter = 0;
		if (start != NULL) {
			LinkNode* iterator = start;
			while (iterator->next != NULL) {
				iterator = iterator->next;
				counter++;
			}
		}
		return counter;
	}

	//Setters
	/*Pre: input parameters must not be null
	Post: Sets corresponding member variable to new(Val)
	*/
	void setCount(int newCount) { count = newCount; }
	void setStart(LinkNode* newStart) { start = newStart; }
	void setEnd(LinkNode* newEnd) { end = newEnd; }

	//addCurrency method which takes a Currency object and a node index value as parameters to add the Currency to the list at that index.
	void addCurrency(Currency& currObj, int index) {
		/*Pre: Index param must be valid. currObj must not be NULL.
		*Post: Adds LinkNode containing the target Currency object to the LinkedList.
		*/
		try {
			if (&currObj == NULL) {
				throw std::invalid_argument("addCurrency() called on invalid Currency object.");
			}

			if (index < 0 || index > count) {
				throw std::invalid_argument("addCurrency() called with invalid index.");
			}

			//Case 1: First Node Insert
			if (index == 0) {
				if (start == NULL) { //  (Empty List) Count == 0
					start = new LinkNode();
					start->data = &currObj;
					end = start;
				}
				else {
					LinkNode* newNode = new LinkNode(); // Count > 0
					newNode->next = start;
					start = newNode;
					start->data = &currObj;
				}
			}
			//Case 2: Insert End Node
			else if (index == count) {
				end->next = new LinkNode();
				end = end->next;
				end->next = NULL;
				end->data = &currObj;
			}
			//Case 3: Insert into Middle of List
			else {
				LinkNode* iterator = start;
				for (int i = 0; i < index - 1; i++) {
					iterator = iterator->next;
				}

				LinkNode* newNode = new LinkNode();
				newNode->next = iterator->next;
				iterator->next = newNode;
				newNode->data = &currObj;
			}
			count++;
			return;
		}

		catch (std::invalid_argument& excpt) {
			std::cout << "Error: " << excpt.what() << std::endl;
			return;
		}

	}

	Currency* removeCurrency(Currency& currObj) {
		/*Pre: LinkedList must not be empty. currObj must not be NULL.
		*Post: Removes LinkNode containing the target Currency object and returns a copy of the Currency object if present.
		*/
		try {

			if (count == 0) {
				throw std::runtime_error("removeCurrency() called on empty list.");
			}

			//Case 1: Remove list head node
			int index = findCurrency(currObj);

			if (index == -1) {
				throw std::invalid_argument("removeCurrency() called on non-existent Currency Object.");
			}

			return removeCurrency(index);
		}

		catch (std::runtime_error& excpt) {
			std::cout << "Error: " << excpt.what() << std::endl;
			return NULL;
		}
		catch (std::invalid_argument& excpt) {
			std::cout << "Error: " << excpt.what() << std::endl;
			return NULL;
		}

	}

	Currency* removeCurrency(int index) {
		/*Pre: LinkedList must not be empty. index param must be valid.
		Post:  Removes the node at the specified index and returns the currency object within.
		*/
		try {
			if (index >= count || index < 0 || index == NULL) {
				throw std::invalid_argument("removeCurrency() called with invalid index.");
			}

			LinkNode* currNode = NULL;
			Currency* currObj = NULL;

			//Case 1: Remove list start node
			if (index == 0) {
				currNode = start;
				currObj = start->data;
				start = start->next;
				if (start == NULL) { // If the last node has been removed, update "end" pointer.
					end = NULL;
				}
			}

			//Case 2: Remove after start node
			else {
				LinkNode* iterator = start;
				for (int i = 0; i < index - 1; i++) {
					iterator = iterator->next;
				}

				currNode = iterator->next;
				currObj = currNode->data;

				if (currNode == end) { // If the end node is being removed...
					end = iterator;
					iterator->next = NULL;
				}

				else {
					iterator->next = currNode->next;
				}
			}
			delete currNode;
			count--;
			return currObj;
		}

		catch (std::invalid_argument& excpt) {
			std::cout << "Error: " << excpt.what() << std::endl;
			return NULL;
		}

	}

	const int findCurrency(Currency& currObj) {
		/*Pre: currObj must not be NULL. List must not be empty.
		Post:  Returns a string signifying the contents of the List from start to end, tab spaced.
		*/
		try {
			if (&currObj == NULL) {
				throw std::invalid_argument("findCurrency() called with invalid Currency Object.");
			}

			int index = 0;
			if (count > 0) {
				LinkNode* iterator = start;
				while (iterator != NULL) {
					if (*(iterator->data) == currObj) {
						return index;
					}
					index++;
					iterator = iterator->next;
				}
			}
			return -1; // Currency object not found
		}

		catch (std::invalid_argument& excpt) {
			std::cout << "Error: " << excpt.what() << std::endl;
			return -1;
		}

	}

	Currency* getCurrency(int index) {
		/*Pre: index param must be valid. List must not be empty.
		Post:  Returns a string signifying the contents of the List from start to end, tab spaced.
		*/
		try {
			if (index >= count || index < 0 || index == NULL) {
				throw std::invalid_argument("getCurrency() called with invalid index.");
			}

			LinkNode* iterator = start;

			for (int i = 0; i < index; i++) {
				iterator = iterator->next;
			}

			return iterator->data;
		}

		catch (std::invalid_argument& excpt) {
			std::cout << "Error: " << excpt.what() << std::endl;
			return NULL;
		}
	}

	std::string printList() {
		/*Pre: List must not be empty.
		Post:  Returns a string signifying the contents of the List from start to end, tab spaced.
		*/

		try {
			if (count == 0) {
				throw std::runtime_error("printList() called on empty list.");
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

	const bool isListEmpty() {
		if (count == 0) {
			return true;
		}
		else {
			return false;
		}
	}

};