/**
 * @file BigInt.h
 *
 * @author <a href="mailto:amir_hakimnejad@yahoo.com">Amirhossein Hakimnejad</a>
 * @date Feb 19, 2018
 */

#ifndef BIGNUMBER_BIGINT_H
#define BIGNUMBER_BIGINT_H
#include "Stack.h"
#include <string>
#include <iomanip>
using std::string;
class BigInt {
    friend istream& operator>> (istream &, BigInt &);
    friend ostream& operator<< (ostream &, const BigInt &);
private:
    Stack<int> bigint;
    BigInt neg() const;
    void pure();
public:
    explicit BigInt(int=10);

    BigInt(string);
    int getSize() const{return bigint.getSize();}
    int getTop() const{return bigint.getTop();}
    bool isEmpty() const{return bigint.isEmpty();}
    bool isFull() const{return bigint.isFull();}
    bool isPos() const{return *this == abs();};
    BigInt abs() const;
    int &operator [] (int n){return bigint[n];}
    int operator [] (int n)const{return bigint[n];}
    bool operator == (const BigInt &) const;
    bool operator != (const BigInt &) const;
    bool operator > (const BigInt &) const;
    bool operator <= (const BigInt &r) const{ return !(*this > r); }
    bool operator < (const BigInt &r) const{ return r > *this; }
    bool operator >= (const BigInt &r) const{ return !(*this < r); }
    const BigInt& operator = (const BigInt &);
    BigInt operator + (const BigInt &) const;
    BigInt operator + (const string) const;
    BigInt operator - (const BigInt &) const;
    BigInt operator * (BigInt &) const;
    BigInt operator / (const BigInt &) const;
    BigInt &operator ++ (int);
    const BigInt& operator += (const BigInt &r);
    const BigInt& operator += (string);
};
#endif //BIGNUMBER_BIGINT_H
