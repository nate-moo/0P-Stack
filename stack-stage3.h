/*
 * stack-stage3.h
 *
 * Implements a simple stack class using dynamic arrays.
 * This may be implemented in 3 stages:
 *   Stage 1: non-template stack class storing strings,
 *            unsafe copies/assignments
 *   Stage 2: template stack class, unsafe copies/assignments
 *   Stage 3: template stack class, safe copies/assignments
 *
 * Note: no underflow detection is performed.  Performing pop() or top()
 * on an empty stack results in undefined behavior (possibly crashing your
 * program)!
 *
 * Author: Nate Moore
 */

#ifndef _STACK_H
#define _STACK_H

// To start stage 2, you probably want to copy all of your code from
// stack-stage1.h and stack-stage1.cpp in place of this comment.

/***
 * DO NOT put unscoped 'using namespace std;' in header files!
 * Instead use the std:: prefix where required in class definitions, as
 * demonstrated in the stack starter code for stage1.
 */

template<class T>
class stack {
public:
    T top(); // non-inline, implemented in stack-stage1.cpp

    // inline definitions, doing nothing at the moment
    void push(const T&);
    void pop();
    size_t size() const;
    bool is_empty() const;

    stack<T>() { ; }
    ~stack<T>();

private:
    T* _data = new T[4];
    size_t _capacity = 1;
    size_t _size = 0;
};

template<class T>
stack<T>::~stack<T>() {
//    for (size_t i; i < _capacity; i++) {
//        delete _data[i];
//    }

    delete[] _data;
}

template<class T>
T stack<T>::top() {
    return _data[_size - 1];
}

template<class T>
void stack<T>::push(const T& pushedVar) {
    if (_capacity > _size) {
        _data[_size] = pushedVar;
        _size++;
    } else if ( _size == _capacity ) {
        auto* _old_data = new T[_capacity];

        for (size_t i = 0; i < _capacity; i++) { _old_data[i] = _data[i]; }
        _capacity = _capacity * 2;

        delete[] _data;
        _data = new T[_capacity];

        for (size_t i = 0; i < _capacity/2; i++) { _data[i] = _old_data[i]; }

        _data[_size] = pushedVar;
        _size++;
//        printf("cap: %zu \n", _capacity);
    }
}
template<class T>
void stack<T>::pop() {
    _size--;
    _data[_size] = T();
}

template<class T>
size_t stack<T>::size() const {
    return _size;
}

template<class T>
bool stack<T>::is_empty() const {
    if (_size == 0) {
        return true;
    } else {
        return false;
    }
}

#endif
