#pragma once

#include <SFML/Graphics.hpp>
#include <map>

#include "classes.h"
#include "variables.h"

void loadResources();

void initializeGraphics(sf::RenderWindow& window);

void drawScreen(sf::RenderWindow& window);

void setValues(sf::RenderWindow& window);

void setupCommonSprites(sf::RenderWindow& window);

void loadCursors();

int handleEvents(sf::RenderWindow& window, sf::Event& event);

void loadAnimations();

