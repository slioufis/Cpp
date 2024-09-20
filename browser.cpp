#include "browser.h"
#include "graphics.h"
#include "config.h"
#include <iostream>

float movex = CANVAS_WIDTH / 2;
void Browser::update()
{

	for (Widget* button : buttons) {
		if (button) {
			button->update();
		}
	}
}

//The method shows/hide the film when you press the button
void hide(void* m_widgets, int id) {
	std::vector<Widget*>* widgets = static_cast<std::vector<Widget*>*>(m_widgets);

	for (auto widget : *widgets) {
		std::cout << "widget (" << widget->getid() << ") visible:" << widget->isVisible() << std::endl;
		if (!(widget->getid() == 4)) {
			widget->show(!widget->isVisible());

		}
	}

}

//The method let you go up in the container that are the movies
void goUp(void* m_widgets, int id) {
	std::vector<Widget*>* widgets = reinterpret_cast<std::vector<Widget*>*>(m_widgets);
	for (auto widget : *widgets) {
		if (!(widget->getid() == 2 && widget->getid() == 3)) {
			widget->move(widget->getBounds().getCenterX(), widget->getBounds().getCenterY() + 2.0f);
		}

	}
}

//The method let you go down in the container that are the movies
void goDown(void* m_widgets, int id) {
	std::vector<Widget*>* widgets = reinterpret_cast<std::vector<Widget*>*>(m_widgets);
	for (auto widget : *widgets) {
		if (!(widget->getid() == 2 && widget->getid() == 3)) {
			widget->move(widget->getBounds().getCenterX(), widget->getBounds().getCenterY() - 2.0f);
		}
		//std::cout << "widget (" << widget->getid() << ") moving down : " << widget->getBounds().getCenterY() - 2.0f << std::endl;
	}
}

// Wrapper function for filmsMainContainer::searchForTag to be used properly
void hideFilmsWithoutTag(void* filmContainer, int id) {
	filmsMainContainer* container = static_cast<filmsMainContainer*>(filmContainer);
	//container->searchForTag();
}



void Browser::draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "photo1.png";
	br.outline_opacity = 0.0f;
	br.fill_opacity = 1.f;


	//draw background
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);

	//draw button

	/*
	Tries to dynamic_cast vector Widget objects into Button objects,
	in order to run the function held by them.
	*/

	Button* buttonChecked;
	for (auto button : buttons) {
		if (button) {
			button->draw();
		}
	}
}



void Browser::init()
{
	graphics::preloadBitmaps(std::string(ASSET_PATH)); //TODO enable in final version

	if (graphics::getGlobalTime() < 2000) {

		//setupCallback(buttons[3], hide, static_cast<void*>(&buttons));
		//setupCallback(buttons[1], goDown, reinterpret_cast<void*>(&buttons));
		//setupCallback(buttons[2], goUp, reinterpret_cast<void*>(&buttons));	



		//In the following lines is the initialization of buttons with the movies titles,photos and infos and their connection by using callbacks.
		DynamicContainer* temp = new DynamicContainer(new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * BUTTON_INITIAL_LOC_Y,
			140.f, 25.f, "Black Adam", 1), 0.f);

		temp->addWidget(new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			"blackadam2022.png", 1));

		temp->addWidget(new Film(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			{ "blackadam2022.png" },
			"Black Adam",
			"Director: Jaume Collet - Serra",
			{ "Summary: The story centers around Adam,",
			" an ancient superhuman who is released from",
			 "his magic imprisonment by a group of archeo-",
			 "logists to free the nation of Kahndaq the nation",
			  "of Kahndaq from the crime syndicate Intergang." },
			2022,
			{ "Stars: " "Dwayne Johnson, " "Aldis Hodge ", "Noah Centineo" },
			{ "Tags: " "Superhero, " "Action, " "Adventure" }));


		filmsMainContainer* MAIN_FILM_CONTAINER = new filmsMainContainer(CANVAS_WIDTH * 0.468f, CANVAS_HEIGHT / 2,
			CANVAS_WIDTH * 0.55f, CANVAS_HEIGHT, temp, 50.f, 4);
		buttons.push_back(MAIN_FILM_CONTAINER);

		Button* filters = new Button(CANVAS_WIDTH * 0.08f, CANVAS_HEIGHT * 0.25f, 140.f, 25.f, "Filters", 2);
		textField* search = new textField(CANVAS_WIDTH * 0.095f, CANVAS_HEIGHT * 0.303f, 193.f, 22.f, "Enter the title ");
		Button* clear = new Button(CANVAS_WIDTH * 0.129f, CANVAS_HEIGHT * 0.75f, 116.f, 20.f, "Clear", 2);
		Button* year = new Button(CANVAS_WIDTH * 0.097f, CANVAS_HEIGHT * 0.353f, 184.f, 20.f, "Year", 2);


		DynamicContainer* searchBar = new DynamicContainer(filters, 0.f);

		searchBar->addWidget(search);

		searchBar->addWidget(clear);

		searchBar->addWidget(year);


		//setupCallback(search, MAIN_FILM_CONTAINER->searchForText(), search->getTextToSearch());
		search->setReleaseData(MAIN_FILM_CONTAINER);


		toggleButton* superhero = new toggleButton(CANVAS_WIDTH * 0.05f, CANVAS_HEIGHT * 0.47f, 80.f, 17.f, "Superhero");
		toggleButton* action = new toggleButton(CANVAS_WIDTH * 0.146f, CANVAS_HEIGHT * 0.47f, 80.f, 17.f, "Action");
		toggleButton* adventure = new toggleButton(CANVAS_WIDTH * 0.05f, CANVAS_HEIGHT * 0.513f, 80.f, 17.f, "Adventure");
		toggleButton* comedy = new toggleButton(CANVAS_WIDTH * 0.146f, CANVAS_HEIGHT * 0.513f, 80.f, 17.f, "Comedy");
		toggleButton* romance = new toggleButton(CANVAS_WIDTH * 0.05f, CANVAS_HEIGHT * 0.555f, 86.f, 17.f, "Romance");
		toggleButton* drama = new toggleButton(CANVAS_WIDTH * 0.146f, CANVAS_HEIGHT * 0.555f, 80.f, 17.f, "Drama");
		toggleButton* crime = new toggleButton(CANVAS_WIDTH * 0.049f, CANVAS_HEIGHT * 0.597f, 88.f, 17.f, "Crime");
		toggleButton* thriller = new toggleButton(CANVAS_WIDTH * 0.05f, CANVAS_HEIGHT * 0.64f, 86.f, 17.f, "Thriller");
		toggleButton* scifi = new toggleButton(CANVAS_WIDTH * 0.146f, CANVAS_HEIGHT * 0.597f, 80.f, 17.f, "Sci-Fi");

		superhero->setReleaseData(MAIN_FILM_CONTAINER);
		action->setReleaseData(MAIN_FILM_CONTAINER);
		adventure->setReleaseData(MAIN_FILM_CONTAINER);
		comedy->setReleaseData(MAIN_FILM_CONTAINER);
		romance->setReleaseData(MAIN_FILM_CONTAINER);
		drama->setReleaseData(MAIN_FILM_CONTAINER);
		crime->setReleaseData(MAIN_FILM_CONTAINER);
		thriller->setReleaseData(MAIN_FILM_CONTAINER);
		scifi->setReleaseData(MAIN_FILM_CONTAINER);



		searchBar->addWidget(superhero);
		searchBar->addWidget(action);
		searchBar->addWidget(adventure);
		searchBar->addWidget(comedy);
		searchBar->addWidget(romance);
		searchBar->addWidget(drama);
		searchBar->addWidget(crime);
		searchBar->addWidget(thriller);
		searchBar->addWidget(scifi);
		//pushes all the widgets that added previously in the container
		buttons.push_back(searchBar);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	



		temp = new DynamicContainer(
			new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * BUTTON_INITIAL_LOC_Y,
				140.f, 25.f,
				"American Pie", 1)
			, 0.f);
		temp->addWidget(new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			"americanpie1999.png", 1));
		temp->addWidget(new Film(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			{ "americanpie1999.png" },
			"American Pie",
			"Director: Paul Weitz, Chris Weitz",
			{ "Summary: A riotous and raunchy exploration of the",
			"most eagerly anticipated -- and most humiliating",
			"-- rite of adulthood, known as losing one's",
			"virginity. In this hilarious lesson in life, love and libido,",
			"a group of friends, fed up with their well-deserved",
			"reputations as sexual no - hitters, decide to", "take action." },
			1999,
			{ "Stars: " "Jason Biggs, " "Chris Klein", "Thomas Ian Nicholas" },
			{ "Tags: " "Comedy, " "Romance" }));
		MAIN_FILM_CONTAINER->addFilm(temp);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		temp = new DynamicContainer(
			new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * BUTTON_INITIAL_LOC_Y,
				140.f, 25.f,
				"TheGirlNextDoor", 1)
			, 0.f);
		temp->addWidget(new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			"thegirlnextdoor2004.png", 1));

		temp->addWidget(new Film(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			{ "thegirlnextdoor2004.png" },
			"The Girl Next Door",
			"Director: Luke Greenfield",
			{ "Summary: A teenager's dreams come true when a",
			"former porn star moves in next door and they,", "fall in love." },
			2004,
			{ "Stars: " "Emile Hirsch, " "Nicholas Downs, ", "Elisha Cuthbert" },
			{ "Tags: " "Comedy, " "Romance" }));
		MAIN_FILM_CONTAINER->addFilm(temp);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		temp = new DynamicContainer(

			new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * BUTTON_INITIAL_LOC_Y,
				140.f, 25.f,
				"The Hangover", 1)

			, 0.f);

		temp->addWidget(new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			"thehangover2009.png", 1));

		temp->addWidget(new Film(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			{ "thehangover2009.png" },
			"The Hangover",
			"Director: Todd Phillips",
			{ "Summary: Three buddies wake up from a bachelor",
					"party in Las Vegas, with no memory of the previous",
					"night and the bachelor missing. They make their",
					"way around the city in order to find their friend",
					"before his wedding." },
			2009,
			{ "Stars: " "Zach Galifianakis, "  "Bradley Cooper", "Justin Bartha" },
			{ "Tags: " "Comedy" }));
		MAIN_FILM_CONTAINER->addFilm(temp);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		temp = new DynamicContainer(

			new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * BUTTON_INITIAL_LOC_Y,
				140.f, 25.f,
				"Fifty Shades", 1)

			, 0.f);


		temp->addWidget(new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			"fiftyshades2015.png", 1));

		temp->addWidget(new Film(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			{ "fiftyshades2015.png" },
			"Fifty Shades of Grey",
			"Director: Sam Taylor-Johnson",
			{ "Summary: Literature student Anastasia Steele's",
			"life changes forever when she meets handsome,",
			"yet tormented, billionaire Christian Grey." },
			2015,
			{ "Stars: " "Dakota Johnson, "  "Jamie Dornan", "Jennifer Ehle" },
			{ "Tags: " "Romance, " "Drama" }));
		MAIN_FILM_CONTAINER->addFilm(temp);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		temp = new DynamicContainer(

			new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * BUTTON_INITIAL_LOC_Y,
				140.f, 25.f,
				"Fast and the Furious: + Tokyo Drift", 1)

			, 0.f);


		temp->addWidget(new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			"fastnfurioustokyo2006.png", 1));

		temp->addWidget(new Film(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			{ "fastnfurioustokyo2006.png" },
			"The Fast and the Furious: + Tokyo Drift",
			"Director: Justin Lin",
			{ "Summary: A teenager becomes a major compe-",
			"titor in the world of drift racing after moving in",
			"with his father in Tokyo to avoid a jail sentence", "in America." },
			2006,
			{ "Stars: " "Justin Lin, "  "Brian Tee, " "Lucas Black" },
			{ "Tags: " "Action, " "Drama" }));
		MAIN_FILM_CONTAINER->addFilm(temp);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		temp = new DynamicContainer(

			new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * BUTTON_INITIAL_LOC_Y,
				140.f, 25.f,
				"Fast Five", 1)

			, 0.f);

		temp->addWidget(new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			"fastfive2011.png", 1));

		temp->addWidget(new Film(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			{ "fastfive2011.png" },
			"Fast Five",
			"Director: Justin Lin",
			{ "Summary: Dominic Toretto and his crew of street",
			"racers plan a massive heist to buy their freedom",
			"while in the sights of a powerful Brazilian drug",
			"lordand a dangerous federal agent." },
			2011,
			{ "Stars: " "Vin Diesel, " "Paul Walker", "Jordana Brewster" },
			{ "Tags: " "Action" }));
		MAIN_FILM_CONTAINER->addFilm(temp);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		temp = new DynamicContainer(

			new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * BUTTON_INITIAL_LOC_Y,
				140.f, 25.f,
				"The Fast and the + Furious", 1)

			, 0.f);

		temp->addWidget(new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			"thefastnthefurious2001.png", 1));

		temp->addWidget(new Film(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			{ "thefastnthefurious2001.png" },
			"The Fast and the + Furious",
			"Director: Rob Cohen",
			{ "Summary: Los Angeles police officer Brian",
			"O'Conner must decide where his loyalty really lies",
			"when he becomes enamored with the street racing world, ",
			"he has been sent undercover to destroy." },
			2001,
			{ "Stars: " "Paul Walker, " "Vin Diesel" , "Michelle Rodriguez, " "Jordana Brewster" },
			{ "Tags: " "Action, " "Crime, " "Thriller" }));
		MAIN_FILM_CONTAINER->addFilm(temp);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		temp = new DynamicContainer(

			new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * BUTTON_INITIAL_LOC_Y,
				140.f, 25.f,
				"Grown Ups", 1)

			, 0.f);



		temp->addWidget(new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			"grownups2010.png", 1));

		temp->addWidget(new Film(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			{ "grownups2010.png" },
			"Grown Ups",
			"Director: Dennis Dugan",
			{ "Summary: After their high school basketball coach",
			"passes away, five good friendsand former",
			"teammates reunite for a Fourth of July holiday ","weekend." },
			2010,
			{ "Stars: ""Adam Sandler, " "Salma Hayek, "  "Kevin James" },
			{ "Tags: " "Comedy" }));
		MAIN_FILM_CONTAINER->addFilm(temp);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		temp = new DynamicContainer(

			new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * BUTTON_INITIAL_LOC_Y,
				140.f, 25.f,
				"Grown Ups 2", 1)

			, 0.f);


		temp->addWidget(new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			"grownups2013.png", 1));

		temp->addWidget(new Film(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			{ "grownups2013.png" },
			"Grown Ups 2",
			"Director: Dennis Dugan",
			{ "Summary: After moving his family back to his hometown",
			"to be with his friends and their kids, Lenny finds out",
			"that between old bullies, new bullies, schizo bus,",
			"drivers, drunk cops on skis and four hundred",
			"costumed  party crashers sometimes crazy", "follows you." },
			2013,
			{ "Stars: " "Adam Sandler, " "Kevin James, " "Chris Rock" },
			{ "Tags: " "Comedy" }));
		MAIN_FILM_CONTAINER->addFilm(temp);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		temp = new DynamicContainer(

			new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * BUTTON_INITIAL_LOC_Y,
				140.f, 25.f,
				"You Don't Mess + with the Zohan", 1)

			, 0.f);


		temp->addWidget(new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			"udontmesswithzohan2008.png", 1));

		temp->addWidget(new Film(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			{ "udontmesswithzohan2008.png" },
			"You Don't Mess + with the Zohan",
			"Director: Dennis Dugan",
			{ "Summary: An Israeli Special Forces Soldier fakes",
					"his death so he can re - emerge in New York City",
					"as a hair stylist." },
			2008,
			{ "Stars: " "Adam Sandler, " "John Turturro", "Emmanuelle Chriqui" },
			{ "Tags: " "Comedy, " "Action" }));
		MAIN_FILM_CONTAINER->addFilm(temp);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		temp = new DynamicContainer(

			new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * BUTTON_INITIAL_LOC_Y,
				140.f, 25.f,
				"Catch Me If + You Can", 1)

			, 0.f);


		temp->addWidget(new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			"catchmeifucan2002.png", 1));

		temp->addWidget(new Film(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			{ "catchmeifucan2002.png" },
			"Catch Me If You Can",
			"Director: Steven Spielberg",
			{ "Summary: Barely 21 yet, Frank is a skilled forger ",
			"who has passed as a doctor, lawyer and pilot. FBI",
			"agent Carl becomes obsessed with tracking down",
			"the con man, who only revels in the pursuit." },
			2002,
			{ "Stars: " "Leonardo DiCaprio, " "Tom Hanks", "Christopher Walken" },
			{ "Tags: " "Drama, " "Crime" }));
		MAIN_FILM_CONTAINER->addFilm(temp);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		temp = new DynamicContainer(

			new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * BUTTON_INITIAL_LOC_Y,
				140.f, 25.f,
				"IndianaJones: Crystal+ Skull Kingdom", 1)

			, 0.f);


		temp->addWidget(new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			"indianajones2008.png", 1));

		temp->addWidget(new Film(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			{ "indianajones2008.png" },
			"Indiana Jones and the + Kingdom of the Crystal Skull",
			"Director: Steven Spielberg",
			{ "Summary: In 1957, archaeologist and adventurer",
					"Dr. Henry 'Indiana' Jones, Jr. is called back into",
					"action and becomes entangled in a Soviet plot to",
					"uncover the secret behind mysterious artifacts",
					"known as the Crystal Skulls." },
			2008,
			{ "Stars: " "Harrison Ford, " "Cate Blanchett", "Shia LaBeouf" },
			{ "Tags: " "Adventure, " "Action" }));
		MAIN_FILM_CONTAINER->addFilm(temp);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		temp = new DynamicContainer(

			new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * BUTTON_INITIAL_LOC_Y,
				140.f, 25.f,
				"Inception", 1)

			, 0.f);



		;
		temp->addWidget(new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			"inception2010.png", 1));

		temp->addWidget(new Film(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			{ "inception2010.png" },
			"Inception",
			"Director: Christopher Nolan",
			{ "Summary: A thief who steals corporate secrets ",
							"use of dream - sharing technology is given the inverse task",
			 "through the use of dream - sharing technology is ",
			 "given the inverse task of planting an idea into the ",
			 "mind of a C.E.O., but his tragic past may doom the ",
			 "project and his team to disaster." },
			2010,
			{ "Stars: " "Leonardo DiCaprio, " "Joseph Gordo-Levitt", "Elliot Page" },
			{ "Tags: " "Sci-Fi, " "Action" }));
		MAIN_FILM_CONTAINER->addFilm(temp);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		temp = new DynamicContainer(

			new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * BUTTON_INITIAL_LOC_Y,
				140.f, 25.f,
				"Tenet", 1)

			, 0.f);


		temp->addWidget(new Button(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			"tenet2020.png", 1));

		temp->addWidget(new Film(CANVAS_WIDTH * 0.3f, CANVAS_HEIGHT * 0.48f,
			140.f, 200.f,
			{ "tenet2020.png" },
			"Tenet",
			"Director: Christopher Nolan",
			{ "Summary: Armed with only one word, Tenet, and",
					"fighting for the survival of the entire world,",
					"a Protagonist journeys through a twilight world of ",
					"international espionage on a mission that will",
					"unfold in something beyond real time." },
			2020,
			{ "Stars: " "John David Washington, " "Robert Pattinson", "ELizabeth Debicki" },
			{ "Tags: " "Sci-Fi, " "Action" }));
		MAIN_FILM_CONTAINER->addFilm(temp);



		MAIN_FILM_CONTAINER->resize(4);


		////
	}
}





Browser::Browser()
{
}

Browser::~Browser()
{
	for (Widget* button : buttons) {
		if (button) {
			delete button;
		}
	}
	buttons.clear();
	buttons.shrink_to_fit();
}


//Utility function to easily setup a button object with according callbacks
bool Browser::setupCallback(Widget* button_to_edit, std::function<void(void*, int id)> func_to_add, void* data_to_add)
{
	if (dynamic_cast<Button*>(button_to_edit)) {
		dynamic_cast<Button*>(button_to_edit)->setCallbackReleased(func_to_add);
		//void* temp = reinterpret_cast<void*>(&data_to_add);
		dynamic_cast<Button*>(button_to_edit)->setReleaseData(data_to_add);
		return true;
	}
	else {
		return false;
	}
}
