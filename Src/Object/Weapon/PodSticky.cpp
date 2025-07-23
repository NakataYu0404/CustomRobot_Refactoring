#include <DxLib.h>
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "PodSticky.h"

void PodSticky::SetParam(void)
{
	//  モデル複製
	modelId_ = MV1DuplicateModel(baseModelId_);

	//  モデルスケール設定
	scl_ = { SCALE, SCALE, SCALE };

	//  回転初期化
	rot_ = { 0.0f,0.0f,0.0f };

	//  移動速度設定
	speed_ = SPEED;

	//  ダメージ設定
	hpDamage_ = HP_DAMAGE;
	stunDamage_ = hpDamage_;

	ShotBlastMax_ = SHOT_BLAST_MAX;
	ShotBlastCnt_ = 0;

	playerHit_ = false;
	stickFlag_ = false;
}

void PodSticky::UpdateWeapon(void)
{
	if (!stickFlag_)
	{

		//  地面と平行にしか移動しないためY方向を0に
		if (pos_.y > BOUNCE_Y_BORDER)
		{
			dir_.y = -1.0f;
		}
		else
		{
			dir_.y = 0.0f;
		}

		rot_.x += AsoUtility::Rad2DegF(AsoUtility::Deg2RadF(1.0f) - fabsf(dir_.z));
		rot_.z += AsoUtility::Rad2DegF(AsoUtility::Deg2RadF(1.0f) - fabsf(dir_.x));


		//  移動量の計算(方向*スピード)
		VECTOR movePow = VScale(dir_, speed_);

		//  移動処理(座標+移動量) 落下を考えていない
		pos_ = VAdd(pos_, movePow);
	}

	//  モデルのスケール、回転、位置を設定
	MV1SetScale(modelId_, scl_);
	MV1SetRotationXYZ(modelId_, rot_);
	MV1SetPosition(modelId_, pos_);
}

void PodSticky::UpdateBlast(void)
{

	//  モデルのスケール、回転、位置を設定
	MV1SetScale(modelId_, scl_);
	MV1SetRotationXYZ(modelId_, rot_);
	MV1SetPosition(modelId_, pos_);

	stickFlag_ = true;
	state_ = STATE::SHOT;
}

void PodSticky::DrawBlast(void)
{
	MV1SetDifColorScale(modelId_, weaponColor_[plNum_ - 1]);
	MV1SetSpcColorScale(modelId_, weaponColor_[plNum_ - 1]);

	MV1DrawModel(modelId_);
}

float PodSticky::GetRadius(void)
{
	VECTOR scale = { 0.0f,0.0f,0.0f };
	float radius = 0.0f;

	//  半径計算のためスケールを取得
	scale.x = scl_.x * RADIUS_SCALE;
	scale.y = scl_.y * RADIUS_SCALE;
	scale.z = scl_.z * RADIUS_SCALE;

	//  スケールの平均値を半径とする
	radius = (scale.x + scale.y + scale.z) / 3;
	return radius;
}

