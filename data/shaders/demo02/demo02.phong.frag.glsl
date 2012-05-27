#version 330

struct LightProperties
{
    vec3 direction;
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
};

struct MaterialProperties
{
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
    float specularExponent;
};

uniform LightProperties    uLight;
uniform MaterialProperties uMaterial;

in vec3 vEye;
in vec3 vNormal;
in vec4 temp;

layout(location = 0, index = 0) out vec4 fragColor;

void main(void)
{
    // All calculations are in camera space.
    vec4 color = uLight.ambientColor * uMaterial.ambientColor;
    vec3 normal = normalize(vNormal);
    float nDotL = max(dot(uLight.direction, normal), 0.0);        
    if (nDotL > 0.0)
    {
        vec3 eye = normalize(vEye);    
        // Incident vector is opposite light direction vector.
        vec3 reflection = reflect(-uLight.direction, normal);        
        float eDotR = max(dot(eye, reflection), 0.0);    
        color += uLight.diffuseColor * uMaterial.diffuseColor * nDotL;        
        color += uLight.specularColor * uMaterial.specularColor * pow(eDotR, uMaterial.specularExponent);
    }
    fragColor = color;    
    
}
