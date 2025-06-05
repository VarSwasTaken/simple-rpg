#include "../include/window.h"
#include "../include/screens.h"
#include "../include/events.h"
#include "../include/classes.h"

Screens currentScreen;
sf::Cursor ArrowCursor, HandCursor, TextCursor;
map<string, sf::Sprite> Sprites;
map<string, sf::RectangleShape> Rectangles;
vector<sf::RectangleShape> ClassBoxes;
vector<sf::RectangleShape> EnemyBoxes;
map<string, sf::Text> Texts; 

PlayerData playerData;
ClassData classData;
Player player(playerData);
Enemy enemy;
map<string, Enemy> Enemies;
int chosenClass, chosenEnemy;
bool isMoving = true;
bool fightStarting = false;

AnimationManager knightAnimation, archerAnimation, wizardAnimation, fireWormAnimation, goblinAnimation, skeletonAnimation, mushroomAnimation, shadowWarriorAnimation, necromancerAnimation, minotaurAnimation;
map<string, AnimationManager> Animations;

sf::Clock animationClock;

void loadResources() {
    ResourceManager::loadTexture(Background, "resources/images/ui/background.jpg");
    ResourceManager::loadTexture(AppName, "resources/images/ui/app_name.png");
    ResourceManager::loadTexture(Button, "resources/images/ui/button.png");
    ResourceManager::loadTexture(Back, "resources/images/ui/back.png");
    ResourceManager::loadTexture(StartFightButton, "resources/images/ui/fight_button.png");
    ResourceManager::loadTexture(KnightIdle, "resources/images/heroes/knight/idle.png");
    ResourceManager::loadTexture(KnightAttack, "resources/images/heroes/knight/attack.png");
    ResourceManager::loadTexture(KnightHurt, "resources/images/heroes/knight/hurt.png");
    ResourceManager::loadTexture(KnightDie, "resources/images/heroes/knight/die.png");
    ResourceManager::loadTexture(ArcherIdle, "resources/images/heroes/archer/idle.png");
    ResourceManager::loadTexture(ArcherAttack, "resources/images/heroes/archer/attack.png");
    ResourceManager::loadTexture(ArcherHurt, "resources/images/heroes/archer/hurt.png");
    ResourceManager::loadTexture(ArcherDie, "resources/images/heroes/archer/die.png");
    ResourceManager::loadTexture(WizardIdle, "resources/images/heroes/wizard/idle.png");
    ResourceManager::loadTexture(WizardAttack, "resources/images/heroes/wizard/attack.png");
    ResourceManager::loadTexture(WizardHurt, "resources/images/heroes/wizard/hurt.png");
    ResourceManager::loadTexture(WizardDie, "resources/images/heroes/wizard/die.png");
    ResourceManager::loadTexture(BronzeLaurel, "resources/images/ui/bronze.png");
    ResourceManager::loadTexture(SilverLaurel, "resources/images/ui/silver.png");
    ResourceManager::loadTexture(GoldLaurel, "resources/images/ui/gold.png");
    ResourceManager::loadTexture(FireWormIdle, "resources/images/enemies/fire_worm/idle.png");
    ResourceManager::loadTexture(FireWormAttack, "resources/images/enemies/fire_worm/attack.png");
    ResourceManager::loadTexture(FireWormHurt, "resources/images/enemies/fire_worm/hurt.png");
    ResourceManager::loadTexture(FireWormDie, "resources/images/enemies/fire_worm/die.png");
    ResourceManager::loadTexture(GoblinIdle, "resources/images/enemies/goblin/idle.png");
    ResourceManager::loadTexture(GoblinHurt, "resources/images/enemies/goblin/hurt.png");
    ResourceManager::loadTexture(GoblinDie, "resources/images/enemies/goblin/die.png");
    ResourceManager::loadTexture(GoblinAttack, "resources/images/enemies/goblin/attack.png");
    ResourceManager::loadTexture(SkeletonIdle, "resources/images/enemies/skeleton/idle.png");
    ResourceManager::loadTexture(SkeletonAttack, "resources/images/enemies/skeleton/attack.png");
    ResourceManager::loadTexture(SkeletonHurt, "resources/images/enemies/skeleton/hurt.png");
    ResourceManager::loadTexture(SkeletonDie, "resources/images/enemies/skeleton/die.png");
    ResourceManager::loadTexture(MushroomIdle, "resources/images/enemies/mushroom/idle.png");
    ResourceManager::loadTexture(MushroomAttack, "resources/images/enemies/mushroom/attack.png");
    ResourceManager::loadTexture(MushroomHurt, "resources/images/enemies/mushroom/hurt.png");
    ResourceManager::loadTexture(MushroomDie, "resources/images/enemies/mushroom/die.png");
    ResourceManager::loadTexture(ShadowWarriorIdle, "resources/images/enemies/shadow_warrior/idle.png");
    ResourceManager::loadTexture(ShadowWarriorAttack, "resources/images/enemies/shadow_warrior/attack.png");
    ResourceManager::loadTexture(ShadowWarriorHurt, "resources/images/enemies/shadow_warrior/hurt.png");
    ResourceManager::loadTexture(ShadowWarriorDie, "resources/images/enemies/shadow_warrior/die.png");
    ResourceManager::loadTexture(NecromancerIdle, "resources/images/enemies/necromancer/idle.png");
    ResourceManager::loadTexture(NecromancerAttack, "resources/images/enemies/necromancer/attack.png");
    ResourceManager::loadTexture(NecromancerHurt, "resources/images/enemies/necromancer/hurt.png");
    ResourceManager::loadTexture(NecromancerDie, "resources/images/enemies/necromancer/die.png");
    ResourceManager::loadTexture(MinotaurIdle, "resources/images/enemies/minotaur/idle.png");
    ResourceManager::loadTexture(MinotaurAttack, "resources/images/enemies/minotaur/attack.png");
    ResourceManager::loadTexture(MinotaurHurt, "resources/images/enemies/minotaur/hurt.png");
    ResourceManager::loadTexture(MinotaurDie, "resources/images/enemies/minotaur/die.png");

    ResourceManager::loadFont(NewRocker, "resources/fonts/NewRocker-Regular.ttf");
    ResourceManager::loadFont(LatoRegular, "resources/fonts/Lato-Regular.ttf");
    ResourceManager::loadFont(LatoLight, "resources/fonts/Lato-Light.ttf");
    ResourceManager::loadFont(LatoBold, "resources/fonts/Lato-Bold.ttf");
}

void loadCursors() {
    if (!ArrowCursor.loadFromSystem(sf::Cursor::Arrow))
        throw runtime_error("Couldn't load arrow cursor");
    if (!HandCursor.loadFromSystem(sf::Cursor::Hand))
        throw runtime_error("Couldn't load hand cursor");
    if (!TextCursor.loadFromSystem(sf::Cursor::Text))
        throw runtime_error("Couldn't load text cursor");
}

void setupCommonSprites(sf::RenderWindow& window) {
    sf::Sprite Background(ResourceManager::getTexture(Textures::Background));
    sf::Sprite AppName(ResourceManager::getTexture(Textures::AppName));
    int x = (window.getSize().x - static_cast<int>(AppName.getGlobalBounds().width)) / 2;
    int y = 100;
    AppName.setPosition(x, y);
    sf::Sprite BackButton(ResourceManager::getTexture(Textures::Back));
    BackButton.setScale(0.07, 0.07);
    BackButton.move(10, 10);

    Sprites["Background"] = Background;
    Sprites["AppName"] = AppName;
    Sprites["BackButton"] = BackButton;
}

void initializeGraphics(sf::RenderWindow& window) {
    initializeMainMenu(window, Sprites, Rectangles, Texts);
    initializeContinueNewGame(window, Sprites, Rectangles, Texts);
    initializeCreationMenu(window, Sprites, Rectangles, Texts, ClassBoxes);
    initializeGameMenu(window, Sprites, Rectangles, Texts);
    initializeProfile(window, Sprites, Rectangles, Texts, playerData);
    initializeAssignPoints(window, Sprites, Rectangles, Texts);
    initializeBattleMenu(window, Sprites, Rectangles, Texts, EnemyBoxes);
    initializeFight(window, Sprites, Rectangles, Texts, player);
}

void drawScreen(sf::RenderWindow& window) {
    switch (currentScreen) {
        case MainMenu:
            drawMainMenu(window, Sprites, Rectangles, Texts, &ArrowCursor, &TextCursor, &HandCursor);
            break;
        case NewGame:
            drawNewGame(window, Sprites, Rectangles, Texts, &ArrowCursor, &TextCursor, &HandCursor);
            break;
        case Continue:
            drawContinue(window, Sprites, Rectangles, Texts, &ArrowCursor, &TextCursor, &HandCursor);
            break;
        case Creation:
            drawCreationMenu(window, Sprites, Rectangles, Texts, &ArrowCursor, &TextCursor, &HandCursor, ClassBoxes, Animations, animationClock);
            break;
        case GameMenu:
            drawGameMenu(window, Sprites, Rectangles, Texts, &ArrowCursor, &TextCursor, &HandCursor);
            break;
        case Profile:
            drawProfile(window, Sprites, Rectangles, Texts, &ArrowCursor, &TextCursor, &HandCursor, player, Animations, animationClock);
            break;
        case AssignPoints:
            drawAssignPoints(window, Sprites, Rectangles, Texts, &ArrowCursor, &TextCursor, &HandCursor, player);
            break;
        case BattleMenu:
            drawBattleMenu(window, Sprites, Rectangles, Texts, &ArrowCursor, &TextCursor, &HandCursor, Animations, animationClock, EnemyBoxes);
            break;
        case Fight:
            drawFight(window, Sprites, Rectangles, Texts, &ArrowCursor, &TextCursor, &HandCursor, Animations, animationClock, player, enemy, isMoving, fightStarting);
    }
}

int handleEvents(sf::RenderWindow& window, sf::Event& event) {
    switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonReleased:
            if (!handleMouseButtonRelease(window, event, currentScreen, playerData, player, Sprites, Texts, ClassBoxes, chosenClass, classData, Rectangles, EnemyBoxes, chosenEnemy, enemy, Enemies, fightStarting))
                return 0;
            break;
        case sf::Event::MouseButtonPressed:
            handleMouseButtonPressed(window, event, currentScreen, Rectangles);
            break;
        case sf::Event::TextEntered:
            handleTextEntered(event, currentScreen, Texts);
            break;
        case sf::Event::KeyPressed:
            handleKeyPressed(window, event, currentScreen, Rectangles, isMoving);
            break;
    }
    return 1;
}

void setValues(sf::RenderWindow& window) {
    window.setFramerateLimit(60);
    srand(time(NULL));
    currentScreen = MainMenu;
    chosenClass = 1;
    chosenEnemy = 1;
    Enemy fireWorm("Fire Worm", 1, 40, 40, 40, 40, 100, 50, 10, 1);
    Enemy goblin("Goblin", 5, 75, 75, 75, 75, 300, 65, 15, 2);
    Enemy skeleton("Skeleton", 10, 95, 95, 95, 95, 500, 75, 20, 3);
    Enemy mushroom("Mushroom", 15, 115, 115, 115, 115, 700, 80, 25, 4);
    Enemy shadowWarrior("Shadow Warrior", 20, 135, 135, 135, 135, 900, 85, 30, 5);
    Enemy necromancer("Necromancer", 25, 165, 165, 165, 165, 1100, 90, 35, 6);
    Enemy minotaur("Minotaur", 30, 200, 200, 200, 200, 1300, 100, 40, 7);
    Enemies["Fire Worm"] = fireWorm;
    Enemies["Goblin"] = goblin;
    Enemies["Skeleton"] = skeleton;
    Enemies["Mushroom"] = mushroom;
    Enemies["Shadow Warrior"] = shadowWarrior;
    Enemies["Necromancer"] = necromancer;
    Enemies["Minotaur"] = minotaur;
    enemy = goblin;
    //playerData.playerName = "Kupadup12431_";
    //playerData.className = "Wizard";
    //playerData.level = 5;
    //playerData.experience = 3200;
    //playerData.expNeeded = 3600;
    //playerData.killed = 30;
    //playerData.health = 80;
    //playerData.attack = 80;
    //playerData.defence = 80;
    //playerData.dodge = 400;
    //playerData.points = 40;
    //playerData.classIdentifier = 3;
    player = Player(playerData);
}

void loadAnimations() {
    sf::Vector2i frameRectangle(7, 1);
    sf::Vector2i spriteSize(96, 84);
    knightAnimation.addAnimation("Idle", ResourceManager::getTexture(KnightIdle), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(6, 1);
    knightAnimation.addAnimation("Attack", ResourceManager::getTexture(KnightAttack), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(4, 1);
    knightAnimation.addAnimation("Hurt", ResourceManager::getTexture(KnightHurt), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(12, 1);
    knightAnimation.addAnimation("Die", ResourceManager::getTexture(KnightDie), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(12, 1);
    spriteSize = sf::Vector2i(288, 128);
    archerAnimation.addAnimation("Idle", ResourceManager::getTexture(ArcherIdle), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(15, 1);
    archerAnimation.addAnimation("Attack", ResourceManager::getTexture(ArcherAttack), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(6, 1);
    archerAnimation.addAnimation("Hurt", ResourceManager::getTexture(ArcherHurt), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(19, 1);
    archerAnimation.addAnimation("Die", ResourceManager::getTexture(ArcherDie), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(6, 1);
    spriteSize = sf::Vector2i(231, 190);
    wizardAnimation.addAnimation("Idle", ResourceManager::getTexture(WizardIdle), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(8, 1);
    wizardAnimation.addAnimation("Attack", ResourceManager::getTexture(WizardAttack), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(3, 1);
    wizardAnimation.addAnimation("Hurt", ResourceManager::getTexture(WizardHurt), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(7, 1);
    wizardAnimation.addAnimation("Die", ResourceManager::getTexture(WizardDie), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(9, 1);
    spriteSize = sf::Vector2i(90, 90);
    fireWormAnimation.addAnimation("Idle", ResourceManager::getTexture(FireWormIdle), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(16, 1);
    fireWormAnimation.addAnimation("Attack", ResourceManager::getTexture(FireWormAttack), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(8, 1);
    fireWormAnimation.addAnimation("Die", ResourceManager::getTexture(FireWormDie), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(4, 1);
    fireWormAnimation.addAnimation("Hurt", ResourceManager::getTexture(FireWormHurt), frameRectangle, spriteSize);
    spriteSize = sf::Vector2i(150, 150);
    goblinAnimation.addAnimation("Idle", ResourceManager::getTexture(GoblinIdle), frameRectangle, spriteSize);
    goblinAnimation.addAnimation("Hurt", ResourceManager::getTexture(GoblinHurt), frameRectangle, spriteSize);
    goblinAnimation.addAnimation("Die", ResourceManager::getTexture(GoblinDie), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(8, 1);
    goblinAnimation.addAnimation("Attack", ResourceManager::getTexture(GoblinAttack), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(11, 1);
    spriteSize = sf::Vector2i(43, 37);
    skeletonAnimation.addAnimation("Idle", ResourceManager::getTexture(SkeletonIdle), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(18, 1);
    skeletonAnimation.addAnimation("Attack", ResourceManager::getTexture(SkeletonAttack), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(8, 1);
    skeletonAnimation.addAnimation("Hurt", ResourceManager::getTexture(SkeletonHurt), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(15, 1);
    skeletonAnimation.addAnimation("Die", ResourceManager::getTexture(SkeletonDie), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(4, 1);
    spriteSize = sf::Vector2i(150, 150);
    mushroomAnimation.addAnimation("Idle", ResourceManager::getTexture(MushroomIdle), frameRectangle, spriteSize);
    mushroomAnimation.addAnimation("Hurt", ResourceManager::getTexture(MushroomHurt), frameRectangle, spriteSize);
    mushroomAnimation.addAnimation("Die", ResourceManager::getTexture(MushroomDie), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(8, 1);
    mushroomAnimation.addAnimation("Attack", ResourceManager::getTexture(MushroomAttack), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(9, 1);
    spriteSize = sf::Vector2i(80, 80);
    shadowWarriorAnimation.addAnimation("Idle", ResourceManager::getTexture(ShadowWarriorIdle), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(12, 1);
    shadowWarriorAnimation.addAnimation("Attack", ResourceManager::getTexture(ShadowWarriorAttack), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(5, 1);
    shadowWarriorAnimation.addAnimation("Hurt", ResourceManager::getTexture(ShadowWarriorHurt), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(23, 1);
    shadowWarriorAnimation.addAnimation("Die", ResourceManager::getTexture(ShadowWarriorDie), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(8, 1);
    spriteSize = sf::Vector2i(160, 128);
    necromancerAnimation.addAnimation("Idle", ResourceManager::getTexture(NecromancerIdle), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(13, 1);
    necromancerAnimation.addAnimation("Attack", ResourceManager::getTexture(NecromancerAttack), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(5, 1);
    necromancerAnimation.addAnimation("Hurt", ResourceManager::getTexture(NecromancerHurt), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(9, 1);
    necromancerAnimation.addAnimation("Die", ResourceManager::getTexture(NecromancerDie), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(5, 1);
    spriteSize = sf::Vector2i(96, 77);
    minotaurAnimation.addAnimation("Idle", ResourceManager::getTexture(MinotaurIdle), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(9, 1);
    minotaurAnimation.addAnimation("Attack", ResourceManager::getTexture(MinotaurAttack), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(4, 1);
    minotaurAnimation.addAnimation("Hurt", ResourceManager::getTexture(MinotaurHurt), frameRectangle, spriteSize);
    frameRectangle = sf::Vector2i(8, 1);
    minotaurAnimation.addAnimation("Die", ResourceManager::getTexture(MinotaurDie), frameRectangle, spriteSize);
    Animations["Knight"] = knightAnimation;
    Animations["Archer"] = archerAnimation;
    Animations["Wizard"] = wizardAnimation;
    Animations["FireWorm"] = fireWormAnimation;
    Animations["Goblin"] = goblinAnimation;
    Animations["Skeleton"] = skeletonAnimation;
    Animations["Mushroom"] = mushroomAnimation;
    Animations["ShadowWarrior"] = shadowWarriorAnimation;
    Animations["Necromancer"] = necromancerAnimation;
    Animations["Minotaur"] = minotaurAnimation;
}