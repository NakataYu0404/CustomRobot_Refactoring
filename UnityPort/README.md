Unity port starter kit
======================

This repository originally targets DxLib. To help move the project into Unity, a minimal starter kit is provided under `UnityPort/Assets/Scripts/Runtime`. It mirrors the existing `Application` and scene flow so you can drop assets in and iterate in the Editor.

Quick start
-----------
1. Create a new Unity 3D project (2021.3 LTS or later).
2. Copy the `Data` folder from this repository into your Unity project's `Assets/Resources` directory, preserving the sub-folders (`Image`, `Model`, `Sound/BGM`, `Sound/SE`, `Effect`). Unity will import the textures, audio clips, and models automatically.
3. Copy `UnityPort/Assets/Scripts/Runtime/LegacyPort.cs` into your project's `Assets/Scripts/Runtime/` directory.
4. In your startup scene, add an empty `GameObject` and attach the `LegacyPort` component. Press Play:
   - The Title image (`Image/Title.png`) is shown via `Resources.Load`.
   - Press any key to enter the stub Game scene.
   - Press `Esc` to return to the Title scene.

How the stub works
------------------
- `LegacyPort` emulates the DxLib `Application` loop using Unity's `MonoBehaviour.Update`.
- `ResourceCatalog` maps a subset of the original `ResourceManager::SRC` identifiers to Unity `Resources` paths so assets can be loaded without hard-coding extensions.
- `TitleScene` simply shows the title sprite; `GameScene` demonstrates how to start BGM playback and swap scenes. Extend these classes with player, stage, and weapon behaviours as you migrate functionality.

Resource path mapping (initial subset)
--------------------------------------
- `Image/Title` -> `Data/Image/Title.png`
- `Image/p1Win` -> `Data/Image/p1Win.png`
- `Image/p2Win` -> `Data/Image/p2Win.png`
- `Sound/BGM/Battle` -> `Data/Sound/BGM/Battle.mp3`
- `Sound/BGM/Victory` -> `Data/Sound/BGM/Victory.mp3`
- `Sound/SE/Damage` -> `Data/Sound/SE/Damage.mp3`

Extend the `Id` enum and `GetResourcePath` switch inside `ResourceCatalog` as you port additional assets (characters, weapons, stage models, UI, etc.).

Notes for import settings
-------------------------
- Textures used for UI (numbers, HP bars, title) should use Sprite (2D and UI) mode with point filtering to preserve pixel edges.
- 3D models (`Data/Model`) can be imported as generic meshes; set scale to `1` and enable normals for proper lighting.
- Audio clips in `Sound/BGM` are configured to loop; `Sound/SE` are single-shot.
