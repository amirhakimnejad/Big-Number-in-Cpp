
//
// Created by amirhakimnejad on 2/19/18.
//

#include "BigInt.h"

BigInt::BigInt(int n){
    bigint = Stack<int> (n);
}

const BigInt& BigInt::operator = (const BigInt &r){
    bigint = bigint.operator=(r.bigint);
    return *this;
}
BigInt BigInt::operator + (const BigInt &b) const{
    BigInt c((getSize() > b.getSize() ? getSize() : b.getSize()) + 1);
    int adder = 0;
    for (int i = 1; i <= c.getSize(); i++){
        if (b.getSize() - i < 0){
            if(getSize()-i >= 0)
                adder += bigint[getSize()-i];//can i use this-> instead of ptr?
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
    return c;
}

BigInt BigInt::operator - (const BigInt &b) /*const*/{
    BigInt c((getSize() > b.getSize() ? getSize() : b.getSize()) + 1);
    std::cout << "c = " << c << endl;
    int adder = 0;
    std::cout << "adder = " << adder << endl;
    for(int i = 1; i < c.getSize(); i++){
        std::cout << "i = " << i << endl;
        adder = bigint[getSize() - i] - b[b.getSize() - i];
        std::cout << "adder = bigint[getSize() - i] - b[b.getSize() - i] = " << adder << endl;
        if (adder < 0) {
            int j = i;
            std::cout << "j = " << j << endl;
            while(getSize() - j > 0){
                std::cout << "bigint[getSize() - j]>0 = " << (bigint[getSize() - j]>0) << endl;
                if(bigint[getSize() - j] > 0){
                    std::cout << "bigint[getSize() - j]" << bigint[getSize() - j] << endl;
                    bigint[getSize() - j]--;
                    std::cout << "bigint[getSize() - j]--;" << bigint[getSize() - j]-- << endl;
                    break;
                }
                j++;
            }
            for(int k = j; k >= i; k--){
                std::cout << "k = " << k << endl;
                bigint[getSize() - k] = 9;
                std::cout << "bigint[getSize() - k] = " << bigint[getSize() - k] << endl;
                if (k == i) {
                    bigint[getSize() - k] = 10;
                    std::cout << "bigint[getSize() - k] = " << bigint[getSize() - k] << endl;
                }
            }
        }

        if (adder >= 0) {
            std::cout << "c[c.getSize() - i] = " << c[c.getSize() - i] << endl;
            c[c.getSize() - i] = adder;
            std::cout << "c[c.getSize() - i] = " << c[c.getSize() - i] << endl;
        }
    }
    std::cout << "c = " << c << endl;
    return c;
}

const BigInt &BigInt::operator += (const BigInt &r){
    *this = *this + r;
    return *this;
}

bool BigInt::operator > (const BigInt &r) const{
    if (getSize() < r.getSize())
        return false;
    else if (getSize() > r.getSize())
        return true;
    for (int i = 0; i < getSize(); i++) {
        if (bigint[i] == r[i] && i == getSize() - 1)
            return false;
        if (bigint[i] > r[i])
            return true;
        else if(bigint[i] == r[i])
            continue;
        else
            return false;
    }
    return true;
}

istream& operator>> (istream &in, BigInt &r){
    for(int i = 0; i < r.getSize(); i++) {
        in >> r[i];
    }
    return in;
}

ostream& operator<< (ostream &out, const BigInt &r){
    for(int i = 0; i < r.getSize(); i++) {
        out << r[i];
    }
    return out << endl;
}