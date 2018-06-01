#pragma once
#include "Weapon.h"
#include <mutex>
#include <vector>

class Armory
{
private:
  Weapon *sniper;
  Weapon *pistol;
  Weapon *shotgun;
  std::mutex sniperRes;
  std::mutex pistolRes;
  std::mutex shotgunRes;
  std::vector<std::mutex *> resources;
  std::vector<Weapon *> weapons;
  int weaponId = 0;
public:
  Armory()
  {
    sniper = new Weapon(700.0f, 5.0f, 1000, 1, 1, weaponId++);
    shotgun = new Weapon(180.0f, 8.0f, 800, 1, 1, weaponId++);
    pistol = new Weapon(300.0f, 3.0f, 300, 1, 1, weaponId++);
    weapons = { *&sniper, *&shotgun, *&pistol };
    resources = { &sniperRes, &shotgunRes, &pistolRes };
  }

  Weapon *getSniper() { return sniper; }
  Weapon *getPistol() { return pistol; }
  Weapon *getShotgun() { return shotgun; }

  std::vector<std::mutex *> getResources() { return resources; }
  std::vector<Weapon *> getWeapons() { return weapons; }
};
