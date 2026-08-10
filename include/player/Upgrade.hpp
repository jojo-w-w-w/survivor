#pragma once
#include <string>
#include <vector>

class Player; // 前向声明

struct Upgrade {
    std::string name;
    std::string description;
    void (*apply)(Player&);   // 函数指针代替 std::function

    static void increaseAttackSpeed(Player& p);
    static void increaseMoveSpeed(Player& p);
    static void increaseMaxHp(Player& p);
    static void increaseBulletSpeed(Player& p);
    static void increaseBulletCount(Player& p);
};

extern std::vector<Upgrade> allUpgrades;