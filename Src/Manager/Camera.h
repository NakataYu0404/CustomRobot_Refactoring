#pragma once
#include <DxLib.h>

//  カメラの回転速度
#define CAMERA_ANGLE_SPEED		0.05f

//  カメラの注視点の高さ
#define CAMERA_LOOK_AT_HEIGHT		400.0f

//  カメラと注視点の距離
#define CAMERA_LOOK_AT_DISTANCE		2150.0f



class Camera
{
public:

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

