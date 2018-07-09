configure_file( test_config.hpp.in test_config.hpp )

macro( plotml_add_simple_test  name )
  add_executable( ${name}_test ${name}_test.cpp )
  target_link_libraries( ${name}_test plotml ${XercesC_LIBRARY_RELEASE})
  add_test( ${name} ${name}_test )
endmacro( plotml_add_simple_test  name )

plotml_add_simple_test( write_curve )
plotml_add_simple_test( read_curve )

