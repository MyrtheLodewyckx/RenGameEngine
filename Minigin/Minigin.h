#pragma once
#include <string>
#include <functional>

namespace dae
{
	class GameObject;
	class Scene;
	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath, const std::string& windowName, int windowWidth, int windowHeight);
		~Minigin();
		void Run(const std::function<dae::Scene*()>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

	};
}