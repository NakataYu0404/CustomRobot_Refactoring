#include <DxLib.h>
#include "../../Manager/SceneManager.h"
#include "PodFreeze.h"

void PodFreeze::SetParam(void)
{
    // モデル複製
    modelId_ = MV1DuplicateModel(baseModelId_);

    // モデルスケール設定
    scl_ = { SCALE, SCALE, SCALE };

    // 回転初期化
    rot_ = { 0.0f,0.0f,0.0f };

    // 移動速度設定
    speed_ = SPEED;

    // ダメージ設定
    hpDamage_ = HP_DAMAGE;
    stunDamage_ = STUN_DAMAGE;

    ShotBlastCnt_ = 0;
    moveDistance = 0.0f;
    ShotBlastMax_ = SHOT_BLAST_MAX;
    blastCnt_ = 0;
}

void PodFreeze::UpdateWeapon(void)
{
    // Y座標が境界より小さい場合は上向き、そうでなければ水平
    if (pos_.y < Y_BORDER)
    {
        dir_.y = 1.0f;
    }
    else
    {
        dir_.y = 0.0f;
    }
    VECTOR movePow = VScale(dir_, speed_);
    moveDistance += sqrtf((movePow.x * movePow.x) + (movePow.z * movePow.z));
    if (moveDistance >= plEnDistance_)
    {
        ChangeState(STATE::BLAST);
    }
    pos_ = VAdd(pos_, movePow);
    MV1SetScale(modelId_, scl_);
    MV1SetRotationXYZ(modelId_, rot_);
    MV1SetPosition(modelId_, pos_);
}

void PodFreeze::UpdateBlast(void)
{
    scl_ = { BLAST_SCL, BLAST_SCL, BLAST_SCL };
    rot_.y += BLAST_ROT_Y;
    MV1SetScale(modelId_, scl_);
    MV1SetRotationXYZ(modelId_, rot_);
    MV1SetPosition(modelId_, pos_);
    blastCnt_++;
    if (blastCnt_ >= BLAST_MAX_CNT)
    {
        ChangeState(STATE::END);
    }
}

void PodFreeze::DrawBlast(void)
{
    COLOR_F tmpCol = weaponColor_[plNum_ - 1];
    switch (plNum_)
    {
    case 1:
        tmpCol = GetColorF(0.8f, 0.3f, 0.2f, 1.0f);
        break;
    case 2:
        tmpCol = GetColorF(0.2f, 0.3f, 0.8f, 1.0f);
        break;
    }
    MV1SetDifColorScale(modelId_, tmpCol);
    MV1SetSpcColorScale(modelId_, tmpCol);
    MV1DrawModel(modelId_);
}

bool PodFreeze::IsShot(void)
{
    if (state_ == STATE::SHOT || state_ == STATE::BLAST)
    {
        return true;
    }
    return false;
}
