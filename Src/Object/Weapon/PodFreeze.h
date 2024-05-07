#pragma once
#include "WeaponBase.h"

class PodFreeze : public WeaponBase
{
public:
	//  特にない
	//  パラメータ
	void SetParam(void) override;

	//  処理
	void UpdateWeapon(void) override;
	void UpdateBlast(void) override;

	void DrawBlast(void) override;

protected:
	bool IsShot(void) override;

private:
	//  このブキ固有の処理が発生する場合はここ
	int blastCnt_;
	float moveDistance;

};
