project(Driver LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    main.cpp
    $<TARGET_OBJECTS:common_obj>
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include          # dynlib.h, plugin_api.h
    ${CMAKE_SOURCE_DIR}/common/include   # common headers
)

if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} dl)
endif()

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Optional: Add a runtime define for the plugin folder
target_compile_definitions(${PROJECT_NAME} PRIVATE PLUGIN_FOLDER="${FINAL_LIB_DIR}")
