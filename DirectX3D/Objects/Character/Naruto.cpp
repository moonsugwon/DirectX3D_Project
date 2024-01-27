#include "Framework.h"

Naruto::Naruto() : ModelAnimator("naruto")
{	



	mainHand = new Transform();
	tmpCollider = new SphereCollider();
	tmpCollider->Scale() *= 10.1f;
	tmpCollider->SetParent(mainHand);

	crosshair = new Quad(L"Textures/UI/cursor.png");
	crosshair->Pos() = { CENTER_X,CENTER_Y, 0 };
	crosshair->Scale() *= 0.3f;
	crosshair->UpdateWorld();

	ReadClip("IDLE");
	ReadClip("Run");
	ReadClip("RunBack");
	ReadClip("RunLeft");
	ReadClip("RunRight");
	ReadClip("THROW");
	ReadClip("Punching");

	FOR(10)
	{
		Model* kunai = new ModelInstancing("Kunai");
		kunai->SetParent(mainHand);
		kunais.push_back(kunai);
	}
	

	GetClip(THROW)->SetEvent(bind(&Naruto::Throw, this), 0.7f);
	GetClip(THROW)->SetEvent(bind(&Naruto::EndThrow, this), 0.9f);

	GetClip(PUNCH)->SetEvent(bind(&Naruto::EndThrow, this), 0.9f);
}

Naruto::~Naruto()
{
	delete crosshair;
	delete mainHand;
	delete tmpCollider;
}

void Naruto::Update()
{
	Control();
	SetAnimation();
	mainHand->SetWorld(GetTransformByNode(38));

	ModelAnimator::Update();
	tmpCollider->UpdateWorld();


	for (auto& k : kunais)
	{
		if (k->Active())
			k->Pos() += Forward() * moveSpeed * DELTA;		
		k->UpdateWorld();
	}

	// TODO :  ���̰� ���� �߿��� ������ ���ư���_ �ƴ� ���� �������

	
}

void Naruto::Render()
{
	ModelAnimator::Render();
	tmpCollider->Render();
	for (auto& k : kunais)
	{
		if(k->Active())
			k->Render();
	}

}

void Naruto::GUIRender()
{
	ModelAnimator::GUIRender();

	string temp = "CAM";
	ImGui::DragFloat3(temp.c_str(), (float*)&CAM->Rot(), 0.1f);

}

void Naruto::PostRender()
{
	crosshair->Render();
}

void Naruto::Control()
{
	Rotate();
	Move();
	Attack();
}

void Naruto::Move()
{
	if (curState == THROW || curState == PUNCH) return; // ������ ���̸� ���� ���� ����

	bool isMoveZ = false; // ���� �̵� �� �ƴ�
	bool isMoveX = false; // �¿� �̵� �� �ƴ�

	if (KEY_PRESS('W'))
	{
		velocity.z += DELTA; // �ӵ�(���뺯��)�� ��Ÿ��ŭ ���İ� �ֱ�
		isMoveZ = true; //���� �̵� ���� ��
	}

	if (KEY_PRESS('S'))
	{
		velocity.z -= DELTA;
		isMoveZ = true; //���� �̵� ���� ��
	}

	if (KEY_PRESS('A'))
	{
		velocity.x -= DELTA;
		isMoveX = true; //�¿� �̵� ���� ��
	}

	if (KEY_PRESS('D'))
	{
		velocity.x += DELTA;
		isMoveX = true; //�¿� �̵� ���� ��
	}

	if (velocity.Length() > 1) //�ӵ��� ��ü ��ġ�� 1�� ������ (������ ǥ���� ������ ���̰� 1 �ʰ�)
		velocity.Normalize(); //����ȭ
	// ������ �Ÿ� : �� �ڵ尡 ���� ������....?

	if (!isMoveZ) // ���� �̵� ���� �ƴϸ�
		velocity.z = Lerp(velocity.z, 0, deceleration * DELTA); //������ ���� ����

	if (!isMoveX) // �¿��̵��� ����
		velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

	//�¿�ȸ���� ��İ�꿡 ���� ����� ���� ( = ���� ���ϱ�)
	Matrix rotY = XMMatrixRotationY(Rot().y);
	Vector3 direction = XMVector3TransformCoord(velocity, rotY); // ������ ������ ������ "����"�� ���� ���� ����

	Pos() += direction * -1 * moveSpeed * DELTA; //"����" ������ �̵�


}

void Naruto::Rotate()
{

	Vector3 forword = CAM->Back();

	if(curState != IDLE)
		Rot().y = atan2(forword.x, forword.z) ;
	
	//CAM->Rot().x -= delta.y * rotSpeed * DELTA;

}

void Naruto::Attack()
{
	if (curState == THROW)
		return;

	if (KEY_DOWN(VK_LBUTTON))
	{
		SetState(THROW);
	}
	if (KEY_DOWN(VK_RBUTTON))
	{
		SetState(PUNCH);
	}

	if (curState == THROW || curState == PUNCH)
	{
		vector<Robot*> robots = RobotManager::Get()->GetRobots();
		for (auto& r : robots)
		{
			if (tmpCollider->IsCollision(r->GetCollider()))
			{
				r->Hit();
			}
		}
	}
}

void Naruto::SetAnimation()
{
	if (curState == THROW || curState == PUNCH)
		return;

	if (velocity.z > 0.1f) // ���� �ӵ��� �����̶� ������
		SetState(RUN_F);
	else if (velocity.z < -0.1f) // ������ ���´� �¿��̵� ���º��� �켱�Ѵٴ� �ڵ�
		SetState(RUN_B);
	else if (velocity.x < -0.1f) // �¿� �߿��� ���� �켱
		SetState(RUN_L);
	else if (velocity.x > 0.1f) // ������ ������
		SetState(RUN_R);
	else // 4�� ���� ��� �������� (����) ����
		SetState(IDLE);

}

void Naruto::SetState(State state)
{
	if (curState == state)
		return;

	curState = state;
	PlayClip(state);

}

void Naruto::Throw()
{
	KunaiManager::Get()->Throw(tmpCollider->GlobalPos(), Back());
}

void Naruto::EndThrow()
{
	SetState(IDLE);
}
