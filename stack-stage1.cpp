/*
 * stack-stage1.cpp
 *
 * Method definitions for the stack implementation (stage 1).
 *
 * Author: Your Name
 */

#include "stack-stage1.h"

using namespace std;

//template<class T>
//T stack::top() {
//    return _data[_size - 1];
//}
//
//template<class T>
//void stack::push(const T& pushedVar) {
//    if (_capacity > _size) {
//        _data[_size] = pushedVar;
//        _size++;
//    } else if ( _size == _capacity ) {
//        auto* _old_data = new T[_capacity];
//
//        for (size_t i = 0; i < _capacity; i++) { _old_data[i] = _data[i]; }
//        _capacity = _capacity * 2;
//
//        delete[] _data;
//        _data = new T[_capacity];
//
//        for (size_t i = 0; i < _capacity/2; i++) { _data[i] = _old_data[i]; }
//
//        _data[_size] = pushedVar;
//        _size++;
////        printf("cap: %zu \n", _capacity);
//    }
//}

void stack::pop() {
    _size--;
    _data[_size] = "";
}

size_t stack::size() const {
    return _size;
}

bool stack::is_empty() const {
    if (_size == 0) {
        return true;
    } else {
        return false;
    }
}
