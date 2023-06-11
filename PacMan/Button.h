#pragma once

class Button
{
public:
	Button();
	virtual ~Button() = default;
	Button(const Button& other) = delete;
	Button(Button&& other) noexcept = delete;
	Button& operator=(const Button& other) = delete;
	Button& operator=(Button&& other)	noexcept = delete;
	virtual void Pressed(){}
};