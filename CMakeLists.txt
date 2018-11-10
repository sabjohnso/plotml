#
# ... Build script for plotml
#

cmake_minimum_required( VERSION 3.7 )

project( PLOTML  VERSION 0.1.0 LANGUAGES CXX )
set( PLOTML_MAJOR ${PROJECT_VERSION_MAJOR})
set( PLOTML_MINOR ${PROJECT_VERSION_MINOR})
set( PLOTML_UPDATE ${PROJECT_VERSION_PATCH})
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
  ${XercesC_INCLUDE_DIRS})

include(GNUInstallDirs)

set( PLOTML_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR}
  CACHE PATH "Path for installation of header files" )

set( PLOTML_INSTALL_SCHEMADIR ${CMAKE_INSTALL_DATAROOTDIR}/schema
  CACHE PATH "Path for installation of schema files" )

set( PLOTML_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR}
  CACHE PATH "Path for installation of library files" )

set( PLOTML_INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR}
  CACHE PATH "Path for installation of executable files" )

set( PLOTML_INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/${PLOTML_VERSION}
  CACHE PATH "Path for installation of configuration files" )


#
# ... Walk the source tree
#
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

  set( PLOTML_INSTALL_DOCDIR ${CMAKE_INSTALL_DOCDIR}
    CACHE PATH "Path for installation of documentation files" )

  set( PLOTML_INTALL_MANDIR ${CMAKE_INSTALL_MANDIR}
    CACHE PATH "Path for installation of man files" )

  install( DIRECTORY ${PLOTML_BINARY_DIR}/doc/html DESTINATION ${PLOTML_INSTALL_DOCDIR} )
  install( DIRECTORY ${PLOTML_BINARY_DIR}/doc/man DESTINATION ${PLOTML_INTALL_MANDIR} )

endif( BUILD_PLOTML_DOCUMENTATION )

# end of build definition for plotml
