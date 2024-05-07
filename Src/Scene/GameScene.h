#pragma once
#include <vector>
#include <memory>
#include "SceneBase.h"
#include "CustomScene.h"

class ResourceManager;
class Stage;
class Cannon;
class PlayerBase;

class GameScene : public SceneBase
{
public:

	//  �Q�[���I�[�o�[�n�_�Փ˔��苅�̔��a
	static constexpr float OVER_COL_RADIUS = 35.0f;

	//  �R���X�g���N�^
	GameScene(void);

	//  �f�X�g���N�^
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	//	�J�X�^�������v���C���[���Z�b�g����(CustomScene��SceneManager��GameScene)
	void SetPlayer(std::weak_ptr<PlayerBase> player[2]);

private:

	//	�X�e�[�W�|�C���^(���̃N���X�ō��)
	std::shared_ptr<Stage> stage_;

	//  �v���C���[��id
	int modelPlayerId_;
	int modelPlayerId2_;

	//	�v���C���[�|�C���^(������̂�������)
	std::shared_ptr<PlayerBase> players_[2];

	//  �Q�[���I�[�o�[����
	bool p2win_;
	bool p1win_;

	//  �Q�[���I�[�o�[�摜
	int imgP1Win_;
	int imgP2Win_;

	//	�v���C���[���W
	VECTOR pl1Pos_;
	VECTOR pl2Pos_;

	//	�e�摜
	int shadowH;

	//	���f��ID
	int pl1ModelId_;
	int pl2ModelId_;

	//	����HP�̊e�ʂ��v�Z����(�摜�ɒ�������)
	int hpHundred_[2];
	int hpTens_[2];
	int hpOnes_[2];

	//  0�`9�̔ԍ��摜�n���h���iHP�Ɏg���j
	int NumImageH_[2][10];

	//	HP�`��Ɏg���摜�n���h��
	int HpWindowH_[2];
	int HpBarImageH_[2];
	int HpBarBlackImageH_;
	int HpScaleImageH_;

	//	�ŏ��̃J�E���g�_�E���Ɏg���摜�n���h��
	int gameNumImgH_[5];

	//	�e�T�E���h�n���h��
	int soundBgmH_;
	int soundVicH_;

	//	��[���ǂ�J�E���g
	int GameCountFlame_;
	int GameCount_;

	//	�X�^�[�g�I�摜�n���h��
	int startH_;
	
	//	1�Q�[�����[�v��������̏����𖳎����邽�߂̃t���O
	bool initFlag_;

	//  ������������̏���(�Z�b�^�[����Ȃ���I)
	void GameSet(void);

	ResourceManager& resMng_;
};

