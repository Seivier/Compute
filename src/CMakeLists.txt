add_subdirectory(glcore)
file(GLOB SOURCES *.cpp *.h)
add_executable(main ${SOURCES})
target_link_libraries(main glcore glm stb)
target_compile_definitions(main PRIVATE RESOURCES_PATH="${PROJECT_SOURCE_DIR}/resources/")
