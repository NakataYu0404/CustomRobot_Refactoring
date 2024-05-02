#pragma once
#include "WeaponBase.h"
class PodSticky : public WeaponBase
{
public:
	// 特にない
	// パラメータ
	void SetParam(void) override;

	// 処理
	void UpdateWeapon(void) override;
	void UpdateBlast(void) override;

	void DrawBlast(void) override;

	float GetRadius(void) override;

protected:
private:
	// このブキ固有の処理が発生する場合はここ
	bool stickFlag_;
};

