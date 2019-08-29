#include <iostream>
#include "random_access_skip_list.h"
#include "skip_list.h"
#include "test_types.h"
int main( )
{
	using goodliffe::random_access_skip_list;
        //using goodliffe::multi_skip_list;
	typedef random_access_skip_list<int,std::less<int> > IntSet;
        //typedef multi_skip_list<int, std::less<int> > IntSet;
	IntSet s1; 
	random_access_skip_list <int,std::less<int> > :: const_iterator s1_RcIter;
	//multi_skip_list <int,std::less<int> > :: const_iterator s1_RcIter;
	s1.insert( 10 );
	s1.insert( 20 );
	s1.insert( 30 );
        
	std::pair <IntSet::const_iterator, IntSet::const_iterator> p1, p2;
	
        p1 = s1.equal_range( 20 );
        
	std::cout << "The upper bound of the element with "
		<< "a key of 20 in the set s1 is: "
		<< *(p1.second) << "." << std::endl;

	std::cout << "The lower bound of the element with "
		<< "a key of 20 in the set s1 is: "
		<< *(p1.first) << "." << std::endl;

	s1_RcIter = s1.upper_bound( 20 );
	std::cout << "A direct call of upper_bound( 20 ) gives "
		<< *s1_RcIter << "," << std::endl
		<< "matching the 2nd element of the pair"
		<< " returned by equal_range( 20 )." << std::endl;
	p2 = s1.equal_range( 40 );

	if ( ( p2.first == s1.end( ) ) && ( p2.second == s1.end( ) ) )
		std::cout << "The set s1 doesn't have an element "
			<< "with a key less than 40." << std::endl;
	else
		std::cout << "The element of set s1 with a key >= 40 is: "
			<< *(p1.first) << "." << std::endl;
        
}
