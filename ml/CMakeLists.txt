cmake_minimum_required( VERSION 2.8 ) 
project( svm )

set( CMAKE_CXX_COMPILER "g++" )
set( CMAKE_BUILD_TYPE "Debug" )
set( CMAKE_CXX_FLAGS "-std=c++11 -march=native -O3" )

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin )

# OpenCV
find_package( OpenCV 3.1 REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( 0.allinone 0.allinone.cpp )
target_link_libraries( 0.allinone ${OpenCV_LIBS} )


add_executable( non_linear_svms_test non_linear_svms_test.cpp )
target_link_libraries( non_linear_svms_test ${OpenCV_LIBS} )

add_executable( 1.get_data 1.get_data.cpp )
target_link_libraries( 1.get_data ${OpenCV_LIBS} )

add_executable( 2.training_svm 2.training_svm.cpp )
target_link_libraries( 2.training_svm ${OpenCV_LIBS} )

add_executable( 3.predict 3.predict.cpp )
target_link_libraries( 3.predict ${OpenCV_LIBS} )
