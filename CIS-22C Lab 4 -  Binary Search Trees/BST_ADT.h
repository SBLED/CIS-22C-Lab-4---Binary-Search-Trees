/* CIS-22C
*  Lab 4 - Binary Search Trees
*  Spencer Bledsoe
*/

#pragma once
#include "BSTNode.h"
#include "Queue.h"
#include "Stack.h"
#include <vector>

class BST_ADT {
private:
    int height;
    BSTNode* root;


    std::string breadthFirstTraversal(BSTNode*);
    std::string inOrderTraversal(BSTNode*);
    std::string preOrderTraversal(BSTNode*);
    std::string postOrderTraversal(BSTNode*);

public:

    BST_ADT() {
        height = 0;
        root = NULL;
    }

    ~BST_ADT() {
        while (root != NULL) {
            BSTNode* iterator = root;
            //logic to progress in order traversal deleting each node;
            Stack stack;
            stack.push(*root->data);

            while (!(stack.peek() == NULL)) {
                iterator = search(*stack.peek()); // sets iterator to node containing the top of stack's Currency obj.
                stack.pop();

                if (iterator->left != NULL) {
                    stack.push(*iterator->left->data);
                }

                if (iterator->right != NULL) {
                    stack.push(*iterator->right->data);
                }

                delete iterator;
            }
        }
    }

	BSTNode* search(Currency&);
	void insert(Currency&);
    Currency* remove(Currency&);


    std::string breadthFirst();
    std::string inOrder();
    std::string preOrder();
    std::string postOrder();

    int getHeight(BSTNode*);
    void print();
    int count();
    bool isEmpty();

};

 

BSTNode* BST_ADT::search(Currency& key) {
    /*Pre: key param must be valid. key must not be NULL.
    *Post: Returns the BSTNode containing the key if found. Otherwise returns NULL.
    */

    BSTNode* currNode = this->root;
	 while (currNode != NULL) {
			if(&key == currNode->data) {
                return currNode; //Found
			}

			else if(&key < currNode->data) {
                currNode = currNode->left;
			}

			else {
                currNode = currNode->right;
			}
	}
    return NULL;
}

void BST_ADT::insert(Currency& newCurr) {
    /*Pre: newCurr param must be valid. newCurr must not be NULL.
    *Post: Adds BSTNode containing the target Currency object to the BST_ADT Tree.
    */

    //Create new node named 'node'
    BSTNode* newNode = new BSTNode();
    newNode->data = &newCurr;

	if (root == NULL) {
        root = newNode;
	}
	else {
        BSTNode* currNode;

        currNode = this->root;
		while (currNode != NULL) {

			if(newNode->data < currNode->data) {
				if(currNode->left == NULL) {
                    currNode->left = newNode;
                    currNode = NULL;
				}
				else {
                    currNode = currNode->left;
				}
			}

			else {
				if(currNode->right == NULL) {
                    currNode->right = newNode;
                    currNode = NULL;
				}
				else {
                    currNode = currNode->right;
				}
			}

		}
	}
    return;
}



Currency* BST_ADT::remove(Currency& newData) {
    /*Pre: newData param must be valid. newData must not be NULL. Tree must not be empty.
    *Post: Removes BSTNode containing the target Currency object from the BST_ADT Tree. 
    *Return: Returns removed Currency object.
    */

    BSTNode* parentNode = NULL;
    BSTNode* succNode = NULL;
    BSTNode* currNode = this->root;


    while (currNode != NULL) { // Search for node
      if (currNode->data == &newData) { // Node found 
         if (currNode->left == NULL && currNode->right == NULL) { // Remove leaf
             if (parentNode == NULL) { // Node is root
                 this->root = NULL;
             }
             else if (parentNode->left == currNode) {
                 parentNode->left = NULL;
             }
             else {
                 parentNode->right = NULL;
             }
         }
         else if (currNode->right == NULL) {                // Remove node with only left child
             if (parentNode == NULL) { // Node is root
                 this->root = currNode->left;
             }
             else if (parentNode->left == currNode) {
                 parentNode->left = currNode->left;
             }
             else {
                 parentNode->right = currNode->left;
             }
         }
         else if (currNode->left == NULL) {                // Remove node with only right child
             if (parentNode == NULL) { // Node is root
                 this->root = currNode->right;
             }
             else if (parentNode->left == currNode) {
                 parentNode->left = currNode->right;
             }
             else {
                 parentNode->right = currNode->right;
             }
         }
         else {                                      // Remove node with two children
            // Find successor (leftmost child of right subtree)
             succNode = currNode->right;
            while (succNode->left != NULL) {
                succNode = succNode->left;
            }
            Currency* succData = succNode->data;
            remove(*succData);     // Remove successor
            currNode->data = succData;
         }
         return currNode->data; // Node found and removed
      }
      else if (currNode->data < &newData) { // Search right
          parentNode = currNode;
          currNode = currNode->right;
      }
      else {                     // Search left
          parentNode = currNode;
          currNode = currNode->left;
      }
   }
    return NULL; // Node not found
}

std::string BST_ADT::breadthFirstTraversal(BSTNode* currNode) {
    /*Pre: The current Node must not be NULL. Tree may not be empty.
    *Post: None
    *Return: Returns a string containing the space-separated Currency values from the BST nodes in level-order.
    */

    try {
        if (currNode == NULL) {
            throw std::runtime_error("Method breadthFirstTraversal called on an empty tree.");
        }
        else {
            // Set tempNode to root
            BSTNode* tempNode = currNode;

            // create Queue
            Queue* queue = new Queue;
            queue->enqueue(*currNode->data);

            // create stringstream to capture traversal data vals
            std::stringstream ss;

            // loop while tempNode != NULL
            while (!queue->isEmpty()) {
                tempNode = search(*queue->dequeue());

                // process tempNode
                if (tempNode != NULL && tempNode->data != NULL) {
                    ss << "$" << tempNode->data->getCurr() << "." << tempNode->data->getCoin() << " ";
                    
                    if (tempNode->left != NULL) {
                        queue->enqueue(*tempNode->left->data);
                    }
                    if (tempNode->right != NULL) {
                        queue->enqueue(*tempNode->right->data);
                    }
                }
            }

            delete queue;

            return ss.str();
        }
    }

    catch (std::runtime_error& excpt) {
        std::cout << "Error: " << excpt.what() << std::endl;
        return "";
    }
}

std::string BST_ADT::breadthFirst() {
    return breadthFirstTraversal(root);
}

std::string BST_ADT::inOrderTraversal(BSTNode* currNode){
    /*Pre: Root node must exist. currNode must not be NULL.
    *Post: None.
    *Return: Returns a string containing the space-separated Currency values from the BST nodes in order.
    */

    if (currNode == NULL) {
        return "";
    }
    else {
        std::stringstream ss;


        inOrderTraversal(currNode->left);

        if (currNode->data != NULL) {
            ss << "$" << currNode->data->getCurr() << "." << currNode->data->getCoin() << " ";
        }

        inOrderTraversal(currNode->right);

        return ss.str();
    }
}

std::string BST_ADT::inOrder() {
    return inOrderTraversal(root);
}

std::string BST_ADT::preOrderTraversal(BSTNode* currNode) {
    /*Pre: The current Node must not be NULL. Tree may not be empty.
    *Post: None.
    *Return: Returns a string containing the space-separated Currency values from the BST nodes in pre-order.
    */

    if (currNode == NULL) {
        return "";
    }
    else {
        std::stringstream ss;

        if (currNode->data != NULL) {
            ss << "$" << currNode->data->getCurr() << "." << currNode->data->getCoin() << " ";
        }
        preOrderTraversal(currNode->left);
        preOrderTraversal(currNode->right);

        return ss.str();
    }
}

std::string BST_ADT::preOrder() {
    return preOrderTraversal(root);
}

std::string BST_ADT::postOrderTraversal(BSTNode* currNode) {
    /*Pre: The current Node must not be NULL. Tree may not be empty.
    *Post: None.
    *Return: Returns a string containing the space-separated Currency values from the BST nodes in post-order.
    */

        if (currNode == NULL) {
            return "";
        }
        else {

            std::stringstream ss;

            ss << postOrderTraversal(currNode->left);
            ss << postOrderTraversal(currNode->right);
            if (currNode->data != NULL) {
                ss << "$" << currNode->data->getCurr() << "." << currNode->data->getCoin() << " ";
            }

            return ss.str();
        }
}

std::string BST_ADT::postOrder() {
    return postOrderTraversal(root);
}

int BST_ADT::getHeight(BSTNode* currNode) {
    /*Pre: The current Node must not be NULL.
    *Post: N/A
    *Return: Returns the height of the tree.
    */

    try {
        if (currNode == NULL) {
            throw std::runtime_error("Method getHeight called on an empty tree.");
        }

        int leftHeight = getHeight(currNode->left);
        int rightHeight = getHeight(currNode->right);
        return (1 + std::max(leftHeight, rightHeight));
    }
    catch (std::runtime_error& excpt) {
        std::cout << "Error: " << excpt.what() << std::endl;
        return -1;
    }
}

void BST_ADT::print() {

    std::cout << "Breadth-first traversal: " << breadthFirstTraversal(root) << std::endl;
    std::cout << "In-order traversal: " << inOrderTraversal(root) << std::endl;
    std::cout << "Pre-order traversal: " << preOrderTraversal(root) << std::endl;
    std::cout << "Post-order traversal: " << postOrderTraversal(root) << std::endl;

    return;
}

int BST_ADT::count() {

    if (root == NULL) {
        return 0;
    }

    else {
        int counter = 0;

        BSTNode* currNode;
        Stack stack;
        stack.push(*root->data);

        while (stack.peek() != NULL) {

            currNode = search(*stack.peek());
            stack.pop();

            if (currNode != NULL) {

                if (currNode->left != NULL) {
                    stack.push(*currNode->left->data);
                }

                if (currNode->right != NULL) {
                    stack.push(*currNode->right->data);
                }

                counter++;
            }
        }

        return counter;
    }
}

bool BST_ADT::isEmpty() {
    return root == NULL;
}