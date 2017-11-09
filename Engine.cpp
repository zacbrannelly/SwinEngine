#include "Engine.h"
#include "Mouse.h"
#include "Keyboard.h"

#include <SDL.h>
#include <SDL_opengl.h>

using namespace std;
using namespace std::chrono_literals;

constexpr std::chrono::nanoseconds timestep(17ms);

Engine::Engine()
{
	_isRunning = false;
	_script = NULL;
	_resourceManager = NULL;
	_renderingContext = NULL;
	_window = NULL;
	_stateManager = NULL;
	_mapLoader = NULL;
}

bool Engine::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "Failed to initialize SDL!" << endl;
		return false;
	}

	if (!_luaBinder.CreateState())
	{
		cout << "Failed to create the Lua State!" << endl;
		return false;
	}

	_luaBinder.BindEngine(this);
	_luaBinder.BindInputFunctions();
	_luaBinder.BindGLM();
	_luaBinder.BindTexture();
	_luaBinder.BindWindow();
	_luaBinder.BindStateManager();
	_luaBinder.BindRenderingContext();
	_luaBinder.BindResourceManager();
	_luaBinder.BindShader();
	_luaBinder.BindShaderProgram();
	_luaBinder.BindBoundingBox();
	_luaBinder.BindMap();
	_luaBinder.BindMapLoader();
	_luaBinder.BindMapObject();
	_luaBinder.BindShape();
	_luaBinder.BindRectangle();
	_luaBinder.BindSprite();
	_luaBinder.BindLine();
	_luaBinder.BindCircle();

	_script = new EngineScript("main", _luaBinder.GetState());
	
	if (!_script->Load("main.lua"))
	{
		cout << "Failed to load the main script!" << endl;
		return false;
	}

	_window = new Window("SwinEngine v1.0", 1024, 600);

	_script->CallSetupWindow(_window);

	if (!_window->Create())
	{
		cout << "Failed to create the window!" << endl;
		return false;
	}

	auto vertShader = Shader::FromFile("shader.vert", GL_VERTEX_SHADER);
	auto fragShader = Shader::FromFile("shader.frag", GL_FRAGMENT_SHADER);

	if (!vertShader || !fragShader)
	{
		cout << "Failed to load one of the shaders!" << endl;
		return false;
	}

	auto shader = new ShaderProgram(vertShader, fragShader);

	if (!shader->Create())
	{
		cout << "Failed to create the shader program!" << endl;
		return false;
	}

	if (!shader->Link())
	{
		cout << "Failed to link the shader program!" << endl;
		return false;
	}

	_renderingContext = new RenderingContext(_window->GetWidth(), _window->GetHeight(), shader);
	_resourceManager = new ResourceManager();

	_mapLoader = new MapLoader(_resourceManager, _luaBinder.GetState());
	_stateManager = new StateManager();
	_script->CallLoadMaps(_mapLoader, _stateManager);

	return true;
}

void Engine::HandleEvents()
{
	auto events = _window->PollEvents();

	Mouse::GetStatesFromEvents(events);
	Keyboard::GetStatesFromEvents(events);

	for (auto event : events)
	{
		if (event.type == SDL_QUIT)
			Stop();
	}
}

void Engine::Update()
{
	auto currentMap = _stateManager->GetCurrentMap();

	if (currentMap != NULL)
		currentMap->Update();
}

void Engine::Render(double interpolation)
{
	_window->ClearScreen();
	_renderingContext->ApplyProjectionViewMatrices();

	auto currentMap = _stateManager->GetCurrentMap();

	if (currentMap != NULL)
		currentMap->Render(_renderingContext, interpolation);

	_window->SwapBuffers();
}

void Engine::Release()
{
	_resourceManager->ReleaseAll();
	_mapLoader->Release();
	_window->Release();
	_luaBinder.Release();

	SDL_Quit();
}

void Engine::StartGameLoop()
{
	_isRunning = true;

	if (!Initialize())
		return;

	using clock = std::chrono::high_resolution_clock;

	std::chrono::nanoseconds lag(0ns);
	float interpolation = 0.0f;

	auto time_start = clock::now();
	while (_isRunning) 
	{
		auto delta_time = clock::now() - time_start;
		time_start = clock::now();

		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

		HandleEvents();

		while (lag >= timestep) 
		{
			lag -= timestep;
			Update();
		}

		interpolation = (double)lag.count() / timestep.count();

		Render(interpolation);
	}

	Release();
}

void Engine::Stop()
{
	_isRunning = false;
}

StateManager* Engine::GetStateManager() const
{
	return _stateManager;
}

Engine::~Engine()
{
	delete _renderingContext;
	delete _window;
	delete _resourceManager;
	delete _stateManager;
	delete _mapLoader;
}
