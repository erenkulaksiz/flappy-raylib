#include "raylib.h"
#include "Player.h"
#include "DebugLogger.h"

Player::Player()
{
  DebugLogger::Log("Player::Player()");
  ResetPlayer();
  m_texture = LoadTexture("resources/bird.png");
}

Player::~Player()
{
  DebugLogger::Log("Player::~Player()");
  UnloadTexture(m_texture);
}

void Player::Update()
{
  if (m_position.y <= (GetScreenHeight() - m_size.y))
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
}

void Player::Draw()
{
  DrawTexturePro(m_texture, Rectangle{0, 0, static_cast<float>(m_texture.width), static_cast<float>(m_texture.height)}, Rectangle{m_position.x, m_position.y, m_size.x, m_size.y}, Vector2{0, 0}, 0, WHITE);
}

void Player::ResetPlayer()
{
  m_position = Vector2{150, static_cast<float>(GetScreenHeight() / 2 - m_size.y / 2)};
  m_velocity = Vector2{0, 0};
  m_isPlayerDead = false;
  m_score = 0;
}