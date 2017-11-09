#pragma once
#include "Script.h"
#include "Window.h"
#include "MapLoader.h"
#include "StateManager.h"

class EngineScript : public Script
{
public:
	EngineScript(std::string tableName, lua_State* state);
	~EngineScript();

	bool Load(std::string path) override;

	void CallSetupWindow(Window* window) const;
	void CallLoadMaps(MapLoader* mapLoader, StateManager* mgr) const;
private:
	luabridge::LuaRef *_loadMapsFunction, *_setupWindowFunction;
};

