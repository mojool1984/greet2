cmake_minimum_required(VERSION 3.10)

project(app LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    main.cpp
)

find_package(greet2 CONFIG REQUIRED PATHS "${CMAKE_CURRENT_LIST_DIR}/../install")

target_link_libraries(${PROJECT_NAME} PRIVATE greet2::greet2)