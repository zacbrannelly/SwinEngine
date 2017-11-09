#pragma once

#include <string>
#include <vector>
#include <SDL.h>

class Window
{
public:
	Window(std::string title, int width, int height);
	~Window();

	bool Create();
	std::vector<SDL_Event> PollEvents();
	void ClearScreen();
	void SwapBuffers();

	void SetDimensions(int w, int h);

	void SetTitle(std::string title);
	std::string GetTitle() const;

	void SetWidth(int width);
	int GetWidth() const;

	void SetHeight(int height);
	int GetHeight() const;

	void SetResizable(bool resizabe);
	bool IsResizable() const;

	void SetFullscreen(bool fullscreen);
	bool IsFullscreen() const;

	bool IsCloseRequested() const;
	bool IsCreated() const;

	void Release(); 
private:
	SDL_Window* _handle;
	SDL_GLContext _context;

	int _width, _height;
	std::string _title;
	bool _isResizable;
	bool _isFullscreen;
	bool _closeRequested;
	bool _isCreated;
};
