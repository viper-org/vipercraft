cmake_minimum_required (VERSION 3.8)

find_package(OpenGL REQUIRED)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/deps/glfw)

set(SOURCES
	"source/Window/Window.cpp"
	"source/Shader/Shader.cpp"
 "source/Vertex/VertexObject.cpp")

set(HEADERS
	"include/public/ViperGL/Window/Window.h"
	"include/Shader/Shader.h"
 "include/Vertex/VertexObject.h")

set(DEP_SOURCES
	"deps/glad/src/glad.c"
)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS} ${DEP_SOURCES})

add_library (ViperGL ${SOURCES} ${HEADERS} ${DEP_SOURCES})
target_include_directories(ViperGL PUBLIC include/public)

target_compile_features(ViperGL PUBLIC cxx_std_20)
target_include_directories(ViperGL PRIVATE include)
target_compile_definitions(ViperGL PRIVATE SHADER_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

target_link_libraries(ViperGL PUBLIC glfw)
target_link_libraries(ViperGL PUBLIC OpenGL::GL)
target_include_directories(ViperGL PUBLIC deps/glad/include)