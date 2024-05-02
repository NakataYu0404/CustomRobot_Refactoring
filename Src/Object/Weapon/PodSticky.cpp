#include <DxLib.h>
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "PodSticky.h"

void PodSticky::SetParam(void)
{
	// 使用メモリ容量と読み込み時間削減のため
// モデルデータをいくつもメモリ上に存在させない
	modelId_ = MV1DuplicateModel(baseModelId_);

	// 弾の大きさを設定
	scl_ = { 0.4f,0.4f,0.4f };

	// 弾の角度を設定
	rot_ = { 0.0f,0.0f,0.0f };

	// 弾の速度
	speed_ = 8.0f;

	hpDamage_ = 50;
	stunDamage_ = hpDamage_;

	ShotBlastMax_ = 0;
	ShotBlastCnt_ = 0;


	playerHit_ = false;
	stickFlag_ = false;
}

void PodSticky::UpdateWeapon(void)
{
	if (!stickFlag_)
	{

		// 地面と平行にしか移動しないためY方向を0に
		if (pos_.y > 25.0f)
		{
			dir_.y = -1.0f;
		}
		else
		{
			dir_.y = 0.0f;
		}

		rot_.x += AsoUtility::Rad2DegF(AsoUtility::Deg2RadF(1.0f) - fabsf(dir_.z));
		rot_.z += AsoUtility::Rad2DegF(AsoUtility::Deg2RadF(1.0f) - fabsf(dir_.x));


		// 移動量の計算(方向*スピード)
		VECTOR movePow = VScale(dir_, speed_);

		// 移動処理(座標+移動量) 落下を考えていない
		pos_ = VAdd(pos_, movePow);
	}
	// 大きさの設定
	MV1SetScale(modelId_, scl_);

	// 角度の設定
	MV1SetRotationXYZ(modelId_, rot_);

	// 位置の設定
	MV1SetPosition(modelId_, pos_);
}

void PodSticky::UpdateBlast(void)
{

	// 大きさの設定
	MV1SetScale(modelId_, scl_);

	// 角度の設定
	MV1SetRotationXYZ(modelId_, rot_);

	// 位置の設定
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
	scale.x = scl_.x * 100.0f;
	scale.y = scl_.y * 100.0f;
	scale.z = scl_.z * 100.0f;
	radius = (scale.x + scale.y + scale.z) / 3;
	return radius;
}

