#include "../include/utility.h"

PlayerData parseLine(const string& line) {
    stringstream ss(line);
    PlayerData playerData_;

    ss >> playerData_.playerName;
    ss >> playerData_.password;
    ss >> playerData_.className;
    ss >> playerData_.classIdentifier;
    ss >> playerData_.level;
    ss >> playerData_.experience;
    ss >> playerData_.expNeeded;
    ss >> playerData_.health;
    ss >> playerData_.attack;
    ss >> playerData_.defence;
    ss >> playerData_.dodge;
    ss >> playerData_.killed;
    ss >> playerData_.points;

    return playerData_;
}

void assignClassData(int health, int attack, int defence, int dodge, int classIdentifier, ClassData& classData)
{
    classData.health = health;
    classData.attack = attack;
    classData.defence = defence;
    classData.dodge = dodge;
    classData.classIdentifier = classIdentifier;
}

void assignPlayerData(string className, ClassData& classData, PlayerData& playerData) {
    playerData.className = className;
    playerData.health = classData.health;
    playerData.attack = classData.attack;
    playerData.defence = classData.defence;
    playerData.dodge = classData.dodge;
    playerData.classIdentifier = classData.classIdentifier;
    playerData.level = 1;
    playerData.experience = 0;
    playerData.expNeeded = 100;
    playerData.killed = 0;
    playerData.points = 0;
}

void handleCursorChange(sf::RenderWindow& window, const vector<sf::RectangleShape>& inputRectangles, const vector<sf::RectangleShape>& rectangles, const vector<sf::Sprite>& buttons, sf::Cursor* arrowCursor, sf::Cursor* textCursor, sf::Cursor* handCursor) {
    sf::Vector2i mousePosPixel = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePosPixel);

    for (const auto& input : inputRectangles) {
        if (input.getGlobalBounds().contains(mousePos)) {
            window.setMouseCursor(*textCursor);
            return;
        }
    }

    for (const auto& rectangle : rectangles) {
        if (rectangle.getGlobalBounds().contains(mousePos)) {
            window.setMouseCursor(*handCursor);
            return;
        }
    }

    for (const auto& button : buttons) {
        if (button.getGlobalBounds().contains(mousePos)) {
            window.setMouseCursor(*handCursor);
            return;
        }
    }

    window.setMouseCursor(*arrowCursor);
}

void centerTextToSprite(sf::Text& text, sf::Sprite& sprite) {
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    sf::FloatRect textBounds = text.getLocalBounds();
    int x = spriteBounds.left + (spriteBounds.width / 2.f) - (textBounds.width / 2.f);
    int y = spriteBounds.top + (spriteBounds.height / 2.f) - (textBounds.height / 2.f) - textBounds.top;
    text.setPosition(x, y);
}

void centerTextToBox(sf::Text& text, sf::RectangleShape& box) {
    sf::FloatRect boxBounds = box.getGlobalBounds();
    sf::FloatRect textBounds = text.getLocalBounds();
    int x = boxBounds.left + (boxBounds.width / 2.f) - (textBounds.width / 2.f);
    int y = boxBounds.top + (boxBounds.height / 2.f) - (textBounds.height / 2.f) - textBounds.top;
    text.setPosition(x, y);
}

void centerSpriteToBox(sf::Sprite& sprite, sf::RectangleShape& box) {
    sf::FloatRect boxBounds = box.getGlobalBounds();
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    int x = boxBounds.left + (boxBounds.width / 2.f) - (spriteBounds.width / 2.f);
    int y = boxBounds.top + (boxBounds.height / 2.f) - (spriteBounds.height / 2.f);
    sprite.setPosition(x, y);
}

void centerRectToSprite(sf::RectangleShape& rectangle, sf::Sprite& sprite) {
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    sf::FloatRect rectangleBounds = rectangle.getGlobalBounds();
    int x = spriteBounds.left + (spriteBounds.width / 2.f) - (rectangleBounds.width / 2.f);
    int y = spriteBounds.top + (spriteBounds.height / 2.f) - (rectangleBounds.height / 2.f);
    rectangle.setPosition(x, y);
}

void centerBoxToBox(sf::RectangleShape& rectangle1, sf::RectangleShape& rectangle2) {
    sf::FloatRect rectBounds2 = rectangle2.getGlobalBounds();
    sf::FloatRect rectBounds1 = rectangle1.getGlobalBounds();
    int x = rectBounds2.left + (rectBounds2.width / 2.f) - (rectBounds1.width / 2.f);
    int y = rectBounds2.top + (rectBounds2.height / 2.f) - (rectBounds1.height / 2.f);
    rectangle1.setPosition(x, y);
}

void setTextProperties(sf::Text& textBlock, sf::Font& font, string text, int size, sf::Color color) {
    textBlock.setFont(font);
    textBlock.setString(text);
    textBlock.setCharacterSize(size);
    textBlock.setFillColor(color);
}

bool enemyHit(int hitConversion)
{
    int number = rand() % 100 + 1;
    if (number >= 1 && number <= hitConversion)
        return true;
    return false;
}

bool dodgeAttack(int dodge) {
    int number = rand() % 500 + 1;
    if (number >= 1 && number <= dodge)
        return true;
    return false;
}

bool checkLogin(sf::Text& input, string password, PlayerData& playerData) {
    fstream file;
    file.open("saves/saves.txt", ios::in);
    if (!file.is_open())
        return -1;
    string line;
    while (getline(file, line)) {
        PlayerData playerData_ = parseLine(line);
        if (playerData_.playerName == input.getString() && playerData_.password == password) {
            playerData = playerData_;
            file.close();
            return 1;
        }
    }
    file.close();
    return 0;
}

bool accountExists(sf::Text& input) {
    fstream file;
    file.open("saves/saves.txt", ios::in);
    if (!file.is_open()) {
        return -1;
    }
    string line;
    while (getline(file, line)) {
        PlayerData playerData_ = parseLine(line);
        if (playerData_.playerName == input.getString()) {
            file.close();
            return 1;
        }
    }
    file.close();
    return 0;
}

bool isUsernameCharValid(int unicode) {
    vector<unsigned int> validASCIIusername = { 45, 95 }; // {_, -}
    for (int i = 48; i <= 57; i++) { // digits
        validASCIIusername.push_back(i);
    }
    for (int i = 65; i <= 90; i++) { // capital letters
        validASCIIusername.push_back(i);
    }
    for (int i = 97; i <= 122; i++) { // non-capital letters
        validASCIIusername.push_back(i);
    }

    if (find(validASCIIusername.begin(), validASCIIusername.end(), unicode) != validASCIIusername.end())
        return 1;
    return 0;
}

void updateInputValues(sf::Text& InputText, int unicode) {
    string currentText = InputText.getString();
    if (unicode == '\b') {
        if (currentText.length() > 0)
            currentText.pop_back();
    }
    else if (isUsernameCharValid(unicode)) {
        if (currentText.length() < 31)
            currentText += static_cast<char>(unicode);
    }
    InputText.setString(currentText);
}

string updatePasswordInputValues(sf::Text& InputText, int unicode, string passwordValue) {
    string currentText = InputText.getString();
    if (unicode == '\b') {
        if (currentText.length() > 0) {
            currentText.pop_back();
            passwordValue.pop_back();
        }
    }
    else if (unicode >= 32 && unicode <= 126) {
        if (currentText.length() < 31) {
            currentText += "*";
            passwordValue += static_cast<char>(unicode);
        }
    }
    InputText.setString(currentText);
    return passwordValue;
}

void updateNumericInputValues(sf::Text& InputText, int unicode) {
    string currentText = InputText.getString();
    if (unicode == '\b') {
        if (currentText.length() > 0)
            currentText.pop_back();
    }
    else if (unicode >= 48 && unicode <= 57) {
        if (currentText.length() < 3)
            currentText += static_cast<char>(unicode);
    }
    InputText.setString(currentText);
}

void updateProfile(sf::Text& username, sf::Text& statistics, Player& player) {
    username.setString(player.getPlayerName());
    statistics.setString("CLASS: " + player.getClassName() + "\n");
    statistics.setString(statistics.getString() + "Experience: " + to_string(player.getLevel()) + "LVL " + "(" + to_string(player.getExperience()) + "/" + to_string(player.getExpNeeded()) + ")\n");
    statistics.setString(statistics.getString() + "Opponents killed: " + to_string(player.getEnemiesKilled()) + "\n\n");
    statistics.setString(statistics.getString() + "Health:      " + to_string(player.getHealth()) + "\n");
    statistics.setString(statistics.getString() + "Attack:      " + to_string(player.getAttack()) + "\n");
    statistics.setString(statistics.getString() + "Defence:   " + to_string(player.getDefence()) + "\n");
    statistics.setString(statistics.getString() + "Dodge:      " + to_string(player.getDodge()));
}

bool spriteClicked(sf::Sprite& sprite, sf::Event& event, sf::Window& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    if (sprite.getGlobalBounds().contains(mousePosF))
        return true;
    return false;
}

void changeClassChoice(sf::RenderWindow& window, vector<sf::RectangleShape>& boxes, int& chosenClass) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    for (int i = 0; i < boxes.size(); i++) {
        if (boxes[i].getGlobalBounds().contains(mousePosF)) {
            chosenClass = i+1;
        }
        boxes[i].setOutlineThickness(1);
    }
    boxes[chosenClass-1].setOutlineThickness(5);
}

void changeEnemyChoice(sf::RenderWindow& window, vector<sf::RectangleShape>& boxes, int& chosenEnemy, Enemy& enemy, map<string, Enemy>& Enemies) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    for (int i = 0; i < boxes.size(); i++) {
        if (boxes[i].getGlobalBounds().contains(mousePosF)) {
            chosenEnemy = i+1;
        }
        boxes[i].setOutlineThickness(1);
    }
    boxes[chosenEnemy-1].setOutlineThickness(5);
    switch (chosenEnemy) {
        case 1:
            enemy = Enemies["Fire Worm"];
            break;
        case 2:
            enemy = Enemies["Goblin"];
            break;
        case 3:
            enemy = Enemies["Skeleton"];
            break;
        case 4:
            enemy = Enemies["Mushroom"];
            break;
        case 5:
            enemy = Enemies["Shadow Warrior"];
            break;
        case 6:
            enemy = Enemies["Necromancer"];
            break;
        case 7:
            enemy = Enemies["Minotaur"];
            break;

    }
}

void updateAssignPoints(map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, Player& player) {
    Texts["CurrentHPText"].setString("Current: " + to_string(player.getHealth()));
    int x = Rectangles["HPInputBox"].getPosition().x + Rectangles["HPInputBox"].getGlobalBounds().width - Texts["CurrentHPText"].getGlobalBounds().width - 10;
    Texts["CurrentHPText"].setPosition(x, Texts["CurrentHPText"].getPosition().y);

    Texts["CurrentATKText"].setString("Current: " + to_string(player.getAttack()));
    x = Rectangles["ATKInputBox"].getPosition().x + Rectangles["ATKInputBox"].getGlobalBounds().width - Texts["CurrentATKText"].getGlobalBounds().width - 10;
    Texts["CurrentATKText"].setPosition(x, Texts["CurrentATKText"].getPosition().y);

    Texts["CurrentDEFText"].setString("Current: " + to_string(player.getDefence()));
    x = Rectangles["DEFInputBox"].getPosition().x + Rectangles["DEFInputBox"].getGlobalBounds().width - Texts["CurrentDEFText"].getGlobalBounds().width - 10;
    Texts["CurrentDEFText"].setPosition(x, Texts["CurrentDEFText"].getPosition().y);

    Texts["CurrentDDGText"].setString("Current: " + to_string(player.getDodge()));
    x = Rectangles["DDGInputBox"].getPosition().x + Rectangles["DDGInputBox"].getGlobalBounds().width - Texts["CurrentDDGText"].getGlobalBounds().width - 10;
    Texts["CurrentDDGText"].setPosition(x, Texts["CurrentDDGText"].getPosition().y);

    Texts["AvailablePointsText"].setString("Available points: " + to_string(player.getPoints()));
}

void drawMenuIcons(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles) {
    centerSpriteToBox(Sprites["FireWormMenuIcon"], Rectangles["FireWormBox"]);
    window.draw(Sprites["FireWormMenuIcon"]);
    centerSpriteToBox(Sprites["GoblinMenuIcon"], Rectangles["GoblinBox"]);
    Sprites["GoblinMenuIcon"].move(0, -10);
    window.draw(Sprites["GoblinMenuIcon"]);
    centerSpriteToBox(Sprites["SkeletonMenuIcon"], Rectangles["SkeletonBox"]);
    Sprites["SkeletonMenuIcon"].move(5, -13);
    window.draw(Sprites["SkeletonMenuIcon"]);
    centerSpriteToBox(Sprites["MushroomMenuIcon"], Rectangles["MushroomBox"]);
    Sprites["MushroomMenuIcon"].move(0, -25);
    window.draw(Sprites["MushroomMenuIcon"]);
    centerSpriteToBox(Sprites["ShadowWarriorMenuIcon"], Rectangles["ShadowWarriorBox"]);
    Sprites["ShadowWarriorMenuIcon"].move(0, -35);
    window.draw(Sprites["ShadowWarriorMenuIcon"]);
    centerSpriteToBox(Sprites["NecromancerMenuIcon"], Rectangles["NecromancerBox"]);
    Sprites["NecromancerMenuIcon"].move(0, -60);
    window.draw(Sprites["NecromancerMenuIcon"]);
    centerSpriteToBox(Sprites["MinotaurMenuIcon"], Rectangles["MinotaurBox"]);
    Sprites["MinotaurMenuIcon"].move(0, -37);
    window.draw(Sprites["MinotaurMenuIcon"]);
}

bool isInside(sf::RectangleShape& box1, sf::RectangleShape& box2) {
    int left_1 = box1.getPosition().x;
    int right_1 = left_1 + box1.getGlobalBounds().width;
    int left_2 = box2.getPosition().x;
    int right_2 = left_2 + box2.getGlobalBounds().width;
    if (left_1 >= left_2 && right_1 <= right_2)
        return true;
    return false;
}