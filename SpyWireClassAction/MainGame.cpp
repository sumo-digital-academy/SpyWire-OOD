#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"
#include "GameObjectClass.h"
#include "StateBaseClass.h"

#include "GameObjectManager.h"
#include "Agent8.h"

int DISPLAY_WIDTH = 1280;
int DISPLAY_HEIGHT = 720;
int DISPLAY_SCALE = 1;

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();
	Play::LoadBackground("Data\\Backgrounds\\background.png");
	Play::StartAudioLoop("music");
	GameObjectManager::CreateObject(TYPE_AGENT8, { 115, 0 }, { 0, 0 });
	GameObjectManager::CreateObject(TYPE_FAN, { 1130, 250 }, { 0, 3 });
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::DrawBackground();
	GameObjectManager::UpdateAll();
	GameObjectManager::UpdateAllDestroyed();
	GameObjectManager::RenderAll();
	GameObjectManager::CleanUp();

	Play::DrawFontText("64px", "ARROW KEYS TO MOVE UP AND DOWN AND SPACE TO FIRE",
		{ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 30 }, Play::CENTRE);
	Play::DrawFontText("132px", "SCORE: " + std::to_string(((Agent8*)GameObjectManager::GetPlayer())->GetScore()),
		{ DISPLAY_WIDTH / 2, 50 }, Play::CENTRE);

	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	//delete gameState.state;
	GameObjectManager::DeleteAll();
	StateBaseClass::DestroyEnd();
	Play::DestroyManager();
	return PLAY_OK;
}

