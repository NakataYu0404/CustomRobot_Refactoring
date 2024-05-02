#pragma once
#include "WeaponBase.h"

class BombCannon : public WeaponBase
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
	bool dirFlag;
	float moveDistance;

	int blastCnt_;

	bool crosshairFlag_;

	int crossHairId_;
	VECTOR crosshairPos_;
	VECTOR crosshairScl_;
	VECTOR crosshairRot_;
};

