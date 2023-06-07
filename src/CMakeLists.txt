set(HEADER_LIST "../include/mage.h" "../include/lexer.h")

add_library(mage STATIC mage.c lexer.c ${HEADER_LIST})
target_include_directories(mage PUBLIC ../include)
set_property(TARGET mage PROPERTY C_STANDARD 11)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
