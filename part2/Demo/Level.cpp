
#include "Level.h"

Level::Level(OperatingSystem * engine)
{
    window = &engine->aquireWindow();
    package = engine->acquireAssetManager()->grabLocalManager();
    package->grab({
        "data/grass.png",
        "data/heightmap.png",
        "data/Aller_Rg.ttf",
        "data/scheune.3DS",
        "data/front.png",
        "data/right.png",
        "data/back.png",
        "data/left.png",
        "data/top.png"
    });
}

Level::~Level()
{
    SAFE_RELEASE(package);
}

void Level::onCreate()
{
    terrain.create(package->getT("data/grass"), "data/heightmap.png", 1.0, 12.5);
    model.setModel(package->getM("data/scheune"));

    skybox.setDistance(500.0);
    skybox.createSkybox({
        package->getT("data/front"),
        package->getT("data/right"),
        package->getT("data/back"),
        package->getT("data/left"),
        package->getT("data/top"),
        package->getT("data/top")
    });

    renderer2D.createRenderer();

    renderer3D.createRenderer(window->getWidth(), window->getHeight());
    renderer3D.changeCamera(FIRST_PERSON);
    renderer3D.setCameraPosition(glm::vec3(0.0, 2.0, -35.0));
    renderer3D.getLightPosition() = glm::vec3(0.0, -0.5, 1.0);

    std::string labelText = "Features : Deferred rendering, multiple light types, heightmap generation, ";
    labelText += "light volumes and cubemaps";

    header.setFont(package->getL("data/Aller_Rg", 30, { 255, 255, 255 }), labelText.c_str());
    header.setArea(glm::vec2(1900, 30), ALIGNMENT::LEFT);

    switchButton.setButtonText(package->getL("data/Aller_Rg", 40, { 255, 255, 255 }), "Randomize Lights");
    switchButton.setArea(glm::vec4(10, 1030, 500, 200), ALIGNMENT::RIGHT);

    generateRandomLights();
}

void Level::onGameEvent(SDL_Event& e)
{
    renderer3D.updateCamera(e);

    if (switchButton.isPressed(e))
    {
        generateRandomLights();
    }
}

void Level::onUpdate()
{
    renderer3D.handleTerrainHeight(&terrain);
    renderer3D.repositionCamera();
}

void Level::onRender()
{
    glm::mat4 projectionMatrix = glm::mat4();
    glm::mat4 modelMatrix = glm::mat4();

    projectionMatrix = glm::perspective(75.0f, 1920.0f / 1080.0f, 0.1f, 1000.0f);

    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0, -2.05, 0.0));
    modelMatrix = glm::rotate(modelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.005, 0.005, 0.005));

    renderer3D.prepare();
    renderer3D.setMatrixForObject("projection", projectionMatrix);
    renderer3D.setMatrixForObject("model", modelMatrix);
    renderer3D.renderModel(&model);
    renderer3D.renderSkybox(&skybox);
    renderer3D.renderMap(&terrain);
    renderer3D.present();

    projectionMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(0.0, 1920.0, 0.0, 1080.0, -1.0, 1.0);

    renderer2D.prepare();
    renderer2D.setMatrixForObject("projection", projectionMatrix);
    renderer2D.setMatrixForObject("model", glm::mat4());
    renderer2D.renderButton(&switchButton);
    renderer2D.renderLabel(&header);
    renderer2D.present();
}

void Level::generateRandomLights()
{
    std::vector<PointLight> pointLights;
    pointLights.reserve(49);

    for (int i = -24; i < 32; i += 8)
    {
        for (int b = -24; b < 32; b += 8)
        {
            pointLights.push_back({
                8.0, glm::vec3(i, 0.0, b),
                generateRandomColour(),
                0.1f, 0.0f,	0.0f, 0.3f
            });
        }
    }

    renderer3D.pushLights(pointLights);
    renderer3D.constructUBO();
}

glm::vec3 Level::generateRandomColour()
{
    auto colour = glm::vec3(0);
    colour.r = ((rand() % 101) / 100.0f);
    colour.g = ((rand() % 101) / 100.0f);
    colour.b = ((rand() % 101) / 100.0f);
    return colour * glm::vec3(2.25);
}