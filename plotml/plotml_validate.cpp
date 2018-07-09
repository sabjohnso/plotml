//
// ... Standard header files
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

//
// ... PlotML header files
//
#include <plotml/config.hpp>
#include <plotml/plotml-binding.hpp>








namespace PlotML
{
  using std::vector;
  using std::string;
  using std::copy_n;
  using std::ifstream;
  using std::runtime_error;
  
  using Arguments = vector<string>;

  Arguments
  make_arguments( int argc, char** argv ){
    Arguments result(argc);
    copy_n( argv, argc, begin( result ));
    return result;
  }

  

  class Driver {
  public:
    Driver( Arguments cmdline_args ) : args( cmdline_args ){
      validate_arguments();
      // ifstream inp( args[ 1 ]);      
      plotData( args[ 1 ]);
    }

    /** 
     * @brief Coercion to an int as zero for success.
     */
    operator int(){ return 0; }
    
  private:

    void
    usage(){ std::cerr << "plotml_validate <file-name>" << std::endl; }
    
    
    void
    validate_arguments(){
      if( args.size() != 2 ){
	usage();
	throw runtime_error( "Invalid usage" );
      }
    }
    Arguments args;
  };


  class Error_handler{
    enum class error {
      none,
      unexpected,
      xml_schema
    };
  public:
    Error_handler() : signal( error::unexpected ) {
      try{
	auto eptr = std::current_exception();
	std::rethrow_exception( eptr );
      }      
      catch( xml_schema::exception& e ){
	signal = error::xml_schema;
	std::cerr << std::endl
		  << "xml_schema::exception: " << std::endl
		  << e << std::endl
		  << "what: " << e.what() << std::endl; 
      }
      catch( std::exception& e ){
	std::cerr << "Unexpected exception: " << std::endl
		  << e.what() << std::endl;
      }
    }

    operator int() const& { return int( signal ); }
    
  private:
    error signal;
  }; // end of class Error_handler

} // end of namespace PlotML


int
main( int argc, char**argv ){
  
  using PlotML::make_arguments;
  using PlotML::Driver;
  using PlotML::Error_handler;
  
  try{ return Driver( make_arguments( argc, argv )); }
  catch( ... ){ return Error_handler(); }
}
