#pragma once
#include <DxLib.h>

class WeaponBase
{
public:

	// �Փ˔���p�̋��̔��a
	static constexpr float COL_RADIUS = 8.0f;

	// �e�̏��
	enum class STATE
	{
		NONE,
		SHOT,
		BLAST,
		END
	};

	// �R���X�g���N�^
	WeaponBase(void);

	// �f�X�g���N�^
	virtual ~WeaponBase(void);

	// �e�̐��� Init����
	void CreateWeapon(VECTOR pos, VECTOR dir,int plNum);

	void Init(int baseModelId, int* blastImgs, int blastAnimNum);

	// �X�V�X�e�b�v
	void Update(void);

	// �`��
	void Draw(void);

	// �������
	virtual void Release(void);

	// �e����
	virtual bool IsShot(void);

	// ��������
	bool IsAlive(void);

	// ��������
	void Blast(void);
	void End(void);

	// �Q�b�^�[
	// �ʒu
	VECTOR GetPos(void);
	// �ړ�����*1�t���[���̈ړ�����
	VECTOR GetMovePow(void);
	// �X�e�[�^�X
	STATE GetState(void);
	// �^�_���[�W
	int GetHpDamage(void);
	int GetStunDamage(void);
	// �e�̔��a(�����锻���)
	virtual float GetRadius(void);
	// ����
	VECTOR GetDir(void);

	// �Z�b�^�[
	// �ʒu
	void SetPos(VECTOR pos);
	// �G�Ƃ̋���
	void SetDistance(float distance);
	// �G�̈ʒu
	void SetEnemyPos(VECTOR pos);
	// ���������n�`�̖@���x�N�g��
	void SetNormal(VECTOR normal);
	// �v���C���[�ɓ�����������ݒ�
	void PlayerHit(bool isHit);
	// �p�x
	void SetRot(VECTOR rot);

	void SetColor(int plNum);
protected:

	// �e�̑傫��
	VECTOR scl_;

	// �e�̈ړ����x
	float speed_;

	float gravityPow_;

	// �e�̏��
	STATE state_;

	// ���ƂȂ�e�̃��f��ID
	int baseModelId_;

	// �e�̃��f��ID
	int modelId_;

	// ����
	VECTOR dir_;

	// �e�̊p�x
	VECTOR rot_;

	// �e�̍��W
	VECTOR pos_;
	VECTOR movePow_;

	// ���ˎ��_�̍��W
	VECTOR posFire_;

	VECTOR enemyPos_;

	int hpDamage_;
	int stunDamage_;

	// �����A�j���[�V�����摜�z��̃|�C���^
	int* blastImgs_;

	// �����A�j���[�V������
	int blastAnimNum_;

	// �����̃A�j���[�V�����p�J�E���^
	int blastCntAnim_;

	// �����̃A�j���[�V�����ԍ�
	int blastIdxAnim_;

	// �����̃A�j���[�V�������x
	float blastSpeedAnim_;

	// ���ɂ������炸�ɔ�ё������Ƃ��̌��E�t���[��
	int ShotBlastMax_;
	int ShotBlastCnt_;

	float plEnDistance_;

	bool isJump_;

	VECTOR hitNormal_;

	bool playerHit_;

	virtual void SetParam(void);
	virtual	void UpdateWeapon(void);
	virtual void UpdateBlast(void);
	void UpdateEnd(void);

	virtual void DrawShot(void);
	virtual void DrawBlast(void);
	void DrawEnd(void);

	// ��ԑJ��
	void ChangeState(STATE state);

	COLOR_F weaponColor_[2];

	int plNum_;
private:

};

