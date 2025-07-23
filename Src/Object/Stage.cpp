#include <DxLib.h>
#include "../Application.h"
#include "../Manager/ResourceManager.h"
#include "Stage.h"

Stage::Stage() : resMng_(ResourceManager::GetInstance()) {}

Stage::~Stage() {}

void Stage::Init()
{
    // 外部ファイルの3Dモデルをロード
    modelId_ = resMng_.LoadModelDuplicate(ResourceManager::SRC::MDL_STAGE);
    coverModelId_ = resMng_.LoadModelDuplicate(ResourceManager::SRC::MDL_COVER);
    charId_ = resMng_.LoadModelDuplicate(ResourceManager::SRC::MDL_CHAR);
    modelSkyId_ = resMng_.LoadModelDuplicate(ResourceManager::SRC::MDL_SKYDOME);

    // 3Dモデルの大きさを設定
    MV1SetScale(modelId_, { 1.0f,1.0f,1.0f });
    MV1SetScale(coverModelId_, { 1.0f,1.0f,1.0f });
    MV1SetScale(charId_, { 1.0f,1.0f,1.0f });
    MV1SetScale(modelSkyId_, {2.0f,2.0f,2.0f });

    // 3Dモデルの位置設定
    MV1SetPosition(modelId_, { 0.0f,0.0f,0.0f });
    MV1SetPosition(coverModelId_, { 0.0f,0.0f,0.0f });
    MV1SetPosition(charId_, { 0.0f,0.0f,0.0f });
    MV1SetPosition(modelSkyId_, { 0.0f,0.0f,0.0f });

    // 3Dモデルの回転設定
    MV1SetRotationXYZ(modelId_, { 0.0f,0.0f,0.0f });
    MV1SetRotationXYZ(coverModelId_, { 0.0f,0.0f,0.0f });
    MV1SetRotationXYZ(charId_, { 0.0f,0.0f,0.0f });
    MV1SetRotationXYZ(modelSkyId_, { 0.0f,0.0f,0.0f });

    // コリジョン情報の作成
    MV1SetupCollInfo(modelId_);
    MV1SetupCollInfo(coverModelId_);
}

void Stage::Update() {}

void Stage::Draw()
{
    // シャドウマップ設定
    SetUseShadowMap(0, shadowH);
    MV1DrawModel(modelId_);
    SetUseShadowMap(0, -1);
    MV1DrawModel(charId_);
    MV1DrawModel(modelSkyId_);
}

void Stage::Release()
{
    // モデルの削除
    MV1DeleteModel(modelId_);
    MV1DeleteModel(coverModelId_);
    MV1DeleteModel(charId_);
    MV1DeleteModel(modelSkyId_);
}

int Stage::GetModelId()
{
    return modelId_;
}

int Stage::GetCoverModelId()
{
    return coverModelId_;
}

void Stage::SetShadowH(int handle)
{
    shadowH = handle;
}

