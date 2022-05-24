#pragma once
#include <exception>
#include <string>

class Invalid_Argument : public std::exception
{
public:
	std::string GetErrorMessage() { return "Invalid argument type"; };
};