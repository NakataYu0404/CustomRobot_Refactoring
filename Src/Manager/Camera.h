#pragma once
#include <DxLib.h>

//  �J�����̉�]���x
#define CAMERA_ANGLE_SPEED		0.05f

//  �J�����̒����_�̍���
#define CAMERA_LOOK_AT_HEIGHT		400.0f

//  �J�����ƒ����_�̋���
#define CAMERA_LOOK_AT_DISTANCE		2150.0f



class Camera
{
public:

	//  �J�������[�h
	enum class MODE
	{
		NONE,
		FIXED_POINT,	//  ��_�J����
		FREE,			//  �t���[���[�h
		AUTO,
		TITLE

	};

	//  �R���X�g���N�^
	Camera(void);

	//  �f�X�g���N�^
	~Camera();

	//  ��������(��{�I�ɍŏ��̈�񂾂�����)
	void Init(void);

	//  �X�V�����i���t���[�����s�j
	void Update(void);

	//  �J�����ݒ�(���t���[�����s)
	void SetBeforeDraw(void);
	void SetBeforeDrawFixedPoint(void);
	void SetBeforeDrawFree(void);
	void SetBeforeDrawAuto(void);
	void SetBeforeDrawTitle(void);

	//  �`�揈��(���t���[�����s)
	void Draw(void);

	//  �������(��{�I�ɍŌ�̈�񂾂�����)
	void Release(void);

	void SetTargetPos(VECTOR plPos1, VECTOR plPos2);


	//  �J�������[�h�̕ύX
	void ChangeMode(MODE mode);

	float GetHAngle(void);
	void SetHAngle(float angle);
	
private:

	//  �J�������[�h
	MODE mode_;

	//  �J�����̈ʒu
	VECTOR pos_;

	//  �J�����̊p�x
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

