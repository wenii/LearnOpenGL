#version 330 core
struct Material
{
	vec3 ambient;			//�����������������ɫֵ
	vec3 diffuse;			//���������������ɫֵ
	vec3 specular;			//����������������ɫֵ
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

uniform Light light;
uniform vec3 objectColor;
//uniform vec3 lightColor;
uniform Material material;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	//������
	vec3 ambient = light.ambient * material.ambient;

	//�������
	vec3 norm = normalize(Normal);						//������
	vec3 lightDir = normalize(lightPos - FragPos);		//������
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	//����߹�
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0f);


}