cmake_minimum_required(VERSION 3.12...3.20)

project(search)

set(SOURCES
     src/main.cpp
)

add_executable(search ${SOURCES})

target_include_directories(search
      PUBLIC
            ${PROJECT_SOURCE_DIR}/include
)