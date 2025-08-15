find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(boost_assert CONFIG REQUIRED)
find_package(boost_gil CONFIG REQUIRED)

set(INCROOT "${PROJECT_SOURCE_DIR}/libs/include/pixengeo/graphics")
set(SRCROOT "${PROJECT_SOURCE_DIR}/libs/src/pixengeo/graphics")

set(SRC
	"${SRCROOT}/pch.cpp"
	"${SRCROOT}/pch.h"
	"${SRCROOT}/glcheck.h"
	"${SRCROOT}/window.cpp"
	"${SRCROOT}/window_impl.h"
	"${SRCROOT}/window_impl.cpp"
	"${SRCROOT}/renderer.cpp"
	"${SRCROOT}/renderer_impl.h"
	"${SRCROOT}/renderer_impl.cpp"
)

add_library(${PROJECT_NAME}-graphics 
	SHARED 
		${SRC}
)

target_include_directories(${PROJECT_NAME}-graphics  
	PUBLIC 
		${PROJECT_SOURCE_DIR}/libs/include
		${PROJECT_NAME}-math
)

target_link_libraries(${PROJECT_NAME}-graphics
	PRIVATE 
		Boost::assert
		Boost::gil
		glfw
		glad::glad
		glm::glm
)

target_compile_options(${PROJECT_NAME}-graphics
	PRIVATE 
		$<$<CXX_COMPILER_ID:MSVC>:${MSVC_WARNINGS}>
		$<$<CXX_COMPILER_ID:GNU>:${GCC_WARNINGS}>
		$<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:${MSVC_DEBUG_OPTIMISATION}>
		$<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:GNU>>:${GCC_DEBUG_OPTIMISATION}>
		$<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:${MSVC_RELEASE_OPTIMISATION}>
		$<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU>>:${GCC_RELEASE_OPTIMISATION}>
)

target_precompile_headers(${PROJECT_NAME}-graphics
	PRIVATE
		"${SRCROOT}/pch.h"
)

target_compile_definitions(${PROJECT_NAME}-graphics
	PRIVATE
		PIXENGEO_GRAPHICS_EXPORTS
)