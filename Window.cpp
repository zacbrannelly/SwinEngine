#include "Window.h"
#include <SDL_opengl.h>
#include <iostream>

using namespace std;

Window::Window(string title, int width, int height)
{
	_title = title;
	_width = width;
	_height = height;

	_handle = NULL;
	_isResizable = false;
	_isFullscreen = false;
	_closeRequested = false;
	_isCreated = false;
}

bool Window::Create()
{
	// Request OpenGL 4.0 Core 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | (_isFullscreen ? SDL_WINDOW_FULLSCREEN : 0) | (_isResizable ? SDL_WINDOW_RESIZABLE : 0);
	_handle = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, flags);

	if (!_handle)
	{
		cout << "Failed to display the window!" << endl;
		return false;
	}

	// Create the OpenGL context
	_context = SDL_GL_CreateContext(_handle);

	if (!_context)
	{
		cout << "Failed to create the OpenGL contex!" << endl;

		SDL_DestroyWindow(_handle);
		return false;
	}

	// Check if the version is above 4, if not then some aspects of the engine will not function.
	int majorVersion = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);

	if (majorVersion < 4)
	{
		cout << "Failed to get the correct OpenGL version!" << endl;

		SDL_GL_DeleteContext(_context);
		SDL_DestroyWindow(_handle);
		return false;
	}

	// We made it here, which means everything went smoothly!
	_isCreated = true;

	return true;
}

vector<SDL_Event> Window::PollEvents()
{
	vector<SDL_Event> events;

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		events.push_back(event);

		if (event.type == SDL_QUIT)
			_closeRequested = true;
	}

	return events;
}

void Window::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::SwapBuffers()
{
	SDL_GL_SwapWindow(_handle);
}

void Window::SetDimensions(int w, int h)
{
	_width = w;
	_height = h;

	if (_isCreated)
		SDL_SetWindowSize(_handle, w, h);
}

void Window::SetTitle(string title)
{
	_title = title;

	if (_isCreated)
		SDL_SetWindowTitle(_handle, title.c_str());
}

string Window::GetTitle() const
{
	return _title;
}

void Window::SetWidth(int width)
{
	_width = width;

	if (_handle != NULL)
		SDL_SetWindowSize(_handle, width, _height);
}

int Window::GetWidth() const
{
	return _width;
}

void Window::SetHeight(int height)
{
	_height = height;

	if (_isCreated)
		SDL_SetWindowSize(_handle, _width, _height);
}

int Window::GetHeight() const
{
	return _height;
}

void Window::SetResizable(bool resizable)
{
	_isResizable = resizable;

	if (_isCreated)
		SDL_SetWindowResizable(_handle, resizable ? SDL_TRUE : SDL_FALSE);
}

bool Window::IsResizable() const
{
	return _isResizable;
}

void Window::SetFullscreen(bool fullscreen)
{
	_isFullscreen = fullscreen;

	if (_isCreated)
		SDL_SetWindowFullscreen(_handle, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
}

bool Window::IsFullscreen() const
{
	return _isFullscreen;
}

bool Window::IsCloseRequested() const
{
	return _closeRequested;
}

bool Window::IsCreated() const
{
	return _isCreated;
}

void Window::Release()
{
	if (_context != NULL)
		SDL_GL_DeleteContext(_context);

	if (_handle != NULL)
		SDL_DestroyWindow(_handle);
}

Window::~Window()
{

}