#include "framework.h"
#include "GameManager.h"

GameManager::GameManager()
{
	UI::Create();

	ENEMY->GetMage()->SetUI();

	player = new Player();

	ENEMY->SetPlayer(player);

	ResourceLoad();
	SCENE->Add("Home", new HomeScene(player));
	SCENE->Add("Town", new TownScene(player));
	SCENE->Add("Forest", new ForestScene(player));
	SCENE->Add("Mountain", new MountainScene(player));
	SCENE->Add("Cave", new CaveScene(player));

	CAM->SetTarget(player);

	SCENE->ChangeScene("Home", { WIN_HALFWIDTH, WIN_HALFHEIGHT });
	//SCENE->ChangeScene("Mountain", { 1006, 1156 });
}

GameManager::~GameManager()
{
	UI::Delete();
}

void GameManager::ResourceLoad() //리소스를 로드하는 함수. 이펙트나 사운드 같은 미리 정의해놓고 사용하는 리소스의 경우 정의 후 사용합시다
{
	SOUND->Add("btnPress", "Resource/SoundFx/btnPress.wav");
	SOUND->Add("btnPress2", "Resource/SoundFx/btnPress2.mp3");
	SOUND->Add("buzzer", "Resource/SoundFx/buzzer.wav");
	SOUND->Add("mouseWheel", "Resource/SoundFx/mouseWheel.wav");
	SOUND->Add("on", "Resource/SoundFx/powerOn.wav");
	SOUND->Add("off", "Resource/SoundFx/powerOff.wav");
	SOUND->Add("cash", "Resource/SoundFx/cash.wav");
	SOUND->Add("coin", "Resource/SoundFx/coin.mp3");
	SOUND->Add("Hit", "Resource/SoundFx/damage2.wav");
	SOUND->Add("PlayerDamage", "Resource/SoundFx/damage3.wav");
	SOUND->Add("PotionHit", "Resource/SoundFx/portionHit.WAV");
	SOUND->Add("potionDrink", "Resource/SoundFx/potionDrink.wav");
	SOUND->Add("GetItem", "Resource/SoundFx/itemGet.wav");
	SOUND->Add("GetItem2", "Resource/SoundFx/getItem2.mp3");
	SOUND->Add("extract", "Resource/SoundFx/extract.mp3");
	SOUND->Add("pushTab", "Resource/SoundFx/pushTab.mp3");
	SOUND->Add("water", "Resource/SoundFx/water.mp3");
	SOUND->Add("set", "Resource/SoundFx/Equip1.mp3");
	SOUND->Add("throw", "Resource/SoundFx/potionThrow.wav");

	SOUND->Add("heal", "Resource/SoundFx/PotionEffect/heal.wav");
	SOUND->Add("antidote", "Resource/SoundFx/PotionEffect/antidote.wav");
	SOUND->Add("regeneration", "Resource/SoundFx/PotionEffect/regeneration.wav");
	SOUND->Add("haste", "Resource/SoundFx/PotionEffect/haste.wav");
	SOUND->Add("cure", "Resource/SoundFx/PotionEffect/cure.wav");
	SOUND->Add("protect", "Resource/SoundFx/PotionEffect/protect.wav");
	SOUND->Add("poison", "Resource/SoundFx/PotionEffect/poison.wav");
	SOUND->Add("shockwave", "Resource/SoundFx/PotionEffect/shockwave.wav");
	SOUND->Add("shock", "Resource/SoundFx/PotionEffect/shock.wav");
	SOUND->Add("paralyze", "Resource/SoundFx/PotionEffect/paralyze.wav");
	SOUND->Add("burn", "Resource/SoundFx/PotionEffect/burn.wav");
	SOUND->Add("freeze", "Resource/SoundFx/PotionEffect/freeze.wav");
	SOUND->Add("explosion", "Resource/SoundFx/PotionEffect/explosion.wav");
	SOUND->Add("extinction", "Resource/SoundFx/PotionEffect/extinction.wav");
	SOUND->Add("hardening", "Resource/SoundFx/PotionEffect/hardening.wav");
	SOUND->Add("corrosion", "Resource/SoundFx/PotionEffect/corrosion.wav");
	SOUND->Add("slow", "Resource/SoundFx/PotionEffect/slow.wav");
	SOUND->Add("enhanceHp", "Resource/SoundFx/PotionEffect/enhance_hp.wav");
	SOUND->Add("void", "Resource/SoundFx/PotionEffect/void.wav");
	SOUND->Add("bleeding", "Resource/SoundFx/PotionEffect/bleeding.wav");

	SOUND->Add("MageTeleport", "Resource/SoundFx/Boss/bossTeleport.wav");
	SOUND->Add("FireBallHit", "Resource/SoundFx/Boss/fireHit.wav");
	SOUND->Add("FireBallShoot", "Resource/SoundFx/Boss/fireShoot.wav");
	SOUND->Add("FireBall8DirShoot", "Resource/SoundFx/Boss/fireShoot2.wav");
	SOUND->Add("BlackBallShoot", "Resource/SoundFx/Boss/blackBall.wav");
	SOUND->Add("LaserReady", "Resource/SoundFx/Boss/laserReady.wav");
	SOUND->Add("LaserBurst", "Resource/SoundFx/Boss/laserBurst.wav", true);
	SOUND->Add("RotationEye", "Resource/SoundFx/Boss/wheelEye.wav");
	SOUND->Add("MageDie", "Resource/SoundFx/Boss/bossDie.wav");

	SOUND->Add("Town", "Resource/Bgm/Town.mp3", true);
	SOUND->Add("Forest", "Resource/Bgm/Forest.mp3", true);
	SOUND->Add("Mountain", "Resource/Bgm/Mountain.mp3", true);
	SOUND->Add("Cave", "Resource/Bgm/Cave.mp3", true);

	EFFECT->Add("Hit", L"Resource/Textures/Effect/HitEffect.png", 5, 1, 50, 0.05f);
	EFFECT->Add("Poison", L"Resource/Textures/Effect/Poison.png", 4, 1, 30, 0.1f);
	EFFECT->Add("GetEffect", L"Resource/Textures/Effect/GetEffect2.png", 3, 1, 10, 0.1f);
}

void GameManager::Update()
{
	printf("%f %f \n", CAM->pos.x, CAM->pos.y);
	if (KEYDOWN(VK_F1))
		CURSCENE->SetFade("Home", { WIN_HALFWIDTH, WIN_HALFHEIGHT });
	if (KEYDOWN(VK_F2))
		CURSCENE->SetFade("Town", { 518,208 });
	if (KEYDOWN(VK_F3))
		CURSCENE->SetFade("Forest", { 1245, -862 });	
	if (KEYDOWN(VK_F4))
		CURSCENE->SetFade("Mountain", { -200, 400 });
	if (KEYDOWN(VK_F6))
		CURSCENE->SetFade("Cave", { 525, 440 });

	SCENE->Update();
	GUI->Update();
}

void GameManager::Render()
{	
	SCENE->Render();
}