#pragma once
#include <map>
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader;

struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
	GLuint Advance;     // Horizontal offset to advance to next glyph
};


class TextRender
{
public:
	TextRender(GLuint width, GLuint height, const GLchar* vertexPath, const GLchar* fragmentPath);
	~TextRender();
	
	void loadFont(const GLchar* fontPath, GLuint fontSize);
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color = glm::vec3(1.0));

private:
	GLuint VAO, VBO;
	Shader* shader;
	std::map<GLchar, Character> Charaters;


};

