#pragma once
#include "WeaponBase.h"

class ShotSniper :public WeaponBase
{
public:
	// ���ɂȂ�
	// �p�����[�^
	void SetParam(void) override;

	// ����
	void UpdateWeapon(void) override;



protected:
private:
	// ���̃u�L�ŗL�̏�������������ꍇ�͂���

};

