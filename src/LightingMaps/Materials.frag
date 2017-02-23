#version 330 core
struct Material
{
	sampler2D diffuse;		//��ͼ
	sampler2D specular;		//����������������ɫֵ
	float shininess;		//Ӱ�쾵��߹��ɢ��뾶
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
	//������
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	//�������
	vec3 norm = normalize(Normal);								//������
	vec3 lightDir = normalize(light.position - FragPos);		//������
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

	//����߹�
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0f);


}