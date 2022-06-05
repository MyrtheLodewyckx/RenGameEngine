#pragma once


namespace dae
{
	class GameObject;

	class Component
	{
		
	public:
		
		~Component() {};
		virtual void Update(const float) {}
		virtual void Render() const {}
	protected:
		Component(GameObject* go) : m_Go{ go } {}
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
		GameObject* m_Go;
	};
}