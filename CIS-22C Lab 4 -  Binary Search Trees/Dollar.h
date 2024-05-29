/* CIS-22C
*  Lab 4
*  Spencer Bledsoe
*/

/*****************************************************************************
							CODE MODIFIED FROM PREVIOUS LAB

	- "const" added to currType, ensuring no unwanted modifications.
*****************************************************************************/

#pragma once
#include "Currency.h"
#include <string>

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