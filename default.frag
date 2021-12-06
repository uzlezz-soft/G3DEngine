#version 330 core

out vec4 FragColor;

in vec3 Position;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;

uniform vec3 camPos;
uniform float time;

struct DirLight {
	vec3 direction;
	vec4 diffuse;
	float ambient;
	float intensity;
};
uniform DirLight directionalLight;

struct PointLight {    
	vec3 position;
	
	float constant;
	float linear;
	float quadratic;
	
	vec4 diffuse;
	float ambient;
};
#define NR_POINT_LIGHTS 1
uniform PointLight pointLights[NR_POINT_LIGHTS];

/*struct SpotLight {
	vec3 position;
	vec3 direction;

	float innerCone;
	float outerCone;

	vec4 diffuse;
	float ambient;
};
#define NR_SPOT_LIGHTS 0
uniform SpotLight spotLights[NR_SPOT_LIGHTS];*/

vec4 direcLight(DirLight light)
{
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(light.direction);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	return (diffuse * light.intensity + light.ambient) * light.diffuse;
}

vec4 pointLight(PointLight light)
{	
	// used in two variables so I calculate it here to not have to do it twice
	vec3 lightVec = light.position - Position;

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float inten = 1.0f / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

	// ambient lighting
	float ambient = light.ambient;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	return (diffuse * inten + ambient) * light.diffuse;
}

/*vec4 spotLight(SpotLight light)
{
	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(light.direction);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// calculates the intensity of the crntPos based on its angle to the center of the light cone
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - light.outerCone) / (light.innerCone - light.outerCone), 0.0f, 1.0f);

	return (diffuse * inten + light.ambient) * light.diffuse;
}*/

void main()
{
	vec4 diffuse = texture(diffuse0, texCoord);

	diffuse *= direcLight(directionalLight);

	for (int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		diffuse *= pointLight(pointLights[i]);
	}

	FragColor = diffuse;
}