
#include "Multiplayer.h"
#include "Networking.h"
#include "Scenes.h"

Multiplayer::Multiplayer(Bank * bank)
{
    this->bank = bank;
}

Multiplayer::~Multiplayer()
{
}

void Multiplayer::onRender(Renderer& renderer)
{
    renderer.renderTexture(&background);
    renderer.renderLabel(&servername);
    renderer.renderLabel(&hostname);
    renderer.renderLabel(&title);
    renderer.renderButton(&player1);
    renderer.renderButton(&player2);
}

void Multiplayer::onLoad(SceneManager&, Renderer& renderer)
{
    background.create(&renderer, "data/background.png");
    background.setPosition(0, 0, 1920, 1080);
    title.create(font, "Multiplayer", 300);
    title.setPosition(1920 / 2, 200, Alignment::CENTER);

    this->click = bank->popItem<Music>("mouse_click_music");

    player1.createL(font, "Player 1", 100);
    player1.setPosition(660, 600, 200, 200);
    player1.onClick(this);

    hostname.create(font, std::string("Your Hostname : ").append(getHostname()), 60);
    hostname.setPosition(10, 1000, Alignment::RIGHT);

    player2.createL(font, "Player 2", 100);
    player2.setPosition(1060, 600, 200, 200);
    player2.onClick(this);
}

void Multiplayer::onActivated(void * data)
{
    Button * clickedButton = static_cast<Button *>(data);

    click->play(0);

    if (&player1 == clickedButton)
    {
        OnlinePlayerMap * scene = (OnlinePlayerMap*)sceneManager->getScene(ONLINE_PLAYER_MAP);
        scene->giveDetails("PLAYER1", name.substr(1));
        sceneManager->setScene(ONLINE_PLAYER_MAP);
    }

    if (&player2 == clickedButton)
    {
        OnlinePlayerMap * scene = (OnlinePlayerMap*)sceneManager->getScene(ONLINE_PLAYER_MAP);
        scene->giveDetails("PLAYER2", name.substr(1));
        sceneManager->setScene(ONLINE_PLAYER_MAP);
    }
}

void Multiplayer::onUpdate(SceneManager& scenes, Renderer&)
{
    sceneManager = &scenes;
}

void Multiplayer::onEvent(SceneManager& scenes, SDL_Event * e)
{
    if (e->key.type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
    {
        scenes.setScene(MENU);
        click->play(0);
    }

    if (e->key.type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_BACKSPACE)
    {
        name.pop_back();
        if (name.empty() || name == "Type Opponents Hostname ..")
        {
            name = " ";
        }

        servername.create(font, name, 100);
        servername.setPosition(1920 / 2, 500, Alignment::CENTER);
    }

    if (e->type == SDL_TEXTINPUT) {
        if (name == "Enter opponents hostname ...")
        {
            name.clear();
        }

        name += e->text.text;

        servername.create(font, name, 100);
        servername.setPosition(1920 / 2, 500, Alignment::CENTER);
    }

    player1.onEvent(e);
    player2.onEvent(e);
}

void Multiplayer::onEnter()
{
    SDL_StartTextInput();

    name = "Type Opponents Hostname ...";

    servername.create(font, name, 100);
    servername.setPosition(1920 / 2, 500, Alignment::CENTER);
}

void Multiplayer::onExit()
{
    SDL_StopTextInput();
}
