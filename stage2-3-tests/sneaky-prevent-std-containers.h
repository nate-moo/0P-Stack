/**
 *  Defines template a specialization for containers with random accesss iterators
 *  (deque, array, string) and the priority_queue<T>.  This prevents them from 
 *  being used explicity (priority_queue) or as a backend (make_heap).
**/

#include <array>
#include <deque>
#include <list>
#include <map>
#include <vector>

#ifndef SNEAKY_PREVENT_STD_CONTAINERS_H
#define SNEAKY_PREVENT_STD_CONTAINERS_H

namespace sneaky_prevent_std_containers {
struct sneaky_t;
struct internal_sneaky_t {
    internal_sneaky_t() { _x = -1; }
    internal_sneaky_t(wchar_t x) { _x = x; }
    bool operator<(const internal_sneaky_t& b) const { return _x < b._x; }
    bool operator>(const internal_sneaky_t& b) const { return _x > b._x; }
    bool operator==(const internal_sneaky_t& b) const { return _x == b._x; }
	operator sneaky_t() const;
	operator const sneaky_t&() const;
    wchar_t _x;
	virtual void make_it_polymorphic() const {}
	virtual ~internal_sneaky_t() {}
};

struct sneaky_t : public internal_sneaky_t {
	sneaky_t() {}
	sneaky_t( const internal_sneaky_t& s ) : internal_sneaky_t(s._x) { }
	sneaky_t( const sneaky_t& s ) : internal_sneaky_t(s.internal_sneaky_t::_x) { }
    sneaky_t(wchar_t x) : internal_sneaky_t(x) {} 
    bool operator<(const sneaky_t& b) const { return internal_sneaky_t::operator<(b); }
    bool operator>(const sneaky_t& b) const { return internal_sneaky_t::operator>(b); }
    bool operator==(const sneaky_t& b) const { return internal_sneaky_t::operator==(b); }
	sneaky_t& operator=( const sneaky_t& r ) { this->_x = r._x; return *this; }
	static void set_test_failure( const char* const n );
	static bool get_test_passed() { return test_passed; }
	private:
	static bool test_passed;
};

internal_sneaky_t::operator sneaky_t() const 
{
	return sneaky_t( _x );
}

internal_sneaky_t::operator const sneaky_t&() const 
{
	return dynamic_cast<const sneaky_t&>(*this);
}

bool sneaky_t::test_passed = true;

void sneaky_t::set_test_failure( const char* const n )
{
	if( !test_passed ) return;
	std::cerr << std::endl;
	std::cerr << "Please don't use std::"<< n << " or it's variants to satisfy the Stack project's requirements." << std::endl;
	std::cerr << "Implement a Stack using dynamically allocated memory (new[]) as specified in the project write-up." << std::endl << std::endl;
	test_passed = false; 
}

// so sneaky_ts can be printed in debug code (without this, students
// simply get build errors)
static inline std::ostream& operator<<( std::ostream& os, const sneaky_t& soo )
{
	const internal_sneaky_t& s(soo);
	return os << "st(" << s._x  << ")" ;
}

} // namespace

#define SNEAKY_T sneaky_prevent_std_containers::sneaky_t
#define INTERNAL_T sneaky_prevent_std_containers::internal_sneaky_t

namespace std {

/***
 * < IMPORTANT >
 ****************
 1. keep in mind we aren't really interested in the correctness of the subclass
 instantiation with respect to ctor arguments, we just want to get past
 compiler errors and flag failure on construction

 2. at least one other very similarly organized prevent-std-containers sneaky header
 file consists in the repo, and updating these when we switch C++ base line spec (11, 14, 17, ..)
 will be a real PiA.  Keep the template specializations in alphabetical order, so that
 when fixes or updates *do* occur, they can be easily merged to and fro different programming
 projects.  compare by *template name*, not header name.  So its:  array, basic_string, deque, ...
 */
	
/***
 * (basic_string)
 * turns out you can't make a basic_string from sneaky_t because sneaky_t
 * fails the compilers' "standard layout test", I suspect because it is polymorphic,
 * for string backing for make_heap has to fail at compile time and provide
 * a much uglier message to students --- then again students that are making strings
 * out of the sorting input vector elements might deserve this, because, well,
 * why else would they be doing this?
 */

template <size_t Size>
struct array<SNEAKY_T, Size> : public std::array<INTERNAL_T,Size> {
	array(): std::array<INTERNAL_T,Size>() { SNEAKY_T::set_test_failure("array"); }
};

template<class Allocator>
struct deque<SNEAKY_T,Allocator> : public std::deque<INTERNAL_T> {
	typedef std::deque<INTERNAL_T>::size_type size_type;
	typedef std::deque<INTERNAL_T>::iterator iterator;
	deque() : std::deque<INTERNAL_T>() { SNEAKY_T::set_test_failure("deque"); }
	deque( size_type Size ) : std::deque<INTERNAL_T>(Size) { SNEAKY_T::set_test_failure("deque"); }
	explicit deque( const Allocator& ) : std::deque<INTERNAL_T>() { SNEAKY_T::set_test_failure("deque"); }
	deque( size_type Size, const SNEAKY_T&, const Allocator& ) 
		: std::deque<INTERNAL_T>(Size) { SNEAKY_T::set_test_failure("deque"); }
//	iterator end()       { SNEAKY_T::set_test_failure("deque"); return this->std::deque<INTERNAL_T>::end(); }
//	iterator end() const { SNEAKY_T::set_test_failure("deque"); return this->std::deque<INTERNAL_T>::end(); }
};



template<class Allocator>
struct list<SNEAKY_T,Allocator> : public std::list<INTERNAL_T> {
	typedef std::list<INTERNAL_T>::size_type size_type;
	list() : std::list<INTERNAL_T>() { SNEAKY_T::set_test_failure("list"); }
	explicit list( const Allocator& ) : std::list<INTERNAL_T>() { SNEAKY_T::set_test_failure("list"); }
#if __cplusplus < 201100L
	list( size_type Size, const SNEAKY_T& = SNEAKY_T(), const Allocator& = Allocator() ) 
		: std::list<INTERNAL_T>(Size) { SNEAKY_T::set_test_failure("list"); }
#else
	list( size_type Size, const SNEAKY_T&, const Allocator& = Allocator() ) 
		: std::list<INTERNAL_T>(Size) { SNEAKY_T::set_test_failure("list"); }
#endif
#if __cplusplus >= 201100L && __cplusplus < 201400L
	list( size_type Size ) : std::list<INTERNAL_T>(Size) { SNEAKY_T::set_test_failure("list"); }
#else
	list( size_type Size, const Allocator& = Allocator() ) 
		: std::list<INTERNAL_T>(Size) { SNEAKY_T::set_test_failure("list"); }
#endif
};


template<class Key, class Compare, class Allocator>
struct map<Key,SNEAKY_T,Compare,Allocator> : public std::map<Key,INTERNAL_T> {
#if __cplusplus < 201100L
	map() : std::map<Key,INTERNAL_T>() { SNEAKY_T::set_test_failure("map"); }
#else 
	map() : std::map<Key,INTERNAL_T>() { SNEAKY_T::set_test_failure("map"); }
#endif
	explicit map( const Compare&, const Allocator& = Allocator() ) 
		: std::map<Key,INTERNAL_T>() { SNEAKY_T::set_test_failure("map"); }
#if __cplusplus >= 201100L
	explicit map( const Allocator& ) : std::map<Key,INTERNAL_T>() { SNEAKY_T::set_test_failure("map"); }
#endif
};

template<class Allocator>
struct vector<SNEAKY_T,Allocator> : public std::vector<INTERNAL_T> {
	typedef std::vector<INTERNAL_T>::size_type size_type;
#if __cplusplus < 201700L
	vector() : std::vector<INTERNAL_T>() { SNEAKY_T::set_test_failure("vector"); }
	vector( const Allocator& ) : std::vector<INTERNAL_T>() { SNEAKY_T::set_test_failure("vector"); }
#else
	vector() noexcept(noexcept(Allocator())): std::vector<INTERNAL_T>() { SNEAKY_T::set_test_failure("vector"); }
	explicit vector( const Allocator& ) noexcept : std::vector<INTERNAL_T>() { SNEAKY_T::set_test_failure("vector"); }
#endif
#if __cplusplus < 201100L
	vector( size_type Size, const SNEAKY_T& = SNEAKY_T(), const Allocator& = Allocator() ) 
		: std::vector<INTERNAL_T>(Size) { SNEAKY_T::set_test_failure("vector"); }
#else
	vector( size_type Size, const SNEAKY_T&, const Allocator& = Allocator() ) 
		: std::vector<INTERNAL_T>(Size) { SNEAKY_T::set_test_failure("vector"); }
#endif
#if __cplusplus >= 201100L && __cplusplus < 201400L
	vector( size_type Size ) : std::vector<INTERNAL_T>(Size) { SNEAKY_T::set_test_failure("vector"); }
#else
	vector( size_type Size, const Allocator& = Allocator() ) 
		: std::vector<INTERNAL_T>(Size) { SNEAKY_T::set_test_failure("vector"); }
#endif
};


} // end namespace std
  
#undef SNEAKY_T
#undef INTERNAL_T
 
 
TEST(ProjectRequirements, PreventStdContainers) {
	using namespace std;
	using namespace sneaky_prevent_std_containers;
    // create stack with specialized type 
    stack<sneaky_t> stack;

	// we don't need to perform i/o on the stack object to trigger a test failure,
	// but this assures us that things do work correctly for the sneaky_t object
	stack.push( sneaky_t(3) );
	stack.push( sneaky_t(4) );
	stack.push( sneaky_t(5) );
	stack.pop( );
	stack.pop( );
	stack.pop( );
	   
    ASSERT_TRUE(sneaky_t::get_test_passed());
}

#endif
