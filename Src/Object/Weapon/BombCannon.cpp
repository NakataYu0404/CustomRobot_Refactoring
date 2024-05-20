#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/ResourceManager.h"
#include "BombCannon.h"


void BombCannon::SetParam(void)
{
	//  使用メモリ容量と読み込み時間削減のため
	//  モデルデータをいくつもメモリ上に存在させない
	modelId_ = MV1DuplicateModel(baseModelId_);

	//  弾の大きさを設定
	scl_ = { 0.8f,0.8f,0.8f };

	//  弾の角度を設定
	rot_ = { 0.0f,0.0f,0.0f };

	//  弾の速度
	speed_ = 8.0f;

	hpDamage_ = 30;
	stunDamage_ = hpDamage_;

	ShotBlastCnt_ = 0;

	moveDistance = 0.0f;

	dirFlag = false;

	ShotBlastMax_ = 600;
	blastCnt_ = 0;

	crossHairId_ = resMng_.LoadModelDuplicate(ResourceManager::SRC::MDL_CROSSHAIR);
	crosshairPos_ = enemyPos_;
	crosshairScl_ = { 0.8f,0.8f,0.8f };
	crosshairRot_ = { 0.0f,0.0f,0.0f };
	
	crosshairFlag_ = false;
}

void BombCannon::UpdateWeapon(void)
{
	//  ↓弾を移動させる
	//  移動量の計算(方向*スピード)
	VECTOR movePow = VScale(dir_, speed_);
	//  撃った時にジャンプしていたかどうかで処理を分ける
	if (!isJump_ && posFire_.y <= enemyPos_.y+0.5f)
	{
		//  移動距離を測る
		moveDistance += sqrt((movePow.x * movePow.x) + (movePow.z * movePow.z));
		if ((moveDistance >= (plEnDistance_ / 2.0f) + (fmodf(plEnDistance_, 2.0f))) && dirFlag == false)
		{
			//  弾の移動距離が敵と自分距離の半分以上になったら処理
			moveDistance = 0.0f;
			dir_.y *= -1.0f;
			dirFlag = true;
		}
	}
	//  移動処理(座標+移動量) 落下を考えていない
	pos_ = VAdd(pos_, movePow);
	if (crosshairFlag_ == false)
	{
		crosshairFlag_ = true;
		crosshairPos_.x += movePow.x*12.0f;
		crosshairPos_.y = 0.0f;
		crosshairPos_.z += movePow.z*12.0f;
	}
	////  加速度的に重力を加える
	//gravityPow_ += SceneManager::GRAVITY / SceneManager::DEFAULT_FPS;
	//pos_ = VAdd(pos_, VScale({ 0.0f,-1.0f,0.0f }, gravityPow_));

	//  大きさの設定
	MV1SetScale(modelId_, scl_);

	//  角度の設定
	MV1SetRotationXYZ(modelId_, rot_);

	//  位置の設定
	MV1SetPosition(modelId_, pos_);

	MV1SetScale(crossHairId_, scl_);
	MV1SetRotationXYZ(crossHairId_, rot_);
	MV1SetPosition(crossHairId_, crosshairPos_);
}

void BombCannon::UpdateBlast(void)
{
	float sclUp = 0.1f;
	if (blastCnt_ == 0)
	{
		//  特定の大きさ(10)まで段々でかくする
		scl_.x += sclUp;
		scl_.y += sclUp;
		scl_.z += sclUp;
	}
	//  演出の為に回転させる
	rot_.y+=0.05f;

	//  大きさの設定
	MV1SetScale(modelId_, scl_);

	//  角度の設定
	MV1SetRotationXYZ(modelId_, rot_);

	//  位置の設定
	MV1SetPosition(modelId_, pos_);

	if (scl_.x > 10.0)
	{
		//  特定の大きさより大きくなったら、持続カウンタを回す
		blastCnt_++;
	}
	if (blastCnt_ >= 60)
	{
		//  持続カウンタがいっぱいになったら消す
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

