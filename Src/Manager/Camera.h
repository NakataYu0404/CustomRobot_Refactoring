#pragma once
#include "../Utility/AsoUtility.h"

class Camera
{
public:

	//  �J�����̉�]���x
	static constexpr float CAMERA_ANGLE_SPEED = 0.05f;

	//  �J�����̒����_�̍���
	static constexpr float CAMERA_LOOK_AT_HEIGHT = 400.0f;

	//  �J�����ƒ����_�̋���
	static constexpr float CAMERA_LOOK_AT_DISTANCE = 2150.0f;

	static constexpr VECTOR INIT_POS = { 0.0f,540.0f,-690.0f };


	static constexpr float SUBLIGHT_RANGE = 80000.0f;
	static constexpr VECTOR SUBLIGHT_ATTEN = { 0.0f,0.0015f,0.0f };

	//	�I�[�g���[�h�ȊO�̃J�����A���O��
	static constexpr VECTOR INIT_ANGLE = { 40.0f * 3.14 / 180.0f,0.0f,0.0f };

	static constexpr VECTOR INIT_ANGLE_AUTO = { 360.0f ,40.0f ,0.0f };

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

