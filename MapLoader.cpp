#include "MapLoader.h"

#include <iostream>
#include <fstream>
#include "glm\glm.hpp"
#include "Rect.h"
#include "Sprite.h"
#include "Circle.h"
#include "Line.h"

using namespace std;
using namespace nlohmann;
using namespace glm;

ObjectType StringToObjectType(string typeString)
{
	if (typeString == "sprite")
		return SpriteObject;
	else if (typeString == "rectangle")
		return RectangleObject;
	else if (typeString == "circle")
		return CircleObject;
	else if (typeString == "line")
		return LineObject;

	return UnknownObject;
}

bool ContainsKey(json& root, string name)
{
	try
	{
		root.at(name);
	}
	catch (std::exception e)
	{
		return false;
	}

	return true;
}

vec2 GetVec2(json& root, string name)
{
	auto array = root.at(name);
	return vec2(array[0].get<float>(), array[1].get<float>());
}

vec4 GetVec4(json& root, string name)
{
	auto array = root.at(name);
	return vec4(array[0].get<float>(), array[1].get<float>(), array[2].get<float>(), array[3].get<float>());
}

MapLoader::MapLoader(ResourceManager* mgr, lua_State* state)
{
	_resourceMgr = mgr;
	_luaState = state;
}

Map* MapLoader::LoadMap(string path)
{
	ifstream in(path.c_str());

	if (!in.is_open()) return NULL;

	json root;
	in >> root;

	in.close();

	auto name = root.at("name").get<string>();
	auto bgColor = GetVec4(root, "backgroundColor");

	auto map = new Map(name, bgColor, _resourceMgr);

	// Try to load a map script
	if (ContainsKey(root, "scriptName") && ContainsKey(root, "scriptPath"))
	{
		auto scriptName = root.at("scriptName").get<string>();
		auto scriptPath = root.at("scriptPath").get<string>();

		auto script = new MapScript(scriptName, _luaState);

		if (script->Load(scriptPath))
		{
			map->SetScript(script);
		}
	}

	auto objectsRoot = root.at("objects");

	// Iterate through all of the objects and create map objects from them.
	for (auto objRoot : objectsRoot)
	{		
		MapObject* newObj = ParseMapObject(objRoot);

		if (newObj != NULL)
			map->Add(newObj);
	}

	map->Initialize();

	_maps.push_back(map);

	return map;
}

MapObject* MapLoader::ParseMapObject(json& objRoot) const
{
	ObjectType type;
	string name;

	if (ContainsKey(objRoot, "name") && ContainsKey(objRoot, "type"))
	{
		name = objRoot.at("name").get<string>();
		type = StringToObjectType(objRoot.at("type").get<string>());
	}
	else
		return NULL;

	MapObject* obj = ParseMapObjectFromType(name, type, objRoot);

	if (obj == NULL)
		return NULL;

	if (ContainsKey(objRoot, "position"))
	{
		auto posArray = objRoot.at("position");
		obj->SetPosition(GetVec2(objRoot, "position"));
	}

	if (ContainsKey(objRoot, "width") && ContainsKey(objRoot, "height"))
	{
		auto width = objRoot.at("width").get<float>();
		auto height = objRoot.at("height").get<float>();
		obj->SetSize(width, height);
	}

	if (ContainsKey(objRoot, "origin"))
	{
		obj->SetOrigin(GetVec2(objRoot, "origin"));
	}

	if (ContainsKey(objRoot, "rotation"))
	{
		auto rotation = objRoot.at("rotation").get<float>();
		obj->SetAngle(rotation);
	}

	// TODO: Add all possible properties here

	return obj;
}

MapObject* MapLoader::ParseMapObjectFromType(string name, ObjectType type, json& root) const
{

	switch (type)
	{
	case ObjectType::SpriteObject:
		return ParseSprite(name, root);
	case ObjectType::RectangleObject:
		return ParseRectangle(name, root);
	case ObjectType::CircleObject:
		return ParseCircle(name, root);
	case ObjectType::LineObject:
		return ParseLine(name, root);
	default:
		return NULL;
	}
}

MapObject* MapLoader::ParseSprite(string name, json& spriteRoot) const
{	
	if (!ContainsKey(spriteRoot, "path"))
		return NULL;

	Sprite* sprite = new Sprite(name, vec2(0, 0), spriteRoot.at("path").get<string>());

	if (!sprite->Load(_resourceMgr))
		return NULL;

	if (ContainsKey(spriteRoot, "sourceRect"))
	{
		auto sourceRect = spriteRoot.at("sourceRect");
		sprite->SetSourceRect(sourceRect[0].get<float>(), sourceRect[1].get<float>(), sourceRect[2].get<float>(), sourceRect[3].get<float>());
	}

	return sprite;
}

MapObject* MapLoader::ParseRectangle(string name, json& rectRoot) const
{
	Rect* rect = new Rect(name, vec2(0, 0), 0, 0);
	rect->Load(_resourceMgr);

	if (ContainsKey(rectRoot, "color"))
		rect->SetColor(GetVec4(rectRoot, "color"));

	if (ContainsKey(rectRoot, "isFilled"))
		rect->SetFilled(rectRoot.at("isFilled").get<bool>());

	return rect;
}

MapObject* MapLoader::ParseLine(string name, json& lineRoot) const
{
	if (!ContainsKey(lineRoot, "startPoint") || !ContainsKey(lineRoot, "endPoint"))
		return NULL;

	auto start = GetVec2(lineRoot, "startPoint");
	auto end = GetVec2(lineRoot, "endPoint");

	Line* line = new Line(name, start, end);
	line->Load(_resourceMgr);

	if (ContainsKey(lineRoot, "color"))
	{
		line->SetColor(GetVec4(lineRoot, "color"));
	}

	return line;
}

MapObject* MapLoader::ParseCircle(string name, json& circleRoot) const
{
	if (!ContainsKey(circleRoot, "radius"))
		return NULL;

	Circle* circle = new Circle(name, vec2(0, 0), circleRoot.at("radius").get<float>());
	circle->Load(_resourceMgr);

	if (ContainsKey(circleRoot, "isFilled"))
	{
		circle->SetFilled(circleRoot.at("isFilled").get<bool>());
	}

	if (ContainsKey(circleRoot, "color"))
	{
		circle->SetColor(GetVec4(circleRoot, "color"));
	}

	return circle;
}

bool MapLoader::IsValid(string path) const
{
	ifstream in(path.c_str());

	if (!in.is_open())
	{
		return false;
	}

	json root;
	in >> root;

	in.close();

	if (root.empty() || !ContainsKey(root, "name") || !ContainsKey(root, "objects") 
		|| !ContainsKey(root, "backgroundColor"))
		return false;

	return true;
}

Map* MapLoader::GetMap(string name) const
{
	for (auto map : _maps)
	{
		if (map->GetName() == name)
			return map;
	}
}

vector<Map*> MapLoader::GetMaps() const
{
	return _maps;
}

void MapLoader::Release()
{
	for (auto map : _maps)
		map->Release();
}

MapLoader::~MapLoader()
{
}