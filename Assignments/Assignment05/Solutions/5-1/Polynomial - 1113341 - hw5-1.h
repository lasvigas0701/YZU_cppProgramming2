//#ifndef POLYNOMIAL_H
//#define POLYNOMIAL_H
//
//#include <cmath>
//using std::sqrt;
//
//#include "vector - 1113341 - hw5.h"
//
//// Represents a term of a polynomial
//template< typename T >
//struct Term
//{
//    bool operator!=(const Term& right) const
//    {
//        return coef != right.coef || expon != right.expon;
//    }
//
//    T coef;
//    T expon;
//};
//
//// Polynomial class template definition
//template< typename T1, typename T2 >
//class Polynomial
//{
//    // Overloaded stream insertion operator
//    template< typename T1, typename T2 >
//    friend ostream& operator<<(ostream& output, Polynomial< T1, T2 > a);
//public:
//
//    // Constructs an empty polynomial, with no terms.
//    Polynomial(size_t n = 0)
//        : polynomial(n)
//    {
//    }
//
//    // Constructs a polynomial with a copy of each of the terms in polynomialToCopy.
//    Polynomial(const Polynomial& right)
//        : polynomial(right.polynomial)
//    {
//    }
//
//    // Destructor with empty body
//    ~Polynomial()
//    {
//    }
//
//    // Copies all the terms from "right" into the polynomial
//    const Polynomial operator=(const Polynomial& right)
//    {
//        if (&right != this) // avoid self-assignment
//            polynomial = right.polynomial;
//
//        return *this; // enables x = y = z, for example
//    }
//
//    bool operator==(const Polynomial& right)
//    {
//        return polynomial == right.polynomial;
//    }
//
//    void setPolynomial(T2 coefficient[], T2 exponent[], int numTerms)
//    {
//        for (int i = 0; i < numTerms; i++)
//        {
//            polynomial[i].coef = coefficient[i];
//            polynomial[i].expon = exponent[i];
//        }
//    }
//
//    // addition assignment operator; Polynomial += Polynomial
//    void operator+=(Polynomial& op2)
//    {
//        Polynomial sum(polynomial.size() + op2.polynomial.size());
//        size_t i = 0, j = 0, k = 0;
//
//        while (i < polynomial.size() && j < op2.polynomial.size())
//        {
//            if (polynomial[i].expon > op2.polynomial[j].expon) /*put bigger in sum*/
//            {
//                //cout << "a\n";
//                sum.polynomial[k].expon = polynomial[i].expon;
//                sum.polynomial[k].coef = polynomial[i].coef;
//                i++, k++;
//            }
//            else if (polynomial[i].expon < op2.polynomial[j].expon)
//            {
//                sum.polynomial[k].expon = op2.polynomial[j].expon;
//                sum.polynomial[k].coef = op2.polynomial[j].coef;
//                j++, k++;
//            }
//            else if (polynomial[i].expon == op2.polynomial[j].expon)
//            {
//                //cout << "c\n";
//                if (polynomial[i].coef + op2.polynomial[j].coef == 0) {
//                    /*cout << "zero!\n";*/
//                    i++, j++;
//                    continue;
//                }
//                sum.polynomial[k].expon = polynomial[i].expon;
//                sum.polynomial[k].coef = polynomial[i].coef + op2.polynomial[j].coef;
//                i++, j++, k++;
//            }
//        }
//
//        while (i < polynomial.size()) {
//            //cout << "d\n";
//            sum.polynomial[k].expon = polynomial[i].expon;
//            sum.polynomial[k].coef = polynomial[i].coef;
//            i++, k++;
//        }
//
//        while (j < op2.polynomial.size()) {
//            //cout << "e\n";
//            sum.polynomial[k].expon = op2.polynomial[j].expon;
//            sum.polynomial[k].coef = op2.polynomial[j].coef;
//            j++, k++;
//        }
//        /*cout << "S1: " << sum << "  " << sum.polynomial.size() << endl;*/
//
//        /*resize the degree of polynomial*/
//        while (sum.polynomial.size() != 0 && sum.polynomial[sum.polynomial.size() - 1].coef == 0) {
//            sum.polynomial.erase(sum.polynomial.end() - 1);
//            /*cout << "S2: " << sum << "  " << sum.polynomial.size() << endl;*/
//        }
//
//        /*for (size_t i = 0; i < sum.polynomial.size(); i++) { cannot
//            if (sum.polynomial[i].coef == 0) {
//                sum.polynomial.erase(&sum.polynomial[i]);
//            }
//        }*/
//
//        /*cout << "S2: " << sum << "  " << sum.polynomial.size() << endl;*/
//        polynomial = sum.polynomial; /*equal to *this = sum*/
//    }
//
//    // subtraction assignment operator; Polynomial -= Polynomial
//    void operator-=(Polynomial& op2)
//    {
//        Polynomial minus = -op2;
//        /*cout << "minus: " << minus << '\t';
//        cout << "minus size: " << minus.polynomial.size() << endl;*/
//        *this += minus;
//    }
//
//    // multiplication operator; Polynomial * Polynomial
//    Polynomial operator*(Polynomial& op2)
//    {
//        Polynomial buffer(polynomial.size());
//
//        Polynomial product;
//        for (size_t i = 0; i < op2.polynomial.size(); i++)
//        {
//            for (size_t j = 0; j < polynomial.size(); j++)
//            {
//                buffer.polynomial[j].expon = op2.polynomial[i].expon + polynomial[j].expon;
//                buffer.polynomial[j].coef = op2.polynomial[i].coef * polynomial[j].coef;
//            }
//            /*cout << "P: " << product << "  " << product.polynomial.size() << endl;*/
//            product += buffer;
//            /*cout << "B: " << buffer << "  " << buffer.polynomial.size() << endl;*/
//        }
//
//        /*don't need because it has resized in operator+=
//        for (size_t i = 0; i < product.polynomial.size(); i++) {
//            if (product.polynomial[i].coef == 0) {
//                product.polynomial.erase(&product.polynomial[i]);
//            }
//
//        }*/
//        /*cout << "P: " << product << endl;*/
//        return product;
//    }
//
//    // computes the square root of the current polynomial
//    Polynomial compSquareRoot()
//    {
//        Polynomial remainder(*this);
//        /*cout << "remainder: " << remainder << endl;*/
//        Polynomial monomial(1);
//        Polynomial squrt, divisor;
//        monomial.polynomial[0].expon = polynomial[0].expon / 2;
//        monomial.polynomial[0].coef = sqrt(polynomial[0].coef);
//        squrt += monomial;
//        divisor += monomial;
//
//        Polynomial buffer(divisor * squrt);
//
//        /*cout << monomial.polynomial[0].expon << "  " << monomial.polynomial[0].coef << endl;*/
//        /*cout << "sq: " << squrt << endl;
//        cout << "div: " << divisor << endl;
//        cout << "buf: " << buffer << endl;*/
//        remainder -= buffer;
//        /* cout << "re: " << remainder<< "  " << remainder.polynomial.size() << endl;*/
//
//        while (!remainder.zero())  /*if remainder is zero means squrt is found*/
//        {
//            divisor.polynomial[divisor.polynomial.size() - 1].coef *= 2;
//            monomial.polynomial[0].expon = remainder.polynomial[0].expon - divisor.polynomial[0].expon;
//            monomial.polynomial[0].coef = remainder.polynomial[0].coef / divisor.polynomial[0].coef;
//
//            squrt += monomial;
//            /*cout << "sqin: " << squrt << endl;*/
//            divisor += monomial;
//            /*cout << "divin: " << divisor << endl;*/
//            buffer = divisor * monomial;
//            /*cout << "bufin: " << buffer << endl;*/
//            remainder -= buffer;
//            /*cout << "rein: " << remainder << endl;*/
//        }
//
//        return squrt;
//    }
//
//private:
//    vector< T1 > polynomial; // a polynomial
//
//    // Attaches a new term to the polynomial
//    void attach(T2 coefficient, T2 exponent)
//    {
//        Term< T2 > tempTerm;
//        tempTerm.coef = coefficient;
//        tempTerm.expon = exponent;
//        polynomial.insert(polynomial.end(), tempTerm);
//    }
//
//    // Returns the minus of the current polynomial
//    Polynomial operator-()
//    {
//        Polynomial minus(polynomial.size());
//        typename vector< T1 >::iterator it2 = minus.polynomial.begin();
//        typename vector< T1 >::iterator it1 = polynomial.begin();
//        for (; it1 != polynomial.end(); ++it1, ++it2)
//        {
//            it2->coef = -it1->coef;
//            it2->expon = it1->expon;
//        }
//
//        return minus;
//    }
//
//    // Returns true if and only if polynomial is a zero polynomial
//    bool zero() const
//    {
//        return polynomial.empty();
//    }
//
//    // Returns the highest of degrees of polynomial's terms
//    int degree() const
//    {
//        if (polynomial.empty())
//            return 0;
//        else
//            return polynomial.begin()->expon;
//    }
//
//}; // end class template Polynomial
//
//// Overloaded stream insertion operator
//template< typename T1, typename T2 >
//ostream& operator<<(ostream& output, Polynomial< T1, T2 > a)
//{
//    if (a.zero())
//    {
//        output << 0 << endl;
//        return output;
//    }
//
//    typename vector< T1 >::iterator it = a.polynomial.begin();
//
//    if (it->coef < 0)
//        cout << "-" << -it->coef;
//    else if (it->coef > 0)
//        cout << it->coef;
//
//    if (it->expon > 0)
//    {
//        if (it->expon == 1)
//            cout << "x";
//        else
//            cout << "x^" << it->expon;
//    }
//
//    for (++it; it != a.polynomial.end(); ++it)
//    {
//        if (it->coef < 0)
//            cout << " - " << -it->coef;
//        else if (it->coef > 0)
//            cout << " + " << it->coef;
//
//        if (it->expon > 0)
//        {
//            if (it->expon == 1)
//                cout << "x";
//            else
//                cout << "x^" << it->expon;
//        }
//    }
//
//    return output; // enables cout << x << y;
//} // end function operator<<
//
//#endif

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <cmath>
using std::sqrt;

#include "vector - 1113341 - hw5.h"

// Represents a term of a polynomial
template< typename T >
struct Term
{
    bool operator!=(const Term& right) const
    {
        return coef != right.coef || expon != right.expon;
    }

    T coef;
    T expon;
};

// Polynomial class template definition
template< typename T1, typename T2 >
class Polynomial
{
    // Overloaded stream insertion operator
    template< typename T1, typename T2 >
    friend ostream& operator<<(ostream& output, Polynomial< T1, T2 > a);
public:

    // Constructs an empty polynomial, with no terms.
    Polynomial(size_t n = 0)
        : polynomial(n)
    {
    }

    // Constructs a polynomial with a copy of each of the terms in polynomialToCopy.
    Polynomial(const Polynomial& right)
        : polynomial(right.polynomial)
    {
    }

    // Destructor with empty body
    ~Polynomial()
    {
    }

    // Copies all the terms from "right" into the polynomial
    const Polynomial operator=(const Polynomial& right)
    {
        if (&right != this) // avoid self-assignment
            polynomial = right.polynomial;

        return *this; // enables x = y = z, for example
    }

    bool operator==(const Polynomial& right)
    {
        return polynomial == right.polynomial;
    }

    void setPolynomial(T2 coefficient[], T2 exponent[], int numTerms)
    {
        for (int i = 0; i < numTerms; i++)
        {
            polynomial[i].coef = coefficient[i];
            polynomial[i].expon = exponent[i];
        }
    }

    // addition assignment operator; Polynomial += Polynomial
    void operator+=(Polynomial& op2)
    {
        Polynomial sum;
        int i = 0, j = 0, k = 0;
        while (i < polynomial.size() && j < op2.polynomial.size()) {
            if (polynomial[i].expon < op2.polynomial[j].expon) {
                sum.polynomial[k].expon = op2.polynomial[j].expon;
                sum.polynomial[k].coef = op2.polynomial[j].coef;
                j++;
                k++;
            }
            else if (polynomial[i].expon > op2.polynomial[j].expon) {
                sum.polynomial[k].expon = polynomial[i].expon;
                sum.polynomial[k].coef = polynomial[i].coef;
                i++;
                k++;
            }
            else {
                if (polynomial[i].coef + op2.polynomial[j].coef == 0)
                    i++; j++;
                continue;
            }
            sum.polynomial[k].expon = op2.polynomial[j].expon;
            sum.polynomial[k].coef = polynomial[i].coef + op2.polynomial[j].coef;
            i++; j++; k++;

        }
        while (i < polynomial.size())
        {
            sum.polynomial[k].expon = polynomial[i].expon;
            sum.polynomial[k].coef = polynomial[i].coef;
            i++;
            k++;
        }
        while (j < op2.polynomial.size())
        {
            sum.polynomial[k].expon = op2.polynomial[j].expon;
            sum.polynomial[k].coef = op2.polynomial[j].coef;
            j++;
            k++;
        }

        polynomial = sum.polynomial;

        //polynomial.size() = k;
        //for (int i = 0; i < polynomial.size; i++) // addend = sum
        //{
        //    polynomial[i].coef = sum.polynomial[i].coef;
        //    polynomial[i].expon = sum.polynomial[i].expon;
        //}

        while (polynomial.size() != 0 && polynomial[polynomial.size() - 1].coef == 0)
        {
            polynomial.erase(polynomial.end() - 1);
        }
    }


    // subtraction assignment operator; Polynomial -= Polynomial
    void operator-=(Polynomial& op2)
    {
        Polynomial minus = -op2;
        *this += minus;
    }

    // multiplication operator; Polynomial * Polynomial
    Polynomial operator*(Polynomial& op2)
    {
        Polynomial buffer;
        Polynomial product;
        if (polynomial[0].coef != 0 && op2.polynomial[0].coef != 0)
        {

            for (int i = 0; i < op2.polynomial.size(); i++)
            {
                for (int j = 0; j < polynomial.size(); j++)
                {
                    buffer.polynomial[i].expon = polynomial[polynomial.size()].expon + op2.polynomial[i].expon;
                    buffer.polynomial[i].coef = polynomial[polynomial.size()].coef * op2.polynomial[i].coef;

                    {
                        product.polynomial[i].expon += buffer.polynomial[i].expon;
                        product.polynomial[i].coef += buffer.polynomial[i].coef;
                    }
                }
            }
        }
        return product;
    }
        // computes the square root of the current polynomial
        Polynomial compSquareRoot()
        {
            Polynomial remainder(*this);
            Polynomial monomial(1);
            Polynomial divisor(polynomial.size() / 2 + 1);
            Polynomial buffer(polynomial.size());
            Polynomial squareRoot(polynomial.size() / 2 + 1);

            while (!remainder.zero()) {
                squareRoot += monomial;
                divisor += monomial;
                for (size_t i = 0; i < squareRoot.polynomial.size(); i++) {
                    buffer.polynomial[i].expon = squareRoot.polynomial[squareRoot.polynomial.size() - 1].expon + divisor.polynomial[i].expon;
                    buffer.polynomial[i].coef = squareRoot.polynomial[squareRoot.polynomial.size() - 1].coef * divisor.polynomial[i].coef;
                }
                remainder -= buffer;
            }


            return squareRoot;
        }

    private:
        vector< T1 > polynomial; // a polynomial

        // Attaches a new term to the polynomial
        void attach(T2 coefficient, T2 exponent)
        {
            Term< T2 > tempTerm;
            tempTerm.coef = coefficient;
            tempTerm.expon = exponent;
            polynomial.insert(polynomial.end(), tempTerm);
        }

        // Returns the minus of the current polynomial
        Polynomial operator-()
        {
            Polynomial minus(polynomial.size());
            typename vector< T1 >::iterator it2 = minus.polynomial.begin();
            typename vector< T1 >::iterator it1 = polynomial.begin();
            for (; it1 != polynomial.end(); ++it1, ++it2)
            {
                it2->coef = -it1->coef;
                it2->expon = it1->expon;
            }

            return minus;
        }

        // Returns true if and only if polynomial is a zero polynomial
        bool zero() const
        {
            return polynomial.empty();
        }

        // Returns the highest of degrees of polynomial's terms
        int degree() const
        {
            if (polynomial.empty())
                return 0;
            else
                return polynomial.begin()->expon;
        }

    }; // end class template Polynomial

    // Overloaded stream insertion operator
    template< typename T1, typename T2 >
    ostream& operator<<(ostream& output, Polynomial< T1, T2 > a)
    {
        if (a.zero())
        {
            output << 0 << endl;
            return output;
        }

        typename vector< T1 >::iterator it = a.polynomial.begin();

        if (it->coef < 0)
            cout << "-" << -it->coef;
        else if (it->coef > 0)
            cout << it->coef;

        if (it->expon > 0)
        {
            if (it->expon == 1)
                cout << "x";
            else
                cout << "x^" << it->expon;
        }

        for (++it; it != a.polynomial.end(); ++it)
        {
            if (it->coef < 0)
                cout << " - " << -it->coef;
            else if (it->coef > 0)
                cout << " + " << it->coef;

            if (it->expon > 0)
            {
                if (it->expon == 1)
                    cout << "x";
                else
                    cout << "x^" << it->expon;
            }
        }

        return output; // enables cout << x << y;
    } // end function operator<<
#endif