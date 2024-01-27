#include "Framework.h"
#include "SkyBox.h"

SkyBox::SkyBox(wstring file)	
{
	// �ؽ��Ŀ� ���̴� ����
	skyMap = Texture::Add(file);
	//material->SetShader(L"basic/texture/hlsl");
	material->SetShader(L"landscape/Skybox.hlsl");

	FOR(2)
	{
		rasterizerState[i] = new RasterizerState();
		depthStencilState[i] = new DepthStencilState();
	}

	rasterizerState[1]->FrontCounterClockwise(true);
	// ȭ�� �켱���� ����
	depthStencilState[1]->DepthEnable(false);


}

SkyBox::~SkyBox()
{
	FOR(2)
	{
		delete rasterizerState[i];
		delete depthStencilState[i];
	}

}

void SkyBox::Render()
{
	skyMap->PSSet(10); 
	// 10 ���� ���� �켱 ������ �ȼ��� ���� �����
	
	// ��ī�̹ڽ��� �ɼ��� ����� ���¸� ȣ��
	rasterizerState[1]->SetState();
	depthStencilState[1]->SetState();

	Sphere::Render();

	rasterizerState[0]->SetState();
	depthStencilState[0]->SetState();
}
