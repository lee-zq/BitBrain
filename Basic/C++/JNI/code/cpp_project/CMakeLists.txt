cmake_minimum_required(VERSION 3.5)
project(main)

# 设置编译器
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++11 -O0")

# 设置头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(/usr/local/java/jdk-17.0.5/include)
include_directories(/usr/local/java/jdk-17.0.5/include/linux)

# 设置库文件目录
link_directories(${PROJECT_SOURCE_DIR}/lib)

# 设置库输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

# 设置源文件目录
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_CPP_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/jni_impl DIR_JNI_SRCS)

aux_source_directory(${PROJECT_SOURCE_DIR}/test DIR_TEST_SRCS)

# 生成动态链接库
add_library(student SHARED ${DIR_CPP_SRCS})
add_library(jnilib SHARED ${DIR_JNI_SRCS})

add_executable(test ${DIR_TEST_SRCS})
target_link_libraries(test student)
# 动态链接库依赖
target_link_libraries(jnilib student)
