cmake_minimum_required(VERSION 3.10.2) # cmake --version

project(dots)

include_directories(inc)

add_executable(
	${PROJECT_NAME}
	src/econio.c
	src/game.c
	src/highscore.c
	src/main.c
	src/screen.c
	src/settings.c
)
