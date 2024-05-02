#include <DxLib.h>
#include "../Application.h"
#include "../Manager/ResourceManager.h"
#include "Stage.h"

Stage::Stage(void)
{
}

Stage::~Stage(void)
{
}

void Stage::Init(void)
{
	
	// 外部ファイルの3Dモデルをロード
	modelId_ = MV1LoadModel((Application::PATH_MODEL + "Stage/Stage.mv1").c_str());
	coverModelId_ = MV1LoadModel((Application::PATH_MODEL + "Stage/Cover.mv1").c_str());
	charId_ = MV1LoadModel((Application::PATH_MODEL + "Stage/Moji.mv1").c_str());

	modelSkyId_ = MV1LoadModel((Application::PATH_MODEL + "Stage/Sky.mv1").c_str());

	// 3Dモデルの大きさを設定(引数はXYZの倍数)
	MV1SetScale(modelId_, { 1.0f,1.0f,1.0f });
	MV1SetScale(coverModelId_, { 1.0f,1.0f,1.0f });

	MV1SetScale(charId_, { 1.0f,1.0f,1.0f });
	
	MV1SetScale(modelSkyId_, {2.0f,2.0f,2.0f });

	// 3Dモデルの位置(引数は3D座標)
	MV1SetPosition(modelId_, { 0.0f,0.0f,0.0f });
	MV1SetPosition(coverModelId_, { 0.0f,0.0f,0.0f });

	MV1SetPosition(charId_, { 0.0f,0.0f,0.0f });
	MV1SetPosition(modelSkyId_, { 0.0f,0.0f,0.0f });

	// 3Dモデルの向き(引数は、XYZの回転量 単位はラジアン)
	MV1SetRotationXYZ(modelId_, { 0.0f,0.0f,0.0f });
	MV1SetRotationXYZ(coverModelId_, { 0.0f,0.0f,0.0f });

	MV1SetRotationXYZ(charId_, { 0.0f,0.0f,0.0f });
	MV1SetRotationXYZ(modelSkyId_, { 0.0f,0.0f,0.0f });

	// 衝突判定情報(コライダ)の作成
	MV1SetupCollInfo(modelId_);
	MV1SetupCollInfo(coverModelId_);

}

void Stage::Update(void)
{

}

void Stage::Draw(void)
{

	// 描画に使用するシャドウマップを設定
	SetUseShadowMap(0, shadowH);
	// モデルの描画
	MV1DrawModel(modelId_);
	// 描画に使用するシャドウマップの設定を解除
	SetUseShadowMap(0, -1);

	MV1DrawModel(charId_);
	MV1DrawModel(modelSkyId_);

}

void Stage::Release(void)
{
	// ロードされた3Dモデルをメモリから解放
	MV1DeleteModel(modelId_);
	MV1DeleteModel(coverModelId_);
	MV1DeleteModel(charId_);
	MV1DeleteModel(charId_);
	MV1DrawModel(modelSkyId_);


}

int Stage::GetModelId(void)
{
	return modelId_;
}

int Stage::GetCoverModelId(void)
{
	return coverModelId_;
}

void Stage::SetShadowH(int Hand)
{
	shadowH = Hand;
}

