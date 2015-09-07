#include "renderTerrainSystem.h"
#include "terrainComponent.h"
#include "worldComponent.h"
#include "cameraComponent.h"
#include "cameraSystem.h"
#include "loadShader.h"
#include "loader.h"
#include "globals.h"
#include "logger.h"

//Unique system ID
SystemID RenderTerrainSystem::ID;

RenderTerrainSystem::RenderTerrainSystem()
{
    std::vector<ComponentID> subList1;
    //Components needed to subscribe to system
    subList1.push_back(WorldComponent::getStaticID());
    subList1.push_back(TerrainComponent::getStaticID());
    addSubList(subList1);

    //Generate shader
    std::vector<const char*> shaderLocations;
    shaderLocations.push_back("vertPos");
    shaderLocations.push_back("vertUV");
    shader = loadShader("shaders/terrainVert.vert", "shaders/terrainFrag.frag", shaderLocations);

    //Get location of uniforms from shader
    textureLoc = glGetUniformLocation(shader, "textureSampler");
    modelMatLoc = glGetUniformLocation(shader, "modelMat");
    viewProjMatLoc = glGetUniformLocation(shader, "viewProjMat");
}
RenderTerrainSystem::~RenderTerrainSystem()
{
    glDeleteShader(shader);
}

void RenderTerrainSystem::update()
{
    //Set shader
    glSetUseProgram(shader);

    for(int subID = 0; subID < subscribedEntities[0].size(); subID++)
    {
        Entity * entity = entities[subscribedEntities[0][subID]];

        //Get components
        WorldComponent* worldComp = static_cast<WorldComponent*>(entity->getComponent(WorldComponent::getStaticID()));
        TerrainComponent* terrainComp = static_cast<TerrainComponent*>(entity->getComponent(TerrainComponent::getStaticID()));

        //Check if VAO needs to be loaded
        if(!terrainComp->loadedVAO)
        {
            //Generate VAO
            glGenVertexArrays(1, &terrainComp->VAO);
            glSetBindVertexArray(terrainComp->VAO);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainComp->indexBuffer);
                glBindBuffer(GL_ARRAY_BUFFER, terrainComp->vertexBuffer);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0); //attribute, size, type, is normalised?, stride, offset

                glBindBuffer(GL_ARRAY_BUFFER, terrainComp->uvBuffer);
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0); //attribute, size, type, is normalised?, stride, offset
            glSetBindVertexArray(0);

            terrainComp->loadedVAO = true;
        }

        //Send texture to shader
        glSetActiveTexture(GL_TEXTURE0);
        glSetBindTexture(GL_TEXTURE_2D, terrainComp->textureStore->textureID);
        glUniform1i(textureLoc, 0);

        //Send model matrix to shader
        glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, &worldComp->modelMatrix[0][0]);

        //Camera operations
        CameraSystem* cameraSys = static_cast<CameraSystem*>(systems[CameraSystem::getStaticID()]);
        if(cameraSys->activeCamera != -1)
        {
            CameraComponent* cameraComp = static_cast<CameraComponent*>(entities[cameraSys->activeCamera]->getComponent(CameraComponent::getStaticID()));
            //Send view and projection matrix to shader
            glUniformMatrix4fv(viewProjMatLoc, 1, GL_FALSE, &cameraComp->jointMatrix[0][0]);
        }

        //Draw
        glSetBindVertexArray(terrainComp->VAO);
            glDrawElements(GL_TRIANGLES, terrainComp->bufSize, GL_UNSIGNED_INT, 0);
        glSetBindVertexArray(0);
    }
}
