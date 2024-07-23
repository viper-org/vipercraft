cmake_minimum_required (VERSION 3.8)

set(SOURCES
	"source/main.cpp"

	"source/ViperCraft/ViperCraft.cpp"

	"source/Input/Input.cpp"

	"source/Game/Block/Tile.cpp"
	"source/Game/Block/Chunk.cpp"
 "source/Game/World/World.cpp" "source/Game/Player/PlayerController.cpp" "source/Game/Player/Player.cpp" "source/Physics/Collider.cpp" "source/Game/World/Sky.cpp" "source/Game/Gui/Gui.cpp" "source/Game/Gui/GuiScreen.cpp")

set(HEADERS
	"include/ViperCraft/ViperCraft.h"

	"include/Input/Input.h"
	
	"include/Game/Block/Tile.h"
	"include/Game/Block/Chunk.h"
 "include/Game/World/World.h" "include/Game/Player/PlayerController.h" "include/Game/Player/Player.h" "include/Physics/Collider.h" "include/Physics/Raycast.h" "include/Game/World/Sky.h" "include/Game/Gui/Gui.h" "include/Game/Gui/GuiScreen.h")

set(DEP_SOURCES
	"deps/stb_perlin/stb_perlin.cpp"
)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS} ${DEP_SOURCES})

add_executable (ViperCraft ${SOURCES} ${HEADERS} ${DEP_SOURCES})
target_include_directories(ViperCraft PUBLIC include)

target_compile_features(ViperCraft PUBLIC cxx_std_20)

target_link_libraries(ViperCraft ViperGL)
target_include_directories(ViperCraft PRIVATE deps/stb_perlin)