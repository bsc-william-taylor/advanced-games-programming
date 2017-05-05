
#include "Heightmap.h"

Heightmap::Heightmap()
    : vertexCount(0), mesh(0)
{
}

Heightmap::~Heightmap()
{
    SAFE_RELEASE(mesh);
}

glm::vec2 Heightmap::getHeightmapSize()
{
    return size;
}

GLfloat Heightmap::getY(FIBITMAP * sprite, int _x, int _y, float scale_y)
{
    RGBQUAD colour;
    FreeImage_GetPixelColor(sprite, _x, _y, &colour);

    GLfloat y = 0.0f;
    y += ((GLfloat)colour.rgbGreen) / 255.0f;
    y += ((GLfloat)colour.rgbBlue) / 255.0f;
    y += ((GLfloat)colour.rgbRed) / 255.0f;
    return (-2 + y*scale_y);
}

GLuint Heightmap::getTexture()
{
    return texture->getID();
}

GLuint Heightmap::getVertexID()
{
    return mesh->getID();
}

GLuint Heightmap::getVertexCount()
{
    return vertexCount;
}

glm::vec3 Heightmap::getSurfaceNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
{
    return glm::cross(v2 - v1, v3 - v1);
}

GLfloat Heightmap::getHeightAt(int x, int y)
{
    if (x >= 0 && y >= 0 && x < size.x && y < size.y)
    {
        return -(terrain_heights[x][size.y - y]);
    }
    else
    {
        return 0.0;
    }
}

HeightmapSurface * Heightmap::getFace(Side side, GLuint i, GLuint b, GLuint size)
{
    switch (side)
    {
        case Side::Top:	if (b + 1 < size) { return faces[i][b + 1]; } break;
        case Side::TopRight: if (i + 1 < size && b + 1 < size) { return faces[i + 1][b + 1]; } break;
        case Side::BottomRight: if (i + 1 < size && b != 0) { return faces[i + 1][b - 1]; } break;
        case Side::BottomLeft:if (i != 0 && b != 0) { return faces[i - 1][b - 1]; } break;
        case Side::TopLeft: if (i != 0 && b + 1 < size) { return faces[i - 1][b + 1]; } break;
        case Side::Right: if (i + 1 < size) { return faces[i + 1][b]; } break;
        case Side::Bottom: if (b != 0) return faces[i][b - 1];	break;
        case Side::Left: if (i != 0) return faces[i - 1][b]; else break;

    default: break;
    }

    return NULL;
}

GLvoid Heightmap::averageNormals(std::vector<glm::vec3>& vertices)
{
    for (int i = 0; i < faces.size(); i++)
    {
        for (int b = 0; b < faces.size(); b++)
        {
            auto face = faces[i][b];

            for (int z = 0; z < 6; z++)
            {
                glm::vec3 normal = face->normal;
                glm::vec3 vert = face->vertices[z];

                for (int s = 0; s < 8; s++)
                {
                    auto next = getFace((Side)s, i, b, faces.size());

                    if (next != nullptr)
                    {
                        for (auto& v : next->vertices)
                        {
                            if (v == vert)
                            {
                                normal += next->normal;
                                break;
                            }
                        }
                    }
                }

                vn.push_back(normal);
            }
        }
    }
}

void Heightmap::create(TextureAsset * file, std::string heightmapFilename, float _x, float _y)
{
    auto bitmap = FreeImage_Load(
        FreeImage_GetFIFFromFilename(heightmapFilename.c_str()),
        heightmapFilename.c_str()
    );

    GLint textureHeight = FreeImage_GetHeight(bitmap);
    GLint textureWidth = FreeImage_GetWidth(bitmap);
    GLint z = -textureHeight / 2;
    GLint x = -textureWidth / 2;

    size = glm::vec2(textureWidth, textureHeight);
    texture = new Sampler(SamplerType::SingleSampler);
    mesh = new Transfer();

    std::vector<glm::vec3> list;
    std::vector<glm::vec3> uvs;

    faces.reserve(textureWidth * textureHeight * 2);
    list.reserve(textureWidth * textureHeight * 2 * 3);
    uvs.reserve(textureWidth * textureHeight * 2 * 2);
    vn.reserve(textureWidth * textureHeight * 2 * 3);

    for (int i = 0; i < textureWidth + 1; i++)
    {
        terrain_heights.push_back(std::vector<float>());
        faces.push_back(std::vector<HeightmapSurface *>());

        for (int a = 0; a < textureHeight + 1; a++, z++)
        {
            float heights[] = {
                getY(bitmap, i, a, _y), 			getY(bitmap, i, a + 1, _y),
                getY(bitmap, i + 1, a + 1, _y), 	getY(bitmap, i, a, _y),
                getY(bitmap, i + 1, a + 1, _y),		getY(bitmap, i + 1, a, _y)
            };

            float heighest_height = 0.0;
            for (int b = 0; b < 6; b++)
            {
                if (heights[b] * heights[b] > heighest_height*heighest_height)
                {
                    heighest_height = heights[b];
                }
            }

            terrain_heights[i].push_back(heighest_height);

            list.push_back(glm::vec3(x, heights[0], z - 1));
            list.push_back(glm::vec3(x, heights[1], z));
            list.push_back(glm::vec3(x + 1, heights[2], z));
            list.push_back(glm::vec3(x, heights[3], z - 1));
            list.push_back(glm::vec3(x + 1, heights[4], z));
            list.push_back(glm::vec3(x + 1, heights[5], z - 1));

            uvs.push_back(glm::vec3(0.0, 0.0, 0.0));
            uvs.push_back(glm::vec3(0.0, 1.0, 0.0));
            uvs.push_back(glm::vec3(1.0, 1.0, 0.0));
            uvs.push_back(glm::vec3(0.0, 0.0, 0.0));
            uvs.push_back(glm::vec3(1.0, 1.0, 0.0));
            uvs.push_back(glm::vec3(1.0, 0.0, 0.0));

            auto surface = new HeightmapSurface();
            auto v1 = getSurfaceNormal(glm::vec3(x, heights[0], z - 1), glm::vec3(x, heights[1], z), glm::vec3(x + 1, heights[2], z));
            auto v2 = getSurfaceNormal(glm::vec3(x, heights[3], z - 1), glm::vec3(x + 1, heights[4], z), glm::vec3(x + 1, heights[5], z - 1));

            surface->normal = v1 + v2;
            surface->vertices = {
                glm::vec3(x,		heights[0],		z - 1),
                glm::vec3(x,		heights[1],		z),
                glm::vec3(x + 1,	heights[2],		z),
                glm::vec3(x,		heights[3],		z - 1),
                glm::vec3(x + 1,	heights[4],		z),
                glm::vec3(x + 1,	heights[5],		z - 1)
            };

            faces[i].push_back(surface);
        }

        z = -textureHeight / 2;
        x++;
    }

    for (auto& v : list) {
        v.x *= _x;
        v.z *= _x;
    }

    averageNormals(list);

    mesh->setTextureCords(uvs);
    mesh->setVertices(list);
    mesh->setNormals(vn);
    mesh->send();

    texture->setTransferQuality(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    texture->setBitmapData(file->getPixels(),
        file->getWidth(),
        file->getHeight(),
        file->getBPP(),
        file->getMask()
    );

    texture->send();

    vertexCount = list.size();
    FreeImage_Unload(bitmap);
}