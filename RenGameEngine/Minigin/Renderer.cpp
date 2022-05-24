#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_sdl.h"
#include "Imgui/imgui_impl_opengl2.h"
#include "Imgui/imgui_plot.h"
#include  <chrono>
#include "GameObject3D.h"
#include <gl/GL.h>

std::vector<float> results1{};
std::vector<float> results2{};

int m_AmtOfSteps{11};

void DisplayExcersize(const char* title, const char* buttonText, ImColor color, std::vector<float> &results, std::vector<float>(*func)());

std::vector<float> Excersize1();

std::vector<float> Excersize2();

void SetGraph(std::vector<float> y_data, ImColor color)
{
	std::vector<float> x_data{};
	float step{ 1 };
	for (unsigned int i{}; i < y_data.size(); ++i)
	{
		step *= 2;
		x_data.push_back(step);
	}

	ImGui::PlotConfig conf;
	conf.values.xs = x_data.data();
	conf.values.ys = y_data.data();
	conf.values.count = 11;
	conf.values.color = color;
	conf.scale.min = 0;
	conf.scale.max = *std::max_element(y_data.begin(), y_data.end());;
	conf.tooltip.show = true;
	conf.tooltip.format = "x=%.2f, y=%.2f";
	conf.grid_x.show = false;
	conf.grid_y.show = false;
	conf.frame_size = ImVec2(200, 200);
	conf.line_thickness = 3.f;

	ImGui::Plot("plot", conf);
}

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	/*ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	{
		DisplayExcersize("Excersize 1", "Trash that cashe: integers", ImColor(250, 100, 5), results1, &Excersize1);
		DisplayExcersize("Excersize 2", "Trash that cashe: GameObject3D", ImColor(100, 250, 5), results2, &Excersize2);
	}
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());*/
	
	
	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height, const float sourceX, const float sourceY, const float sourceWidth, const float sourceHeight, SDL_RendererFlip flip) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);

	SDL_Rect srt{};
	srt.x = static_cast<int>(sourceX);
	srt.y = static_cast<int>(sourceY);
	srt.w = static_cast<int>(sourceWidth);
	srt.h = static_cast<int>(sourceHeight);

	//SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &srt, &dst);
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srt, &dst, 0, 0, flip);
}

void DisplayExcersize(const char* title, const char* buttonText, ImColor color, std::vector<float> &results, std::vector<float>(*func)())
{
	ImGui::Begin(title, nullptr);
	if (ImGui::Button(buttonText))
	{
		if (results.size() == 0)
			results = func();
		else results.clear();
	}
	if (results.size() > 0)
		SetGraph(results, color);
	ImGui::End();
}

std::vector<float> Excersize1()
{
	std::vector<int> integers{};
	std::vector<float> results{};
	results.reserve(m_AmtOfSteps);
	integers.resize(100000000);
	int stepsize{ 1 };


	auto timeLast = std::chrono::high_resolution_clock::now();
	auto timeNow = std::chrono::high_resolution_clock::now();

	for (int j{}; j < m_AmtOfSteps; ++j)
	{
		for (unsigned int i{ 0 }; i < integers.size(); i += stepsize)
		{
			integers[i] *= 2;
		}
		timeNow = std::chrono::high_resolution_clock::now();
		results.push_back(float(std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - timeLast).count()));
		//std::cout << "Stepsize " << stepsize << "	:" << results.back() << '\n';

		stepsize *= 2;
		timeLast = std::chrono::high_resolution_clock::now();
	}

	return results;
}

std::vector<float> Excersize2()
{
	std::vector<GameObject3D> objs{};
	std::vector<float> results{};

	results.reserve(m_AmtOfSteps);
	objs.resize(100000000);

	int stepsize{ 1 };


	auto timeLast = std::chrono::high_resolution_clock::now();
	auto timeNow = std::chrono::high_resolution_clock::now();

	for (int j{}; j < m_AmtOfSteps; ++j)
	{
		for (unsigned int i{ 0 }; i < objs.size(); i += stepsize)
		{
			objs[i].SetId(2);
		}
		timeNow = std::chrono::high_resolution_clock::now();
		results.push_back(float(std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - timeLast).count()));
		//std::cout << "Stepsize " << stepsize << "	:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - timeLast).count() << '\n';

		stepsize *= 2;
		timeLast = std::chrono::high_resolution_clock::now();
	}

	return results;
}
