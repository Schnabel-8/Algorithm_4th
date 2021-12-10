cmake_minimum_required(VERSION 3.12...3.20)

project(sort)

set(SOURCES
     src/main.cpp
)

add_executable(sort ${SOURCES})

target_include_directories(sort
      PRIVATE
            ${PROJECT_SOURCE_DIR}/include
)