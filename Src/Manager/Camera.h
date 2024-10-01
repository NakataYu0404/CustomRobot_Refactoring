#pragma once
#include "../Utility/AsoUtility.h"

class Camera
{
public:

	//  カメラの回転速度
	static constexpr float CAMERA_ANGLE_SPEED = 0.05f;

	//  カメラの注視点の高さ
	static constexpr float CAMERA_LOOK_AT_HEIGHT = 400.0f;

	//  カメラと注視点の距離
	static constexpr float CAMERA_LOOK_AT_DISTANCE = 2150.0f;

	static constexpr VECTOR INIT_POS = { 0.0f,540.0f,-690.0f };


	static constexpr float SUBLIGHT_RANGE = 80000.0f;
	static constexpr VECTOR SUBLIGHT_ATTEN = { 0.0f,0.0015f,0.0f };

	//	オートモード以外のカメラアングル
	static constexpr VECTOR INIT_ANGLE = { 40.0f * 3.14 / 180.0f,0.0f,0.0f };

	static constexpr VECTOR INIT_ANGLE_AUTO = { 360.0f ,40.0f ,0.0f };

	//  カメラモード
	enum class MODE
	{
		NONE,
		FIXED_POINT,	//  定点カメラ
		FREE,			//  フリーモード
		AUTO,
		TITLE

	};

	//  コンストラクタ
	Camera(void);

	//  デストラクタ
	~Camera();

	//  初期処理(基本的に最初の一回だけ実装)
	void Init(void);

	//  更新処理（毎フレーム実行）
	void Update(void);

	//  カメラ設定(毎フレーム実行)
	void SetBeforeDraw(void);
	void SetBeforeDrawFixedPoint(void);
	void SetBeforeDrawFree(void);
	void SetBeforeDrawAuto(void);
	void SetBeforeDrawTitle(void);

	//  描画処理(毎フレーム実行)
	void Draw(void);

	//  解放処理(基本的に最後の一回だけ実装)
	void Release(void);

	void SetTargetPos(VECTOR plPos1, VECTOR plPos2);


	//  カメラモードの変更
	void ChangeMode(MODE mode);

	float GetHAngle(void);
	void SetHAngle(float angle);
	
private:

	//  カメラモード
	MODE mode_;

	//  カメラの位置
	VECTOR pos_;

	//  カメラの角度
	VECTOR angles_;

	int cLight_;
	int light2_;

	VECTOR targetPos_;

	VECTOR plDistance_;
	float plDisLen;

	float  cameraHAngle_;
	float  cameraVAngle_;
	float  sinParam_;
	float  cosParam_;

	int xRotCam_;
};

