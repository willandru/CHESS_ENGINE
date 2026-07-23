#include "HDRITexture.h"

#include <glad/glad.h>

#include <ImfRgbaFile.h>
#include <ImfArray.h>

#include <iostream>
#include <vector>

#include <ImfHeader.h>
#include <ImfChannelList.h>

using namespace OPENEXR_IMF_NAMESPACE;
using namespace IMATH_NAMESPACE;



HDRITexture::HDRITexture()
{

}



HDRITexture::~HDRITexture()
{

    destroy();

}



//====================================================
// LOAD EXR
//====================================================

bool HDRITexture::loadFromFile(
    const std::string& path
)
{

    destroy();



    try
    {

        RgbaInputFile file(
            path.c_str()
        );

        //------------------------------------------------
    // OPENEXR INFORMATION
    //------------------------------------------------

    const Header& header =
        file.header();


    std::cout
        << "\n========== CHANNELS ==========\n";


    for(
        auto it = header.channels().begin();
        it != header.channels().end();
        ++it
    )
    {
        std::cout
            << "Channel: "
            << it.name()
            << std::endl;
    }


    std::cout
        << "==============================\n";



    std::cout
        << "\n========== ATTRIBUTES ==========\n";


    for(
        auto it = header.begin();
        it != header.end();
        ++it
    )
    {
        std::cout
            << "Attribute: "
            << it.name()
            << std::endl;
    }


    std::cout
        << "================================\n";



        Box2i dataWindow =
            file.dataWindow();



        width =
            dataWindow.max.x -
            dataWindow.min.x
            + 1;


        height =
            dataWindow.max.y -
            dataWindow.min.y
            + 1;



        //------------------------------------------------
        // READ PIXELS
        //------------------------------------------------

        Array2D<Rgba> pixels;


        pixels.resizeErase(
            height,
            width
        );


        file.setFrameBuffer(
            &pixels[0][0]
            -
            dataWindow.min.x
            -
            dataWindow.min.y * width,

            1,
            width
        );


        file.readPixels(
            dataWindow.min.y,
            dataWindow.max.y
        );



        //------------------------------------------------
        // CONVERT FLOAT RGB
        //------------------------------------------------

        std::vector<float> data;


        data.resize(
            width *
            height *
            3
        );



        for(
            int y = 0;
            y < height;
            y++
        )
        {

            for(
                int x = 0;
                x < width;
                x++
            )
            {

                const Rgba& pixel =
                    pixels[y][x];


                int index =
                    (y * width + x)
                    * 3;



                data[index + 0] =
                    pixel.r;


                data[index + 1] =
                    pixel.g;


                data[index + 2] =
                    pixel.b;

            }

        }



        //------------------------------------------------
        // OPENGL TEXTURE
        //------------------------------------------------

        glGenTextures(
            1,
            &id
        );


        glBindTexture(
            GL_TEXTURE_2D,
            id
        );


        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB16F,
            width,
            height,
            0,
            GL_RGB,
            GL_FLOAT,
            data.data()
        );



        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            GL_LINEAR
        );


        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER,
            GL_LINEAR
        );


        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_S,
            GL_CLAMP_TO_EDGE
        );


        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_T,
            GL_CLAMP_TO_EDGE
        );


        glBindTexture(
            GL_TEXTURE_2D,
            0
        );



        channels = 3;

        loaded = true;



        std::cout
            << "[HDRI] Loaded: "
            << path
            << std::endl;


        std::cout
            << "[HDRI] Size: "
            << width
            << " x "
            << height
            << std::endl;



        return true;


    }
    catch(
        const std::exception& e
    )
    {

        std::cout
            << "[HDRI] ERROR: "
            << e.what()
            << std::endl;


        loaded = false;

        return false;

    }

}



//====================================================
// BIND
//====================================================

void HDRITexture::bind(
    unsigned int slot
) const
{

    if(!loaded)
        return;



    glActiveTexture(
        GL_TEXTURE0 + slot
    );


    glBindTexture(
        GL_TEXTURE_2D,
        id
    );

}



//====================================================
// DESTROY
//====================================================

void HDRITexture::destroy()
{

    if(id != 0)
    {

        glDeleteTextures(
            1,
            &id
        );


        id = 0;

    }


    width = 0;

    height = 0;

    channels = 0;

    loaded = false;

}