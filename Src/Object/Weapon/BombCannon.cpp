#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/ResourceManager.h"
#include "BombCannon.h"


void BombCannon::SetParam(void)
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

	ShotBlastCnt_ = 0;
	moveDistance = 0.0f;
	dirFlag = false;
	ShotBlastMax_ = SHOT_BLAST_MAX;
	blastCnt_ = 0;

	// クロスヘア初期化
	crossHairId_ = resMng_.LoadModelDuplicate(ResourceManager::SRC::MDL_CROSSHAIR);
	crosshairPos_ = enemyPos_;
	crosshairScl_ = { CROSSHAIR_SCALE, CROSSHAIR_SCALE, CROSSHAIR_SCALE };
	crosshairRot_ = { 0.0f,0.0f,0.0f };
	
	crosshairFlag_ = false;
}

void BombCannon::UpdateWeapon(void)
{
	// 移動量計算
	VECTOR movePow = VScale(dir_, speed_);
	// ジャンプしていないかつ発射位置Yが敵Y+0.5以下なら反転判定
	if (!isJump_ && posFire_.y <= enemyPos_.y + 0.5f)
	{
		moveDistance += sqrt((movePow.x * movePow.x) + (movePow.z * movePow.z));
		if ((moveDistance >= (plEnDistance_ / 2.0f) + (fmodf(plEnDistance_, 2.0f))) && dirFlag == false)
		{
			moveDistance = 0.0f;
			dir_.y *= -1.0f;
			dirFlag = true;
		}
	}
	// 位置更新
	pos_ = VAdd(pos_, movePow);
	if (crosshairFlag_ == false)
	{
		crosshairFlag_ = true;
		crosshairPos_.x += movePow.x * CROSSHAIR_MOVE_SCALE;
		crosshairPos_.y = 0.0f;
		crosshairPos_.z += movePow.z * CROSSHAIR_MOVE_SCALE;
	}
	// モデルスケール・回転・位置設定
	MV1SetScale(modelId_, scl_);
	MV1SetRotationXYZ(modelId_, rot_);
	MV1SetPosition(modelId_, pos_);
	MV1SetScale(crossHairId_, scl_);
	MV1SetRotationXYZ(crossHairId_, rot_);
	MV1SetPosition(crossHairId_, crosshairPos_);
}

void BombCannon::UpdateBlast(void)
{
	// 爆発時スケール増加
	if (blastCnt_ == 0)
	{
		scl_.x += BLAST_SCL_UP;
		scl_.y += BLAST_SCL_UP;
		scl_.z += BLAST_SCL_UP;
	}
	// 爆発時Y軸回転
	rot_.y += BLAST_ROT_Y;
	MV1SetScale(modelId_, scl_);
	MV1SetRotationXYZ(modelId_, rot_);
	MV1SetPosition(modelId_, pos_);
	if (scl_.x > BLAST_MAX_SCL)
	{
		blastCnt_++;
	}
	if (blastCnt_ >= BLAST_MAX_CNT)
	{
		ChangeState(STATE::END);
	}
}

void BombCannon::DrawShot(void)
{
	MV1SetDifColorScale(modelId_, weaponColor_[plNum_ - 1]);
	MV1SetSpcColorScale(modelId_, weaponColor_[plNum_ - 1]);

	MV1DrawModel(crossHairId_);
	MV1DrawModel(modelId_);
}

void BombCannon::DrawBlast(void)
{
	COLOR_F tmpCol = weaponColor_[plNum_ - 1];

	switch (plNum_)
	{
	case 1:
		tmpCol = GetColorF(0.8f, 0.3f, 0.2f, 1.0f);
		break;
	case 2:
		tmpCol = GetColorF(0.2f, 0.3f, 0.8f, 1.0f);
		break;
	}

	MV1SetDifColorScale(modelId_, tmpCol);
	MV1SetSpcColorScale(modelId_, tmpCol);
	MV1DrawModel(modelId_);
}

void BombCannon::Release(void)
{
	MV1DeleteModel(modelId_);
	MV1DeleteModel(crossHairId_);
}

bool BombCannon::IsShot(void)
{
	if (state_ == STATE::SHOT || state_ == STATE::BLAST)
	{
		return true;
	}

	return false;
	
}

