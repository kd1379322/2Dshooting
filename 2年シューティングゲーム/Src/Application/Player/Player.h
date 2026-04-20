#pragma once
#include "Bullet.h"

class C_Player
{
public:
	C_Player(){}
	~C_Player() {}

	// 初期設定
	void Init();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

	void SetTex(KdTexture* tex) { m_PlayerTex = tex; }
private:

	const float m_moveSpeed = 16.0f;	//移動速度

	const float ScreenTop = 360;	
	const float ScreenBottom = -360;	
	const float ScreenLeft = -640;	
	const float ScreenRight = 640;	

	const float PlayerSize = 64;	
	
	bool Moveflg;					//行動用フラグ

	bool Bulletkeyflg;			//弾発射キーフラグ
	int BulletCnt;

	int playerAlpha;
	int Hp;						//HP
	static const int MHp = 6;	//HPの最大値

	KdTexture* m_PlayerTex;			//画像用	

	Math::Vector2 m_pos;		//座標

	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_scaleMat;	//拡大行列
	Math::Matrix m_rotationMat;	//回転行列
	Math::Matrix m_mat;			//プレイヤー行列

	Math::Rectangle rect;	//プレイヤー切り取り範囲

	static const int MaxBullet = 10;
	C_Bullet m_Bullet[MaxBullet];
	KdTexture m_BulletTex;			//画像用	

};

