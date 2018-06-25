#ifndef TEST_MACROS_HPP_INCLUDED_2246883537166276714
#define TEST_MACROS_HPP_INCLUDED_2246883537166276714 1
//
// ... Standard header files
//
#include <iostream>



#define PLOTML_TEST_PRINT_AUX( ... ) #__VA_ARGS__
#define PLOTML_TEST_PRINT( ... ) PLOTML_TEST_PRINT_AUX( __VA_ARGS__ )

#define PLOTML_FAIL( accum, ... )				\
  {								\
    ++accum;							\
    std::cout << '\n' << __FILE__ << ':' << __LINE__ << ":0"	\
	      << " PLOTML test failure\n"			\
	      << PLOTML_TEST_PRINT( __VA_ARGS__ ) << '\n'	\
	      << " did not evaluate to true.\n\n";		\
  }
  

#define PLOTML_PASS( ... )			\
  {						\
    std::cout << '.';				\
  }
  
/** The first argument to a test is a variable 
    that is accumulating the count of test failures,
    and the rest are an expression that evaluates 
    to true to pass or false to fail. Upon failure,
    a message is printed with the location of the
    failure.  Upon success, a '.' is printed to
    indicate the successfull execution. */
#define PLOTML_TEST( accum , ... )		\
  if(!(  __VA_ARGS__ )){			\
    PLOTML_FAIL( accum, __VA_ARGS__ );		\
  }						\
  else{						\
    PLOTML_PASS( __VA_ARGS___ );		\
  }


/** Static tests use static_assert and are really only executed
    at compile time.  At runtime,  a '+' is printed to indicate
    the static test passed, but it was not actually executed at
    runtime. 
*/
#define PLOTML_STATIC_TEST( ... )				\
  {								\
    static_assert( __VA_ARGS__, "PLOTML static test failure" );	\
    std::cout << '+';						\
  }

/**  Don't run the test, just print a ? to idicated that
     the test is pending.
*/
#define PLOTML_PENDING_TEST( ... )		\
  {						\
    std::cout << '?';				\
  }
#endif // !defined TEST_MACROS_HPP_INCLUDED_2246883537166276714
