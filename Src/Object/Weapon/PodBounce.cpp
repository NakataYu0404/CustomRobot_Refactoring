#include <DxLib.h>
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "PodBounce.h"

void PodBounce::SetParam(void)
{
	// 使用メモリ容量と読み込み時間削減のため
// モデルデータをいくつもメモリ上に存在させない
	modelId_ = MV1DuplicateModel(baseModelId_);

	// 弾の大きさを設定
	scl_ = { 0.15f,0.15f,0.15f };

	// 弾の角度を設定
	rot_ = { 0.0f,0.0f,0.0f };

	// 弾の速度
	speed_ = 8.0f;

	hpDamage_ = 56;
	stunDamage_ = hpDamage_;

	ShotBlastMax_ = 1200;
	ShotBlastCnt_ = 0;

	bounceCnt_ = 14;

	playerHit_ = false;
}

void PodBounce::UpdateWeapon(void)
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

	// 大きさの設定
	MV1SetScale(modelId_, scl_);

	// 角度の設定
	MV1SetRotationXYZ(modelId_, rot_);

	// 位置の設定
	MV1SetPosition(modelId_, pos_);
}

void PodBounce::UpdateBlast(void)
{

	if (bounceCnt_ > 0 && playerHit_ == false)
	{
		Bounce();
		ChangeState(STATE::SHOT);
	}
	else
	{
		bounceCnt_ = 0;
		// アニメーション処理
		blastIdxAnim_++;
		// アニメーションが終了したら、STATEをENDへ

		// 爆発アニメーションの終了判定
		if (blastIdxAnim_ + 1 >= blastAnimNum_)
		{
			blastIdxAnim_ = 0;
			ChangeState(STATE::END);
		}
	}
}

void PodBounce::DrawBlast(void)
{
	if (bounceCnt_ <= 0)
	{
		DrawBillboard3D(pos_, 0.5f, 0.5f, 80.0f, 0.0f, blastImgs_[blastIdxAnim_], true);
	}
	else
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

		MV1DrawModel(modelId_);
	}
}

float PodBounce::GetRadius(void)
{
	VECTOR scale = { 0.0f,0.0f,0.0f };
	float radius = 0.0f;
	scale.x = scl_.x * 100.0f;
	scale.y = scl_.y * 100.0f;
	scale.z = scl_.z * 100.0f;
	radius = (scale.x + scale.y + scale.z) / 3;
	return radius;
}

void PodBounce::Bounce(void)
{
	if (fabsf(hitNormal_.x) > fabsf(hitNormal_.z))
	{
		if ((hitNormal_.x > 0.0f && dir_.x > 0.0f)||(hitNormal_.x < 0.0f && dir_.x < 0.0f))
		{
			dir_.x = hitNormal_.x;
		}
		else
		{
			dir_.x *= -1.0f;
			rot_.x *= AsoUtility::Deg2RadF(-1.0f);
		}
	}
	else if (fabsf(hitNormal_.x) < fabsf(hitNormal_.z))
	{
		if ((hitNormal_.z > 0.0f && dir_.z > 0.0f) || (hitNormal_.z < 0.0f && dir_.z < 0.0f))
		{
			dir_.z = hitNormal_.z;
		}
		else
		{
			dir_.z *= -1.0f;
			rot_.z *= AsoUtility::Deg2RadF(-1.0f);
		}
	}
	else
	{
		dir_.x *= -1;
		dir_.z *= -1;
	}
	bounceCnt_--;
}

