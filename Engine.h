#pragma once
#include <iostream>
#include <chrono>

#include "EngineScript.h"
#include "ResourceManager.h"
#include "Window.h"
#include "LuaStateFactory.h"

class Engine
{
public:
	Engine();
	~Engine();

	bool Initialize();
	void HandleEvents();
	void Update();
	void Render(double interpolation);
	void Release();

	StateManager* GetStateManager() const;

	void StartGameLoop();
	void Stop();
private:
	EngineScript* _script;
	ResourceManager* _resourceManager;
	RenderingContext* _renderingContext;
	Window* _window;
	StateManager* _stateManager;
	MapLoader* _mapLoader;
	LuaStateFactory _luaBinder;
	bool _isRunning;
};

