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
	//  �e�̔��ˈʒu��ݒ�
	pos_ = pos;
	posFire_ = pos;
	posFire_.y -= 50.0f;

	//  �e�̔��˕����̐ݒ�
	dir_ = dir;

	//  �d�͉����x
	gravityPow_ = 0.0f;

	//  �����̃A�j���[�V�����p�J�E���^
	blastCntAnim_ = 0;
	
	//  �����̃A�j���[�V�������x
	blastSpeedAnim_ = 0.3f;

	movePow_ = { 0.0f,0.0f,0.0f };

	SetParam();

	plNum_ = plNum;

	//  ��ԑJ��
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
	//  �g�p�������e�ʂƓǂݍ��ݎ��ԍ팸�̂���
	//  ���f���f�[�^����������������ɑ��݂����Ȃ�
	modelId_ = MV1DuplicateModel(baseModelId_);

	//  �e�̑傫����ݒ�
	scl_ = { 0.8f,0.8f,0.8f };

	//  �e�̊p�x��ݒ�
	rot_ = { 0.0f,0.0f,0.0f };

	//  �e�̑��x
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
		//  �������Ă��Ȃ���Ώ������f
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
	//  ���e���ړ�������
	//  �ړ��ʂ̌v�Z(����*�X�s�[�h)
	movePow_ = VScale(dir_, speed_);

	//  �G�̈ʒu�Ǝ����̈ʒu�����ꂼ��̐�����r���āA
	//  �G�̕�����dir����������Ă����悤�ɂ��遨�V���b�g���ꂼ��Ƀz�[�~���O�p���[������āAdir+=�z�[�~���O�p���[�Ƃ��H
	
	//  �傫���̐ݒ�
	MV1SetScale(modelId_, scl_);

	//  �p�x�̐ݒ�
	MV1SetRotationXYZ(modelId_, rot_);

	//  �ʒu�̐ݒ�
	MV1SetPosition(modelId_, pos_);
}

void WeaponBase::UpdateBlast(void)
{
	//  �A�j���[�V��������
	blastIdxAnim_++;
	//  �A�j���[�V�������I��������ASTATE��END��

	//  �����A�j���[�V�����̏I������
	if (blastIdxAnim_ + 1 >= blastAnimNum_)
	{
		blastIdxAnim_ = 0;
		ChangeState(STATE::END);
	}
}

void WeaponBase::UpdateEnd(void)
{
	//  �������Ȃ� �I��邽�߂̊֐��Ȃ̂ł���𔲂�����ɂ�������u���Ȃ�
}

void WeaponBase::Draw(void)
{
	if (!IsAlive())
	{
		//  �������Ă��Ȃ���Ώ������f
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
	//  ���ɉ������Ȃ��@���̂��Ƃɏ�����u���Ȃ�
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
	//  �ʒu�̐ݒ�
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

//  �X�e�[�W�ɏՓ˂��������̖@�����擾����
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
