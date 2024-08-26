/***
 * sneaky-prevent-std-copy.h:  check that students have used their own sort 
 * implementation and not std::sort
 */

#include <iostream>
#include <algorithm>

#ifndef SNEAKY_PREVENT_STD_COPY_H_H
#define SNEAKY_PREVENT_STD_COPY_H_H

namespace sneaky_psc {

struct psc_object {
    psc_object() { _x = -1; }
    psc_object(int x) { _x = x; }
    int _x;
	static void set_psc_failure( const char* const n );
	static bool get_passed() { return passed; }
	private: 
	static bool passed;
};

bool psc_object::passed = true;

// so psc_object can be printed in debug code (without this, students
// simply get build errors)
static inline std::ostream& operator<<( std::ostream& os, const psc_object& psc )
{
	return os << "psc(" << psc._x  << ")" ;
}

void psc_object::set_psc_failure( const char* const n ) 
{ 
	/***
	 * No, this output is not buggy.  Turns out on at least one common CPP library distribution
	 * all four sorting routines lead to standard sort.
	 */
	if( ! psc_object::passed ) return;
	psc_object::passed = false;
	std::cerr << std::endl;
	std::cerr << "Please don't use std::"<< n << " or it's variants to satisfy this project's"
				 "stack growing requirements." << std::endl;
	std::cerr << "Implement Stack as specified in the project write-up." << std::endl << std::endl;
	//::exit(1);
}
} // namespace sneaky_psc

namespace std {
/***
 * template specializations
 * we don't need to provide constexpr (return value) specializations for sort because
 * since we invoke it from the SneakyStudentSort TEST we know the arguments are
 * not themselves constexpr.
 */
#if __cplusplus < 202000L
// until C++ 20
#define SN_CONSTEXPR
#else
// since C++ 20
#define SN_CONSTEXPR constexpr
#endif

// specializations of std::...
template<>
SN_CONSTEXPR sneaky_psc::psc_object*
copy(sneaky_psc::psc_object* first, sneaky_psc::psc_object* last, sneaky_psc::psc_object* result )
{
	sneaky_psc::psc_object::set_psc_failure( "copy" );
	while( first != last ) {
		*result = *first;
		first++;
		result++;
	}
	return result;
}

template<>
SN_CONSTEXPR sneaky_psc::psc_object*
copy_backward(sneaky_psc::psc_object* first, sneaky_psc::psc_object* last, sneaky_psc::psc_object* result)
{
	sneaky_psc::psc_object::set_psc_failure( "copy_backward" );
	while( first != last ) {
		*(--result) = *(--last);
	}
	return result;
}

template<>
SN_CONSTEXPR sneaky_psc::psc_object*
reverse_copy(sneaky_psc::psc_object* first, sneaky_psc::psc_object* last, sneaky_psc::psc_object* result )
{
	sneaky_psc::psc_object::set_psc_failure( "reverse_copy" );
	while( first != last ) {
		*result = *(--last);
	}
	return result;
}



#undef SN_CONSTEXPR
} // namespace std

#define LARGE_STACK_SIZE 10000

TEST(ProjectRequirements, SneakyPreventStdCopy) {
	// use a large stack because students may have avoided small 
	// stack copies (permitted)
	stack<sneaky_psc::psc_object> s;
    for (int i = 0; i < LARGE_STACK_SIZE; i++) {
        s.push(sneaky_psc::psc_object(i));
    }
    ASSERT_TRUE(sneaky_psc::psc_object::get_passed());
}

#endif
