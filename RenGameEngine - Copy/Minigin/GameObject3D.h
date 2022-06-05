#pragma once

struct Transform
{
	float matrix[16]
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

};

class GameObject3D
{
public:
	Transform transform;
	int ID;
	void SetId(int i) { ID = i; };
};