#include <DxLib.h>
#include "../Application.h"
#include "Resource.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::instance_ = nullptr;

void ResourceManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new ResourceManager();
	}
	instance_->Init();
}

ResourceManager& ResourceManager::GetInstance(void)
{
	return *instance_;
}

void ResourceManager::Init(void)
{

	//  推奨しませんが、どうしても使いたい方は
	using RES = Resource;
	using RES_T = RES::TYPE;
	static std::string PATH_IMG = Application::PATH_IMAGE;
	static std::string PATH_MDL = Application::PATH_MODEL;
	static std::string PATH_EFF = Application::PATH_EFFECT;

	Resource* res;

	//  画像
	res = new RES(RES_T::IMG, PATH_IMG + "Title.png");
	resourcesMap_.emplace(SRC::IMG_TITLE, res);

	res = new RES(RES_T::IMG, PATH_IMG + "p1Win.png");
	resourcesMap_.emplace(SRC::IMG_1P_WIN, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p2Win.png");
	resourcesMap_.emplace(SRC::IMG_2P_WIN, res);

	res = new RES(RES_T::IMG, PATH_IMG + "p1Num/0.png");
	resourcesMap_.emplace(SRC::IMG_1P_NUM0, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p1Num/1.png");
	resourcesMap_.emplace(SRC::IMG_1P_NUM1, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p1Num/2.png");
	resourcesMap_.emplace(SRC::IMG_1P_NUM2, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p1Num/3.png");
	resourcesMap_.emplace(SRC::IMG_1P_NUM3, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p1Num/4.png");
	resourcesMap_.emplace(SRC::IMG_1P_NUM4, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p1Num/5.png");
	resourcesMap_.emplace(SRC::IMG_1P_NUM5, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p1Num/6.png");
	resourcesMap_.emplace(SRC::IMG_1P_NUM6, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p1Num/7.png");
	resourcesMap_.emplace(SRC::IMG_1P_NUM7, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p1Num/8.png");
	resourcesMap_.emplace(SRC::IMG_1P_NUM8, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p1Num/9.png");
	resourcesMap_.emplace(SRC::IMG_1P_NUM9, res);

	res = new RES(RES_T::IMG, PATH_IMG + "p2Num/0.png");
	resourcesMap_.emplace(SRC::IMG_2P_NUM0, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p2Num/1.png");
	resourcesMap_.emplace(SRC::IMG_2P_NUM1, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p2Num/2.png");
	resourcesMap_.emplace(SRC::IMG_2P_NUM2, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p2Num/3.png");
	resourcesMap_.emplace(SRC::IMG_2P_NUM3, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p2Num/4.png");
	resourcesMap_.emplace(SRC::IMG_2P_NUM4, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p2Num/5.png");
	resourcesMap_.emplace(SRC::IMG_2P_NUM5, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p2Num/6.png");
	resourcesMap_.emplace(SRC::IMG_2P_NUM6, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p2Num/7.png");
	resourcesMap_.emplace(SRC::IMG_2P_NUM7, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p2Num/8.png");
	resourcesMap_.emplace(SRC::IMG_2P_NUM8, res);
	res = new RES(RES_T::IMG, PATH_IMG + "p2Num/9.png");
	resourcesMap_.emplace(SRC::IMG_2P_NUM9, res);

	res = new RES(RES_T::IMG, PATH_IMG + "player1.png");
	resourcesMap_.emplace(SRC::IMG_1P_HPBAR, res);
	res = new RES(RES_T::IMG, PATH_IMG + "player2.png");
	resourcesMap_.emplace(SRC::IMG_2P_HPBAR, res);

	res = new RES(RES_T::IMG, PATH_IMG + "Hpbar.png");
	resourcesMap_.emplace(SRC::IMG_HPSCALE, res);

	res = new RES(RES_T::IMG, PATH_IMG + "HpbarBlack.png");
	resourcesMap_.emplace(SRC::IMG_HPBLACK, res);

	res = new RES(RES_T::IMG, PATH_IMG + "Num/1.png");
	resourcesMap_.emplace(SRC::IMG_COUNTDOWN_NUM1, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Num/2.png");
	resourcesMap_.emplace(SRC::IMG_COUNTDOWN_NUM2, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Num/3.png");
	resourcesMap_.emplace(SRC::IMG_COUNTDOWN_NUM3, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Num/4.png");
	resourcesMap_.emplace(SRC::IMG_COUNTDOWN_NUM4, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Num/5.png");
	resourcesMap_.emplace(SRC::IMG_COUNTDOWN_NUM5, res);

	res = new RES(RES_T::IMG, PATH_IMG + "start.png");
	resourcesMap_.emplace(SRC::IMG_GAMESTART, res);

	res = new RES(RES_T::IMG, PATH_IMG + "Enemy/birb.png");
	resourcesMap_.emplace(SRC::IMG_BIRB, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Enemy/yeti.png");
	resourcesMap_.emplace(SRC::IMG_YETI, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Enemy/cactoro.png");
	resourcesMap_.emplace(SRC::IMG_CACTORO, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Enemy/ghost.png");
	resourcesMap_.emplace(SRC::IMG_GHOST, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Enemy/bluedemon.png");
	resourcesMap_.emplace(SRC::IMG_BEMON, res);

	res = new RES(RES_T::IMG, PATH_IMG + "Weapon/machine.png");
	resourcesMap_.emplace(SRC::IMG_MACHINE, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Weapon/punch.png");
	resourcesMap_.emplace(SRC::IMG_PUNCH, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Weapon/sniper.png");
	resourcesMap_.emplace(SRC::IMG_SNIPER, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Weapon/cannon.png");
	resourcesMap_.emplace(SRC::IMG_CANNON, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Weapon/delay.png");
	resourcesMap_.emplace(SRC::IMG_DELAY, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Weapon/bounce.png");
	resourcesMap_.emplace(SRC::IMG_BOUNCE, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Weapon/air.png");
	resourcesMap_.emplace(SRC::IMG_AIR, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Weapon/sticky.png");
	resourcesMap_.emplace(SRC::IMG_STICKY, res);

	res = new RES(RES_T::IMG, PATH_IMG + "Weapon/airdash.png");
	resourcesMap_.emplace(SRC::IMG_AIRDASH, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Weapon/hover.png");
	resourcesMap_.emplace(SRC::IMG_HOVER, res);

	res = new RES(RES_T::IMG, PATH_IMG + "ready.png");
	resourcesMap_.emplace(SRC::IMG_READY, res);

	res = new RES(RES_T::IMG, PATH_IMG + "P1customend.png");
	resourcesMap_.emplace(SRC::IMG_1P_CUSTOMEND, res);
	res = new RES(RES_T::IMG, PATH_IMG + "P2customend.png");
	resourcesMap_.emplace(SRC::IMG_2P_CUSTOMEND, res);

	res = new RES(RES_T::IMG, PATH_IMG + "Select/select1.png");
	resourcesMap_.emplace(SRC::IMG_SELECT_ANIM1, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Select/select2.png");
	resourcesMap_.emplace(SRC::IMG_SELECT_ANIM2, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Select/select3.png");
	resourcesMap_.emplace(SRC::IMG_SELECT_ANIM3, res);

	res = new RES(RES_T::IMG, PATH_IMG + "smoke.png");
	resourcesMap_.emplace(SRC::IMG_SMOKE, res);

	res = new RES(RES_T::IMGS, PATH_IMG + "Blast.png");
	resourcesMap_.emplace(SRC::IMG_BLAST, res);

	res = new RES(RES_T::IMG, PATH_IMG + "Stun/1.png");
	resourcesMap_.emplace(SRC::IMG_STUN_ANIM1, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Stun/2.png");
	resourcesMap_.emplace(SRC::IMG_STUN_ANIM2, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Stun/3.png");
	resourcesMap_.emplace(SRC::IMG_STUN_ANIM3, res);
	res = new RES(RES_T::IMG, PATH_IMG + "Stun/4.png");
	resourcesMap_.emplace(SRC::IMG_STUN_ANIM4, res);

	res = new RES(RES_T::IMG, PATH_IMG + "sousakihon.png");
	resourcesMap_.emplace(SRC::IMG_INSTRUCTION_BASE, res);
	res = new RES(RES_T::IMG, PATH_IMG + "sousakougeki.png");
	resourcesMap_.emplace(SRC::IMG_INSTRUCTION_ATTACK, res);

	res = new RES(RES_T::IMG, PATH_IMG + "Box.png");
	resourcesMap_.emplace(SRC::IMG_UIBOX, res);

	res = new RES(RES_T::MODEL, PATH_MDL + "Stage/Sky.mv1");
	resourcesMap_.emplace(SRC::MDL_SKYDOME, res);

	res = new RES(RES_T::MODEL, PATH_MDL + "Enemy/Birb.mv1");
	resourcesMap_.emplace(SRC::MDL_BIRB, res);
	res = new RES(RES_T::MODEL, PATH_MDL + "Enemy/Yeti.mv1");
	resourcesMap_.emplace(SRC::MDL_YETI, res);
	res = new RES(RES_T::MODEL, PATH_MDL + "Enemy/Cactoro.mv1");
	resourcesMap_.emplace(SRC::MDL_CACTORO, res);
	res = new RES(RES_T::MODEL, PATH_MDL + "Enemy/BlueDemon.mv1");
	resourcesMap_.emplace(SRC::MDL_BEMON, res);
	res = new RES(RES_T::MODEL, PATH_MDL + "Enemy/Ghost.mv1");
	resourcesMap_.emplace(SRC::MDL_GHOST, res);

	res = new RES(RES_T::MODEL, PATH_MDL + "Stage/Stage.mv1");
	resourcesMap_.emplace(SRC::MDL_STAGE, res);
	res = new RES(RES_T::MODEL, PATH_MDL + "Stage/Cover.mv1");
	resourcesMap_.emplace(SRC::MDL_COVER, res);
	res = new RES(RES_T::MODEL, PATH_MDL + "Stage/Moji.mv1");
	resourcesMap_.emplace(SRC::MDL_CHAR, res);

	res = new RES(RES_T::MODEL, PATH_MDL + "Shot/Crosshair.mv1");
	resourcesMap_.emplace(SRC::MDL_CROSSHAIR, res);
	res = new RES(RES_T::MODEL, PATH_MDL + "Shot/Shot.mv1");
	resourcesMap_.emplace(SRC::MDL_SHOT, res);
	res = new RES(RES_T::MODEL, PATH_MDL + "Shot/Fist.mv1");
	resourcesMap_.emplace(SRC::MDL_FIST, res);
	res = new RES(RES_T::MODEL, PATH_MDL + "Shot/SpikeShot.mv1");
	resourcesMap_.emplace(SRC::MDL_SPIKESHOT, res);
	res = new RES(RES_T::MODEL, PATH_MDL + "Shot/Bird.mv1");
	resourcesMap_.emplace(SRC::MDL_BIRD, res);

}

void ResourceManager::Release(void)
{
	for (auto& p : loadedMap_)
	{
		p.second.Release();
	}

	loadedMap_.clear();
}

void ResourceManager::Destroy(void)
{
	Release();
	for (auto& res : resourcesMap_)
	{
		res.second->Release();
		delete res.second;
	}
	resourcesMap_.clear();
	delete instance_;
}

const Resource& ResourceManager::Load(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return dummy_;
	}
	return res;
}

int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res.handleId_);
	res.duplicateModelIds_.push_back(duId);

	return duId;
}

ResourceManager::ResourceManager(void)
{
}

Resource& ResourceManager::_Load(SRC src)
{

	//  ロード済みチェック
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		return *resourcesMap_.find(src)->second;
	}

	//  リソース登録チェック
	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		//  登録されていない
		return dummy_;
	}

	//  ロード処理
	rPair->second->Load();

	//  念のためコピーコンストラクタ
	loadedMap_.emplace(src, *rPair->second);

	return *rPair->second;

}
