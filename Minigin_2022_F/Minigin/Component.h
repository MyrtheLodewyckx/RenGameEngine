#pragma once


namespace dae
{
	class GameObject;
	class Component

	{
	public:
		Component(std::weak_ptr<GameObject> go);
		~Component() {};
		virtual void Update(const float) = 0;
		virtual void Render() const = 0;
		//std::weak_ptr<GameObject> GetGameObject() { return m_go; };

	protected:
		std::weak_ptr<GameObject> m_go;
	};
}