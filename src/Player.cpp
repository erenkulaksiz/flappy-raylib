#include "raylib.h"
#include "Player.h"
#include "DebugLogger.h"

Player::Player()
{
  DebugLogger::Log("Player::Player()");
  ResetPlayer();
}

Player::~Player()
{
  DebugLogger::Log("Player::~Player()");
}

void Player::Update()
{
  if (m_position.y <= (GetScreenHeight() - m_size))
  {
    m_velocity.y += GetFrameTime() * 5.0f;
  }
  else
  {
    m_velocity.y = 0;
    m_isPlayerDead = true;
  }

  if (IsKeyPressed(KEY_SPACE))
  {
    m_velocity.y -= 2.5f;
  }

  m_position.x += m_velocity.x;
  m_position.y += m_velocity.y;

  DrawRectangleV(m_position, Vector2{m_size, m_size}, RED);
}

void Player::ResetPlayer()
{
  m_position = Vector2{150, static_cast<float>(GetScreenHeight() / 2 - m_size / 2)};
  m_velocity = Vector2{0, 0};
  m_isPlayerDead = false;
  m_score = 0;
}