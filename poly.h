/**
 * |--------------------------------------------------------------------------------------|
 *  Poly.h
 *  Prajeet Pounraj
 *  CSS 343 - Prof. Rahman
 *  April 6, 2023
 * |--------------------------------------------------------------------------------------|
 *  Description: 
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

using namespace std;

#ifndef POLY_H
#define POLY_H


#include <iostream>


class Poly {

    /**
     * Overload >> to input all coeffs (sets all terms of one Poly, in a loop; it is expected 
     * that a user enters one coefficient and an exponent repeatedly, Enters -1 for both when done;)
     */
    friend istream &operator>>(istream &inStream, Poly &obj);

    //Overloading << to output an entire polynomial, print “ +5x^3 -2x^2 +4” to represent the Poly
    friend ostream &operator<<(ostream &outStream, const Poly &obj);

    private:
        int *ptr; // Coeff pointer of array
        int size; // length of array

    public:
    // Constructors
    // Initializes both coefficient and power to 0, 0X^0
        Poly();
    // Copy constructor, makes deep copy of object
        Poly(Poly &obj);
    // Memory is reserved for polynomial, (5, 7) == 5X^7
        Poly(int coEff, int power);
    // Memory is reserved for polynomial, (5) == 5x^0
        Poly(int coEff);
    // Destructor
        ~Poly();

    // Setters
    void setCoeff(int coeff, int power);

    // Getters
    int getCoeff(int power) const;

    // Overloading Common Operators
    Poly operator+(const Poly &rhs) const;
    Poly operator-(const Poly &rhs) const;
    Poly operator*(const Poly &rhs) const;

    Poly& operator+=(const Poly &rhs);
    Poly& operator-=(const Poly &rhs);
    Poly& operator*=(const Poly &rhs);

    // The (=) operator assigns one polynomial to another
    Poly& operator=(const Poly &rhs);
    // The equality and inequality operators
    bool operator==(const Poly &rhs) const;
    bool operator!=(const Poly &rhs) const;


};

#endif //POLY_H