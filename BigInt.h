//
// Created by amirhakimnejad on 2/19/18.
//

#ifndef BIGINT_H
#define BIGINT_H
#include "Stack.h"

class BigInt {
    friend istream& operator>> (istream &, BigInt &);
    friend ostream& operator<< (ostream &, const BigInt &);
private:
    Stack<int> bigint;
public:
    BigInt(int=10);
    int getSize() const{return bigint.getSize();}
    int getTop() const{return bigint.getTop();}
    bool isEmpty() const{return bigint.isEmpty();}
    bool isFull() const{return bigint.isFull();}
    int &operator [] (int n){return bigint[n];}
    int operator [] (int n)const{return bigint[n];}
    bool operator > (const BigInt &) const;
    bool operator <= (const BigInt &r) const{ return !(*this > r); }
    bool operator < (const BigInt &r) const{ return r > *this; }
    bool operator >= (const BigInt &r) const{ return !(*this < r); }
    const BigInt& operator = (const BigInt &);
    BigInt operator + (const BigInt &) const;
    const BigInt& operator += (const BigInt &r);
};
#endif //BIGINT_H
