#pragma once

class C_Title;

class C_GamePlay;

class C_Result;

class C_Mosaic;

class C_Ranking;

class C_Manual;

class C_Backgraund;

enum SceneType
{
	Title,
	GamePlay,
	Result,
	Ranking,
	Manual
};

class Scene
{
private:

	//シーン管理用変数
	SceneType nowScene;

	std::shared_ptr<C_Title>		m_Title;
	std::shared_ptr <C_GamePlay>	m_GamePlay;
	std::shared_ptr<C_Result>		m_Result;
	std::shared_ptr<C_Ranking>		m_Ranking;
	std::shared_ptr<C_Manual>		m_manual;

	std::shared_ptr<C_Mosaic>		m_mosaic;
	std::shared_ptr<C_Backgraund>	m_backgraund;

	bool SoundPlayed = false;

	SceneType Tgoto = Title;

public:

	// 初期設定
	void Init();

	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

private:

	bool Spacekeyflg = false;
	bool Xkeyflg = false;
	bool diff = false;

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
