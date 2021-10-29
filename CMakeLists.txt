cmake_minimum_required(VERSION 3.10.2) # cmake --version

project(dots)

include_directories(inc)

add_executable(
	${PROJECT_NAME}
	src/game.c
	src/highscore.c
	src/main.c
	src/screen.c
	src/settings.c
)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)

if(${CMAKE_SYSTEM_NAME} MATCHES Windows)
	target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX /wd4996 /wd5105)
	target_sources(
		${PROJECT_NAME} PRIVATE
	    src/port_windows.c
		src/econio.c
	)
elseif(${CMAKE_SYSTEM_NAME} MATCHES Linux)
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
	target_sources(
		${PROJECT_NAME} PRIVATE
	    src/port_linux.c
	)

	find_package(Curses REQUIRED)
	include_directories(${CURSES_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
else()
	message(FATAL_ERROR "System not supported: " ${CMAKE_SYSTEM_NAME})
endif()
