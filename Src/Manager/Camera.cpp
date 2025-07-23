#include <DxLib.h>
#include "InputManager.h"
#include "Camera.h"

Camera::Camera()
{
    // カメラ初期化（必要ならここで初期値を設定）
}

Camera::~Camera()
{
    // カメラリソース解放
}

void Camera::Init()
{
    // カメラ位置・角度初期化
    pos_ = INIT_POS;
    angles_ = INIT_ANGLE;

    // サブライト生成
    light2_ = CreatePointLightHandle(pos_, SUBLIGHT_RANGE, SUBLIGHT_ATTEN.x, SUBLIGHT_ATTEN.y, SUBLIGHT_ATTEN.z);

    // カメラ自動回転初期化
    cameraHAngle_ = INIT_ANGLE_AUTO.x;
    cameraVAngle_ = INIT_ANGLE_AUTO.y;

    targetPos_ = { 0.0f,0.0f,0.0f };
    plDistance_ = { 0.0f,0.0f,0.0f };
    xRotCam_ = 0;
}

void Camera::Update()
{
    // サブライト位置更新
    SetLightPositionHandle(light2_, pos_);
}

void Camera::SetBeforeDraw()
{
    // カメラの描画範囲設定
    SetCameraNearFar(10.0f, 30000.0f);

    switch (mode_)
    {
    case Camera::MODE::NONE:
        break;
    case Camera::MODE::FIXED_POINT:
        SetBeforeDrawFixedPoint();
        SetCameraPositionAndAngle(pos_, angles_.x, angles_.y, angles_.z);
        break;
    case Camera::MODE::FREE:
        SetBeforeDrawFree();
        SetCameraPositionAndAngle(pos_, angles_.x, angles_.y, angles_.z);
        break;
    case Camera::MODE::AUTO:
        SetBeforeDrawAuto();
        break;
    default:
        break;
    }
}

void Camera::SetBeforeDrawFixedPoint()
{
    // 固定カメラ位置・角度設定
    pos_ = { 0.0f, FIXED_POINT_Y, FIXED_POINT_Z };
    angles_ = { FIXED_POINT_ANGLE_X, 0.0f, 0.0f };
}

void Camera::SetBeforeDrawFree()
{
    auto& ins = InputManager::GetInstance();

    // WASDキーでカメラ移動
    if (ins.IsNew(KEY_INPUT_W)) { pos_.z += CAMERA_MOVE_POWER; }
    if (ins.IsNew(KEY_INPUT_A)) { pos_.x -= CAMERA_MOVE_POWER; }
    if (ins.IsNew(KEY_INPUT_S)) { pos_.z -= CAMERA_MOVE_POWER; }
    if (ins.IsNew(KEY_INPUT_D)) { pos_.x += CAMERA_MOVE_POWER; }
    if (ins.IsNew(KEY_INPUT_Q)) { pos_.y += CAMERA_MOVE_POWER; }
    if (ins.IsNew(KEY_INPUT_E)) { pos_.y -= CAMERA_MOVE_POWER; }

    // IJKLキーでカメラ回転
    if (ins.IsNew(KEY_INPUT_I)) { angles_.x -= CAMERA_ROT_POWER; }
    if (ins.IsNew(KEY_INPUT_J)) { angles_.y -= CAMERA_ROT_POWER; }
    if (ins.IsNew(KEY_INPUT_K)) { angles_.x += CAMERA_ROT_POWER; }
    if (ins.IsNew(KEY_INPUT_L)) { angles_.y += CAMERA_ROT_POWER; }
}

void Camera::SetBeforeDrawAuto()
{
    // 自動回転カメラ処理
    cameraHAngle_ -= CAMERA_ANGLE_SPEED;
    if (cameraHAngle_ <= -180)
    {
        cameraHAngle_ += 360;
    }

    VECTOR tempPos;
    VECTOR tempPos2;

    // 垂直角度からY座標算出
    sinParam_ = sin(cameraVAngle_ / 180.0f * DX_PI_F);
    cosParam_ = cos(cameraVAngle_ / 180.0f * DX_PI_F);
    tempPos.x = 0.0f;
    if (plDisLen <= 700)
    {
        tempPos.y = sinParam_ * 700;
    }
    else if (plDisLen > 1000)
    {
        tempPos.y = sinParam_ * 1000 - xRotCam_;
        xRotCam_ = plDisLen - 1000.0f;
        if (xRotCam_ > 200)
        {
            xRotCam_ = 200;
        }
    }
    else
    {
        tempPos.y = sinParam_ * plDisLen;
    }
    tempPos.z = -cosParam_ * plDisLen;

    // 水平角度からX,Z座標算出
    sinParam_ = sin(cameraHAngle_ / 180.0f * DX_PI_F);
    cosParam_ = cos(cameraHAngle_ / 180.0f * DX_PI_F);
    tempPos2.x = cosParam_ * tempPos.x - sinParam_ * tempPos.z;
    tempPos2.y = tempPos.y + plDistance_.y;
    tempPos2.z = sinParam_ * tempPos.x + cosParam_ * tempPos.z;

    // ターゲット座標にオフセット加算
    pos_ = VAdd(tempPos2, targetPos_);

    // カメラ位置・ターゲット設定
    SetCameraPositionAndTarget_UpVecY(pos_, targetPos_);
}

void Camera::SetBeforeDrawTitle()
{
    // タイトル用カメラ位置・角度
    pos_ = { 0.0f,0.0f,0.0f };
    angles_ = { 0.5f,0.0f,0.0f };
}

void Camera::ChangeMode(MODE mode)
{
    // カメラモード変更
    mode_ = mode;
    // 必要ならモードごとの初期化処理
}

float Camera::GetHAngle()
{
    // カメラ水平角度取得
    return cameraHAngle_;
}

void Camera::SetHAngle(float angle)
{
    // カメラ水平角度設定
    cameraHAngle_ = angle;
}

void Camera::Draw()
{
    // カメラデバッグ描画（必要なら有効化）
    // DrawFormatString(0, 0, 0x000000, "WASDでX,Z移動、QEでY移動、IJKLでX,Y回転");
}

void Camera::Release()
{
    // サブライト解放
    DeleteLightHandle(light2_);
}

void Camera::SetTargetPos(VECTOR plPos1, VECTOR plPos2)
{
    // プレイヤー2点間の中心座標・距離を計算
    if (plPos1.x > plPos2.x)
    {
        plDistance_.x = plPos1.x - plPos2.x;
        targetPos_.x = plDistance_.x / 2 + plPos2.x;
    }
    else if (plPos2.x > plPos1.x)
    {
        plDistance_.x = plPos2.x - plPos1.x;
        targetPos_.x = plDistance_.x / 2 + plPos1.x;
    }
    else
    {
        plDistance_.x = 0;
        targetPos_.x = plDistance_.x / 2 + plPos1.x;
    }

    if (plPos1.y > plPos2.y)
    {
        plDistance_.y = plPos1.y - plPos2.y;
        targetPos_.y = plDistance_.y / 2 + plPos2.y;
    }
    else if (plPos2.y > plPos1.y)
    {
        plDistance_.y = plPos2.y - plPos1.y;
        targetPos_.y = plDistance_.y / 2 + plPos1.y;
    }
    else
    {
        plDistance_.y = 0;
        targetPos_.y = plDistance_.y / 2 + plPos1.y;
    }

    if (plPos1.z > plPos2.z)
    {
        plDistance_.z = plPos1.z - plPos2.z;
        targetPos_.z = plDistance_.z / 2 + plPos2.z;
    }
    else if (plPos2.z > plPos1.z)
    {
        plDistance_.z = plPos2.z - plPos1.z;
        targetPos_.z = plDistance_.z / 2 + plPos1.z;
    }
    else
    {
        plDistance_.z = 0;
        targetPos_.z = plDistance_.z / 2 + plPos1.z;
    }

    // プレイヤー中心座標の高さ補正
    targetPos_.y -= 100;

    // プレイヤー間距離の長さ計算
    plDisLen = sqrt(plDistance_.x * plDistance_.x + plDistance_.y * plDistance_.y + plDistance_.z * plDistance_.z);
    if (plDisLen <= 500)
    {
        plDisLen = 500;
    }
}
