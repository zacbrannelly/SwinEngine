#include "MapScript.h"
#include "Map.h"

using namespace std;
using namespace luabridge;

MapScript::MapScript(string tableName, lua_State* state) : Script(tableName, state)
{
	
}

bool MapScript::Load(string path) 
{
	bool result = Script::Load(path);

	if (result)
	{
		_initializeFunction = GetFunction("Initialize");
		_updateFunction = GetFunction("Update");
		_renderFunction = GetFunction("Render");

		result = _initializeFunction != NULL && _updateFunction != NULL && _renderFunction != NULL 
			&& _initializeFunction->isFunction() && _updateFunction->isFunction() && _renderFunction->isFunction();
	}

	return result;
}

void MapScript::CallInitialize(Map* map) const
{
	(*_initializeFunction)(map);
}

void MapScript::CallUpdate(Map* map) const
{
	(*_updateFunction)(map);
}

void MapScript::CallRender(RenderingContext* context, double interpolation) const
{
	(*_renderFunction)(context, interpolation);
}

MapScript::~MapScript()
{
	delete _initializeFunction;
	delete _updateFunction;
	delete _renderFunction;
}
