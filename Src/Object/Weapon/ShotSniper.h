#pragma once
#include "WeaponBase.h"

class ShotSniper :public WeaponBase
{
public:
	// 特にない
	// パラメータ
	void SetParam(void) override;

	// 処理
	void UpdateWeapon(void) override;



protected:
private:
	// このブキ固有の処理が発生する場合はここ

};

