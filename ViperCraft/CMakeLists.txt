cmake_minimum_required (VERSION 3.8)

set(SOURCES
	"source/main.cpp"

	"source/ViperCraft/ViperCraft.cpp"
)

set(HEADERS
	"include/ViperCraft/ViperCraft.h"
)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

add_executable (ViperCraft ${SOURCES} ${HEADERS})
target_include_directories(ViperCraft PUBLIC include)

target_compile_features(ViperCraft PUBLIC cxx_std_20)
target_link_libraries(ViperCraft ViperGL)