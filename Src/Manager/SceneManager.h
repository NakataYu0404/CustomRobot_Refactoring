#pragma once
#include <chrono>
#include <memory>
class SceneBase;
class CustomScene;
class GameScene;
class Fader;
class Camera;
class PlayerBase;

class SceneManager
{

public:

	// シーン管理用
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		CUSTOM,
		GAME
	};
	
	// インスタンスの生成
	static void CreateInstance(void);

	// インスタンスの取得
	static SceneManager& GetInstance(void);

	void Init(void);
	void Init3D(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	// 状態遷移
	void ChangeScene(SCENE_ID nextId);

	// シーンIDの取得
	SCENE_ID GetSceneID(void);

	// デルタタイムの取得
	float GetDeltaTime(void) const;

	// Cameraポインタを取得
	std::weak_ptr<Camera> GetCamera(void);

	static constexpr float DEFAULT_FPS = 60.0f;

	// 重力
	static constexpr float GRAVITY = 9.81f;

private:

	// 静的インスタンス
	static SceneManager* instance_;

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;

	// カメラ
	std::shared_ptr<Camera> camera_;

	// フェード
	std::unique_ptr<Fader> fader_;



	// 各種シーン
	std::shared_ptr<SceneBase> scene_;

	std::shared_ptr<CustomScene> custom_;
	std::shared_ptr<GameScene> game_;

	// シーン遷移中判定
	bool isSceneChanging_;

	// デルタタイム
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;
	
	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	SceneManager(void);
	// コピーコンストラクタも同様
	SceneManager(const SceneManager&);
	// デストラクタも同様
	~SceneManager(void);

	// デルタタイムをリセットする
	void ResetDeltaTime(void);

	// シーン遷移
	void DoChangeScene(SCENE_ID sceneId);

	// フェード
	void Fade(void);


	std::weak_ptr<PlayerBase> player_[2];
};