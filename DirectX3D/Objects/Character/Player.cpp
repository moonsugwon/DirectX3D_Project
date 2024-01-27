#include "Framework.h"
#include "Player.h"

Player::Player() : ModelAnimator("Player")
{
	mainHand = new Transform();
	root = new Transform();
	realPos = new Transform();
	tmpCollider = new SphereCollider();
	tmpCollider->Scale() *= 10.1f;
	tmpCollider->SetParent(root);

	//ReadClip("L_001");
	ReadClip("L_101");
	ReadClip("L_102");
	ReadClip("L_103");
	ReadClip("L_104");
	ReadClip("L_001");

	CAM->SetTarget(realPos);
}

Player::~Player()
{
	delete mainHand;
	delete root;
	delete realPos;
	delete tmpCollider;
}

void Player::Update()
{
	Control();
	Move();
	Rotate();

	root->SetWorld(GetTransformByNode(1));
	realPos->Pos() = GetTranslationByNode(1);	
	realPos->UpdateWorld();
	ModelAnimator::Update();
	tmpCollider->UpdateWorld();
}

void Player::Render()
{
	ModelAnimator::Render();
	tmpCollider->Render();
}

void Player::GUIRender()
{
	ModelAnimator::GUIRender();

	float t = GetClip(0)->GetRatio();
	ImGui::DragFloat("ratio_0", &t); 
	Vector3 pos = realPos->Pos();

	ImGui::DragFloat3("RealPos", (float*)&pos);

	// t = GetClip(1)->GetRatio();
	// ImGui::DragFloat("ratio_1", &t);

	//Matrix x = GetTransformByNode(0);
	//Vector3 S, R, T;
	//XMMatrixDecompose(S.GetValue(), R.GetValue(), T.GetValue(), x);
	//
	//string temp = "_Pos";
	//ImGui::DragFloat3(temp.c_str(), (float*)&T, 0.1f);
	//
	//temp = "_GlobalPos";
	//Vector3 globalPos = GetTranslationByNode(0);
	//ImGui::DragFloat3(temp.c_str(), (float*)&globalPos, 0.1f);
	//
	//temp = "Real_GlobalPos";
	//Vector3 Pos = root->GlobalPos();
	//ImGui::DragFloat3(temp.c_str(), (float*)&Pos, 0.1f);
}

void Player::PostRender()
{

}

void Player::Control()
{
	switch (curState)
	{
	case Player::L_001:
		L001();
		break;
	case Player::L_002:
		break;
	case Player::L_003:
		break;
	case Player::L_004:
		break;
	case Player::L_005:
		break;
	case Player::L_006:
		break;
	case Player::L_007:
		break;
	case Player::L_008:
		break;
	case Player::L_009:
		break;
	case Player::L_010:
		break;
	case Player::L_011:
		break;
	case Player::L_012:
		break;
	case Player::L_013:
		break;
	case Player::L_014:
		break;
	case Player::L_015:
		break;
	case Player::L_071:
		break;
	case Player::L_072:
		break;
	case Player::L_073:
		break;
	case Player::L_077:
		break;
	case Player::L_078:
		break;
	case Player::L_079:
		break;
	case Player::L_101:
		L101();
		break;
	case Player::L_102:
		L102();
		break;
	case Player::L_103:
		L103();
		break;
	case Player::L_104:
		L104();
		break;
	case Player::L_105:
		L105();
		break;
	case Player::L_106:
		break;
	case Player::L_107:
		break;
	case Player::L_108:
		break;
	case Player::L_109:
		break;
	case Player::L_110:
		break;
	case Player::L_111:
		break;
	case Player::L_112:
		break;
	case Player::L_113:
		break;
	case Player::L_114:
		break;
	case Player::L_115:
		break;
	case Player::L_116:
		break;
	case Player::L_117:
		break;
	case Player::L_118:
		break;
	case Player::L_119:
		break;
	case Player::L_120:
		break;
	case Player::L_121:
		break;
	case Player::L_122:
		break;
	case Player::L_123:
		break;
	default:
		break;
	}
}

void Player::Move()
{
}

void Player::Rotate()
{
	Vector3 forword = CAM->Back();
	//Rot().y = atan2(forword.x, forword.z);
}

void Player::Attack()
{
}

void Player::SetAnimation()
{
}

void Player::SetState(State state)
{
	if (curState == state)
		return;

	curState = state;
//	PlayClip(state);
}

void Player::Throw()
{
}

void Player::EndThrow()
{
}

void Player::ReadClips()
{
	ReadClip("L_001");
	ReadClip("L_002");
	ReadClip("L_003");
	ReadClip("L_004");
	ReadClip("L_005");
	ReadClip("L_006");
	ReadClip("L_007");
	ReadClip("L_008");
	ReadClip("L_009");
	ReadClip("L_010");
	ReadClip("L_011");
	ReadClip("L_012");
	ReadClip("L_013");
	ReadClip("L_014");
	ReadClip("L_015");
	ReadClip("L_071");
	ReadClip("L_072");
	ReadClip("L_073");
	ReadClip("L_077");
	ReadClip("L_078");
	ReadClip("L_079");
	ReadClip("L_101");
	ReadClip("L_102");
	ReadClip("L_103");
	ReadClip("L_104");
	ReadClip("L_105");
	ReadClip("L_106");
	ReadClip("L_107");
	ReadClip("L_108");
	ReadClip("L_109");
	ReadClip("L_110");
	ReadClip("L_111");
	ReadClip("L_112");
	ReadClip("L_113");
	ReadClip("L_114");
	ReadClip("L_115");
	ReadClip("L_116");
	ReadClip("L_117");
	ReadClip("L_118");
	ReadClip("L_119");
	ReadClip("L_120");
	ReadClip("L_121");
	ReadClip("L_122");
	ReadClip("L_123");
}

void Player::RecordLastPos()
{
	//Pos() = root->GlobalPos();
	Pos() = GetTranslationByNode(1);
}

void Player::L001()
{
	if (curState != L_001)
		SetState(L_001);

	if (GetClip(4)->isFirstPlay())
		PlayClip(4);

	if (KEY_DOWN(VK_LBUTTON))
	{
		Pos() = realPos->Pos();
		L101();
	}
}

void Player::L002()
{
}

void Player::L003()
{
}

void Player::L004()
{
}

void Player::L005()
{
}

void Player::L006()
{
}

void Player::L007()
{
}

void Player::L101()
{
	// 함수 호출 됐는데 상태는 아직 안변했다면 바꿔주기 == SetState
	if (curState != L_101)
		curState = L_101;

	// PlayClip 하는데 계속 반복해서 호출되면 모션 반복되니까 방지
	if(GetClip(0)->isFirstPlay())
		PlayClip(0);

	// 공격 모션이면 충돌판정

	// 

	if (GetClip(0)->GetRatio() > 60 )
	{
		GetClip(0)->ResetPlayTime();
		Pos() = realPos->Pos();

		L102();
	}



	// 해당 클립이 98% 이상 재생됐으면 if 조건 충족
	if (GetClip(0)->IsNearEnd())
	{
		GetClip(0)->ResetPlayTime();
		Pos() = realPos->Pos();
		L102();
	}


}

void Player::L102()
{
	if (curState != L_102)
		curState = L_102;

	if (GetClip(1)->isFirstPlay())
		PlayClip(1, motionSpeed);

	if (GetClip(1)->IsNearEnd(motionSpeed))
	{
		GetClip(1)->ResetPlayTime();
		Pos() = realPos->Pos();
		L103();
	}
}

void Player::L103()
{
	if (curState != L_103)
		curState = L_103;

	if (GetClip(2)->isFirstPlay())
		PlayClip(2, motionSpeed);

	if (GetClip(2)->IsNearEnd(motionSpeed))
	{
		GetClip(2)->ResetPlayTime();
		Pos() = realPos->Pos();
		L104();
	}
}

void Player::L104()
{
	if (curState != L_104)
		curState = L_104;

	if (GetClip(3)->isFirstPlay())
		PlayClip(3);

	if (GetClip(3)->IsNearEnd())
	{
		GetClip(3)->ResetPlayTime();
		Pos() = realPos->Pos();
		GetClip(0)->ResetPlayTime();
		L101();
	}
}

void Player::L105()
{

}
