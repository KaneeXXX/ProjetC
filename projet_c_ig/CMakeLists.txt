# STUDENT CMakeLists.txt
#
# tabs: 8 space

# CMake initialization

cmake_minimum_required(VERSION 3.0)
project("ProjetC_IG")


# Paths

get_filename_component(ROOT_DIR		${CMAKE_CURRENT_LIST_FILE} PATH)
set(HEADER_DIRS				"${ROOT_DIR}/api")
set(TEST_DIR				"${ROOT_DIR}/tests")
set(DOCS_DIR				"${ROOT_DIR}/docs")
set(SRC_DIR				"${ROOT_DIR}/implem")

set(LIB_FLAGS				-lfreeimage -lSDL2 -lSDL2_ttf)

if(NOT DEFINED WIN32)
	# set(CMAKE_C_FLAGS		"${CMAKE_C_FLAGS} -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-parameter -Werror")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
endif(NOT DEFINED WIN32)

if(IG_ASAN)
	set(CMAKE_C_FLAGS		"${CMAKE_C_FLAGS} -fsanitize=address -O1 -DIG_ASAN=1")
endif(IG_ASAN)

# Platform specific definitions

if(${APPLE})
	set(HEADER_DIRS			${HEADER_DIRS}
					"/opt/local/include/SDL2"
					"/opt/local/include")
	set(PLATFORM_DIR		"${ROOT_DIR}/_macos")
	set(EIBASE			${PLATFORM_DIR}/libeibase.a)
	set(EXTCLASS			${PLATFORM_DIR}/libexternalclass.a)
	set(PLATFORM_LIB_FLAGS		${EIBASE} -L/opt/local/lib ${LIB_FLAGS})


	message(STATUS "Building for MacOS with eibase: ${EIBASE}")

elseif(${UNIX})

	set(HEADER_DIRS			${HEADER_DIRS}
					"/usr/include/SDL2")
	set(PLATFORM_DIR		"${ROOT_DIR}/_x11")
	set(EIBASE			${PLATFORM_DIR}/libeibase.a)
	set(EXTCLASS			${PLATFORM_DIR}/libexternalclass.a)
	set(PLATFORM_LIB_FLAGS		${EIBASE} -L${PLATFORM_DIR} ${LIB_FLAGS} -lm)

	message(STATUS "Building for Linux with eibase: ${EIBASE}")

else()

	set(SDL				"C:/projetc/SDL2_windows")
	set(HEADER_DIRS			${HEADER_DIRS}
					"${SDL}/include")
	add_definitions			(-D__WIN__=1 -D_CRT_SECURE_NO_WARNINGS=1 -D_AMD64_=1)
	add_compile_options		(/wd4068 /wd4142)

	set(PLATFORM_DIR		"${ROOT_DIR}/_win")
	set(EIBASE			${PLATFORM_DIR}/eibase.lib)
	set(EXTCLASS			${PLATFORM_DIR}/externalclass.lib)
	set(PLATFORM_LIB_FLAGS		${EIBASE}
					${SDL}/lib/SDL2.lib
					${SDL}/lib/SDL2_ttf.lib
					${SDL}/lib/FreeImage.lib)

	message(STATUS "Building for Windows with eibase: ${EIBASE}")

endif(${APPLE})

# General definitions for all targets

include_directories(${HEADER_DIRS})

# target ei (libei)

set(LIB_EI_SOURCES
     ${SRC_DIR}/ei_draw.c
	${SRC_DIR}/ei_application.c
	${SRC_DIR}/ei_widget.c
	${SRC_DIR}/ei_widget_attributes.c
	${SRC_DIR}/ei_widget_configure.c
	${SRC_DIR}/ei_widgetclass.c
	${SRC_DIR}/toplevelclassManager.c
	${SRC_DIR}/frameclassManager.c
	${SRC_DIR}/buttonclassManager.c
	${SRC_DIR}/ei_placer.c
	${SRC_DIR}/ei_event.c)



add_library(ei STATIC			${LIB_EI_SOURCES})

# target fill_test

add_executable(fill_test 		${TEST_DIR}/fill_test.c)
target_link_libraries(fill_test		ei ${PLATFORM_LIB_FLAGS})
target_include_directories(fill_test	PRIVATE ${SRC_DIR})

# target poly_test

add_executable(poly_test 		${TEST_DIR}/poly_test.c)
target_link_libraries(poly_test		ei ${PLATFORM_LIB_FLAGS})
target_include_directories(poly_test	PRIVATE ${SRC_DIR})

# target arc_test

add_executable(arc_test 		${TEST_DIR}/arc_test.c)
target_link_libraries(arc_test		ei ${PLATFORM_LIB_FLAGS})
target_include_directories(arc_test	PRIVATE ${SRC_DIR})


# target rounded_frame_test

add_executable(rounded_frame_test 		${TEST_DIR}/rounded_frame_test.c)
target_link_libraries(rounded_frame_test	ei ${PLATFORM_LIB_FLAGS})
target_include_directories(rounded_frame_test	PRIVATE ${SRC_DIR})

# target buttons_test

add_executable(buttons_test 		${TEST_DIR}/buttons_test.c)
target_link_libraries(buttons_test	ei ${PLATFORM_LIB_FLAGS})
target_include_directories(buttons_test	PRIVATE ${SRC_DIR})

# target toplevel_test

add_executable(toplevel_test 		${TEST_DIR}/toplevel_test.c)
target_link_libraries(toplevel_test	ei ${PLATFORM_LIB_FLAGS})
target_include_directories(toplevel_test	PRIVATE ${SRC_DIR})

# target toplevel

add_executable(toplevel		${TEST_DIR}/toplevel.c)
target_link_libraries(toplevel	ei ${PLATFORM_LIB_FLAGS})
target_include_directories(toplevel	PRIVATE ${SRC_DIR})

# target toplevel

add_executable(image_test		${TEST_DIR}/image_test.c)
target_link_libraries(image_test	ei ${PLATFORM_LIB_FLAGS})
target_include_directories(image_test	PRIVATE ${SRC_DIR})

# target minimal

add_executable(minimal 			${TEST_DIR}/minimal.c)
target_link_libraries(minimal		ei ${PLATFORM_LIB_FLAGS})

# target lines

add_executable(lines			${TEST_DIR}/lines.c)
target_link_libraries(lines		ei ${PLATFORM_LIB_FLAGS})

# target frame

add_executable(frame			${TEST_DIR}/frame.c)
target_link_libraries(frame		ei ${PLATFORM_LIB_FLAGS})

# target button

add_executable(button			${TEST_DIR}/button.c)
target_link_libraries(button		ei ${PLATFORM_LIB_FLAGS})

# target hello_world

add_executable(hello_world		${TEST_DIR}/hello_world.c)
target_link_libraries(hello_world	ei ${PLATFORM_LIB_FLAGS})

# target puzzle

add_executable(puzzle			${TEST_DIR}/puzzle.c)
target_link_libraries(puzzle		ei ${PLATFORM_LIB_FLAGS})

# target two048

add_executable(two048			${TEST_DIR}/two048.c)
target_link_libraries(two048		ei ${PLATFORM_LIB_FLAGS})

# target minesweeper

add_executable(minesweeper		${TEST_DIR}/minesweeper.c)
target_link_libraries(minesweeper	ei ${PLATFORM_LIB_FLAGS})

# external_class

add_executable(external_class		${TEST_DIR}/external_class.c)
target_link_libraries(external_class	ei ${PLATFORM_LIB_FLAGS} ${EXTCLASS})


# target to build the documentation

add_custom_target(doc doxygen		${DOCS_DIR}/doxygen.cfg WORKING_DIRECTORY ${ROOT_DIR})

# all

add_custom_target(ig_all ALL)
add_dependencies(ig_all minimal frame button hello_world puzzle two048 minesweeper)
