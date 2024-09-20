#include "Widget.h"
#include "graphics.h"
#include "config.h"
#include <vector>
#include <iostream>
#include "Film.h"
#include <set>

int Widget::next_uid = 0;
int Widget::focused = 0;



void print(std::string temp) {//debuggin func. TODO delete
	std::cout << temp << std::endl;
}

void print(std::string temp, int temp2) {
	std::cout << temp << std::to_string(temp2) << std::endl;
}

void print(std::string temp, float temp2) {
	std::cout << temp << std::to_string(temp2) << std::endl;
}




/*This constructor is creating a button object with a given positionand color
* and sets the button's initial state as IDLE.
*/

Button::Button(float x, float y, float w, float h, std::vector<int> color)
	: Widget(x, y, w, h, color), currentState(buttonStates::IDLE)
{
	widgetVisible = true;
	pos_x = x;
	pos_y = y;
	WidgetColor_highlight = WidgetColor;
}

/*This constructor is creating a button object with a button_textand button_id
* as extra from the previous and sets text as button_text.
*/
Button::Button(float x, float y, float w, float h, std::string button_text, int button_id, std::vector<int> color)
	: Widget(x, y, w + button_text.length() * 2.f, h + 2.f, color), currentState(buttonStates::IDLE)
{
	widgetVisible = true;

	text = button_text;



	pos_x = x;
	pos_y = y;
	WidgetColor_highlight = WidgetColor;
}

Button::Button() {
	widgetVisible = true;
	pos_x = CANVAS_WIDTH / 2;
	pos_y = CANVAS_HEIGHT / 2;
}


void Button::update() {

}
/*
graphics::setOrientation(0.f);
br.fill_opacity = 1.0f;
br.fill_color[0] = { 1.f };
br.fill_color[1] = { 1.f };
br.fill_color[2] = { 1.f };

/*    Is responsible for calculating if the user is hovering his mouse on the button bounds container,
*    and how the button state should change depending in the current mouse state and other
*    Button objects in the same location.
*
*    Depending on the current button state, an according message is sent to the changeButtonState method
*    to change the appearance of the button on screen. This method is also used by inherited classes and
*    polymorphed accordingly.
*/
float tempi = 2.f;
void Button::draw() {

	if (!widgetVisible) {
		return;
	}

	released = false;

	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX((float)ms.cur_pos_x);
	float my = graphics::windowToCanvasY((float)ms.cur_pos_y);
	std::vector<float> coord = { mx, my }; //int cast is temp solution. May be removed at the future
	bool in_bounds = bounds.contains(coord);

	if (in_bounds) {
		if (!requestFocus()) {
			changeBasedOnState(buttonStates::IDLE);
			return;
		}
		if (ms.button_left_pressed) {
			changeBasedOnState(buttonStates::PRESSED);
			//graphics::playSound(assetPath + "hover.wav", 0.7f);
			//if (callback_isPressed) {callback_isPressed(isPressed_data, uid);}
		}
		else if (currentState == buttonStates::PRESSED && ms.button_left_down) {
			changeBasedOnState(buttonStates::PRESSED);
		}
		else if (ms.button_left_released) {
			changeBasedOnState(buttonStates::HOVERED);
			released = true;
			if (callback_isReleased) {
				isCallbackON = !isCallbackON;
				callback_isReleased(isReleased_data, uid);
				releaseFocus();
				return;
			}
		}
		else {
			changeBasedOnState(buttonStates::HOVERED);
		}
	}
	else {
		changeBasedOnState(buttonStates::IDLE);
		releaseFocus();
	}

}
/*  API method used by DynamicContainerand filmMainContainer to change state of callbacks
*   in case a Button is a toggle button, and not a run once only Button.
*/
void Button::runCallback() {
	isCallbackON = !isCallbackON;
	return callback_isReleased(isReleased_data, uid);
}

/*    Changes the appearance of the button as it appears on the screen, depending on its current state and properties
*    The button has additional functionalities such as:
*        -Splitting the text that has to appear in 2 lines if it is too large.
*        -Rounded corners in buttons, using an algorithm descibed below in more details.
*/
void Button::changeBasedOnState(buttonStates state)
{
	graphics::setOrientation(0.f);
	graphics::Brush br;
	//br.fill_opacity = 1.0f;
	br.fill_opacity = 0.8f;
	br.outline_width = 0.01f;
	br.outline_opacity = 0.f;
	//br.texture = std::string(ASSET_PATH) + "button-white-small.png";


	std::string temptext;
	br.texture = "";
	br.fill_secondary_color[0] = 0.3f;
	br.fill_secondary_color[1] = 0.1f;
	if (state == buttonStates::HOVERED) {
		temptext = "[HOVERED]";
		br.fill_color[0] = { 0.8f };
		br.fill_color[1] = { 0.8f };
		br.fill_color[2] = { 0.8f };
	}
	else if (state == buttonStates::PRESSED) {
		temptext = "[PRESSED]";
		br.fill_color[0] = { 0.5f };
		br.fill_color[1] = { 0.5f };
		br.fill_color[2] = { 0.5f };
	}
	else if (state == buttonStates::IDLE) {
		temptext = "[IDLE]";
		br.fill_color[0] = { 1.f };
		br.fill_color[1] = { 1.f };
		br.fill_color[2] = { 1.f };
	}
	if ((int)graphics::getGlobalTime() % 70 == 0) {
		//std::cout << "---" << br.fill_color[0] << " " << br.fill_color[1] << " " << br.fill_color[2] << "---";
		//std::cout << temptext;
	}

	graphics::Brush debug_br;
	debug_br.fill_opacity = 1.0f;
	debug_br.fill_color[0] = { 0.f };
	debug_br.fill_color[1] = { 0.f };
	debug_br.fill_color[2] = { 0.f };

	/* //Debug funtion to show which button id is in focus right now, and its current state
	if (state == buttonStates::HOVERED || state == buttonStates::PRESSED) {
		graphics::drawText(5.f, 45.f, 20.0f, "id (" + std::to_string(getid()) + ") status:" + temptext, debug_br);
	}
	*/

	graphics::Brush text_br;
	text_br.fill_opacity = 1.0f;
	text_br.fill_color[0] = { 0.f };
	text_br.fill_color[1] = { 0.f };
	text_br.fill_color[2] = { 0.f };



	if (text.find(".png") != std::string::npos) {
		graphics::Brush img_br;

		img_br.texture = std::string(ASSET_PATH) + text;

		img_br.fill_opacity = 0.6f;

		graphics::drawRect(bounds.getCenterX(), bounds.getCenterY(), bounds.getWidth(), bounds.getHeight(), img_br);
	}
	else {


		/*
		*
		*	ASCII representation of button with rounded corners:
		*
		*	The width of the rectangle A is minimized by a const padding,
		*	and the additional drawSectors B, C, D, E are used
		*	to simulate the rounded corners.
		*
		*	2 more small rectangels F, G are used to fill the gap between the
			sectors, and they have height zero if the padding is big enough to
			make button half circle.

			Because the rectangle A had reduced width and every other shape was drawn
			in that excess width, the extra shapes also used as bounds when the user
			hovers mouse in them.

				  ○○▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬○○○
				 ○○ │                               │  ○○○○
			   ○○○  │                               │     ○○○
			  ○○  B │                               │  C    ○○
			 ○○     │                               │        ○
			 ○○○○○○○○                               ○○○○○○○○○○
			 ○      │                               │        ○
			 ○      │                               │        ○
			 ○    F │              A                │  G     ○
			 ○      │                               │        ○
			 ○      │                               │        ○
			 ○○○○○○○○                               ○○○○○○○○○○
			 ○      │                               │        ○
			 ○○   D │                               │  E    ○○
			  ○○    │                               │     ○○○
			   ○○○  │                               │    ○○
				 ○○○▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬○○○○○

			|▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬ total width ▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬|

		*/
		graphics::drawRect(bounds.getCenterX(), bounds.getCenterY(), bounds.getWidth() - 2 * padding, bounds.getHeight(), br);

		graphics::drawSector(bounds.getMinX() + padding, bounds.getMinY() + padding, 0, padding, 90, 180, br);
		graphics::drawSector(bounds.getMaxX() - padding, bounds.getMinY() + padding, 0, padding, 0, 90, br);
		graphics::drawSector(bounds.getMinX() + padding, bounds.getMaxY() - padding, 0, padding, 180, 270, br);
		graphics::drawSector(bounds.getMaxX() - padding, bounds.getMaxY() - padding, 0, padding, 270, 360, br);

		graphics::drawRect(bounds.getMinX() + padding / 2, bounds.getCenterY(), padding, bounds.getHeight() - 2 * padding, br);
		graphics::drawRect(bounds.getMaxX() - padding / 2, bounds.getCenterY(), padding, bounds.getHeight() - 2 * padding, br);



		std::string s = text;
		std::string delimiter = "+";
		if (s.find(delimiter) != std::string::npos) {

			std::string token1 = s.substr(0, s.find(delimiter));
			std::string token2 = s.substr(s.find(delimiter) + 2, s.length());
			graphics::drawText(bounds.getMinX() + 8.f, bounds.getMaxY() - 16.f, bounds.getHeight() * 0.5f, token1, text_br);
			graphics::drawText(bounds.getMinX() + 8.f, bounds.getMaxY() - 4.f, bounds.getHeight() * 0.5f, token2, text_br);

		}
		else {
			graphics::drawText(bounds.getMinX() + 8.f, bounds.getMaxY() - 7.f, bounds.getHeight() * 0.6f, text, text_br);

		}



	}



	//graphics::drawRect(50.f, 25.f, 20.0f, 10.f, br);
	//graphics::drawRect(bounds.getCenterX(), bounds.getCenterY() - 3.f, bounds.getWidth(), bounds.getHeight(), br);
	currentState = state;
}

/*
* The button checks if the id is the static id that all button have in common,
* in the event of a conflict, the button with the longest id will prevail.
*/

bool Widget::requestFocus() {
	//std::cout << "REQUEST--[focused] id: (" << std::to_string(focused) << ")--[uid] id: (" << std::to_string(uid) << ")" << std::endl;
	if (!focused || focused <= uid) {
		focused = uid;
		return true;
	}
	return false;
}

/* when a button is finished with its responsibilities, it releases the focus,
*  allows other buttons to use focus.
*/
void Widget::releaseFocus() {
	if (focused == uid) {
		focused = 0;
	}
	//std::cout << "RELEASE--[focused] id: (" << std::to_string(focused) << ")--[uid] id: (" << std::to_string(uid) << ")" << std::endl;

}

//for every object in the container does draw.
void DynamicContainer::draw() {

	if (!isVisible()) { return; }


	for (auto button : widgetsContained) {
		if (button) {
			//std::cout << "Creating contained button: " << button->getid() << std::endl;

			button->draw();
		}
	}
}

void DynamicContainer::update() {
	for (Widget* button : widgetsContained) {
		if (button) {
			button->update();
		}
	}
}












void Widget::update()
{
}

void Widget::draw()
{
}

Widget::~Widget()
{
}

Widget::Widget()
{
	uid = next_uid++;
}

void Widget::setPosition(float x, float y)
{
}

void Widget::move(float dx, float dy)
{
	//std::cout << "Moving (" << getid() << ") to(" << getBounds().getCenterX() << ", " << getBounds().getCenterY() << ")" << std::endl;

	bounds = CollidingBox(dx, dy, bounds.getWidth(), bounds.getHeight());
	//std::cout << "Moved  ("<<getid()<<") to("<< getBounds().getCenterX()<<", " << getBounds().getCenterY() << ")"<<std::endl<<std::endl;

}

CollidingBox::CollidingBox()
{
}

bool CollidingBox::contains(std::vector<float>& coord)
{
	if (getMinX() <= coord[0] && getMaxX() >= coord[0]) {
		if (getMinY() <= coord[1] && getMaxY() >= coord[1]) {
			return true;
		}
	}
	return false;
}

void setColor(float* target, float* source)
{
}

void DynamicContainer::resize(float newWidth, float newHeight) {
	bounds = CollidingBox(bounds.getCenterX(), bounds.getCenterY(), newWidth, newHeight);

	float height_resize_rate = newHeight / bounds.getHeight();

	for (auto widget : widgetsContained) {
		if (dynamic_cast<Button*>(widget)) {
			if (dynamic_cast<Button*>(widget)->getText().find(".png") != std::string::npos) {
				//widget->getBoundsPtr()->setSize({ newWidth, newHeight });
				widget->getBoundsPtr()->setSize({ newWidth, widget->getBounds().getHeight() });
				//widget->getBoundsPtr()->setSize({ newWidth, height_resize_rate* widget->getBounds().getHeight() });
				//widget->move(widget->getBounds().getCenterX(),
				//				getBounds().getMaxY() + widget->getBounds().getWidth());


			}
			else {

				//widget->getBoundsPtr()->setSize({ newWidth,	widget->getBounds().getHeight() * (newHeight/widget->getBounds().getHeight())});

				widget->getBoundsPtr()->setSize({ newWidth, widget->getBounds().getHeight() });
				//	widget->move(	widget->getBounds().getCenterX(),
				//					getBounds().getMaxY() + widget->getBounds().getWidth());

			}
		}
		else {
			widget->getBoundsPtr()->setSize({ newWidth, widget->getBounds().getHeight() });
		}
	}
	fitConstraints();
}


bool DynamicContainer::hide_film(void* film_to_toggle, int id) {


	bool is_visible;
	if (static_cast<Film*>(film_to_toggle)) {
		Film* film = static_cast<Film*>(film_to_toggle);
		film->show((!film->isVisible()));
		is_visible = film->isVisible();
	}
	else {
		is_visible = false;
	}
	return is_visible;
}


void DynamicContainer::addWidget(Widget* widgetToAdd) {

	Film* widget_to_film = dynamic_cast<Film*>(widgetToAdd);
	if (widget_to_film) {
		for (auto widget : widgetsContained) {
			//std::function<void(void*, int)> functemp = [this]() { hide_film(); }
			dynamic_cast<Button*>(widget)->setCallbackReleased(hide_film);
			dynamic_cast<Button*>(widget)->setReleaseData(static_cast<void*>(widget_to_film));

		}
	}

	widgetsContained.push_back(widgetToAdd);

	fitConstraints();
}

void DynamicContainer::move(float dx, float dy) {
	float steps_x = dx - getBounds().getCenterX();
	float steps_y = dy - getBounds().getCenterY();
	Button::move(dx, dy);
	//std::cout << "Moved to ("<< getBounds().getCenterX()<<", " << getBounds().getCenterY() << ")";
	for (auto widget : widgetsContained) {
		widget->move(widget->getBounds().getCenterX() + steps_x,
			widget->getBounds().getCenterY() + steps_y);
		//std::cout << "Moved to (" << widget->getBounds().getCenterX() + dx << ", " << widget->getBounds().getCenterY() + dy << ")";

	}
}

void DynamicContainer::show(bool visiblity) {
	//std::cout << "Visibility (" << getid() << ") to ("<<isVisible()<<  ")" << std::endl;

	Widget::show(visiblity);
	for (auto widget : widgetsContained) {
		//std::cout << "Visibility (" << getid() << ") to (" << isVisible() << ")" << std::endl;

		widget->show(visiblity);
		//std::cout << "Visibility (" << getid() << ") to (" << isVisible() << ")" << std::endl<<std::endl;

	}
}

bool DynamicContainer::isCallbackActed() {
	bool temp_callback_state = false;
	for (auto widget : widgetsContained) {
		Button* temp = dynamic_cast<Button*>(widget);
		if (temp) {
			if (temp->isCallbackActed()) {
				temp_callback_state = temp->isCallbackActed();
			}
		}
	}
	return temp_callback_state;
}



/*	Runs the callback contained in the inside Button objects.
*	Because the 2 buttons inside both have the same callback function
*	to hide/show the film onbject, we had to verify in some way
*	what would happen if for example: the user presses the text button to
*	show the film, and the img buttonto hide the image.
*
*	The code above uses the following logical table to change button states
*
*
*
*/

void DynamicContainer::runCallback() {
	bool isActedON = false;
	Button* temp = nullptr;


	for (auto widget : widgetsContained) {
		temp = dynamic_cast<Button*>(widget);
		if (temp) {
			if (temp->isCallbackActed()) {
				temp->runCallback();
			}
		}
	}



}


void DynamicContainer::fitConstraints()
{
	bool flag = true;
	float temp_minx, temp_maxx, temp_miny, temp_maxy;
	for (auto widget : widgetsContained) {
		if (flag) {
			flag = false;
			temp_minx = widget->getBounds().getMinX() + padding;
			temp_maxx = widget->getBounds().getMaxX() - padding;
			temp_miny = widget->getBounds().getMinY() + padding;
			temp_maxy = widget->getBounds().getMaxY() - padding;
		}

		if (widget->getBounds().getMinX() < temp_minx) {
			temp_minx = widget->getBounds().getMinX();
		}
		if (widget->getBounds().getMinY() < temp_miny) {
			temp_miny = widget->getBounds().getMinY();
		}
		if (widget->getBounds().getMaxX() > temp_maxx) {
			temp_maxx = widget->getBounds().getMaxX();
		}
		if (widget->getBounds().getMaxY() > temp_maxy) {
			temp_maxy = widget->getBounds().getMaxY();
		}
		/*
		Button(	(temp_maxx + temp_minx)/2,
				(temp_maxy + temp_miny)/2,
				temp_maxx - temp_minx,
				temp_maxy - temp_miny,
				{ 255, 255, 255 });
		*/
		bounds = CollidingBox((temp_maxx + temp_minx) / 2,
			(temp_maxy + temp_miny) / 2,
			temp_maxx - temp_minx,
			temp_maxy - temp_miny);
	}
}

DynamicContainer::DynamicContainer(Widget* widgetToAdd, float new_margin)
	:Button(widgetToAdd->getBounds().getCenterX(),
		widgetToAdd->getBounds().getCenterY(),
		widgetToAdd->getBounds().getWidth() + 2 * new_margin,
		widgetToAdd->getBounds().getHeight() + 2 * new_margin
		, { 255, 255, 255 })
{
	widgetsContained.push_back(widgetToAdd);

	float temp_minx, temp_maxx, temp_miny, temp_maxy;

	temp_minx = std::min(getBounds().getMinX(), widgetToAdd->getBounds().getMinX());
	temp_miny = std::min(getBounds().getMinY(), widgetToAdd->getBounds().getMinY());
	temp_maxx = std::max(getBounds().getMaxX(), widgetToAdd->getBounds().getMaxX());
	temp_maxy = std::max(getBounds().getMaxY(), widgetToAdd->getBounds().getMaxY());

	margin = new_margin;

	widgetVisible = true;
	pos_x = CANVAS_WIDTH / 2;
	pos_y = CANVAS_HEIGHT / 2;
}

textField::textField(float x, float y, float width, float height, std::string placeholder_text)
	:Button(x, y, width, height, { 255,255,255 })
{
	placeholder = placeholder_text;
	text = placeholder;
}
bool textField::CAPS_LOCK_ENABLED = false;

std::string textField::getTextToSearch() {
	if (text != placeholder) {
		return text;
	}
	else {
		return "0";
	}
}

void textField::refresh() {
	text = placeholder;
}

void textField::draw() {
	//text = placeholder;
	char characterToAdd;
	if (userIsWriting) {
		characterToAdd = write();
		//print("User is writing");
		if (characterToAdd) {


			if (characterToAdd == 8) {
				if (!text.empty()) {
					text.pop_back();
					static_cast<filmsMainContainer*>(isReleased_data)->searchForText(text, true);
				}
			}
			else if (text.length() <= 20) {


				text = text + characterToAdd;
				static_cast<filmsMainContainer*>(isReleased_data)->searchForText(text, true);

			}

		}
	}
	else {
		//print("Outside text bounds");

		if (text.length() == 0) {


			text = placeholder;
		}

	}

	if (!widgetVisible) {
		return;
	}



	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX((float)ms.cur_pos_x);
	float my = graphics::windowToCanvasY((float)ms.cur_pos_y);
	std::vector<float> coord = { mx, my };
	bool in_bounds = bounds.contains(coord);

	if (in_bounds) {
		if (!requestFocus()) {
			changeBasedOnState(buttonStates::IDLE);
			return;
		}
		if (ms.button_left_pressed) {
			changeBasedOnState(buttonStates::PRESSED);

		}
		else if (currentState == buttonStates::PRESSED && ms.button_left_down) {
			changeBasedOnState(buttonStates::PRESSED);
		}
		else if (ms.button_left_released) {
			//changeBasedOnState(buttonStates::HOVERED);
			released = true;
			userIsWriting = true;
			text = "";
			/*
			if (callback_isReleased) {
				callback_isReleased(isReleased_data, uid);
				releaseFocus();
				return;
			}*/

		}
		else {
			changeBasedOnState(buttonStates::HOVERED);
		}
	}
	else if (ms.button_left_pressed) {
		changeBasedOnState(buttonStates::IDLE);
		userIsWriting = false;
		released = false;
		releaseFocus();
	}
	else {
		changeBasedOnState(buttonStates::IDLE);

	}
}

/*	The method handles input from a keyboard and converts them
*	into ASCII characters. The characts that can be returned
*	are [A-Z], [a-z], space and backspace.
*/
char textField::write() {
	static float delay = 0.0f;
	static int prev = 0;
	delay += graphics::getDeltaTime();
	char ascii = 0;
	for (int i = graphics::SCANCODE_A; i <= graphics::SCANCODE_SPACE; i++)
	{
		if (i == 30) { i += 11; continue; }	//Messy way to do things. TODO fix later
											//Jumps ahead and skips the scancodes for numbers

		if (graphics::getKeyState((graphics::scancode_t)i))
		{
			if (prev == i && delay < 200.f)
			{
				continue;
			}
			else
			{
				prev = i;
				delay = 0.f;
			}
			ascii = (char)(i + 93);

			if (i == 44) {
				ascii = ' '; // If it's space
			}
			if (i == 42) {
				ascii = 8; //The ASCII number for backspace
			}




			if (graphics::getKeyState(graphics::SCANCODE_CAPSLOCK)) {
				if (CAPS_LOCK_ENABLED) {
					ascii -= 32;
				}
				CAPS_LOCK_ENABLED = !CAPS_LOCK_ENABLED;
			}
			if (graphics::getKeyState(graphics::SCANCODE_RSHIFT) || graphics::getKeyState(graphics::SCANCODE_LSHIFT))
			{
				ascii -= 32;
			}

		}

	}

	return ascii;
}

doubleTextField::doubleTextField(float x, float y, float w, float h, std::string _text, std::vector<int> color)
	:Button(x, y, w + _text.length() * 2.f, h + 2.f, color) {
	text = _text;
	left = new textField(x - getBounds().getCenterX() / 2, y, w / 2, h, "Start");
	left = new textField(x - getBounds().getCenterX() / 2, y, w / 2, h, "End");

}

void doubleTextField::draw() {
	left->draw();
	right->draw();

	int start = std::stoi(left->getTextToSearch());
}



toggleButton::toggleButton(float x, float y, float w, float h, std::string _text, std::vector<int> color)
	:Button(x, y, w + _text.length() * 2.f, h + 2.f, color) {
	text = _text;
	buttonToggled = false;
}

void toggleButton::draw() {
	if (!widgetVisible) {
		return;
	}



	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX((float)ms.cur_pos_x);
	float my = graphics::windowToCanvasY((float)ms.cur_pos_y);
	std::vector<float> coord = { mx, my }; //int cast is temp solution. May be removed at the future
	bool in_bounds = bounds.contains(coord);

	if (in_bounds) {
		if (!requestFocus()) {
			changeBasedOnState(buttonStates::IDLE);
			return;
		}
		if (ms.button_left_pressed) {
			changeBasedOnState(buttonStates::PRESSED);
			//graphics::playSound(assetPath + "hover.wav", 0.7f);
			//if (callback_isPressed) {callback_isPressed(isPressed_data, uid);}
		}
		else if (currentState == buttonStates::PRESSED && ms.button_left_down) {
			changeBasedOnState(buttonStates::PRESSED);
		}
		else if (ms.button_left_released) {
			buttonToggled = !buttonToggled;

			if (buttonToggled) {
				changeBasedOnState(buttonStates::PRESSED);
				isCallbackON = true;
				runCallback();
				releaseFocus();
				return;

			}
			else {
				changeBasedOnState(buttonStates::HOVERED);
				isCallbackON = false;
				runCallback();
				releaseFocus();
				return;
			}
		}
		else {
			changeBasedOnState(buttonStates::HOVERED);
		}

	}
	else {
		if (buttonToggled) {
			changeBasedOnState(buttonStates::PRESSED);
		}
		else {
			changeBasedOnState(buttonStates::IDLE);
		}

		releaseFocus();
	}
}

void toggleButton::runCallback() {
	filmsMainContainer* filmsMain = static_cast<filmsMainContainer*>(isReleased_data);
	filmsMain->searchForTag(text, buttonToggled);
}


filmsMainContainer::filmsMainContainer(float x, float y, float w, float h,
	Widget* widget, float _padding, int _filmsPerRow)
	:Button(x, y, w, h, { 255,255,255 })
{
	widgetVisible = true;
	filmsPerRow = _filmsPerRow;
	padding = _padding;
	addFilm(widget);


}

void filmsMainContainer::refresh() {
	DynamicContainer* film;
	for (auto filmWidget : widgetsContained) {
		film = dynamic_cast<DynamicContainer*>(filmWidget);
		if (film) {
			if (!film->isVisible()) {
				film->show(true);
			}
		}
	}
}


std::string tolowercase(std::string& unfiltered_text) {
	std::string text = unfiltered_text;
	for (auto& letter : text) {
		letter = std::tolower(letter);
	}
	return text;
}



bool filmsMainContainer::searchForTag(std::string& tag_rawVersion, bool add_or_remove_tag_on_list)
{
	std::string tag;
	if (tag_rawVersion[0] == '0') {
		return false;
	}
	else {
		print(tag_rawVersion);
		tag = tolowercase(tag_rawVersion);
		print(tag_rawVersion);
	}
	if (add_or_remove_tag_on_list) {
		tags_active.insert(tag);
	}
	else {
		tags_active.erase(tag);
	}

	if (tags_active.empty()) {
		refresh();
		scrolledFromTop = 0.f;
		resize(filmsPerRow);
		return false;
	}

	for (auto widget : widgetsContained) {
		Widget* var = dynamic_cast<DynamicContainer*>(widget)->getContainer()[2];
		if (dynamic_cast<DynamicContainer*>(widget)->isVisible()) {
			if (dynamic_cast<Film*>(var)) {
				std::vector<std::string> tagstotal = dynamic_cast<Film*>(var)->getTags();
				bool doesNotExist = true;
				bool allTagsContained = true;
				for (auto tag : tags_active) {
					bool specificTagContained = false;
					for (auto tag_picked : tagstotal) {
						if (tolowercase(tag_picked).find(tag) != std::string::npos) {
							specificTagContained = true;
						}
					}
					if (!specificTagContained) { allTagsContained = false; }
				}

				doesNotExist = !allTagsContained;

				if (doesNotExist) {
					//hide img
					widget->show(false);
				}

				else {
					//show img
					widget->show(true);

				}
			}
		}
	}
	scrolledFromTop = 0.f;

	resize(filmsPerRow);
}

bool filmsMainContainer::searchForText(std::string& text_unfiltered, bool showOnlyResults)
{
	std::string textToSearch;
	if (text_unfiltered[0] == '0') {
		return false;
	}
	else {

		textToSearch = tolowercase(text_unfiltered);

	}

	print("Loweracased text is:" + textToSearch);
	bool MoviesFound = false;
	std::string degubText;
	for (auto widget : widgetsContained)
	{
		Widget* var = dynamic_cast<DynamicContainer*>(widget)->getContainer()[2];
		DynamicContainer* filmContainer = dynamic_cast<DynamicContainer*>(widget);
		if (dynamic_cast<Film*>(var))
		{
			std::string titlestotal = dynamic_cast<Film*>(var)->getTitle();
			std::string directorstotal = dynamic_cast<Film*>(var)->getDirector();
			std::vector<std::string> actorstotal = dynamic_cast<Film*>(var)->getActors();
			bool doesNotExist = true;
			if (tolowercase(titlestotal).find(textToSearch) != std::string::npos)
			{
				//show img
				doesNotExist = false;
				degubText = titlestotal;
				print("String found: " + degubText);
			}
			if (tolowercase(directorstotal).find(textToSearch) != std::string::npos)
			{
				//show img
				doesNotExist = false;
				degubText = directorstotal;
				print("String found: " + degubText);
			}
			for (auto actors_picked : actorstotal)
			{
				if (tolowercase(actors_picked).find(textToSearch) != std::string::npos)
				{
					//show img
					doesNotExist = false;
					degubText = actors_picked;
					print("String found: " + degubText);
				}
			}
			if (doesNotExist)
			{
				//hide img
				filmContainer->show(!showOnlyResults);
				filmContainer->runCallback();
			}
			else
			{
				//show img
				filmContainer->show(showOnlyResults);
				MoviesFound = !doesNotExist;
			}

		}
	}
	if (MoviesFound) {
		scrolledFromTop = 0.f;

		resize(filmsPerRow);
	}
	return MoviesFound;
}

bool filmsMainContainer::yearsShownBound(int startDate, int endDate)
{
	refresh();
	bool anyMovieFulfills = false;
	for (auto widget : widgetsContained)
	{
		Widget* var = dynamic_cast<DynamicContainer*>(widget)->getContainer()[2];
		DynamicContainer* filmContainer = dynamic_cast<DynamicContainer*>(widget);
		if (dynamic_cast<Film*>(var))
		{
			int filmYear = dynamic_cast<Film*>(var)->getYear();
			bool movie_is_in_dates;

			if (startDate <= filmYear && filmYear <= endDate) {
				movie_is_in_dates = true;
			}
			else {
				movie_is_in_dates = false;
			}


			if (movie_is_in_dates)
			{
				filmContainer->show(movie_is_in_dates);
				anyMovieFulfills = true;

			}
			else
			{
				filmContainer->show(!movie_is_in_dates);
			}

		}
	}
	resize(filmsPerRow);
	return anyMovieFulfills;
}

void filmsMainContainer::draw()
{
	if (!widgetVisible) {
		return;
	}
	DynamicContainer* movie;
	for (auto movie_picked : widgetsContained) {
		movie = dynamic_cast<DynamicContainer*>(movie_picked);
		if (movie) {
			if (movie->isCallbackActed()) {
				if (!filmIsVisible) {

					buttonShown = movie;
					filmIsVisible = true;
				}
				else if (movie->getid() != buttonShown->getid()) {
					buttonShown->runCallback();
					buttonShown = movie;
				}
			}
		}


	}





	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX((float)ms.cur_pos_x);
	float my = graphics::windowToCanvasY((float)ms.cur_pos_y);
	std::vector<float> coord = { mx, my };
	bool in_bounds = bounds.contains(coord);

	float prev_my = graphics::windowToCanvasY((float)ms.prev_pos_y);
	if (in_bounds) {

		if (ms.button_left_pressed) {
			mouseCurrentY = my;
		}

		if (ms.dragging && ms.button_left_down) {
			float delta = my - mouseCurrentY;
			/*
			if (my != prev_my) {
				scrollVertically(my-prev_my);
			}
			*/

			print("DELTA: ", delta);
			print("Current scroll y: ", scrolledFromTop);


			//print("Current scroll y: ", scrolledFromTop);
			scrolledFromTop = scrolledFromTop - delta;
			if (scrolledFromTop >= 0
				&& scrolledFromTop <= currentHeight - (currentHeight / filmsPerRow)) {

				scrollVertically(delta);
			}
			else if (scrolledFromTop < 0.f) {
				scrolledFromTop = scrolledFromTop + delta;
			}
			else if (scrolledFromTop > currentHeight - (currentHeight / filmsPerRow)) {
				scrolledFromTop = scrolledFromTop + delta;
			}
			//print("Current scroll y: ", scrolledFromTop);



			mouseCurrentY = my;
		}
	}
	/* // Debug code used to see the container bounds of the central container
	graphics::Brush br;
	br.fill_color[0] = 0.1f;
	br.fill_color[1] = 0.1f;
	br.fill_color[2] = 0.9f;
	graphics::drawRect(bounds.getCenterX(), bounds.getCenterY(),
		bounds.getWidth(), bounds.getHeight(), br);
	*/

	for (auto film : widgetsContained) {
		film->draw();
	}

}

// Utility function used for debugging purposes
void print_bounds(CollidingBox bound) {
	graphics::Brush t_br;
	graphics::drawText(bound.getMinX(), bound.getMinY(), 15.f,
		"(" + std::to_string(bound.getMinX()) + ", " + std::to_string(bound.getMinY()) + ")", t_br);
	graphics::drawText(bound.getMaxX(), bound.getMinY(), 15.f,
		"(" + std::to_string(bound.getMaxX()) + ", " + std::to_string(bound.getMinY()) + ")", t_br);
	graphics::drawText(bound.getMinX(), bound.getMaxY(), 15.f,
		"(" + std::to_string(bound.getMinX()) + ", " + std::to_string(bound.getMaxY()) + ")", t_br);
	graphics::drawText(bound.getMaxX(), bound.getMaxY(), 15.f,
		"(" + std::to_string(bound.getMaxX()) + ", " + std::to_string(bound.getMaxY()) + ")", t_br);
}

/*	Resizes all objects inside the container in order to fit n of them in a row
*	The resizing in done by subtracing the total padding needed from the container
*	width. The rest of the space is divided equally among the contained objects.
*
*	The handling of the location of the boxes in the screen, and if they are visiable
*	is done by the draw method.
*/
void filmsMainContainer::resize(int filmsPerRow) {
	float temp_oldWidth;
	float temp_oldHeight;
	float newWidth;
	float newHeight;


	bool temp_flag = true;





	for (auto film : widgetsContained) {
		if (temp_flag) {
			temp_oldWidth = film->getBounds().getWidth();
			temp_oldHeight = film->getBounds().getHeight();
			temp_flag = false;
		}
		//print_bounds(film->getBounds());
		newWidth = ((bounds.getWidth() - padding) / (filmsPerRow));
		newHeight = (temp_oldHeight / temp_oldWidth) * newWidth;
		if (dynamic_cast<DynamicContainer*>(film)) {
			dynamic_cast<DynamicContainer*>(film)->resize(newWidth, newHeight);
		}

		//print_bounds(film->getBounds());
	}

	minHeight = bounds.getMinY() + newHeight / 2 + padding;
	currentHeight = minHeight;
	int films_in_current_row = 0;
	float x_of_new_center = bounds.getMinX() + (bounds.getWidth() / filmsPerRow - newWidth / 2);//-padding / 8);


	for (auto film : widgetsContained) {
		if (film->isVisible()) {
			film->move(x_of_new_center, currentHeight);
			x_of_new_center = x_of_new_center + (bounds.getWidth() / filmsPerRow);
			films_in_current_row++;
			if (films_in_current_row == filmsPerRow) {
				currentHeight = currentHeight + padding / 2 + newHeight;
				x_of_new_center = bounds.getMinX() + (bounds.getWidth() / filmsPerRow - newWidth / 2);
				films_in_current_row = 0;
			}
		}
	}
}

void filmsMainContainer::scrollVertically(float scrollTo) {

	float steps_y;


	for (auto widget : widgetsContained) {
		steps_y = scrollTo - widget->getBounds().getCenterY();






		//print("scrolledFromTop <= currentHeight + padding: ", scrolledFromTop <= currentHeight + padding);
		//print("currentHeight + padding: ", currentHeight + padding);
		if (scrolledFromTop >= 0
			&& scrolledFromTop <= currentHeight - (currentHeight / filmsPerRow))
		{
			widget->move(widget->getBounds().getCenterX(),
				widget->getBounds().getCenterY() + scrollTo);
		}

		//widget->getBounds().getCenterY() + steps_y);
	//std::cout << "Moved to (" << widget->getBounds().getCenterX() + dx << ", " << widget->getBounds().getCenterY() + dy << ")";

	}
}

