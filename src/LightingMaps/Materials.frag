#version 330 core
struct Material
{
	sampler2D diffuse;		//贴图
	sampler2D specular;		//镜面光照下物体的颜色值
	float shininess;		//影响镜面高光的散射半径
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


out vec4 color;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform Light light;
uniform Material material;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	//环境光
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	//漫反射光
	vec3 norm = normalize(Normal);								//法向量
	vec3 lightDir = normalize(light.position - FragPos);		//光向量
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

	//镜面高光
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0f);


}