cmake_minimum_required(VERSION 3.14)
project(onepack)

add_subdirectory(third_party/minizip)

file(GLOB LZIP_HEADERS include/elzip/*.hpp)

if (USE_FILESYSTEM_FALLBACK)
    set(ELZIP_CPP src/elzip_fs_fallback.cpp)
else()
    set(ELZIP_CPP src/elzip.cpp)
endif()

file(GLOB LZIP_SOURCES 
    ${ELZIP_CPP}
    src/unzipper.cpp
    src/zipper.cpp
)

add_library(elzip ${LZIP_HEADERS} ${LZIP_SOURCES})
target_link_libraries(elzip minizip)

if (USE_FILESYSTEM_FALLBACK)
    target_link_libraries(elzip tinydir)
elseif (CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(elzip stdc++fs)
endif()

target_include_directories(elzip
    PUBLIC 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/elzip>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_property(TARGET elzip PROPERTY CXX_STANDARD 17)
set_property(TARGET elzip PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET elzip PROPERTY CXX_EXTENSIONS OFF)

add_executable(onepack onepack.cc)
target_link_libraries(onepack elzip)
