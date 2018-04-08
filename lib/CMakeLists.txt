include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

set(LIBRARY_NAME gpio)
set(SRC_FILES libgpio.c)
set(INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../include/libgpio.h)

add_library(${LIBRARY_NAME} SHARED ${SRC_FILES} ${INCLUDE_FILES})

install (TARGETS ${LIBRARY_NAME}  DESTINATION lib)
install (FILES ${INCLUDE_FILES} DESTINATION include)