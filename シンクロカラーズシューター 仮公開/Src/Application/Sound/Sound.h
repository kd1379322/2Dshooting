#pragma once

class C_Sound
{
public:
	C_Sound(){}
	~C_Sound(){}

	void Init();

	void Title_BGM();              //タイトルBGM
	void Game_BGM();               //ゲーム中BGM         
	void Result_BGM();             //リザルトBGM 

	void PlayerDamage_SE();        //プレイヤーがくらった時のダメージ音

	void EnemyDamage_SE();         //敵がくらった時のダメージ音

	void Hinsi_SE();               //瀕死
	
	void drum_SE();                //リザルトのゲーム結果の数字が増えていく音
	void LevelUp_SE();             //リザルトのゲーム結果の数字がでた音
	void CountDown1_SE();          //ゲーム開始時のカウントダウン
	void CountDown2_SE();          //カウントダウンが1の後になるときの音
	
	void DecisionSound_SE();       //決定時の音

	void Start_SE();
	void Finish_SE();

	void Chenge_SE();

	void AllSoundStop();           //音を一斉に止める

	//BGM
	//タイトルBGM
	std::shared_ptr<KdSoundEffect>		Title_bgm;		 //音データ
	std::shared_ptr<KdSoundInstance>	Title_bgmInst;	 //音を鳴らす為の変数(イメージ的にはスピーカー)

	//ゲームBGM
	std::shared_ptr<KdSoundEffect>		Game_bgm;		 //音データ
	std::shared_ptr<KdSoundInstance>	Game_bgmInst;	 //音を鳴らす為の変数(イメージ的にはスピーカー)
	//			型名					変数名

	//リザルトBGM  
	std::shared_ptr<KdSoundEffect>		Result_bgm;		 //音データ
	std::shared_ptr<KdSoundInstance>	Result_bgmInst;	 //音を鳴らす為の変数(イメージ的にはスピーカー)

	//SE


	//プレイヤーがくらった時のダメージ音
	std::shared_ptr<KdSoundEffect>		PlayerDamage_se;
	std::shared_ptr<KdSoundInstance>	PlayerDamage_seInst;


	//敵がくらった時のダメージ音
	std::shared_ptr<KdSoundEffect>		EnemyDamage_se;
	std::shared_ptr<KdSoundInstance>	EnemyDamage_seInst;


	//瀕死音
	std::shared_ptr<KdSoundEffect>		Hinsi_se;
	std::shared_ptr<KdSoundInstance>	Hinsi_seInst;

	//キャンセル時の音
	std::shared_ptr<KdSoundEffect>		CancelSound_se;
	std::shared_ptr<KdSoundInstance>	CancelSound_seInst;

	//決定時の音
	std::shared_ptr<KdSoundEffect>		DecisionSound_se;
	std::shared_ptr<KdSoundInstance>	DecisionSound_seInst;

	//リザルトのゲーム結果の数字が増えていく音
	std::shared_ptr<KdSoundEffect>		Drum_se;
	std::shared_ptr<KdSoundInstance>	Drum_seInst;

	//リザルトのゲーム結果の数字がでた音
	std::shared_ptr<KdSoundEffect>		Levelup_se;
	std::shared_ptr<KdSoundInstance>	Levelup_seInst;

	// ゲーム開始時のカウントダウン音
	std::shared_ptr<KdSoundEffect>		Countdown1_se;
	std::shared_ptr<KdSoundInstance>	Countdown1_seInst;

	// カウントダウンが1の後になるときの音
	std::shared_ptr<KdSoundEffect>		Countdown2_se;
	std::shared_ptr<KdSoundInstance>	Countdown2_seInst;

	std::shared_ptr<KdSoundEffect>		Start_se;
	std::shared_ptr<KdSoundInstance>	Start_seInst;

	std::shared_ptr<KdSoundEffect>		finish_se;
	std::shared_ptr<KdSoundInstance>	finish_seInst;


	std::shared_ptr<KdSoundEffect>		Chenge_se;
	std::shared_ptr<KdSoundInstance>	Chenge_seInst;


	float Bgmvol;
	float Sevol;
private:

public:
	static C_Sound& GetInstance()
	{
		static C_Sound instance;
		return instance;
	}
};

#define SOUND C_Sound::GetInstance()


