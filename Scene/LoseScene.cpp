#include <functional>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "LoseScene.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "ScoreBoardScene.hpp"
#include "UI/Component/TextInput.hpp"

void LoseScene::Initialize() {
	// TODO: [HACKATHON-1-SCENE] (1/4): You can imitate the 2 files: 'LoseScene.hpp', 'LoseScene.cpp' to implement your start scene.
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	AddNewObject(new Engine::Label("You Lose :(", "pirulen.ttf", 48, halfW, halfH / 4 + 10, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&LoseScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    bgmInstance = AudioHelper::PlaySample("astronomia.ogg", false, AudioHelper::BGMVolume, PlayScene::DangerTime);

	// Create a TextInput object
    Engine::TextInput* input = new Engine::TextInput("Enter your name", "pirulen.ttf", 48, halfW-200, halfH * 3 / 4, 400, 100);

    // Add the TextInput object to the scene
    AddNewControlObject(input);
}
void LoseScene::Terminate() {
	AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}
void LoseScene::BackOnClick(int stage) {
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
