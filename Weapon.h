class Weapon : public GameObject
{
private:
  int ownerID;
  float range;
  float damage;
  float bulletSize;
public:
  Weapon() { }
  Weapon(float _range, float _damage)
  {
    range = _range;
    damage = _damage;
  }

  void setRange(float _range) { range = _range; }
  float getRange() { return range; }

  void setDamage(float _damage) { damage = _damage; }
  float getDamage() { return damage; }

  void setOwnerID(int _ownerID) { ownerID = _ownerID; }
  int getOwnerID() { return ownerID; }
};
