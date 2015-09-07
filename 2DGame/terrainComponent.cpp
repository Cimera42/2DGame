#include "terrainComponent.h"
#include "loader.h"
#include "logger.h"
#include "noise.h"

ComponentID TerrainComponent::ID;

TerrainComponent::TerrainComponent(int numPoints, float heightScale, float noiseScale)
{
    //Generate surface points
    for(int i = 0; i <= numPoints; i++)
    {
        surface.push_back(glm::vec2((float)i/numPoints,SimplexNoise::noise((float)i/numPoints * noiseScale)*heightScale));
    }

    //Position of bottom of terrain - where terrain ends vertically
    int baseline = -2;
    //Generate the triangles
    for(int i = 0; i < surface.size()-1; i++)
    {
        //Generate the triangle vertices
        vertices.push_back(surface[i]);
        vertices.push_back(glm::vec2(surface[i].x, baseline));
        vertices.push_back(surface[i+1]);
        vertices.push_back(glm::vec2(surface[i+1].x,baseline));

        //Generate the triangles uvs
        uvs.push_back(glm::vec2(surface[i].x,1));
        uvs.push_back(glm::vec2(surface[i].x,0));
        uvs.push_back(glm::vec2(surface[i+1].x,1));
        uvs.push_back(glm::vec2(surface[i+1].x,0));

        //Generate indices
        //Start of triangle in array
        int tristart = i*4;
        indices.push_back(tristart);
        indices.push_back(tristart+1);
        indices.push_back(tristart+3);

        indices.push_back(tristart);
        indices.push_back(tristart+2);
        indices.push_back(tristart+3);
    }

    //Generate vertex buffer
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);

    //Generate uv buffer
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    //Generate index buffer
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    //Set number of indices
    bufSize = indices.size();

    //Set VAO to be loaded
    //Must be loaded in systems, as VAO's are not shared across GL contexts
    loadedVAO = false;

    //Load texture
    Load<TextureStore>::Object(&textureStore, "debug/textureTerrain.store");
}
TerrainComponent::~TerrainComponent()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &uvBuffer);
    glDeleteBuffers(1, &indexBuffer);

    Unload<TextureStore>::Object(&textureStore);
}

//Regenerate buffers if data has changed
void TerrainComponent::rebuildBuffers()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    bufSize = indices.size();
}
