set(SRCROOT "${PROJECT_SOURCE_DIR}/libs/src/pixengeo/map")

set(SRC
	"${SRCROOT}/pch.cpp"
	"${SRCROOT}/pch.h"
	"${SRCROOT}/object.h"
	"${SRCROOT}/object.cpp"
)

add_library(${PROJECT_NAME}-map
	SHARED 
		${SRC}
)

target_include_directories(${PROJECT_NAME}-map 
	PUBLIC 
		${PROJECT_SOURCE_DIR}/libs/include
)

target_compile_options(${PROJECT_NAME}-map
	PRIVATE 
		$<$<CXX_COMPILER_ID:MSVC>:${MSVC_WARNINGS}>
		$<$<CXX_COMPILER_ID:GNU>:${GCC_WARNINGS}>
		$<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:${MSVC_DEBUG_OPTIMISATION}>
		$<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:GNU>>:${GCC_DEBUG_OPTIMISATION}>
		$<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:${MSVC_RELEASE_OPTIMISATION}>
		$<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU>>:${GCC_RELEASE_OPTIMISATION}>
)

target_precompile_headers(${PROJECT_NAME}-map
	PRIVATE
		"${SRCROOT}/pch.h"
)

target_compile_definitions(${PROJECT_NAME}-map
	PRIVATE
		PIXENGEO_MAP_EXPORTS
)