#include "../include/window.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Simple RPG", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    setValues(window);
    loadCursors();
    loadResources();
    loadAnimations();
    setupCommonSprites(window);
    initializeGraphics(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(!handleEvents(window, event)) 
                return 0;
        }
        drawScreen(window);
    }

    return 0;
}

