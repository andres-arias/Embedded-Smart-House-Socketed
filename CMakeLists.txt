cmake_minimum_required( VERSION 2.8 )
project( Embedded-Socket-server )
add_executable( server main.c ./src/photo.c )
add_executable( client client.c )