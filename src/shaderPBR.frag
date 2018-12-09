#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse1;
// parametry materiałowe
uniform float metallic;
uniform float roughness;
uniform float ao;

// światła
struct PointLight {
    vec3 position;
    vec3 color;
};

struct DirLight {
    vec3 direction;
    vec3 color;
    float lightStrength;
};

struct SpotLight{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    vec3 color; 
};
uniform PointLight pointLight;
uniform DirLight dirLight;
uniform SpotLight spotLight[2];

uniform vec3 camPos;
const float PI = 3.14159265359;

float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySchlickGGX(float NdotV, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0);
vec3 calculatePointLight(vec3 albedo, vec3 N, vec3 V);
vec3 calculateDirLight(vec3 albedo, vec3 N, vec3 V);
vec3 calculateSpotLight(vec3 albedo, vec3 N, vec3 V, SpotLight light);
void main()
{
    vec3 albedo  = vec3(texture(texture_diffuse1, TexCoords));
    vec3 N = normalize(Normal);
    vec3 V = normalize(camPos - FragPos);
    
    vec3 color = vec3(0);
    color += calculatePointLight(albedo, N, V);
    color += calculateDirLight(albedo, N, V);
    for(int i = 0; i < 2; i++)
        color += calculateSpotLight(albedo, N, V, spotLight[i]);
    FragColor = vec4(color, 1.0);
}
vec3 calculateSpotLight(vec3 albedo, vec3 N, vec3 V, SpotLight light)
{
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    // równanie odbicia
    vec3 Lo = vec3(0.0);
    // obliczy radiancję per-światło
    vec3 L = normalize(light.position - FragPos);
    vec3 H = normalize(V + L);
    
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (distance * distance);
    vec3 radiance     = light.color * attenuation;        

    // cook-torrance brdf
    float NDF = DistributionGGX(N, H, roughness);
    float NdotV = max(dot(N,V),0);
    float G   = GeometrySchlickGGX(NdotV, roughness);             
    //float G   = GeometrySmith(N, V, L, roughness);      
    vec3 F    = fresnelSchlickRoughness(max(dot(H, V), 0.0), F0);       

    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;	  

    vec3 numerator    = NDF * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
    vec3 specular     = numerator / max(denominator, 0.001);  

    // dodaj do wynikowej radiancji Lo
    float NdotL = max(dot(N, L), 0.0);                
    Lo += (kD * albedo / PI + specular) * radiance * NdotL;  

    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + Lo;

    //spotlight (miękkie krawędzie)
    float theta = dot(L, normalize(-light.direction)); 
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    color *= intensity;
    color = color / (color + vec3(1.0));
    return color = pow(color, vec3(1.0/2.2)); 
}

vec3 calculatePointLight(vec3 albedo, vec3 N, vec3 V)
{
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    // równanie odbicia
    vec3 Lo = vec3(0.0);
    // obliczy radiancję per-światło
    vec3 L = normalize(pointLight.position - FragPos);
    vec3 H = normalize(V + L);
    float distance    = length(pointLight.position - FragPos);
    float attenuation = 1.0 / (distance * distance);
    vec3 radiance     = pointLight.color * attenuation;        

    // cook-torrance brdf
    float NDF = DistributionGGX(N, H, roughness);
    float NdotV = max(dot(N,V),0);
    float G   = GeometrySchlickGGX(NdotV, roughness);             
    //float G   = GeometrySmith(N, V, L, roughness);      
    vec3 F    = fresnelSchlickRoughness(max(dot(H, V), 0.0), F0);       

    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;	  

    vec3 numerator    = NDF * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
    vec3 specular     = numerator / max(denominator, 0.001);  

    // dodaj do wynikowej radiancji Lo
    float NdotL = max(dot(N, L), 0.0);                
    Lo += (kD * albedo / PI + specular) * radiance * NdotL;  

    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + Lo;

    color = color / (color + vec3(1.0));
    return color = pow(color, vec3(1.0/2.2)); 
}

vec3 calculateDirLight(vec3 albedo, vec3 N, vec3 V)
{
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    // równanie odbicia
    vec3 Lo = vec3(0.0);
    // obliczy radiancję per-światło
    vec3 L = normalize(dirLight.direction); //kierunek, z którego pada światło
    vec3 H = normalize(V + L);
    vec3 radiance     = dirLight.color * dirLight.lightStrength;        

    // cook-torrance brdf
    float NDF = DistributionGGX(N, H, roughness);
    float NdotV = max(dot(N,V),0);
    float G   = GeometrySchlickGGX(NdotV, roughness);             
    //float G   = GeometrySmith(N, V, L, roughness);      
    vec3 F    = fresnelSchlickRoughness(max(dot(H, V), 0.0), F0);       

    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;	  

    vec3 numerator    = NDF * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
    vec3 specular     = numerator / max(denominator, 0.001);  

    // dodaj do wynikowej radiancji Lo
    float NdotL = max(dot(N, L), 0.0);                
    Lo += (kD * albedo / PI + specular) * radiance * NdotL;  

    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + Lo;

    color = color / (color + vec3(1.0));
    return color = pow(color, vec3(1.0/2.2)); 
}

vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0)
{
    //F0 - odbicie powierzchniowe przy zerowym kącie padania
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}

//rzucanie cieni przez mikrościanki (zależy od chropowatości)
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}