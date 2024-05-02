#pragma once
#include <DxLib.h>

class WeaponBase
{
public:

	// 衝突判定用の球体半径
	static constexpr float COL_RADIUS = 8.0f;

	// 弾の状態
	enum class STATE
	{
		NONE,
		SHOT,
		BLAST,
		END
	};

	// コンストラクタ
	WeaponBase(void);

	// デストラクタ
	virtual ~WeaponBase(void);

	// 弾の生成 Init込み
	void CreateWeapon(VECTOR pos, VECTOR dir,int plNum);

	void Init(int baseModelId, int* blastImgs, int blastAnimNum);

	// 更新ステップ
	void Update(void);

	// 描画
	void Draw(void);

	// 解放処理
	virtual void Release(void);

	// 弾判定
	virtual bool IsShot(void);

	// 生存判定
	bool IsAlive(void);

	// 爆発処理
	void Blast(void);
	void End(void);

	// ゲッター
	// 位置
	VECTOR GetPos(void);
	// 移動方向*1フレームの移動距離
	VECTOR GetMovePow(void);
	// ステータス
	STATE GetState(void);
	// 与ダメージ
	int GetHpDamage(void);
	int GetStunDamage(void);
	// 弾の半径(当たる判定に)
	virtual float GetRadius(void);
	// 方向
	VECTOR GetDir(void);

	// セッター
	// 位置
	void SetPos(VECTOR pos);
	// 敵との距離
	void SetDistance(float distance);
	// 敵の位置
	void SetEnemyPos(VECTOR pos);
	// 当たった地形の法線ベクトル
	void SetNormal(VECTOR normal);
	// プレイヤーに当たったかを設定
	void PlayerHit(bool isHit);
	// 角度
	void SetRot(VECTOR rot);

	void SetColor(int plNum);
protected:

	// 弾の大きさ
	VECTOR scl_;

	// 弾の移動速度
	float speed_;

	float gravityPow_;

	// 弾の状態
	STATE state_;

	// 元となる弾のモデルID
	int baseModelId_;

	// 弾のモデルID
	int modelId_;

	// 方向
	VECTOR dir_;

	// 弾の角度
	VECTOR rot_;

	// 弾の座標
	VECTOR pos_;
	VECTOR movePow_;

	// 発射時点の座標
	VECTOR posFire_;

	VECTOR enemyPos_;

	int hpDamage_;
	int stunDamage_;

	// 爆発アニメーション画像配列のポインタ
	int* blastImgs_;

	// 爆発アニメーション数
	int blastAnimNum_;

	// 爆発のアニメーション用カウンタ
	int blastCntAnim_;

	// 爆発のアニメーション番号
	int blastIdxAnim_;

	// 爆発のアニメーション速度
	float blastSpeedAnim_;

	// 何にも当たらずに飛び続けたときの限界フレーム
	int ShotBlastMax_;
	int ShotBlastCnt_;

	float plEnDistance_;

	bool isJump_;

	VECTOR hitNormal_;

	bool playerHit_;

	virtual void SetParam(void);
	virtual	void UpdateWeapon(void);
	virtual void UpdateBlast(void);
	void UpdateEnd(void);

	virtual void DrawShot(void);
	virtual void DrawBlast(void);
	void DrawEnd(void);

	// 状態遷移
	void ChangeState(STATE state);

	COLOR_F weaponColor_[2];

	int plNum_;
private:

};

