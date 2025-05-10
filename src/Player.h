#pragma once
#include "raylib.h"

class Player
{
public:
  Player();
  ~Player();
  Vector2 GetPosition() { return m_position; }
  void SetPosition(const Vector2 &position) { m_position = position; }
  Vector2 GetVelocity() { return m_velocity; }
  void SetVelocity(const Vector2 &velocity) { m_velocity = velocity; }
  float GetSpeed() { return m_speed; }
  void SetSpeed(float speed) { m_speed = speed; }
  void Update();
  bool IsPlayerDead() { return m_isPlayerDead; }
  void SetPlayerDead(bool isPlayerDead) { m_isPlayerDead = isPlayerDead; }
  Vector2 GetSize() { return m_size; }
  void SetSize(const Vector2 &size) { m_size = size; }
  void ResetPlayer();
  void IncrementScore() { m_score++; }
  int GetScore() { return m_score; }
  void SetScore(int score) { m_score = score; }
  void Draw();

private:
  Vector2 m_position = {0, 0};
  Vector2 m_velocity = {0, 0};
  Vector2 m_size = {64, 45};
  float m_speed = 2.0f;
  bool m_isPlayerDead = false;
  int m_score = 0;
  Texture2D m_texture;
};
