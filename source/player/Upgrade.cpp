#include "Upgrade.hpp"
#include "Player.hpp"

std::vector<Upgrade> allUpgrades = {
    {"Fire Rate +",    "Reduce shoot cooldown by 10%", [](Player& p) { p.reduceShootCooldown(0.9f); }},
    {"Move Speed +",   "Increase move speed by 10%",   [](Player& p) { p.increaseSpeed(1.1f); }},
    {"Max HP +",       "Max HP +1, heal 1",            [](Player& p) { p.increaseMaxHp(1); }},
    {"Bullet Speed +", "Bullet speed +20%",             [](Player& p) { p.increaseBulletSpeed(1.2f); }},
    {"Multishot +1",   "Fire an extra bullet",          [](Player& p) { p.increaseBulletCount(1); }}
};