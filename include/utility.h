#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>

#include "variables.h"
#include "classes.h"

PlayerData parseLine(const string& line);

void assignClassData(int health, int attack, int defence, int dodge, int classIdentifier, ClassData& classData);

void assignPlayerData(string className, ClassData& classData, PlayerData& playerData);

void handleCursorChange(sf::RenderWindow& window, const vector<sf::RectangleShape>& inputRectangles, const vector<sf::RectangleShape>& rectangles, const vector<sf::Sprite>& buttons, sf::Cursor* arrowCursor, sf::Cursor* textCursor, sf::Cursor* handCursor);

void centerTextToSprite(sf::Text& text, sf::Sprite& sprite);

void centerTextToBox(sf::Text& text, sf::RectangleShape& box);

void centerSpriteToBox(sf::Sprite& sprite, sf::RectangleShape& box);

void centerRectToSprite(sf::RectangleShape& rectangle, sf::Sprite& sprite);

void centerBoxToBox(sf::RectangleShape& rectangle1, sf::RectangleShape& rectangle2);

void setTextProperties(sf::Text& textBlock, sf::Font& font, string text, int size, sf::Color color);

bool enemyHit(int hitConversion);

bool dodgeAttack(int dodge);

bool checkLogin(sf::Text& input, string password, PlayerData& playerData);

bool accountExists(sf::Text& input);

bool isUsernameCharValid(int unicode);

void updateInputValues(sf::Text& InputText, int unicode);

string updatePasswordInputValues(sf::Text& InputText, int unicode, string passwordValue);

void updateNumericInputValues(sf::Text& InputText, int unicode);

void updateProfile(sf::Text& username, sf::Text& statistics, Player& player);

bool spriteClicked(sf::Sprite& sprite, sf::Event& event, sf::Window& window);

void changeClassChoice(sf::RenderWindow& window, vector<sf::RectangleShape>& boxes, int& chosenClass);

void changeEnemyChoice(sf::RenderWindow& window, vector<sf::RectangleShape>& boxes, int& chosenEnemy, Enemy& enemy, map<string, Enemy>& Enemies);

void updateAssignPoints(map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, Player& player);

void drawMenuIcons(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles);

bool isInside(sf::RectangleShape& box1, sf::RectangleShape& box2);