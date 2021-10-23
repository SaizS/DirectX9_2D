#include "framework.h"

Player::Player() : color(1, 1, 1, 1), speed(300), isDamage(false), damageDistance(250),
damageAngle(0.0f), collectTime(0.0f), isCollect(false)
{
	LoadActions();

	shader = Shader::Add(L"Shader/Object.hlsl");

	state = DOWNIDLE;
	actions[state]->Play();

	hitBox = new World();

	pos = { WIN_HALFWIDTH, WIN_HALFHEIGHT };
	offset = { 0, 20 };
	SetCollider({ 20,10 });
	scale = { 1, 1 };

	maxHp = 100;
	hp = 100;
	def = 0;
	atk = 5;

	GUI->SetHp(&hp, &maxHp);

	hitBox->pos = pos;
	hitBox->SetCollider({ 20, 50 });

	for (int i = 0; i < POTION_COUNT; i++)
		portions.push_back(new Potion());
	//portions.emplace_back();

	standardAngle = { -((PI * 0.5) + (PI * 0.25)), -(PI * 0.25f), (PI * 0.5) + (PI * 0.25), PI * 0.25 }; // LT, RT, LB, RB

	bm = new BuffManager(this);
	bm->SetParent(&world);
	bm->SetOffset(0, -45);
}

Player::~Player()
{
	for (Animation* ani : actions)
		delete ani;
	for (Potion* portion : portions)
		delete portion;

	delete hitBox;
}

void Player::Update()
{
	if (hp > maxHp)
		hp = maxHp;

	SetFade();

	for (int i = 0; i < POTION_COUNT; i++) {
		if (!portions[i]->GetIsActive())
			portions[i]->pos = pos;
	}
	SetPortion();
	CollectPaticle();

	Move();
	Attack();
	KnockBack();
	Die();

	hitBox->pos = pos;
	hitBox->Update();
	bm->Update();

	actions[state]->Update();
	World::Update();

	for (Effect* effect : EFFECT->GetEffect("GetEffect"))
		effect->Update();
}

void Player::Render()
{
	SetWorld();

	shader->SetTexture("map", actions[state]->GetTexture());
	shader->SetVector("color", &color, 4);
	shader->Begin();
	actions[state]->Render();
	shader->End();

	bm->Render();

	for (Effect* effect : EFFECT->GetEffect("GetEffect"))
		effect->Render();
}

void Player::Move()
{
	if (isDamage || isDie || CURSCENE->GetIsFadeIn() || CURSCENE->GetIsFadeOut())
		return;

	if (state == UPATTACK || state == DOWNATTACK || state == LEFTATTACK || state == RIGHTATTACK)
		return;

	if (bm->BuffCheck(BUFFTYPE::FREEZE) ||
		bm->BuffCheck(BUFFTYPE::PARALYZE) ||
		GUI->GetStore()->isActive ||
		GUI->GetCauldron()->isActive) {
		switch (state)
		{
		case Player::UPRUN:
			SetActions(UPIDLE);
			break;
		case Player::DOWNRUN:
			SetActions(DOWNIDLE);
			break;
		case Player::LEFTRUN:
			SetActions(LEFTIDLE);
			break;
		case Player::RIGHTRUN:
			SetActions(RIGHTIDLE);
			break;
		default:
			break;
		}
		return;
	}

	if (KEYPRESS('W'))
	{
		pos.y -= speed * DELTA;
		SetActions(UPRUN);

		collectTime = 0;
	}

	if (KEYPRESS('S'))
	{
		pos.y += speed * DELTA;
		SetActions(DOWNRUN);

		collectTime = 0;
	}

	if (KEYPRESS('A'))
	{
		pos.x -= speed * DELTA;
		SetActions(LEFTRUN);

		collectTime = 0;
	}

	if (KEYPRESS('D'))
	{
		pos.x += speed * DELTA;
		SetActions(RIGHTRUN);

		collectTime = 0;
	}

	if (KEYUP('W'))
	{
		SetActions(UPIDLE);
	}

	if (KEYUP('S'))
	{
		SetActions(DOWNIDLE);
	}

	if (KEYUP('A'))
	{
		SetActions(LEFTIDLE);
	}

	if (KEYUP('D'))
	{
		SetActions(RIGHTIDLE);
	}
}
void Player::Attack()
{
	if (isDie || state == COLLECT || state == COLLECTING)
		return;
	if (GUI->UIClickCheck()) //좌클릭을 했을 때 그 위에 활성화된 UI가 있는 경우 참을 반환하는 함수 (state와 hotbar 같은 상시로 켜져있는 UI엔 적용되지 않습니다)
		return;
	if (bm->BuffCheck(BUFFTYPE::FREEZE))
		return;
	if (state == UPATTACK ||
		state == DOWNATTACK ||
		state == LEFTATTACK ||
		state == RIGHTATTACK)
		return;
	if (KEYDOWN(VK_LBUTTON))
	{
		if (GUI->GetInven()->GetSelectedPotion() == NULL || GUI->GetInven()->GetSelectedPotion()->key == -1) //선택된 포션이 없다면 함수 종료
			return;
		if (GUI->GetInven()->GetSelectedPotion()->key % 2 == 0) { //플라스크가 짝수, 물약이 홀수
			SOUND->Play("throw");
			GUI->GetInven()->GetSelectedPotion()->stack--;
			Vector2 attackVec = MOUSEPOS - pos;
			float attackAngle = atan2(attackVec.y, attackVec.x);

			if (attackAngle > standardAngle.x&& attackAngle < standardAngle.y)
				SetActions(UPATTACK);
			if (attackAngle > standardAngle.y&& attackAngle < standardAngle.w)
				SetActions(RIGHTATTACK);
			if (attackAngle > standardAngle.w&& attackAngle < standardAngle.z)
				SetActions(DOWNATTACK);
			if (attackAngle > standardAngle.z || attackAngle < standardAngle.x)
				SetActions(LEFTATTACK);

			Vector2 attackPos = pos;
			attackPos.x += cos(attackAngle) * 30;
			attackPos.y += sin(attackAngle) * 30;

			for (Potion* portion : portions)
			{
				if (!portion->GetIsActive())
				{
					portion->Fire(attackAngle, attackPos);
					break;
				}
			}
			//아이템 세이브
		}

		if (GUI->GetInven()->GetSelectedPotion()->key % 2 == 1) { //플라스크가 짝수, 물약이 홀수
			GUI->GetInven()->GetSelectedPotion()->stack--;
			SOUND->Play("potionDrink");
			bm->SetBuff(GUI->GetInven()->GetSelectedPotion()->effect);
			//아이템 세이브
		}

		for (Potion* portion : portions)
		{
			if (portion->GetIsActive())
			{
				if (portion->pos.x > pos.x + WIN_WIDTH || portion->pos.x < pos.x - WIN_WIDTH ||
					portion->pos.y > pos.y + WIN_HEIGHT || portion->pos.y < pos.y - WIN_HEIGHT)
				{
					portion->SetIsActive(false);
				}
			}
		}
	}
}

void Player::Die()
{
	if (hp <= 0 && !isDie)
	{
		isDie = true;
		switch (state)
		{
		case Player::UPIDLE:
			SetActions(UPDIE);
			break;
		case Player::DOWNIDLE:
			SetActions(DOWNDIE);
			break;
		case Player::LEFTIDLE:
			SetActions(LEFTDIE);
			break;
		case Player::RIGHTIDLE:
			SetActions(RIGHTDIE);
			break;
		case Player::UPRUN:
			SetActions(UPDIE);
			break;
		case Player::DOWNRUN:
			SetActions(DOWNDIE);
			break;
		case Player::LEFTRUN:
			SetActions(LEFTDIE);
			break;
		case Player::RIGHTRUN:
			SetActions(RIGHTDIE);
			break;
		case Player::UPATTACK:
			SetActions(UPDIE);
			break;
		case Player::DOWNATTACK:
			SetActions(DOWNDIE);
			break;
		case Player::LEFTATTACK:
			SetActions(LEFTDIE);
			break;
		case Player::RIGHTATTACK:
			SetActions(RIGHTDIE);
			break;
		case Player::COLLECT:
			SetActions(DOWNDIE);
			break;
		default:
			break;
		}
		GUI->GetInven()->SetGold(0);
		bm->ClearBuff();
		SCENE->DiePlayer();
	}
}

void Player::Damage(int damage, float angle)
{
	if (isDie || isDamage)
		return;

	if (!isDamage)
		isDamage = true;

	switch (state)
	{
	case Player::UPRUN:
		SetActions(UPIDLE);
		break;
	case Player::DOWNRUN:
		SetActions(DOWNIDLE);
		break;
	case Player::LEFTRUN:
		SetActions(LEFTIDLE);
		break;
	case Player::RIGHTRUN:
		SetActions(RIGHTIDLE);
		break;
	case Player::UPATTACK:
		SetActions(UPIDLE);
		break;
	case Player::DOWNATTACK:
		SetActions(DOWNIDLE);
		break;
	case Player::LEFTATTACK:
		SetActions(LEFTIDLE);
		break;
	case Player::RIGHTATTACK:
		SetActions(RIGHTIDLE);
		break;
	case Player::COLLECT:
	case Player::COLLECTING:
		SetActions(DOWNIDLE);
		collectTime = 0.0f;
		break;
	default:
		break;
	}
	if (damage - def < 1)
		damage = 1;
	else
		damage -= def;
	hp -= damage;
	if (bm->BuffCheck(17)) // 감전일때 추가 뎀지
		hp -= 3;
	damageAngle = angle;
	color = D3DXCOLOR(1, 0, 0, 1);
	SOUND->Play("PlayerDamage");
}

void Player::KnockBack()
{
	if (!isDamage || isDie)
		return;

	damageDistance -= 5;

	if (damageDistance < 200)
		color = D3DXCOLOR(1, 1, 1, 1);

	if (damageDistance <= 0)
	{
		isDamage = false;
		damageDistance = 250;
	}

	pos.x += cos(damageAngle) * damageDistance * DELTA;
	pos.y += sin(damageAngle) * damageDistance * DELTA;
}

void Player::SetActions(State dir)
{
	if (this->state != dir)
	{
		if (dir == COLLECT)
			EFFECT->Play("GetEffect", { hitBox->Left(), hitBox->Top() });
		this->state = dir;
		actions[dir]->Play();
	}
}

void Player::LoadActions()
{
	vector<Texture*> clips;

	//UPIDLE
	clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Idle/Idle - Up.png"));
	actions.push_back(new Animation(clips, Type::END));
	clips.clear();

	//DOWNIDLE
	clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Idle/Idle - Down.png"));
	actions.push_back(new Animation(clips, Type::END));
	clips.clear();

	//LEFTIDLE
	clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Idle/Idle - Left.png"));
	actions.push_back(new Animation(clips, Type::END));
	clips.clear();

	//RIGHTIDLE
	clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Idle/Idle - Right.png"));
	actions.push_back(new Animation(clips, Type::END));
	clips.clear();

	//UPRUN
	for (int i = 0; i < 6; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Run/Run - Up.png", i, 0, 6, 1));

	actions.push_back(new Animation(clips, Type::LOOP));
	clips.clear();

	//DOWNRUN
	for (int i = 0; i < 6; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Run/Run - Down.png", i, 0, 6, 1));

	actions.push_back(new Animation(clips, Type::LOOP));
	clips.clear();

	//LEFTRUN
	for (int i = 0; i < 6; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Run/Run - Left.png", i, 0, 6, 1));

	actions.push_back(new Animation(clips, Type::LOOP));
	clips.clear();

	//RIGHTRUN
	for (int i = 0; i < 6; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Run/Run - Right.png", i, 0, 6, 1));

	actions.push_back(new Animation(clips, Type::LOOP));
	clips.clear();

	//UPATTACK
	for (int i = 0; i < 4; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Attack/Attack - Up.png", i, 0, 4, 1));

	actions.push_back(new Animation(clips, Type::END, 0.07f));
	actions[UPATTACK]->SetEndEvent(bind(&Player::UpIdle, this));
	clips.clear();

	//DOWNATTACK
	for (int i = 0; i < 4; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Attack/Attack - Down.png", i, 0, 4, 1));

	actions.push_back(new Animation(clips, Type::END, 0.07f));
	actions[DOWNATTACK]->SetEndEvent(bind(&Player::DownIdle, this));
	clips.clear();

	//LEFTATTACK
	for (int i = 0; i < 4; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Attack/Attack - Left.png", i, 0, 4, 1));

	actions.push_back(new Animation(clips, Type::END, 0.07f));
	actions[LEFTATTACK]->SetEndEvent(bind(&Player::LeftIdle, this));
	clips.clear();

	//RIGHTATTACK
	for (int i = 0; i < 4; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Attack/Attack - Right.png", i, 0, 4, 1));

	actions.push_back(new Animation(clips, Type::END, 0.07f));
	actions[RIGHTATTACK]->SetEndEvent(bind(&Player::RightIdle, this));
	clips.clear();

	//UPDIE
	for (int i = 0; i < 5; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Die/Die - Up.png", i, 0, 5, 1));

	actions.push_back(new Animation(clips, Type::END, 0.07f));
	clips.clear();

	//DOWNDIE
	for (int i = 0; i < 5; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Die/Die - Down.png", i, 0, 5, 1));

	actions.push_back(new Animation(clips, Type::END, 0.07f));
	clips.clear();

	//LEFTDIE
	for (int i = 0; i < 5; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Die/Die - Left.png", i, 0, 5, 1));

	actions.push_back(new Animation(clips, Type::END, 0.07f));
	clips.clear();

	//RIGHTDIE
	for (int i = 0; i < 5; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Die/Die - Right.png", i, 0, 5, 1));

	actions.push_back(new Animation(clips, Type::END, 0.07f));
	clips.clear();

	//GET
	for (int i = 0; i < 6; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Get/Get.png", i, 0, 6, 1));

	actions.push_back(new Animation(clips, Type::END, 0.15f));
	actions[COLLECT]->SetEndEvent(bind(&Player::DownIdle, this));
	clips.clear();

	clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Get/Getting.png"));
	clips.push_back(TEXTURE->Add(L"Resource/Textures/Player/Get/Getting2.png"));

	actions.push_back(new Animation(clips, Type::LOOP, 0.15f));
}

void Player::SetPortion() // 포션 텍스쳐 가져오기
{
	if (GUI->GetInven()->GetSelectedPotion() == NULL) //인벤토리에 선택된 포션이 없으면 함수 종료
		return;
	for (Potion* portion : portions) //선택된 포션으로 모든 포션의 텍스쳐로 변경
		if (!portion->GetIsActive()) {
			portion->SetTexture(DATA->GetItemImage(GUI->GetInven()->GetSelectedPotion()->image + 200));
			portion->SetEffect(GUI->GetInven()->GetSelectedPotion()->effect);
		}
}

void Player::CollectPaticle()
{
	if (state != COLLECTING)
		return;

	collectTime += DELTA;

	if (collectTime > COLLECT_TIME)
	{
		if (actions[COLLECT]->GetClipNum() != 0)
			actions[COLLECT]->SetClipNum(0);
		collectTime = 0;
		SetActions(COLLECT);
		SOUND->Play("GetItem");
		curPaticle->SetIsActive(false);

		switch (curPaticle->GetStage())
		{
		case Paticle::FOREST:
			switch (OP::Random(0, 20))
			{
			case 0:
				GUI->GetInven()->GetItem(2); // 약초
			case 1:
			case 2:
				GUI->GetInven()->GetItem(2); // 약초
				break;
			case 3:
				GUI->GetInven()->GetItem(6); // 홍선화
				break;
			case 4:
				GUI->GetInven()->GetItem(3); // 해독초
			case 5:
			case 6:
				GUI->GetInven()->GetItem(3); // 해독초
				break;
			case 7:
				GUI->GetInven()->GetItem(7); // 청선화
				break;
			case 8:
				GUI->GetInven()->GetItem(4); // 청사과
			case 9:
			case 10:
				GUI->GetInven()->GetItem(4); // 청사과
				break;
			case 11:
				GUI->GetInven()->GetItem(5); // 해맞이풀
				break;
			case 12:
				GUI->GetInven()->GetItem(8); // 박화
				break;
			case 13:
				GUI->GetInven()->GetItem(12); // 갈색버섯
			case 14:
				GUI->GetInven()->GetItem(12); // 갈색버섯
			case 15:
				GUI->GetInven()->GetItem(12); // 갈색버섯
				break;
			case 16:
				GUI->GetInven()->GetItem(14); // 방귀버섯
				break;
			case 17:
				GUI->GetInven()->GetItem(13); // 점박이버섯
			case 18:
				GUI->GetInven()->GetItem(13); // 점박이버섯
				break;
			case 19:
				GUI->GetInven()->GetItem(15); // 저리버섯
				break;
			case 20:
				GUI->GetInven()->GetItem(62); // 녹심토
				break;
			default:
				break;
			}

			break;
		case Paticle::MOUNTAIN:
		{
			switch (OP::Random(0, 22))
			{
			case 0:
				GUI->GetInven()->GetItem(6); // 홍선화
			case 1:
				GUI->GetInven()->GetItem(6); // 홍선화
				break;
			case 2:
				GUI->GetInven()->GetItem(8); // 박화
			case 3:
				GUI->GetInven()->GetItem(8); // 박화
				break;
			case 4:
				GUI->GetInven()->GetItem(7); // 청선화
			case 5:
				GUI->GetInven()->GetItem(7); // 청선화
				break;
			case 6:
				GUI->GetInven()->GetItem(9); // 금사과
				break;
			case 7:
				GUI->GetInven()->GetItem(10); // 생명초
			case 8:
				GUI->GetInven()->GetItem(5); // 해맞이풀
			case 9:
				GUI->GetInven()->GetItem(5); // 해맞이풀
				break;
			case 10:
				GUI->GetInven()->GetItem(12); // 갈색버섯
			case 11:
				GUI->GetInven()->GetItem(12); // 갈색버섯
				break;
			case 12:
				GUI->GetInven()->GetItem(19); // 빙결버섯
				break;
			case 13:
				GUI->GetInven()->GetItem(14); // 방귀버섯
			case 14:
				GUI->GetInven()->GetItem(14); // 방귀버섯
				break;
			case 15:
				GUI->GetInven()->GetItem(15); // 저리버섯
			case 16:
				GUI->GetInven()->GetItem(15); // 저리버섯
				break;
			case 17:
				GUI->GetInven()->GetItem(20); // 폭발버섯
			case 18:
				GUI->GetInven()->GetItem(16); // 마비버섯
				break;
			case 19:
				GUI->GetInven()->GetItem(17); // 맹독버섯
			case 20:
				GUI->GetInven()->GetItem(17); // 맹독버섯
				break;
			case 21:
				GUI->GetInven()->GetItem(18); // 화끈버섯
				break;
			case 22:
				GUI->GetInven()->GetItem(63); // 홍련토
				break;
			default:
				break;
			}
		}

		break;
		default:
			break;
		}
		//GUI->inven->GetItem(key)
	}
}

void Player::SetFade()
{
	if (state == UPRUN)
		UpIdle();
	if (state == DOWNRUN)
		DownIdle();
	if (state == LEFTRUN)
		LeftIdle();
	if (state == RIGHTRUN)
		RightIdle();
}

void Player::Spawn()
{
	SetActions(DOWNIDLE);
	color = { 1,1,1,1 };
	pos = { WIN_HALFWIDTH, WIN_HALFHEIGHT };
	isDie = false;
	hp = maxHp;
	isDamage = false;
}