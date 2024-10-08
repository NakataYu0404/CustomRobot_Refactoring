#pragma once
class ResourceManager;

class Fader
{

public:

	//  フェードが進む速さ
	static constexpr float SPEED_ALPHA = 5.0f;

	//  状態
	enum class STATE
	{
		NONE, 
		FADE_OUT,	//  徐々に暗転
		FADE_IN		//  徐々に明転
	};

	Fader(void);

	//  状態の取得
	STATE GetState(void) const;

	//  フェード処理が終了しているか
	bool IsEnd(void) const;

	//  指定フェードを開始する
	void SetFade(STATE state);

	void Init(void);
	void Update(void);
	void Draw(void);

	void SetRand(void);
private:

	//  状態
	STATE state_;

	//  透明度
	float alpha_;

	//  状態(STATE)を保ったまま終了判定を行うため、
	//  Update->Draw->Updateの1フレーム判定用
	bool isPreEnd_;

	//  フェード処理の終了判定
	bool isEnd_;

	int imgSousakiH_;
	int imgSousakoH_;

	int rand_;
	bool random_;

	ResourceManager& resMng_;
};
