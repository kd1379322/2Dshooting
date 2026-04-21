#include "Player.h"

void C_Player::Init()
{
	Moveflg = true;
	playerAlpha = 1.0f;
	Hp = MHp;
	m_pos = { -300,0 };
	rect = { 0,0,64,64 };


	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scaleMat = Math::Matrix::CreateScale(2, 2, 0);
	m_rotationMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(270));
	m_mat = m_scaleMat * m_rotationMat * m_transMat;
}

void C_Player::Update()
{

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (m_pos.x > ScreenLeft + PlayerSize)
		{
			m_pos.x -= m_moveSpeed;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (m_pos.x < ScreenRight - PlayerSize)
		{
			m_pos.x += m_moveSpeed;
		}
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (m_pos.y < ScreenTop - PlayerSize)
		{
			m_pos.y += m_moveSpeed;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (m_pos.y > ScreenBottom + PlayerSize)
		{
			m_pos.y -= m_moveSpeed;
		}
	}
	

	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scaleMat = Math::Matrix::CreateScale(2, 2, 0);
	m_rotationMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(270));
	m_mat = m_scaleMat * m_rotationMat * m_transMat;
}

void C_Player::Draw2D()
{


	//プレイヤーの描画
	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex(m_PlayerTex, rect, playerAlpha);//画像の描画

}

void C_Player::ImGuiUpdate()
{
	//ImGui::Text("x = %f", m_pos.x);
	//ImGui::Text("y = %f", m_pos.y);

}
