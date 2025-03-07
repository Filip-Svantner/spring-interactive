/// <summary>
/// author Filip Svantner March 2025
/// </summary>

#include "Game.h"
#include <iostream>


/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup the image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ WIDTH, HEIGHT, 32U }, "Aim trainer" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	setupBackground(); // load background
	setupHitboxes(); // loads hitboxes of menu
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but method needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
#ifdef _DEBUG
			render(); // want to debug drawing while stepping through code
#endif // _DEBUG

		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type) //user clicked mouse
		{
			mouseClick(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type) // user released mouse
		{
			mouseRelease(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (m_intro)
	{
		if (sf::Keyboard::Enter == t_event.key.code)
		{
			m_intro = false;
			m_menu = true;
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (t_deltaTime.asMilliseconds() != 16)
	{
		std::cout << "time warp" << std::endl; // expecting 60 fps of action
	}
	if (m_exitGame)
	{
		m_window.close();
	}
	if (m_intro)
	{
		starGameTextFlash();
	}
	if (m_difficulty)
	{
		if (m_wait > 0)
		{
			m_wait--;
			std::cout << m_wait << std::endl;
		}
		if (m_wait == 0)
		{
			m_delay = true;
		}
	}
	if (m_game)
	{
		if (m_wait > 0)
		{
			m_wait--;
			std::cout << m_wait << std::endl;
		}
		if (m_wait == 0)
		{
			//m_delay = true;
		}
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_backgroundSprite);
	if (m_intro)
	{
		m_window.draw(m_introMessage);
		m_window.draw(m_introLogoSprite);
		m_window.draw(m_startGame);
	}
	if (m_menu)
	{
		m_window.draw(m_introMessage);
		m_window.draw(m_playGame);
		m_window.draw(m_highScore);
		m_window.draw(m_controls);
		m_window.draw(m_exit);
	}
	if (m_controlsScreen || m_highScoreScreen)
	{
		m_window.draw(m_back);
		m_window.draw(m_backHitbox);
	}
	if (m_difficulty)
	{
		m_window.draw(m_easy);
		m_window.draw(m_medium);
		m_window.draw(m_hard);
		m_window.draw(m_back);
	}
	if (m_game)
	{
		
	}

	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_introMessage.setFont(m_ArialBlackfont);
	m_introMessage.setString("Aim trainer");
	m_introMessage.setPosition(250.0f, 40.0f);
	m_introMessage.setCharacterSize(80U);
	m_introMessage.setOutlineColor(sf::Color::Black);
	m_introMessage.setFillColor(sf::Color::White);
	m_introMessage.setOutlineThickness(3.0f);

	m_startGame.setString("Press enter to start");
	m_startGame.setFont(m_ArialBlackfont);
	m_startGame.setPosition(350.0f, 600.0f);
	m_startGame.setCharacterSize(30U);
	m_startGame.setFillColor(sf::Color::White);

	m_playGame.setString("Play");
	m_playGame.setFont(m_ArialBlackfont);
	m_playGame.setPosition(450.0f, 200.0f);
	m_playGame.setCharacterSize(50U);
	m_playGame.setFillColor(sf::Color::White);

	m_highScore.setString("High scores");
	m_highScore.setFont(m_ArialBlackfont);
	m_highScore.setPosition(360.0f, 350.0f);
	m_highScore.setCharacterSize(50U);
	m_highScore.setFillColor(sf::Color::White);

	m_controls.setString("How to play");
	m_controls.setFont(m_ArialBlackfont);
	m_controls.setPosition(360.0f, 500.0f);
	m_controls.setCharacterSize(50U);
	m_controls.setFillColor(sf::Color::White);

	m_exit.setString("Exit");
	m_exit.setFont(m_ArialBlackfont);
	m_exit.setPosition(450.0f, 650.0f);
	m_exit.setCharacterSize(50U);
	m_exit.setFillColor(sf::Color::White);

	m_back.setString("Back");
	m_back.setFont(m_ArialBlackfont);
	m_back.setPosition(450.0f, 700.0f);
	m_back.setCharacterSize(50U);
	m_back.setFillColor(sf::Color::White);
	
	m_easy.setString("Easy");
	m_easy.setFont(m_ArialBlackfont);
	m_easy.setPosition(450.0f, 200.0f);
	m_easy.setCharacterSize(50U);
	m_easy.setFillColor(sf::Color::White);
	

	m_medium.setString("Medium");
	m_medium.setFont(m_ArialBlackfont);
	m_medium.setPosition(450.0f, 350.0f);
	m_medium.setCharacterSize(50U);
	m_medium.setFillColor(sf::Color::White);

	m_hard.setString("Hard");
	m_hard.setFont(m_ArialBlackfont);
	m_hard.setPosition(450.0f, 500.0f);
	m_hard.setCharacterSize(50U);
	m_hard.setFillColor(sf::Color::White);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_introLogoTexture.loadFromFile("ASSETS\\IMAGES\\logo.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_introLogoSprite.setTexture(m_introLogoTexture);
	m_introLogoSprite.setPosition(420.0f, 280.0f);

}
/// <summary>
/// load rectangles used as hitboxes (through collision)
/// </summary>
void Game::setupHitboxes()
{
	m_playGameHitbox.setFillColor(sf::Color::Transparent);
	m_playGameHitbox.setPosition(450.0f, 200.0f);
	m_playGameHitbox.setSize(sf::Vector2f{ 120.0f,70.0f });

	m_highScoreHitbox.setFillColor(sf::Color::Transparent);
	m_highScoreHitbox.setPosition(360.0f, 350.0f);
	m_highScoreHitbox.setSize(sf::Vector2f{ 330.0f,70.0f });

	m_controlsHitbox.setFillColor(sf::Color::Transparent);
	m_controlsHitbox.setPosition(360.0f, 500.0f);
	m_controlsHitbox.setSize(sf::Vector2f{ 330.0f,70.0f });

	m_exitHitbox.setFillColor(sf::Color::Transparent);
	m_exitHitbox.setPosition(450.0f, 650.0f);
	m_exitHitbox.setSize(sf::Vector2f{ 120.0f,70.0f });
	
	m_backHitbox.setFillColor(sf::Color::Transparent);
	m_backHitbox.setPosition(450.0f, 700.0f);
	m_backHitbox.setSize(sf::Vector2f{ 150.0f,70.0f });

	m_easyHitbox.setFillColor(sf::Color::Green);
	m_easyHitbox.setPosition(450.0f, 200.0f);
	m_easyHitbox.setSize(sf::Vector2f{ 120.0f,70.0f });

	m_mediumHitbox.setFillColor(sf::Color::Blue);
	m_mediumHitbox.setPosition(450.0f, 350.0f);
	m_mediumHitbox.setSize(sf::Vector2f{ 330.0f,70.0f });

	m_hardHitbox.setFillColor(sf::Color::Red);
	m_hardHitbox.setPosition(450.0f, 500.0f);
	m_hardHitbox.setSize(sf::Vector2f{ 330.0f,70.0f });


}

/// <summary>
/// loads background image and sets it as background
/// </summary>
void Game::setupBackground()
{

	sf::IntRect background{ 0,0,200,200};

	if (!m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\background.jpg"))
	{
		std::cout << "Problem with loading background" << std::endl;
	}

	m_backgroundTexture.setRepeated(true);
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setTextureRect(background);
	m_backgroundSprite.setScale(sf::Vector2f{20,16});
	
	

}


/// <summary>
/// This function uses opacity to change text 
/// color so it seems like the text is flashing
/// </summary>
void Game::starGameTextFlash()
{
	sf::Color color(255, 255, 255, m_opacity);

	int frame;

	m_startGameFrameTimer += m_startGameFrameIncrement;

	frame = static_cast<int>(m_startGameFrameTimer) % 5;

	if (frame >= 3 && goingDown)
	{
		m_startGame.setFillColor(color);
		m_opacity -= 4;
		if (m_opacity <= 0)
		{
			goingDown = false;
		}
	}
	else if (frame >= 3)
	{
		m_startGame.setFillColor(color);
		m_opacity += 4;
		if (m_opacity >= 100)
		{
			goingDown = true;
		}
	}
}
/// <summary>
/// this function tracks position
/// of mouse if mouse button is pressed 
/// </summary>
/// <param name="t_event"></param>
void Game::mouseClick(sf::Event t_event)
{
	
	m_mouseClick.x = static_cast<float>(t_event.mouseButton.x);
	m_mouseClick.y = static_cast<float>(t_event.mouseButton.y);
	
	if (m_difficulty)
	{
		m_wait = 5;
	}
	if (m_game)
	{
		m_wait = 20;
	}

	

}
/// <summary>
/// this function tracks position
/// of mouse if mouse button is released
/// and creates sprite on mouse release
/// to track collision and proceed user
/// to another screen
/// </summary>
/// <param name="t_event"></param>
void Game::mouseRelease(sf::Event t_event)
{
	if (sf::Mouse::Left == t_event.mouseButton.button)
	{
		sf::Vector2f mouseRelease;

		mouseRelease.x = static_cast<float>(t_event.mouseButton.x);
		mouseRelease.y = static_cast<float>(t_event.mouseButton.y);

		m_mouseTracker.setPosition(mouseRelease.x, mouseRelease.y);
		m_mouseTracker.setSize(sf::Vector2f{ 5.0f, 5.0f });

		if (m_menu)
		{
			if (m_playGameHitbox.getGlobalBounds().intersects(m_mouseTracker.getGlobalBounds()))
			{
				m_menu = false;
				m_difficulty = true;

			}
			if (m_highScoreHitbox.getGlobalBounds().intersects(m_mouseTracker.getGlobalBounds()))
			{
				m_menu = false;
				m_highScoreScreen = true;

			}
			if (m_controlsHitbox.getGlobalBounds().intersects(m_mouseTracker.getGlobalBounds()))
			{
				m_menu = false;
				m_controlsScreen = true;

			}
			if (m_exitHitbox.getGlobalBounds().intersects(m_mouseTracker.getGlobalBounds()))
			{
				m_menu = false;

			}

		}
		if (m_controlsScreen || m_highScoreScreen || m_difficulty)
		{
			if (m_backHitbox.getGlobalBounds().intersects(m_mouseTracker.getGlobalBounds()))
			{
				m_controlsScreen = false;
				m_highScoreScreen = false;
				m_difficulty = false;
				m_menu = true;
			}
		}
		if (m_difficulty)
		{
			if (m_delay)
			{
				if (m_easyHitbox.getGlobalBounds().intersects(m_mouseTracker.getGlobalBounds()))
				{
					m_game = true;
					m_difficulty = false;

				}
				if (m_mediumHitbox.getGlobalBounds().intersects(m_mouseTracker.getGlobalBounds()))
				{
					m_game = true;
					m_difficulty = false;
				}
				if (m_hardHitbox.getGlobalBounds().intersects(m_mouseTracker.getGlobalBounds()))
				{
					m_game = true;
					m_difficulty = false;
				}
			}

		}
	}
}








