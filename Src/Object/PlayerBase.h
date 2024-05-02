#pragma once
#include <vector>
#include <string>
#include <memory>
#include <DxLib.h>
#include "../Manager/InputManager.h"


class GameScene;
class WeaponBase;

class PlayerBase
{
public:

	// 衝突半径
	static constexpr float COL_RADIUS = 35.0f;

	// 回転量(deg)
	static constexpr float SPEED_ROT = 8.0f;

	// 回転量(rad)
	static constexpr float SPEED_ROT_RAD = SPEED_ROT * DX_PI_F / 180.0f;

	// 爆発のアニメーション数
	static constexpr int BLAST_ANIM_NUM = 16;

	// 爆発のサイズ
	static constexpr int BLAST_SIZE_X = 32;
	static constexpr int BLAST_SIZE_Y = 32;

	static constexpr float MIN_MOVE_SPEED = 0.1f;
	// 加速(accelerator=アクセラレーター)
	static constexpr float MOVE_ACC = 0.10f;

	// 体力最大値
	const int hpMax_ = 999;

	const float BOMB_HIGHEST = 500.0f;

	int InvincibleCntMax = 10;

	int smokeImage_[12];
	VECTOR smokeSpriteSize_ = { 176,61,0 };
	VECTOR jumpPos_;
	int smokesprite = 0;
	bool isSpriteEnd_;

	int stunImgs_[4];

	enum class TYPE
	{
		// 1P,2P
		NONE,
		PLAYER_1,
		PLAYER_2,
		MAX
	};

	struct KEY_CONFIG
	{
		// キーコンフィグ(1P,2P)
		InputManager::JOYPAD_BTN SHOT;
		InputManager::JOYPAD_BTN BOMB;
		InputManager::JOYPAD_BTN POD;
		InputManager::JOYPAD_BTN JUMP;
		InputManager::JOYPAD_BTN AIRDASH;
		InputManager::JOYPAD_BTN TACKLE;

	};

	enum class STATUS
	{
		IDLE,
		WALK,
		RUN,
		JUMP,
		STUN,
		TACKLE,
		RECOVERY
	};

	// 弾数
	struct BULLETS
	{
		static constexpr int S_MACHINE = 8;
		static constexpr int S_ELECSHOCK = 1;
		static constexpr int S_SNIPER = 1;
		static constexpr int B_CANNON = 1;
		static constexpr int B_MINE = 1;
		static constexpr int P_BOUNCE = 10;
		static constexpr int P_FREEZE = 2;
		static constexpr int P_STICKY = 1;
	};

	struct WeaponDelay
	{
		static constexpr int S_MACHINE = 25;
		static constexpr int S_ELECSHOCK = 1;
		static constexpr int S_SNIPER = 100;
		static constexpr int B_CANNON = 150;
		static constexpr int B_MINE = 220;
		static constexpr int P_BOUNCE = 50;
		static constexpr int P_FREEZE = 100;
		static constexpr int P_STICKY = 60;
	};

	enum class ATTACK_TYPE
	{
		SHOT,
		BOMB,
		POD,
		MAX
	};

	enum class SHOT_TYPE
	{
		MACHINE,
		ELECSHOCK,
		SNIPER,
		MAX,
	};

	enum class BOMB_TYPE
	{
		CANNON,
		MINE,
		MAX,
	};

	enum class POD_TYPE
	{
		BOUNCE,
		FREEZE,
		STICKY,
		MAX,
	};


	enum class REG_TYPE
	{
		AIRDASH,
		HOVER,
		MAX
	};

	struct PlayerAnim
	{
		int IdleAnim;
		int WalkAnim;
		int RunAnim;
		int JumpAnim;
		int StunAnim;
	};

	// コンストラクタ
	PlayerBase(void);

	// デストラクタ
	~PlayerBase(void);

	// 初期処理(最初の1回のみ実行)
	void Init(TYPE type, KEY_CONFIG keyConfig);

	void ChangeBody(int modelId);
	void ChangeShot(SHOT_TYPE shotType);
	void ChangeBomb(BOMB_TYPE bombType);
	void ChangePod(POD_TYPE podType);
	void ChangeReg(REG_TYPE regType);

	// パラメータ設定(純粋仮想関数)
	virtual void SetParam(void);

	// 共通のパラメータ設定(キャラによって変わらない)
	void SetCommon(void);

	// 更新処理(毎フレーム実行)
	void Update(void);

	// 描画処理(毎フレーム実行)
	void Draw(void);

	// 解放処理(最後の１回のみ実行)
	void Release(void);

	void Animation(void);
	void ChangeAnim(void);

	// 座標の取得
	VECTOR GetPos(void);

	// 衝突判定座標の取得
	VECTOR GetColPos(void);

	VECTOR GetScl(void);

	// 座標の設定
	void SetPos(VECTOR pos);

	// 生存判定
	bool IsAlive(void);

	// 生存判定を設定
	void SetAlive(bool alive);

	// ダメージを与える
	void Damage(int hpDamage,int stunDamage,VECTOR weaponDir,ATTACK_TYPE type);

	// 衝突判定球の半径を取得する
	float GetRadius(void);

	// HPを取得する
	int GetHp(void);
	
	// スタン値を取得する
	int GetStunHp(void);


	// 敵位置をセットする(敵に向かって撃つ弾に使っている)ゲームシーンからセットされている。
	void SetEnemyPos(VECTOR pos);

	// 弾の取得
	std::vector<std::shared_ptr<WeaponBase>> GetShots(void);
	std::vector<std::shared_ptr<WeaponBase>> GetBombs(void);
	std::vector<std::shared_ptr<WeaponBase>> GetPods(void);

	SHOT_TYPE GetShotType(void);
	BOMB_TYPE GetBombType(void);

	// ステージと蓋のIDをゲームシーンから取ってくる(当たり判定を作成するために必要)
	void SetModelStageId(int stageId);
	void SetModelCoverId(int coverId);

	// モデルID取得
	int GetPlayerModelId(void);

	// 無敵か？
	bool GetInvincible(void);
	bool GetRecovery(void);

	// アタックのダメージ
	int GetAttackDamage(void);

	// SETGETどちらも同じクラスで使うならこの関数を使う宛先に変数作れば良いような気がするが、プレイヤーごとに変数を分けるために必要
	void SetAlreadyAttack(bool hit);
	bool GetAlreadyAttack(void);

	POD_TYPE GetPodType(void);

	void ChangeStatus(STATUS state);

protected:

	enum class SE_TYPE
	{
		SHOT,
		BOMB,
		POD,
		DAMAGE,
		TACKLE
	};

	// ブキ系
	// 使うブキ種が何か
	SHOT_TYPE shotType_;
	BOMB_TYPE bombType_;
	POD_TYPE podType_;
	REG_TYPE regType_;

	// 発射した弾数のカウンタ
	int shotFireCnt_;
	int bombFireCnt_;
	int podFireCnt_;

	int shotFlameCnt_;
	int podFlameCnt_;

	// 弾が発射可能になるまでのカウンタ
	int delayShotCnt_;
	int delayShot_;
	// ボムが発射可能になるまでのカウンタ
	int delayBombCnt_;
	int delayBomb_;
	// ポッドが発射可能になるまでのカウンタ
	int delayPodCnt_;
	int delayPod_;

	int delayAttackCnt_;
	int delayAttack_;

	// 現在弾を撃っているか(撃っていたら足を遅くする)
	bool isShot_;

	// 残弾数
	int shotBullet_;
	int bombBullet_;
	int podBullet_;

	// 移動速度の最大値
	float MAX_MOVE_SPEED;

	// ジャンプ、空中アクション系
	// エアダッシュ、ジャンプできる回数
	int MAX_AIRDASH_CNT;

	// ホバーできる時間
	int MAX_HOVER_CNT;

	// ジャンプキー入力を受け付けるフレーム数
	int INPUT_JUMP_FRAME;

	//	最大ジャンプ力
	float MAX_JUMP_POW;

	// 現在ジャンプ中かの判定 YESでジャンプ中
	bool isJump_;

	// ジャンプキーの押下判定
	bool isPutJumpKey_;

	// ジャンプキー入力カウンタ
	int cntJumpInput_;

	// 今エアダッシュ中か？
	bool isAirDash_;

	// すでにエアダッシュを行ったか？
	bool alreadyAirDash_;

	// エアダッシュを何回使ったかのカウンタ
	int airDashCnt_;

	bool isHover_;
	bool alreadyHover_;
	int hoverCnt_;

	// Init系
	// 元となるプレイヤーのモデルID
	int baseModelId_;


	// プレイヤーのモデルID
	int modelId_;
	int modelIdOld_;

	// 移動速度
	float speed_;

	// 空中ダッシュ速度
	float airDashSpeed_;

	// 体力
	int hp_;

	// スタン値の最大(スタンしやすさ)はキャラによって変更したい
	int stunHpMax_;
	// スタン値
	int stunHp_;

	// アタックしたから無敵なのか？
	bool attackFlag;
	// 体当たりのダメージ
	int attackDamage_;

	bool alreadyAttackHit_;

	// スタン中にもらったダメージ
	int stunDmg_;
	// スタンしている時間
	int stunCnt_;

	// 防御力(hp-damage/防御力=damage)
	float defensePower_;

	// 最後に自分が当たった攻撃の種類
	ATTACK_TYPE lastHitType_;

	// ジャンプ力
	float jumpPow_;

	// 現在の状態
	STATUS status_;

	// 大きさ
	VECTOR scl_;

	// 角度
	VECTOR rot_;

	// 表示座標
	VECTOR pos_;

	// 敵の位置
	VECTOR enemyPos_;

	// 移動方向
	VECTOR dir_;

	// 空中ダッシュ方向
	VECTOR airDashDir_;

	// 実際に移動するベクトル
	VECTOR airDashVec_;


	// アニメーションをアタッチする番号
	int animAttachNo_;

	// アニメーションの総再生時間
	float animTotalTime_;

	// 再生中のアニメーション時間
	float stepAnim_;

	PlayerAnim playerAnim_;

	// アニメーション速度
	float speedAnim_;

	// 足元から衝突判定に使う球をどのぐらい移動させるか（基本的にYのみ）
	VECTOR collisionLocalPos_;

	// 重力
	float gravityPow_;

	// 生存判定
	bool isAlive_;

	bool invincible_;
	int invincibleCnt_;
	bool recovery_;
	int recoveryCnt_;


	// プレイヤー番号
	TYPE playerNumber_;

	// キーコンフィグ
	KEY_CONFIG keyConfig_;

	// プレイヤーから敵のX軸角度
	float PlEnAngleDegX;

	// 弾のモデルID
	int modelShotId_;
	int modelPodId_;
	int modelBombId_;
	int modelStageId_;
	int modelStageCoverId_;

	// 爆発の画像(本来は外部リソース用の管理クラスを作るべき。弾モデルも)
	int blastImgs_[BLAST_ANIM_NUM];

	int soundDamageH_;
	int soundShotH_;
	int soundBombH_;
	int soundPodH_;
	int soundTackleH_;


	// 弾方向のVECTOR
	VECTOR weaponDir_;
	VECTOR bombDir_;
	float bombDirX_;
	VECTOR shotLocalPos_;
	VECTOR weaponPos_;


	// ショット(ポインタ)
	std::vector<std::shared_ptr<WeaponBase>> shots_;
	std::vector<std::shared_ptr<WeaponBase>> bombs_;
	std::vector<std::shared_ptr<WeaponBase>> pods_;

	int newPod = 0;

	// 敵との距離の長さ
	float PythagorasDisXZ_;

	// 体当たりするときの自分と敵のベクトル(ノーマライズされている)
	VECTOR attackPlEnVec_;


	// HPの各位の数字
	int hpHundredPlace_;
	int hpTensPlace_;
	int hpOnesPlace_;

	void DrawUI(void);

	// 攻撃処理
	void Fire(SHOT_TYPE shotType, BOMB_TYPE bombType, POD_TYPE podType);
	void Shot(SHOT_TYPE shotType);
	void Bomb(BOMB_TYPE bombType);
	void Pod(POD_TYPE podType);

	void Attack(void);

	// 移動処理
	void Move(void);
	void ProcessMove(void);
	void Accele(float speed);
	void Decelerate(void);

	// 向く角度処理
	void Turn(void);

	// ジャンプ操作
	void ProcessJump(void);

	// ジャンプ
	void Jump(void);

	// ジャンプ力を設定
	void SetJumpPow(float jumpPow);

	// 重力
	void AddGravity(void);

	// 空中ダッシュ
	void AirDash(void);

	// ホバー
	void Hover(void);
	void Stun(void);
	void RecoveryInit(void);
	void Recovery(void);

	// 弾の処理
	void ShotUpdate(void);

	void SoundPlayer(SE_TYPE type);

private:



};

