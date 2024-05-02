#include "InputManager.h"
#include "../Utility/AsoUtility.h"
#include "Camera.h"

Camera::Camera(void)
{
}

Camera::~Camera()
{
}

void Camera::Init(void)
{
	// �J�����̈ʒu
	pos_ = { 0.0f,540.0f,-690.0f };
	
	// �J�����̊p�x
	angles_ = { 40.0f * DX_PI_F / 180.0f,0.0f,0.0f };

	light2_ = CreatePointLightHandle(pos_,80000.0f,0.0f,0.0015f,0.0f);

	// �J�����̌�����������
	cameraHAngle_ = 360.0f;
	cameraVAngle_ = 40.0f;

	targetPos_ = { 0.0f,0.0f,0.0f };
	plDistance_ = { 0.0f,0.0f,0.0f };

	xRotCam_ = 0;
}

void Camera::Update(void)
{
	SetLightPositionHandle(light2_, pos_);
}

void Camera::SetBeforeDraw(void)
{
	// �N���b�v������ݒ肷��(SetDrawScreen�Ń��Z�b�g������)
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
		//�J�����̐ݒ�(�ʒu�Ɗp�x�ɂ�鐧��)
		SetCameraPositionAndAngle(pos_, angles_.x, angles_.y, angles_.z);

		break;
	case Camera::MODE::AUTO:
		SetBeforeDrawAuto();
		break;
	default:
		break;
	}
}

void Camera::SetBeforeDrawFixedPoint(void)
{
	pos_ = { 0.0f,98.0f,-80.0f };
	angles_ = { 0.5f,0.0f,0.0f };

}

void Camera::SetBeforeDrawFree(void)
{
	auto& ins = InputManager::GetInstance();

	// WASD�ŃJ�����̈ʒu��ς���
	float movePow = 3.0f;
	if (ins.IsNew(KEY_INPUT_W)) { pos_.z += movePow; }
	if (ins.IsNew(KEY_INPUT_A)) { pos_.x -= movePow; }
	if (ins.IsNew(KEY_INPUT_S)) { pos_.z -= movePow; }
	if (ins.IsNew(KEY_INPUT_D)) { pos_.x += movePow; }
	if (ins.IsNew(KEY_INPUT_Q)) { pos_.y += movePow; }
	if (ins.IsNew(KEY_INPUT_E)) { pos_.y -= movePow; }

	// ���L�[�ŃJ�����̊p�x��ς���
	float rotPow = 1.0f * DX_PI_F / 180.0f;

	if (ins.IsNew(KEY_INPUT_I))	 { angles_.x -= rotPow; }
	if (ins.IsNew(KEY_INPUT_J))	 { angles_.y -= rotPow; }
	if (ins.IsNew(KEY_INPUT_K))	 { angles_.x += rotPow; }
	if (ins.IsNew(KEY_INPUT_L))	 { angles_.y += rotPow; }

}

void Camera::SetBeforeDrawAuto(void)
{

	cameraHAngle_ -= CAMERA_ANGLE_SPEED;
	if (cameraHAngle_ <= -180)
	{
		cameraHAngle_ += 360;
	}

		VECTOR tempPos;
		VECTOR tempPos2;

		// �J�����̈ʒu�̓J�����̐����p�x�Ɛ����p�x����Z�o

		// �ŏ��ɐ����p�x�𔽉f�����ʒu���Z�o
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

		// ���ɐ����p�x�𔽉f�����ʒu���Z�o
		sinParam_ = sin(cameraHAngle_ / 180.0f * DX_PI_F);
		cosParam_ = cos(cameraHAngle_ / 180.0f * DX_PI_F);
		tempPos2.x = cosParam_ * tempPos.x - sinParam_ * tempPos.z;
		tempPos2.y = tempPos.y + plDistance_.y;
		tempPos2.z = sinParam_ * tempPos.x + cosParam_ * tempPos.z;

		// �Z�o�������W�ɒ����_�̈ʒu�����Z�������̂��J�����̈ʒu
		pos_ = VAdd(tempPos2, targetPos_);

		// �J�����̐ݒ�ɔ��f����
		SetCameraPositionAndTarget_UpVecY(pos_, targetPos_);
	
}

void Camera::SetBeforeDrawTitle(void)
{
	pos_ = { 0.0f,0.0f,0.0f };
	angles_ = { 0.5f,0.0f,0.0f };

}

void Camera::ChangeMode(MODE mode)
{
	mode_ = mode;

	// �ύX���̏���������
	switch (mode_)
	{
	case Camera::MODE::FIXED_POINT:

		break;
	case Camera::MODE::FREE:

		break;
	case Camera::MODE::AUTO:
		break;
	}
}

float Camera::GetHAngle(void)
{
	return cameraHAngle_;
}

void Camera::SetHAngle(float angle)
{
	cameraHAngle_ = angle;
}

void Camera::Draw(void)
{
	//DrawFormatString(0, 0, 0x000000, "WASD��X,Z���J�����ړ��AQE��Y���J�����ړ��AIJKL��X,Y���J������]");
	//DrawFormatString(0, 20, 0x000000,"game�J�������W�F(%.2f, %.2f, %.2f)", pos_.x, pos_.y, pos_.z);
	//DrawFormatString(0, 40, 0x000000, "game�J�����p�x�F(%.2f, %.2f, %.2f)", cameraVAngle_, cameraHAngle_,0.0f);
	//DrawFormatString(0, 150, 0x000000, "%.2f", plDisLen);
}

void Camera::Release(void)
{
	DeleteLightHandle(light2_);
}

void Camera::SetTargetPos(VECTOR plPos1, VECTOR plPos2)
{
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

	// �n�ʂ�菭�����𒍎��_�ɐݒ肵����
	targetPos_.y -= 100;

	plDisLen = sqrt(plDistance_.x * plDistance_.x + plDistance_.y * plDistance_.y + plDistance_.z * plDistance_.z);

	if (plDisLen <= 500)
	{
		plDisLen = 500;
	}

}
