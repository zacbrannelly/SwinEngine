#include "Map.h"
#include <SDL_opengl.h>

// Must undefine the macro (from SDL_opengl.h) that has the same name as one of our functions
#undef GetObject

using namespace std;
using namespace glm;


Map::Map(string name, vec4 bgColor, ResourceManager* mgr)
{
	_name = name;
	_backgroundColor = bgColor;
	_resourceMgr = mgr;
	_script = NULL;
}

void Map::Initialize()
{
	if (_script != NULL)
		_script->CallInitialize(this);
}

void Map::Update()
{
	if (_script != NULL)
		_script->CallUpdate(this);

	for (auto obj : _objects)
		obj->Update();
}

void Map::Render(RenderingContext* context, double interpolation)
{
	glClearColor(_backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a);

	for (auto obj : _objects)
		obj->Render(context, interpolation);

	if (_script != NULL)
		_script->CallRender(context, interpolation);
}

void Map::Add(MapObject* obj)
{
	_objects.push_back(obj);
}

void Map::Remove(MapObject* obj)
{
	for (auto it = _objects.begin(); it != _objects.end(); it++)
	{
		if (*it == obj)
		{
			_objects.erase(it);
			break;
		}
	}
}

MapObject* Map::GetObject(string name) const
{
	for (auto obj : _objects)
	{
		if (obj->GetName() == name)
			return obj;
	}

	return NULL;
}

vector<MapObject*> Map::GetObjects(string name) const
{
	vector<MapObject*> result;

	for (auto obj : _objects)
	{
		if (obj->GetName() == name)
			result.push_back(obj);
	}

	return result;
}

void Map::SetBackground(vec4 color)
{
	_backgroundColor = color;
}

vec4 Map::GetBackground() const
{
	return _backgroundColor;
}

string Map::GetName() const
{
	return _name;
}

void Map::SetScript(MapScript* script)
{
	_script = script;
}

MapScript* Map::GetScript() const
{
	return _script;
}

void Map::Release()
{
	for (auto obj : _objects)
		obj->Release();
}

Map::~Map()
{
	if (_script != NULL)
		delete _script;
}
