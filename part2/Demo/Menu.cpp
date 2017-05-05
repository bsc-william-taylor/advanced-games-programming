

#include "main.h"

Menu::Menu(OperatingSystem * system)
{
    scenes = system->acquireSceneManager();
    package = system->acquireAssetManager()->grabLocalManager();
    package->grab({
        "data/background.png",
        "data/Aller_Rg.ttf",
    });
}

Menu::~Menu()
{
    SAFE_RELEASE(package);
}

void Menu::onCreate()
{
    header.setFont(package->newFont("data/Aller_Rg", 150, { 255, 255, 255 }), "AGP Part 2 - B00235610");
    header.setArea(glm::vec2(1920 / 2, 900), ALIGNMENT::CENTER);

    playDemoButton.setButtonText(package->newFont("data/Aller_Rg", 100, { 255, 255, 255 }), "Start tech demo");
    playDemoButton.setArea(glm::vec4(1920 / 2 - 250, 300, 500, 100), ALIGNMENT::CENTER);

    background.setTexture(package->newTexture("data/background"));
    background.setArea(glm::vec4(0.0, 0.0, 1920, 1080));

    renderer2D.createRenderer();
}

void Menu::onGameEvent(SDL_Event& e)
{
    if (playDemoButton.isPressed(e))
    {
        scenes->switchScene((unsigned)SceneID::Level);
    }
}

void Menu::onUpdate()
{
}

void Menu::onRender()
{
    auto projectionMatrix = glm::mat4();
    auto modelMatrix = glm::mat4();

    projectionMatrix = glm::ortho(0.0, 1920.0, 0.0, 1080.0, -1.0, 1.0);

    renderer2D.prepare();
    renderer2D.setMatrixForObject("projection", projectionMatrix);
    renderer2D.setMatrixForObject("model", modelMatrix);
    renderer2D.renderTexture(&background);
    renderer2D.renderButton(&playDemoButton);
    renderer2D.renderLabel(&header);
    renderer2D.present();
}