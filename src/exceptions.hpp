/*
 * exceptions.hpp
 *
 *  Created on: 2018. dec. 3.
 *      Author: Wero
 */

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

#include <exception>

//A 3. heti órai kód megoldásából átemelve

class UnderFlowException : public std::exception {
    public:
        const char* what() const throw() { return "UnderFlow!"; }
};

class OverFlowException : public std::exception {
    public:
        const char* what() const throw() { return "OverFlow!"; }

};
class OutOfIndexException : public std::exception {
public:
	const char* what() const throw() {
		return "Index is out of boundaries!";
	}
};


#endif /* EXCEPTIONS_HPP_ */
