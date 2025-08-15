add_library(${PROJECT_NAME}-math
	INTERFACE
)

target_include_directories(${PROJECT_NAME}-math
	INTERFACE
		"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/libs/include>"
		"$<INSTALL_INTERFACE:libs/include>"
)