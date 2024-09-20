#include "Widget.h"
#include "graphics.h"
#include "config.h"
#include <vector>
#include <iostream>
#include "Film.h"



//This constructor is creating a film object with parameters
//and is inherited from class Widget.
Film::Film(float x, float y, float w, float h,
    std::vector<std::string> images)
    : Widget(x, y, w, h, { 255, 255, 255 })
{
    widgetVisible = true;
    _images = images;
    pos_x = x;
    pos_y = y;

    _title = "";
    _director = "";
}

//This constructor is creating a film object with paremeters, inherited from
//class Widget, declaring some variables to use them in the film container.
Film::Film(float x, float y, float w, float h,
    std::vector<std::string> images,
    std::string title,
    std::string director,
    std::vector<std::string> description,
    int year,
    std::vector<std::string> actors,
    std::vector<std::string> tags)
    : Widget(x, y, w, h, { 255, 255, 255 })
{
    widgetVisible = true;

    _images = images;
    pos_x = x;
    pos_y = y;
    _title = title;
    _director = director;
    _description = description;
    _yearReleased = year;
    _actors = actors;
    _tags = tags;
}


//In this method we arrange where we want the movies photos and infos to appear ïn the film container
void Film::draw() {
    if (!!isVisible()) {
        return;
    }
    graphics::Brush br;

    br.fill_opacity = 0.8f;
    br.outline_width = 0.01f;
    br.outline_opacity = 0.f;

    br.texture = "";
    br.fill_secondary_color[0] = 0.3f;
    br.fill_secondary_color[1] = 0.1f;

    float FILM_BOUND = CANVAS_WIDTH * 0.85f;
    float FILM_BOUND1 = CANVAS_WIDTH * 0.754f;
    float FILM_BOUNDPIC = CANVAS_WIDTH * 0.87f;

    graphics::drawRect(898.f, 250.f, 300.0f, 500.f, br);


    br.texture = std::string(ASSET_PATH) + _images[0];
    graphics::drawRect(FILM_BOUNDPIC, 140.f,
        bounds.getWidth(), bounds.getHeight(), br);

    graphics::Brush textbr;
    textbr.fill_opacity = 1.0f;
    textbr.fill_color[0] = { 0.f };
    textbr.fill_color[1] = { 0.f };
    textbr.fill_color[2] = { 0.f };

    std::string s = _title;
    std::string delimiter = "+";
    if (s.find(delimiter) != std::string::npos) {

        std::string token1 = s.substr(0, s.find(delimiter));
        std::string token2 = s.substr(s.find(delimiter) + 2, s.length());
        graphics::drawText(FILM_BOUND - _title.length() * 1.8f, 270.f, 21.0f, token1, textbr);
        graphics::drawText(FILM_BOUND - _title.length() * 1.8f, 290.f, 21.0f, token2, textbr);
    }
    else {
        graphics::drawText(FILM_BOUND - _title.length() * 5.f, 285.f, 27.0f, _title, textbr);
    }

    graphics::drawText(FILM_BOUND1, 320.f, 12.0f, _director, textbr);
    float temp1 = 15.f;
    for (auto desc : _description)  //using for loop due to descriptions,actors and tags are vectors
    {
        graphics::drawText(FILM_BOUND1, 358.f + temp1, 12.0f, desc, textbr);
        temp1 = temp1 + 15.f;
    }
    graphics::drawText(FILM_BOUND1, 358.f, 12.0f, std::to_string(_yearReleased), textbr);
    float temp = 13.f;
    for (auto act : _actors)
    {
        graphics::drawText(FILM_BOUND1, 320.f + temp, 12.0f, act, textbr);
        temp = temp + 13.f;
    }
    float temp2 = 15.f;
    for (auto tg : _tags)
    {
        graphics::drawText(FILM_BOUND1, 290 + temp2, 12.0f, tg, textbr);
        temp2 = temp2 + 15.f;
    }




}

void Film::update() {



}