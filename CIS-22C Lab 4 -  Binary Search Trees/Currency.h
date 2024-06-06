/* CIS-22C
*  Lab 4 - Binary Search Trees
*  Spencer Bledsoe
*/

/*************************************************************************************************************************************************************************
													CODE MODIFIED FROM PREVIOUS LAB

	- Exception handling changed to throw/catch invalid_argument type instead of string type per exception handling guidelines in Zybooks Ch 1.51.
		- Affects add(), subtract(), ==(), >(), <()
	- Subtraction Method now handles negative coin values properly with the addition of a new "if" statement.
	- Adjusted double constructor to round correctly. Certain values would not cast correctly, e.g. '32.23' rounding to 32.22, using the old method.
	- New logic for <(), >() overloads to correct logic errors. Old implementation for '>' would return false if currency > secondObj.currency if coin < secondObj.coin
	- Added a "friend" function to overload << ostream operator.
*************************************************************************************************************************************************************************/

#pragma once
#include <string>
#include <iomanip>
#include <iostream>

class Currency {
protected:
	int currency;
	int coin;

public:
	//Constructor Declarations (Default, All Param, Copy), no constructors/destructors needed, abstract class
	Currency() {
		currency = 0;
		coin = 0;
	}

	Currency(double inCurr) {
		currency = static_cast<int>(inCurr);
		coin = static_cast<int>((inCurr * 100) - (currency * 100) + 0.5);
	}

	Currency(Currency& t) {
		currency = t.currency;
		coin = t.coin;
	}

	bool operator == (const Currency& y) const;
	bool operator > (const Currency& y) const;
	bool operator < (const Currency& y) const;

	//Getters (make virtual)
	/*Pre: Object type == derived class
	Post: returns corresponding member variable value from derived class after override.
	*/
	virtual int getCurr() const = 0;
	virtual int getCoin() const = 0;
	virtual std::string getType() const = 0;

	//Setters
	/*Pre: this.currType == newCurr.currType && validated input
	Post: this.currency && this.coin +- newCurr.currency && newCurr.coin
	*/
	void add(Currency& newCurr) {
		try {
			if (this->getType() == newCurr.getType()) {
				currency = currency + newCurr.getCurr();
				coin = coin + newCurr.getCoin();
				if (coin > 99) {
					coin = coin - 100;
					currency++;
				}
			}
			else {
				throw std::invalid_argument("addition");
			}
		}

		catch (std::invalid_argument& excpt) {
			std::cout << "Invalid " << excpt.what() << std::endl;
		}

		return;
	}
	void subtract(Currency& newCurr) {
		try {
			if (this->isGreater(&newCurr) || this->isEqual(&newCurr)) {
				currency = currency - newCurr.getCurr();
				coin = coin - newCurr.getCoin();

				if (coin < 0) {
					coin = coin + 100;
					currency--;
				}
			}
			else {
				throw std::invalid_argument("subtraction");
			}
		}

		catch (std::invalid_argument& excpt) {
			std::cout << "Invalid " << excpt.what() << std::endl;
		}

		return;
	}
	/*Pre: y.currType == this.currType
	* Post: returns comparison output
	*/
	bool isEqual(Currency* y) const { return (this == y); }
	bool isGreater(Currency* y) const { return (this > y); }

	void print() {
	/*Pre: None
	Post: Prints this.currency && this.coin to console.
	*/
		std::cout << getCurr() << "." << std::setw(2) << std::setfill('0') << std::right << getCoin() << " " << getType();
		return;
	}

	friend std::ostream& operator<<(std::ostream& os, const Currency& curr) {
		os << curr.getCurr() << "." << std::setw(2) << std::setfill('0') << curr.getCoin() << " " << curr.getType();
		return os;
	}

};

bool Currency::operator==(const Currency& y) const {
	/*Pre: this.currType == y.currType
	Post: returns comparison
	*/
	try {
		if (this->getType() != y.getType()) {
			throw std::invalid_argument("==");
		}

		else {
			return (this->getCurr() == y.getCurr() && this->getCoin() == y.getCoin());
		}
	}

	catch (std::invalid_argument& excpt) {
		std::cout << "Invalid comparison: Currency Type Mismatch for operator " << excpt.what() << std::endl;
		return false;
	}

}

bool Currency::operator > (const Currency& y) const {
	/*Pre: this.currType == y.currType
	Post: returns comparison output
	*/
	try {
		if (this->getType() != y.getType()) {
			throw std::invalid_argument(">");
		}

		if (this->getCurr() > y.getCurr()) {
			return true;
		}

		else if (this->getCurr() == y.getCurr()) {
			return (this->getCoin() > y.getCoin());
		}

		else {
			return false;
		}

	}

	catch (std::invalid_argument& excpt) {
		std::cout << "Invalid comparison: Currency Type Mismatch for operator " << excpt.what() << std::endl;
		return false;
	}
}

bool Currency::operator < (const Currency& y) const {
	/*Pre: this.currType == y.currType
	Post: returns comparison output
	*/
	try {
		if (getType() != y.getType()) {
			throw std::invalid_argument(">");
		}

		if (this->getCurr() < y.getCurr()) {
			return true;
		}

		else if (this->getCurr() == y.getCurr()) {
			return (this->getCoin() < y.getCoin());
		}

		else {
			return false;
		}

	}

	catch (std::invalid_argument& excpt) {
		std::cout << "Invalid comparison: Currency Type Mismatch for operator " << excpt.what() << std::endl;
		return false;
	}
}