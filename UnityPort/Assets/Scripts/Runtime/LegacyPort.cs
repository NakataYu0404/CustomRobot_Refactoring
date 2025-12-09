using UnityEngine;

namespace CustomRobot.UnityPort
{
    /// <summary>
    /// Lightweight bootstrap that mirrors the original DxLib Application loop for Unity.
    /// Attach this to an empty GameObject in your startup scene.
    /// </summary>
    public class LegacyPort : MonoBehaviour
    {
        [SerializeField] private ResourceCatalog catalog;

        private IScene current;

        private void Awake()
        {
            if (catalog == null)
            {
                catalog = ScriptableObject.CreateInstance<ResourceCatalog>();
            }

            SwitchScene(new TitleScene(this, catalog));
        }

        private void Update()
        {
            current?.Tick(Time.deltaTime);
        }

        public void SwitchScene(IScene next)
        {
            current?.Exit();
            current = next;
            current?.Enter();
        }
    }

    internal interface IScene
    {
        void Enter();
        void Tick(float deltaTime);
        void Exit();
    }

    internal sealed class TitleScene : IScene
    {
        private readonly LegacyPort owner;
        private readonly ResourceCatalog catalog;
        private GameObject uiRoot;

        public TitleScene(LegacyPort owner, ResourceCatalog catalog)
        {
            this.owner = owner;
            this.catalog = catalog;
        }

        public void Enter()
        {
            uiRoot = new GameObject("TitleUI");
            var renderer = uiRoot.AddComponent<SpriteRenderer>();
            var tex = catalog.LoadTexture(ResourceCatalog.Id.Title);
            if (tex != null)
            {
                renderer.sprite = Sprite.Create(tex, new Rect(0, 0, tex.width, tex.height), new Vector2(0.5f, 0.5f), 100.0f);
            }
        }

        public void Tick(float deltaTime)
        {
            if (Input.anyKeyDown)
            {
                owner.SwitchScene(new GameScene(owner, catalog));
            }
        }

        public void Exit()
        {
            if (uiRoot != null)
            {
                Object.Destroy(uiRoot);
            }
        }
    }

    internal sealed class GameScene : IScene
    {
        private const string LabelText = "Game scene stub\nWire controls and characters here.";

        private readonly LegacyPort owner;
        private readonly ResourceCatalog catalog;
        private GameObject label;
        private AudioSource audioSource;

        public GameScene(LegacyPort owner, ResourceCatalog catalog)
        {
            this.owner = owner;
            this.catalog = catalog;
        }

        public void Enter()
        {
            label = new GameObject("GameSceneLabel");
            var mesh = label.AddComponent<TextMesh>();
            mesh.text = LabelText;
            mesh.fontSize = 48;
            mesh.anchor = TextAnchor.MiddleCenter;
            label.transform.position = Vector3.zero;

            audioSource = label.AddComponent<AudioSource>();
            audioSource.clip = catalog.LoadBgm(ResourceCatalog.Id.BgmBattle);
            if (audioSource.clip != null)
            {
                audioSource.loop = true;
                audioSource.Play();
            }
        }

        public void Tick(float deltaTime)
        {
            if (Input.GetKeyDown(KeyCode.Escape))
            {
                owner.SwitchScene(new TitleScene(owner, catalog));
            }
        }

        public void Exit()
        {
            if (audioSource != null)
            {
                audioSource.Stop();
            }

            if (label != null)
            {
                Object.Destroy(label);
            }
        }
    }

    [CreateAssetMenu(fileName = "ResourceCatalog", menuName = "CustomRobot/Resource Catalog", order = 0)]
    public class ResourceCatalog : ScriptableObject
    {
        public enum Id
        {
            Title,
            OnePWin,
            TwoPWin,
            BgmBattle,
            BgmVictory,
            SeDamage,
        }

        public Texture2D LoadTexture(Id id)
        {
            var path = GetResourcePath(id);
            return string.IsNullOrEmpty(path) ? null : Resources.Load<Texture2D>(path);
        }

        public AudioClip LoadBgm(Id id)
        {
            var path = GetResourcePath(id);
            return string.IsNullOrEmpty(path) ? null : Resources.Load<AudioClip>(path);
        }

        public AudioClip LoadSe(Id id)
        {
            var path = GetResourcePath(id);
            return string.IsNullOrEmpty(path) ? null : Resources.Load<AudioClip>(path);
        }

        private string GetResourcePath(Id id)
        {
            switch (id)
            {
                case Id.Title:
                    return "Image/Title";
                case Id.OnePWin:
                    return "Image/p1Win";
                case Id.TwoPWin:
                    return "Image/p2Win";
                case Id.BgmBattle:
                    return "Sound/BGM/Battle";
                case Id.BgmVictory:
                    return "Sound/BGM/Victory";
                case Id.SeDamage:
                    return "Sound/SE/Damage";
                default:
                    return null;
            }
        }
    }
}
