#include <DxLib.h>
#include "../../Manager/SceneManager.h"
#include "ShotSniper.h"


void ShotSniper::SetParam(void)
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
	stunDamage_ = hpDamage_;

	ShotBlastMax_ = SHOT_BLAST_MAX;
	ShotBlastCnt_ = 0;
}


void ShotSniper::UpdateWeapon(void)
{
	// 移動量計算（進行方向×速度）
	movePow_ = VScale(dir_, speed_);
	// 毎フレーム速度増加
	speed_ += SPEED_UP;

	MV1SetScale(modelId_, scl_);
	MV1SetRotationXYZ(modelId_, rot_);
	MV1SetPosition(modelId_, pos_);
}
