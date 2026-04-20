#include "GamePlay.h"

void C_GamePlay::Init()
{
	m_playerTex.Load("Texture/player.png");
	m_player.SetTex(&m_playerTex);

	m_enemyTex.Load("Texture/enemy.png");
	m_player.SetTex(&m_enemyTex);

	GameCnt = 0;
	m_player.Init();
	m_enemy.Init();
}

void C_GamePlay::Update()
{
	GameCnt++;
	m_player.Update();
	m_enemy.Update();
}

void C_GamePlay::Draw2D()
{
	m_player.Draw2D();
	m_enemy.Draw2D();
}

void C_GamePlay::ImGuiUpdate()
{
	ImGui::Text("GameC = %d", GameCnt);
	m_player.ImGuiUpdate();
}
