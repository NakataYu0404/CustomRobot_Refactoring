#include "../../Manager/SceneManager.h"
#include "WeaponBase.h"

WeaponBase::WeaponBase(void)
{
}

WeaponBase::~WeaponBase(void)
{
}

void WeaponBase::CreateWeapon(VECTOR pos, VECTOR dir,int plNum)
{
	//  弾の発射位置を設定
	pos_ = pos;
	posFire_ = pos;
	posFire_.y -= 50.0f;

	//  弾の発射方向の設定
	dir_ = dir;

	//  重力加速度
	gravityPow_ = 0.0f;

	//  爆発のアニメーション用カウンタ
	blastCntAnim_ = 0;
	
	//  爆発のアニメーション速度
	blastSpeedAnim_ = 0.3f;

	movePow_ = { 0.0f,0.0f,0.0f };

	SetParam();

	plNum_ = plNum;

	//  状態遷移
	ChangeState(STATE::SHOT);
}

void WeaponBase::Init(void)
{
	weaponColor_[0] = GetColorF(1.0f, 0.1f, 0.1f, 1.0f);
	weaponColor_[1] = GetColorF(0.1, 0.1f, 1.0f, 1.0f);
}

void WeaponBase::SetInitial(int baseModelId, int* blastImgs, int blastAnimNum)
{
	baseModelId_ = baseModelId;
	blastImgs_ = blastImgs;
	blastAnimNum_ = blastAnimNum;
}

void WeaponBase::SetParam(void)
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

	hpDamage_ = 100;
	stunDamage_ = hpDamage_;

	ShotBlastMax_ = 600;
	ShotBlastCnt_ = 0;

	plEnDistance_ = 0;


}

void WeaponBase::Update(void)
{
	if (!IsAlive())
	{
		//  生存していなければ処理中断
		return;
	}

	switch (state_)
	{
	case WeaponBase::STATE::NONE:
		break;
	case WeaponBase::STATE::SHOT:
	UpdateWeapon();
	ShotBlastCnt_++;
	if (ShotBlastCnt_ > ShotBlastMax_ && ShotBlastMax_ != 0)
	{
		ChangeState(STATE::BLAST);
		ShotBlastCnt_ = 0;
	}
		break;
	case WeaponBase::STATE::BLAST:
	UpdateBlast();
		break;
	case WeaponBase::STATE::END:
	UpdateEnd();
		break;
	default:
		break;
	}
}

void WeaponBase::UpdateWeapon(void)
{
	//  ↓弾を移動させる
	//  移動量の計算(方向*スピード)
	movePow_ = VScale(dir_, speed_);

	//  敵の位置と自分の位置をそれぞれの成分比較して、
	//  敵の方向にdirが調整されていくようにする→ショットそれぞれにホーミングパワーを作って、dir+=ホーミングパワーとか？
	
	//  大きさの設定
	MV1SetScale(modelId_, scl_);

	//  角度の設定
	MV1SetRotationXYZ(modelId_, rot_);

	//  位置の設定
	MV1SetPosition(modelId_, pos_);
}

void WeaponBase::UpdateBlast(void)
{
	//  アニメーション処理
	blastIdxAnim_++;
	//  アニメーションが終了したら、STATEをENDへ

	//  爆発アニメーションの終了判定
	if (blastIdxAnim_ + 1 >= blastAnimNum_)
	{
		blastIdxAnim_ = 0;
		ChangeState(STATE::END);
	}
}

void WeaponBase::UpdateEnd(void)
{
	//  何もしない 終わるための関数なのでこれを抜けた後にも処理を置かない
}

void WeaponBase::Draw(void)
{
	if (!IsAlive())
	{
		//  生存していなければ処理中断
		return;
	}

	switch (state_)
	{
	case WeaponBase::STATE::NONE:
		break;
	case WeaponBase::STATE::SHOT:
	DrawShot();
		break;
	case WeaponBase::STATE::BLAST:
	DrawBlast();
		break;
	case WeaponBase::STATE::END:
	DrawEnd();
		break;
	default:
		break;
	}

}

void WeaponBase::DrawShot(void)
{
	MV1SetDifColorScale(modelId_, weaponColor_[plNum_-1]);
	MV1SetSpcColorScale(modelId_, weaponColor_[plNum_-1]);

	MV1DrawModel(modelId_);
}

void WeaponBase::DrawBlast(void)
{
	DrawBillboard3D(pos_, 0.5f, 0.5f, 80.0f, 0.0f, blastImgs_[blastIdxAnim_], true);
}

void WeaponBase::DrawEnd(void)
{
	//  特に何もしない　このあとに処理を置かない
}

void WeaponBase::Release(void)
{
	MV1DeleteModel(modelId_);
	for (int i = 0; i < blastAnimNum_; i++)
	{
		DeleteGraph(blastImgs_[i]);
	}
}

bool WeaponBase::IsShot(void)
{
	if (state_ == STATE::SHOT)
	{
		return true;
	}

	return false;
}

bool WeaponBase::IsAlive(void)
{
	if (state_ != STATE::END)
	{
		return true;
	}
	return false;
}

void WeaponBase::Blast(void)
{
	state_ = STATE::BLAST;
}

void WeaponBase::End(void)
{
	state_ = STATE::END;
}

VECTOR WeaponBase::GetPos(void)
{
	return pos_;
}

VECTOR WeaponBase::GetMovePow(void)
{
	return movePow_;
}

WeaponBase::STATE WeaponBase::GetState(void)
{
	return state_;
}

void WeaponBase::SetPos(VECTOR pos)
{
	pos_ = pos;
	//  位置の設定
	MV1SetPosition(modelId_, pos_);
}

int WeaponBase::GetHpDamage(void)
{
	return hpDamage_;
}

int WeaponBase::GetStunDamage(void)
{
	return stunDamage_;
}

void WeaponBase::SetDistance(float distance)
{
	plEnDistance_ = distance;
}

float WeaponBase::GetRadius(void)
{
	VECTOR scale = {0.0f,0.0f,0.0f};
	float radius = 0.0f;
	scale.x = scl_.x * 10.0f;
	scale.y = scl_.y * 10.0f;
	scale.z = scl_.z * 10.0f;
	radius = (scale.x + scale.y + scale.z) / 3;
	return radius;
}

VECTOR WeaponBase::GetDir(void)
{
	return dir_;
}

void WeaponBase::SetEnemyPos(VECTOR pos)
{
	enemyPos_ = pos;
}

//  ステージに衝突した部分の法線を取得する
void WeaponBase::SetNormal(VECTOR normal)
{
	hitNormal_ = normal;
}

void WeaponBase::PlayerHit(bool isHit)
{
	playerHit_ = isHit;
}

void WeaponBase::SetRot(VECTOR rot)
{
	rot_ = rot;
}

void WeaponBase::SetColor(int plNum)
{
}

void WeaponBase::ChangeState(STATE state)
{
	state_ = state;
}
