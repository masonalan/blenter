#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct Flashlight {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutoff;
    float outerCutoff;
};

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 ModelPos;

uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;
uniform sampler2D tex4;
uniform sampler2D tex5;
uniform sampler2D tex6;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform DirectionalLight dirLight;
uniform PointLight posLight;
uniform Flashlight flashlight;
uniform vec3 edge;
uniform bool mouseDown;
uniform bool useTexture;
uniform vec4 fillColor;
uniform vec4 borderColor;
uniform bool useMultiTextures;
uniform bool focused;
uniform bool selected;
uniform float borderWidth;
uniform bool showGrid;

void main()
{
    // Ambient light (there is always some baseline amount of light in a scene)
    //float ambientStrength = 0.1;


    vec4 color = vec4(0);

    if (useMultiTextures) {
        if (ModelPos.z == 0.5 || ModelPos.z == -0.5) {
            color = texture(tex1, TexCoord);
        }
        else if (ModelPos.x == 0.5 || ModelPos.x == -0.5) {
            color = texture(tex2, TexCoord);
        }
        else if (ModelPos.y == 0.5 || ModelPos.y == -0.5) {
            color = texture(tex3, TexCoord);
        }
    } else {
        color = texture(tex1, TexCoord);
    }

    if (!useTexture) {
        color = fillColor;
    }
    FragColor = color;
    FragPos;

    vec4 selCol = mix(color, vec4(mouseDown ? 0.6 : 1, 0, 0, 1), 0.5);

    if (edge.z != 0) {
        if (ModelPos.z == edge.z) {
            FragColor = selCol;
        }
    } else if (edge.x != 0) {
        if (ModelPos.x == edge.x) {
            FragColor = selCol;
        }
    } else if (edge.y != 0) {
        if (ModelPos.y == edge.y) {
            FragColor = selCol;
        }
    }

    //    if (selected) {
    //        float thresh = 0.4;
    //        if (ModelPos.x < -thresh || ModelPos.x > thresh || ModelPos.y > thresh || ModelPos.y < -thresh) {
    //            float f = mouseDown ? 0.6f : 1.f;
    //            FragColor = vec4(borderColor.xyz * f, 1.f);
    //        }
    //    }
    //
    //
    //    if (focused) {
    float thresh = borderWidth;
    if (ModelPos.x < -thresh || ModelPos.x > thresh || ModelPos.y > thresh || ModelPos.y < -thresh) {
        float f = mouseDown ? 0.6f : 1.f;
        FragColor = vec4(borderColor.xyz * f, 1.f);
    }
    //    }

    float subGridStep = 0.1f;
    float gridStep = 0.5f;
    float gridWidth = 0.003f;

    if (showGrid) {
        if (mod(FragPos.x, gridStep) < gridWidth || mod(FragPos.z, gridStep) < gridWidth) {
            FragColor = color;
        } else if (mod(FragPos.x, subGridStep) < gridWidth || mod(FragPos.z, subGridStep) < gridWidth) {
            FragColor = color * 1.3f;
        } else {
            FragColor = vec4(0, 0, 0, 0);
        }
    }



    return;
    //
    //    float distance    = length(posLight.position - FragPos);
    //    float attenuation = 1.0 / (posLight.constant + posLight.linear * distance + posLight.quadratic * (distance * distance));
    //
    //    vec3 ambient = flashlight.ambient * color;
    //    //ambient *= attenuation;
    //
    //    // Diffuse lightinge
    //    vec3 norm = normalize(Normal);
    //    //vec3 lightDir = normalize(-dirLight.direction);
    //    vec3 lightDir = normalize(flashlight.position - FragPos);
    //
    //    float theta = dot(lightDir, normalize(-flashlight.direction));
    //    float epsilon   = flashlight.cutoff - flashlight.outerCutoff;
    //    float intensity = clamp((theta - flashlight.outerCutoff) / epsilon, 0.0, 1.0);
    //
    //    //if (theta > flashlight.outerCutoff) {
    //
    //        float diff = max(dot(norm, lightDir), 0.0);
    //        vec3 diffuse = flashlight.diffuse * (diff * color);
    //        //diffuse *= attenuation;
    //        diffuse *= intensity;
    //
    //        // Specular lighting
    //        vec3 viewDir = normalize(viewPos - FragPos);
    //        vec3 reflectDir = reflect(-lightDir, norm);
    //        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //        vec3 specular = flashlight.specular * (material.specular * spec);
    //        //specular *= attenuation;
    //        specular *= intensity;
    //
    //        FragColor = vec4((ambient + diffuse + specular), 1.0);
    //
    ////    } else {
    ////
    ////        FragColor = vec4(ambient * color, 1.0);
    ////    }
}