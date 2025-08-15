find_package(boost_program_options CONFIG REQUIRED)
find_package(boost_log CONFIG REQUIRED)
find_package(boost_log_setup CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS dll)
find_package(boost_property_tree CONFIG REQUIRED)

set(SRCROOT "${PROJECT_SOURCE_DIR}/libs/src/pixengeo/core")

set(SRC
	"${SRCROOT}/pch.cpp"
	"${SRCROOT}/pch.h"
	"${SRCROOT}/engine.cpp"
	"${SRCROOT}/engine_impl.cpp"
	"${SRCROOT}/engine_impl.h"
	"${SRCROOT}/command_line_info.h"
	"${SRCROOT}/composite_factory.h"
	"${SRCROOT}/composite_factory.cpp"
)

add_library(${PROJECT_NAME}-core
	SHARED 
		${SRC}
)

target_include_directories(${PROJECT_NAME}-core 
	PUBLIC 
		${PROJECT_SOURCE_DIR}/libs/include
)

target_link_libraries(${PROJECT_NAME}-core 
	PRIVATE 
		Boost::program_options
		Boost::log
		Boost::log_setup
		Boost::dll
		Boost::property_tree
		${PROJECT_NAME}-graphics
)

target_compile_options(${PROJECT_NAME}-core
	PRIVATE 
		$<$<CXX_COMPILER_ID:MSVC>:${MSVC_WARNINGS}>
		$<$<CXX_COMPILER_ID:GNU>:${GCC_WARNINGS}>
		$<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:${MSVC_DEBUG_OPTIMISATION}>
		$<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:GNU>>:${GCC_DEBUG_OPTIMISATION}>
		$<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:${MSVC_RELEASE_OPTIMISATION}>
		$<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU>>:${GCC_RELEASE_OPTIMISATION}>
)

target_precompile_headers(${PROJECT_NAME}-core
	PRIVATE
		"${SRCROOT}/pch.h"
)

target_compile_definitions(${PROJECT_NAME}-core
	PRIVATE
		PIXENGEO_CORE_EXPORTS
		PIXENGEO_VERSION="${PROJECT_VERSION}"
)