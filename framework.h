#pragma once

#include "targetver.h"
#include "Resource.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_WIDTH 1024 //해상도 X
#define WIN_HEIGHT 720 //해상도 Y
#define WIN_HALFWIDTH WIN_WIDTH * 0.5f
#define WIN_HALFHEIGHT WIN_HEIGHT * 0.5f
#define WIN_START_X 0 //프로그램 시작 위치 X
#define WIN_START_Y 0 //프로그램 시작 위치 Y

#define RED 0xffff0000
#define GREEN 0xff00ff00
#define BLUE 0xff0000ff
#define YELLOW 0xffffff00
#define CYAN 0xff00ffff
#define MAGENTA 0xffff00ff
#define WHITE 0xffffffff
#define BLACK 0xff000000

#define INPUTMANAGER InputManager::Get()
#define DELTA Timer::GetInstance()->GetElapsedTime()
#define NPC NpcManager::GetInstance()
#define ENEMY EnemyManager::GetInstance()
#define PATICLE PaticleManager::GetInstance()
#define CURSUR MouseCursur::GetInstance()
#define BAR TweakBar::Get()->GetBar()

#include <windows.h>
#include <time.h>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <string>
#include <fstream>
#include <functional>
#include <algorithm>
#include <crtdbg.h>

using namespace std;
extern HWND hWnd;

//DirectX9
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//TweakBar
#pragma comment(lib, "Libraries/AntTweakBar.lib")
#include "Libraries/AntTweakBar.h"
#include "Libraries/TweakBar.h"

typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR4 Vector4;
typedef D3DXCOLOR Color;
typedef D3DXMATRIX Matrix;

enum Dir {
	NONE,
	UP,
	DOWN,
	RIGHT,
	LEFT
};

struct Vertex
{
	static const DWORD fvf = D3DFVF_XYZ | D3DFVF_TEX1;

	Vector3 position;
	Vector2 uv;

	D3DCOLOR color;

	Vertex() {}
	Vertex(float x, float y, float u, float v)
	{
		position = { x, y, 0 };
		uv = { u, v };
	}
};

//Framework ===

//Utility
#include "Framework/Utility/Operation.h"
#include "Framework/Utility/BinaryWriter.h"
#include "Framework/Utility/BinaryReader.h"
#include "Framework/Utility/Xml.h"

//System
#include "Framework/System/Device.h"
#include "Framework/System/Timer.h"
#include "Framework/System/World.h"
#include "Framework/Info.h"
#include "Framework/System/TextureEditor.h"
#include "Framework/System/WorldEditor.h"
#include "Framework/System/ObjectTool.h"
#include "Framework/System/MapEditor.h"

//IO
#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmod_vc.lib")

#include "Framework/IO/Output/SoundManager.h"
#include "Framework/IO/Output/Camera.h"
#include "Framework/IO/Output/Shader.h"
#include "Framework/IO/Output/Texture.h"
#include "Framework/IO/Output/TextureManager.h"
#include "Framework/IO/Output/Animation.h"
#include "Framework/IO/Output/Effect.h"
#include "Framework/IO/Output/EffectManager.h"
#include "Framework/IO/Output/ImageFont.h"
#include "Framework/IO/Output/RenderTarget.h"

#include "Framework/IO/Input/InputManager.h"
#include "Framework/IO/Input/Button.h"
#include "Framework/IO/Input/UIButton.h"

#include "Framework/Utility/DataManager.h"

//Entity
#include "Game/Entity/Object.h"

//Buff
#include "Game/Entity/Buff/BuffEffect.h"
#include "Game/Entity/Buff/BuffIcon.h"
#include "Game/Entity/Buff/BuffManager.h"

//Npc
#include "Game/Entity/Npc/Npc.h"
#include "Game/Entity/Npc/BlackSmith.h"
#include "Game/Entity/Npc/FolkOne.h"
#include "Game/Entity/Npc/FolkTwo.h"
#include "Game/Entity/Npc/ChildMan1.h"
#include "Game/Entity/Npc/ChildMan2.h"
#include "Game/Entity/Npc/ChildWoman1.h"
#include "Game/Entity/Npc/ChildWoman2.h"
#include "Game/Entity/Npc/Cat.h"
#include "Game/Entity/Npc/NpcManager.h"

//Enemy
#include "Game/Entity/Enemy/Enemy.h"
#include "Game/Entity/Enemy/Forest/ChiCken.h"
#include "Game/Entity/Enemy/Forest/Pig.h"
#include "Game/Entity/Enemy/Forest/Slime.h"
#include "Game/Entity/Enemy/Mountain/Flower_Bullet.h"
#include "Game/Entity/Enemy/Mountain/Flower.h"
#include "Game/Entity/Enemy/Mountain/MushRoom.h"
#include "Game/Entity/Enemy/Mountain/Goblin.h"

//Enemy(Mage)
#include "Game/Entity/Enemy/Cave/Mage_Emote.h"
#include "Game/Entity/Enemy/Cave/Mage_EyeLaser.h"
#include "Game/Entity/Enemy/Cave/Mage_Eye.h"
#include "Game/Entity/Enemy/Cave/Mage_FireBall.h"
#include "Game/Entity/Enemy/Cave/Mage_BlackBall.h"
#include "Game/Entity/Enemy/Cave/Mage.h"

#include "Game/Entity/Enemy/EnemyManager.h"

//Player
#include "Game/Entity/Player/Portion.h"
#include "Game/Entity/Player/Player.h"

//UI
#include "Game/GUI/UIObject.h"
#include "Game/GUI/Cursor.h"

#include "Game/ItemTest/Item.h"
#include "Game/ItemTest/ItemImage.h"
#include "Game/ItemTest/ItemInfo.h"
#include "Game/ItemTest/ItemSlot.h"

#include "Game/GUI/GetItemWindow.h"
#include "Game/GUI/GWManager.h"
#include "Game/GUI/ItemNotice.h"
#include "Game/GUI/HotBar.h"
#include "Game/GUI/QuickSlot.h"
#include "Game/GUI/StateBar.h"
#include "Game/GUI/BossHpBar.h"
#include "Game/GUI/InvenTab.h"
#include "Game/GUI/Inventory.h"
#include "Game/GUI/BuyWindow.h"
#include "Game/GUI/SellWindow.h"
#include "Game/GUI/Store.h"
#include "Game/GUI/Cauldron.h"
#include "Game/GUI/UI.h"

//Field
#include "Game/Field/Particle.h"
#include "Game/Field/PaticleManager.h"
#include "Game/Field/Home/Home.h"
#include "Game/Field/Town/Town.h"
#include "Game/Field/Forest/Forest.h"
#include "Game/Field/Mountain/Mountain.h"
#include "Game/Field/Cave/Cave.h"

//Scene
#include "GameManager/Scene/Scene.h"
#include "GameManager/Scene/SceneManager.h"

#include "Game/Field/Home/HomeScene.h"
#include "Game/Field/Town/TownScene.h"
#include "Game/Field/Forest/ForestScene.h"
#include "Game/Field/Mountain/MountainScene.h"
#include "Game/Field/Cave/CaveScene.h"

//GameManager
#include "GameManager/GameManager.h"