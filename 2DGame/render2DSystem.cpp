#include "render2DSystem.h"
#include "globals.h"

#include <iostream>
#include "worldComponent.h"
#include "loadShader.h"
#include "openGLFunctions.h"
#include "loader.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

SystemID Render2DSystem::ID;

Render2DSystem::Render2DSystem()
{
    componentSubList.push_back(WorldComponent::getStaticID());
    componentSubList.push_back(Render2DComponent::getStaticID());

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);

    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STREAM_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, NULL, GL_STREAM_DRAW);

    glGenVertexArrays(1, &VAO);
    glSetBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //attribute, size, type, is normalised?, stride, offset

        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0); //attribute, size, type, is normalised?, stride, offset
    glSetBindVertexArray(0);

    std::vector<const char*> shaderLocations;
    shaderLocations.push_back("vertPos");
    shader = loadShader("shaders/vert.vert", "shaders/frag.frag", shaderLocations);

    bool success = Load<TextureStore>::Object(&textureStore, "debug/texture.store");
    textureLoc = glGetUniformLocation(shader, "textureSampler");
}
Render2DSystem::~Render2DSystem()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &uvBuffer);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteShader(shader);
}

void Render2DSystem::update()
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<unsigned int> indices;

    for(int subID = 0; subID < subscribedEntities.size(); subID++)
    {
        Entity * entity = entities[subscribedEntities[subID]];

        WorldComponent* worldComp = static_cast<WorldComponent*>(entity->getComponent(WorldComponent::getStaticID()));
        Render2DComponent* render2DComp = static_cast<Render2DComponent*>(entity->getComponent(Render2DComponent::getStaticID()));

        vertices.push_back(glm::vec3(worldComp->position + render2DComp->topLeft, 0));
        int tl = vertices.size()-1;
        vertices.push_back(glm::vec3(worldComp->position + render2DComp->topRight, 0));
        int tr = vertices.size()-1;
        vertices.push_back(glm::vec3(worldComp->position + render2DComp->bottomLeft, 0));
        int bl = vertices.size()-1;
        vertices.push_back(glm::vec3(worldComp->position + render2DComp->bottomRight, 0));
        int br = vertices.size()-1;

        uvs.push_back(glm::vec2(0,1));
        uvs.push_back(glm::vec2(1,1));
        uvs.push_back(glm::vec2(0,0));
        uvs.push_back(glm::vec2(1,0));

        indices.push_back(tl);
        indices.push_back(tr);
        indices.push_back(br);

        indices.push_back(tl);
        indices.push_back(bl);
        indices.push_back(br);
    }

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STREAM_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STREAM_DRAW);
    bufSize = indices.size();

    glSetUseProgram(shader);

    glSetActiveTexture(GL_TEXTURE0);
    glSetBindTexture(GL_TEXTURE_2D, textureStore->textureID);
    glUniform1i(textureLoc, 0);

    glSetBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, bufSize, GL_UNSIGNED_INT, 0);
    glSetBindVertexArray(0);
}
