#pragma once
#include "WeaponBase.h"

class BombMine : public WeaponBase
{
public:
	// ���ɂȂ�
	// �p�����[�^
	void SetParam(void) override;

	void UpdateWeapon(void) override;

	void UpdateBlast(void) override;
	void DrawShot(void) override;
	void DrawBlast(void) override;

	void Release(void) override;

protected:
	bool IsShot(void) override;

private:
	// ���̃u�L�ŗL�̏�������������ꍇ�͂���
	float moveDistance;

	int blastCnt_;

	int waitCnt_;
};

