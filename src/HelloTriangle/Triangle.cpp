
#include <iostream>
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

//Callback function ���̻ص����������м��������ʱ�򴰿ڻ���øú������û����������ڲ��԰����԰������д���ʵ�ּ򵥽����߼���
void Key_callBack(GLFWwindow* window, int key, int scancode, int action, int mode);

//Window dimensions ���ڳߴ磬�ڴ������ڵ�ʱ��ʹ��
const GLuint WIDTH = 800, HEIGHT = 600;

//Vertex Shader ������ɫ������ �ó�����������GPU�еģ��������GLSL(OpenGL Shading Language)���ԣ�����﷨��C������ͬ��������OpenGL�汾�ţ�����������main������
const GLchar* vertexShaderSource = "#version 330 core\n"			//�����汾�ţ�����OpenGL3.3 core�����ִ�OpenGl
"layout (location = 0) in vec3 position;\n"							//��������
																	//loyout(location = 0) �����˸ñ����ڸ���ɫ���е�λ�ã���λ����cpu�����л�ʹ�õ�
																	//in ����ñ�����һ������ı���������Ҫ���ⲿ���
																	//vec3 ����һ����������float�������������ͣ�ͬ������vec2�� vec4����������ִ����ڲ���������
																	//position �������ƣ����������C++��ͬ
																	//positionʵ���ϴ������һ���������꣬������ɫ������Ҫ�������еĶ��㣬����һЩ�任����Ȼ�󴫵ݸ���һ����ɫ��
																	//�ڱ��������øñ��������ݶ�������

"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"	//gl_Position��һ��Ԥ����ı���������������������һ����ɫ�����������������position�����������
																	//��gl_Position��һ���ķ�����һ�����������Ǹ�w������1.0
"}\n";

//Fragment Shader Ƭ����ɫ��������ɫ����gpu��������һ����ɫ��
const GLchar* fragmentShaderSource = "#version 330 core\n"			//ͬ������ɫ��һ������OpenGL�汾��
"out vec4 color;\n"													//����һ���ķ�������ɫ�������ñ�����һ���������
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"							//����ɫ������ֵ��Ҳ�Ǻ�����򴰿����ɵ������ε���ɫ
"}\n\0";

//ͼ�ε���Ⱦ���Ҫ����6��������̣�������Ⱦ˳��ֱ��Ƕ�����ɫ������״��ɫ���� ������ɫ������դ����Ƭ����ɫ�����������ϣ����ж�����ɫ����Ƭ����ɫ����Ҫ����
//�Լ�ʵ�ֵģ������Ķ���Ĭ�ϵĴ���ʽ

// The main function
int main()
{
	//ʹ��GLFW������������
	//init GLFW	��ʼ��GLFW��
	glfwInit();
	//Set all the required options for GLFW ���ô�����ز���
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						//���ð汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);			
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Create a GLFWwindow oject that we can use for GLFW's functions	��������
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);		//���û���������

	//Set the required callback fucntions	���ô��ڻص�����
	glfwSetKeyCallback(window, Key_callBack);	

	//Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions ��Ҫ��GLEW����OpenGL����ָ���ʱ��ʹ�ú���ģʽ
	glewExperimental = GL_TRUE;

	//Init GLEW to setup the OpenGL Function pointers	//��ʼ��GLEW
	glewInit();

	//Define the viewport dimensions	������Ⱦ���ڵĴ�С���ڱ���������������Ⱦ���ڴ�С�ʹ��ڳߴ�һ����
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	//Build and compile our shader program �����������ɫ��������ɫ���������ڳ������е�ʱ���������ӵ�
	//Vertex shader ������ɫ��
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);				//���ɶ�����ɫ��
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);			//��������ɫ������ɫ��������ϵ����
	glCompileShader(vertexShader);										//���붥����ɫ��
	//Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);		    //��鶥����ɫ����������Ƿ��д���
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//Fragment shader Ƭ����ɫ��
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);		
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILEATION_FAILED\n" << infoLog << std::endl;
	}
	//Link shaders ����
	GLuint shaderProgram = glCreateProgram();					//������ɫ����������Ҫ�ڻ�ͼ��ʱ��ʹ��
	glAttachShader(shaderProgram, vertexShader);				//��������ɫ���������ɫ����ϵһ��
	glAttachShader(shaderProgram, fragmentShader);				//��Ƭ����ɫ���������ɫ����ϵһ��
	glLinkProgram(shaderProgram);								//������ɫ������
	//Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);	//��������Ƿ����
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);								//������֮�����ɾ����ɫ������
	glDeleteShader(fragmentShader);
	/*
	//Set up vertex data		�������ݣ������ʾ��������ֱ�ʱ�����ε��������㣬ÿ�������z����Ϊ0�������ڿռ�xyƽ���ϵ�һ��������
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,	//left
		 0.5f, -0.5f, 0.0f, //right
		 0.0f,  0.5f, 0.0f  //top
	};
	*/
	//����������󣬺�VBO���ƣ��û��������Ϊ�˽�������ظ�����ģ�����Ҫ����һ���ı�����Ҫ4������Ϳ����ˣ��������ʹ�������������Ļ���Ҫ6�����㣬��2��������
	//����Ϊ�˱��ⶥ���ظ������µ��ڴ��˷����������������������������ǻ���һ���ı�����Ӧ��һ�������������
	
	GLfloat vertices[] = {	//�ı��ε��ĸ���������
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f };
	
	GLuint indices[] = { //�������������һ���ı��Σ�ͨ������ֻ��Ҫ�ĸ�����
		0, 1, 3,	//��һ��������
		1, 2, 3 };	//�ڶ���������
	

	GLuint VAO;							//�����������
	GLuint VBO;							//���㻺�����
	GLuint EBO;							//�����������
	glGenVertexArrays(1, &VAO);			//����VAO������������ڶ����ݽ��д���֮ǰ��VAO���������֮���󣬵�Ҫ��ͼʱ��ֻҪ�ٴΰ��Ҹ�VAO�Ϳ����ˣ������¼�󶨺��һϵ�в���
	glGenBuffers(1, &VBO);				//����VBO���㻺����󣬸ö����󶨵�GL_ARRAY_BUFFER�ϣ��������ݻᱣ�浽GPU�����У�ͨ��VBO�����ʶ���������
	glGenBuffers(1, &EBO);				//����EBO����������󣬸ö����󶨵�GL_ELEMENT_ARRAY_BUFFER��
	//Bind the Vertex Array Object first, the bind and set vertex buffer and attribute pointer
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);			//��VBO��GL_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);	//��EBO��GL_ELEMENT_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);			//�������ݵ��󶨵Ļ�����VBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);	//�������ݵ��󶨵Ļ�����EBO

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); //����OpenGL��ν����������ݣ����ڶ�������������ܰ����������ݣ�����˵��ɫ����������ȣ����Ը���OpenGL��δ�GL_ARRAY_BUFFER�л�ȡ����Ӧ������
						//��һ������ָ������ҩ���õĶ������ԣ�0�����������ڶ�����ɫ�������ж�����Ǹ�������� layout��location = 0��positioin�����Ըò���ָ������Ҫ���뵽������ɫ���е��Ǹ�����
						//�ڶ�������ָ���������ԵĴ�С�������3����һ������3����
						//����������ָ���������ͣ�������float����
						//���ĸ�������ʾ�Ƿ�Ҫ��׼��������ת����-1��1֮�����
						//����������������������ڶ�����ʼλ��֮��ľ��룬��λ���ֽڣ���Ϊ���Ƕ���֮���������ģ�����ÿ������������float��ɣ���������Ϊ3*sizeof(float)
						//����������ָ����һ�����ݵ�ƫ�ƾ��룬�������ǳ����ж������������ݵĿ�ͷ������������0
	glEnableVertexAttribArray(0);	//ʹ�������ݿ��ã�Ҳ���Ƕ�����ɫ���е�position������Ĭ���ǲ����õġ�

	glBindBuffer(GL_ARRAY_BUFFER, 0);	//ȡ���󶨣�һ�������ɺ�Ҫȡ���󶨣��Է�����������
	glBindVertexArray(0);

	//�������û���Ϊ�߿�ģʽ���������Ƴ���������������ɵ���״��
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);			//�߿�ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);			//Ĭ��ģʽ

	//Game loop	//�൱����Ϣѭ����ÿ��ѭ���л���ͼ��
	while (!glfwWindowShouldClose(window))
	{
		//Check if any events have been activiated (key pressed, mouse moved etc.) and call correspnding response functions
		glfwPollEvents();		//����Ƿ����¼�����

		//Render
		//Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);		//�������������ɫ
		glClear(GL_COLOR_BUFFER_BIT);				//���������õ���ɫ������

		//Draw our first triangle
		glUseProgram(shaderProgram);				//ÿ�λ�ͼʱҪ���øú������������Լ���������ɫ��������
		glBindVertexArray(VAO);						//��VAO������������൱�ڽ�����֮ǰVAO��ʱ�����в���
		//glDrawArrays(GL_TRIANGLES, 0, 3);			//���������Σ���һ��������ʾҪ����һ�������Σ��ڶ���������ʾ�������ݵ���ʼ������������������ʾҪ���ƶ�ɱ������
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	//ͨ���������������Σ���һ��������ʾҪ���������Σ��ڶ�������ָҪ���ƵĶ�������������������ʾ���������ͣ����ĸ�������EBO��ƫ����
		glBindVertexArray(0);

		//Swap the screen buffers					//������Ļ��������
		glfwSwapBuffers(window);

	}
	//Properly de_allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//Terminate GLFW, clearing any resource allocated by GLFW.
	glfwTerminate();
	return 0;

}

//Is called whenever akey is pressed/released via GLFW
void Key_callBack(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}