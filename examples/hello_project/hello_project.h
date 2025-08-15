#pragma once

class hello_project : public pxg::core::project
{
#pragma region Constructors

public:

	hello_project() noexcept = default;
	~hello_project() = default;
	hello_project(const hello_project&) = delete;
	hello_project& operator=(const hello_project&) = delete;

#pragma endregion
#pragma region Overridables

public:

	[[no_discard]] std::string_view name() const noexcept override
	{
		return HELLO_PROJECT_NAME;
	}

	[[no_discard]] std::string_view version() const noexcept override
	{
		return HELLO_PROJECT_VERSION;
	}

#pragma endregion
};