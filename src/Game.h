#pragma once
#include "Player.h"
#include "Obstacle.h"
#include "raylib.h"

class Game
{
public:
  Game();
  ~Game();
  void Update();
  void DrawBackground();

private:
  float m_moveSpeed = 0.1f;
  Player *m_pPlayer = nullptr;
  Obstacle *m_pObstacle = nullptr;
  bool m_isGameOver = false;
  Texture2D m_backgroundTexture;
};
