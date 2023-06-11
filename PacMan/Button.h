#pragma once

class Button
{
public:
	Button();
	virtual ~Button() = default;
	virtual void Pressed(){}
};