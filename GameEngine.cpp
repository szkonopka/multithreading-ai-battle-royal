#include "GameEngine.h"
using namespace Players;

void GameEngine::Redraw()
{
  teamABar->draw();
  teamBBar->draw();

  for(Player *item : teamA) {
    item->draw();
  }

  for(Player *item : teamB) {
    item->draw();
  }
}

void GameEngine::Refresh()
{
  for(int i = 0; i < teamSize; i++)
  {
    teamATotalHP += teamA[i]->getMaxHp();
    teamASumHP += teamA[i]->getHp();
    teamBTotalHP += teamB[i]->getMaxHp();
    teamBSumHP += teamB[i]->getHp();
  }

  teamABar->setCurrentProgress(teamASumHP / teamATotalHP);
  teamBBar->setCurrentProgress(teamBSumHP / teamBTotalHP);

  CheckInWeaponsRange();
}

void GameEngine::Run()
{
  Weapon *sniper = new Weapon(400.0f, 30.0f);
  Weapon *shotgun = new Weapon(100.0f, 40.0f);
  Weapon *pistol = new Weapon(175.0f, 35.0f);

  Players::PlayerID = 0;
  color3 teamAColor = { 1.0f, 0.0f, 0.0f };
  color3 teamBColor = { 0.0f, 0.0f, 1.0f };
  for(int i = 0; i < teamSize; i++) {
    float yStep = ((-matrixWidth / 2 - 40.0f) + (i * matrixWidth / 2));
    teamA.push_back(new Player(Players::PlayerID++, -matrixWidth / 2, yStep, 100, 100, 0, teamAColor));
    teamB.push_back(new Player(Players::PlayerID++, matrixWidth / 2, yStep, 100, 100, 0, teamBColor));
  }

  teamA[0]->setWeapon(sniper);
  //teamA[2]->setWeapon(shotgun);
  teamB[0]->setWeapon(pistol);

  std::thread *teamAThreads = new std::thread[teamSize];
  std::thread *teamBThreads = new std::thread[teamSize];
  std::thread shootTickRate(&ShootTickRate);

  for(int i = 0; i < teamSize; i++) {
    teamAThreads[i] = std::thread(&Player::play, teamA[i]);
    teamBThreads[i] = std::thread(&Player::play, teamB[i]);
  }

  shootTickRate.join();
  for(int i = 0; i < teamSize; i++) {
    teamAThreads[i].join();
    teamBThreads[i].join();
  }
}

void GameEngine::ShootTickRate()
{
  while(true)
  {
    Players::IsShooting = true;
    SLEEP(1);
    Players::IsShooting = false;
    SLEEP(500);
  }
}

void GameEngine::CheckInWeaponsRange()
{
  for(Player *playerA: teamA)
  {
    float ax = playerA->getXPosition();
    float ay = playerA->getYPosition();
    float aw = playerA->getXSize();
    float ar = playerA->getRange();

    for(Player *playerB : teamB)
    {
      float bx = playerB->getXPosition();
      float by = playerB->getYPosition();
      float bw = playerB->getXSize();
      float br = playerB->getRange();

      if(((ax + ar) >= (bx - bw)) && ((ax - ar) <= (bx + bw)))
      {
        if(((ay + ar) >= (by - bw)) && ((ay - ar) <= (by + bw)))
        {
          /*
          std::cout << "KOLIZJA " <<  playerB->getId() << " ORAZ " << playerA->getId() << std::endl;
          std::cout << ax + ar << " >= " << bx - bw << " " << ax - ar << " <= " << bx + bw << std::endl;
          std::cout << "A: ( " << ax << " , " << ay << " ) - range: " << ar << " - width: " << aw << std::endl;
          std::cout << "B: ( " << bx << " , " << by << " ) - range: " << br << " - width: " << bw <<std::endl;
          std::cin.get();
          */
          if(Players::IsShooting)
            playerA->shoot();
          //SLEEP(100);
        }
      }
    }
  }
}
