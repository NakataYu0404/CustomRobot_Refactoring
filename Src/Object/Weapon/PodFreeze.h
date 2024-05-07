#pragma once
#include "WeaponBase.h"

class PodFreeze : public WeaponBase
{
public:
	//  ���ɂȂ�
	//  �p�����[�^
	void SetParam(void) override;

	//  ����
	void UpdateWeapon(void) override;
	void UpdateBlast(void) override;

	void DrawBlast(void) override;

protected:
	bool IsShot(void) override;

private:
	//  ���̃u�L�ŗL�̏�������������ꍇ�͂���
	int blastCnt_;
	float moveDistance;

};
