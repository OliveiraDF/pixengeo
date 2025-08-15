find_package(Boost REQUIRED COMPONENTS dll)

set(HELLO_PROJECT_NAME "Hello Project")
set(HELLO_PROJECT_VERSION 1.0.0)
set(SRCROOT "${PROJECT_SOURCE_DIR}/examples/hello_project")

set(SRC
	"${SRCROOT}/pch.cpp"
	"${SRCROOT}/pch.h"
	"${SRCROOT}/hello_project.h"
)

add_library(hello_project
	MODULE 
		${SRC}
)

target_include_directories(hello_project
    PRIVATE
        ${CMAKE_SOURCE_DIR}/libs/include
)

target_link_libraries(hello_project
	PRIVATE 
		Boost::dll
)

target_compile_definitions(hello_project
	PRIVATE
		HELLO_PROJECT_VERSION="${HELLO_PROJECT_VERSION}"
		HELLO_PROJECT_NAME="${HELLO_PROJECT_NAME}"
)