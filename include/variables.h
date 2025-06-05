#pragma once

#include <iostream>
#include <fstream>

using namespace std;

enum Screens {
    MainMenu,
    Continue,
    NewGame,
    Creation,
    GameMenu,
    Profile,
    BattleMenu,
    Fight,
    AssignPoints
};

enum Textures {
    Background,
    AppName,
    Button,
    Back,
    StartFightButton,
    KnightIdle,
    KnightAttack,
    KnightHurt,
    KnightDie,
    ArcherIdle,
    ArcherAttack,
    ArcherHurt,
    ArcherDie,
    WizardIdle,
    WizardAttack,
    WizardHurt,
    WizardDie,
    FireWormIdle,
    FireWormAttack,
    FireWormHurt,
    FireWormDie,
    GoblinIdle,
    GoblinAttack,
    GoblinHurt,
    GoblinDie,
    SkeletonIdle,
    SkeletonAttack,
    SkeletonHurt,
    SkeletonDie,
    MushroomIdle,
    MushroomAttack,
    MushroomHurt,
    MushroomDie,
    ShadowWarriorIdle,
    ShadowWarriorAttack,
    ShadowWarriorHurt,
    ShadowWarriorDie,
    NecromancerIdle,
    NecromancerAttack,
    NecromancerHurt,
    NecromancerDie,
    MinotaurIdle,
    MinotaurAttack,
    MinotaurHurt,
    MinotaurDie,
    BronzeLaurel,
    SilverLaurel,
    GoldLaurel
};

enum Fonts {
    NewRocker,
    LatoRegular,
    LatoLight,
    LatoBold
};

struct PlayerData {
    string playerName, className, password;
    int level = 1;
    int experience = 0;
    int expNeeded = 100;
    int health, attack, defence, dodge;
    int killed = 0;
    int points = 0;
    int classIdentifier;
};

struct ClassData
{
    int health, attack, defence, dodge, classIdentifier;
};