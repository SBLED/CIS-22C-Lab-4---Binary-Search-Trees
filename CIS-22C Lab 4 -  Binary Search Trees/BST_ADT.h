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
    void inOrderTraversal(BSTNode*, std::stringstream&);
    void preOrderTraversal(BSTNode*, std::stringstream&);
    void postOrderTraversal(BSTNode*, std::stringstream&);

public:

    BST_ADT() {
        height = 0;
        root = NULL;
    }

    ~BST_ADT() {
        emptyBST(root);
    }

    void emptyBST(BSTNode*);

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

void BST_ADT::emptyBST(BSTNode* currNode) {
    if (currNode != NULL) {
        emptyBST(currNode->left);
        emptyBST(currNode->right);
        delete currNode;
    }
    return;
}

BSTNode* BST_ADT::search(Currency& key) {
    /*Pre: key param must be valid. key must not be NULL.
    *Post: Returns the BSTNode containing the key if found. Otherwise returns NULL.
    */

    BSTNode* currNode = root;
	 while (currNode != NULL) {
			if(key == *currNode->data) {
                return currNode;
			}

			else if(key < *currNode->data) {
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
    *Return: Void
    */

   //Create new node named 'node'
   BSTNode* newNode = new BSTNode();
   newNode->data = &newCurr;

   if (root == NULL) {
       root = newNode;
   }
   else {
        BSTNode* currNode;
        BSTNode* parNode = NULL;
        currNode = root;

        while (currNode) {
            parNode = currNode;
            if (newCurr < *currNode->data) {
                currNode = currNode->left;
            }
            else {
                currNode = currNode->right;
            }
        }

        if (newCurr < *parNode->data) {
            parNode->left = newNode;
        }
        else {
            parNode->right = newNode;
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
    BSTNode* currNode = root;
    Currency* currData;


    while (currNode != NULL) {
      if (*currNode->data == newData) { // Node found 
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
         else if (currNode->right == NULL) {  // Remove node with only left child
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
         else if (currNode->left == NULL) { // Remove node with only right child
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
         else { // Remove node with two children
            // Find successor (leftmost child of right subtree)
             succNode = currNode->right;
            while (succNode->left != NULL) {
                succNode = succNode->left;
            }
            Currency* succData = succNode->data;
            remove(*succData);     // Remove successor
            currNode->data = succData;
         }
         return currNode->data;
      }
      else if (*currNode->data < newData) {
          parentNode = currNode;
          currNode = currNode->right;
      }
      else {
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
            BSTNode* tempNode = currNode;

            // create Queue
            Queue queue;
            queue.enqueue(*currNode->data);

            // create stringstream to capture traversal data
            std::stringstream ss;

            // loop while tempNode != NULL
            while (!queue.isEmpty()) {
                tempNode = search(*queue.dequeue());

                // process tempNode
                if (tempNode != NULL && tempNode->data != NULL) {
                    ss << "$" << tempNode->data->getCurr() << "." << std::setw(2) << std::setfill('0') << std::right << tempNode->data->getCoin() << " ";
                    
                    if (tempNode->left != NULL) {
                        queue.enqueue(*tempNode->left->data);
                    }
                    if (tempNode->right != NULL) {
                        queue.enqueue(*tempNode->right->data);
                    }
                }
            }

            return ss.str();
        }
    }

    catch (std::runtime_error& excpt) {
        std::cout << "Error: " << excpt.what() << std::endl;
        return "";
    }
}

std::string BST_ADT::breadthFirst() {
    /*Pre: Root node must exist.
    Post: None.
    Return: Returns a string containing space-separated node currency values in level-order.
    */

    return breadthFirstTraversal(root);
}

void BST_ADT::inOrderTraversal(BSTNode* currNode, std::stringstream& ss){
    /*Pre: Root node must exist. currNode must not be NULL.
    *Post: Appends node values in-order, space-separated, to a stringstream that was passed by reference.
    *Return: None
    */

    if (currNode == NULL) {
        return;
    }
    else {


        inOrderTraversal(currNode->left, ss);

        if (currNode->data != NULL) {
            ss << "$" << currNode->data->getCurr() << "." << std::setw(2) << std::setfill('0') << std::right << currNode->data->getCoin() << " ";
        }

        inOrderTraversal(currNode->right, ss);

        return;
    }
}

std::string BST_ADT::inOrder() {
    std::stringstream ss;
    inOrderTraversal(root, ss);
    return ss.str();
}

void BST_ADT::preOrderTraversal(BSTNode* currNode, std::stringstream& ss) {
    /*Pre: The current Node must not be NULL. Tree may not be empty.
    *Post: Appends node values, space-separated, in pre-order to a stringstream that was passed by reference.
    *Return: None
    */

    if (currNode == NULL) {
        return ;
    }
    else {

        if (currNode->data != NULL) {
            ss << "$" << currNode->data->getCurr() << "." << std::setw(2) << std::setfill('0') << std::right << currNode->data->getCoin() << " ";
        }
        preOrderTraversal(currNode->left, ss);
        preOrderTraversal(currNode->right, ss);

        return;
    }
}

std::string BST_ADT::preOrder() {
    std::stringstream ss;
    preOrderTraversal(root, ss);
    return ss.str();
}

void BST_ADT::postOrderTraversal(BSTNode* currNode, std::stringstream& ss) {
    /*Pre: The current Node must not be NULL. Tree may not be empty.
    *Post: Appends node values, space-separated and in post-order, to a stringstream that was passed by reference.
    *Return: None.
    */

        if (currNode == NULL) {
            return;
        }
        else {

            postOrderTraversal(currNode->left, ss);
            postOrderTraversal(currNode->right, ss);
            if (currNode->data != NULL) {
                ss << "$" << currNode->data->getCurr() << "." << std::setw(2) << std::setfill('0') << std::right << currNode->data->getCoin() << " ";
            }

            return;
        }
}

std::string BST_ADT::postOrder() {
    std::stringstream ss;
    postOrderTraversal(root, ss);
    return ss.str();
}

int BST_ADT::getHeight(BSTNode* currNode) {
    /*Pre: The current Node must not be NULL.
    *Post: N/A
    *Return: Returns the height of the tree.
    */

 
    if (currNode == NULL) {
        return 0;
    }

    int leftHeight = getHeight(currNode->left);
    int rightHeight = getHeight(currNode->right);
    return (1 + std::max(leftHeight, rightHeight));
}

void BST_ADT::print() {

    std::cout << "Breadth-first traversal: " << breadthFirst() << std::endl;
    std::cout << "In-order traversal: " << inOrder() << std::endl;
    std::cout << "Pre-order traversal: " << preOrder() << std::endl;
    std::cout << "Post-order traversal: " << postOrder() << std::endl;

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