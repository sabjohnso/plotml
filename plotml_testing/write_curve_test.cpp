//
// ... Standard header files
//
#include <iterator>
#include <algorithm>
#include <vector>

//
// ... PlotML header files
//
#include <plotml/config.hpp>
#include <plotml/plotml-binding.hpp>


//
// ... Testing header files
//
#include <plotml_testing/test_macros.hpp>

namespace PlotML
{

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
      curves.curve().push_back( Curve2D());

      auto& curve = curves.curve()[ 0 ];

      populate_curve( curve, 10 );
      

      xml_schema::namespace_infomap map;
      map["plt"].name = "http://sabjohnso.github.io/2018/PlotML";
      map["plt"].schema = Config::build_schema_path;
      
      plotData( std::cout, data, map );
      
      
      
    }
  
    int accum;
  
    }; // end of struct Write_curves_test  
} // end of namespace PlotML

int
main( int, char** )
{
  int accum = 0;
  accum += PlotML::Write_curves_test();
  return accum;
}
