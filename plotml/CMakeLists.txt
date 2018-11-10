
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

target_include_directories( plotml
  PUBLIC  
   $<BUILD_INTERFACE:${PLOTML_SOURCE_DIR}>
   $<BUILD_INTERFACE:${PLOTML_BINARY_DIR}>
   $<INSTALL_INTERFACE:${PLOTML_INSTALL_INCLUDEDIR}>
  PRIVATE ${XercesC_INCLUDE_DIRS})

add_executable( plotml_validate  plotml_validate.cpp )
target_link_libraries( plotml_validate plotml ${XercesC_LIBRARY_RELEASE})

install( FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  ${CMAKE_CURRENT_BINARY_DIR}/plotml-binding.hpp
  ${CMAKE_CURRENT_BINARY_DIR}/plotml-binding-fwd.hpp
  plotml.hpp
  DESTINATION ${PLOTML_INSTALL_INCLUDEDIR})

install( FILES
  ${CMAKE_CURRENT_BINARY_DIR}/plotml.xsd
  DESTINATION ${PLOTML_INSTALL_SCHEMADIR})


install( TARGETS
  plotml
  EXPORT plotml_targets
  DESTINATION ${PLOTML_INSTALL_LIBDIR})

install( TARGETS
  plotml_validate
  DESTINATION ${PLOTML_INSTALL_BINDIR})

set( PLOTML_TARGETS_NAME plotml_targets.cmake)

install(
  EXPORT
    plotml_targets
  NAMESPACE
    plotml::
  FILE 
    ${PLOTML_TARGETS_NAME}
  DESTINATION
    ${PLOTML_INSTALL_CONFIGDIR})

configure_file( plotml-config.cmake.in plotml-config.cmake @ONLY)
