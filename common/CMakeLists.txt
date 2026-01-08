project(common LANGUAGES CXX)

file(GLOB SOURCES "src/*.cpp")

add_library(common_obj OBJECT
    ${SOURCES}
)

# Makes common headers visible to targets linking to common_obj
target_include_directories(common_obj PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)