#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"
#include "GameObjectClass.h"
#include "Agent8.h"
#include "StateBaseClass.h"
#include "StateAppear.h"

#include "Factory.h"

int DISPLAY_WIDTH = 1280;
int DISPLAY_HEIGHT = 720;
int DISPLAY_SCALE = 1;

struct GameState
{
	int score = 0;
	Agent8* player = nullptr;
};

GameState gameState;

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	GameObjectClass::SetScorePointer(&gameState.score); // Getting a pointer to the gameState's score so we can access it from all classes using GameObjectClass

	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();
	Play::LoadBackground("Data\\Backgrounds\\background.png");
	Play::StartAudioLoop("music");
	Agent8* player = (Agent8*)Factory::ReturnCreateObject(TYPE_AGENT8, { 115, 0 });
	Factory::CreateObject(TYPE_FAN, { 1130, 250 });

	gameState.player = player;
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::DrawBackground();
	GameObjectClass::UpdateAll();
	GameObjectClass::UpdateAllDestroyed();
	GameObjectClass::RenderAll();
	GameObjectClass::CleanUp();

	Play::DrawFontText("64px", "ARROW KEYS TO MOVE UP AND DOWN AND SPACE TO FIRE",
		{ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 30 }, Play::CENTRE);
	Play::DrawFontText("132px", "SCORE: " + std::to_string(gameState.score),
		{ DISPLAY_WIDTH / 2, 50 }, Play::CENTRE);

	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	//delete gameState.state;
	GameObjectClass::DeleteAll();
	Play::DestroyManager();
	return PLAY_OK;
}

