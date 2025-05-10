#pragma once
#include "raylib.h"
#include <vector>
#include "Player.h"

class Obstacle
{
public:
  Obstacle();
  ~Obstacle();
  void Update();
  void SetPlayer(Player *player) { m_pPlayer = player; }
  void ResetObstacles();
  void Draw();

private:
  void GenerateObstacle();
  void DrawObstacle(Vector2 position);
  void UpdatePositions();
  bool CheckCollision(Vector2 obstaclePosition);
  void CheckScore();
  std::vector<Vector2> m_obstaclePositions = {};
  float m_obstacleMoveSpeed = 250.0f;
  Player *m_pPlayer = nullptr;
  bool m_hasScoredCurrentObstacle = false;
  Texture2D m_obstacleTexture;
};