#include "MiniginPCH.h"
#include "Component.h"
#include "GameObject.h"
#include <memory>

dae::Component::Component(std::weak_ptr<GameObject> go)
	:m_go{go}
{
}
