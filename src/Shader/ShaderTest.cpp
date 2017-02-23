#include <iostream>
#include <cmath>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

#include <Shader.h>

//Function callback
void Key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

//Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

/*
//Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"						//position����������λ��Ϊ0
"out vec4 vertexColor;\n"										//ΪƬ����ɫ��ָ��һ����ɫ���
"void main()\n"
"{\n"
"gl_Position = vec4(position, 1.0);\n"
"vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"					//�������������Ϊ����ɫ
"}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"in vec4 vertexColor;\n"										//�Ӷ�����ɫ�����������������������ͬ��������ͬ��
"out vec4 color;"												//Ƭ����ɫ������ı��������������������ͱ�����vec4
"void main()\n"
"{\n"
"color = vertexColor;\n"
"}\0";
*/

/*
//ʹ��uniform�����ı���ɫ���е���ɫ��uniform��������ֱ����cpu�����ж�����в������ı�ֵ��
//Shaders ������ɫ����ֻ��һ����������
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position, 1.0);\n"
"}\0";

//Ƭ����ɫ��ͨ��uniform��������ɫ��cpu����ֱ�Ӹ���ɫ������
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"color = ourColor;\n"
"}\0";
*/

//�����룬���������а��������������ݵ����
//������ɫ��
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"					//λ�ñ���������λ��Ϊ0
"layout (location = 1) in vec3 color;\n"					//��ɫ����������λ��Ϊ1
"out vec3 ourColor;\n"										//��Ƭ����ɫ�����һ����ɫ
"void main()\n"
"{\n"
"gl_Position = vec4(position, 1.0);\n"
"ourColor = color;\n"										//��ourColor����Ϊ���ǴӶ�����������õ���������ɫ���Ҹ���ɫ�ᴫ�͵�Ƭ����ɫ��
"}\0";
//Ƭ����ɫ��
const GLchar* fragmentShaderSource = "#version 330 core\n"
"in vec3 ourColor;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(ourColor, 1.0f);\n"
"}\0";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, Key_callback);

	glewExperimental = GL_TRUE;

	glewInit();

	glViewport(0, 0, WIDTH, HEIGHT);

	//ʹ��Shader����������ɫ������
	Shader ourShader("shader.vs", "shader.frag");

	/*
	//vertexSahder
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEXD::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//fragmentShader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Link shader
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	*/

	/*
	//vertex data
	GLfloat vertices[] = {
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	*/
	//����ɫ����Ҳ���뵽���������У����������������ε��������㣬ÿ�������һ����ɫֵ
	GLfloat vertices[] = {
		//λ��					   //��ɫ
		 0.5f, -0.5f, 0.0f,        1.0f, 0.0f, 0.0f,		//����
		-0.5f, -0.5f, 0.0f,        0.0f, 1.0f, 0.0f,		//����
		 0.0f,  0.5f, 0.0f,        0.0f, 0.0f, 1.0f			//����
	};
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//glUseProgram(shaderProgram);
		ourShader.Use();

		/*
		//ÿ�θı�uniform���������ı�����ɫֵ
		GLfloat timeValue = glfwGetTime(); 
		GLfloat greenValue = (sin(timeValue) / 2) + 0.5;								//����ɫֵʼ����0��1֮��仯
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");	//�õ�uniform����λ��
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);					//�޸���ɫֵ������cpu������ֱ���޸���Ƭ����ɫ����ourColor��ֵ
		*/
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}

void Key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}