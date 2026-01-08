cmake_minimum_required(VERSION 3.15)

project(cross_platform_plugins LANGUAGES CXX)

# ---- C++ standard ----
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Unified output directories ----
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Folder to put all final plugin libraries
set(FINAL_LIB_DIR ${CMAKE_SOURCE_DIR}/final_libs)

# Ensure the folder exists
# file(MAKE_DIRECTORY ${FINAL_LIB_DIR})

add_custom_target(clean_final_libs
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${FINAL_LIB_DIR}
    COMMENT "Cleaning final_libs directory"
)

add_custom_target(clean_all
    DEPENDS clean clean_final_libs
)

# ---- Global include path (headers only) ----
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# ---- Subprojects ----
add_subdirectory(common)
add_subdirectory(Driver)
add_subdirectory(plugins/leetcode/medium/802)
add_subdirectory(plugins/leetcode/medium/841)
add_subdirectory(plugins/leetcode/medium/2353)
add_subdirectory(plugins/hacker_rank/medium/two_pluses)
