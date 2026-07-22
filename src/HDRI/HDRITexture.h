#pragma once

#include <string>


class HDRITexture
{

public:

    HDRITexture();

    ~HDRITexture();



    //------------------------------------------------
    // LOAD EXR
    //------------------------------------------------

    bool loadFromFile(
        const std::string& path
    );



    //------------------------------------------------
    // OPENGL
    //------------------------------------------------

    void bind(
        unsigned int slot = 0
    ) const;


    void destroy();



    //------------------------------------------------
    // INFO
    //------------------------------------------------

    int getWidth() const
    {
        return width;
    }


    int getHeight() const
    {
        return height;
    }


    int getChannels() const
    {
        return channels;
    }


    unsigned int getID() const
    {
        return id;
    }


    bool isLoaded() const
    {
        return loaded;
    }



private:


    //------------------------------------------------
    // OPENGL TEXTURE
    //------------------------------------------------

    unsigned int id = 0;



    //------------------------------------------------
    // IMAGE DATA
    //------------------------------------------------

    int width = 0;

    int height = 0;

    int channels = 0;



    //------------------------------------------------
    // STATE
    //------------------------------------------------

    bool loaded = false;


};