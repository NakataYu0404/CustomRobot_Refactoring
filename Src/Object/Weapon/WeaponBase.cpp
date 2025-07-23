#include "../../Manager/SceneManager.h"
#include "../../Manager/ResourceManager.h"
#include "WeaponBase.h"

WeaponBase::WeaponBase(void) : resMng_(ResourceManager::GetInstance())
{
}

WeaponBase::~WeaponBase(void)
{
}

void WeaponBase::CreateWeapon(VECTOR pos, VECTOR dir,int plNum)
{
    // 武器の発射位置設定
    pos_ = pos;
    posFire_ = pos;
    posFire_.y -= DEFAULT_FIRE_Y_OFFSET;

    // 武器の進行方向設定
    dir_ = dir;

    // 重力加速度初期化
    gravityPow_ = 0.0f;

    // 爆発アニメカウンタ初期化
    blastCntAnim_ = 0;
    // 爆発アニメ速度初期化
    blastSpeedAnim_ = DEFAULT_BLAST_SPEED_ANIM;

    movePow_ = { 0.0f,0.0f,0.0f };

    SetParam();

    plNum_ = plNum;

    // 状態変更: SHOT
    ChangeState(STATE::SHOT);
}

void WeaponBase::Init(void)
{
    // 武器色初期化
    weaponColor_[0] = GetColorF(1.0f, 0.1f, 0.1f, 1.0f);
    weaponColor_[1] = GetColorF(0.1f, 0.1f, 1.0f, 1.0f);
}

void WeaponBase::SetInitial(int baseModelId, int* blastImgs, int blastAnimNum)
{
    baseModelId_ = baseModelId;
    blastImgs_ = blastImgs;
    blastAnimNum_ = blastAnimNum;
}

void WeaponBase::SetParam(void)
{
    // モデル複製
    modelId_ = MV1DuplicateModel(baseModelId_);

    // 武器のスケール設定
    scl_ = { DEFAULT_SCALE, DEFAULT_SCALE, DEFAULT_SCALE };

    // 武器の回転初期化
    rot_ = { 0.0f,0.0f,0.0f };

    // 武器の速度設定
    speed_ = DEFAULT_SPEED;

    // ダメージ設定
    hpDamage_ = DEFAULT_HP_DAMAGE;
    stunDamage_ = DEFAULT_STUN_DAMAGE;

    // ショット持続最大設定
    ShotBlastMax_ = DEFAULT_SHOT_BLAST_MAX;
    ShotBlastCnt_ = 0;

    plEnDistance_ = 0;
}

void WeaponBase::Update(void)
{
    if (!IsAlive())
    {
        // 生存していない場合は処理しない
        return;
    }

    switch (state_)
    {
    case WeaponBase::STATE::NONE:
        break;
    case WeaponBase::STATE::SHOT:
        UpdateWeapon();
        ShotBlastCnt_++;
        if (ShotBlastCnt_ > ShotBlastMax_ && ShotBlastMax_ != 0)
        {
            ChangeState(STATE::BLAST);
            ShotBlastCnt_ = 0;
        }
        break;
    case WeaponBase::STATE::BLAST:
        UpdateBlast();
        break;
    case WeaponBase::STATE::END:
        UpdateEnd();
        break;
    default:
        break;
    }
}

void WeaponBase::UpdateWeapon(void)
{
    // 武器の移動量計算（進行方向×速度）
    movePow_ = VScale(dir_, speed_);

    // モデルのスケール・回転・位置設定
    MV1SetScale(modelId_, scl_);
    MV1SetRotationXYZ(modelId_, rot_);
    MV1SetPosition(modelId_, pos_);
}

void WeaponBase::UpdateBlast(void)
{
    // 爆発アニメインデックス更新
    blastIdxAnim_++;
    // 爆発アニメ終了判定
    if (blastIdxAnim_ + 1 >= blastAnimNum_)
    {
        blastIdxAnim_ = 0;
        ChangeState(STATE::END);
    }
}

void WeaponBase::UpdateEnd(void)
{
    // 終了状態（特に処理なし）
}

void WeaponBase::Draw(void)
{
    if (!IsAlive())
    {
        // 生存していない場合は描画しない
        return;
    }

    switch (state_)
    {
    case WeaponBase::STATE::NONE:
        break;
    case WeaponBase::STATE::SHOT:
        DrawShot();
        break;
    case WeaponBase::STATE::BLAST:
        DrawBlast();
        break;
    case WeaponBase::STATE::END:
        DrawEnd();
        break;
    default:
        break;
    }
}

void WeaponBase::DrawShot(void)
{
    // 武器色設定
    MV1SetDifColorScale(modelId_, weaponColor_[plNum_-1]);
    MV1SetSpcColorScale(modelId_, weaponColor_[plNum_-1]);
    MV1DrawModel(modelId_);
}

void WeaponBase::DrawBlast(void)
{
    // 爆発描画
    DrawBillboard3D(pos_, DEFAULT_BLAST_DRAW_SCALE_X, DEFAULT_BLAST_DRAW_SCALE_Y, DEFAULT_BLAST_DRAW_SIZE, DEFAULT_BLAST_DRAW_ROT, blastImgs_[blastIdxAnim_], true);
}

void WeaponBase::DrawEnd(void)
{
    // 終了状態（特に描画なし）
}

void WeaponBase::Release(void)
{
    MV1DeleteModel(modelId_);
    for (int i = 0; i < blastAnimNum_; i++)
    {
        DeleteGraph(blastImgs_[i]);
    }
}

bool WeaponBase::IsShot(void)
{
    if (state_ == STATE::SHOT)
    {
        return true;
    }
    return false;
}

bool WeaponBase::IsAlive(void)
{
    if (state_ != STATE::END)
    {
        return true;
    }
    return false;
}

void WeaponBase::Blast(void)
{
    state_ = STATE::BLAST;
}

void WeaponBase::End(void)
{
    state_ = STATE::END;
}

VECTOR WeaponBase::GetPos(void)
{
    return pos_;
}

VECTOR WeaponBase::GetMovePow(void)
{
    return movePow_;
}

WeaponBase::STATE WeaponBase::GetState(void)
{
    return state_;
}

void WeaponBase::SetPos(VECTOR pos)
{
    pos_ = pos;
    MV1SetPosition(modelId_, pos_);
}

int WeaponBase::GetHpDamage(void)
{
    return hpDamage_;
}

int WeaponBase::GetStunDamage(void)
{
    return stunDamage_;
}

void WeaponBase::SetDistance(float distance)
{
    plEnDistance_ = distance;
}

float WeaponBase::GetRadius(void)
{
    VECTOR scale = {0.0f,0.0f,0.0f};
    float radius = 0.0f;
    scale.x = scl_.x * 10.0f;
    scale.y = scl_.y * 10.0f;
    scale.z = scl_.z * 10.0f;
    radius = (scale.x + scale.y + scale.z) / 3;
    return radius;
}

VECTOR WeaponBase::GetDir(void)
{
    return dir_;
}

void WeaponBase::SetEnemyPos(VECTOR pos)
{
    enemyPos_ = pos;
}

void WeaponBase::SetNormal(VECTOR normal)
{
    hitNormal_ = normal;
}

void WeaponBase::PlayerHit(bool isHit)
{
    playerHit_ = isHit;
}

void WeaponBase::SetRot(VECTOR rot)
{
    rot_ = rot;
}

void WeaponBase::SetColor(int plNum)
{
}

void WeaponBase::ChangeState(STATE state)
{
    state_ = state;
}
