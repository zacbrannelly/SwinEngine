#pragma once

#include "RenderingContext.h"
#include "ResourceManager.h"
#include "Map.h"
#include "json.hpp"

class MapLoader
{
public:
	MapLoader(ResourceManager* mgr, lua_State* state);
	~MapLoader();

	Map* LoadMap(std::string path);
	bool IsValid(std::string path) const;

	Map* GetMap(std::string name) const;
	std::vector<Map*> GetMaps() const;

	void Release();
private:
	std::vector<Map*> _maps;
	ResourceManager* _resourceMgr;
	lua_State* _luaState;

	MapObject* ParseMapObject(nlohmann::json& objRoot) const;
	MapObject* ParseMapObjectFromType(std::string name, ObjectType type, nlohmann::json& root) const;
	MapObject* ParseSprite(std::string name, nlohmann::json& spriteRoot) const;
	MapObject* ParseRectangle(std::string name, nlohmann::json& rectRoot) const;
	MapObject* ParseLine(std::string name, nlohmann::json& lineRoot) const;
	MapObject* ParseCircle(std::string name, nlohmann::json& circleRoot) const;
};

