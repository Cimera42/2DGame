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
    //Components required for subscription
    componentSubList.push_back(WorldComponent::getStaticID());
    componentSubList.push_back(Render2DComponent::getStaticID());

    //Standard quad vertices
    vertices.push_back(glm::vec2(-0.5f,0.5f));
    int tl = vertices.size()-1;
    vertices.push_back(glm::vec2(0.5f,0.5f));
    int tr = vertices.size()-1;
    vertices.push_back(glm::vec2(-0.5f,-0.5f));
    int bl = vertices.size()-1;
    vertices.push_back(glm::vec2(0.5f,-0.5f));
    int br = vertices.size()-1;

    //Standard quad indices
    indices.push_back(tl);
    indices.push_back(tr);
    indices.push_back(br);

    indices.push_back(tl);
    indices.push_back(bl);
    indices.push_back(br);

    //Generate vertex buffer using standard data
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);

    //Set up uv buffer for data stream
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STREAM_DRAW);

    //Generate index buffer using standard data
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    bufSize = indices.size();

    //Set up matrix buffer for data stream
    glGenBuffers(1, &matrixBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, matrixBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STREAM_DRAW);

    glGenVertexArrays(1, &VAO);
    glSetBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        //Enable vertex buffer
        int vertLoc = 0;
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glEnableVertexAttribArray(vertLoc);
        glVertexAttribPointer(vertLoc, 2, GL_FLOAT, GL_FALSE, 0, 0); //attribute, size, type, is normalised?, stride, offset
        //Use same data set each draw
        glVertexAttribDivisor(vertLoc,0);

        int uvLoc = 1;
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glEnableVertexAttribArray(uvLoc);
        glVertexAttribPointer(uvLoc, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), 0); //attribute, size, type, is normalised?, stride, offset
        //PROBLEM HERE
        //Use unique uvs for each draw
        glVertexAttribDivisor(uvLoc,1);

        //Use a unique matrix for each draw
        int matLoc = 2;
        glBindBuffer(GL_ARRAY_BUFFER, matrixBuffer);
        //Vertex attribute for each matrix row
        glEnableVertexAttribArray(matLoc+0);
        glEnableVertexAttribArray(matLoc+1);
        glEnableVertexAttribArray(matLoc+2);
        glEnableVertexAttribArray(matLoc+3);
        glVertexAttribPointer(matLoc+0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float)*0)); //attribute, size, type, is normalised?, stride, offset
        glVertexAttribPointer(matLoc+1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float)*4)); //attribute, size, type, is normalised?, stride, offset
        glVertexAttribPointer(matLoc+2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float)*8)); //attribute, size, type, is normalised?, stride, offset
        glVertexAttribPointer(matLoc+3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float)*12)); //attribute, size, type, is normalised?, stride, offset

        glVertexAttribDivisor(matLoc+0,1);
        glVertexAttribDivisor(matLoc+1,1);
        glVertexAttribDivisor(matLoc+2,1);
        glVertexAttribDivisor(matLoc+3,1);
    glSetBindVertexArray(0);

    //Create shader
    std::vector<const char*> shaderLocations;
    shaderLocations.push_back("vertPos");
    shaderLocations.push_back("vertUV");
    shaderLocations.push_back("instanceMatrix");
    shader = loadShader("shaders/vert.vert", "shaders/frag.frag", shaderLocations);

    //Load texture
    bool success = Load<TextureStore>::Object(&textureStore, "debug/texture.store");
    textureLoc = glGetUniformLocation(shader, "textureSampler");
}
Render2DSystem::~Render2DSystem()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &uvBuffer);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteBuffers(1, &matrixBuffer);
    glDeleteShader(shader);
}

void Render2DSystem::addToList(WorldComponent* inWorld, Render2DComponent* inRender)
{
    //Push uvs
    uvs.push_back(glm::vec4(inRender->startUV.x,inRender->startUV.y,inRender->UVsize.x,inRender->UVsize.y));

    //Push matrix
    matrices.push_back(inWorld->modelMatrix);
}

void Render2DSystem::resizeBuffers()
{
    //Reallocate buffers in order
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec4), &uvs[0], GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, matrixBuffer);
    glBufferData(GL_ARRAY_BUFFER, matrices.size() * sizeof(glm::mat4), &matrices[0][0], GL_STREAM_DRAW);
}

void Render2DSystem::refillBuffers()
{
    //Reload matrix data
    std::vector<glm::mat4>().swap(matrices);
    for(int subID = 0; subID < subscribedEntities.size(); subID++)
    {
        Entity * entity = entities[subscribedEntities[subID]];

        WorldComponent* worldComp = static_cast<WorldComponent*>(entity->getComponent(WorldComponent::getStaticID()));

        matrices.push_back(worldComp->modelMatrix);
    }

    //Refill the matrix buffer with new data
    glBindBuffer(GL_ARRAY_BUFFER, matrixBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, matrices.size() * sizeof(glm::mat4), &matrices[0][0]);
}

void Render2DSystem::entitySubscribed(Entity* inEntity)
{
    WorldComponent* worldComp = static_cast<WorldComponent*>(inEntity->getComponent(WorldComponent::getStaticID()));
    Render2DComponent* render2DComp = static_cast<Render2DComponent*>(inEntity->getComponent(Render2DComponent::getStaticID()));

    //Add render data to list
    addToList(worldComp,render2DComp);

    //Tell system to reallocate buffers to add space for new data
    shouldResizeBuffers = true;
}

void Render2DSystem::entityUnsubscribed(Entity* inEntity)
{
    //Clear buffers
    std::vector<glm::vec4>().swap(uvs);
    std::vector<glm::mat4>().swap(matrices);
    //Reload data for all objects
    for(int subID = 0; subID < subscribedEntities.size(); subID++)
    {
        Entity * entity = entities[subscribedEntities[subID]];

        if(entity != inEntity)
        {
            WorldComponent* worldComp = static_cast<WorldComponent*>(entity->getComponent(WorldComponent::getStaticID()));
            Render2DComponent* render2DComp = static_cast<Render2DComponent*>(entity->getComponent(Render2DComponent::getStaticID()));

            addToList(worldComp,render2DComp);
        }
    }

    //Tell system to reallocate buffers to remove old data space
    shouldResizeBuffers = true;
}

void Render2DSystem::update()
{
    //Check if buffers need to be reallocated, else refill buffers with updated data
    if(shouldResizeBuffers)
    {
        resizeBuffers();
        shouldResizeBuffers = false;
    }
    else
    {
        if(!glfwGetKey(mainWindow->glfwWindow, GLFW_KEY_R))
            refillBuffers();
    }
    glSetUseProgram(shader);

    //Bind texture
    glSetActiveTexture(GL_TEXTURE0);
    glSetBindTexture(GL_TEXTURE_2D, textureStore->textureID);
    glUniform1i(textureLoc, 0);

    //Draw
    glSetBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, bufSize, GL_UNSIGNED_INT, 0);
        glDrawElementsInstanced(GL_TRIANGLES, bufSize, GL_UNSIGNED_INT, 0, matrices.size());
    glSetBindVertexArray(0);
}
