/* CIS-22C
*  Lab 4 - Binary Search Trees
*  Spencer Bledsoe
*/

#pragma once

#include "Currency.h"

struct BSTNode {
public:
	Currency* data;
	BSTNode* left;
	BSTNode* right;
};
