#include "../include/screens.h"

void initializeMainMenu(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts) {
    sf::Sprite NewGameButton(ResourceManager::getTexture(Textures::Button));
    int x = (window.getSize().x - static_cast<int>(NewGameButton.getGlobalBounds().width)) / 2;
    int y = (window.getSize().y - static_cast<int>(NewGameButton.getGlobalBounds().height)) / 8 * 5;
    NewGameButton.setPosition(static_cast<float>(x), static_cast<float>(y));

    sf::Sprite ContinueButton(ResourceManager::getTexture(Textures::Button));
    y = (window.getSize().y - static_cast<int>(ContinueButton.getGlobalBounds().height)) / 8 * 7;
    ContinueButton.setPosition(static_cast<float>(x), static_cast<float>(y));

    sf::Sprite LoginButton(ResourceManager::getTexture(Textures::Button));
    y = (window.getSize().y - static_cast<int>(LoginButton.getGlobalBounds().height)) / 16 * 15;
    LoginButton.setPosition(static_cast<float>(x), static_cast<float>(y));

    Sprites["NewGameButton"] = NewGameButton;
    Sprites["ContinueButton"] = ContinueButton;
    Sprites["LoginButton"] = LoginButton;

    sf::Text NewGameButtonText;
    setTextProperties(NewGameButtonText, ResourceManager::getFont(NewRocker), "NEW GAME", 20, sf::Color::White);
    NewGameButtonText.setOutlineColor(sf::Color(123, 1, 143));
    NewGameButtonText.setOutlineThickness(1);
    centerTextToSprite(NewGameButtonText, NewGameButton);
    NewGameButtonText.move(0, 3.5);

    sf::Text ContinueButtonText;
    setTextProperties(ContinueButtonText, ResourceManager::getFont(NewRocker), "CONTINUE", 20, sf::Color::White);
    ContinueButtonText.setOutlineColor(sf::Color(123, 1, 143));
    ContinueButtonText.setOutlineThickness(1);
    centerTextToSprite(ContinueButtonText, ContinueButton);
    ContinueButtonText.move(0, 3.5);

    sf::Text LoginButtonText;
    setTextProperties(LoginButtonText, ResourceManager::getFont(NewRocker), "LOGIN", 20, sf::Color::White);
    LoginButtonText.setOutlineColor(sf::Color(123, 1, 143));
    LoginButtonText.setOutlineThickness(1);

    Texts["NewGameButtonText"] = NewGameButtonText;
    Texts["ContinueButtonText"] = ContinueButtonText;
    Texts["LoginButtonText"] = LoginButtonText;
}

void drawMainMenu(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, sf::Cursor* ArrowCursor, sf::Cursor* TextCursor, sf::Cursor* HandCursor) {
    window.clear();
    window.draw(Sprites["Background"]);
    window.draw(Sprites["AppName"]);
    window.draw(Sprites["NewGameButton"]);
    window.draw(Sprites["ContinueButton"]);
    window.draw(Texts["NewGameButtonText"]);
    window.draw(Texts["ContinueButtonText"]);
    handleCursorChange(window, {}, {}, { Sprites["ContinueButton"], Sprites["NewGameButton"] }, ArrowCursor, TextCursor, HandCursor);
    window.display();
}

void initializeContinueNewGame(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts) {
    sf::RectangleShape UsernameInputBox(sf::Vector2f(360, 30));
    UsernameInputBox.setFillColor(sf::Color(0, 0, 0, 64));
    UsernameInputBox.setOutlineColor(sf::Color::White);
    UsernameInputBox.setOutlineThickness(1);
    int x = (window.getSize().x - static_cast<int>(UsernameInputBox.getGlobalBounds().width)) / 2;
    int y = (window.getSize().y - static_cast<int>(UsernameInputBox.getGlobalBounds().height)) / 16 * 9.5;
    UsernameInputBox.setPosition(static_cast<float>(x), static_cast<float>(y));

    sf::RectangleShape PasswordInputBox(sf::Vector2f(360, 30));
    PasswordInputBox.setFillColor(sf::Color(0, 0, 0, 64));
    PasswordInputBox.setOutlineColor(sf::Color::White);
    PasswordInputBox.setOutlineThickness(1);
    x = (window.getSize().x - static_cast<int>(PasswordInputBox.getGlobalBounds().width)) / 2;
    y = (window.getSize().y - static_cast<int>(PasswordInputBox.getGlobalBounds().height)) / 16 * 12;
    PasswordInputBox.setPosition(static_cast<float>(x), static_cast<float>(y));

    Rectangles["UsernameInputBox"] = UsernameInputBox;
    Rectangles["PasswordInputBox"] = PasswordInputBox;

    sf::Text UsernameHeaderText;
    setTextProperties(UsernameHeaderText, ResourceManager::getFont(NewRocker), "USERNAME", 20, sf::Color::White);
    x = (window.getSize().x - static_cast<int>(UsernameHeaderText.getGlobalBounds().width)) / 2;
    y = (window.getSize().y - static_cast<int>(UsernameHeaderText.getGlobalBounds().height)) / 16 * 8;
    UsernameHeaderText.setPosition(static_cast<float>(x), static_cast<float>(y));

    sf::Text PasswordHeaderText;
    setTextProperties(PasswordHeaderText, ResourceManager::getFont(NewRocker), "PASSWORD", 20, sf::Color::White);
    x = (window.getSize().x - static_cast<int>(PasswordHeaderText.getGlobalBounds().width)) / 2;
    y = (window.getSize().y - static_cast<int>(PasswordHeaderText.getGlobalBounds().height)) / 16 * 10.5;
    PasswordHeaderText.setPosition(static_cast<float>(x), static_cast<float>(y));

    Texts["UsernameHeaderText"] = UsernameHeaderText;
    Texts["PasswordHeaderText"] = PasswordHeaderText;

    sf::Text UsernameInputText;
    setTextProperties(UsernameInputText, ResourceManager::getFont(LatoRegular), "QWERTYUIOPLKJHGFDSAZXCVBNMmnbvcxzlkjhgfdsapoiuytrewq1234567890#!@$%*&", 15, sf::Color::White);
    y = UsernameInputBox.getPosition().y + (UsernameInputBox.getGlobalBounds().height - UsernameInputText.getLocalBounds().height) / 2 - UsernameInputText.getLocalBounds().top;
    UsernameInputText.setPosition(UsernameInputBox.getPosition().x + 10, y);
    UsernameInputText.setString("");

    sf::Text PasswordInputText;
    setTextProperties(PasswordInputText, ResourceManager::getFont(LatoRegular), "**", 15, sf::Color::White);
    y = PasswordInputBox.getPosition().y + (PasswordInputBox.getGlobalBounds().height - PasswordInputText.getLocalBounds().height) / 2 - PasswordInputText.getLocalBounds().top;
    PasswordInputText.setPosition(PasswordInputBox.getPosition().x + 10, y);
    PasswordInputText.setString("");
    string passwordValue = "";

    sf::Text ErrorText;
    setTextProperties(ErrorText, ResourceManager::getFont(LatoRegular), "", 15, sf::Color::Red);

    Texts["UsernameInputText"] = UsernameInputText;
    Texts["PasswordInputText"] = PasswordInputText;
    Texts["ErrorText"] = ErrorText;
}

void drawNewGame(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, sf::Cursor* ArrowCursor, sf::Cursor* TextCursor, sf::Cursor* HandCursor) {
    window.clear();
    window.draw(Sprites["Background"]);
    window.draw(Sprites["AppName"]);
    window.draw(Sprites["BackButton"]);
    window.draw(Texts["UsernameHeaderText"]);
    window.draw(Rectangles["UsernameInputBox"]);
    window.draw(Texts["UsernameInputText"]);
    window.draw(Texts["PasswordHeaderText"]);
    window.draw(Rectangles["PasswordInputBox"]);
    window.draw(Texts["PasswordInputText"]);
    window.draw(Sprites["LoginButton"]);
    window.draw(Texts["ErrorText"]);
    Texts["LoginButtonText"].setString("REGISTER");
    centerTextToSprite(Texts["LoginButtonText"], Sprites["LoginButton"]);
    Texts["LoginButtonText"].move(0, 3.5);
    window.draw(Texts["LoginButtonText"]);
    handleCursorChange(window, { Rectangles["UsernameInputBox"], Rectangles["PasswordInputBox"] }, {}, { Sprites["LoginButton"], Sprites["BackButton"]}, ArrowCursor, TextCursor, HandCursor);
    window.display();
}

void drawContinue(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, sf::Cursor* ArrowCursor, sf::Cursor* TextCursor, sf::Cursor* HandCursor) {
    window.clear();
    window.draw(Sprites["Background"]);
    window.draw(Sprites["AppName"]);
    window.draw(Sprites["BackButton"]);
    window.draw(Texts["UsernameHeaderText"]);
    window.draw(Rectangles["UsernameInputBox"]);
    window.draw(Texts["UsernameInputText"]);
    window.draw(Texts["PasswordHeaderText"]);
    window.draw(Rectangles["PasswordInputBox"]);
    window.draw(Texts["PasswordInputText"]);
    window.draw(Sprites["LoginButton"]);
    window.draw(Texts["ErrorText"]);
    Texts["LoginButtonText"].setString("LOGIN");
    centerTextToSprite(Texts["LoginButtonText"], Sprites["LoginButton"]);
    Texts["LoginButtonText"].move(0, 3.5);
    window.draw(Texts["LoginButtonText"]);
    handleCursorChange(window, { Rectangles["UsernameInputBox"], Rectangles["PasswordInputBox"] }, {}, { Sprites["LoginButton"], Sprites["BackButton"]}, ArrowCursor, TextCursor, HandCursor);
    window.display();
}

void initializeCreationMenu(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, vector<sf::RectangleShape>& ClassBoxes) {
    sf::Sprite KnightIconCreation(ResourceManager::getTexture(Textures::KnightIdle));
    KnightIconCreation.setScale(3, 3);
    int x = 90;
    int y = 105;
    KnightIconCreation.setPosition(x, y);

    sf::Sprite ArcherIconCreation(ResourceManager::getTexture(Textures::ArcherIdle));
    ArcherIconCreation.setScale(2.4, 2.4);
    x = 155;
    y = -15;
    ArcherIconCreation.setPosition(x, y);

    sf::Sprite WizardIconCreation(ResourceManager::getTexture(Textures::WizardIdle));
    WizardIconCreation.setScale(1.35, 1.35);
    x = 625;
    y = 100;
    WizardIconCreation.setPosition(x, y);

    sf::Sprite ConfirmButton(ResourceManager::getTexture(Textures::Button));
    x = (window.getSize().x - static_cast<int>(ConfirmButton.getGlobalBounds().width)) / 2;
    y = window.getSize().y - ConfirmButton.getGlobalBounds().height - 30;
    ConfirmButton.setPosition(static_cast<float>(x), static_cast<float>(y));

    Sprites["KnightIconCreation"] = KnightIconCreation;
    Sprites["ArcherIconCreation"] = ArcherIconCreation;
    Sprites["WizardIconCreation"] = WizardIconCreation;
    Sprites["ConfirmButton"] = ConfirmButton;

    sf::RectangleShape KnightBox(sf::Vector2f(225, 300));
    KnightBox.setFillColor(sf::Color::Transparent);
    KnightBox.setOutlineColor(sf::Color::White);
    KnightBox.setOutlineThickness(5);
    x = 120;
    y = 160;
    KnightBox.setPosition(x, y);

    sf::RectangleShape ArcherBox(sf::Vector2f(225, 300));
    ArcherBox.setFillColor(sf::Color::Transparent);
    ArcherBox.setOutlineColor(sf::Color::White);
    ArcherBox.setOutlineThickness(1);
    x = (window.getSize().x - static_cast<int>(ArcherBox.getGlobalBounds().width)) / 2;
    y = 160;
    ArcherBox.setPosition(x, y);

    sf::RectangleShape WizardBox(sf::Vector2f(225, 300));
    WizardBox.setFillColor(sf::Color::Transparent);
    WizardBox.setOutlineColor(sf::Color::White);
    WizardBox.setOutlineThickness(1);
    x = window.getSize().x - 225 - 120;
    y = 160;
    WizardBox.setPosition(x, y);

    Rectangles["KnightBox"] = KnightBox;
    Rectangles["ArcherBox"] = ArcherBox;
    Rectangles["WizardBox"] = WizardBox;
    ClassBoxes.push_back(KnightBox);
    ClassBoxes.push_back(ArcherBox);
    ClassBoxes.push_back(WizardBox);

    sf::Text ConfirmButtonText;
    setTextProperties(ConfirmButtonText, ResourceManager::getFont(NewRocker), "CONFIRM", 20, sf::Color::White);
    ConfirmButtonText.setOutlineColor(sf::Color(123, 1, 143));
    ConfirmButtonText.setOutlineThickness(1);
    centerTextToSprite(ConfirmButtonText, ConfirmButton);
    ConfirmButtonText.move(0, 3.5);

    sf::Text CreationHeaderText;
    setTextProperties(CreationHeaderText, ResourceManager::getFont(NewRocker), "Choose your class", 50, sf::Color::White);
    x = (window.getSize().x - static_cast<int>(CreationHeaderText.getGlobalBounds().width)) / 2;
    y = 50;
    CreationHeaderText.setPosition(x, y);

    sf::Text KnightHeaderText;
    setTextProperties(KnightHeaderText, ResourceManager::getFont(NewRocker), "Knight", 30, sf::Color::White);
    centerTextToBox(KnightHeaderText, KnightBox);
    KnightHeaderText.move(0, 5);

    sf::Text ArcherHeaderText;
    setTextProperties(ArcherHeaderText, ResourceManager::getFont(NewRocker), "Archer", 30, sf::Color::White);
    centerTextToBox(ArcherHeaderText, ArcherBox);
    ArcherHeaderText.move(0, 5);

    sf::Text WizardHeaderText;
    setTextProperties(WizardHeaderText, ResourceManager::getFont(NewRocker), "Wizard", 30, sf::Color::White);
    centerTextToBox(WizardHeaderText, WizardBox);
    WizardHeaderText.move(0, 5);

    sf::Text KnightStatsText;
    setTextProperties(KnightStatsText, ResourceManager::getFont(NewRocker), "Health: 100\nAttack: 60\nDefence: 50\nDodge: 10", 20, sf::Color::White);
    x = KnightBox.getGlobalBounds().left + 20;
    y = KnightHeaderText.getGlobalBounds().top + KnightHeaderText.getGlobalBounds().height + 10;
    KnightStatsText.setPosition(x, y);

    sf::Text ArcherStatsText;
    setTextProperties(ArcherStatsText, ResourceManager::getFont(NewRocker), "Health: 50\nAttack: 50\nDefence: 20\nDodge: 100", 20, sf::Color::White);
    x = ArcherBox.getGlobalBounds().left + 20;
    y = ArcherHeaderText.getGlobalBounds().top + ArcherHeaderText.getGlobalBounds().height + 10;
    ArcherStatsText.setPosition(x, y);

    sf::Text WizardStatsText;
    setTextProperties(WizardStatsText, ResourceManager::getFont(NewRocker), "Health: 40\nAttack: 100\nDefence: 30\nDodge: 50", 20, sf::Color::White);
    x = WizardBox.getGlobalBounds().left + 20;
    y = WizardHeaderText.getGlobalBounds().top + WizardHeaderText.getGlobalBounds().height + 10;
    WizardStatsText.setPosition(x, y);

    Texts["ConfirmButtonText"] = ConfirmButtonText;
    Texts["CreationHeaderText"] = CreationHeaderText;
    Texts["KnightHeaderText"] = KnightHeaderText;
    Texts["ArcherHeaderText"] = ArcherHeaderText;
    Texts["WizardHeaderText"] = WizardHeaderText;
    Texts["KnightStatsText"] = KnightStatsText;
    Texts["ArcherStatsText"] = ArcherStatsText;
    Texts["WizardStatsText"] = WizardStatsText;
}

void drawCreationMenu(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, sf::Cursor* ArrowCursor, sf::Cursor* TextCursor, sf::Cursor* HandCursor, vector<sf::RectangleShape>& ClassBoxes, map<string, AnimationManager>& Animations, sf::Clock& clock) {
    window.clear();
    window.draw(Sprites["Background"]);
    window.draw(Sprites["BackButton"]);
    window.draw(Texts["CreationHeaderText"]);
    for (const auto& box : ClassBoxes) {
        window.draw(box);
    }
    window.draw(Sprites["ConfirmButton"]);
    window.draw(Texts["ConfirmButtonText"]);
    static float elapsedTime = 0.0f;
    elapsedTime += clock.restart().asSeconds();
    if (elapsedTime >= 0.12f) {
        elapsedTime = 0.0f;
        Animations["Knight"].update("Idle", Sprites["KnightIconCreation"]);
        Animations["Archer"].update("Idle", Sprites["ArcherIconCreation"]);
        Animations["Wizard"].update("Idle", Sprites["WizardIconCreation"]);
    }
    window.draw(Sprites["KnightIconCreation"]);
    window.draw(Sprites["ArcherIconCreation"]);
    window.draw(Sprites["WizardIconCreation"]);
    window.draw(Texts["KnightHeaderText"]);
    window.draw(Texts["ArcherHeaderText"]);
    window.draw(Texts["WizardHeaderText"]);
    window.draw(Texts["KnightStatsText"]);
    window.draw(Texts["ArcherStatsText"]);
    window.draw(Texts["WizardStatsText"]);
    handleCursorChange(window, {}, ClassBoxes, { Sprites["ConfirmButton"], Sprites["BackButton"]}, ArrowCursor, TextCursor, HandCursor);
    window.display();
}

void initializeGameMenu(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts) {
    sf::Sprite ProfileButton(ResourceManager::getTexture(Textures::Button));
    int x = (window.getSize().x - static_cast<int>(ProfileButton.getGlobalBounds().width)) / 2 - 200;
    int y = window.getSize().y / 8 * 3.5;
    ProfileButton.setPosition(x, y);

    sf::Sprite FightButton(ResourceManager::getTexture(Textures::Button));
    x = (window.getSize().x - static_cast<int>(ProfileButton.getGlobalBounds().width)) / 2 + 200;
    y = window.getSize().y / 8 * 3.5;
    FightButton.setPosition(x, y);

    sf::Sprite AssignPointsButton(ResourceManager::getTexture(Textures::Button));
    x = (window.getSize().x - static_cast<int>(AssignPointsButton.getGlobalBounds().width)) / 2 - 200;
    y = window.getSize().y / 8 * 5.5;
    AssignPointsButton.setPosition(x, y);

    sf::Sprite SaveButton(ResourceManager::getTexture(Textures::Button));
    x = (window.getSize().x - static_cast<int>(SaveButton.getGlobalBounds().width)) / 2 + 200;
    y = window.getSize().y / 8 * 5.5;
    SaveButton.setPosition(x, y);

    Sprites["ProfileButton"] = ProfileButton;
    Sprites["FightButton"] = FightButton;
    Sprites["AssignPointsButton"] = AssignPointsButton;
    Sprites["SaveButton"] = SaveButton;
         
    sf::Text ProfileButtonText;
    setTextProperties(ProfileButtonText, ResourceManager::getFont(NewRocker), "PLAYER PROFILE", 15, sf::Color::White);
    ProfileButtonText.setOutlineColor(sf::Color(123, 1, 143));
    ProfileButtonText.setOutlineThickness(1);
    centerTextToSprite(ProfileButtonText, ProfileButton);
    ProfileButtonText.move(0, 3.5);

    sf::Text FightButtonText;
    setTextProperties(FightButtonText, ResourceManager::getFont(NewRocker), "FIGHT", 20, sf::Color::White);
    FightButtonText.setOutlineColor(sf::Color(123, 1, 143));
    FightButtonText.setOutlineThickness(1);
    centerTextToSprite(FightButtonText, FightButton);
    FightButtonText.move(0, 3.5);

    sf::Text AssignPointsButtonText;
    setTextProperties(AssignPointsButtonText, ResourceManager::getFont(NewRocker), "ASSIGN POINTS", 15, sf::Color::White);
    AssignPointsButtonText.setOutlineColor(sf::Color(123, 1, 143));
    AssignPointsButtonText.setOutlineThickness(1);
    centerTextToSprite(AssignPointsButtonText, AssignPointsButton);
    AssignPointsButtonText.move(0, 3.5);

    sf::Text SaveButtonText;
    setTextProperties(SaveButtonText, ResourceManager::getFont(NewRocker), "SAVE & EXIT", 20, sf::Color::White);
    SaveButtonText.setOutlineColor(sf::Color(123, 1, 143));
    SaveButtonText.setOutlineThickness(1);
    centerTextToSprite(SaveButtonText, SaveButton);
    SaveButtonText.move(0, 3.5);

    Texts["ProfileButtonText"] = ProfileButtonText;
    Texts["FightButtonText"] = FightButtonText;
    Texts["AssignPointsButtonText"] = AssignPointsButtonText;
    Texts["SaveButtonText"] = SaveButtonText;
}

void drawGameMenu(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, sf::Cursor* ArrowCursor, sf::Cursor* TextCursor, sf::Cursor* HandCursor) {
    window.clear();
    window.draw(Sprites["Background"]);
    window.draw(Sprites["AppName"]);
    window.draw(Sprites["ProfileButton"]);
    window.draw(Texts["ProfileButtonText"]);
    window.draw(Sprites["FightButton"]);
    window.draw(Texts["FightButtonText"]);
    window.draw(Sprites["AssignPointsButton"]);
    window.draw(Texts["AssignPointsButtonText"]);
    window.draw(Sprites["SaveButton"]);
    window.draw(Texts["SaveButtonText"]);
    handleCursorChange(window, {}, {}, { Sprites["ProfileButton"], Sprites["FightButton"], Sprites["AssignPointsButton"], Sprites["SaveButton"] }, ArrowCursor, TextCursor, HandCursor);
    window.display();
}

void initializeProfile(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, PlayerData& playerData) {
    sf::Sprite ProfileArcher(ResourceManager::getTexture(Textures::ArcherIdle));
    ProfileArcher.setScale(3.2, 3.2);
    int x = 50;
    int y = (window.getSize().y - static_cast<int>(ProfileArcher.getGlobalBounds().height)) / 8 * 5;
    ProfileArcher.setPosition(x, y);
    ProfileArcher.move(-270, -110);

    sf::Sprite ProfileKnight(ResourceManager::getTexture(Textures::KnightIdle));
    ProfileKnight.setScale(4, 4);
    x = 50;
    y = (window.getSize().y - static_cast<int>(ProfileKnight.getGlobalBounds().height)) / 8 * 5;
    ProfileKnight.setPosition(x, y);

    sf::Sprite ProfileWizard(ResourceManager::getTexture(Textures::WizardIdle));
    ProfileWizard.setScale(1.8, 1.8);
    x = 50;
    y = (window.getSize().y - static_cast<int>(ProfileWizard.getGlobalBounds().height)) / 8 * 5;
    ProfileWizard.setPosition(x, y);

    Sprites["ProfileArcher"] = ProfileArcher;
    Sprites["ProfileKnight"] = ProfileKnight;
    Sprites["ProfileWizard"] = ProfileWizard;

    sf::Text ProfileHeaderText;
    setTextProperties(ProfileHeaderText, ResourceManager::getFont(NewRocker), "Player profile", 50, sf::Color::White);
    x = (window.getSize().x - static_cast<int>(ProfileHeaderText.getGlobalBounds().width)) / 2;
    y = 100;
    ProfileHeaderText.setPosition(x, y);

    sf::Text ProfileUsernameText;
    setTextProperties(ProfileUsernameText, ResourceManager::getFont(NewRocker), playerData.playerName, 25, sf::Color::White);

    sf::Text StatisticsText;
    setTextProperties(StatisticsText, ResourceManager::getFont(NewRocker), "", 20, sf::Color::White);
    x = (window.getSize().x) / 2 + 50;
    y = (window.getSize().y) / 2 - 40;
    StatisticsText.setPosition(x, y);

    Texts["ProfileHeaderText"] = ProfileHeaderText;
    Texts["ProfileUsernameText"] = ProfileUsernameText;
    Texts["StatisticsText"] = StatisticsText;
}

void drawProfile(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, sf::Cursor* ArrowCursor, sf::Cursor* TextCursor, sf::Cursor* HandCursor, Player& player, map<string, AnimationManager>& Animations, sf::Clock& clock) {
    window.clear();
    window.draw(Sprites["Background"]);
    window.draw(Sprites["BackButton"]);
    window.draw(Texts["ProfileHeaderText"]);
    static float elapsedTime = 0.0f;
    elapsedTime += clock.restart().asSeconds();
    switch (player.getClassIdentifier()) {
        case 1:
            if (elapsedTime >= 0.12f) {
                elapsedTime = 0.0f;
                Animations["Knight"].update("Idle", Sprites["ProfileKnight"]);
            }
            window.draw(Sprites["ProfileKnight"]);
            centerTextToSprite(Texts["ProfileUsernameText"], Sprites["ProfileKnight"]);
            Texts["ProfileUsernameText"].move(0, 120);
            break;
        case 2:
            if (elapsedTime >= 0.12f) {
                elapsedTime = 0.0f;
                Animations["Archer"].update("Idle", Sprites["ProfileArcher"]);
            }
            window.draw(Sprites["ProfileArcher"]);
            centerTextToSprite(Texts["ProfileUsernameText"], Sprites["ProfileArcher"]);
            Texts["ProfileUsernameText"].move(0, 240);
            break;
        case 3:
            if (elapsedTime >= 0.12f) {
                elapsedTime = 0.0f;
                Animations["Wizard"].update("Idle", Sprites["ProfileWizard"]);
            }
            window.draw(Sprites["ProfileWizard"]);
            centerTextToSprite(Texts["ProfileUsernameText"], Sprites["ProfileWizard"]);
            Texts["ProfileUsernameText"].move(-20, 120);
            break;
    }
    updateProfile(Texts["ProfileUsernameText"], Texts["StatisticsText"], player);
    window.draw(Texts["StatisticsText"]);
    window.draw(Texts["ProfileUsernameText"]);
    handleCursorChange(window, {}, {}, {Sprites["BackButton"]}, ArrowCursor, TextCursor, HandCursor);
    window.display();
}

void initializeAssignPoints(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts) {
    sf::Sprite ConfirmButton2(ResourceManager::getTexture(Textures::Button));
    int x = (window.getSize().x - static_cast<int>(ConfirmButton2.getGlobalBounds().width)) / 2;
    int y = window.getSize().y - ConfirmButton2.getGlobalBounds().height - 30;
    ConfirmButton2.setPosition(static_cast<float>(x), static_cast<float>(y));

    Sprites["ConfirmButton2"] = ConfirmButton2;

    sf::RectangleShape HPInputBox(sf::Vector2f(330, 30));
    HPInputBox.setFillColor(sf::Color(0, 0, 0, 64));
    HPInputBox.setOutlineColor(sf::Color::White);
    HPInputBox.setOutlineThickness(1);
    x = (window.getSize().x - static_cast<int>(HPInputBox.getGlobalBounds().width)) / 2;
    y = 250;
    HPInputBox.setPosition(static_cast<float>(x), static_cast<float>(y));

    sf::RectangleShape ATKInputBox(sf::Vector2f(330, 30));
    ATKInputBox.setFillColor(sf::Color(0, 0, 0, 64));
    ATKInputBox.setOutlineColor(sf::Color::White);
    ATKInputBox.setOutlineThickness(1);
    x = (window.getSize().x - static_cast<int>(ATKInputBox.getGlobalBounds().width)) / 2;
    y = 300;
    ATKInputBox.setPosition(static_cast<float>(x), static_cast<float>(y));

    sf::RectangleShape DEFInputBox(sf::Vector2f(330, 30));
    DEFInputBox.setFillColor(sf::Color(0, 0, 0, 64));
    DEFInputBox.setOutlineColor(sf::Color::White);
    DEFInputBox.setOutlineThickness(1);
    x = (window.getSize().x - static_cast<int>(DEFInputBox.getGlobalBounds().width)) / 2;
    y = 350;
    DEFInputBox.setPosition(static_cast<float>(x), static_cast<float>(y));

    sf::RectangleShape DDGInputBox(sf::Vector2f(330, 30));
    DDGInputBox.setFillColor(sf::Color(0, 0, 0, 64));
    DDGInputBox.setOutlineColor(sf::Color::White);
    DDGInputBox.setOutlineThickness(1);
    x = (window.getSize().x - static_cast<int>(DDGInputBox.getGlobalBounds().width)) / 2;
    y = 400;
    DDGInputBox.setPosition(static_cast<float>(x), static_cast<float>(y));

    Rectangles["HPInputBox"] = HPInputBox;
    Rectangles["ATKInputBox"] = ATKInputBox;
    Rectangles["DEFInputBox"] = DEFInputBox;
    Rectangles["DDGInputBox"] = DDGInputBox;

    sf::Text AssignPointsHeaderText;
    setTextProperties(AssignPointsHeaderText, ResourceManager::getFont(NewRocker), "Assign points", 50, sf::Color::White);
    x = (window.getSize().x - static_cast<int>(AssignPointsHeaderText.getGlobalBounds().width)) / 2;
    y = 50;
    AssignPointsHeaderText.setPosition(x, y);

    sf::Text AssignPointsSubheaderText;
    setTextProperties(AssignPointsSubheaderText, ResourceManager::getFont(LatoLight), "+X points = +X skill points to the chosen stat", 12, sf::Color::White);
    x = (window.getSize().x - static_cast<int>(AssignPointsSubheaderText.getGlobalBounds().width)) / 2;
    y = 120;
    AssignPointsSubheaderText.setPosition(x, y);

    sf::Text AvailablePointsText;
    setTextProperties(AvailablePointsText, ResourceManager::getFont(NewRocker), "Available points: 5", 20, sf::Color::White);
    x = (window.getSize().x - static_cast<int>(AvailablePointsText.getGlobalBounds().width)) / 2;
    y = 200;
    AvailablePointsText.setPosition(x, y);

    sf::Text HPText;
    setTextProperties(HPText, ResourceManager::getFont(NewRocker), "+HP:", 20, sf::Color::White);
    centerTextToBox(HPText, HPInputBox);
    x = 270;
    HPText.setPosition(x+12, HPText.getPosition().y);

    sf::Text ATKText;
    setTextProperties(ATKText, ResourceManager::getFont(NewRocker), "+ATK:", 20, sf::Color::White);
    centerTextToBox(ATKText, ATKInputBox);
    ATKText.setPosition(x, ATKText.getPosition().y);

    sf::Text DEFText;
    setTextProperties(DEFText, ResourceManager::getFont(NewRocker), "+DEF:", 20, sf::Color::White);
    centerTextToBox(DEFText, DEFInputBox);
    DEFText.setPosition(x+1, DEFText.getPosition().y);

    sf::Text DDGText;
    setTextProperties(DDGText, ResourceManager::getFont(NewRocker), "+DDG:", 20, sf::Color::White);
    centerTextToBox(DDGText, DDGInputBox);
    DDGText.setPosition(x, DDGText.getPosition().y);

    sf::Text CurrentHPText;
    setTextProperties(CurrentHPText, ResourceManager::getFont(LatoLight), "Current: 120", 12, sf::Color::White);
    centerTextToBox(CurrentHPText, HPInputBox);

    sf::Text CurrentATKText;
    setTextProperties(CurrentATKText, ResourceManager::getFont(LatoLight), "Current: 120", 12, sf::Color::White);
    centerTextToBox(CurrentATKText, ATKInputBox);

    sf::Text CurrentDEFText;
    setTextProperties(CurrentDEFText, ResourceManager::getFont(LatoLight), "Current: 120", 12, sf::Color::White);
    centerTextToBox(CurrentDEFText, DEFInputBox);

    sf::Text CurrentDDGText;
    setTextProperties(CurrentDDGText, ResourceManager::getFont(LatoLight), "Current: 120", 12, sf::Color::White);
    centerTextToBox(CurrentDDGText, DDGInputBox);

    sf::Text HPInputText;
    setTextProperties(HPInputText, ResourceManager::getFont(LatoBold), "1234567890", 15, sf::Color::White);
    y = HPInputBox.getPosition().y + (HPInputBox.getGlobalBounds().height - HPInputText.getLocalBounds().height) / 2 - HPInputText.getLocalBounds().top;
    HPInputText.setPosition(HPInputBox.getPosition().x + 10, y);
    HPInputText.setString("");

    sf::Text ATKInputText;
    setTextProperties(ATKInputText, ResourceManager::getFont(LatoBold), "1234567890", 15, sf::Color::White);
    y = ATKInputBox.getPosition().y + (ATKInputBox.getGlobalBounds().height - ATKInputText.getLocalBounds().height) / 2 - ATKInputText.getLocalBounds().top;
    ATKInputText.setPosition(ATKInputBox.getPosition().x + 10, y);
    ATKInputText.setString("");

    sf::Text DEFInputText;
    setTextProperties(DEFInputText, ResourceManager::getFont(LatoBold), "1234567890", 15, sf::Color::White);
    y = DEFInputBox.getPosition().y + (DEFInputBox.getGlobalBounds().height - DEFInputText.getLocalBounds().height) / 2 - DEFInputText.getLocalBounds().top;
    DEFInputText.setPosition(DEFInputBox.getPosition().x + 10, y);
    DEFInputText.setString("");

    sf::Text DDGInputText;
    setTextProperties(DDGInputText, ResourceManager::getFont(LatoBold), "1234567890", 15, sf::Color::White);
    y = DDGInputBox.getPosition().y + (DDGInputBox.getGlobalBounds().height - DDGInputText.getLocalBounds().height) / 2 - DDGInputText.getLocalBounds().top;
    DDGInputText.setPosition(DDGInputBox.getPosition().x + 10, y);
    DDGInputText.setString("");

    sf::Text ErrorText2;
    setTextProperties(ErrorText2, ResourceManager::getFont(LatoRegular), "", 15, sf::Color::Red);

    Texts["AssignPointsHeaderText"] = AssignPointsHeaderText;
    Texts["AssignPointsSubheaderText"] = AssignPointsSubheaderText;
    Texts["AvailablePointsText"] = AvailablePointsText;
    Texts["HPText"] = HPText;
    Texts["ATKText"] = ATKText;
    Texts["DEFText"] = DEFText;
    Texts["DDGText"] = DDGText;
    Texts["CurrentHPText"] = CurrentHPText;
    Texts["CurrentATKText"] = CurrentATKText;
    Texts["CurrentDEFText"] = CurrentDEFText;
    Texts["CurrentDDGText"] = CurrentDDGText;
    Texts["HPInputText"] = HPInputText;
    Texts["ATKInputText"] = ATKInputText;
    Texts["DEFInputText"] = DEFInputText;
    Texts["DDGInputText"] = DDGInputText;
    Texts["ErrorText2"] = ErrorText2;
}

void drawAssignPoints(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, sf::Cursor* ArrowCursor, sf::Cursor* TextCursor, sf::Cursor* HandCursor, Player& player) {
    window.clear();
    window.draw(Sprites["Background"]);
    window.draw(Sprites["BackButton"]);
    window.draw(Texts["AssignPointsHeaderText"]);
    window.draw(Texts["AssignPointsSubheaderText"]);
    window.draw(Texts["AvailablePointsText"]);
    window.draw(Texts["HPText"]);
    window.draw(Texts["ATKText"]);
    window.draw(Texts["DEFText"]);
    window.draw(Texts["DDGText"]);
    window.draw(Rectangles["HPInputBox"]);
    window.draw(Rectangles["ATKInputBox"]);
    window.draw(Rectangles["DEFInputBox"]);
    window.draw(Rectangles["DDGInputBox"]);
    window.draw(Texts["HPInputText"]);
    window.draw(Texts["ATKInputText"]);
    window.draw(Texts["DEFInputText"]);
    window.draw(Texts["DDGInputText"]);
    window.draw(Texts["CurrentHPText"]);
    window.draw(Texts["CurrentATKText"]);
    window.draw(Texts["CurrentDEFText"]);
    window.draw(Texts["CurrentDDGText"]);
    window.draw(Sprites["ConfirmButton2"]);
    window.draw(Texts["ConfirmButtonText"]);
    window.draw(Texts["ErrorText2"]);
    updateAssignPoints(Rectangles, Texts, player);
    handleCursorChange(window, { Rectangles["HPInputBox"], Rectangles["ATKInputBox"], Rectangles["DEFInputBox"], Rectangles["DDGInputBox"] }, {}, {Sprites["ConfirmButton"], Sprites["BackButton"]}, ArrowCursor, TextCursor, HandCursor);
    window.display();
}

void initializeBattleMenu(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, vector<sf::RectangleShape>& EnemyBoxes) {
    sf::RectangleShape FireWormBox(sf::Vector2f(150, 150));
    sf::RectangleShape GoblinBox(sf::Vector2f(150, 150));
    sf::RectangleShape SkeletonBox(sf::Vector2f(150, 150));
    sf::RectangleShape MushroomBox(sf::Vector2f(150, 150));

    int squares = 4;
    int windowWidth = window.getSize().x;
    int squareSize = 150;
    float totalSpacing = windowWidth - (squares * squareSize);
    float gap = totalSpacing / (squares + 1);

    std::vector<sf::RectangleShape> TopSquares = { FireWormBox, GoblinBox, SkeletonBox, MushroomBox };
    for (int i = 0; i < squares; i++) {
        TopSquares[i].setFillColor(sf::Color::Transparent);
        TopSquares[i].setOutlineColor(sf::Color::White);
        TopSquares[i].setOutlineThickness(1);

        int x = static_cast<int>(gap + i * (squareSize + gap));
        int y = 150;

        TopSquares[i].setPosition(x, y);
    }

    TopSquares[0].setOutlineThickness(5);

    Rectangles["FireWormBox"] = TopSquares[0];
    Rectangles["GoblinBox"] = TopSquares[1];
    Rectangles["SkeletonBox"] = TopSquares[2];
    Rectangles["MushroomBox"] = TopSquares[3];
    EnemyBoxes.push_back(TopSquares[0]);
    EnemyBoxes.push_back(TopSquares[1]);
    EnemyBoxes.push_back(TopSquares[2]);
    EnemyBoxes.push_back(TopSquares[3]);

    sf::RectangleShape NecromancerBox(sf::Vector2f(150, 150));
    NecromancerBox.setFillColor(sf::Color::Transparent);
    NecromancerBox.setOutlineColor(sf::Color(192, 192, 192));
    NecromancerBox.setOutlineThickness(1);
    float x = (window.getSize().x - NecromancerBox.getGlobalBounds().width) / 2;
    int y = 350;
    NecromancerBox.setPosition(x, y);

    sf::RectangleShape ShadowWarriorBox(sf::Vector2f(150, 150));
    ShadowWarriorBox.setFillColor(sf::Color::Transparent);
    ShadowWarriorBox.setOutlineColor(sf::Color(143, 67, 33));
    ShadowWarriorBox.setOutlineThickness(1);
    x = NecromancerBox.getGlobalBounds().left - ShadowWarriorBox.getGlobalBounds().width - gap;
    y = 350;
    ShadowWarriorBox.setPosition(x, y);

    sf::RectangleShape MinotaurBox(sf::Vector2f(150, 150));
    MinotaurBox.setFillColor(sf::Color::Transparent);
    MinotaurBox.setOutlineColor(sf::Color(212, 175, 55));
    MinotaurBox.setOutlineThickness(1);
    x = NecromancerBox.getGlobalBounds().left + NecromancerBox.getGlobalBounds().width + gap;
    y = 350;
    MinotaurBox.setPosition(x, y);

    Rectangles["ShadowWarriorBox"] = ShadowWarriorBox;
    Rectangles["NecromancerBox"] = NecromancerBox;
    Rectangles["MinotaurBox"] = MinotaurBox;
    EnemyBoxes.push_back(ShadowWarriorBox);
    EnemyBoxes.push_back(NecromancerBox);
    EnemyBoxes.push_back(MinotaurBox);

    sf::Sprite BronzeLaurel(ResourceManager::getTexture(Textures::BronzeLaurel));
    sf::FloatRect spriteBounds = BronzeLaurel.getGlobalBounds();
    sf::FloatRect rectBounds = ShadowWarriorBox.getGlobalBounds();
    float diff = spriteBounds.width - rectBounds.width;
    x = rectBounds.left - diff/2;
    y = rectBounds.top + rectBounds.height - 30;
    BronzeLaurel.setPosition(x, y);

    sf::Sprite SilverLaurel(ResourceManager::getTexture(Textures::SilverLaurel));
    spriteBounds = SilverLaurel.getGlobalBounds();
    rectBounds = NecromancerBox.getGlobalBounds();
    diff = spriteBounds.width - rectBounds.width;
    x = rectBounds.left - diff / 2;
    y = rectBounds.top + rectBounds.height - 30;
    SilverLaurel.setPosition(x, y);

    sf::Sprite GoldLaurel(ResourceManager::getTexture(Textures::GoldLaurel));
    spriteBounds = GoldLaurel.getGlobalBounds();
    rectBounds = MinotaurBox.getGlobalBounds();
    diff = spriteBounds.width - rectBounds.width;
    x = rectBounds.left - diff / 2;
    y = rectBounds.top + rectBounds.height - 30;
    GoldLaurel.setPosition(x, y);

    sf::Sprite FireWormMenuIcon(ResourceManager::getTexture(Textures::FireWormIdle));
    FireWormMenuIcon.setScale(1.4, 1.4);

    sf::Sprite GoblinMenuIcon(ResourceManager::getTexture(Textures::GoblinIdle));
    GoblinMenuIcon.setScale(1.7, 1.7);

    sf::Sprite SkeletonMenuIcon(ResourceManager::getTexture(Textures::SkeletonIdle));
    SkeletonMenuIcon.setScale(2.2, 2.2);

    sf::Sprite MushroomMenuIcon(ResourceManager::getTexture(Textures::MushroomIdle));
    MushroomMenuIcon.setScale(1.8, 1.8);

    sf::Sprite ShadowWarriorMenuIcon(ResourceManager::getTexture(Textures::ShadowWarriorIdle));
    ShadowWarriorMenuIcon.setScale(2.2, 2.2);

    sf::Sprite NecromancerMenuIcon(ResourceManager::getTexture(Textures::NecromancerIdle));
    NecromancerMenuIcon.setScale(1.7, 1.7);

    sf::Sprite MinotaurMenuIcon(ResourceManager::getTexture(Textures::MinotaurIdle));
    MinotaurMenuIcon.setScale(1.6, 1.6);

    sf::Sprite StartFightButton(ResourceManager::getTexture(Textures::StartFightButton));
    x = 800;
    y = 50;
    StartFightButton.setPosition(x, y);

    Sprites["BronzeLaurel"] = BronzeLaurel;
    Sprites["SilverLaurel"] = SilverLaurel;
    Sprites["GoldLaurel"] = GoldLaurel;
    Sprites["FireWormMenuIcon"] = FireWormMenuIcon;
    Sprites["GoblinMenuIcon"] = GoblinMenuIcon;
    Sprites["SkeletonMenuIcon"] = SkeletonMenuIcon;
    Sprites["MushroomMenuIcon"] = MushroomMenuIcon;
    Sprites["ShadowWarriorMenuIcon"] = ShadowWarriorMenuIcon;
    Sprites["NecromancerMenuIcon"] = NecromancerMenuIcon;
    Sprites["MinotaurMenuIcon"] = MinotaurMenuIcon;
    Sprites["StartFightButton"] = StartFightButton;

    sf::Text BattleHeaderText;
    setTextProperties(BattleHeaderText, ResourceManager::getFont(NewRocker), "Battle", 50, sf::Color::White);
    x = (window.getSize().x - static_cast<int>(BattleHeaderText.getGlobalBounds().width)) / 2;
    y = 30;
    BattleHeaderText.setPosition(x, y);

    sf::Text BattleSubheaderText;
    setTextProperties(BattleSubheaderText, ResourceManager::getFont(LatoLight), "Choose your enemy!", 12, sf::Color::White);
    x = (window.getSize().x - static_cast<int>(BattleSubheaderText.getGlobalBounds().width)) / 2;
    y = 95;
    BattleSubheaderText.setPosition(x, y);

    sf::Text FireWormHeaderText;
    setTextProperties(FireWormHeaderText, ResourceManager::getFont(NewRocker), "Fire Worm", 19, sf::Color::White);
    centerTextToBox(FireWormHeaderText, TopSquares[0]);
    FireWormHeaderText.move(0, 40);

    sf::Text FireWormSubheaderText;
    setTextProperties(FireWormSubheaderText, ResourceManager::getFont(LatoLight), "Suggested level: 1", 12, sf::Color::White);
    centerTextToBox(FireWormSubheaderText, TopSquares[0]);
    FireWormSubheaderText.move(0, 60);

    sf::Text GoblinHeaderText;
    setTextProperties(GoblinHeaderText, ResourceManager::getFont(NewRocker), "Goblin", 19, sf::Color::White);
    centerTextToBox(GoblinHeaderText, TopSquares[1]);
    GoblinHeaderText.move(0, 40);

    sf::Text GoblinSubheaderText;
    setTextProperties(GoblinSubheaderText, ResourceManager::getFont(LatoLight), "Suggested level: 5", 12, sf::Color::White);
    centerTextToBox(GoblinSubheaderText, TopSquares[1]);
    GoblinSubheaderText.move(0, 60);

    sf::Text SkeletonHeaderText;
    setTextProperties(SkeletonHeaderText, ResourceManager::getFont(NewRocker), "Skeleton", 19, sf::Color::White);
    centerTextToBox(SkeletonHeaderText, TopSquares[2]);
    SkeletonHeaderText.move(0, 40);

    sf::Text SkeletonSubheaderText;
    setTextProperties(SkeletonSubheaderText, ResourceManager::getFont(LatoLight), "Suggested level: 10", 12, sf::Color::White);
    centerTextToBox(SkeletonSubheaderText, TopSquares[2]);
    SkeletonSubheaderText.move(0, 60);

    sf::Text MushroomHeaderText;
    setTextProperties(MushroomHeaderText, ResourceManager::getFont(NewRocker), "Mushroom", 19, sf::Color::White);
    centerTextToBox(MushroomHeaderText, TopSquares[3]);
    MushroomHeaderText.move(0, 40);

    sf::Text MushroomSubheaderText;
    setTextProperties(MushroomSubheaderText, ResourceManager::getFont(LatoLight), "Suggested level: 15", 12, sf::Color::White);
    centerTextToBox(MushroomSubheaderText, TopSquares[3]);
    MushroomSubheaderText.move(0, 60);

    sf::Text ShadowWarriorHeaderText;
    setTextProperties(ShadowWarriorHeaderText, ResourceManager::getFont(NewRocker), "Shadow Warrior", 19, sf::Color::White);
    centerTextToBox(ShadowWarriorHeaderText, ShadowWarriorBox);
    ShadowWarriorHeaderText.move(0, 40);

    sf::Text ShadowWarriorSubheaderText;
    setTextProperties(ShadowWarriorSubheaderText, ResourceManager::getFont(LatoLight), "Suggested level: 20", 12, sf::Color::White);
    centerTextToBox(ShadowWarriorSubheaderText, ShadowWarriorBox);
    ShadowWarriorSubheaderText.move(0, 60);

    sf::Text NecromancerHeaderText;
    setTextProperties(NecromancerHeaderText, ResourceManager::getFont(NewRocker), "Necromancer", 19, sf::Color::White);
    centerTextToBox(NecromancerHeaderText, NecromancerBox);
    NecromancerHeaderText.move(0, 40);

    sf::Text NecromancerSubheaderText;
    setTextProperties(NecromancerSubheaderText, ResourceManager::getFont(LatoLight), "Suggested level: 25", 12, sf::Color::White);
    centerTextToBox(NecromancerSubheaderText, NecromancerBox);
    NecromancerSubheaderText.move(0, 60);

    sf::Text MinotaurHeaderText;
    setTextProperties(MinotaurHeaderText, ResourceManager::getFont(NewRocker), "Minotaur", 19, sf::Color::White);
    centerTextToBox(MinotaurHeaderText, MinotaurBox);
    MinotaurHeaderText.move(0, 40);

    sf::Text MinotaurSubheaderText;
    setTextProperties(MinotaurSubheaderText, ResourceManager::getFont(LatoLight), "Suggested level: 30", 12, sf::Color::White);
    centerTextToBox(MinotaurSubheaderText, MinotaurBox);
    MinotaurSubheaderText.move(0, 60);

    Texts["BattleHeaderText"] = BattleHeaderText;
    Texts["BattleSubheaderText"] = BattleSubheaderText;
    Texts["FireWormHeaderText"] = FireWormHeaderText;
    Texts["FireWormSubheaderText"] = FireWormSubheaderText;
    Texts["GoblinHeaderText"] = GoblinHeaderText;
    Texts["GoblinSubheaderText"] = GoblinSubheaderText;
    Texts["SkeletonHeaderText"] = SkeletonHeaderText;
    Texts["SkeletonSubheaderText"] = SkeletonSubheaderText;
    Texts["MushroomHeaderText"] = MushroomHeaderText;
    Texts["MushroomSubheaderText"] = MushroomSubheaderText;
    Texts["ShadowWarriorHeaderText"] = ShadowWarriorHeaderText;
    Texts["ShadowWarriorSubheaderText"] = ShadowWarriorSubheaderText;
    Texts["NecromancerHeaderText"] = NecromancerHeaderText;
    Texts["NecromancerSubheaderText"] = NecromancerSubheaderText;
    Texts["MinotaurHeaderText"] = MinotaurHeaderText;
    Texts["MinotaurSubheaderText"] = MinotaurSubheaderText;
}

void drawBattleMenu(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, sf::Cursor* ArrowCursor, sf::Cursor* TextCursor, sf::Cursor* HandCursor, map<string, AnimationManager>& Animations, sf::Clock& clock, vector<sf::RectangleShape>& EnemyBoxes) {
    window.clear();
    window.draw(Sprites["Background"]);
    window.draw(Sprites["BackButton"]);
    window.draw(Sprites["StartFightButton"]);
    window.draw(Texts["BattleHeaderText"]);
    window.draw(Texts["BattleSubheaderText"]);
    for (const auto& box : EnemyBoxes) {
        window.draw(box);
    }
    window.draw(Sprites["BronzeLaurel"]);
    window.draw(Sprites["SilverLaurel"]);
    window.draw(Sprites["GoldLaurel"]);
    window.draw(Texts["FireWormHeaderText"]);
    window.draw(Texts["FireWormSubheaderText"]);
    window.draw(Texts["GoblinHeaderText"]);
    window.draw(Texts["GoblinSubheaderText"]);
    window.draw(Texts["SkeletonHeaderText"]);
    window.draw(Texts["SkeletonSubheaderText"]);
    window.draw(Texts["MushroomHeaderText"]);
    window.draw(Texts["MushroomSubheaderText"]);
    window.draw(Texts["ShadowWarriorHeaderText"]);
    window.draw(Texts["ShadowWarriorSubheaderText"]);
    window.draw(Texts["NecromancerHeaderText"]);
    window.draw(Texts["NecromancerSubheaderText"]);
    window.draw(Texts["MinotaurHeaderText"]);
    window.draw(Texts["MinotaurSubheaderText"]);
    static float elapsedTime = 0.0f;
    elapsedTime += clock.restart().asSeconds();
    if (elapsedTime >= 0.12f) {
        elapsedTime = 0.0f;
        Animations["FireWorm"].update("Idle", Sprites["FireWormMenuIcon"]);
        Animations["Goblin"].update("Idle", Sprites["GoblinMenuIcon"]);
        Animations["Skeleton"].update("Idle", Sprites["SkeletonMenuIcon"]);
        Animations["Mushroom"].update("Idle", Sprites["MushroomMenuIcon"]);
        Animations["ShadowWarrior"].update("Idle", Sprites["ShadowWarriorMenuIcon"]);
        Animations["Necromancer"].update("Idle", Sprites["NecromancerMenuIcon"]);
        Animations["Minotaur"].update("Idle", Sprites["MinotaurMenuIcon"]);
    }
    drawMenuIcons(window, Sprites, Rectangles);
    handleCursorChange(window, {}, EnemyBoxes, { Sprites["BackButton"], Sprites["StartFightButton"]}, ArrowCursor, TextCursor, HandCursor);
    window.display();
}

void initializeFight(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, Player& player) {
    cout << player.getPlayerName() << ".";
    sf::RectangleShape PlayerHpOutline(sf::Vector2f(250, 20));
    PlayerHpOutline.setFillColor(sf::Color::Transparent);
    PlayerHpOutline.setOutlineColor(sf::Color::White);
    PlayerHpOutline.setOutlineThickness(2);
    int x = 120;
    int y = 400;
    PlayerHpOutline.setPosition(x, y);

    sf::RectangleShape PlayerHpBar(sf::Vector2f(250, 20));
    PlayerHpBar.setFillColor(sf::Color(63, 143, 41));
    PlayerHpBar.setPosition(x, y);

    sf::RectangleShape EnemyHpOutline(sf::Vector2f(250, 20));
    EnemyHpOutline.setFillColor(sf::Color::Transparent);
    EnemyHpOutline.setOutlineColor(sf::Color::White);
    EnemyHpOutline.setOutlineThickness(2);
    x = window.getSize().x - 120 - 250;
    EnemyHpOutline.setPosition(x, y);

    sf::RectangleShape EnemyHpBar(sf::Vector2f(250, 20));
    EnemyHpBar.setFillColor(sf::Color(63, 143, 41));
    EnemyHpBar.setPosition(x, y);

    sf::RectangleShape HitBarOutline(sf::Vector2f(300, 30));
    HitBarOutline.setFillColor(sf::Color::Transparent);
    HitBarOutline.setOutlineColor(sf::Color::White);
    HitBarOutline.setOutlineThickness(2);
    x = (window.getSize().x - HitBarOutline.getGlobalBounds().width) / 2;
    y = 490;
    HitBarOutline.setPosition(x, y);

    sf::RectangleShape LightGreenTarget(sf::Vector2f(60, 30));
    LightGreenTarget.setFillColor(sf::Color(63, 143, 41));
    int random = rand() % 220 + 1;
    x = HitBarOutline.getPosition().x + random;
    LightGreenTarget.setPosition(x, y);
    
    sf::RectangleShape DarkGreenTarget(sf::Vector2f(10, 30));
    DarkGreenTarget.setFillColor(sf::Color(5, 101, 23));
    int top = LightGreenTarget.getPosition().x + LightGreenTarget.getGlobalBounds().width - DarkGreenTarget.getGlobalBounds().width;
    int bottom = LightGreenTarget.getPosition().x;
    random = rand() % (top - bottom) + bottom;
    DarkGreenTarget.setPosition(random, y);

    sf::RectangleShape RedTarget(sf::Vector2f(3, 60));
    RedTarget.setFillColor(sf::Color(222, 26, 36));
    x = (window.getSize().x - RedTarget.getGlobalBounds().width) / 2;
    RedTarget.setPosition(x, y-15);

    sf::RectangleShape BackgroundOverlay(sf::Vector2f(1000, 600));
    BackgroundOverlay.setFillColor(sf::Color::Transparent);

    Rectangles["PlayerHpOutline"] = PlayerHpOutline;
    Rectangles["EnemyHpOutline"] = EnemyHpOutline;
    Rectangles["PlayerHpBar"] = PlayerHpBar;
    Rectangles["EnemyHpBar"] = EnemyHpBar;
    Rectangles["HitBarOutline"] = HitBarOutline;
    Rectangles["LightGreenTarget"] = LightGreenTarget;
    Rectangles["DarkGreenTarget"] = DarkGreenTarget;
    Rectangles["RedTarget"] = RedTarget;
    Rectangles["BackgroundOverlay"] = BackgroundOverlay;

    sf::Text FightHeaderText;
    setTextProperties(FightHeaderText, ResourceManager::getFont(NewRocker), "Fight", 50, sf::Color::White);
    x = (window.getSize().x - static_cast<int>(FightHeaderText.getGlobalBounds().width)) / 2;
    y = 80;
    FightHeaderText.setPosition(x, y);

    sf::Text PlayerMinHp;
    setTextProperties(PlayerMinHp, ResourceManager::getFont(LatoRegular), "0", 15, sf::Color::White);
    centerTextToBox(PlayerMinHp, PlayerHpBar);
    PlayerMinHp.move(-140, 0);

    sf::Text EnemyMinHp;
    setTextProperties(EnemyMinHp, ResourceManager::getFont(LatoRegular), "0", 15, sf::Color::White);
    centerTextToBox(EnemyMinHp, EnemyHpBar);
    EnemyMinHp.move(-140, 0);

    sf::Text PlayerMaxHp;
    setTextProperties(PlayerMaxHp, ResourceManager::getFont(LatoRegular), "0", 15, sf::Color::White);
    centerTextToBox(PlayerMaxHp, PlayerHpBar);
    PlayerMaxHp.move(140, 0);

    sf::Text EnemyMaxHp;
    setTextProperties(EnemyMaxHp, ResourceManager::getFont(LatoRegular), "0", 15, sf::Color::White);
    centerTextToBox(EnemyMaxHp, EnemyHpBar);
    EnemyMaxHp.move(140, 0);

    sf::Text PlayerName;
    setTextProperties(PlayerName, ResourceManager::getFont(NewRocker), "", 20, sf::Color::White);

    sf::Text EnemyName;
    setTextProperties(EnemyName, ResourceManager::getFont(NewRocker), "", 20, sf::Color::White);
    centerTextToBox(EnemyName, EnemyHpOutline);

    sf::Text PlayerDmg;
    setTextProperties(PlayerDmg, ResourceManager::getFont(LatoBold), "", 15, sf::Color::Transparent);
    PlayerDmg.setPosition(330, 220);

    sf::Text EnemyDmg;
    setTextProperties(EnemyDmg, ResourceManager::getFont(LatoBold), "", 15, sf::Color::Transparent);
    EnemyDmg.setPosition(650, 220);

    sf::Text BattleResult;
    setTextProperties(BattleResult, ResourceManager::getFont(NewRocker), "", 50, sf::Color::Transparent);

    sf::Text BattleComment;
    setTextProperties(BattleComment, ResourceManager::getFont(NewRocker), "", 20, sf::Color::Transparent);

    sf::Text HitComment;
    setTextProperties(HitComment, ResourceManager::getFont(LatoBold), "", 15, sf::Color::Transparent);

    Texts["FightHeaderText"] = FightHeaderText;
    Texts["PlayerMinHp"] = PlayerMinHp;
    Texts["EnemyMinHp"] = EnemyMinHp;
    Texts["PlayerMaxHp"] = PlayerMaxHp;
    Texts["EnemyMaxHp"] = EnemyMaxHp;
    Texts["PlayerName"] = PlayerName;
    Texts["EnemyName"] = EnemyName;
    Texts["PlayerDmg"] = PlayerDmg;
    Texts["EnemyDmg"] = EnemyDmg;
    Texts["BattleResult"] = BattleResult;
    Texts["BattleComment"] = BattleComment;
    Texts["HitComment"] = HitComment;

    sf::Sprite FightKnightIcon(ResourceManager::getTexture(Textures::KnightIdle));
    FightKnightIcon.setScale(4, 4);

    sf::Sprite FightArcherIcon(ResourceManager::getTexture(Textures::ArcherIdle));
    FightArcherIcon.setScale(3.2, 3.2);

    sf::Sprite FightWizardIcon(ResourceManager::getTexture(Textures::WizardIdle));
    FightWizardIcon.setScale(1.8, 1.8);

    Sprites["FightKnightIcon"] = FightKnightIcon;
    Sprites["FightArcherIcon"] = FightArcherIcon;
    Sprites["FightWizardIcon"] = FightWizardIcon;

    sf::Sprite FireWormFightIcon(ResourceManager::getTexture(Textures::FireWormIdle));
    FireWormFightIcon.setScale(-3, 3);

    sf::Sprite GoblinFightIcon(ResourceManager::getTexture(Textures::GoblinIdle));
    GoblinFightIcon.setScale(-3.2, 3.2);

    sf::Sprite SkeletonFightIcon(ResourceManager::getTexture(Textures::SkeletonIdle));
    SkeletonFightIcon.setScale(-4, 4);

    sf::Sprite MushroomFightIcon(ResourceManager::getTexture(Textures::MushroomIdle));
    MushroomFightIcon.setScale(-3.4, 3.4);

    sf::Sprite ShadowWarriorFightIcon(ResourceManager::getTexture(Textures::ShadowWarriorIdle));
    ShadowWarriorFightIcon.setScale(-3.7, 3.7);

    sf::Sprite NecromancerFightIcon(ResourceManager::getTexture(Textures::NecromancerIdle));
    NecromancerFightIcon.setScale(-2.7, 2.7);

    sf::Sprite MinotaurFightIcon(ResourceManager::getTexture(Textures::MinotaurIdle));
    MinotaurFightIcon.setScale(3.2, 3.2);

    Sprites["FireWormFightIcon"] = FireWormFightIcon;
    Sprites["GoblinFightIcon"] = GoblinFightIcon;
    Sprites["SkeletonFightIcon"] = SkeletonFightIcon;
    Sprites["MushroomFightIcon"] = MushroomFightIcon;
    Sprites["ShadowWarriorFightIcon"] = ShadowWarriorFightIcon;
    Sprites["NecromancerFightIcon"] = NecromancerFightIcon;
    Sprites["MinotaurFightIcon"] = MinotaurFightIcon;
}

void drawFight(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, sf::Cursor* ArrowCursor, sf::Cursor* TextCursor, sf::Cursor* HandCursor, map<string, AnimationManager>& Animations, sf::Clock& animationClock, Player& player, Enemy& enemy, bool& isMoving, bool& ongoingFight) {
    window.clear();
    window.draw(Sprites["Background"]);
    window.draw(Texts["FightHeaderText"]);
    window.draw(Rectangles["PlayerHpOutline"]);
    window.draw(Rectangles["PlayerHpBar"]);
    window.draw(Rectangles["EnemyHpOutline"]);
    window.draw(Rectangles["EnemyHpBar"]);
    window.draw(Texts["PlayerMinHp"]);
    window.draw(Texts["EnemyMinHp"]);
    window.draw(Texts["PlayerName"]);
    Texts["PlayerName"].setString(player.getPlayerName());
    centerTextToBox(Texts["PlayerName"], Rectangles["PlayerHpOutline"]);
    Texts["PlayerName"].move(0, -210);
    window.draw(Rectangles["HitBarOutline"]);
    window.draw(Rectangles["LightGreenTarget"]);
    window.draw(Rectangles["DarkGreenTarget"]);
    window.draw(Rectangles["RedTarget"]);
    player.battle(window, Sprites, Rectangles, Texts, Animations, animationClock, enemy, isMoving, ongoingFight);
    window.draw(Texts["PlayerDmg"]);
    window.draw(Texts["EnemyDmg"]);
    window.draw(Rectangles["BackgroundOverlay"]);
    window.draw(Texts["BattleResult"]);
    window.draw(Texts["BattleComment"]);
    window.draw(Texts["HitComment"]);
    window.draw(Sprites["BackButton"]);
    handleCursorChange(window, {}, {}, {Sprites["BackButton"]}, ArrowCursor, TextCursor, HandCursor);
    window.display();
}