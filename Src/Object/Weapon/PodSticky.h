#pragma once
#include "WeaponBase.h"
class PodSticky : public WeaponBase
{
public:
	// ���ɂȂ�
	// �p�����[�^
	void SetParam(void) override;

	// ����
	void UpdateWeapon(void) override;
	void UpdateBlast(void) override;

	void DrawBlast(void) override;

	float GetRadius(void) override;

protected:
private:
	// ���̃u�L�ŗL�̏�������������ꍇ�͂���
	bool stickFlag_;
};

