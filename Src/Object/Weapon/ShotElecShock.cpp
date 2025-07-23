#include <DxLib.h>
#include "../../Manager/SceneManager.h"
#include "ShotElecShock.h"

void ShotElecShock::SetParam(void)
{
	// モデル複製
	modelId_ = MV1DuplicateModel(baseModelId_);

	// モデルスケール設定
	scl_ = { SCALE, SCALE, SCALE };

	// 回転初期化
	rot_ = { 0.0f,0.0f,0.0f };

	// 移動速度設定
	speed_ = SPEED;

	// ダメージ設定
	hpDamage_ = HP_DAMAGE;
	stunDamage_ = STUN_DAMAGE;

	ShotBlastMax_ = SHOT_BLAST_MAX;
	ShotBlastCnt_ = 0;
}

