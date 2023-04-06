/**
 * |--------------------------------------------------------------------------------------|
 *  Poly.cpp
 *  Prajeet Pounraj
 *  CSS 343 - Prof. Rahman
 *  April 6, 2023
 * |--------------------------------------------------------------------------------------|
 *  Description: (Function Definition for Poly.h file)
 *  Create an ADT called Poly to represent polynomials with nonnegative exponents.
 *  Implement it as an array of terms, where each term has an exponent and a coefficient.
 *  Use dynamic memory allocation for the array, and allow modification of the polynomial
 *  as well as addition, subtraction, and multiplication with other polynomials.
 * |--------------------------------------------------------------------------------------|
 *  Assume: 
 *  The code for the ADT Poly assumes that all input data is correct and no error handling 
 *  is included. Negative exponents will be ignored, and there is no provision for checking 
 *  incorrect data types. The internal representation of the polynomial is implemented as an
 *  array of terms, where each term has an exponent and a coefficient. The size of the array
 *  is dynamically allocated, and the polynomial can be modified, added, subtracted, or
 *  multiplied with other polynomials.
*/

#include "poly.h"

using namespace std;

/** Constructors
 * |--------------------------------------------------------------------------------------|
 * Initializes both coefficient and power to 0, 0X^0 and sets size to 1.
*/
Poly::Poly() {
    this->size = 1;
    this->ptr = new int[this->size];
    ptr[0] = 0; 
}
// Copy constructor, makes deep copy of object.
Poly::Poly(Poly &obj) {
    this->size = obj.size;
    this->ptr = new int[this->size];
    // deep copy so for loop to copy each coeff over to the new array.
    for(int i = 0; i < this->size; i++) {
        this->ptr[i] = obj.ptr[i];
    }
}
// Constructor takes in two int parameters to be able to reserve memory for polynomial, (5, 7) == 5X^7.
Poly::Poly(int coEff, int power) {
    this->size = power + 1;
    this->ptr = new int[this->size];
    // initialize the coefficients to 0 before editing the coefficient of the power. 
    for(int i = 0; i < this->size; i++) {
        this->ptr[i] = 0;
    }
    this->ptr[power] = coEff;
}
// Constructor takes in a int parameters to be able to reserve memory for the coefficient of the polynomial, (5) == 5x^0.
Poly::Poly(int coEff) {
    this->size = 1;
    this->ptr = new int[this->size];
    this->ptr[0] = coEff;
}
// Destructor, helps clear memory.
Poly::~Poly() {
    delete[] this->ptr;
    this->size = 0;
}

/** Setters
 * |--------------------------------------------------------------------------------------|
 * This method allows for other methods to set the coefficient given the power(AKA index).
*/
void Poly::setCoeff(int coeff, int power) {
    if (power < 0 || coeff == 0) { 
        return; // exit method if invalid.
    }
    if (power >= this->size) { // check if array needs to be resized.
        int new_size = power + 1;
        int* new_ptr = new int[new_size]; 
        for (int i = 0; i < this->size; i++) {
            new_ptr[i] = this->ptr[i]; // copy existing coefficients to new array.
        }
        for (int i = this->size; i < new_size; i++) {
            new_ptr[i] = 0; 
        }
        delete[] this->ptr; // free memory from old array.
        this->size = new_size; 
        this->ptr = new_ptr;
    }
    this->ptr[power] = coeff;
}

/** Getters
 * |--------------------------------------------------------------------------------------|
 * This method allows for other methods to call for the coefficient given the power of the polynomial. 
*/
int Poly::getCoeff(int power) const {
    if((power >= 0) && (power <= this->size)) {
        return this->ptr[power];
    }
    return 0;
}

/** Overloading Common Operators.
 * |--------------------------------------------------------------------------------------|
 * These methods overload common operations to be able to add, subtract and multiply polynomials.
*/
// This method allows to add two different polynomials together.
Poly Poly::operator+(const Poly &rhs) const {
    int new_size = this->size;
    if (size < rhs.size) { // compare sizes to get the maximum size.
        new_size = rhs.size;
    }
    Poly result(0, new_size - 1); // create a new Poly object to store the sum.
    for (int i = 0; i < new_size; i++) {
        int coeff = 0;
        if (i < this->size) { // add coefficients of the same power.
            coeff += this->ptr[i];
        }
        if (i < rhs.size) {
            coeff += rhs.ptr[i];
        }
        result.setCoeff(coeff, i); // set the new coefficient in the result Poly object.
    }
    return result; // return the sum in a new Poly object.
}
// This method allows to subtract two different polynomials together.
Poly Poly::operator-(const Poly &rhs) const {
     int new_size = this->size;
    if (size < rhs.size) { // compare sizes to get the maximum size.
        new_size = rhs.size;
    }
    Poly result(0, new_size - 1);
    for (int i = 0; i < new_size; i++) {
        int coeff = 0;
        if (i < this->size) {
            coeff += this->ptr[i];
        }
        if (i < rhs.size) {
            coeff -= rhs.ptr[i]; // subtract second coefficient.
        }
        result.setCoeff(coeff, i);
    }
    return result;
}
// This method allows to multiply two different polynomials together.
Poly Poly::operator*(const Poly &rhs) const {
    int new_size = size + rhs.size - 1; // get the maximum size.
    Poly result(0, new_size - 1); // create a new Poly object to store the product.
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < rhs.size; j++) {
            if ((this->ptr[i] != 0) && (rhs.ptr[j] != 0)) {
                int coeff = this->ptr[i] * rhs.ptr[j]; // multiply coefficients of different powers.
                int currCoeff = 0;
                if (i+j < result.size) {
                    currCoeff = result.getCoeff(i+j);
                }
                result.setCoeff(currCoeff + coeff, i+j);
            }
        }
    }
    return result; // return the product in a new Poly object.
}
// The implementation simply calls the operator+ method to add the coefficients of the two Poly objects.
// The current object is the sum of the two.
Poly& Poly::operator+=(const Poly &rhs) {
    *this = *this + rhs;
    return *this;
}
// The implementation simply calls the operator- method to subtract the coefficients of the two Poly objects.
// The current object is the difference of the two.
Poly& Poly::operator-=(const Poly &rhs) {
    *this = *this - rhs;
    return *this;
}
// The implementation simply calls the operator* method to multiply the coefficients of the two Poly objects.
// The current object is the multiple of the two.
Poly& Poly::operator*=(const Poly &rhs) {
    *this = *this * rhs;
    return *this;
}

// The (=) operator assigns one polynomial to another.
Poly& Poly::operator=(const Poly &rhs) {
    if (this == &rhs) { // handle self-assignment
        return *this;
    }
    if (this->size < rhs.size) { // resize if necessary
        delete[] this->ptr;
        this->ptr = new int[rhs.size];
        this->size = rhs.size;
    }
    for(int k = 0; k < this->size; k++) {
        this->ptr[k] = 0;
    } // sets all the coefficients to 0
    for(int i = 0; i < rhs.size; i++) {
        this->ptr[i] = rhs.ptr[i]; // copy elements
    }
    return *this;
}

// returns true if two polynomials are equal to each other, if not it returns false. 
bool Poly::operator==(const Poly& rhs) const {
    if (size == rhs.size) { // checks if the sizes are equal, if so checks coefficients to see if they are too.
        for (int i = size - 1; i >= 0; i--) {
            if (ptr[i] != rhs.ptr[i]) {
                return false;
            }
        }
        return true;
    } else {
        int start, end, diff;
        const Poly* smaller;

        if (size < rhs.size) { // determine which polynomial is small
            start = size - 1; // sets the starting index of the loop
            end = -1;
            diff = -1; // setting the decrement value of the loop
            smaller = this; // setting the smaller polynomial depending on size.
        } else {
            start = rhs.size - 1;
            end = size - rhs.size - 1;
            diff = -1;
            smaller = &rhs;
        }
        // iterate through the polynomial from the highest degree to the lowest degree of the smaller polynomial.
        for (int i = start; i > end; i--) { 
            if (ptr[i] != smaller->ptr[i - size + smaller->size]) { // if the coefficients are not equal, return false.
                return false;
                return false;
            }
        }
        // check if the coefficients of the larger polynomial are all zero from the highest degree of the 
        //smaller polynomial to the lowest degree of the larger polynomial. if it is not a 0 it returns false.
        for (int i = end; i >= 0; i--) {
            if (ptr[i] != 0) {
                return false;
            }
        }
        return true;
    }
}


// returns a true or false based on if the function is not equal. 
bool Poly::operator!=(const Poly &rhs) const {
    return !(*this == rhs); // returns the opposite of == method making it !=.
}

// ISTREAM method that allows for setting up the ptr[] by calling setCoeff with data from the terminal.
istream& operator>>(istream& inStream, Poly& obj) {
    int coeff;
    int power;
    bool status = true;
    while (status) {
        inStream >> coeff >> power; // assigns first to coeff, second to power
        if ((coeff == -1) && (power == -1)) {
            status = false;
        } else {
            obj.setCoeff(coeff, power);
        }
    } // takes in a number pairs from console and exists when two -1 are taken in.
    return inStream;
}

// OSTREAM method that prints all the polynomials onto the terminal.
ostream& operator<<(ostream& outStream, const Poly& obj) {
    bool empty = true;  // to check polynomial if its all 0

    for (int i = obj.size - 1; i >= 0; i--) { 
        if (obj.ptr[i] != 0) {    // check if index isn't 0
            empty = false; 

            if (i == obj.size - 1) { // print first term without a leading space
                if (obj.ptr[i] >= 0) { // check sign of coefficient
                    outStream << " +" << obj.ptr[i]; 
                } else {
                    outStream << " " << obj.ptr[i]; 
                }
            } else {
                outStream << " "; 
                if (obj.ptr[i] >= 0) { 
                    outStream << "+"; 
                }
                outStream << obj.ptr[i];
            }
            if (i > 1) {   // check if power should be printed
                outStream << "x^" << i;
            } else if (i == 1) { // check if x should be printed
                outStream << "x";   
            }
        }
    }
    if (empty) { // check if polynomial is all zeroes
        outStream << "0";    // print 0 if polynomial is all zeroes
    }
    return outStream;
}
