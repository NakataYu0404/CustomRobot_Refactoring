#pragma once
#include "WeaponBase.h"

class BombMine : public WeaponBase
{
public:
	// 特にない
	// パラメータ
	void SetParam(void) override;

	void UpdateWeapon(void) override;

	void UpdateBlast(void) override;
	void DrawShot(void) override;
	void DrawBlast(void) override;

	void Release(void) override;

protected:
	bool IsShot(void) override;

private:
	// このブキ固有の処理が発生する場合はここ
	float moveDistance;

	int blastCnt_;

	int waitCnt_;
};

