cmake_minimum_required(VERSION 3.0)
project(filter_test)

find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    include
)

add_executable(filter src/filter.cpp)
target_link_libraries(filter ${OpenCV_LIBS})
