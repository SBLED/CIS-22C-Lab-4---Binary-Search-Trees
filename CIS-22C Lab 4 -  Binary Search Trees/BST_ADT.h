/* CIS-22C
*  Lab 4 - Binary Search Trees
*  Spencer Bledsoe
*/

#pragma once
#include "BSTNode.h"
#include "Queue.h"
#include <vector>

class BST_ADT {
private:
    int height;
    BSTNode* root;


public:

    BST_ADT() {
        height = 0;
        root = NULL;
    }

    ~BST_ADT() {
        while (root != NULL) {
            BSTNode* iterator = root;
            //logic to progress in order traversal deleting each node;
            delete iterator;
        }
    }

	BSTNode* search(Currency&);
	void insert(Currency&);
    Currency* remove(Currency&);

    std::string breadthFirstTraversal(BSTNode*);
    std::string inOrderTraversal(BSTNode*);
    std::vector<Currency*> inOrder(BSTNode*, std::string&);
    std::string preOrderTraversal(BSTNode*);
    std::string postOrderTraversal(BSTNode*);

    int getHeight(BSTNode*);
    void print();
    int count();
    bool isEmpty();
    //empty?

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

	if (this->root == NULL) {
        this->root = newNode;
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

std::string breadthFirstTraversal(BSTNode* currNode) {
    /*Pre: The current Node must not be NULL. Tree may not be empty.
    *Post: Prints the tree in level-order (breadth-first).
    *Return: Void
    */

    try {
        if (currNode == NULL) {
            throw std::runtime_error("Method breadthFirstTraversal called on an empty tree.");
        }
        else {

            // Set tempNode to root
            BSTNode* tempNode = currNode;
            // create Queue
            Queue queue;
            queue.enqueue(*currNode->data);

            // loop while tempNode != NULL
            while (!queue.isEmpty()) {

                // process tempNode
                if (tempNode != NULL) {
                    if (tempNode->left != NULL) {
                        queue.enqueue(*tempNode->left->data);
                    }
                    if (tempNode->right != NULL) {
                        queue.enqueue(*tempNode->right->data);
                    }
                    // if (!queue.isEmpty())
                        // tempNode->data = queue.dequeue();
                    // else
                        // tempNode = NULL;
                }
            }

            //delete queue;



            return;
        }
    }

    catch (std::runtime_error& excpt) {
        std::cout << "Error: " << excpt.what() << std::endl;
        return;
    }
}

std::string BST_ADT::inOrderTraversal(BSTNode* currNode){
    /*Pre: Root node must exist. currNode must not be NULL.
    *Post: Prints the tree in order of smallest to largest values.
    *Return: Void
    */
    std::string str = "";
    inOrder(currNode, str);


    return str;

}

std::vector<Currency*> BST_ADT::inOrder(BSTNode* currNode, std::string& str) {
    try {
        if (currNode == NULL) {
            throw std::runtime_error("Method inOrderTraversal called on an empty tree.");
        }
        else {
            std::string str;
            inOrderTraversal(currNode->left);
            str.append(currNode->data->getData());
            inOrderTraversal(currNode->right);

            return;
        }
    }

    catch (std::runtime_error& excpt) {
        std::cout << "Error: " << excpt.what() << std::endl;
        return;
    }
}

std::string preOrderTraversal(BSTNode* currNode) {
    /*Pre: The current Node must not be NULL. Tree may not be empty.
    *Post: Prints the tree in pre-order.
    *Return: Void
    */

    try {
        if (currNode == NULL) {
            throw std::runtime_error("Method preOrderTraversal called on an empty tree.");
        }
        else {
            currNode->data->print();
            preOrderTraversal(currNode->left);
            preOrderTraversal(currNode->right);

            return;
        }
    }

    catch (std::runtime_error& excpt) {
        std::cout << "Error: " << excpt.what() << std::endl;
        return;
    }
}

std::string postOrderTraversal(BSTNode* currNode) {
    /*Pre: The current Node must not be NULL. Tree may not be empty.
    *Post: Prints the tree in post-order.
    *Return: Void
    */

    try {
        if (currNode == NULL) {
            throw std::runtime_error("Method postOrderTraversal called on an empty tree.");
        }
        else {
            postOrderTraversal(currNode->left);
            postOrderTraversal(currNode->right);
            currNode->data->print();

            return;
        }
    }

    catch (std::runtime_error& excpt) {
        std::cout << "Error: " << excpt.what() << std::endl;
        return;
    }
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

    std::string strArr[4];
    int i = 0;

    strArr[i++] = breadthFirstTraversal(root);
    strArr[i++] = inOrderTraversal(root);
    strArr[i++] = preOrderTraversal(root);
    strArr[i++] = postOrderTraversal(root);

}

int BST_ADT::count() {
    return 1;
}

bool BST_ADT::isEmpty() {
    return root == NULL;
}