#include<glad/glad.h>
#include"stb_image.h"
#include<string>
#include<iostream>

class Texture {
public:
	unsigned int ID;

	Texture(const char* path) {
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		
		int width, hight, nrchannels;
		unsigned char* data = stbi_load(path, &width, &hight, &nrchannels, NULL);
		if (data) {
			GLenum format;
			switch (nrchannels) {
			case 1: format = GL_RED; break;
			case 2: format = GL_RG; break;
			case 3: format = GL_RGB; break;
			case 4: format = GL_RGBA; break;
			default:format = GL_RGB; break;
			}

			//glBindTexture(GL_TEXTURE_2D, ID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, hight, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else std::cout << "Failed to load texture in :\n " << path << std::endl;
		stbi_image_free(data);
	}
	void bind() {
		glBindTexture(GL_TEXTURE_2D, ID);
	}
};