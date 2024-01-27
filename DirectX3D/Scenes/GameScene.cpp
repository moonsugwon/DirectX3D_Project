#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	//naruto = new Naruto();
	player = new Player();
	ground = new Model("forest");
	ground->Scale() *= 10.0f;
	ground->UpdateWorld();

	sky = new SkyBox(L"Textures/Landscape/BlueSky.dds");
	sky->Scale() *= 100.0f;
	sky->UpdateWorld();

	//RobotManager::Get()->SetTarget(naruto);
	//CAM->SetTarget(player);

	clockFrame = new Quad(L"Textures/UI/ClockFrame.png");
	clockFrame->Pos() = { 80,640,0 };
	clockFrame->UpdateWorld();

    durability = new Quad(L"Textures/UI/Durability.png");
	durability->Pos() = { 200,600,0 };
	durability->UpdateWorld();

    durability_gauge = new Quad(L"Textures/UI/Durability_Gauge.png");
	durability_gauge->Pos() = { 200,600,0 };

    hpBar = new Quad(L"Textures/UI/HpBar.png");
	hpBar->Pos() = { 140,650,0 };

    idBar = new Quad(L"Textures/UI/IDBar.png");
	idBar->Pos() = { 220,680,0 };
	idBar->UpdateWorld();

    itemSlot = new Quad(L"Textures/UI/ItemSlot.png");
	itemSlot->Pos() = { 1160,120,0 };
	itemSlot->UpdateWorld();

    lsCoting = new Quad(L"Textures/UI/LSCoting.png");
	lsCoting->Pos() = { 340,600,0 };

    lsCoting2 = new Quad(L"Textures/UI/LSCoting2.png");
	lsCoting2->Pos() = { 340,600,0 };

    lsGauge = new Quad(L"Textures/UI/LSGauge.png");
	lsGauge->Pos() = { 340,600,0 };
	lsGauge->UpdateWorld();

    lsGauge2 = new Quad(L"Textures/UI/LSGauge2.png");
	lsGauge2->Pos() = { 347,600,0 };

    quickSlot = new Quad(L"Textures/UI/QuickSlot.png");
	quickSlot->Pos() = { 1000,120,0 };
	quickSlot->UpdateWorld();

    slingerBug = new Quad(L"Textures/UI/SlingerBug.png");
	slingerBug->Pos() = { 640,120,0 };

    staminarBar = new Quad(L"Textures/UI/StaminaBar.png");
	staminarBar->Pos() = { 140,630,0 };

}

GameScene::~GameScene()
{
	//RobotManager::Delete();

	delete player;

	delete ground;

	delete sky;
	
	delete clockFrame;
	delete durability;
	delete durability_gauge;
	delete hpBar;
	delete idBar;
	delete itemSlot;
	delete lsCoting;
	delete lsCoting2;
	delete lsGauge;
	delete lsGauge2;
	delete quickSlot;
	delete slingerBug;
	delete staminarBar;
}

void GameScene::Update()
{
//	RobotManager::Get()->Update();

	player->Update();
	durability_gauge->UpdateWorld();
	hpBar->UpdateWorld();
	lsCoting->UpdateWorld();
	lsCoting2->UpdateWorld();
	lsGauge2->UpdateWorld();
	slingerBug->UpdateWorld();
	staminarBar->UpdateWorld();
}

void GameScene::PreRender()
{
}

void GameScene::Render()
{
	// naruto->Render();
	// RobotManager::Get()->Render();
	// KunaiManager::Get()->Render();

	sky->Render();
	ground->Render();
	player->Render();
}

void GameScene::PostRender()
{
	//	naruto->PostRender();
	player->PostRender();

	clockFrame->Render();
	durability->Render();
	durability_gauge->Render();
	hpBar->Render();
	idBar->Render();
	itemSlot->Render();
	lsCoting->Render();
	lsCoting2->Render();
	lsGauge->Render();
	lsGauge2->Render();
	quickSlot->Render();
	slingerBug->Render();
	staminarBar->Render();
}

void GameScene::GUIRender()
{
	//   naruto->GUIRender();
	player->GUIRender();
}