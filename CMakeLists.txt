cmake_minimum_required(VERSION 3.18)
project(SnakeGame)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 寻找 OpenCV 库
find_package(OpenCV REQUIRED)

# 添加可执行文件
add_executable(${PROJECT_NAME} main.cpp)

# 链接 OpenCV 库
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/utf-8")
endif()