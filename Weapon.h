#pragma once
#include "GameObject.h"
#include <string>

class Weapon : public GameObject
{
private:
  int id;
  int ownerID;
  float range;
  float damage;
  int frequency;
  int capacity;
  float bulletSize;
  bool armored;
  std::string name;
public:
  Weapon() : armored(false), name("none") { }
  Weapon(float _range, float _damage, int _frequency, int _capacity, float _bulletSize, int _id, std::string _name) :
  range(_range), damage(_damage), frequency(_frequency), capacity(_capacity), bulletSize(_bulletSize), armored(true), id(_id), name(_name)
  { }

  void setId(int _id) { id = _id; }
  int getId() { return id; }

  void setRange(float _range) { range = _range; }
  float getRange() { return range; }

  void setDamage(float _damage) { damage = _damage; }
  float getDamage() { return damage; }

  void setFrequency(int _frequency) { frequency = _frequency; }
  int getFrequency() { return frequency; }

  void setOwnerID(int _ownerID) { ownerID = _ownerID; }
  int getOwnerID() { return ownerID; }

  void setCapacity(int _capacity) { capacity = _capacity; }
  int getCapacity() { return capacity; }

  void setBulletSize(int _bulletSize) { bulletSize = _bulletSize; }
  float getBulletSize() { return bulletSize; }

  void setArmored(bool _armored) { armored = _armored; }
  bool getArmored() { return armored; }

  void setName(std::string _name) { name = _name; }
  std::string getName() { return name; }
};
