/*
 * main-stage1.cpp
 *
 * Includes the main() function for the stack project (stage 1).
 *
 * This code is included in the build target "run-stage1-main", and
 * in the convenience target "stage1".
 */

#include <iostream>

#include "stack-stage1.h"

using namespace std;

int main() {
    // You can use this main() to run your own analysis or initial testing code.
    stack stk;
    stk.push("a");
    stk.push("b");
    stk.push("c");
    cout << stk.top() << endl;
//    ASSERT_EQ(stk.top(), "c");
    stk.pop();
    cout << stk.top() << endl;
//    ASSERT_EQ(stk.top(), "b");
    stk.pop();
    cout << stk.top() << endl;
//    ASSERT_EQ(stk.top(), "a");
    return 0;
}
