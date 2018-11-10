configure_file( test_config.hpp.in test_config.hpp )

function( plotml_add_test )
  set( optkeys "")
  set( valkeys NAME EXENAME)
  set( multikeys SOURCE_FILES DEPENDENCIES)
  cmake_parse_arguments( TEST "${optkeys}" "${valkeys}" "${multikeys}" ${ARGN})

  add_executable( ${TEST_EXENAME} ${TEST_SOURCE_FILES})
  if( TEST_DEPENDENCIES )
    target_link_libraries( ${TEST_EXENAME} ${TEST_DEPENDENCIES})
  endif()
  add_test( ${TEST_NAME} ${TEST_EXENAME})
  
endfunction()

plotml_add_test( NAME write_curve EXENAME write_curve_test
  SOURCE_FILES write_curve_test.cpp
  DEPENDENCIES plotml google::test_main )

plotml_add_test( NAME read_curve EXENAME read_curve_test
  SOURCE_FILES read_curve_test.cpp
  DEPENDENCIES plotml google::test_main )
