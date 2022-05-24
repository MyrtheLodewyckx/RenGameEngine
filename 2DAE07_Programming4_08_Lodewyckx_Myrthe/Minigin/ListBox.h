#pragma once

namespace dae
{
	class ListBox
	{
		unsigned int m_ButtonIdx = 0;

	public:
		void update();
		void render();
	};
}