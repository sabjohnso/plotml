
set( PLOTML_SCHEMA_NAME plotml.xsd )

configure_file( config.hpp.in config.hpp )
configure_file( xsdcxx-options.in xsdcxx-options )
configure_file( plotml.xsd.in ${PLOTML_SCHEMA_NAME} )

set( XSDEXE xsdcxx )
set( XSDFLAGS
--std c++11
--include-prefix plotml/
--hxx-suffix -binding.hpp
--cxx-suffix -binding.cpp
--fwd-suffix -binding-fwd.hpp
--generate-serialization
--generate-ostream
--generate-doxygen
--generate-comparison
--generate-from-base-ctor
--generate-forward
--omit-default-attributes )


add_custom_target( data_binding ALL )
add_custom_command(
  OUTPUT plotml-binding.hpp plotml-binding.cpp plotml-binding-fwd.hpp
  COMMAND ${XSDEXE} cxx-tree ${XSDFLAGS} plotml.xsd
  MAIN_DEPENDENCY ${CMAKE_CURRENT_BINARY_DIR}/plotml.xsd
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/xsdcxx-options
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})


add_library( plotml SHARED
  plotml-binding.cpp
  plotml-binding.hpp
  plotml-binding-fwd.hpp )

target_link_libraries( plotml ${XercesC_LIBRARY_RELEASE})


install( FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  ${CMAKE_CURRENT_BINARY_DIR}/plotml-binding.hpp
  ${CMAKE_CURRENT_BINARY_DIR}/plotml-binding-fwd.hpp
  plotml.hpp
  DESTINATION ${PLOTML_INSTALL_INCLUDE_DIR})

install( FILES
  ${CMAKE_CURRENT_BINARY_DIR}/plotml.xsd
  DESTINATION ${PLOTML_INSTALL_SCHEMA_DIR})

install( TARGETS plotml
  DESTINATION ${PLOTML_INSTALL_LIBRARY_DIR})
