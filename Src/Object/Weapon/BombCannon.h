#pragma once
#include "WeaponBase.h"

class BombCannon : public WeaponBase
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
	bool dirFlag;
	float moveDistance;

	int blastCnt_;

	bool crosshairFlag_;

	int crossHairId_;
	VECTOR crosshairPos_;
	VECTOR crosshairScl_;
	VECTOR crosshairRot_;
};

