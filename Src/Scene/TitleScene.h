#pragma once
#include "SceneBase.h"
class ResourceManager;

class TitleScene : public SceneBase
{

public:

	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);


	//
	void Init(void) override;
	//
	void Update(void) override;
	//
	void Draw(void) override;
	//
	void Release(void) override;


private:

	int imgTitle_;        // タイトル画像ハンドル
	int modelSkyId_;      // 空背景モデルID
	float rotY_;          // 背景回転値

	ResourceManager& resMng_;
};
