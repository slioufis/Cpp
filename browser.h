#pragma once
#include "widget.h"
#include "film.h"
#include <vector>

class Browser
{
	std::vector<Widget*>  buttons;
	std::vector<Film*> films;
public:
	void update();
	void draw();
	void init();
	Browser();
	~Browser();

	bool setupCallback(Widget*, std::function<void(void*, int id)>, void*);
};