#include "Obstacle.h"
#include "DebugLogger.h"

float obstacleWidth = 100;
float obstacleHeight = 1000;
float obstacleHeightBetween = 100;
int minObstaclePosition = 150;
int obstacleBetweenDistance = 400;

Obstacle::Obstacle()
{
  DebugLogger::Log("Obstacle::Obstacle()");
}

Obstacle::~Obstacle()
{
  DebugLogger::Log("Obstacle::~Obstacle()");
}

void Obstacle::Update()
{
  if (m_obstaclePositions.size() <= 10)
  {
    GenerateObstacle();
  }

  for (int i = 0; i < m_obstaclePositions.size(); i++)
  {
    DrawObstacle(m_obstaclePositions[i]);

    if (m_pPlayer && CheckCollision(m_obstaclePositions[i]))
    {
      m_pPlayer->SetPlayerDead(true);
    }
  }

  CheckScore();
  UpdatePositions();
}

bool Obstacle::CheckCollision(Vector2 obstaclePosition)
{
  if (!m_pPlayer)
    return false;

  Vector2 playerPos = m_pPlayer->GetPosition();
  float playerSize = m_pPlayer->GetSize();

  float topObstacleY = (obstaclePosition.y - obstacleHeight) - obstacleHeightBetween;
  float bottomObstacleY = obstaclePosition.y + obstacleHeightBetween;

  Rectangle playerRect = {
      playerPos.x,
      playerPos.y,
      playerSize,
      playerSize};

  Rectangle topObstacleRect = {
      obstaclePosition.x - obstacleWidth / 2,
      topObstacleY,
      obstacleWidth,
      obstacleHeight};

  Rectangle bottomObstacleRect = {
      obstaclePosition.x - obstacleWidth / 2,
      bottomObstacleY,
      obstacleWidth,
      obstacleHeight};

  return CheckCollisionRecs(playerRect, topObstacleRect) ||
         CheckCollisionRecs(playerRect, bottomObstacleRect);
}

void Obstacle::DrawObstacle(Vector2 position)
{
  float topObstaclePosition = (position.y - obstacleHeight) - obstacleHeightBetween;
  float bottomObstaclePosition = position.y + obstacleHeightBetween;

  DrawRectangleV(Vector2{position.x - obstacleWidth / 2, topObstaclePosition}, Vector2{obstacleWidth, obstacleHeight}, RED);
  DrawRectangleV(Vector2{position.x - obstacleWidth / 2, bottomObstaclePosition}, Vector2{obstacleWidth, obstacleHeight}, RED);
}

void Obstacle::GenerateObstacle()
{
  int maxObstaclePosition = GetScreenHeight() - 150;

  float randomXPosition = static_cast<float>(GetRandomValue(minObstaclePosition, maxObstaclePosition));

  if (m_obstaclePositions.size() == 0)
  {
    m_obstaclePositions.push_back(Vector2{static_cast<float>(200 + obstacleBetweenDistance), randomXPosition});

    return;
  }

  int lastObstaclePosition = m_obstaclePositions[m_obstaclePositions.size() - 1].x;

  m_obstaclePositions.push_back(Vector2{static_cast<float>(lastObstaclePosition + obstacleBetweenDistance), randomXPosition});
}

void Obstacle::UpdatePositions()
{
  for (int i = 0; i < m_obstaclePositions.size(); i++)
  {
    m_obstaclePositions[i].x -= GetFrameTime() * m_obstacleMoveSpeed;

    if (m_obstaclePositions[i].x < -obstacleWidth)
    {
      m_obstaclePositions.erase(m_obstaclePositions.begin() + i);
    }
  }
}

void Obstacle::ResetObstacles()
{
  m_obstaclePositions = {};
  m_hasScoredCurrentObstacle = false;
}

void Obstacle::CheckScore()
{
  if (!m_pPlayer || m_pPlayer->IsPlayerDead() || m_obstaclePositions.size() == 0)
    return;

  Vector2 playerPos = m_pPlayer->GetPosition();

  Vector2 firstObstaclePos = m_obstaclePositions[0];

  if (playerPos.x > firstObstaclePos.x && !m_hasScoredCurrentObstacle)
  {
    m_pPlayer->IncrementScore();
    m_hasScoredCurrentObstacle = true;
  }
  else if (playerPos.x <= firstObstaclePos.x)
  {
    m_hasScoredCurrentObstacle = false;
  }
}