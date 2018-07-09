#
# ... Build script for plotml
#

cmake_minimum_required( VERSION 3.7 )

project( PLOTML )
set( PLOTML_MAJOR 0)
set( PLOTML_MINOR 1)
set( PLOTML_UPDATE 0)
set( PLOTML_VERSION plotml-${PLOTML_MAJOR}.${PLOTML_MINOR} )
set( PLOTML_VERSION_UPDATE ${PLOTML_VERSION}.${PLOTML_UPDATE} )

option( BUILD_PLOTML_TESTING  "Build the plotml  tests" ON )
option( BUILD_PLOTML_DOCUMENTATION "Build the plotml documentation" ON )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

find_package( XercesC REQUIRED )
find_package( CodeSynthesisXSD )

include_directories( 
  ${PLOTML_SOURCE_DIR}
  ${PLOTML_BINARY_DIR}
  ${XercesC_INCLUDE_DIRS} )

if( NOT PLOTML_INSTALL_INCLUDE_DIR)
  set( PLOTML_INSTALL_INCLUDE_DIR include/plotml
    CACHE PATH "Path for installation of header files" )
endif( NOT PLOTML_INSTALL_INCLUDE_DIR)

if( NOT PLOTML_INSTALL_SCHEMA_DIR)
  set( PLOTML_INSTALL_SCHEMA_DIR share/schema
    CACHE PATH "Path for installation of schema files" )
endif( NOT PLOTML_INSTALL_SCHEMA_DIR)

if( NOT PLOTML_INSTALL_LIBRARY_DIR)
  set( PLOTML_INSTALL_LIBRARY_DIR lib
    CACHE PATH "Path for installation of library files" )
endif( NOT PLOTML_INSTALL_LIBRARY_DIR)


if( NOT PLOTML_INSTALL_BIN_DIR )
  set( PLOTML_INSTALL_BIN_DIR bin
    CACHE PATH "Path for installation of executable files" )
endif( NOT PLOTML_INSTALL_BIN_DIR )



add_subdirectory( plotml )



#
# ... Testing 
#
if( BUILD_PLOTML_TESTING )
  enable_testing()
  add_subdirectory( plotml_testing )
endif( BUILD_PLOTML_TESTING )



#
# ... Documentation
#
if( BUILD_PLOTML_DOCUMENTATION )

  configure_file( Doxyfile.in Doxyfile )

  if( NOT PLOTML_INSTALL_DOC_DIR)
    set( PLOTML_INSTALL_DOC_DIR share/doc/${PLOTML_VERSION}
      CACHE PATH "Path for installation of documentation files" )
  endif( NOT PLOTML_INSTALL_DOC_DIR)

  if( NOT PLOTML_INTALL_MAN_DIR)
    set( PLOTML_INTALL_MAN_DIR include/plotml
      CACHE PATH "Path for installation of man files" )
  endif( NOT PLOTML_INTALL_MAN_DIR)

  find_package( Doxygen REQUIRED )

  add_custom_command(
    OUTPUT ${PLOTML_BINARY_DIR}/doxygen.log
    COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile > doxygen.log
    MAIN_DEPENDENCY Doxyfile
    DEPENDS ${PLOTML_BINARY_DIR}/plotml
    WORKING_DIRECTORY ${PLOTML_BINARY_DIR} )

  add_custom_target(
    plotml_documentation ALL
    DEPENDS ${PLOTML_BINARY_DIR}/doxygen.log )

  install( DIRECTORY ${PLOTML_BINARY_DIR}/doc/html DESTINATION ${PLOTML_INSTALL_DOC_DIR} )
  install( DIRECTORY ${PLOTML_BINARY_DIR}/doc/man DESTINATION ${PLOTML_INTALL_MAN_DIR} )
endif( BUILD_PLOTML_DOCUMENTATION )

# end of build definition for plotml
