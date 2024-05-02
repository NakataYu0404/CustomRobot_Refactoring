#pragma once
#include <map>
#include <string>
#include "Resource.h"

class ResourceManager
{

public:


	// リソース名
	enum class SRC
	{
		//	画像
		IMG_TITLE,		//	タイトル

		IMG_1P_WIN,		//	勝利
		IMG_2P_WIN,

		IMG_1P_NUM0,	//	プレイヤーごとの体力を表す数字
		IMG_1P_NUM1,	//	持ってる画像のスプライトが手に入ったらこれを一つにまとめたい…
		IMG_1P_NUM2,
		IMG_1P_NUM3,
		IMG_1P_NUM4,
		IMG_1P_NUM5,
		IMG_1P_NUM6,
		IMG_1P_NUM7,
		IMG_1P_NUM8,
		IMG_1P_NUM9,
		IMG_2P_NUM0,
		IMG_2P_NUM1,
		IMG_2P_NUM2,
		IMG_2P_NUM3,
		IMG_2P_NUM4,
		IMG_2P_NUM5,
		IMG_2P_NUM6,
		IMG_2P_NUM7,
		IMG_2P_NUM8,
		IMG_2P_NUM9,

		IMG_1P_HPBAR,		//	HPバーの枠組み
		IMG_2P_HPBAR,

		IMG_HPSCALE,	//	HPのメモリ

		IMG_HPBLACK,	//	HPバーの黒背景

		IMG_COUNTDOWN_NUM1,	//	ゲーム開始時のカウントダウン数字
		IMG_COUNTDOWN_NUM2,
		IMG_COUNTDOWN_NUM3,
		IMG_COUNTDOWN_NUM4,
		IMG_COUNTDOWN_NUM5,

		IMG_GAMESTART,	//	カウントダウン終了時のゲームスタート

		IMG_BIRB,		//	キャラクター説明
		IMG_YETI,
		IMG_CACTORO,
		IMG_BEMON,
		IMG_GHOST,

		IMG_MACHINE,	//	ガン説明
		IMG_PUNCH,
		IMG_SNIPER,
		IMG_CANNON,		//	ボム説明
		IMG_DELAY,
		IMG_BOUNCE,		//	ポッド説明
		IMG_AIR,
		IMG_STICKY,

		IMG_AIRDASH,	//	レッグ説明
		IMG_HOVER,

		IMG_READY,		//	準備完了にカーソルを合わせたときの画像

		IMG_1P_CUSTOMEND,	//	準備完了
		IMG_2P_CUSTOMEND,

		IMG_SELECT_ANIM1,	//	選択操作説明アニメーション
		IMG_SELECT_ANIM2,
		IMG_SELECT_ANIM3,

		IMG_SMOKE,		//	足元スモーク画像

		IMG_STUN_ANIM1,	//	スタン画像アニメーション
		IMG_STUN_ANIM2,
		IMG_STUN_ANIM3,
		IMG_STUN_ANIM4,

		IMG_INSTRUCTION_BASE,	//	基本操作説明画像
		IMG_INSTRUCTION_ATTACK,	//	攻撃操作説明画像

		//	モデル
		MDL_SKYDOME,	//	スカイドーム

		MDL_BIRB,		//	キャラクター
		MDL_YETI,
		MDL_CACTORO,
		MDL_BEMON,
		MDL_GHOST,

		MDL_STAGE,		//	ステージ
		MDL_COVER,		//	見えないステージカバー(当たり判定だけある)
		MDL_CHAR,		//	ステージの地面に出す文字

		MDL_CROSSHAIR,	//	クロスヘアモデル(キャノンボムで使用)
		MDL_SHOT,		//	通常ショット
		MDL_FIST,		//	拳
		MDL_SPIKESHOT,	//	トゲ(バウンス、スティッキーポッドで使用)
		MDL_BIRD,		//	鳥(スカイポッドで使用)

	};

	// 明示的にインステンスを生成する
	static void CreateInstance(void);

	// 静的インスタンスの取得
	static ResourceManager& GetInstance(void);

	// 初期化
	void Init(void);

	// 解放(シーン切替時に一旦解放)
	void Release(void);

	// リソースの完全破棄
	void Destroy(void);

	// リソースのロード
	const Resource& Load(SRC src);

	// リソースの複製ロード(モデル用)
	int LoadModelDuplicate(SRC src);

private:

	// 静的インスタンス
	static ResourceManager* instance_;

	// リソース管理の対象
	std::map<SRC, Resource*> resourcesMap_;

	// 読み込み済みリソース
	std::map<SRC, Resource&> loadedMap_;

	Resource dummy_;

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	ResourceManager(void);
	ResourceManager(const ResourceManager& manager) = default;
	~ResourceManager(void) = default;

	// 内部ロード
	Resource& _Load(SRC src);

};
