#include "pch.h"
#include "hello_project.h"

pxg::core::project* create_project()
{
	return new hello_project;
}

void destroy_project(pxg::core::project* project)
{
	delete project;
}

BOOST_DLL_ALIAS(create_project, create_project_func)
BOOST_DLL_ALIAS(destroy_project, destroy_project_func)