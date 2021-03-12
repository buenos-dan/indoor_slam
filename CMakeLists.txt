cmake_minimum_required(VERSION 3.17)
project(indoor_slam)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV 3 REQUIRED)

include_directories(
        ${OpenCV_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/include
        "/usr/local/include/eigen3"
)

add_executable(indoor_slam
        examples/stereo_kitti_test.cpp
        src/Tracker.cpp
        src/Frame.cpp
        src/StereoFrame.cpp
        src/Camera.cpp
        )
target_link_libraries(indoor_slam ${OpenCV_LIBS})