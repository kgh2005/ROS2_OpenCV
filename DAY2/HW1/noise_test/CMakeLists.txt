cmake_minimum_required(VERSION 3.0)
project(noise_test)

find_package(OpenCV REQUIRED)


add_executable(noise_test src/noise_test.cpp)
target_link_libraries(noise_test ${OpenCV_LIBS})
