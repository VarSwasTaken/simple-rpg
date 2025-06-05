#pragma once

#include <SFML/Graphics.hpp>
#include "variables.h"
#include "classes.h"

using namespace std;

int handleMouseButtonRelease(sf::RenderWindow& window, sf::Event& event, Screens& currentScreen, PlayerData& playerData, Player& player, map<string, sf::Sprite>& Sprites, map<string, sf::Text>& Texts, vector<sf::RectangleShape>& ClassBoxes, int& chosenClass, ClassData& classData, map<string, sf::RectangleShape>& Rectangles, vector<sf::RectangleShape>& EnemyBoxes, int& chosenEnemy, Enemy& enemy, map<string, Enemy>& Enemies, bool& ongoingFight);

void handleMouseButtonPressed(sf::RenderWindow& window, sf::Event& event, Screens& currentScreen, map<string, sf::RectangleShape>& Rectangles);

void handleTextEntered(sf::Event& event, Screens& currentScreen, map<string, sf::Text>& Texts);

void handleKeyPressed(sf::RenderWindow& window, sf::Event& event, Screens& currentScreen, map<string, sf::RectangleShape>& Rectangles, bool& isMoving);