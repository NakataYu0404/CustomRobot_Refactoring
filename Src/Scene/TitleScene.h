#pragma once
#include "SceneBase.h"
class ResourceManager;

class TitleScene : public SceneBase
{

public:

	//  �R���X�g���N�^
	TitleScene(void);

	//  �f�X�g���N�^
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	//  �摜
	int imgTitle_;
	int modelSkyId_;
	float rotY_;

	ResourceManager& resMng_;
};
