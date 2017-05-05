
#include "DeferredRenderer.h"
#include "FirstPersonCamera.h"

DeferredRenderer::DeferredRenderer()
    : sphereAsset("no-name")
{
    sceneCamera = new DefaultCamera();
    lightPosition = glm::vec3(1.0, 0.0, 0.0);
    lightColour = glm::vec3(0.4, 0.4, 0.4);
    cameraType = CameraType::DefaultCamera;
}

DeferredRenderer::~DeferredRenderer()
{
    SAFE_RELEASE(sceneCamera);
    SAFE_RELEASE(gbuffer);
    SAFE_RELEASE(sphere);
    SAFE_RELEASE(quad);
}

void DeferredRenderer::createRenderer(int w, int h)
{
    sphereAsset.grabFromFile("data/sphere.obj");

    std::vector<glm::vec3> area = {
        glm::vec3(-1.0, -1.0, 0.0), glm::vec3(-1.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 0.0),
        glm::vec3(-1.0, -1.0, 0.0), glm::vec3(1.0, -1.0, 0.0), glm::vec3(1.0, 1.0, 0.0)
    };

    quad = new Transfer();
    quad->setVertices(area);
    quad->send();

    sphere = new Transfer();
    sphere->setVertices(sphereAsset.getVertices());
    sphere->send();

    secondPassShader.compile();
    firstPassShader.compile();

    gbuffer = new GeometryBuffer();
    gbuffer->setupGeometryBuffer(w, h);
    glGenBuffers(1, &lID);
}

glm::vec3& DeferredRenderer::getLightPosition()
{
    return lightPosition;
}

glm::vec3& DeferredRenderer::getLightColour()
{
    return lightColour;
}

void DeferredRenderer::prepare()
{
    gbuffer->startFrame();
    gbuffer->prepareForWriting();

    Program * program = firstPassShader.getProgram();

    program->bindShader();
    program->setMatrix("view", glm::value_ptr(sceneCamera->getView()));
    program->setInteger("sampler_index", 0);

    glUniform1i(glGetUniformLocation(program->getID(), "sampler"), 0);
    glUniform1i(glGetUniformLocation(program->getID(), "cubeMap"), 1);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
    glCullFace(GL_BACK);
}

void DeferredRenderer::pushLights(std::vector<PointLight>& pointLights)
{
    this->pointLights.clear();

    for (auto& pointLight : pointLights)
    {
        this->pointLights.push_back(pointLight);
    }
}

void DeferredRenderer::present()
{
    glDisable(GL_CULL_FACE);
    glDepthMask(GL_FALSE);

    glEnable(GL_STENCIL_TEST);
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);

    secondPassShader.getProgram()->bindShader();
    secondPassShader.getProgram()->setVector("screenSize", gbuffer->getBufferSize());

    auto projectionMatrix = glm::mat4();
    auto modelMatrix = glm::mat4();
    auto view = glm::mat4();

    GLuint ID = 0;
    for (auto light : pointLights)
    {
        auto lightPos = light.pointPosition / glm::vec3(light.area, light.area, light.area);

        projectionMatrix = glm::perspective(75.0f, 1920.0f / 1080.0f, 0.1f, 1000.0f);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(light.area, light.area, light.area));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.15, -1.0, 0.4));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(lightPos));

        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_STENCIL_BUFFER_BIT);
        glStencilFunc(GL_ALWAYS, 0, 0);
        glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
        glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);

        secondPassShader.prepare(sphere->getID());
        secondPassShader.getProgram()->setInteger("lightPass", -1);
        secondPassShader.getProgram()->setMatrix("projectionMatrix", glm::value_ptr(projectionMatrix));
        secondPassShader.getProgram()->setMatrix("model", glm::value_ptr(modelMatrix));
        secondPassShader.getProgram()->setMatrix("view", glm::value_ptr(sceneCamera->getView()));
        secondPassShader.run(NULL, sphereAsset.getMeshLength(NULL));

        gbuffer->prepareForReading();

        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
        glDisable(GL_DEPTH_TEST);

        secondPassShader.prepare(sphere->getID());
        secondPassShader.getProgram()->setInteger("lightPass", 1);
        secondPassShader.getProgram()->setInteger("pointID", ID);
        secondPassShader.run(NULL, sphereAsset.getMeshLength(NULL));

        glDisable(GL_CULL_FACE);
        modelMatrix = glm::mat4();
        ++ID;
    }

    glDisable(GL_STENCIL_TEST);
    glDisable(GL_DEPTH_TEST);

    gbuffer->prepareForReading();

    projectionMatrix = glm::ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    secondPassShader.getProgram()->setMatrix("projectionMatrix", glm::value_ptr(projectionMatrix));
    secondPassShader.getProgram()->setMatrix("model", glm::value_ptr(modelMatrix));
    secondPassShader.getProgram()->setMatrix("view", glm::value_ptr(view));
    secondPassShader.getProgram()->setInteger("lightPass", 0);
    secondPassShader.prepare(quad->getID());
    secondPassShader.run((int)Geometry::Quad);

    gbuffer->stopFrame();

    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
}

void DeferredRenderer::handleTerrainHeight(Heightmap * heightmap)
{
    glm::vec2 heightmapSize = heightmap->getHeightmapSize();
    glm::vec3 cameraPosition = sceneCamera->getPosition();

    float y = heightmap->getHeightAt(heightmapSize.x / 2 - cameraPosition.x, heightmapSize.y / 2 + cameraPosition.z);
    sceneCamera->handleTerrainHeight(y);
}

void DeferredRenderer::constructUBO()
{
    std::vector<float> ubo_data;
    ubo_data.push_back(lightPosition.x);
    ubo_data.push_back(lightPosition.y);
    ubo_data.push_back(lightPosition.z);
    ubo_data.push_back(0.0f);

    ubo_data.push_back(lightColour.x);
    ubo_data.push_back(lightColour.y);
    ubo_data.push_back(lightColour.z);
    ubo_data.push_back(0.25F);

    for (auto& light : pointLights)
    {
        ubo_data.push_back(light.pointPosition.x);
        ubo_data.push_back(light.pointPosition.y);
        ubo_data.push_back(light.pointPosition.z);

        ubo_data.push_back(0.0);
        ubo_data.push_back(light.pointColour.x);
        ubo_data.push_back(light.pointColour.y);
        ubo_data.push_back(light.pointColour.z);
        ubo_data.push_back(0.0);

        ubo_data.push_back(light.constantA);
        ubo_data.push_back(light.ambientI);
        ubo_data.push_back(light.linearA);
        ubo_data.push_back(light.expA);
    }

    GLuint bindingPoint = 1, blockIndex;
    GLuint programID = secondPassShader.getProgram()->getID();

    blockIndex = glGetUniformBlockIndex(programID, "SceneLights");
    glUniformBlockBinding(programID, blockIndex, bindingPoint);
    glBindBuffer(GL_UNIFORM_BUFFER, lID);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(float) * ubo_data.size(), ubo_data.data(), GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, lID);
}

void DeferredRenderer::renderCube(Cube * cube)
{
    if (cube != nullptr)
    {
        firstPassShader.prepare(cube->getDataID(), cube->getTextureID());
        firstPassShader.run((int)Geometry::Cube);
    }
    else
    {
        throw Error(ErrorType::Renderer, "Error you tried to render a null cube pointer");
    }
}

void DeferredRenderer::renderMap(Heightmap * heightmap)
{
    if (heightmap != NULL)
    {
        firstPassShader.prepare(heightmap->getVertexID(), heightmap->getTexture());
        firstPassShader.run(heightmap->getVertexCount());
    }
    else
    {
        throw Error(ErrorType::Renderer, "Error you tried to render a null map pointer");
    }
}

void DeferredRenderer::updateCamera(SDL_Event& event)
{
    sceneCamera->updateCameraPosition(event);
}

void DeferredRenderer::repositionCamera()
{
    sceneCamera->repositionCamera();
}

void DeferredRenderer::setMatrixForObject(const char * name, glm::mat4& mat)
{
    Program * program = firstPassShader.getProgram();

    program->setMatrix((char *)name, glm::value_ptr(mat));
}

void DeferredRenderer::changeCamera(CameraType newCamera)
{
    switch (newCamera)
    {
    case CameraType::FirstPerson:
    {
        auto newSceneCamera = new FirstPersonCamera(sceneCamera);
        SAFE_RELEASE(sceneCamera);
        sceneCamera = newSceneCamera;
        cameraType = CameraType::FirstPerson;
        break;
    }

    default: break;
    }
}

void DeferredRenderer::setCameraPosition(glm::vec3 positions)
{
    sceneCamera->setPosition(positions);
}

CameraType DeferredRenderer::getCameraType()
{
    return cameraType;
}

void DeferredRenderer::renderModel(Model * model)
{
    if (model != NULL)
    {
        ModelAsset * file = model->getModelAsset();

        GLuint current = 0;
        for (GLuint i = 0; i < model->getMeshCount(); i++)
        {
            GLuint meshLength = file->getMeshLength(i);

            firstPassShader.prepare(model->getDataID(), model->getTextureIDs(i));
            firstPassShader.run(current, meshLength);

            current += meshLength;
        }
    }
    else
    {
        throw Error(ErrorType::Renderer, "Error you tried to render a null model pointer");
    }
}

void DeferredRenderer::renderSkybox(Skybox * skybox)
{
    if (skybox != NULL)
    {
        glm::mat4 modelMatrix = glm::mat4(1.0);
        modelMatrix = glm::translate(modelMatrix, -sceneCamera->getPosition());

        Program* program = firstPassShader.getProgram();
        program->setMatrix("model", glm::value_ptr(modelMatrix));
        program->setMatrix("view", glm::value_ptr(sceneCamera->getView()));
        program->setInteger("sampler_index", 1);

        glDisable(GL_CULL_FACE);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->getTextureID());
        glUniform1i(glGetUniformLocation(program->getID(), "cubeMap"), 1);

        firstPassShader.prepare(skybox->getDataID());
        firstPassShader.run((int)Geometry::Cube);

        glBindTexture(GL_TEXTURE_CUBE_MAP, NULL);
        glEnable(GL_CULL_FACE);

        modelMatrix = glm::mat4(1.0);

        program->setInteger("sampler_index", 0);
        program->setMatrix("model", glm::value_ptr(modelMatrix));
    }
    else
    {
        throw Error(ErrorType::Renderer, "Error you tried to render a null skybox pointer");
    }
}