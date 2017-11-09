#pragma once

#include <LuaBridge\LuaBridge.h>
#include <string>
#include <memory>

class Script
{
public:
	Script(std::string tableName, lua_State* state);
	virtual ~Script();

	virtual bool Load(std::string path);

	luabridge::LuaRef* GetFunction(std::string name) const;
	std::string GetTableName() const;

	bool IsLoaded() const;
private:
	lua_State* _luaState;
	std::string _code, _tableName;
	bool _isLoaded;
};

