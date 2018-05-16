class GameEngine
{
private:
  int membersInTeam;
  std::vector<Player> teamA;
  std::vector<Player> teamB;
public:
  void checkForCollisions();
};
