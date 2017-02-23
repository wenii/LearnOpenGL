#version 330 core
struct Material
{
	vec3 ambient;			//环境光照下物体的颜色值
	vec3 diffuse;			//漫反射下物体的颜色值
	vec3 specular;			//镜面光照下物体的颜色值
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

uniform Light light;
uniform vec3 objectColor;
//uniform vec3 lightColor;
uniform Material material;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	//环境光
	vec3 ambient = light.ambient * material.ambient;

	//漫反射光
	vec3 norm = normalize(Normal);						//法向量
	vec3 lightDir = normalize(lightPos - FragPos);		//光向量
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	//镜面高光
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0f);


}