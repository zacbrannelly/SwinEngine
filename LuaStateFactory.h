#pragma once

#include <LuaBridge\LuaBridge.h>

class Engine;

class LuaStateFactory
{
public:
	LuaStateFactory();
	~LuaStateFactory();

	bool CreateState();
	lua_State* GetState() const;
	void Release();

	void BindEngine(Engine* engine);
	void BindInputFunctions();
	void BindRenderingContext();
	void BindShaderProgram();
	void BindShader();
	void BindGLM();
	void BindResourceManager();
	void BindTexture();
	void BindMapLoader();
	void BindMap();
	void BindMapObject();
	void BindShape();
	void BindRectangle();
	void BindCircle();
	void BindLine();
	void BindSprite();
	void BindBoundingBox();
	void BindStateManager();
	void BindWindow();
private:
	lua_State* _state;
};

