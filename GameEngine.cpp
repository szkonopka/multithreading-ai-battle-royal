#include "GameEngine.h"
using namespace Players;

void GameEngine::Redraw()
{
  gr.freeResource.lock();
  teamABar->draw();
  teamBBar->draw();

  for(Player *item : teamA) {
    item->draw();
  }

  for(Player *item : teamB) {
    item->draw();
  }
  gr.freeResource.unlock();
}

void GameEngine::Refresh()
{
  gr.freeResource.lock();
  teamASumHP = 0;
  teamBSumHP = 0;

  for(Player *player : teamA)
  {
    teamASumHP += player->getHp();
  }

  for(Player *player : teamB)
  {
    teamBSumHP += player->getHp();
  }
  gr.freeResource.unlock();

  teamABar->setCurrentProgress(teamASumHP / teamATotalHP);
  teamBBar->setCurrentProgress(teamBSumHP / teamBTotalHP);

  //CheckInWeaponsRange();
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
    //float yStep = ((-matrixWidth / 2 - 40.0f) + (i * matrixWidth / 2));
    float yStep = ((-matrixWidth / 2) + (i * matrixWidth / 2));
    teamA.push_back(new Player(-matrixWidth / 2, yStep, 100, 100, 0, teamAColor));
    teamB.push_back(new Player(matrixWidth / 2, yStep, 100, 100, 0, teamBColor));
  }

  for(int i = 0; i < teamSize; i++)
  {
    teamATotalHP += teamA[i]->getMaxHp();
    teamBTotalHP += teamB[i]->getMaxHp();
  }

  for(int i = 0; i < teamSize; i++)
  {
    std::cout << "A[" << i << "] X: " << teamA[i]->getXPosition() << ", Y: " << teamA[i]->getYPosition() << std::endl;
    std::cout << "B[" << i << "] X: " << teamB[i]->getXPosition() << ", Y: " << teamB[i]->getYPosition() << std::endl;
    //std::cin.get();
  }

  teamA[0]->setWeapon(sniper);
  teamA[1]->setWeapon(pistol);
  teamA[2]->setWeapon(shotgun);
  teamB[0]->setWeapon(sniper);
  teamB[1]->setWeapon(pistol);
  teamB[2]->setWeapon(shotgun);

  std::thread *teamAThreads = new std::thread[teamSize];
  std::thread *teamBThreads = new std::thread[teamSize];
  std::thread shootTickRate(&GameEngine::ShootTickRate, this);
  std::thread checkBulletsCollision(&GameEngine::CheckBulletsCollision, this);
  //std::thread checkInWeaponsRange(&GameEngine::CheckInWeaponsRange, this);

  for(int i = 0; i < teamSize; i++) {
    teamAThreads[i] = std::thread(&Player::play, teamA[i]);
    teamBThreads[i] = std::thread(&Player::play, teamB[i]);
  }

  checkBulletsCollision.join();
  shootTickRate.join();
  //checkInWeaponsRange.join();
  for(int i = 0; i < teamSize; i++) {
    teamAThreads[i].join();
    teamBThreads[i].join();
  }
}

void GameEngine::ShootTickRate()
{
  while(true)
  {
    Players::IsShooting = false;
    SLEEP(1);
    Players::IsShooting = true;
    SLEEP(1);
    CheckInWeaponsRange();
  }
}

void GameEngine::CheckInWeaponsRange()
{
  while(true)
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
          {
            float destX, destY;
            if(ax >= bx && ay >= by)
            {
              destX = bx - matrixWidth;
              destY = bx - matrixWidth;
            }

            if(ax >= bx && ay <= by)
            {
              destX = bx - matrixWidth;
              destY = bx + matrixWidth;
            }

            if(ax <= bx && ay >= by)
            {
              destX = bx + matrixWidth;
              destY = bx + matrixWidth;
            }

            if(ax <= bx && ay <= by)
            {
              destX = bx + matrixWidth;
              destY = bx - matrixWidth;
            }

            playerA->shoot(gr.tt, bx, by);
            //playerA->shoot(gr.tt, destX, destY);
          }
        }
      }

      if(((bx + br) >= (ax - aw)) && ((bx - br) <= (ax + aw)))
      {
        if(((by + br) >= (ay - aw)) && ((by - br) <= (ay + aw)))
        {
          if(Players::IsShooting)
          {
            float destX, destY;
            if(bx >= ax && by >= ay)
            {
              destX = ax - matrixWidth;
              destY = ax - matrixWidth;
            }

            if(bx >= ax && by <= ay)
            {
              destX = ax - matrixWidth;
              destY = ax + matrixWidth;
            }

            if(bx <= ax && by >= ay)
            {
              destX = ax + matrixWidth;
              destY = ax + matrixWidth;
            }

            if(bx <= ax && by <= ay)
            {
              destX = ax + matrixWidth;
              destY = ax - matrixWidth;
            }

            playerB->shoot(gr.tt, ax, ay);
            //playerB->shoot(gr.tt, destX, destY);
          }
        }
      }
    }
  }
  SLEEP(500);
  }
}

void GameEngine::CheckBulletsCollision()
{
  std::cout << "Sprawdzam kolizcje pociskow" << std::endl;
  while(true)
  {
    CheckTeamCollision(teamA, teamB);
    CheckTeamCollision(teamB, teamA);
    //CheckTeamCollision(teamB, teamA);
    /*
    for(Player *playerA : teamA)
    {
      for(Bullet &bullet : playerA->firedBullets)
      {
        float bltx = bullet.getXPosition();
        float blty = bullet.getYPosition();

        for(Player *playerB : teamB)
        {
          float bx = playerB->getXPosition();
          float by = playerB->getYPosition();
          float bw = playerB->getXSize();

          if((bltx <= (bx + bw)) && (bltx >= (bx - bw)))
          {
            if((blty <= (by + bw)) && (blty >= (by -bw)))
            {
              playerB->setHp(playerB->getHp() - 10.0f);

              auto it = std::find(playerA->firedBullets.begin(), playerA->firedBullets.end(), bullet);
              if(it != playerA->firedBullets.end()) { playerA->firedBullets.erase(it); }

              if(playerB->getHp() <= 0.0f)
              {
                playerB->setIsAlive(false);
                auto itPlayer = std::find(teamB.begin(), teamB.end(), playerB);
                if(itPlayer != teamB.end()) { teamB.erase(itPlayer); }
              }
            }
          }
        }

        if(bltx < -(matrixWidth / 2) || bltx > (matrixWidth / 2) || blty < -(matrixWidth / 2) || blty > (matrixWidth / 2))
        {
          auto it = std::find(playerA->firedBullets.begin(), playerA->firedBullets.end(), bullet);
          if(it != playerA->firedBullets.end()) { playerA->firedBullets.erase(it); }
          std::cout << "usuwam bullet" << std::endl;
        }
      }
    }
    */
    /*
    for(Player *playerB : teamB)
    {
      float bltx = bullet.getXPosition();
      float blty = bullet.getYPosition();

        for(Player *playerB : teamB)
        {
          float bx = playerB->getXPosition();
          float by = playerB->getYPosition();
          float bw = playerB->getXSize();

          if((bltx <= (bx + bw)) && (bltx >= (bx - bw)))
          {
            if((blty <= (by + bw)) && (blty >= (by -bw)))
            {
              playerB->setHp(playerB->getHp() - 10.0f);

              auto it = std::find(playerA->firedBullets.begin(), playerA->firedBullets.end(), bullet);
              if(it != playerA->firedBullets.end()) { playerA->firedBullets.erase(it); }

              if(playerB->getHp() <= 0.0f)
              {
                playerB->setIsAlive(false);
                auto itPlayer = std::find(teamB.begin(), teamB.end(), playerB);
                if(itPlayer != teamB.end()) { teamB.erase(itPlayer); }
              }
            }
          }
        }

        if(bltx < -(matrixWidth / 2) || bltx > (matrixWidth / 2) || blty < -(matrixWidth / 2) || blty > (matrixWidth / 2))
        {
          auto it = std::find(playerA->firedBullets.begin(), playerA->firedBullets.end(), bullet);
          if(it != playerA->firedBullets.end()) { playerA->firedBullets.erase(it); }
          std::cout << "usuwam bullet" << std::endl;
        }
      }
    }
    */
  }
}

void GameEngine::CheckTeamCollision(std::vector<Player *> &firstTeam, std::vector<Player *> &secondTeam)
{
  for(Player *playerA : firstTeam)
  {
    gr.tt.lock();
    for(Bullet &bullet : playerA->firedBullets)
    {
      float bltx = bullet.getXPosition();
      float blty = bullet.getYPosition();

      for(Player *playerB : secondTeam)
      {
        float bx = playerB->getXPosition();
        float by = playerB->getYPosition();
        float bw = playerB->getXSize();

        if((bltx <= (bx + bw)) && (bltx >= (bx - bw)))
        {
          if((blty <= (by + bw)) && (blty >= (by -bw)))
          {
            playerB->setHp(playerB->getHp() - 10.0f);

            auto it = std::find(playerA->firedBullets.begin(), playerA->firedBullets.end(), bullet);
            if(it != playerA->firedBullets.end()) { playerA->firedBullets.erase(it); }

            if(playerB->getHp() <= 0.0f)
            {
              gr.freeResource.lock();
              playerB->setIsAlive(false);
              auto itPlayer = std::find(secondTeam.begin(), secondTeam.end(), playerB);
              if(itPlayer != secondTeam.end()) { secondTeam.erase(itPlayer); }
              gr.freeResource.unlock();
            }
          }
        }
      }

      if(bltx < -(matrixWidth / 2) || bltx > (matrixWidth / 2) || blty < -(matrixWidth / 2) || blty > (matrixWidth / 2))
      {
        auto it = std::find(playerA->firedBullets.begin(), playerA->firedBullets.end(), bullet);
        if(it != playerA->firedBullets.end()) { playerA->firedBullets.erase(it); }
      }
    }
    gr.tt.unlock();
  }
}
