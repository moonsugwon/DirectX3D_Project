#include "Framework.h"
#include "Kunai.h"

Kunai::Kunai(Transform* transform)
	: transform(transform)
{
	collider = new SphereCollider();
	collider->SetParent(transform);
	transform->Scale() *= 50.0f;

}

Kunai::~Kunai()
{
	delete collider;
}

void Kunai::Update()
{
	// ��Ȱ��ȭ �߿��� �ȿ�����
	if (!transform->Active())
	{
		return;
	}
	time += DELTA;
	if (time > LIFE_SPAN)
	{
		transform->SetActive(false);
	}
	transform->Pos() += direction * speed * DELTA;

	collider->UpdateWorld();
}

void Kunai::Render()
{
	collider->Render();
}

void Kunai::Throw(Vector3 pos, Vector3 dir)
{
	// Ȱ��ȭ
	transform->SetActive(true);

	transform->Pos() = pos;
	direction = dir;

	transform->Rot().y = atan2(dir.x, dir.z) - XM_PIDIV2;
	time = 0.0f;
}
