#pragma once
#include "Script.h"
#include "RenderingContext.h"

class Map;

class MapScript : public Script
{
public:
	MapScript(std::string tableName, lua_State* state);
	~MapScript();

	bool Load(std::string path) override;

	void CallInitialize(Map* map) const;
	void CallUpdate(Map* map) const;
	void CallRender(RenderingContext* context, double interpolation) const;

private:
	luabridge::LuaRef *_initializeFunction, *_updateFunction, *_renderFunction;
};

