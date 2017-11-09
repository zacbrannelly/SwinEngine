#pragma once

#include <string>
#include <vector>
#include "glm\glm.hpp"
#include "RenderingContext.h"
#include "ResourceManager.h"
#include "MapObject.h"
#include "MapScript.h"

class Map
{
public:
	Map(std::string name, glm::vec4 bgColor, ResourceManager* mgr);
	~Map();

	void Initialize();
	void Update();
	void Render(RenderingContext* context, double interpolation);

	void Add(MapObject* obj);
	void Remove(MapObject* obj);

	MapObject* GetObject(std::string name) const;
	std::vector<MapObject*> GetObjects(std::string name) const;

	void SetBackground(glm::vec4 bgColor);
	glm::vec4 GetBackground() const;
	 
	std::string GetName() const;

	void SetScript(MapScript* script);
	MapScript* GetScript() const;

	void Release();
private:
	std::string _name;
	std::vector<MapObject*> _objects;
	glm::vec4 _backgroundColor;
	MapScript* _script;
	ResourceManager* _resourceMgr;
};

