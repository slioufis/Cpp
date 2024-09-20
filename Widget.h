#pragma once
#include "graphics.h"
#include <string>
#include <functional>
#include <vector>
#include <set>
void setColor(float* target, float* source);

class CollidingBox {
protected:
	std::vector<float> m_size;
	std::vector<float> m_center;
public:
	CollidingBox();
	CollidingBox(float x, float y, float w, float h) {
		m_center = { x, y };
		m_size = { w, h };
	}

	CollidingBox(std::vector<float> center, std::vector<float> size) {
		m_center = center;
		m_size = size;
	}

	void setSize(std::vector<float> size) { m_size = size; }

	float getMinX() const { return m_center[0] - m_size[0] / 2; }
	float getMaxX() const { return m_center[0] + m_size[0] / 2; }

	float getMinY() const { return m_center[1] - m_size[1] / 2; }
	float getMaxY() const { return m_center[1] + m_size[1] / 2; }

	float getWidth() const { return m_size[0]; }
	float getHeight() const { return m_size[1]; }

	float getCenterX() const { return m_center[0]; }
	float getCenterY() const { return m_center[1]; }

	bool contains(std::vector<float>& comparedCoord);
};

class Widget {
protected:
	static int focused;
	bool widgetVisible = false;
	std::vector<int> WidgetColor;
	std::vector<int> WidgetColor_highlight;
	CollidingBox bounds;

	static int next_uid;
	int uid = 0;

	static std::string assetPath;

	bool requestFocus();
	void releaseFocus();
public:
	void resize(float newWidth, float newHeight) {
		bounds = CollidingBox(bounds.getCenterX(), bounds.getCenterY(), newWidth, newHeight);
	};

	bool temp = true;
	static void setAssetPath(const std::string& path) {
		assetPath = path;
	}
	virtual void update();
	virtual void draw();

	void show(bool visiblity) {
		widgetVisible = visiblity;
	}
	bool isVisible() {
		return widgetVisible;
	}

	virtual ~Widget();
	Widget();
	Widget(float x, float y, float w, float h, std::vector<int> color = { 255, 255, 255 }) {
		bounds = CollidingBox(x, y, w, h);
		WidgetColor = color;
		uid = ++next_uid;
	}

	int getid() { return uid; }

	void setPosition(float x, float y);
	virtual void move(float dx, float dy);

	CollidingBox getBounds() {
		return bounds;
	}

	CollidingBox* getBoundsPtr() {
		return &bounds;
	}
};

class Button : public Widget {
protected:
	graphics::Brush brush;

	bool released = false;
	enum class buttonStates { PRESSED, IDLE, HOVERED };
	buttonStates currentState = buttonStates::IDLE;
	std::string text;

	float padding = 8.f;
	float pos_x, pos_y;
	//virtual void update();
	//virtual void draw();
	bool isCallbackON = false;
	std::function<void(void*, int id)> callback_isPressed = nullptr;
	std::function<void(void*, int id)> callback_isReleased = nullptr;
	void* isPressed_data = nullptr;
	void* isReleased_data = nullptr;
	virtual void changeBasedOnState(buttonStates state);
	/*    Changes the apperance of the button as it appears on the screen, depending on its current state and properties
*    The button has additional functionalities such as:
*        -Splitting the text that has to appear in 2 lines if it is too large.
*        -Rounded corners in buttons, using an algorithm descibed below in more details.
*/
public:
	void setPadding(float new_padding) { padding = new_padding; };
	Button(float x, float y, float w, float h, std::string text, int id, std::vector<int> color = { 255, 255, 255 });
	Button(float x, float y, float w, float h, std::vector<int> color = { 255, 255, 255 });

	void resize(float newWidth, float newHeight);
	std::string getText() { return text; }
	virtual void update() override;

	/*    Is responsible for calculating if the user is hovering his mouse on the button bounds container,
*    and how the button state should change depending in the current mouse state and other
*    Button objects in the same location.
*
*    Depending on the current button state, an according message is sent to the changeButtonState method
*    to change the appearance of the button on screen. This method is also used by inherited classes and
*    polymorphed accordingly.
*/
	virtual void draw() override;
	bool isReleased() { return released; };
	void runCallback();
	bool isCallbackActed() { return isCallbackON; }
	void setReleaseData(void* data) {
		isReleased_data = data;
	}

	void setPressedData(void* data) {
		isPressed_data = data;
	}

	void setCallbackReleased(std::function<void(void*, int id)> newFunc) {
		callback_isReleased = newFunc;
	}

	void setCallbackPressed(std::function<void(void*, int id)> newFunc) {
		callback_isPressed = newFunc;
	}

	Button();
};

class DynamicContainer : public  Button {
	//	Preferred to inherit Button instead of Widget, to make use of the already
	//	implemented draw() and update().
protected:
	std::vector<Widget*> widgetsContained;
	float margin = 0.f;
	static  bool isOn;
public:
	void resize(float newWidth, float newHeight);

	void addWidget(Widget* widgetToAdd);
	std::vector<Widget*> getContainer() { return widgetsContained; };
	//	Functions with additional scope in every contained Widget object
	void move(float dx, float dy);
	static bool hide_film(void* film_to_toggle, int id);
	void show(bool visiblity);
	bool isCallbackActed();
	//Container(float x, float y , float w, float h, Widget *, int padding);
	DynamicContainer(Widget*, float padding);
	void runCallback();
	//	Dynamically resizes the container, to fit all contained objects
	//	Used when adding or removing new onjects. The padding is 
	//	used to increase the white space inside. 
	virtual void fitConstraints();
	//void setMultiCallbacks(std::function<void(void*, int id)> callback, Film* film);
	virtual void update() override;

	void draw();

};

class textField : public Button {
private:
	static bool CAPS_LOCK_ENABLED;
	std::string placeholder;
	std::string search_text;
	bool userIsWriting = false;
public:
	textField(float x, float y, float width, float height, std::string placeholder);
	char write();
	void draw() override;
	void refresh();
	std::string getTextToSearch();
};


class toggleButton : public Button {
private:
	bool buttonToggled;
public:
	toggleButton(float x, float y, float w, float h, std::string, std::vector<int> color = { 255, 255, 255 });
	void draw() override;
	void runCallback();
};

class doubleTextField : public Button {
private:
	textField* left;
	textField* right;
public:
	void draw();
	doubleTextField(float x, float y, float w, float h, std::string, std::vector<int> color = { 255, 255, 255 });
};




class filmsMainContainer : public Button {
private:
	int filmsPerRow;
	std::vector<Widget*> widgetsContained;
	float scrolledFromTop = 0;
	float minHeight;
	float currentHeight;
	float maxheight;
	float padding;
	bool is_resized = false;
	std::set<std::string> tags_active;
	float mouseCurrentY = 0;

	DynamicContainer* buttonShown;
	bool filmIsVisible = false;

public:
	filmsMainContainer(float x, float y, float w, float h,
		Widget* widget, float padding, int filmsPerRow = 4);
	void addFilm(Widget* film_to_add) { widgetsContained.push_back(film_to_add); resize(filmsPerRow); };
	void scrollVertically(float scrollStep);
	void refresh();
	void resize(int filmsPerRow);
	bool searchForTag(std::string& tag, bool showOnlyResults);
	bool searchForText(std::string& tag, bool showOnlyResults);
	bool yearsShownBound(int startDate, int endDate);

	void draw() override;
};