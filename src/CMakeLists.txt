set(HEADER_LIST "../include/mage.h" "../include/lexer.h")

add_library(mage STATIC mage.c lexer.c ${HEADER_LIST})
target_include_directories(mage PUBLIC ../include)
set_property(TARGET mage PROPERTY C_STANDARD 11)
set_property(TARGET mage PROPERTY C_STANDARD_REQUIRED 11)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})

option(BUILD_DOCS "Build documentation with doxygen" ON)
find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(DOXYGEN_IN Doxyfile)
  set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/docs/doxygen_docs/Doxyfile)

  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
  message("Started Doxygen build")

  add_custom_target(
    doxygen_docs ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    VERBATIM)
else(DOXYGEN_FOUND)
  message("Doxygen was not found - cannot build documentation")
endif(DOXYGEN_FOUND)
