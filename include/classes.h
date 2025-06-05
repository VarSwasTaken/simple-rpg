#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <map>
#include <string>

#include "variables.h"

using namespace std;

class ResourceManager {
    static std::map<Textures, sf::Texture> textures;
    static std::map<Fonts, sf::Font> fonts;
public:
    static void loadTexture(Textures name, std::string filePath);
    static void loadFont(Fonts name, std::string filePath);
    static sf::Texture& getTexture(Textures id);
    static sf::Font& getFont(Fonts id);
};

class AnimationManager {
private:
    map<string, sf::Texture> m_textures;
    map<string, sf::Vector2i> m_indicies;
    map<string, sf::Vector2i> m_startingIndicies;
    map<string, sf::Vector2i> m_endingIndicies;
    map<string, sf::Vector2i> m_sheetSizes;
    map<string, sf::Vector2i> m_spriteSizes;
    map<string, int> m_frequencies;
    map<string, int> m_timesUpdated;
public:
    void update(string animation, sf::Sprite& sprite);
    void addAnimation(string animation, sf::Texture texture, sf::Vector2i sheetSize,
        sf::Vector2i spriteSize, sf::Vector2i index = sf::Vector2i(0, 0), int frequency = 0,
        sf::Vector2i startingIndex = sf::Vector2i(0, 0));
    void deleteAnimation(string animation);
    int getFramesAmount(const std::string& animation) const;
};

class Statistics
{
public:
    int getHealth();
    int getAttack();
    int getDefence();
    int getDodge();
    int getCurrentHealth();
    void setCurrentHealth(int health);
protected:
    int level;
    int health;
    int attack;
    int defence;
    int dodge;
    int currentHealth;
};

class Enemy :public Statistics
{
public:
    Enemy(string enemyName, int level, int health, int attack, int defence, int dodge, int expGiven, int hitConversion, int critChance, int enemyIdentifier);
    Enemy();
    int getExpGiven();
    int getHitConversion();
    int getCritChance();
    int getEnemyIdentifier();
    string getEnemyName();
private:
    string enemyName;
    int expGiven;
    int hitConversion; 
    int critChance;
    int enemyIdentifier;
};

class Player :public Statistics
{
public:
    Player(PlayerData data);
    string getClassName();
    string getPlayerName();
    string className;
    int getLevel();
    int getExperience();
    int getExpNeeded();
    int getEnemiesKilled();
    int getPoints();
    int getClassIdentifier();
    void levelUp();
    int assignPoints(int hp, int atk, int def, int ddg);
    void battle(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, map<string, AnimationManager>& Animationsn, sf::Clock& animationsClock, Enemy& enemy, bool& isMoving, bool& fightStarting);
    void enemyKilled(int expAdded);
    void removeExp(int expRemoved);
    bool saveToFile(string password);
private:
    string playerName;
    int playerExperience;
    int expNeeded;
    int availablePoints;
    int enemiesKilled;
    int classIdentifier;
};