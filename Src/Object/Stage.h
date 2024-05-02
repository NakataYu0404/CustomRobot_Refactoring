#pragma once
class Stage
{
public:

	// �R���X�g���N�^
	Stage(void);
	// �f�X�g���N�^
	~Stage(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	int GetModelId(void);
	int GetCoverModelId(void);

	void SetShadowH(int Hand);

private:

	// 3D���f���̃n���h��ID
	int modelId_;
	int coverModelId_;

	int modelSkyId_;

	// �X�e�[�W��ɔz�u������蕶����ID�A�����蔻�肢��Ȃ�
	int charId_;

	// �w�i�摜�̃n���h��ID
	int imgBack_;

	int shadowH;

};

