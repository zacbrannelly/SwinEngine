#include "Script.h"

using namespace std;
using namespace luabridge;

Script::Script(string tableName, lua_State* state) 
{
	_tableName = tableName;
	_luaState = state;

	_isLoaded = false;
}

bool Script::Load(string path)
{
	// Create the table for the script (so we don't have to define it in the script)
	luaL_dostring(_luaState, (_tableName + " = {}").c_str());

	// Load the script code into the lua state from the file provided
	_isLoaded = !luaL_dofile(_luaState, path.c_str());

	return _isLoaded;
}

LuaRef* Script::GetFunction(string name) const
{
	auto table = getGlobal(_luaState, _tableName.c_str());

	if (!table.isNil())
	{
		auto functionRef = table[name.c_str()];

		if (functionRef.isFunction())
		{
			return new LuaRef(functionRef);
		}
	}
	
	return NULL;
}

string Script::GetTableName() const
{
	return _tableName;
}

bool Script::IsLoaded() const
{
	return _isLoaded;
}

Script::~Script()
{
}
