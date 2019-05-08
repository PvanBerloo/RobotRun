cmake_minimum_required(VERSION 3.8)
project(RobotRun LANGUAGES C)

set(source_files
	${PROJECT_SOURCE_DIR}/src/main.c
	${PROJECT_SOURCE_DIR}/src/comport.c
)

set(header_files
	${PROJECT_SOURCE_DIR}/inc/comport.h
)

add_executable(RobotRunConsole ${source_files} ${header_files})
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
target_include_directories(RobotRunConsole PRIVATE inc)
target_link_libraries(RobotRunConsole Xinput)