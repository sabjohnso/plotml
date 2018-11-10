//
// ... Standard header files
//
#include <string>
#include <fstream>


//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... PlotML header files
//
#include <plotml/plotml-binding.hpp>


//
// ... Testing header files
//
#include <plotml_testing/test_macros.hpp>
#include <plotml_testing/test_config.hpp>

namespace PlotML
{
  namespace Testing
  {

    /** Test reading a curve */
    struct Read_curve_test
    {
      Read_curve_test() : accum( 0 ) {
	std::ifstream is( std::string( data_path ) + "/" + std::string( "curve1.xml" ));
	auto data = plotData( is );
	PLOTML_TEST( accum, data );

	auto& curves = data->curves();
	PLOTML_TEST( accum, curves.title());
	PLOTML_TEST( accum,  *curves.title() == "Test Plot" );

	PLOTML_TEST( accum, curves.xmin());
	PLOTML_TEST( accum, *curves.xmin() == 0 );

	PLOTML_TEST( accum, curves.xmax() );
	PLOTML_TEST( accum, *curves.xmax() == 9 );
	
	auto& curve_sequence = curves.curve();
	PLOTML_TEST( accum, curve_sequence.size() == 1 );
	

	//auto& curve = data->curves().curve()[ 0 ];
	
	

	

      }
      operator int() const { return accum; }
      int accum;
    }; // end of struct Read_curve_test

    
  } // end of namespace Testing
} // end of namespace PlotML

TEST( read_curve, basic )
{
  int accum = 0;
  accum += PlotML::Testing::Read_curve_test();
  EXPECT_EQ( accum, 0 );
}
