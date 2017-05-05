
#pragma once

#include "DeferredOutputShader.h"
#include "DeferredInputShader.h"
#include "FirstPersonCamera.h"
#include "GeometryBuffer.h"
#include "DefaultCamera.h"
#include "Heightmap.h"
#include "Skybox.h"
#include "Model.h"
#include "Cube.h"
#include "GPU.h"

class DeferredRenderer
{
    DeferredOutputShader secondPassShader;
    DeferredInputShader firstPassShader;
    GeometryBuffer* gbuffer;
    ModelAsset sphereAsset;
    Camera* sceneCamera;
    CameraType cameraType;

    std::vector<PointLight> pointLights;
    glm::vec3 lightPosition;
    glm::vec3 lightColour;

    Transfer * sphere;
    Transfer * quad;
    GLuint lID;
public:
    DeferredRenderer();
    ~DeferredRenderer();

    CameraType getCameraType();

    void setMatrixForObject(const char *, glm::mat4&);
    void handleTerrainHeight(Heightmap * heightmap);
    void setCameraPosition(glm::vec3 positions);
    void changeCamera(CameraType newCamera);
    void createRenderer(int width, int height);
    void updateCamera(SDL_Event& event);
    void repositionCamera();
    void pushLights(std::vector<PointLight>& pointLights);
    void renderSkybox(Skybox * skybox);
    void renderMap(Heightmap * map);
    void renderModel(Model * model);
    void renderCube(Cube *  cube);
    void constructUBO();
    void prepare();
    void present();

    glm::vec3& getLightPosition();
    glm::vec3& getLightColour();
};