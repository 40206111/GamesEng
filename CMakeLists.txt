cmake_minimum_required(VERSION 3.9)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Directories ####
# Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Output all DLLs from all libs into main build folder
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

#### Copy resources ####
add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND}
	-E copy_directory
		"${PROJECT_SOURCE_DIR}/res"
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
)

#### Tile loader lib ####
file(GLOB_RECURSE SOURCE_FILES
	lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE
		"${CMAKE_SOURCE_DIR}/lib_tile_level_loader/" PUBLIC ${SFML_INCS})
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)

#### Maths lib ####
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE
	"${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE
	"${CMAKE_SOURCE_DIR}/lib_maths" SYSTEM INTERFACE ${SFML_INCS})

#### Practical 1 ####
file(GLOB_RECURSE SOURCES practical_1/*.cpp practical_1/*.h)
add_executable(PRACTICAL_1_PONG ${SOURCES})
target_include_directories(PRACTICAL_1_PONG PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_1_PONG sfml-graphics)
add_dependencies(PRACTICAL_1_PONG copy_resources)
set_target_properties(PRACTICAL_1_PONG PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
	)

#### Practical 2 ####
file(GLOB_RECURSE SOURCES practical_2/*.cpp practical_2/*.h)
add_executable(PRACTICAL_2_INVADERS ${SOURCES} )
target_include_directories(PRACTICAL_2_INVADERS SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_2_INVADERS sfml-graphics)
add_dependencies(PRACTICAL_2_INVADERS copy_resources)
set_target_properties(PRACTICAL_2_INVADERS PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
	)
	
#### Practical 3 ####
file(GLOB_RECURSE SOURCES practical_3/*.cpp practical_3/*.h)
add_executable(PRACTICAL_3_MAZE ${SOURCES})
target_include_directories(PRACTICAL_3_MAZE PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_3_MAZE lib_tile_level_loader sfml-graphics)
add_dependencies(PRACTICAL_3_MAZE copy_resources)
set_target_properties(PRACTICAL_3_MAZE PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
	)
	
#### Practical 4 ####
file(GLOB_RECURSE SOURCES practical_4/*.cpp practical_4/*.h)
add_executable(PRACTICAL_4_PACMAN ${SOURCES})
target_include_directories(PRACTICAL_4_PACMAN PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_4_PACMAN lib_tile_level_loader sfml-graphics)
add_dependencies(PRACTICAL_4_PACMAN copy_resources)
set_target_properties(PRACTICAL_4_PACMAN PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
	)