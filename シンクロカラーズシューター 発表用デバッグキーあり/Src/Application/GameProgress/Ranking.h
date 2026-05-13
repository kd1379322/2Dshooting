#pragma once

class C_Ranking
{
public:
	C_Ranking(){}
	~C_Ranking(){}

	void Init();

	void Update();

	void Draw();

private:
	void Relese();

	void NumDraw(int Num, int keta, int i, Math::Matrix a_mat);

	int* Hairetu(int value, int digits)
	{
		// digits 要素の int 配列を動的に作成
		int* arr = new int[digits];

		// 配列の最後から順に埋めていく
		for (int i = digits - 1; i >= 0; --i) {
			arr[i] = value % 10;
			value /= 10;
		}

		return arr;
	}

	int Rk[3];

	KdTexture m_Rankingtex;
	KdTexture m_NumTex;
	KdTexture m_RankTex;

	KdTexture m_s_Tex;
	
	Math::Matrix m_scaleMat;	//拡大行列
	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_Rankingmat;
	Math::Matrix m_Nummat[3][10];
	Math::Matrix m_Rankmat[3];


	Math::Matrix m_s_mat;		//行列

	Math::Rectangle r_rect;

	int RankposX[3] = {450};

	float s_Alpha = 1.0f;
	float s_alphaAdd = -0.01f;

};
