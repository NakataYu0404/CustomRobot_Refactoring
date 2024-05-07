#pragma once
#include "SceneBase.h"
class ResourceManager;

class TitleScene : public SceneBase
{

public:

	//  コンストラクタ
	TitleScene(void);

	//  デストラクタ
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	//  画像
	int imgTitle_;
	int modelSkyId_;
	float rotY_;

	ResourceManager& resMng_;
};
