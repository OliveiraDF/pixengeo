set(SRCROOT "${PROJECT_SOURCE_DIR}/app/src")

set(SRC "${SRCROOT}/main.cpp")

add_executable(${PROJECT_NAME}
	${SRC}
)

target_include_directories(${PROJECT_NAME}
	PUBLIC 
		${PROJECT_SOURCE_DIR}/libs/include
)

target_link_libraries(${PROJECT_NAME} 
	PRIVATE 
		${PROJECT_NAME}-core
)