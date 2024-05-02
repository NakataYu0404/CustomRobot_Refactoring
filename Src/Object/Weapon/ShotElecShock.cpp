#include <DxLib.h>
#include "../../Manager/SceneManager.h"
#include "ShotElecShock.h"

void ShotElecShock::SetParam(void)
{
	// 使用メモリ容量と読み込み時間削減のため
	// モデルデータをいくつもメモリ上に存在させない
	modelId_ = MV1DuplicateModel(baseModelId_);

	// 弾の大きさを設定
	scl_ = { 4.0f,4.0f,4.0f };

	// 弾の角度を設定
	rot_ = { 0.0f,0.0f,0.0f };

	// 弾の速度
	speed_ = 10.0f;

	hpDamage_ = 70;
	stunDamage_ = 250;

	ShotBlastMax_ = 30;
	ShotBlastCnt_ = 0;
}

