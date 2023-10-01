#pragma once
#include <string>
#include <functional>

namespace dae
{
	class GameObject;
	class Scene;
	class Rengen
	{
	public:
		explicit Rengen(const std::string& dataPath, const std::string& windowName, int windowWidth, int windowHeight);
		~Rengen();
		void Run(const std::function<dae::Scene*()>& load);

		Rengen(const Rengen& other) = delete;
		Rengen(Rengen&& other) = delete;
		Rengen& operator=(const Rengen& other) = delete;
		Rengen& operator=(Rengen&& other) = delete;

	};
}