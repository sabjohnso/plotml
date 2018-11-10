//
// ... Standard header files
//

#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <streambuf>
#include <sstream>
#include <fstream>
#include <iostream>

//
// ... PlotML header files
//
#include <plotml/config.hpp>
#include <plotml/plotml-binding.hpp>


//
// ... Testing header files
//
#include <plotml_testing/test_macros.hpp>
#include <plotml_testing/test_config.hpp>

namespace PlotML
{
  namespace Testing {

    /** Test writing curve data */
    struct Write_curves_test
    {
      Write_curves_test() : accum( 0 ) {
	plotData_test();
      }
    
      operator int() const { return accum; }
    
    private:

    
      static Scalar1D
      make_datum( size_t index ){
	return Scalar1D( index, index*index );
      }

      static Curve2D&
      populate_curve( Curve2D& curve, size_t n ){
	auto& data = curve.d();
	data.reserve( n );
	for( size_t i = 0; i < n; ++i ){
	  data.push_back( make_datum( i ));
	}
	return curve;
      }
    
      void
      plotData_test(){
      
	auto data = PlotData( Curves());
	auto& curves = data.curves();
	curves.title( std::string( "Test Plot" ));
	curves.curve().push_back( Curve2D());


	auto& curve = curves.curve()[ 0 ];

	populate_curve( curve, 10 );
	curve.label( std::string( "Test Curve" ));

	auto xminit = std::min_element(
	  curve.d().begin(), curve.d().end(),
	  [](auto da, auto db ){ return da.x() < db.x(); });

	auto xmin = xminit->x();

	auto xmaxit = std::max_element(
	  curve.d().begin(), curve.d().end(),
	  []( auto da, auto db ){ return da.x() < db.x(); });

	auto xmax = xmaxit->x();

	PLOTML_TEST( accum, xmax > xmin );

	curves.xmin( xmin );
	curves.xmax( xmax );

	xml_schema::namespace_infomap map;
	map["plt"].name = "http://sabjohnso.github.io/2018/PlotML";
	map["plt"].schema = Config::build_schema_path;

	std::stringstream ss;
	plotData( ss, data, map );

	std::cout << std::endl << ss.str() << std::endl;

	std::ifstream inp( std::string( data_path ) + "/" + std::string( "curve1.xml" ));
	
	std::string expected(
	  (std::istreambuf_iterator<char>( inp )),
	  std::istreambuf_iterator<char>());

	PLOTML_TEST( accum,  expected == ss.str());

      }
  
      int accum;
  
    }; // end of struct Write_curves_test

  } // end of namespace Testing
} // end of namespace PlotML


int
main( int, char** )
{
  int accum = 0;
  accum += PlotML::Testing::Write_curves_test();
  return accum;
}

