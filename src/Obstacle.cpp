#include "Obstacle.h"
#include "DebugLogger.h"

Vector2 obstacleSize = {120, 700};
float obstacleHeightBetween = 100;
int minObstaclePosition = 150;
int obstacleBetweenDistance = 400;

Obstacle::Obstacle()
{
  DebugLogger::Log("Obstacle::Obstacle()");
  m_obstacleTexture = LoadTexture("resources/pipe.png");
}

Obstacle::~Obstacle()
{
  DebugLogger::Log("Obstacle::~Obstacle()");
  m_obstaclePositions.clear();
  UnloadTexture(m_obstacleTexture);
}

void Obstacle::Update()
{
  if (m_obstaclePositions.size() <= 10)
  {
    GenerateObstacle();
  }

  for (int i = 0; i < m_obstaclePositions.size(); i++)
  {
    if (m_pPlayer && CheckCollision(m_obstaclePositions[i]))
    {
      m_pPlayer->SetPlayerDead(true);
    }
  }

  CheckScore();
  UpdatePositions();
}

void Obstacle::Draw()
{
  for (int i = 0; i < m_obstaclePositions.size(); i++)
  {
    DrawObstacle(m_obstaclePositions[i]);
  }
}

bool Obstacle::CheckCollision(Vector2 obstaclePosition)
{
  if (!m_pPlayer)
    return false;

  Vector2 playerPos = m_pPlayer->GetPosition();
  Vector2 playerSize = m_pPlayer->GetSize();

  float topObstacleY = (obstaclePosition.y - obstacleSize.y) - obstacleHeightBetween;
  float bottomObstacleY = obstaclePosition.y + obstacleHeightBetween;

  Rectangle playerRect = {
      playerPos.x,
      playerPos.y,
      playerSize.x,
      playerSize.y};

  Rectangle topObstacleRect = {
      obstaclePosition.x - obstacleSize.x / 2,
      topObstacleY,
      obstacleSize.x,
      obstacleSize.y};

  Rectangle bottomObstacleRect = {
      obstaclePosition.x - obstacleSize.x / 2,
      bottomObstacleY,
      obstacleSize.x,
      obstacleSize.y};

  return CheckCollisionRecs(playerRect, topObstacleRect) ||
         CheckCollisionRecs(playerRect, bottomObstacleRect);
}

void Obstacle::DrawObstacle(Vector2 position)
{
  float topObstaclePosition = (position.y - obstacleSize.y) - obstacleHeightBetween;
  float bottomObstaclePosition = position.y + obstacleHeightBetween;

  DrawTexturePro(
      m_obstacleTexture,
      Rectangle{
          0,
          0,
          static_cast<float>(m_obstacleTexture.width),
          static_cast<float>(m_obstacleTexture.height)},
      Rectangle{
          position.x - obstacleSize.x / 2,
          topObstaclePosition,
          obstacleSize.x,
          obstacleSize.y},
      Vector2{obstacleSize.x, obstacleSize.y},
      180.0f,
      WHITE);

  DrawTexturePro(
      m_obstacleTexture,
      Rectangle{
          0,
          0,
          static_cast<float>(m_obstacleTexture.width),
          static_cast<float>(m_obstacleTexture.height)},
      Rectangle{
          position.x - obstacleSize.x / 2,
          bottomObstaclePosition,
          obstacleSize.x,
          obstacleSize.y},
      Vector2{0, 0},
      0,
      WHITE);
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

    if (m_obstaclePositions[i].x < -obstacleSize.x)
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