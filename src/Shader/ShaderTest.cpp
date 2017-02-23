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
"layout (location = 0) in vec3 position;\n"						//position变量的属性位置为0
"out vec4 vertexColor;\n"										//为片段着色器指定一个颜色输出
"void main()\n"
"{\n"
"gl_Position = vec4(position, 1.0);\n"
"vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"					//把输出变量设置为暗红色
"}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"in vec4 vertexColor;\n"										//从顶点着色器传来的输入变量（名称相同，类型相同）
"out vec4 color;"												//片段着色器输出的变量可以任意命名，类型必须是vec4
"void main()\n"
"{\n"
"color = vertexColor;\n"
"}\0";
*/

/*
//使用uniform变量改变着色器中的颜色，uniform变量可以直接在cpu程序中对其进行操作，改变值。
//Shaders 顶点着色器中只是一个顶点属性
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position, 1.0);\n"
"}\0";

//片段着色器通过uniform变量将颜色从cpu程序直接给着色器程序
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"color = ourColor;\n"
"}\0";
*/

//多输入，顶点数据中包含其他属性数据的情况
//顶点着色器
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"					//位置变量的属性位置为0
"layout (location = 1) in vec3 color;\n"					//颜色变量的属性位置为1
"out vec3 ourColor;\n"										//向片段着色器输出一个颜色
"void main()\n"
"{\n"
"gl_Position = vec4(position, 1.0);\n"
"ourColor = color;\n"										//将ourColor设置为我们从顶点数据那里得到的输入颜色，找个颜色会传送到片段着色器
"}\0";
//片段着色器
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

	//使用Shader类来生成着色器程序
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
	//将颜色数据也加入到顶点数据中，该数据中是三角形的三个顶点，每个顶点带一个颜色值
	GLfloat vertices[] = {
		//位置					   //颜色
		 0.5f, -0.5f, 0.0f,        1.0f, 0.0f, 0.0f,		//右下
		-0.5f, -0.5f, 0.0f,        0.0f, 1.0f, 0.0f,		//左下
		 0.0f,  0.5f, 0.0f,        0.0f, 0.0f, 1.0f			//顶部
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
		//每次改变uniform变量，即改变了颜色值
		GLfloat timeValue = glfwGetTime(); 
		GLfloat greenValue = (sin(timeValue) / 2) + 0.5;								//让颜色值始终在0到1之间变化
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");	//得到uniform变量位置
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);					//修改颜色值，即从cpu程序中直接修改了片段着色器中ourColor的值
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