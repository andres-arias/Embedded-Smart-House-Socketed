cmake_minimum_required( VERSION 2.8 )

project( Embedded-Socket-Server )

add_subdirectory(lib)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(houseserv main.c ./src/base64.c ./src/photo.c ./src/lights.c ./src/doors.c)

target_link_libraries(houseserv gpio)

install (TARGETS server DESTINATION bin)