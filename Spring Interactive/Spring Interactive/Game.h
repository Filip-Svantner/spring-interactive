/// <summary>
/// author Filip Svantner March 2025
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

const int HEIGHT = 800; // screen height
const int WIDTH = 1000;// screen width

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();
	void setupHitboxes();
	void setupBackground();
	void starGameTextFlash();
	void mouseClick(sf::Event t_event);
	void mouseRelease(sf::Event t_event);
	


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used for text

	//mouse variables
	sf::Vector2f m_mouseClick; // used for tracking mouse position
	sf::RectangleShape m_mouseTracker; // used for mouse collision
	
	//intro screen
	sf::Text m_introMessage; // text used for name of the game on screen
	sf::Texture m_introLogoTexture; // texture used for introduction screen logo
	sf::Sprite m_introLogoSprite; // sprite used for introduction screen logo
	sf::Texture m_backgroundTexture; // texture used for background
	sf::Sprite m_backgroundSprite; // sprite used for background
	sf::Text m_startGame; // Press <key> to start game text
	
	float m_startGameFrameIncrement{ 0.6f }; // how much the frame goes up
	float m_startGameFrameTimer{ 0.0f }; // used for counting frames
	bool goingDown = true; // used for either taking from or adding to opacity
	int m_opacity{ 100 }; // controls opacity to flash text
	//end intro screen

	//menu screen 
	sf::Text m_playGame; // text for start game
	sf::RectangleShape m_playGameHitbox; // hitbox used to track collision with mouse
	sf::Text m_highScore; // text for high score
	sf::RectangleShape m_highScoreHitbox; // hitbox used to track collision with mouse
	sf::Text m_controls; // text for controls
	sf::RectangleShape m_controlsHitbox; // hitbox used to track collision with mouse
	sf::Text m_exit; // text for exit
	sf::RectangleShape m_exitHitbox; // hitbox used to track collision with mouse
	//end menu screen

	//difficulty screen
	sf::Text m_easy; // text for easy difficulty
	sf::RectangleShape m_easyHitbox; // hitbox used to track collision with mouse
	sf::Text m_medium; // text for medium difficulty
	sf::RectangleShape m_mediumHitbox; // hitbox used to track collision with mouse
	sf::Text m_hard; // text for hard difficulty
	sf::RectangleShape m_hardHitbox; // hitbox used to track collision with mouse

	//back button
	sf::Text m_back; // text for back button
	sf::RectangleShape m_backHitbox; // hitbox used to track collision with mouse

	int m_wait = 0;
	bool m_delay = false;
	

	bool m_highScoreScreen = false; // checks if we are in high score screen
	bool m_controlsScreen = false; // checks if we are in controls screen
	bool m_difficulty = false; // checks if we are in difficulty screen
	bool m_game = false; // checks if 
	bool m_menu = false;  // checks if we are in menu
	bool m_intro = true; // checks if we are in introduction screen
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

