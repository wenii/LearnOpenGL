
#include <iostream>
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

//Callback function 键盘回调函数，当有键盘输入的时候窗口会调用该函数，用户可以在其内部对按键对按键进行处理，实现简单交互逻辑。
void Key_callBack(GLFWwindow* window, int key, int scancode, int action, int mode);

//Window dimensions 窗口尺寸，在创建窗口的时候使用
const GLuint WIDTH = 800, HEIGHT = 600;

//Vertex Shader 顶点着色器程序， 该程序是运行在GPU中的，程序采用GLSL(OpenGL Shading Language)语言，大多语法和C语言相同，先声明OpenGL版本号，声明变量，main函数。
const GLchar* vertexShaderSource = "#version 330 core\n"			//声明版本号，代表OpenGL3.3 core采用现代OpenGl
"layout (location = 0) in vec3 position;\n"							//声明变量
																	//loyout(location = 0) 声明了该变量在该着色器中的位置，该位置在cpu程序中会使用到
																	//in 代表该变量是一个输入的变量，数据要从外部获得
																	//vec3 代表一个具有三个float变量的数据类型，同样还有vec2， vec4，后面的数字代表内部几个数据
																	//position 变量名称，命名规则和C++相同
																	//position实际上代表的是一个顶点坐标，顶点着色器就是要接收所有的顶点，进行一些变换处理，然后传递给下一个着色器
																	//在本程序中用该变量来传递顶点数据

"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"	//gl_Position是一个预定义的变量，这个变量会输出给下一个着色器，这里把三分量的position给这个变量，
																	//而gl_Position是一个四分量的一个变量后面那个w分量给1.0
"}\n";

//Fragment Shader 片段着色器，该着色器是gpu处理的最后一个着色器
const GLchar* fragmentShaderSource = "#version 330 core\n"			//同顶点着色器一样声明OpenGL版本号
"out vec4 color;\n"													//定义一个四分量的颜色变量，该变量是一个输出变量
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"							//给颜色变量赋值，也是后面程序窗口生成的三角形的颜色
"}\n\0";

//图形的渲染大概要经历6个处理过程，按照渲染顺序分别是顶点着色器，形状着色器， 几何着色器，光栅化，片段着色器，测试与混合，其中顶点着色器和片段着色器是要我们
//自己实现的，其他的都有默认的处理方式

// The main function
int main()
{
	//使用GLFW库来创建窗口
	//init GLFW	初始化GLFW库
	glfwInit();
	//Set all the required options for GLFW 设置窗口相关参数
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						//设置版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);			
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Create a GLFWwindow oject that we can use for GLFW's functions	创建窗口
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);		//设置环境上下文

	//Set the required callback fucntions	设置窗口回调函数
	glfwSetKeyCallback(window, Key_callBack);	

	//Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions 主要让GLEW管理OpenGL函数指针的时候使用核心模式
	glewExperimental = GL_TRUE;

	//Init GLEW to setup the OpenGL Function pointers	//初始化GLEW
	glewInit();

	//Define the viewport dimensions	设置渲染窗口的大小，在本程序里面设置渲染窗口大小和窗口尺寸一样大
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	//Build and compile our shader program 编译和连接着色器程序，着色器程序是在程序运行的时候编译和连接的
	//Vertex shader 顶点着色器
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);				//生成顶点着色器
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);			//将顶点着色器和着色器代码联系起来
	glCompileShader(vertexShader);										//编译顶点着色器
	//Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);		    //检查顶点着色器编译过程是否有错误
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//Fragment shader 片段着色器
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
	//Link shaders 链接
	GLuint shaderProgram = glCreateProgram();					//生成着色器程序，最终要在绘图的时候使用
	glAttachShader(shaderProgram, vertexShader);				//将顶点着色器程序和着色器联系一起
	glAttachShader(shaderProgram, fragmentShader);				//将片段着色器程序和着色器联系一起
	glLinkProgram(shaderProgram);								//链接着色器程序
	//Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);	//检查链接是否出错
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);								//链接完之后可以删除着色器程序
	glDeleteShader(fragmentShader);
	/*
	//Set up vertex data		顶点数据，下面表示三个顶点分别时三角形的三个顶点，每个顶点的z坐标为0，代表在空间xy平面上的一个三角形
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,	//left
		 0.5f, -0.5f, 0.0f, //right
		 0.0f,  0.5f, 0.0f  //top
	};
	*/
	//索引缓冲对象，和VBO类似，该缓冲对象是为了解决顶点重复问题的，比如要绘制一个四边形需要4个顶点就可以了，但如果不使用索引缓冲对象的话就要6个顶点，即2个三角形
	//所以为了避免顶点重复而导致的内存浪费问题就有了索引缓冲对象。下面我们绘制一个四边形来应用一下索引缓冲对象
	
	GLfloat vertices[] = {	//四边形的四个顶点数据
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f };
	
	GLuint indices[] = { //两个三角形组成一个四边形，通过索引只需要四个顶点
		0, 1, 3,	//第一个三角形
		1, 2, 3 };	//第二个三角形
	

	GLuint VAO;							//顶点数组对象
	GLuint VBO;							//顶点缓冲对象
	GLuint EBO;							//索引缓冲对象
	glGenVertexArrays(1, &VAO);			//生成VAO顶点数组对象，在对数据进行处理之前绑定VAO，处理结束之后解绑，当要绘图时候只要再次绑定找个VAO就可以了，他会记录绑定后的一系列操作
	glGenBuffers(1, &VBO);				//生成VBO顶点缓冲对象，该对象会绑定到GL_ARRAY_BUFFER上，顶点数据会保存到GPU缓冲中，通过VBO对象标识具体的数据
	glGenBuffers(1, &EBO);				//生成EBO索引缓冲对象，该对象会绑定到GL_ELEMENT_ARRAY_BUFFER上
	//Bind the Vertex Array Object first, the bind and set vertex buffer and attribute pointer
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);			//绑定VBO到GL_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);	//绑定EBO到GL_ELEMENT_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);			//输入数据到绑定的缓冲中VBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);	//输入数据到绑定的缓冲中EBO

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); //告诉OpenGL如何解析顶点数据，由于顶点数据里面可能包含其他数据，比如说颜色，纹理坐标等，所以告诉OpenGL如何从GL_ARRAY_BUFFER中获取到相应的数据
						//第一个参数指定我猛药配置的顶点属性，0代表了我们在顶点着色器程序中定义的那个顶点变量 layout（location = 0）positioin，所以该参数指定我们要传入到顶点着色器中的那个变量
						//第二个参数指定顶点属性的大小，这里的3代表一个顶点3个数
						//第三个参数指定数据类型，这里是float类型
						//第四个参数表示是否要标准化，即都转换成-1到1之间的数
						//第五个参数叫做步长，相邻顶点起始位置之间的距离，单位是字节，因为我们顶点之间是连续的，并且每个顶点由三个float组成，所以这里为3*sizeof(float)
						//第六个参数指定第一个数据的偏移距离，由于我们程序中顶点数据在数据的开头，所以这里是0
	glEnableVertexAttribArray(0);	//使顶点数据可用，也就是顶点着色器中的position变量，默认是不可用的。

	glBindBuffer(GL_ARRAY_BUFFER, 0);	//取消绑定，一般操作完成后都要取消绑定，以防后面的误操作
	glBindVertexArray(0);

	//可以设置绘制为线框模式，这样绘制出来就是由线条组成的形状了
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);			//线框模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);			//默认模式

	//Game loop	//相当于消息循环，每次循环中绘制图像
	while (!glfwWindowShouldClose(window))
	{
		//Check if any events have been activiated (key pressed, mouse moved etc.) and call correspnding response functions
		glfwPollEvents();		//检查是否有事件输入

		//Render
		//Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);		//设置清理缓冲的颜色
		glClear(GL_COLOR_BUFFER_BIT);				//用上面设置的颜色清理缓冲

		//Draw our first triangle
		glUseProgram(shaderProgram);				//每次绘图时要调用该函数，用我们自己创建的着色器当参数
		glBindVertexArray(VAO);						//绑定VAO顶点数组对象，相当于进行了之前VAO绑定时的所有操作
		//glDrawArrays(GL_TRIANGLES, 0, 3);			//绘制三角形，第一个参数表示要绘制一个三角形，第二个参数表示顶点数据的起始索引，第三个参数表示要绘制多杀个顶点
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	//通过索引绘制三角形，第一个参数表示要绘制三角形，第二个参数指要绘制的顶点数，第三个参数表示索引的类型，第四个参数是EBO的偏移量
		glBindVertexArray(0);

		//Swap the screen buffers					//交换屏幕缓冲数据
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