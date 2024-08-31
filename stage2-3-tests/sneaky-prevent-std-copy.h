/***
 * sneaky-prevent-std-copy.h:  check that students have used their own sort 
 * implementation and not std::sort
 */

#include <iostream>
#include <algorithm>

#ifndef SNEAKY_PREVENT_STD_COPY_H_H
#define SNEAKY_PREVENT_STD_COPY_H_H

namespace sneaky_prevent_std_copy {

struct sneaky_t {
    sneaky_t() { _x = -1; }
    sneaky_t(int x) { _x = x; }
    int _x;
	static void set_failure( const char* const n );
	static bool get_passed() { return passed; }
	private: 
	static bool passed;
};

bool sneaky_t::passed = true;

// so sneaky_t can be printed in debug code (without this, students
// simply get build errors)
static inline std::ostream& operator<<( std::ostream& os, const sneaky_t& psc )
{
	return os << "psc(" << psc._x  << ")" ;
}

void sneaky_t::set_failure( const char* const n ) 
{ 
	/***
	 * No, this output is not buggy.  Turns out on at least one common CPP library distribution
	 * all four sorting routines lead to standard sort.
	 */
	if( ! sneaky_t::passed ) return;
	sneaky_t::passed = false;
	std::cerr << std::endl;
	std::cerr << "Please don't use std::"<< n << " or it's variants to satisfy this project's"
				 "stack growing requirements." << std::endl;
	std::cerr << "Implement Stack as specified in the project write-up." << std::endl << std::endl;
	//::exit(1);
}
} // namespace sneaky_prevent_std_copy

#define SNEAKY_T sneaky_prevent_std_copy::sneaky_t

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
#define SN_CONSTEXPR // constexpr
#endif

// specializations of std::...
template<>
SN_CONSTEXPR SNEAKY_T*
copy(SNEAKY_T* first, SNEAKY_T* last, SNEAKY_T* result )
{
	SNEAKY_T::set_failure( "copy" );
	while( first != last ) {
		*result = *first;
		first++;
		result++;
	}
	return result;
}

template<>
SN_CONSTEXPR SNEAKY_T*
copy_backward(SNEAKY_T* first, SNEAKY_T* last, SNEAKY_T* result)
{
	SNEAKY_T::set_failure( "copy_backward" );
	while( first != last ) {
		*(--result) = *(--last);
	}
	return result;
}

template<>
SN_CONSTEXPR SNEAKY_T*
reverse_copy(SNEAKY_T* first, SNEAKY_T* last, SNEAKY_T* result )
{
	SNEAKY_T::set_failure( "reverse_copy" );
	while( first != last ) {
		*result = *(--last);
	}
	return result;
}

#undef SN_CONSTEXPR
#undef SNEAKY_T

} // namespace std

#define LARGE_STACK_SIZE 10000

TEST(ProjectRequirements, SneakyPreventStdCopy) {
	using namespace sneaky_prevent_std_copy;
	// use a large stack because students may have avoided small 
	// stack copies (permitted)
	stack<sneaky_prevent_std_copy::sneaky_t> s;
    for (int i = 0; i < LARGE_STACK_SIZE; i++) {
        s.push(sneaky_prevent_std_copy::sneaky_t(i));
    }
    ASSERT_TRUE(sneaky_prevent_std_copy::sneaky_t::get_passed());
}

#endif
