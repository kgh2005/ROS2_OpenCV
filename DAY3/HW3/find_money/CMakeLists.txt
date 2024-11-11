cmake_minimum_required(VERSION 3.0)
project(find_money)

find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    include
)

add_executable(find_money src/find_money.cpp)
target_link_libraries(find_money ${OpenCV_LIBS})
