/**
 * @file BigInt.cpp
 *
 * @author <a href="mailto:amir_hakimnejad@yahoo.com">Amirhossein Hakimnejad</a>
 * @date Feb 19, 2018
 * @date Mar 6, 2018
 */

#include "BigInt.h"
BigInt::BigInt(int n)
{
    bigint = Stack<int> (n);
}

BigInt::BigInt(string r)
{
    bigint = Stack<int> (r.length());
    for (int i = 0; i < getSize(); i++)
        bigint[i] = r[i] - '0';
}

bool BigInt::operator > (const BigInt &r) const
{
    if (getSize() > r.getSize())
        return true;
    if (getSize() < r.getSize())
        return false;
    for (int i = 0; i < r.getSize(); i++)
    {
        if (bigint[i] > r[i])
            return true;
        if (r[i] > bigint[i])
            return false;
    }
}

bool BigInt::operator == (const BigInt &r) const
{
    if (this == &r)//self assignment
        return true;
    if (getSize() != r.getSize())
        return false;
    for (int i = 0;i < getSize();i++)
        if (bigint[i] != r.bigint[i])
            return false;
    return true;
}

bool BigInt::operator != (const BigInt &r) const
{
    return !(*this == r);
}

const BigInt &BigInt:: operator += (const BigInt &r)
{
    *this = *this + r;
    return *this;
}

BigInt BigInt::operator + (const BigInt &b) const
{
    BigInt c((getSize() > b.getSize() ? getSize() : b.getSize()) + 1);
    int adder = 0;
    for (int i = 1; i <= c.getSize(); i++){
        if (b.getSize() - i < 0){
            if(getSize()-i >= 0)
                adder += bigint[getSize()-i];
            c[c.getSize()-i] = adder % 10;
            adder /= 10;
            continue;
        }
        if ((getSize() - i) < 0) {
            if(b.getSize()-i >= 0)
                adder += b[b.getSize()-i];
            c[c.getSize()-i] = adder % 10;
            adder /= 10;
            continue;
        }
        adder += (bigint[getSize()-i] + b[b.getSize()-i]);
        c[c.getSize()-i] = adder % 10;
        adder /= 10;
    }
    c.pure();
    return c;
}

const BigInt &BigInt:: operator += (string r)
{
    BigInt temp;
    temp = r;
    *this = *this + temp;
    return *this;
}

BigInt BigInt::operator + (string r) const
{
    BigInt temp;
    temp = r;
    return *this + temp;
}

BigInt &BigInt::operator ++ (int n)
{
    for (int i = 1; i <= getSize(); i++){
        if ((bigint[getSize() - i])==9) {
            bigint[getSize() - i] = 0;
            continue;
        }
        bigint[getSize() - i] += 1;
        break;
    }
    return *this;
}

void BigInt::pure()
{
    int i = 0;
    for (i; i < getSize() - 1; i++)
        if(bigint[i] != 0)
            break;
    i--;
    BigInt temp(getSize() - i - 1);
    i = 1;
    for (i; i <= temp.getSize(); i++){
        temp[temp.getSize() - i] = bigint[getSize() - i];
    }
    *this = temp;
}

BigInt BigInt::abs(void) const
{
    BigInt temp;
    temp = *this;
    for (int i = 0; i < temp.getSize() ;i++)
        if (temp[i] < 0)
            temp[i] = temp[i] * (-1);
    return temp;
}

BigInt BigInt::operator / (const BigInt &b) const
{
    BigInt i("0");
    BigInt r;
    r = *this;
    while(r >= b){
        r = r - b;
        i++;
    }
}
BigInt BigInt::operator * (BigInt &r) const
{
    BigInt a = *this;
    std::cout << "*this = " << *this << std::endl;
    std::cout << "a = " << a << std::endl;
    BigInt temp = r;
    temp.pure();
    std::cout << "temp = " << temp << std::endl;
    BigInt i("1"),j("1");
    for(i; i < r ; i += j) {
        std::cout << "i = " << i << std::endl;
        a += *this;
        std::cout << a << " += " << *this <<" = " << a << std::endl;

    }
    return a;
}

BigInt BigInt::neg() const
{
    BigInt temp;
    temp = *this;
    for (int i = 0; i < getSize(); i++)
        temp[i] *= -1;
    return temp;
}
BigInt c;
BigInt BigInt::operator - (const BigInt &r) const
{
    BigInt a;//temp of this
    a = *this;
    int s = 1;
    BigInt b = r;
    b = r;
    if(a.isPos() && !(b.isPos())) {
      return *this + b.abs();
    }
    if (!(a.isPos())&&(b.isPos()))
        return (b.abs() + a.abs()).neg();//recursive
    if (b > a){
        s *= -1;
        BigInt temp;
        temp = a;
        a = b;
        b = temp;
    }

    c = BigInt((a.getSize() > b.getSize() ? a.getSize() : b.getSize()) );
    for (int i = 1; i <= c.getSize(); i++){
        if(b.getSize()-i < 0){
            c[c.getSize()-i] = a[a.getSize()-i] * s;
            continue;
        }
        if (b[b.getSize()-i] > a[a.getSize()-i]){
            int j = i + 1;
            while (j <= c.getSize()){
                if (a[a.getSize()-j] > 0){
                    a[a.getSize()-j]--;
                    break;
                }
                j++;
            }
            for (int k = j - 1; k >= i; k--){
                if (k==i){
                    a[a.getSize()-k] += 10;
                    break;
                }
                a[a.getSize()-k] += 9;
            }
        }
        c[c.getSize()-i] = (a[a.getSize()-i] - b[b.getSize()-i]) * s;
    }
    c.pure();
    return c;
}

istream& operator>> (istream &in, BigInt &r)
{

    for(int i = 0; i < r.getSize(); i++) {
        in >> r[i];
    }
    return in;
}

ostream& operator<< (ostream &out, const BigInt &r)
{
    for(int i = 0; i < r.getSize(); i++) {
        out << r[i];
    }
    return out << endl;
}

const BigInt& BigInt::operator = (const BigInt &r)
{
    bigint = r.bigint;
    return *this;
}


