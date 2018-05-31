#include "Weapon.h"

class Armory
{
private:
  Weapon *sniper;
  Weapon *pistol;
  Weapon *shotgun;
public:
  Armory()
  {
    sniper = new Weapon();
    pistol = new Weapon();
    shotgun = new Weapon();
  }
};
