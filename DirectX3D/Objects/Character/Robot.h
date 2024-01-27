#pragma once
class Robot 
{
private:

	enum State
	{
		STAND_UP, 
		WALK,
		RUN,
		HIT,
		DYING
	};

public:
//	Robot(); // �⺻ ����
	Robot(Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
	~Robot();

	void Update();
	void Render();
	void PostRender();

	// �׼� 
	void Hit();
	void Spawn(Vector3 pos);
	void SetTarget(Transform* target);

	Transform* GetTransform() { return transform; }
	CapsuleCollider* GetCollider() { return collider; }

private:
	void SetEvent(int clip, Event event, float timeRatio);
	void ExecuteEvent();

	void EndStandUp();
	void EndHit();
	void EndDying();

	void SetState(State state);

	void Move();
	void UpdateUI(); //


private:
	Transform* transform = nullptr;
	CapsuleCollider* collider = nullptr;

	// �ָ���
	Transform* root = nullptr;
	Transform* target = nullptr;

	//
	ModelAnimatorInstancing* instancing = nullptr;
	ModelAnimatorInstancing::Motion* motion;

	// ���� ��� �����
	float speed = 50;
	float maxHp = 100;
	float curHP = 100;

	Vector3 velocity = { 0, 0, 0 };
	// ������Ʈ�� ���� ������

	UINT index = 0;
	State curState = STAND_UP;

	// ������Ʈ Ȥ�� �����ӿ� ���� �̺�Ʈ ����
	vector<map<float, Event>> totalEvent;
	vector<map<float, Event>::iterator> eventIters;


};

