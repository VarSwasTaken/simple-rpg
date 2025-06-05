#pragma once

#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <windows.h>
//#include <math.h>
//#include <conio.h>
//#include <time.h>
//#include <fstream>
//#include <string>
//#include <sstream>
#include <map>
#include <optional>

#include "classes.h"
#include "utility.h"

using namespace std;

void initializeMainMenu(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts);

void drawMainMenu(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, sf::Cursor* ArrowCursor, sf::Cursor* TextCursor, sf::Cursor* HandCursor);

void initializeContinueNewGame(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts);

void drawNewGame(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, sf::Cursor* ArrowCursor, sf::Cursor* TextCursor, sf::Cursor* HandCursor);

void drawContinue(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, sf::Cursor* ArrowCursor, sf::Cursor* TextCursor, sf::Cursor* HandCursor);

void initializeCreationMenu(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, vector<sf::RectangleShape>& ClassBoxes);

void drawCreationMenu(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, sf::Cursor* ArrowCursor, sf::Cursor* TextCursor, sf::Cursor* HandCursor, vector<sf::RectangleShape>& ClassBoxes, map<string, AnimationManager>& Animations, sf::Clock& clock);

void initializeGameMenu(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts);

void drawGameMenu(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, sf::Cursor* ArrowCursor, sf::Cursor* TextCursor, sf::Cursor* HandCursor);

void initializeProfile(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, PlayerData& playerData);

void drawProfile(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, sf::Cursor* ArrowCursor, sf::Cursor* TextCursor, sf::Cursor* HandCursor, Player& player, map<string, AnimationManager>& Animations, sf::Clock& clock);

void initializeAssignPoints(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts);

void drawAssignPoints(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, sf::Cursor* ArrowCursor, sf::Cursor* TextCursor, sf::Cursor* HandCursor, Player& player);

void initializeBattleMenu(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, vector<sf::RectangleShape>& EnemyBoxes);

void drawBattleMenu(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, sf::Cursor* ArrowCursor, sf::Cursor* TextCursor, sf::Cursor* HandCursor, map<string, AnimationManager>& Animations, sf::Clock& clock, vector<sf::RectangleShape>& EnemyBoxes);

void initializeFight(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, Player& player);

void drawFight(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, sf::Cursor* ArrowCursor, sf::Cursor* TextCursor, sf::Cursor* HandCursor, map<string, AnimationManager>& Animations, sf::Clock& animationClock, Player& player, Enemy& enemy, bool& isMoving, bool& ongoingFight);