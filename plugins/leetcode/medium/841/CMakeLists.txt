project(841 LANGUAGES CXX)

file(GLOB SOURCES "src/*.cpp")

add_library(${PROJECT_NAME} SHARED
    ${SOURCES}
    $<TARGET_OBJECTS:common_obj>
)

target_include_directories(${PROJECT_NAME} PRIVATE
   ${CMAKE_SOURCE_DIR}/include          # root/include
   ${CMAKE_SOURCE_DIR}/common/include   # root/common/include
)

target_compile_definitions(${PROJECT_NAME} PRIVATE PLUGIN_EXPORTS)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION plugins
    LIBRARY DESTINATION plugins
)

# Ensure debug symbols
if(MSVC)
    # MSVC automatically generates .pdb for Debug
    set_target_properties(${PROJECT_NAME} PROPERTIES
        COMPILE_PDB_NAME "${PROJECT_NAME}_debug"  # optional custom .pdb name
        COMPILE_PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Driver"
    )
else()
    # GCC/Clang flags
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
endif()

# --- Disable import library (.lib) on Windows ---
if(WIN32)
    # WINDOWS_EXPORT_ALL_SYMBOLS will export all symbols automatically
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS ON
        ARCHIVE_OUTPUT_NAME ""      # disables .lib output
    )
endif()


# Cross-platform: copy DLL/.so to final_libs folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${FINAL_LIB_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}> ${FINAL_LIB_DIR}
)

# Copy DLL + PDB after build
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_PDB_FILE:${PROJECT_NAME}>
            ${FINAL_LIB_DIR}
    )
endif()