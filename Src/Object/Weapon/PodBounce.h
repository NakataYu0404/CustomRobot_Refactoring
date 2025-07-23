#pragma once
#include "WeaponBase.h"

class PodBounce : public WeaponBase
{
public:
    // PodBounce固有パラメータ定数
    static constexpr float SCALE = 0.15f;               // モデルスケール
    static constexpr float SPEED = 8.0f;                // 移動速度
    static constexpr int HP_DAMAGE = 56;                // HPダメージ
    static constexpr int SHOT_BLAST_MAX = 1200;         // ショット持続最大
    static constexpr int BOUNCE_MAX_CNT = 14;           // バウンド最大回数
    static constexpr float BOUNCE_Y_BORDER = 25.0f;     // バウンドY境界
    static constexpr float BLAST_DRAW_SCALE = 0.5f;     // 爆発描画スケール
    static constexpr float BLAST_DRAW_SIZE = 80.0f;     // 爆発描画サイズ
    static constexpr float BLAST_DRAW_ROT = 0.0f;       // 爆発描画回転

    void SetParam(void) override;

    void UpdateWeapon(void) override;
    void UpdateBlast(void) override;

    void DrawBlast(void) override;

    float GetRadius(void) override;

protected:
private:
    int bounceCnt_;         // バウンド回数
    void Bounce(void);      // バウンド処理
};
