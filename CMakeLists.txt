cmake_minimum_required(VERSION 3.0)
find_package(OpenCV REQUIRED )
add_executable(GOL main.cpp )
target_link_libraries(GOL ${OpenCV_LIBS})