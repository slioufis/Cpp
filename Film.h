#pragma once
#include "graphics.h"
#include <string>
#include <functional>
#include <vector>

class Film : public Widget {
protected:
	graphics::Brush brush;

	std::string text;
	int id;
	float pos_x, pos_y;

	std::function<void(void*, int id)> callback_isPressed = nullptr;
	std::function<void(void*, int id)> callback_isReleased = nullptr;
	void* isPressed_data = nullptr;
	void* isReleased_data = nullptr;

	std::vector<std::string> _images;
	std::string _title;
	std::string _director;
	std::vector<std::string> _description;
	int _yearReleased;
	std::vector<std::string> _actors;
	std::vector<std::string> _tags;

public:
	Film(float x, float y, float w, float h, std::vector<std::string> images);
	virtual void update() override;

	virtual void draw();
	Film(float x, float y, float w, float h, std::vector<std::string> images, std::string title, std::string director, std::vector<std::string> description, int year, std::vector<std::string> actors, std::vector<std::string> tags);


	std::vector<std::string>	getImagesUsed() { return _images; }
	std::vector<std::string>	getActors() { return _actors; }
	std::vector<std::string>	getTags() { return _tags; }
	std::string					getTitle() { return _title; }
	std::string					getDirector() { return _director; }
	std::vector<std::string>	getDscription() { return _description; }
	int							getYear() { return _yearReleased; }
};