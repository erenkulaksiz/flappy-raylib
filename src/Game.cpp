#include "raylib.h"
#include "Game.h"
#include "Player.h"
#include "Obstacle.h"
#include "DebugLogger.h"

Game::Game()
{
  DebugLogger::Log("Game::Game()");

  InitWindow(1280, 720, "raylib");

  DisableCursor();

  int maxFps = GetMonitorRefreshRate(GetCurrentMonitor());
  SetTargetFPS(maxFps);

  m_pPlayer = new Player();
  m_pObstacle = new Obstacle();
  m_pObstacle->SetPlayer(m_pPlayer);
  m_backgroundTexture = LoadTexture("resources/background.png");
}

Game::~Game()
{
  DebugLogger::Log("Game::~Game()");
  CloseWindow();
  delete m_pPlayer;
  m_pPlayer = nullptr;
  delete m_pObstacle;
  m_pObstacle = nullptr;
  UnloadTexture(m_backgroundTexture);
}

void Game::Update()
{
  BeginDrawing();
  ClearBackground(BLACK);

  DrawBackground();

  m_pPlayer->Draw();
  m_pObstacle->Draw();

  if (m_pPlayer->IsPlayerDead())
  {
    m_isGameOver = true;

    const char *gameOverText = "Game Over";
    int textWidth = MeasureText(gameOverText, 32);
    DrawText(gameOverText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 10, 32, WHITE);

    const char *restartText = "Press R to restart";
    int restartTextWidth = MeasureText(restartText, 16);
    DrawText(restartText, GetScreenWidth() / 2 - restartTextWidth / 2, GetScreenHeight() / 2 + 64, 16, WHITE);

    const char *scoreText = TextFormat("Score: %d", m_pPlayer->GetScore());
    int scoreTextWidth = MeasureText(scoreText, 16);
    DrawText(scoreText, GetScreenWidth() / 2 - scoreTextWidth / 2, GetScreenHeight() / 2 + 128, 16, WHITE);

    if (IsKeyPressed(KEY_R))
    {
      m_isGameOver = false;
      m_pPlayer->ResetPlayer();
      m_pObstacle->ResetObstacles();
    }
  }
  else
  {
    m_pPlayer->Update();
    m_pObstacle->Update();

    int score = m_pPlayer->GetScore();

    DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);
  }

  EndDrawing();
}

void Game::DrawBackground()
{
  DrawTexturePro(m_backgroundTexture,
                 Rectangle{0, 0, static_cast<float>(m_backgroundTexture.width), static_cast<float>(m_backgroundTexture.height)},
                 Rectangle{0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())},
                 Vector2{0, 0},
                 0.0f,
                 WHITE);
}
