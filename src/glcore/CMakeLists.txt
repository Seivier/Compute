file(GLOB LIB_SOURCES *.cpp *.h)
find_package(OpenGL REQUIRED)
add_library(glcore ${LIB_SOURCES})
target_link_libraries(glcore PUBLIC glfw glad OpenGL::GL glm stb)
target_include_directories(glcore PUBLIC "${CMAKE_SOURCE_DIR}/include")
