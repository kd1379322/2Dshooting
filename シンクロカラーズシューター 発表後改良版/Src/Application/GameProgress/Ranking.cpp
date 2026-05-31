#include "Ranking.h"

void C_Ranking::Init()
{
	FILE* fp;

	if (fopen_s(&fp, "Data/Ranking.csv", "r") == 0)
	{

		fscanf_s(fp, "%d,%d,%d%*[^\n]", &Rk[0], &Rk[1], &Rk[2]);//頭に,で読み飛ばし

		fclose(fp);
	}
	m_Rankingtex.Load("Texture/Ranking_.png");
	m_NumTex.Load("Texture/Digit.png");
	m_RankTex.Load("Texture/Rank_.png");

	m_s_Tex.Load("Texture/Text_.png");

}

void C_Ranking::Update()
{

	s_Alpha += s_alphaAdd;

	if (s_Alpha < 0.3f)
	{
		s_Alpha = 0.3f;
		s_alphaAdd *= -1;
	}
	else if (s_Alpha > 1.0f)
	{
		s_Alpha = 1.0f;
		s_alphaAdd *= -1;
	}


	m_scaleMat = Math::Matrix::CreateScale(0.8f, 0.8f, 0);
	m_transMat = Math::Matrix::CreateTranslation(0, -280, 0);
	m_s_mat = m_scaleMat * m_transMat;

	m_scaleMat = Math::Matrix::CreateScale(0.9f, 0.9f, 0);
	m_transMat = Math::Matrix::CreateTranslation(0, 100, 0);
	m_Rankingmat = m_scaleMat * m_transMat;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			m_scaleMat = Math::Matrix::CreateScale(0.45f, 0.45f, 0);
			m_transMat = Math::Matrix::CreateTranslation(128 * j * 0.45f - 150, 127 * i - 90, 0);
			m_Nummat[i][j] = m_scaleMat * m_transMat;
		}

		m_scaleMat = Math::Matrix::CreateScale(0.4f, 0.4f, 0);
		m_transMat = Math::Matrix::CreateTranslation(RankposX[i], 128 * i - 95, 0);
		m_Rankmat[i] = m_scaleMat * m_transMat;
	}
}

void C_Ranking::Draw()
{
	Math::Rectangle rect;

	rect = { 0,620,1280,100 };

	SHADER.m_spriteShader.SetMatrix(m_s_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex(&m_s_Tex, rect, s_Alpha);//画像の描画

	rect = { 0,0,1536,1025 };
	SHADER.m_spriteShader.SetMatrix(m_Rankingmat);//行列のセット
	SHADER.m_spriteShader.DrawTex(&m_Rankingtex, rect, 1.0f);//画像の描画

	//RankposX = 450;

	for (int i = 0; i < 3; i++)
	{
		if (Rk[i] < 50000)
		{
			RankposX[i] = 450;
			r_rect = { 690,220,230,210 };//E
		}
		else if (Rk[i] < 100000)
		{
			RankposX[i] = 450;
			r_rect = { 460,220,230,210 };//D
		}
		else if (Rk[i] < 300000)
		{
			RankposX[i] = 450;
			r_rect = { 230,220,230,210 }; //C
		}
		else if (Rk[i] < 500000)
		{
			RankposX[i] = 460;
			r_rect = { 0,220,230,210 }; //B
		}
		else if (Rk[i] < 800000)
		{
			RankposX[i] = 450;
			r_rect = { 690,0,230,210 };  //A
		}
		else if (Rk[i] < 1000000)
		{
			RankposX[i] = 460;
			r_rect = { 460,0,230,210 };	//A+
		}
		else if (Rk[i] < 1200000)
		{
			RankposX[i] = 460;
			r_rect = { 230,0,230,210 };	//S
		}
		else
		{
			RankposX[i] = 470;
			r_rect = { 0,0,230,210 };		//S+
		}

		SHADER.m_spriteShader.SetMatrix(m_Rankmat[i]);//行列のセット
		SHADER.m_spriteShader.DrawTex(&m_RankTex, r_rect, 1.0f);//画像の描画
	}


	for (int i = 0; i < 7; i++)
	{
		NumDraw(Rk[0], 7, i, m_Nummat[0][i]);
	}

	for (int i = 0; i < 7; i++)
	{
		NumDraw(Rk[1], 7, i, m_Nummat[1][i]);
	}

	for (int i = 0; i < 7; i++)
	{
		NumDraw(Rk[2], 7, i, m_Nummat[2][i]);
	}
}

void C_Ranking::Relese()
{
	m_Rankingtex.Release();
	m_NumTex.Release();
	m_RankTex.Release();
}

void C_Ranking::NumDraw(int Num, int keta, int i, Math::Matrix a_mat)
{
	Math::Rectangle Numrect;

	// 数字
	if (Hairetu(Num, keta)[i] == 0)
	{
		Numrect = { 128 * 9, 0, 128, 256 };
	}
	else
	{
		Numrect = { 128 * (Hairetu(Num, keta)[i] - 1), 0, 128, 256 };
	}

	SHADER.m_spriteShader.SetMatrix(a_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex(&m_NumTex, Numrect, 1.0f);//画像の描画

}
