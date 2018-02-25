
//
// Created by amirhakimnejad on 2/19/18.
//

#include "BigInt.h"



/*BigInt BigInt::abs(void) const {
    BigInt temp = *this;
    std::cout << "temp created" << std::endl;
    for (int i = 0; i < temp.getSize() ; i++)
        if (temp[i] < 0)
            temp[i] = temp[i] * (-1);
    return temp;
}*/


BigInt BigInt::operator * (BigInt &r) const{
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



BigInt BigInt::operator - (const BigInt &b) const{
    BigInt a = *this;//temp of this
    /*
    BigInt b = r;//temp of r
    if (b > a){
        BigInt temp = a;
        std::cout << "temp = a = " << temp << endl;
        a = b;
        std::cout << "a = b = " << a << endl;
        b = temp;
        std::cout << "b = temp = " << b << endl;
    }
    if (!(a.isPos())&&(b.isPos())){
        return b.abs() - a.abs();//recursive
    }

    if(a[0] >= 0 && !(b[0] < 0))
        return *this + b.abs();
    */
    BigInt c((getSize() > b.getSize() ? getSize()  : b.getSize()) );
    std::cout << "c = " << c << endl;
    for (int i = 1; i <= c.getSize(); i++){
        std::cout << "i = " << i << endl;
        if(b.getSize()-i < 0){
            c[c.getSize()-i] = a[a.getSize()-i];
            continue;
        }
        if (b[b.getSize()-i] > a[a.getSize()-i]){
            int j = i + 1;
            std::cout << "j = " << c << endl;
            while (j <= c.getSize()){
                if (a[a.getSize()-j] > 0){
                    a[a.getSize()-j]--;
                    break;
                }
                j++;
            }
            for (int k = j - 1; k >= i; k--){
                std::cout << "k = " << k << endl;
                if (k==i){
                    a[a.getSize()-k] += 10;
                    break;
                }
                a[a.getSize()-k] += 9;
            }
        }
        c[c.getSize()-i] = a[a.getSize()-i] - b[b.getSize()-i];
        std::cout << "c = " << c << endl;
    }
    c.pure();
    return c;
}

istream& operator>> (istream &in, BigInt &r){

    for(int i = 0; i < r.getSize(); i++) {
        in >> r[i];
    }
    return in;
}

ostream& operator<< (ostream &out, const BigInt &r){
    //int s = 1;
    //if(!r.isPos()) {
    //    s = -1;
    //    out << '-';
    //}
    for(int i = 0; i < r.getSize(); i++) {
        out << r[i] /* * s*/;
    }
    return out << endl;
}


//Works perfectly ----------------------------------------------------
BigInt::BigInt(int n){
    bigint = Stack<int> (n);
}

BigInt::BigInt(string r){
    bigint = Stack<int> (r.length());
    for (int i = 0; i < getSize(); i++)
        bigint[i] = r[i] - '0';
}

BigInt::~BigInt() {std::cout << "\n\ndes runs\n\n";}

const BigInt& BigInt::operator = (const BigInt &r){
    bigint = bigint.operator=(r.bigint);
    return *this;
}

const BigInt &BigInt:: operator = (const string r){
    Stack<int> temp(r.length());
    for (int i = 0; i < temp.getSize(); i++)
        temp[i] = r[i] - '0';
    bigint = temp;
    return *this;
}

bool BigInt::operator > (const BigInt &r) const{
    //if(getSize() > r.getSize())
    //    return true;
    //if(getSize() < r.getSize())
    //    return false;
    for (int i = 0; i < r.getSize(); i++) {
        return bigint[i] > r[i] ? true : false;
    }
}

bool BigInt::operator == (const BigInt &r) const{
    if (this == &r)//self assignment
        return true;
    if (getSize() != r.getSize())
        return false;
    for (int i = 0;i < getSize();i++)
        if (bigint[i]!=r[i])
            return false;
    return true;
}

bool BigInt::operator != (const BigInt &r) const{
    return !(*this == r);
}

const BigInt &BigInt:: operator += (const BigInt &r){
    *this = *this + r;
    return *this;
}

BigInt BigInt::operator + (const BigInt &b) const{
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

const BigInt &BigInt:: operator += (string r){
    BigInt temp = r;
    *this = *this + temp;
    return *this;
}

BigInt BigInt::operator + (string r) const{
    BigInt temp = r;
    return *this + temp;
}

BigInt &BigInt::operator ++ (int n){
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

void BigInt::pure(){
    int i = 0;
    for (i; i < getSize(); i++){
        if(bigint[i] != 0)
            break;
    }
    i--;
    BigInt temp(getSize() - i - 1);
    i = 1;
    for (i; i <= temp.getSize(); i++){
        temp[temp.getSize() - i] = bigint[getSize() - i];
    }
    *this = temp;
}