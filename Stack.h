//
// Created by amirhakimnejad on 2/13/18.
//

#ifndef MY_STACK_STACK_H
#define MY_STACK_STACK_H
#include <iostream>
#include <cstdlib>

using std::istream;
using std::ostream;
using std::endl;


template <typename T> class Stack;
template <typename T> istream& operator>>(istream &, Stack<T> &);
template <typename T> ostream& operator<<(ostream &, const Stack<T> &);


template <typename T>
class Stack{
    friend class BigInt;
    friend istream& operator>> <T>(istream &, Stack<T> &);
    friend ostream& operator<< <T>(ostream &, const Stack<T> &);
private:
    T *ptr;
    int size;
    int top;
public:
    Stack(int=10);
    ~Stack();
    int getSize() const;
    int getTop() const;
    bool push(T);
    bool pop();
    bool isEmpty() const;
    bool isFull() const;
    T &operator [] (int);
    T operator [] (int)const;
    const Stack& operator = (const Stack&);
    const Stack& operator += (const Stack &);

};


template <typename T>
Stack<T>::Stack(int n){
    size = n > 0 ? n : 10;
    top = -1;
    ptr = new T[size];
    for(int i = 0; i < size; i++)
        ptr[i] = 0;
}

template <typename T>
Stack<T>::~Stack(){
    delete[] ptr;
}

template <typename T>
bool Stack<T>::push(T val){
    if(!isFull()){
        ptr[++top] = val;
        return true;
    }
    return false;
}

template <typename T>
bool Stack<T>::pop(){
    if (!isEmpty()){
        top--;
        return true;
    }
    return false;
}

template <typename T>
int Stack<T>::getSize() const{
    return size;
}

template <typename T>
int Stack<T>::getTop() const{
    return top;
}

template <typename T>
bool Stack<T>::isEmpty()const{
    return getTop() == -1;
}

template <typename T>
bool Stack<T>::isFull()const{
    return getTop() == getSize() - 1;
}
template <typename T>
T &Stack<T>::operator [] (int n) {
    if(n < 0 || n >= getSize()) {
        throw(std::out_of_range("Out of range index in stack::operator []."));
    }
    return ptr[n];
}
template <typename T>
T Stack<T>::operator [] (int n) const{
    if(n < 0 || n >= getSize()) {
        throw(std::out_of_range("Out of range index in stack::operator []."));
    }
    return ptr[n];
}

template <typename T>
const Stack<T>& Stack<T>::operator = (const Stack&r){
    if(getSize()!=r.getSize()){
        delete[] ptr;
        size = r.getSize();
        ptr = new T[size];
    }
    for(int i = 0; i < getSize(); i++)
        ptr[i] = r[i];
    return *this;
}

template <typename T>
istream &operator>> (istream &input, Stack<T> &a){
    for(int i = 0; i < a.getSize(); i++) {
        input >> a.ptr[i];
        a.top++;
    }
    return input;
}

template <typename T>
ostream& operator<< (ostream &output, const Stack<T> &a){
    for(int i = 0; i < a.getSize(); i++) {
        output << a.ptr[i];
    }
    return output << endl;
}


#endif //MY_STACK_STACK_H
