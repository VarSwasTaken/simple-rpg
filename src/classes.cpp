#include "../include/classes.h"
#include "../include/utility.h"

map<Textures, sf::Texture> ResourceManager::textures;
map<Fonts, sf::Font> ResourceManager::fonts;

int Statistics::getHealth()
{
    return health;
}

int Statistics::getAttack()
{
    return attack;
}

int Statistics::getDefence()
{
    return defence;
}

int Statistics::getDodge()
{
    return dodge;
}

int Statistics::getCurrentHealth() {
    return currentHealth;
}

void Statistics::setCurrentHealth(int health) {
    currentHealth = health;
}

Player::Player(PlayerData data)
{
    this->playerName = data.playerName;
    this->className = data.className;
    this->level = data.level;
    this->playerExperience = data.experience;
    this->expNeeded = data.expNeeded;
    this->health = data.health;
    this->attack = data.attack;
    this->defence = data.defence;
    this->dodge = data.dodge;
    this->enemiesKilled = data.killed;
    this->availablePoints = data.points;
    this->classIdentifier = data.classIdentifier;
    this->currentHealth = data.health;
}

string Player::getPlayerName() {
    return playerName;
}

string Player::getClassName() {
    return className;
}

int Player::getLevel() {
    return level;
}

int Player::getExperience() {
    return playerExperience;
}

int Player::getExpNeeded() {
    return expNeeded;
}

int Player::getEnemiesKilled() {
    return enemiesKilled;
}

int Player::getPoints() {
    return availablePoints;
}

int Player::getClassIdentifier() {
    return classIdentifier;
}

void Player::levelUp()
{
    if (playerExperience >= expNeeded)
    {
        level++;
        availablePoints+=10;
        expNeeded = pow(((level + 1) / 0.1), 2);
    }
    if (level > 35)
    {
        level = 35;
        availablePoints-=10;
        playerExperience = 122500;
        expNeeded = 122500;
    }
}

int Player::assignPoints(int hp, int atk, int def, int ddg) {
    int sum = hp + atk + def + ddg;
    if (sum > availablePoints) {
        return 0;
    }
    health += hp;
    attack += atk;
    defence += def;
    dodge += ddg;
    availablePoints -= sum;

    return 1;
}

void Player::enemyKilled(int expAdded)
{
    playerExperience += expAdded;
    enemiesKilled++;
}

void Player::removeExp(int expRemoved)
{
    playerExperience -= expRemoved;
    if (playerExperience < 0)
        playerExperience = 0;
}

void Player::battle(sf::RenderWindow& window, map<string, sf::Sprite>& Sprites, map<string, sf::RectangleShape>& Rectangles, map<string, sf::Text>& Texts, map<string, AnimationManager>& Animations, sf::Clock& animationsClock, Enemy& enemy, bool& isMoving, bool& fightStarting) {
    bool fightEnd = false;
    static bool playingPlayerAnimation = false;
    static bool playingEnemyAnimation = false;
    static bool enemyDead = false;
    static bool playerDead = false;
    static bool playerCanAttack = true;
    static bool enemyCanAttack = false;
    static string playerAnimation = "";
    static string enemyAnimation = "";
    static sf::Clock delayClock;
    static sf::Clock deathDelayClock;
    sf::Sprite* playerSprite = &Sprites["FightKnightIcon"];
    string playerString, enemyString;
    sf::Sprite* enemySprite = &Sprites["FireWormFightIcon"];
    static int change = 1;

    if (fightStarting) {
        currentHealth = health;
        enemy.setCurrentHealth(enemy.getCurrentHealth());
        Sprites["BackButton"].setColor(sf::Color(255, 255, 255, 0));
        Rectangles["PlayerHpBar"].setSize(sf::Vector2f(250, Rectangles["PlayerHpBar"].getGlobalBounds().height));
        Rectangles["PlayerHpBar"].setFillColor(sf::Color(63, 143, 41));
        Rectangles["EnemyHpBar"].setSize(sf::Vector2f(250, Rectangles["EnemyHpBar"].getGlobalBounds().height));
        Rectangles["EnemyHpBar"].setFillColor(sf::Color(63, 143, 41));
        Texts["BattleResult"].setFillColor(sf::Color::Transparent);
        Texts["BattleComment"].setFillColor(sf::Color::Transparent);
        Texts["EnemyDmg"].setFillColor(sf::Color::Transparent);
        Texts["PlayerDmg"].setFillColor(sf::Color::Transparent);
        Texts["HitComment"].setFillColor(sf::Color::Transparent);
        Rectangles["BackgroundOverlay"].setFillColor(sf::Color::Transparent);
        fightStarting = false;
        playerDead = false;
        enemyDead = false;
        playerCanAttack = true;
        enemyCanAttack = false;
        delayClock.restart();
        deathDelayClock.restart();
        isMoving = true;
        Rectangles["RedTarget"].setPosition((window.getSize().x - Rectangles["RedTarget"].getGlobalBounds().width) / 2, Rectangles["RedTarget"].getPosition().y);
        change = 1;
    }

    int playerHp = currentHealth;
    int enemyHp = enemy.getCurrentHealth();

    int playerDmg = attack - enemy.getDefence();
    int playerCritDmg = 1.5 * attack - enemy.getDefence();
    int enemyDmg = enemy.getAttack() - defence;
    int enemyCritDmg = 1.5 * enemy.getAttack() - defence;
    static int currentPlayerDmg = 0;
    static int currentEnemyDmg = 0;
    if (playerDmg < 0)
        playerDmg = 0;
    if (playerCritDmg < 0)
        playerCritDmg = 0;
    if (enemyDmg < 0)
        enemyDmg = 0;
    if (enemyCritDmg < 0)
        enemyCritDmg = 0;

    switch (classIdentifier) {
    case 1:
        centerSpriteToBox(Sprites["FightKnightIcon"], Rectangles["PlayerHpOutline"]);
        Sprites["FightKnightIcon"].move(0, -110);
        playerSprite = &Sprites["FightKnightIcon"];
        playerString = "Knight";
        window.draw(Sprites["FightKnightIcon"]);
        break;
    case 2:
        centerSpriteToBox(Sprites["FightArcherIcon"], Rectangles["PlayerHpOutline"]);
        Sprites["FightArcherIcon"].move(0, -230);
        playerSprite = &Sprites["FightArcherIcon"];
        playerString = "Archer";
        window.draw(Sprites["FightArcherIcon"]);
        break;
    case 3:
        centerSpriteToBox(Sprites["FightWizardIcon"], Rectangles["PlayerHpOutline"]);
        Sprites["FightWizardIcon"].move(0, -110);
        playerSprite = &Sprites["FightWizardIcon"];
        playerString = "Wizard";
        window.draw(Sprites["FightWizardIcon"]);
        break;
    }

    Texts["EnemyName"].setString(enemy.getEnemyName());
    centerTextToBox(Texts["EnemyName"], Rectangles["EnemyHpOutline"]);
    Texts["EnemyName"].move(0, -210);
    window.draw(Texts["EnemyName"]);
    Texts["EnemyMaxHp"].setString(to_string(enemy.getHealth()));
    window.draw(Texts["EnemyMaxHp"]);
    Texts["PlayerMaxHp"].setString(to_string(health));
    window.draw(Texts["PlayerMaxHp"]);

    switch (enemy.getEnemyIdentifier()) {
    case 1:
        Sprites["FireWormFightIcon"].setOrigin(Sprites["FireWormFightIcon"].getLocalBounds().width, 0.f);
        centerSpriteToBox(Sprites["FireWormFightIcon"], Rectangles["EnemyHpOutline"]);
        Sprites["FireWormFightIcon"].move(0, -75);
        enemySprite = &Sprites["FireWormFightIcon"];
        enemyString = "FireWorm";
        window.draw(Sprites["FireWormFightIcon"]);
        break;
    case 2:
        Sprites["GoblinFightIcon"].setOrigin(Sprites["GoblinFightIcon"].getLocalBounds().width, 0.f);
        centerSpriteToBox(Sprites["GoblinFightIcon"], Rectangles["EnemyHpOutline"]);
        Sprites["GoblinFightIcon"].move(0, -90);
        enemySprite = &Sprites["GoblinFightIcon"];
        enemyString = "Goblin";
        window.draw(Sprites["GoblinFightIcon"]);
        break;
    case 3:
        Sprites["SkeletonFightIcon"].setOrigin(Sprites["SkeletonFightIcon"].getLocalBounds().width, 0.f);
        centerSpriteToBox(Sprites["SkeletonFightIcon"], Rectangles["EnemyHpOutline"]);
        Sprites["SkeletonFightIcon"].move(0, -100);
        enemySprite = &Sprites["SkeletonFightIcon"];
        enemyString = "Skeleton";
        window.draw(Sprites["SkeletonFightIcon"]);
        break;
    case 4:
        Sprites["MushroomFightIcon"].setOrigin(Sprites["MushroomFightIcon"].getLocalBounds().width, 0.f);
        centerSpriteToBox(Sprites["MushroomFightIcon"], Rectangles["EnemyHpOutline"]);
        Sprites["MushroomFightIcon"].move(0, -120);
        enemySprite = &Sprites["MushroomFightIcon"];
        enemyString = "Mushroom";
        window.draw(Sprites["MushroomFightIcon"]);
        break;
    case 5:
        Sprites["ShadowWarriorFightIcon"].setOrigin(Sprites["ShadowWarriorFightIcon"].getLocalBounds().width, 0.f);
        centerSpriteToBox(Sprites["ShadowWarriorFightIcon"], Rectangles["EnemyHpOutline"]);
        Sprites["ShadowWarriorFightIcon"].move(0, -120);
        enemySprite = &Sprites["ShadowWarriorFightIcon"];
        enemyString = "ShadowWarrior";
        window.draw(Sprites["ShadowWarriorFightIcon"]);
        break;
    case 6:
        Sprites["NecromancerFightIcon"].setOrigin(Sprites["NecromancerFightIcon"].getLocalBounds().width, 0.f);
        centerSpriteToBox(Sprites["NecromancerFightIcon"], Rectangles["EnemyHpOutline"]);
        Sprites["NecromancerFightIcon"].move(0, -160);
        enemySprite = &Sprites["NecromancerFightIcon"];
        enemyString = "Necromancer";
        window.draw(Sprites["NecromancerFightIcon"]);
        break;
    case 7:
        centerSpriteToBox(Sprites["MinotaurFightIcon"], Rectangles["EnemyHpOutline"]);
        Sprites["MinotaurFightIcon"].move(0, -150);
        enemySprite = &Sprites["MinotaurFightIcon"];
        enemyString = "Minotaur";
        window.draw(Sprites["MinotaurFightIcon"]);
        break;
    }

    static float elapsedTime = 0.0f;
    static float elapsedDelayTime = 2.0f;
    static float elapsedDeathDelayTime = 0.0f;
    static int playerAnimationFrame = 0;
    static int enemyAnimationFrame = 0;
    static float frameDuration = 0.12f;
    elapsedTime += animationsClock.restart().asSeconds();
    int min_x = 350;
    int max_x = 650;
    static float percentage = 0;
    static float width = 0;

    if (elapsedTime >= frameDuration) {
        elapsedTime = 0.0f;

        if (!playingPlayerAnimation && currentHealth != 0) { // no player animations are being played, play idle
            Animations[playerString].update("Idle", *playerSprite);
        }

        else if (!playerDead && !playingEnemyAnimation) { // if player hasn't died yet, play animation

                if (playerAnimation == "Hurt" && currentEnemyDmg == 0) { // if enemy finished attacking but didnt deal damage, dont do hurt animation, but add frames for delay
                    playerAnimationFrame++;
                    Animations[playerString].update("Idle", *playerSprite);
                }

                else { // play animation
                    Animations[playerString].update(playerAnimation, *playerSprite);
                    playerAnimationFrame++;
                }

                if (playerAnimation == "Die") // ensure to restart delay clock on death
                    deathDelayClock.restart();

                if (playerAnimationFrame == Animations[playerString].getFramesAmount(playerAnimation)) { // player animation finished
                    playerAnimationFrame = 0;
                    playingPlayerAnimation = false;

                    if (playerAnimation == "Die") { // player dying animation finished
                        playerDead = true;
                        playerCanAttack = false;
                        enemyCanAttack = false;
                        cout << "DEFEAT. Enemy killed the player." << endl;
                        this->removeExp(enemy.getExpGiven() / 2);
                        Texts["PlayerDmg"].setFillColor(sf::Color::Transparent);
                    }

                    else if (playerAnimation == "Attack") { // player attacking animation finished
                        delayClock.restart();
                        deathDelayClock.restart();
                        playingEnemyAnimation = true;
                        playerCanAttack = false;
                        enemyCanAttack = false;

                        if (enemy.getCurrentHealth() > 0) // if enemy is alive - play hurt
                            enemyAnimation = "Hurt";
                        else // if enemy is dead - play die
                            enemyAnimation = "Die";

                        if (currentPlayerDmg > 0) {
                            if (percentage <= 0.6) {
                                if (percentage <= 0.2)
                                    Rectangles["EnemyHpBar"].setFillColor(sf::Color::Red);
                                else
                                    Rectangles["EnemyHpBar"].setFillColor(sf::Color::Yellow);
                            }
                            Rectangles["EnemyHpBar"].setSize(sf::Vector2f(width, Rectangles["EnemyHpBar"].getGlobalBounds().height));
                            Texts["EnemyDmg"].setFillColor(sf::Color::Red);
                        }
                        else
                            Texts["EnemyDmg"].setFillColor(sf::Color::White);
                    }

                    else if (playerAnimation == "Hurt") { // player hurting animation finished
                        playerCanAttack = true;
                        enemyCanAttack = false;
                        int random = rand() % 220 + 1;
                        int x = Rectangles["HitBarOutline"].getPosition().x + random;
                        Rectangles["LightGreenTarget"].setPosition(x, 490);
                        int top = Rectangles["LightGreenTarget"].getPosition().x + Rectangles["LightGreenTarget"].getGlobalBounds().width - Rectangles["DarkGreenTarget"].getGlobalBounds().width;
                        int bottom = Rectangles["LightGreenTarget"].getPosition().x;
                        random = rand() % (top - bottom) + bottom;
                        Rectangles["DarkGreenTarget"].setPosition(random, 490);
                        Rectangles["RedTarget"].setPosition((window.getSize().x - Rectangles["RedTarget"].getGlobalBounds().width) / 2, Rectangles["RedTarget"].getPosition().y);
                        isMoving = true;
                        change = 1;
                        Texts["PlayerDmg"].setFillColor(sf::Color::Transparent);
                    }
                }
        }

        if (!playingEnemyAnimation && enemy.getCurrentHealth() != 0) { // no animations are being played for enemy, play Idle
            Animations[enemyString].update("Idle", *enemySprite);
        }

        else if (!enemyDead && !playingPlayerAnimation) { // if enemy hasn't died yet, play animation

                if (enemyAnimation == "Hurt" && currentPlayerDmg == 0) // if player finished attacking but didnt deal damage, dont do hurt animation, but add frames;
                    enemyAnimationFrame++;

                else { // play animation
                    Animations[enemyString].update(enemyAnimation, *enemySprite);
                    enemyAnimationFrame++;
                }

                if (enemyAnimation == "Die") // ensure to restart delay clock on death
                    deathDelayClock.restart();

                if (enemyAnimationFrame == Animations[enemyString].getFramesAmount(enemyAnimation)) { // enemy animation finished
                    enemyAnimationFrame = 0;
                    playingEnemyAnimation = false;

                    if (enemyAnimation == "Die") { // enemy dying animation finished
                        enemyDead = true;
                        playerCanAttack = false;
                        enemyCanAttack = false;
                        cout << "VICTORY! Enemy has been defeated." << endl;
                        this->enemyKilled(enemy.getExpGiven());
                        this->levelUp();
                        Texts["EnemyDmg"].setFillColor(sf::Color::Transparent);
                    }

                    else if (enemyAnimation == "Attack") { // enemy attack animation finished
                        delayClock.restart();
                        deathDelayClock.restart();
                        playingPlayerAnimation = true;
                        playerCanAttack = false;
                        enemyCanAttack = false;

                        if (currentHealth > 0) // if player is alive - play hurt
                            playerAnimation = "Hurt";
                        else // if player is dead - play die
                            playerAnimation = "Die";

                        if (currentEnemyDmg > 0) {
                            if (percentage <= 0.6) {
                                if (percentage <= 0.2)
                                    Rectangles["PlayerHpBar"].setFillColor(sf::Color::Red);
                                else
                                    Rectangles["PlayerHpBar"].setFillColor(sf::Color::Yellow);
                            }
                            Rectangles["PlayerHpBar"].setSize(sf::Vector2f(width, Rectangles["PlayerHpBar"].getGlobalBounds().height));
                            Texts["PlayerDmg"].setFillColor(sf::Color::Red);
                        }
                        else {
                            Texts["PlayerDmg"].setFillColor(sf::Color::White);
                        }
                    }

                    else if (enemyAnimation == "Hurt") { // enemy hurting animation finished
                        delayClock.restart();
                        enemyCanAttack = true;
                        playerCanAttack = false;
                        Texts["EnemyDmg"].setFillColor(sf::Color::Transparent);
                        Texts["HitComment"].setFillColor(sf::Color::Transparent);
                    }
                }
        }
    }

    elapsedDelayTime = delayClock.getElapsedTime().asSeconds();

    if (playerHp > 0 && enemyHp > 0) {

        if (isMoving) { // move red target
            float speed = 1.5f * enemy.getEnemyIdentifier();
            int left = Rectangles["RedTarget"].getPosition().x;
            int right = left + Rectangles["RedTarget"].getGlobalBounds().width;
            if (right >= max_x || left <= min_x)
                change = -change;
            Rectangles["RedTarget"].move(change * speed, 0);
        }

        else if (playerCanAttack) { // damage taking phase
            playingPlayerAnimation = true;
            playerAnimation = "Attack";
            playerCanAttack = false;
            enemyCanAttack = false;

            if (isInside(Rectangles["RedTarget"], Rectangles["LightGreenTarget"])) { // player hit
                if (!dodgeAttack(enemy.getDodge())) { // enemy didn't dodge player's attack
                    if (isInside(Rectangles["RedTarget"], Rectangles["DarkGreenTarget"])) { // player hit CRIT
                        enemyHp -= playerCritDmg;
                        currentPlayerDmg = playerCritDmg;
                        Texts["HitComment"].setString("CRIT");
                        Texts["HitComment"].setFillColor(sf::Color(5, 101, 23));
                    }
                    else { // player hit normal damage
                        enemyHp -= playerDmg;
                        currentPlayerDmg = playerDmg;
                        Texts["HitComment"].setString("HIT");
                        Texts["HitComment"].setFillColor(sf::Color(63, 143, 41));
                    }

                    std::cout << "Player dealt " << currentPlayerDmg << "DMG to enemy (";
                    if (currentPlayerDmg == 0)
                        Texts["EnemyDmg"].setString(to_string(currentPlayerDmg));
                    else
                        Texts["EnemyDmg"].setString("-" + to_string(currentPlayerDmg));

                    if (enemyHp <= 0) {
                        enemyHp = 0;
                        fightEnd = true;
                    }
                    std::cout << enemyHp << "HP)." << endl;
                    percentage = (float)enemyHp / (float)enemy.getHealth();
                    width = 250 * percentage;
                }

                else { // enemy dodged the attack
                    currentPlayerDmg = 0;
                    std::cout << "Enemy dodged the attack." << endl;
                    Texts["EnemyDmg"].setString("DODGE");
                }
            }

            else { // player missed
                currentPlayerDmg = 0;
                std::cout << "Player missed the target." << endl;
                Texts["EnemyDmg"].setString("0");
                Texts["HitComment"].setString("MISS");
                Texts["HitComment"].setFillColor(sf::Color::White);
            }
            centerTextToBox(Texts["HitComment"], Rectangles["RedTarget"]);
            Texts["HitComment"].move(0, 40);
            Texts["EnemyDmg"].setPosition(Rectangles["EnemyHpOutline"].getPosition().x, Texts["EnemyDmg"].getPosition().y);
            enemy.setCurrentHealth(enemyHp);
        }

        if (enemyCanAttack && elapsedDelayTime >= 2.f) {
            playingEnemyAnimation = true;
            enemyAnimation = "Attack";
            enemyCanAttack = false;
            playerCanAttack = false;

            if (enemyHit(enemy.getHitConversion())) { // enemy hit
                if (!dodgeAttack(dodge)) { // player didn't dodge the enemy's attack
                    if (enemyHit(enemy.getCritChance())) { // enemy hit CRIT
                        playerHp -= enemyCritDmg;
                        currentEnemyDmg = enemyCritDmg;
                    }
                    else {
                        playerHp -= enemyDmg;
                        currentEnemyDmg = enemyDmg;
                    }

                    std::cout << "Enemy dealt " << currentEnemyDmg << "DMG to player (";
                    if(currentEnemyDmg == 0)
                        Texts["PlayerDmg"].setString(to_string(currentEnemyDmg));
                    else
                        Texts["PlayerDmg"].setString("-" + to_string(currentEnemyDmg));

                    if (playerHp <= 0) {
                        playerHp = 0;
                        fightEnd = true;
                    }
                    std::cout << playerHp << "HP)." << endl;
                    percentage = (float)playerHp / (float)health;
                    width = 250 * percentage;
                }

                else { // player dodged the attack
                    currentEnemyDmg = 0;
                    std::cout << "Player dodged the attack." << endl;
                    Texts["PlayerDmg"].setString("DODGE");
                }
            }

            else { // enemy missed
                currentEnemyDmg = 0;
                std::cout << "Enemy missed the target." << endl;
                Texts["PlayerDmg"].setString("MISS");
            }
            Texts["PlayerDmg"].setPosition(Rectangles["PlayerHpOutline"].getPosition().x + Rectangles["PlayerHpOutline"].getGlobalBounds().width - Texts["PlayerDmg"].getGlobalBounds().width, Texts["PlayerDmg"].getPosition().y);
            currentHealth = playerHp;
        }
    }

    elapsedDeathDelayTime = deathDelayClock.getElapsedTime().asSeconds();

    if (elapsedDelayTime >= 1.5f && !playingEnemyAnimation && !playingPlayerAnimation) {
        if (enemy.getCurrentHealth() == 0) {
            Rectangles["BackgroundOverlay"].setFillColor(sf::Color(0, 30, 0, 200));
            Texts["BattleResult"].setString("VICTORY!");
            Texts["BattleComment"].setString("You've won and gained " + to_string(enemy.getExpGiven()) + "EXP.");
            Sprites["BackButton"].setColor(sf::Color(255, 255, 255, 255));
            Texts["BattleResult"].setFillColor(sf::Color::White);
            Texts["BattleComment"].setFillColor(sf::Color::White);
            centerTextToBox(Texts["BattleResult"], Rectangles["BackgroundOverlay"]);
            centerTextToBox(Texts["BattleComment"], Rectangles["BackgroundOverlay"]);
            Texts["BattleComment"].move(0, 50); 
        }
        else if (currentHealth == 0) {
            Rectangles["BackgroundOverlay"].setFillColor(sf::Color(30, 0, 0, 200));
            Texts["BattleResult"].setString("DEFEAT");
            Texts["BattleComment"].setString("You've been defeated and lost " + to_string(enemy.getExpGiven() / 2) + "EXP.");
            Sprites["BackButton"].setColor(sf::Color(255, 255, 255, 255));
            Texts["BattleResult"].setFillColor(sf::Color::White);
            Texts["BattleComment"].setFillColor(sf::Color::White);
            centerTextToBox(Texts["BattleResult"], Rectangles["BackgroundOverlay"]);
            centerTextToBox(Texts["BattleComment"], Rectangles["BackgroundOverlay"]);
            Texts["BattleComment"].move(0, 50);
        }
    }
}

bool Player::saveToFile(string passwordValue)
{
    ifstream saves("Saves/saves.txt");
    ofstream temp("Saves/temp.txt");
    if (!saves.is_open() || !temp.is_open())
        return -1;
    string line;
    while (getline(saves, line)) {
        PlayerData playerData_ = parseLine(line);
        if (playerData_.playerName != playerName) {
            temp << line << "\n";
        }
    }
    saves.close();
    temp << playerName + " " + passwordValue + " " + className + " " + to_string(classIdentifier) + " " + to_string(level) + " " + to_string(playerExperience) + " " + to_string(expNeeded) + " " + to_string(health) + " " + to_string(attack) + " " + to_string(defence) + " " + to_string(dodge) + " " + to_string(enemiesKilled) + " " + to_string(availablePoints);
    temp.close();
    if (remove("Saves/saves.txt") != 0 || rename("Saves/temp.txt", "Saves/saves.txt") != 0)
        return -1;
    return 1;
}

Enemy::Enemy(string enemyName, int level, int health, int attack, int defence, int dodge, int expGiven, int hitConversion, int critChance, int enemyIdentifier)
{
    this->enemyName = enemyName;
    this->level = level;
    this->health = health;
    this->attack = attack;
    this->defence = defence;
    this->dodge = dodge;
    this->expGiven = expGiven;
    this->hitConversion = hitConversion;
    this->critChance = critChance;
    this->enemyIdentifier = enemyIdentifier;
    this->currentHealth = health;
}

Enemy::Enemy() {
    enemyName = "";
    level = 0;
    health = 0;
    attack = 0;
    defence = 0;
    dodge = 0;
    expGiven = 0;
    hitConversion = 0;
    critChance = 0;
    enemyIdentifier = 0;
    currentHealth = 0;
}

int Enemy::getExpGiven() {
    return expGiven;
}

int Enemy::getHitConversion() {
    return hitConversion;
}

int Enemy::getCritChance() {
    return critChance;
}

int Enemy::getEnemyIdentifier() {
    return enemyIdentifier;
}

string Enemy::getEnemyName() {
    return enemyName;
}

void ResourceManager::loadTexture(Textures name, std::string filePath) {
    if (textures.find(name) != textures.end())
        return;
    sf::Texture texture;
    if (!texture.loadFromFile(filePath))
        throw runtime_error("Couldn't load texture: " + filePath);
    textures[name] = texture;
}

void ResourceManager::loadFont(Fonts name, std::string filePath) {
    if (fonts.find(name) != fonts.end())
        return;
    sf::Font font;
    if (!font.loadFromFile(filePath))
        throw runtime_error("Couldn't load font: " + filePath);
    fonts[name] = font;
}

sf::Texture& ResourceManager::getTexture(Textures id) {
    auto it = textures.find(id);
    if (it == textures.end()) {
        throw runtime_error("Texture not found for given ID.");
    }
    return it->second;
}

sf::Font& ResourceManager::getFont(Fonts id) {
    auto it = fonts.find(id);
    if (it == fonts.end()) {
        throw runtime_error("Font not found for given ID.");
    }
    return it->second;
}

void AnimationManager::update(string animation, sf::Sprite& sprite) {
    if (m_sheetSizes.find(animation) == m_sheetSizes.end()) {
        std::cerr << "No animation entry found for \"" << animation << "\"!" << std::endl;
        return;
    }

    m_timesUpdated[animation]++;
    if (m_timesUpdated[animation] < m_frequencies[animation]) {
        return;
    }
    m_timesUpdated[animation] = 0;

    sf::IntRect rect(
        m_indicies[animation].x * m_spriteSizes[animation].x,
        m_indicies[animation].y * m_spriteSizes[animation].y,
        m_spriteSizes[animation].x,
        m_spriteSizes[animation].y
    );

    if (rect.left + rect.width > m_textures[animation].getSize().x ||
        rect.top + rect.height > m_textures[animation].getSize().y) {
        std::cerr << "Animation frame out of bounds for: " << animation << std::endl;
        return;
    }

    sprite.setTexture(m_textures[animation]);
    sprite.setTextureRect(rect);

    m_indicies[animation].y++;
    if (m_indicies[animation].y >= m_sheetSizes[animation].y) {
        m_indicies[animation].y = 0;
        m_indicies[animation].x++;
        if (m_indicies[animation].x >= m_sheetSizes[animation].x) {
            m_indicies[animation].x = 0;
        }
    }
}

void AnimationManager::addAnimation(string animation, sf::Texture texture,
    sf::Vector2i sheetSize, sf::Vector2i spriteSize, sf::Vector2i index, int frequency,
    sf::Vector2i startingIndex) {
    m_textures[animation] = texture;
    m_sheetSizes[animation].x = sheetSize.x;
    m_sheetSizes[animation].y = sheetSize.y;

    m_spriteSizes[animation].x = spriteSize.x;
    m_spriteSizes[animation].y = spriteSize.y;

    m_indicies[animation].x = index.x;
    m_indicies[animation].y = index.y;

    m_startingIndicies[animation].x = startingIndex.x;
    m_startingIndicies[animation].y = startingIndex.y;

    m_endingIndicies[animation].x = sheetSize.x;
    m_endingIndicies[animation].y = sheetSize.y;

    m_frequencies[animation] = frequency;
}

void AnimationManager::deleteAnimation(string animation) {
    m_textures.erase(animation);
    m_indicies.erase(animation);
    m_startingIndicies.erase(animation);
    m_sheetSizes.erase(animation);
    m_spriteSizes.erase(animation);
    m_frequencies.erase(animation);
    m_timesUpdated.erase(animation);
    m_endingIndicies.erase(animation);
}

int AnimationManager::getFramesAmount(const std::string& animation) const {
    auto it = m_sheetSizes.find(animation);
    if (it != m_sheetSizes.end()) {
        const sf::Vector2i& sheetSize = it->second;
        return sheetSize.x * sheetSize.y;
    }
    return -1;
}