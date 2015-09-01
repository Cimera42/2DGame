#include "loadTexture.h"
#include "logger.h"

GLuint load2DTexture(std::string texturePath, bool srgb)
{
    GLuint texture_id;
    if(!srgb)
    {
        texture_id = SOIL_load_OGL_texture(texturePath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);

        glSetBindTexture(GL_TEXTURE_2D, texture_id);
        //default
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //settings that we need to include
        /*
        if(!checkSetting(TEXTURE_FILTERING, DISABLED))
        {
            glGenerateMipmap(GL_TEXTURE_2D);  //Generate mipmaps now!!!
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
        if (checkSetting(TEXTURE_FILTERING, DISABLED))
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }
        else if (checkSetting(TEXTURE_FILTERING, BILINEAR_FILTERING))
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        }
        else if (checkSetting(TEXTURE_FILTERING, TRILINEAR_FILTERING))
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        }
        else if (checkSetting(TEXTURE_FILTERING, ANISOTROPIC_FILTERING))
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            int AFLargest;
            glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &AFLargest);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, AFLargest);
        }*/
    }
    else
    {
        int width, height;
        unsigned char* image;
        image = SOIL_load_image(texturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
        if (image)
        {
            glGenTextures(1, &texture_id);
            glSetBindTexture(GL_TEXTURE_2D, texture_id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            //default
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
    }
    if (!texture_id)
    {
        Logger()<<"Texture not loaded- ("<<texturePath<<") - "<<SOIL_last_result()<<std::endl;
        return 0;
    }
    else
    {
        Logger()<<"Texture loaded: "<<texturePath<<"."<<std::endl;
    }

    return texture_id;
}

unsigned char* load2DTextureData(std::string texturePath, int* widthLoc, int* heightLoc)
{
    int width, height;
    unsigned char* image;
    image = SOIL_load_image(texturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

    if (!image)
    {
        Logger()<<"Texture data not loaded- ("<<texturePath<<") - "<<SOIL_last_result()<<std::endl;
        return 0;
    }
    else
    {
        Logger()<<"Texture data loaded: "<<texturePath<<"."<<std::endl;
    }
    *widthLoc = width;
    *heightLoc = height;

    return image;
}

GLuint load2DTextureByData(unsigned char* inData, int width, int height, bool srgb)
{
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glSetBindTexture(GL_TEXTURE_2D, texture_id);
    if(srgb)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, inData);
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, inData);
    }
    //default
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (!texture_id)
    {
        Logger()<<"Texture not loaded by data - "<<SOIL_last_result()<<std::endl;
        return 0;
    }
    else
    {
        Logger()<<"Texture loaded by data."<<std::endl;
    }

    return texture_id;
}

GLuint load2DTextureArray(std::vector<const char*> texturePaths, int imgsize)
{
    GLuint texture_id;

    glGenTextures(1, &texture_id);
    glSetBindTexture(GL_TEXTURE_2D_ARRAY, texture_id);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, imgsize, imgsize, texturePaths.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    //default
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    /*if(!checkSetting(TEXTURE_FILTERING, DISABLED))
    {
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    if (checkSetting(TEXTURE_FILTERING, DISABLED))
    {
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }*/
    for(int i = 0; i < texturePaths.size(); i++)
    {
        int width, height;
        unsigned char* image;
        image = SOIL_load_image(texturePaths[i], &width, &height, 0, SOIL_LOAD_RGBA);
        if (image)
        {
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,0,0, i, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, image);
            Logger()<<"RGBA texture loaded- ("<<texturePaths[i]<<") - "<<SOIL_last_result()<<std::endl;
        }
        else
        {
            Logger()<<"RGBA texture not loaded- ("<<texturePaths[i]<<") - "<<SOIL_last_result()<<std::endl;
            return 0;
        }
    }

    return texture_id;
}
