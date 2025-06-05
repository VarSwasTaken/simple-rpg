#include "../include/events.h"
#include "../include/utility.h"

int x, y;
bool isEditingUsername = false;
bool isEditingPassword = false;
bool isEditingHp = false;
bool isEditingAtk = false;
bool isEditingDef = false;
bool isEditingDdg = false;
string passwordValue = "";

int handleMouseButtonRelease(sf::RenderWindow& window, sf::Event& event, Screens& currentScreen, PlayerData& playerData, Player& player, map<string, sf::Sprite>& Sprites, map<string, sf::Text>& Texts, vector<sf::RectangleShape>& ClassBoxes, int& chosenClass, ClassData& classData, map<string, sf::RectangleShape>& Rectangles, vector<sf::RectangleShape>& EnemyBoxes, int& chosenEnemy, Enemy& enemy, map<string, Enemy>& Enemies, bool& ongoingFight) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        switch (currentScreen) {
            case MainMenu:
                if (spriteClicked(Sprites["NewGameButton"], event, window))
                    currentScreen = NewGame;
                if (spriteClicked(Sprites["ContinueButton"], event, window))
                    currentScreen = Continue;
                break;

            case NewGame:
                if (spriteClicked(Sprites["BackButton"], event, window)) {
                    Texts["UsernameInputText"].setString("");
                    Texts["PasswordInputText"].setString("");
                    Texts["ErrorText"].setString("");
                    currentScreen = MainMenu;
                }
                if (spriteClicked(Sprites["LoginButton"], event, window)) {
                    if (Texts["UsernameInputText"].getString().toAnsiString().length() < 3) {
                        Texts["ErrorText"].setString("Username must be atleast 3 characters long");
                        x = (window.getSize().x - static_cast<int>(Texts["ErrorText"].getGlobalBounds().width)) / 2;
                        y = (window.getSize().y - static_cast<int>(Texts["ErrorText"].getGlobalBounds().height)) / 16 * 12.5;
                        Texts["ErrorText"].setPosition(x, y);
                    }
                    else if (Texts["PasswordInputText"].getString().toAnsiString().length() < 8) {
                        Texts["ErrorText"].setString("Password must be atleast 8 characters long");
                        x = (window.getSize().x - static_cast<int>(Texts["ErrorText"].getGlobalBounds().width)) / 2;
                        y = (window.getSize().y - static_cast<int>(Texts["ErrorText"].getGlobalBounds().height)) / 16 * 12.5;
                        Texts["ErrorText"].setPosition(x, y);
                    }
                    else if (accountExists(Texts["UsernameInputText"])) {
                        Texts["ErrorText"].setString("Username taken");
                        x = (window.getSize().x - static_cast<int>(Texts["ErrorText"].getGlobalBounds().width)) / 2;
                        y = (window.getSize().y - static_cast<int>(Texts["ErrorText"].getGlobalBounds().height)) / 16 * 12.5;
                        Texts["ErrorText"].setPosition(x, y);
                    }
                    else {
                        Texts["ErrorText"].setString("");
                        playerData.playerName = Texts["UsernameInputText"].getString();
                        currentScreen = Creation;
                    }
                }
                break;

            case Continue:
                if (spriteClicked(Sprites["BackButton"], event, window)) {
                    Texts["UsernameInputText"].setString("");
                    Texts["PasswordInputText"].setString("");
                    Texts["ErrorText"].setString("");
                    currentScreen = MainMenu;
                }
                if (spriteClicked(Sprites["LoginButton"], event, window)) {
                    if (checkLogin(Texts["UsernameInputText"], passwordValue, playerData)) {
                        Texts["ErrorText"].setString("");
                        player = Player(playerData);
                        currentScreen = GameMenu;
                    }
                    else {
                        Texts["ErrorText"].setString("Wrong username or password");
                        x = (window.getSize().x - static_cast<int>(Texts["ErrorText"].getGlobalBounds().width)) / 2;
                        y = (window.getSize().y - static_cast<int>(Texts["ErrorText"].getGlobalBounds().height)) / 16 * 12.5;
                        Texts["ErrorText"].setPosition(x, y);
                    }
                }
                break;

                case Creation:
                    changeClassChoice(window, ClassBoxes, chosenClass);
                    if (spriteClicked(Sprites["ConfirmButton"], event, window)) {
                        switch (chosenClass) {
                            case 1:
                                assignClassData(100, 60, 50, 10, 1, classData);
                                assignPlayerData("Knight", classData, playerData);
                                player = Player(playerData);
                                break;
                            case 2:
                                assignClassData(50, 50, 20, 100, 2, classData);
                                assignPlayerData("Archer", classData, playerData);
                                player = Player(playerData);
                                break;
                            case 3:
                                assignClassData(40, 100, 30, 50, 3, classData);
                                assignPlayerData("Wizard", classData, playerData);
                                player = Player(playerData);
                                break;
                        }
                        currentScreen = GameMenu;
                    }
                    break;

                case GameMenu:
                    if (spriteClicked(Sprites["ProfileButton"], event, window))
                        currentScreen = Profile;
                    if (spriteClicked(Sprites["AssignPointsButton"], event, window))
                        currentScreen = AssignPoints;
                    if (spriteClicked(Sprites["FightButton"], event, window))
                        currentScreen = BattleMenu;
                    if (spriteClicked(Sprites["SaveButton"], event, window)) {
                        if (player.saveToFile(passwordValue)) {
                            cout << "Game saved" << endl;
                            return 0;
                        }
                    }
                    break;

                case Profile:
                    if (spriteClicked(Sprites["BackButton"], event, window))
                        currentScreen = GameMenu;
                    break;

                case AssignPoints:
                    if (spriteClicked(Sprites["BackButton"], event, window)) {
                        currentScreen = GameMenu;
                    }
                    if (spriteClicked(Sprites["ConfirmButton2"], event, window)) {
                        string HP = Texts["HPInputText"].getString().toAnsiString();
                        string ATK = Texts["ATKInputText"].getString().toAnsiString();
                        string DEF = Texts["DEFInputText"].getString().toAnsiString();
                        string DDG = Texts["DDGInputText"].getString().toAnsiString();
                        int HPValue = HP.length() > 0 ? stoi(HP) : 0;
                        int ATKValue = ATK.length() > 0 ? stoi(ATK) : 0;
                        int DEFValue = DEF.length() > 0 ? stoi(DEF) : 0;
                        int DDGValue = DDG.length() > 0 ? stoi(DDG) : 0;
                        if (player.assignPoints(HPValue, ATKValue, DEFValue, DDGValue) == 0) {
                            Texts["ErrorText2"].setString("You don't have enough points to assign");
                            x = (window.getSize().x - static_cast<int>(Texts["ErrorText2"].getGlobalBounds().width)) / 2;
                            y = Sprites["ConfirmButton2"].getGlobalBounds().top - 35;
                            Texts["ErrorText2"].setPosition(x, y);
                        }
                        else {
                            Texts["ErrorText2"].setString("");
                            Texts["HPInputText"].setString("");
                            Texts["ATKInputText"].setString("");
                            Texts["DEFInputText"].setString("");
                            Texts["DDGInputText"].setString("");
                            updateAssignPoints(Rectangles, Texts, player);
                        }
                    }
                    break;
                case BattleMenu:
                    if (spriteClicked(Sprites["BackButton"], event, window)) {
                        currentScreen = GameMenu;
                    }
                    changeEnemyChoice(window, EnemyBoxes, chosenEnemy, enemy, Enemies);
                    if (spriteClicked(Sprites["StartFightButton"], event, window)) {
                        currentScreen = Fight;
                        ongoingFight = true;
                    }
                    break;
                case Fight:
                    if (spriteClicked(Sprites["BackButton"], event, window)) {
                        currentScreen = GameMenu;
                    }
                    break;
        }
        return 1;
    }
}

void handleMouseButtonPressed(sf::RenderWindow& window, sf::Event& event, Screens& currentScreen, map<string, sf::RectangleShape>& Rectangles) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        switch (currentScreen) {
            case NewGame:
            case Continue:
                if (Rectangles["UsernameInputBox"].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    isEditingUsername = true;
                    isEditingPassword = false;
                    Rectangles["UsernameInputBox"].setFillColor(sf::Color(68, 15, 71));
                    Rectangles["PasswordInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                }
                else if (Rectangles["PasswordInputBox"].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    isEditingPassword = true;
                    isEditingUsername = false;
                    Rectangles["UsernameInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                    Rectangles["PasswordInputBox"].setFillColor(sf::Color(68, 15, 71));
                }
                else {
                    isEditingUsername = false;
                    isEditingPassword = false;
                    Rectangles["UsernameInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                    Rectangles["PasswordInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                }
                break;

            case AssignPoints:
                if (Rectangles["HPInputBox"].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    isEditingHp = true;
                    isEditingAtk = false;
                    isEditingDef = false;
                    isEditingDdg = false;
                    Rectangles["HPInputBox"].setFillColor(sf::Color(68, 15, 71));
                    Rectangles["ATKInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                    Rectangles["DEFInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                    Rectangles["DDGInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                }
                else if (Rectangles["ATKInputBox"].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    isEditingHp = false;
                    isEditingAtk = true;
                    isEditingDef = false;
                    isEditingDdg = false;
                    Rectangles["HPInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                    Rectangles["ATKInputBox"].setFillColor(sf::Color(68, 15, 71));
                    Rectangles["DEFInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                    Rectangles["DDGInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                }
                else if (Rectangles["DEFInputBox"].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    isEditingHp = false;
                    isEditingAtk = false;
                    isEditingDef = true;
                    isEditingDdg = false;
                    Rectangles["HPInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                    Rectangles["ATKInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                    Rectangles["DEFInputBox"].setFillColor(sf::Color(68, 15, 71));
                    Rectangles["DDGInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                }
                else if (Rectangles["DDGInputBox"].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    isEditingHp = false;
                    isEditingAtk = false;
                    isEditingDef = false;
                    isEditingDdg = true;
                    Rectangles["HPInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                    Rectangles["ATKInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                    Rectangles["DEFInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                    Rectangles["DDGInputBox"].setFillColor(sf::Color(68, 15, 71));
                }
                else {
                    isEditingHp = false;
                    isEditingAtk = false;
                    isEditingDef = false;
                    isEditingDdg = false;
                    Rectangles["HPInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                    Rectangles["ATKInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                    Rectangles["DEFInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                    Rectangles["DDGInputBox"].setFillColor(sf::Color(0, 0, 0, 64));
                }
                break;
        }
    }
}

void handleTextEntered(sf::Event& event, Screens& currentScreen, map<string, sf::Text>& Texts) {
    switch (currentScreen) {
        case NewGame:
        case Continue:
            if (isEditingUsername)
                updateInputValues(Texts["UsernameInputText"], event.text.unicode);
            else if (isEditingPassword)
                passwordValue = updatePasswordInputValues(Texts["PasswordInputText"], event.text.unicode, passwordValue);
            break;

        case AssignPoints:
            if (isEditingHp)
                updateNumericInputValues(Texts["HPInputText"], event.text.unicode);
            else if (isEditingAtk)
                updateNumericInputValues(Texts["ATKInputText"], event.text.unicode);
            else if (isEditingDef)
                updateNumericInputValues(Texts["DEFInputText"], event.text.unicode);
            else if (isEditingDdg)
                updateNumericInputValues(Texts["DDGInputText"], event.text.unicode);
            break;
    }
}

void handleKeyPressed(sf::RenderWindow& window, sf::Event& event, Screens& currentScreen, map<string, sf::RectangleShape>& Rectangles, bool& isMoving) {
    if (event.key.code == sf::Keyboard::Space && isMoving) {
        switch (currentScreen) {
            case Fight:
                isMoving = false;
                break;
        }
    }
}