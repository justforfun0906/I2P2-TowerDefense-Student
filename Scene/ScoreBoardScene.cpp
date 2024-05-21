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
#include <fstream>
#include <sstream>


void ScoreBoardScene::Initialize() {
	// TODO: [HACKATHON-1-SCENE] (1/4): You can imitate the 2 files: 'LoseScene.hpp', 'LoseScene.cpp' to implement your start scene.
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	AddNewObject(new Engine::Label("Leader Board", "pirulen.ttf", 48, halfW, halfH / 4 + 10, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 1));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
	//TODO: change the BGM
	bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);

	//leaderboard body
	std::ifstream fin("Resource/scoreboard.txt");

    // Check if the file was opened successfully.
    if (!fin) {
        throw std::runtime_error("Unable to open scoreboard file");
    }

    // Read data from the file.
    std::string line;
	int i = 0;
    while (std::getline(fin, line)) {
        // Process the line. For example, you could split it into a name and a score.
        std::istringstream iss(line);
        std::string name;
        int score;
        if (!(iss >> name >> score)) {
            throw std::runtime_error("Scoreboard file is corrupted");
        }

        // TODO: Use the name and score.
		std::string text = name + ": " + std::to_string(score);
        int y = halfH / 4 + 10 + 50 * (i + 1);  // Calculate the y position of the label.
        AddNewObject(new Engine::Label(text, "pirulen.ttf", 32, halfW, y, 255, 255, 255, 255, 0.5, 0.5));

        i++;
    }

    // Close the file.
    fin.close();
}
void ScoreBoardScene::Terminate() {
	AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}
void ScoreBoardScene::BackOnClick(int stage) {
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("start");
}
