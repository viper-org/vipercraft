cmake_minimum_required (VERSION 3.8)

find_package(OpenGL REQUIRED)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/deps/glfw)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/deps/glm)

set(SOURCES
	"source/Window/Window.cpp"
	"source/Window/Input.cpp"

	"source/Shader/Shader.cpp"

	"source/Texture/Texture.cpp"

	"source/Vertex/VertexObject.cpp"
	"source/Vertex/ElementBuffer.cpp"
	
	
	"source/Render/RenderQueue.cpp"
	
	
	"source/Render/Cam.cpp"
 "source/Render/UI.cpp")

set(HEADERS
	"include/public/ViperGL/Window/Window.h"
	"include/public/ViperGL/Window/Input.h"

	"include/public/ViperGL/Render/RenderQueue.h"

	"include/public/ViperGL/Camera/Camera.h"
	
	"include/Render/Cam.h"

	"include/Shader/Shader.h"

	"include/Texture/Texture.h"

	"include/Vertex/VertexObject.h"
	"include/Vertex/ElementBuffer.h"
 "include/public/ViperGL/Render/UI.h")

set(DEP_SOURCES
	"deps/glad/src/glad.c"
)
source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS} ${DEP_SOURCES})

add_library (ViperGL ${SOURCES} ${HEADERS} ${DEP_SOURCES} "source/Render/UI.cpp")
target_include_directories(ViperGL PUBLIC include/public)

target_compile_features(ViperGL PUBLIC cxx_std_20)
target_include_directories(ViperGL PRIVATE include)
target_compile_definitions(ViperGL PRIVATE SHADER_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

target_link_libraries(ViperGL PUBLIC glfw)
target_link_libraries(ViperGL PUBLIC glm::glm)
target_link_libraries(ViperGL PUBLIC OpenGL::GL)
target_include_directories(ViperGL PUBLIC deps/glad/include)
target_include_directories(ViperGL PUBLIC deps/stb)