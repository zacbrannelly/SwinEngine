#include "LuaStateFactory.h"

#include "Mouse.h"
#include "Keyboard.h"
#include "RenderingContext.h"
#include "ResourceManager.h"
#include "MapLoader.h"
#include "Shape.h"
#include "Rect.h"
#include "Circle.h"
#include "Line.h"
#include "Sprite.h"
#include "StateManager.h"
#include "Window.h"
#include "Engine.h"
#include "MapObject.h"

#include "glm\gtc\matrix_transform.hpp"

#include <SDL_opengl.h>
#undef GetObject

using namespace luabridge;
using namespace std;
using namespace glm;

LuaStateFactory::LuaStateFactory()
{
	_state = NULL;
}

bool LuaStateFactory::CreateState()
{
	_state = luaL_newstate();

	if (_state != NULL)
	{
		luaL_openlibs(_state);
		return true;
	}

	return false;
}

lua_State* LuaStateFactory::GetState() const
{
	return _state;
}

void LuaStateFactory::Release()
{
	lua_close(_state);
}

void LuaStateFactory::BindEngine(Engine* engine)
{
	getGlobalNamespace(_state)
		.beginClass<Engine>("ENGINE_CLASS")
			.addFunction("Stop", &Engine::Stop)
			.addProperty("StateManager", &Engine::GetStateManager)
		.endClass()
	.beginNamespace("Engine")
		.addVariable("Instance", engine, false)
	.endNamespace();
}

void LuaStateFactory::BindInputFunctions()
{
	Button* left = new Button(Button::Left);
	Button* middle = new Button(Button::Middle);
	Button* right = new Button(Button::Right);

	getGlobalNamespace(_state)
		.beginClass<Button>("Button")
			.addStaticData("Left", left, false)
			.addStaticData("Middle", middle, false)
			.addStaticData("Right", right, false)
		.endClass()
		.beginClass<Mouse>("Mouse")
			.addStaticFunction("IsButtonDown", &Mouse::IsButtonDown)
			.addStaticFunction("IsButtonUp", &Mouse::IsButtonUp)
			.addStaticFunction("WasButtonDown", &Mouse::WasButtonDown)
			.addStaticFunction("WasButtonUp", &Mouse::WasButtonUp)
			.addStaticProperty("X", Mouse::GetMouseX)
			.addStaticProperty("Y", Mouse::GetMouseY)
		.endClass()
		.beginClass<Keyboard>("Keyboard")
			.addStaticFunction("IsKeyDown", &Keyboard::IsKeyDown)
			.addStaticFunction("IsKeyUp", &Keyboard::IsKeyUp)
			.addStaticFunction("WasKeyDown", &Keyboard::WasKeyDown)
			.addStaticFunction("WasKeyUp", &Keyboard::WasKeyUp)
		.endClass();
}

void LuaStateFactory::BindRenderingContext()
{
	getGlobalNamespace(_state)
		.beginClass<RenderingContext>("RenderingContext")
			.addProperty("Width", &RenderingContext::GetViewWidth)
			.addProperty("Height", &RenderingContext::GetViewHeight)
			.addProperty("Shader", &RenderingContext::GetShaders, &RenderingContext::SetShaders)
			.addProperty("Camera", &RenderingContext::GetCamera)
		.endClass();
}

void LuaStateFactory::BindShader()
{
	getGlobalNamespace(_state)
		.beginClass<Shader>("Shader")
			.addStaticFunction("FromFile", &Shader::FromFile)
			.addFunction("Compile", &Shader::Compile)
			.addProperty("IsCompiled", &Shader::IsCompiled)
			.addProperty("Source", &Shader::GetSource, &Shader::SetSource)
		.endClass();

	luaL_dostring(_state, "FRAGMENT_SHADER = 35632");
	luaL_dostring(_state, "VERTEX_SHADER = 35633");
}

void LuaStateFactory::BindShaderProgram()
{
	getGlobalNamespace(_state)
		.beginClass<ShaderProgram>("ShaderProgram")
			.addConstructor<void(*)(Shader*, Shader*)>()
			.addFunction("Create", &ShaderProgram::Create)
			.addFunction("Link", &ShaderProgram::Link)
			.addProperty("IsLinked", &ShaderProgram::IsLinked)
			.addProperty("FragmentShader", &ShaderProgram::GetFragmentShader, &ShaderProgram::SetFragmentShader)
			.addProperty("VertexShader", &ShaderProgram::GetVertexShader, &ShaderProgram::SetVertexShader)
			.addFunction("Use", &ShaderProgram::Use)
			.addFunction<void(ShaderProgram::*)(string, vec2)>("SetUniformVec2", &ShaderProgram::SetUniform)
			.addFunction<void(ShaderProgram::*)(string, float)>("SetUniformFloat", &ShaderProgram::SetUniform)
			.addFunction<void(ShaderProgram::*)(string, int)>("SetUniformInt", &ShaderProgram::SetUniform)
			.addFunction<void(ShaderProgram::*)(string, mat4)>("SetUniformMatrix", &ShaderProgram::SetUniform)
			.addFunction("SetSubroutine", &ShaderProgram::SetSubroutine)
		.endClass();
}

void LuaStateFactory::BindGLM()
{
	getGlobalNamespace(_state)
		.beginClass<vec2>("vec2")
			.addConstructor<void(*)(float, float)>()
			.addData("x", &vec2::x)
			.addData("y", &vec2::y)
		.endClass()
		.beginClass<vec3>("vec3")
			.addConstructor<void(*)(float, float, float)>()
			.addData("x", &vec3::x)
			.addData("y", &vec3::y)
			.addData("z", &vec3::z)
		.endClass()
		.beginClass<vec4>("vec4")
			.addConstructor<void(*)(float, float, float, float)>()
			.addData("x", &vec4::x)
			.addData("y", &vec4::y)
			.addData("z", &vec4::z)
			.addData("w", &vec4::w)
			.addData("r", &vec4::r)
			.addData("g", &vec4::g)
			.addData("b", &vec4::b)
			.addData("a", &vec4::a)
		.endClass()
		.beginClass<glm::mat4>("mat4")
			.addConstructor<void(*)(float)>()
		.endClass()
		.addFunction<glm::mat4(*)(const glm::mat4&, const glm::vec3&)>("translate", &glm::translate)
		.addFunction<glm::mat4(*)(const glm::mat4&, float, const glm::vec3&)>("rotate", &glm::rotate)
		.addFunction<glm::mat4(*)(const glm::mat4&, const glm::vec3&)>("scale", &glm::scale)
		.addFunction<glm::mat4(*)(float, float, float, float)>("ortho", &glm::ortho<float>);
}

void LuaStateFactory::BindResourceManager()
{
	getGlobalNamespace(_state)
		.beginClass<ResourceManager>("ResourceManager")
			.addFunction("GetTexture", &ResourceManager::GetTexture)
			.addFunction("LoadTexture", &ResourceManager::LoadTexture)
			.addFunction("ReleaseTexture", &ResourceManager::ReleaseTexture)
			.addFunction("ReleaseAll", &ResourceManager::ReleaseAll)
		.endClass();
}

void LuaStateFactory::BindTexture()
{
	getGlobalNamespace(_state)
		.beginClass<Texture>("Texture")
			.addProperty("Width", &Texture::GetWidth)
			.addProperty("Height", &Texture::GetHeight)
			.addProperty("Quality", &Texture::GetQuality, &Texture::SetQuality)
			.addFunction("ClampToEdge", &Texture::ClampToEdge)
			.addFunction("Bind", &Texture::Bind)
			.addFunction("Unbind", &Texture::Unbind)
			.addFunction("Release", &Texture::Release)
			.addFunction("UploadData", &Texture::UploadData)
			.addStaticFunction("GenerateEmpty", &Texture::GenerateEmpty)
		.endClass();
}

void LuaStateFactory::BindMapLoader()
{
	getGlobalNamespace(_state)
		.beginClass<MapLoader>("MapLoader")
			.addFunction("LoadMap", &MapLoader::LoadMap)
			.addFunction("IsValid", &MapLoader::IsValid)
			.addFunction("GetMap", &MapLoader::GetMap)
		.endClass();
}

void LuaStateFactory::BindMap()
{
	getGlobalNamespace(_state)
		.beginClass<Map>("Map")
			.addConstructor<void(*)(string, vec4, ResourceManager*)>()
			.addFunction("Add", &Map::Add)
			.addFunction("Remove", &Map::Remove)
			.addFunction("GetObject", &Map::GetObject)
			.addFunction("GetObjects", &Map::GetObjects)
			.addProperty("Background", &Map::GetBackground, &Map::SetBackground)
			.addProperty("Name", &Map::GetName)
			.addProperty("Script", &Map::GetScript, &Map::SetScript)
			.addFunction("Release", &Map::Release)
		.endClass()
		.beginClass<vector<MapObject*>>("MapObjectVector")
			.addConstructor<void(*)()>()
			.addFunction<MapObject*&(vector<MapObject*>::*)(const unsigned int)>("at", &vector<MapObject*>::at)
			.addFunction("size", &vector<MapObject*>::size)
			.addFunction<void(vector<MapObject*>::*)(vector<MapObject*>::const_reference)>("add", &vector<MapObject*>::push_back)
		.endClass();
}

void LuaStateFactory::BindMapObject()
{
	getGlobalNamespace(_state)
		.beginClass<MapObject>("MapObject")
			.addFunction("Load", &MapObject::Load)
			.addFunction("Update", &MapObject::Update)
			.addFunction("Render", &MapObject::Render)
			.addFunction("CalculateModelMatrix", &MapObject::CalculateModelMatrix)
			.addFunction("Release", &MapObject::Release)
			.addFunction<Sprite*(MapObject::*)()>("CastToSprite", &MapObject::CastTo<Sprite>)
			.addFunction<Rect*(MapObject::*)()>("CastToRectangle", &MapObject::CastTo<Rect>)
			.addFunction<Circle*(MapObject::*)()>("CastToCircle", &MapObject::CastTo<Circle>)
			.addFunction<Line*(MapObject::*)()>("CastToLine", &MapObject::CastTo<Line>)
			.addFunction<MapObject*(MapObject::*)()>("CastToMapObject", &MapObject::CastTo<MapObject>)
			.addProperty("Name", &MapObject::GetName, &MapObject::SetName)
			.addProperty("Position", &MapObject::GetPosition, &MapObject::SetPosition)
			.addFunction("SetSize", &MapObject::SetSize)
			.addProperty("Width", &MapObject::GetWidth)
			.addProperty("Height", &MapObject::GetHeight)
			.addProperty("Origin", &MapObject::GetOrigin, &MapObject::SetOrigin)
			.addProperty("Rotation", &MapObject::GetAngle, &MapObject::SetAngle)
			.addProperty("Scale", &MapObject::GetScale, &MapObject::SetScale)
			.addProperty("BoundingBox", &MapObject::GetBoundingBox, &MapObject::SetBoundingBox)
			.addProperty("Acceleration", &MapObject::GetAcceleration, &MapObject::SetAcceleration)
			.addProperty("Velocity", &MapObject::GetVelocity, &MapObject::SetVelocity)
			.addProperty("AngularAcceleration", &MapObject::GetAngularAcceleration, &MapObject::SetAngularAcceleration)
			.addProperty("AngularVelocity", &MapObject::GetAngularVelocity, &MapObject::SetAngularVelocity)
		.endClass();
}

void LuaStateFactory::BindShape()
{
	getGlobalNamespace(_state)
		.deriveClass<Shape, MapObject>("Shape")	
		.endClass();
}

void LuaStateFactory::BindRectangle()
{
	getGlobalNamespace(_state)
		.deriveClass<Rect, Shape>("Rect")
			.addConstructor<void(*)(string, vec2, float, float)>()
			.addFunction("SetColor", &Rect::SetColor)
			.addProperty("Filled", &Rect::IsFilled, &Rect::SetFilled)
		.endClass();
}

void LuaStateFactory::BindCircle()
{
	getGlobalNamespace(_state)
		.deriveClass<Circle, Shape>("Circle")
			.addConstructor<void(*)(string, vec2, float)>()
			.addFunction("SetColor", &Circle::SetColor)
			.addProperty("Radius", &Circle::GetRadius, &Circle::SetRadius)
			.addProperty("Filled", &Circle::IsFilled, &Circle::SetFilled)
		.endClass();
}

void LuaStateFactory::BindLine()
{
	getGlobalNamespace(_state)
		.deriveClass<Line, Shape>("Line")
			.addConstructor<void(*)(string, vec2, vec2)>()
			.addFunction("SetColor", &Line::SetColor)
			.addFunction("SetPoints", &Line::SetPoints)
			.addProperty("StartPoint", &Line::GetStartPoint, &Line::SetStartPoint)
			.addProperty("EndPoint", &Line::GetEndPoint, &Line::SetEndPoint)
		.endClass();
}

void LuaStateFactory::BindSprite()
{
	getGlobalNamespace(_state)
		.deriveClass<Sprite, Rect>("Sprite")
			.addConstructor<void(*)(string, vec2, string)>()
			.addFunction("SetSourceRect", &Sprite::SetSourceRect)
			.addProperty("SourceRect", &Sprite::GetSourceRect)
			.addProperty("Texture", &Sprite::GetTexture, &Sprite::SetTexture)
		.endClass();
}

void LuaStateFactory::BindBoundingBox()
{
	getGlobalNamespace(_state)
		.beginClass<BoundingBox>("BoundingBox")
			.addConstructor<void(*)(vec2, vec2)>()
			.addFunction("Calculate", &BoundingBox::Calculate)
			.addFunction("Intersects", &BoundingBox::Intersects)
			.addFunction("Contains", &BoundingBox::Contains)
			.addProperty("Min", &BoundingBox::GetMin, &BoundingBox::SetMin)
			.addProperty("Max", &BoundingBox::GetMax, &BoundingBox::SetMax)
			.addProperty("Position", &BoundingBox::GetPosition, &BoundingBox::SetPosition)
			.addProperty("Width", &BoundingBox::GetWidth, &BoundingBox::SetWidth)
			.addProperty("Height", &BoundingBox::GetHeight, &BoundingBox::SetHeight)
		.endClass();
}

void LuaStateFactory::BindStateManager()
{
	getGlobalNamespace(_state)
		.beginClass<StateManager>("StateManager")
			.addFunction("RegisterMap", &StateManager::RegisterMap)
			.addFunction("GetMap", &StateManager::GetMap)
			.addProperty("State", &StateManager::GetState, &StateManager::SetState)
			.addProperty("PreviousState", &StateManager::GetPreviousState)
			.addProperty("CurrentMap", &StateManager::GetCurrentMap)
		.endClass();
}

void LuaStateFactory::BindWindow()
{
	getGlobalNamespace(_state)
		.beginClass<Window>("Window")
			.addFunction("SetDimensions", &Window::SetDimensions)
			.addProperty("Title", &Window::GetTitle, &Window::SetTitle)
			.addProperty("Width", &Window::GetWidth, &Window::SetWidth)
			.addProperty("Height", &Window::GetHeight, &Window::SetHeight)
			.addProperty("Resizable", &Window::IsResizable, &Window::SetResizable)
			.addProperty("Fullscreen", &Window::IsFullscreen, &Window::SetFullscreen)
			.addProperty("CloseRequested", &Window::IsCloseRequested)
			.addProperty("IsCreated", &Window::IsCreated)
		.endClass();
}

LuaStateFactory::~LuaStateFactory()
{
}
