#pragma once
#pragma warning(disable : 4996)  

#include <string>
#include <fstream>
#include <GL/glew.h>

namespace sparky {
    class FileUtils
    {
    public:
        static std::string read_file(const char* filepath)
        {
            FILE* file = fopen(filepath, "rt");
            fseek(file, 0, SEEK_END);
            unsigned long length = ftell(file);
            char* data = new char[length + 1];
            memset(data, 0, length + 1);
            fseek(file, 0, SEEK_SET);
            fread(data, 1, length, file);
            fclose(file);
            std::string result(data);
            delete[] data;
            return result;
        }

        static GLuint loadBMP(const char * imagepath)
        {
            unsigned char header[54];
            unsigned int dataPos;
            unsigned int width, height;
            unsigned int imageSize;

            unsigned char * data;

            FILE * file = fopen(imagepath, "rb");
            if (!file) {
                printf("Image could not be opened\n");
                return 0;
            }

            if ( fread(header, 1, 54, file) != 54 ) 
            {

                printf("Not a correct BMP file\n");
                return false;
            }

            if (header[0] != 'B' || header[1] != 'M')
            {
                printf("Not a correct BMP file\n");
                return 0;
            }

            dataPos = *(int*)&(header[0x0A]);
            imageSize = *(int*)&(header[0x22]);
            width = *(int*)&(header[0x12]);
            height = *(int*)&(header[0x16]);

            if (imageSize == 0) imageSize = width * height * 3;
            if (dataPos == 0) dataPos = 54;

            data = new unsigned char[imageSize];

            fread(data, 1, imageSize, file);
            fclose(file);

            GLuint textureID;

            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

            return textureID;
        } ;


	};

        
}
