#include "GameEngine.h"

void GameEngine::Redraw()
{
  go->draw();
  go2->draw();
  teamABar->draw();
  teamBBar->draw();
}

void GameEngine::Refresh()
{

}

void GameEngine::Run()
{
  std::thread goThread(&Player::play, go);
  std::thread go2Thread(&Player::play, go2);
  goThread.join();
  go2Thread.join();
}
