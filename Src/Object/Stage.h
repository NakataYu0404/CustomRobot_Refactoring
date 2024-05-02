#pragma once
class Stage
{
public:

	// コンストラクタ
	Stage(void);
	// デストラクタ
	~Stage(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	int GetModelId(void);
	int GetCoverModelId(void);

	void SetShadowH(int Hand);

private:

	// 3DモデルのハンドルID
	int modelId_;
	int coverModelId_;

	int modelSkyId_;

	// ステージ上に配置する飾り文字のID、当たり判定いらない
	int charId_;

	// 背景画像のハンドルID
	int imgBack_;

	int shadowH;

};

