#pragma once

#include <iostream>
#include <functional>
#ifndef _WIN32
#include <unistd.h>
#endif
#include "Window.h"

class Event 
{

public:
	Event();
	Event(Ucraft::Window *window, World *world);
	~Event();

	void			AllCallback();
	static void		window_size_callback(GLFWwindow* window, int width, int height);
	static void		cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
	static void		key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void		mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void			mouseDragging(double width, double height);
	void			keybordEvents(double deltaTime);

	double			getMoveSpeedCam() const { return _movementSpeedCam; }


private:

	Ucraft::Window		*m_win;
	World				*m_world;
	bool				keybordButtons[512];
	bool				dirRight;
	bool				dirLeft;
	bool				dirUp;
	bool				dirDown;
	bool				mbutton_down;
	bool				_guiState;
	double				m_lastMouseX;
	double				m_lastMouseY;
	double				cx;
	double				cy;
	double				_movementSpeedCam;

};