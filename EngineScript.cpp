#include "EngineScript.h"

using namespace std;
using namespace luabridge;


EngineScript::EngineScript(string tableName, lua_State* state) : Script(tableName, state)
{
	_loadMapsFunction = NULL;
	_setupWindowFunction = NULL;
}

bool EngineScript::Load(string path)
{
	bool result = Script::Load(path);

	if (result)
	{
		_loadMapsFunction = GetFunction("LoadMaps");
		_setupWindowFunction = GetFunction("SetupWindow");

		result = _loadMapsFunction != NULL && _setupWindowFunction != NULL 
			&& _loadMapsFunction->isFunction() && _setupWindowFunction->isFunction();
	}

	return result;
}

void EngineScript::CallLoadMaps(MapLoader* loader, StateManager* manager) const
{
	(*_loadMapsFunction)(loader, manager);
}

void EngineScript::CallSetupWindow(Window* window) const
{
	(*_setupWindowFunction)(window);
}

EngineScript::~EngineScript()
{
	delete _loadMapsFunction;
	delete _setupWindowFunction;
}
