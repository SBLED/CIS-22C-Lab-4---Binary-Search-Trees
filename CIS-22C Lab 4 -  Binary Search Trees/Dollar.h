/* CIS-22C
*  Lab 4 - Binary Search Trees
*  Spencer Bledsoe
*/

/*****************************************************************************
							CODE MODIFIED FROM PREVIOUS LAB

	- "const" added to currType, ensuring no unwanted modifications.
	- Removed unnecessary #include <string>. Already included in Currency.h
*****************************************************************************/

#pragma once
#include "Currency.h"

class Dollar : public Currency {
private:
	const std::string currType = "Dollar";

public:
	//Constructor Declarations (Default, All Param, Copy)
	using Currency::Currency;

	//Getters (make "override")
	/*Pre: this.currType == Dollar
	Post: Returns corresponding member variable
	*/
	int getCurr() const override { return currency; }
	int getCoin() const override { return coin; }
	std::string getType() const override { return currType; }

};