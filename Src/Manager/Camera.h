#pragma once
#include "../Utility/AsoUtility.h"

class Camera
{
public:
	// カメラの回転速度（ラジアン/フレーム）
	static constexpr float CAMERA_ANGLE_SPEED = 0.05f;
	// カメラの注視点高さ
	static constexpr float CAMERA_LOOK_AT_HEIGHT = 400.0f;
	// カメラの注視点距離
	static constexpr float CAMERA_LOOK_AT_DISTANCE = 2150.0f;
	// カメラの初期位置
	static constexpr VECTOR INIT_POS = { 0.0f,540.0f,-690.0f };
	// サブライトの有効範囲
	static constexpr float SUBLIGHT_RANGE = 80000.0f;
	// サブライト減衰係数
	static constexpr VECTOR SUBLIGHT_ATTEN = { 0.0f,0.0015f,0.0f };
	// カメラの初期角度
	static constexpr VECTOR INIT_ANGLE = { 40.0f * 3.14f / 180.0f,0.0f,0.0f };
	// カメラの自動回転初期角度
	static constexpr VECTOR INIT_ANGLE_AUTO = { 360.0f ,40.0f ,0.0f };

	// --- マジックナンバー定数化 ---
	static constexpr float CAMERA_MOVE_POWER = 3.0f; // WASD移動時の移動量
	static constexpr float CAMERA_ROT_POWER = 1.0f * DX_PI_F / 180.0f; // IJKL回転時の回転量
	static constexpr float FIXED_POINT_Y = 98.0f; // 固定カメラY座標
	static constexpr float FIXED_POINT_Z = -80.0f; // 固定カメラZ座標
	static constexpr float FIXED_POINT_ANGLE_X = 0.5f; // 固定カメラX軸角度

	// カメラモード
	enum class MODE
	{
		NONE,           // 無効
		FIXED_POINT,    // 固定カメラ
		FREE,           // フリーカメラ
		AUTO,           // 自動カメラ
		TITLE           // タイトル用カメラ
	};

	// コンストラクタ
	Camera(void);
	// デストラクタ
	~Camera();

	// 初期化
	void Init(void);

	// 更新
	void Update(void);

	// 描画前設定
	void SetBeforeDraw(void);
	void SetBeforeDrawFixedPoint(void);
	void SetBeforeDrawFree(void);
	void SetBeforeDrawAuto(void);
	void SetBeforeDrawTitle(void);

	// 描画
	void Draw(void);

	// 解放
	void Release(void);

	// プレイヤー位置からターゲット座標を設定
	void SetTargetPos(VECTOR plPos1, VECTOR plPos2);

	// カメラモード変更
	void ChangeMode(MODE mode);

	// 水平角度取得・設定
	float GetHAngle(void);
	void SetHAngle(float angle);

private:
	MODE mode_;         // カメラモード

	VECTOR pos_;        // カメラ位置
	VECTOR angles_;     // カメラ角度

	int cLight_;        // メインライトハンドル
	int light2_;        // サブライトハンドル

	VECTOR targetPos_;  // ターゲット座標
	VECTOR plDistance_; // プレイヤー間距離
	float plDisLen;     // プレイヤー間距離の長さ

	float cameraHAngle_; // カメラ水平角度
	float cameraVAngle_; // カメラ垂直角度
	float sinParam_;     // サイン計算用
	float cosParam_;     // コサイン計算用

	int xRotCam_;        // X軸回転補正
};

