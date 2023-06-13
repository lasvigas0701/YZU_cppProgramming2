#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <cmath>
using std::sqrt;

#include "vector - Student ID - hw5.h"

// Represents a term of a polynomial
template< typename T >
struct Term
{
    bool operator!=( const Term &right ) const
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
    friend ostream &operator<<( ostream &output, Polynomial< T1, T2 > a );
public:

    // Constructs an empty polynomial, with no terms.
    Polynomial( size_t n = 0 )
        : polynomial( n )
    {
    }

    // Constructs a polynomial with a copy of each of the terms in polynomialToCopy.
    Polynomial( const Polynomial &right )
        : polynomial( right.polynomial )
    {
    }

    // Destructor with empty body
    ~Polynomial()
    {
    }

    // Copies all the terms from "right" into the polynomial
    const Polynomial operator=( const Polynomial &right )
    {
        if( &right != this ) // avoid self-assignment
            polynomial = right.polynomial;

        return *this; // enables x = y = z, for example
    }

    bool operator==( const Polynomial &right )
    {
        return polynomial == right.polynomial;
    }

    void setPolynomial( T2 coefficient[], T2 exponent[], int numTerms )
    {
        for( int i = 0; i < numTerms; i++ )
        {
            polynomial[ i ].coef = coefficient[ i ];
            polynomial[ i ].expon = exponent[ i ];
        }
    }

    // addition assignment operator; Polynomial += Polynomial
    void operator+=( Polynomial &op2 )
    {
        Polynomial sum;
        typename vector<T1>::iterator it = polynomial.begin(), it2 = op2.polynomial.begin();
        while (it < polynomial.end() && it2 < op2.polynomial.end())
        {
            if (it->expon > it2->expon)
            {
                sum.attach(it->coef, it->expon);
                it++;
            }
            else if (it->expon < it2->expon)
            {
                sum.attach(it2->coef, it2->expon);
                it2++
            }
            else
            {
                T2 coef = it->coef + it2->coef;
                if (coef)
                    sum.attach(coef, it->expon);
                it++, it2++;
            }
        }

        while (it < polynomial.end())
        {
            sum.attach(it->coef, it->expon);
            it++;
        }

        while (it2 < op2.polynomial.end())
        {
            sum.attach(it2->coef, it2->expon);
            it2++;
        }
        *this = sum;
    }

    // subtraction assignment operator; Polynomial -= Polynomial
    void operator-=( Polynomial &op2 )
    {
        Polynomial minus = -op2;
        *this += minus;
    }

    // multiplication operator; Polynomial * Polynomial
    Polynomial operator*( Polynomial &op2 )
    {
        Polynomial product;
        typename vector<T1>::iterator it = polynomial.begin();
        for (; it < polynomial.end(); it++)
        {
            typename vector<T1>::iterator it2 = op2.polynomial.begin();
            Polynomial buf;
            for (; it2 < op2.polynomial; it2++)
            {
                buf.attach(it->coef * it2->coef, it->expon + it->expon);
            }
            product += buf;
        }

        return product;
    }

    // computes the square root of the current polynomial
    Polynomial compSquareRoot()
    {
        Polynomial monomial(1);
        Polynomial remainder(*this);
        Polynomial squrt, div, buf;
        monomial[0].expon = remainder[0].expon / 2;
        monomial[0].coef = sqrt(remainder[0].coef);
        squrt += monomial;
        div += monomial;
        buf = monomial * div;
        remainder -= buf;

        while (!remainder.zero())
        {
            typename vector<T1>::iterator divEnd = div.polynomial.end() - 1;
            typename vector<T1>::iterator divBeg = div.polynomial.begin();
            typename vector<T1>::iterator reBeg = remainder.polynomial.begin() - 1;

            divEnd->coef *= 2;
            monomial[0].expon = reBeg->expon - divBeg->expon;
            monomial[0].coef = reBeg->coef / divBeg->coef;

            squrt += monomial;
            div += monomial;
            buf = monomial * div;
            remainder -= buf;
        }
    }

private:
    vector< T1 > polynomial; // a polynomial

    // Attaches a new term to the polynomial
    void attach( T2 coefficient, T2 exponent )
    {
        Term< T2 > tempTerm;
        tempTerm.coef = coefficient;
        tempTerm.expon = exponent;
        polynomial.insert( polynomial.end(), tempTerm );
    }

    // Returns the minus of the current polynomial
    Polynomial operator-()
    {
        Polynomial minus( polynomial.size() );
        typename vector< T1 >::iterator it2 = minus.polynomial.begin();
        typename vector< T1 >::iterator it1 = polynomial.begin();
        for( ; it1 != polynomial.end(); ++it1, ++it2 )
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
        if( polynomial.empty() )
            return 0;
        else
            return polynomial.begin()->expon;
    }

}; // end class template Polynomial

// Overloaded stream insertion operator
template< typename T1, typename T2 >
ostream& operator<<( ostream &output, Polynomial< T1, T2 > a )
{
    if( a.zero() )
    {
        output << 0 << endl;
        return output;
    }

    typename vector< T1 >::iterator it = a.polynomial.begin();

    if( it->coef < 0 )
        cout << "-" << -it->coef;
    else if( it->coef > 0 )
        cout << it->coef;

    if( it->expon > 0 )
    {
        if( it->expon == 1 )
            cout << "x";
        else
            cout << "x^" << it->expon;
    }

    for( ++it; it != a.polynomial.end(); ++it )
    {
        if( it->coef < 0 )
            cout << " - " << -it->coef;
        else if( it->coef > 0 )
            cout << " + " << it->coef;

        if( it->expon > 0 )
        {
            if( it->expon == 1 )
            cout << "x";
            else
            cout << "x^" << it->expon;
        }
    }

    return output; // enables cout << x << y;
} // end function operator<<

#endif