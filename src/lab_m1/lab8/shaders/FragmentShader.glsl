#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform float cut_off_angle;

uniform int is_spot;

// TODO(student): Declare any other uniforms
uniform vec3 second_light_position;
uniform vec3 object_color;

// Output
layout(location = 0) out vec4 out_color;

float point_light_contribution(vec3 light_pos, int spot)
{
    vec3 L = normalize(light_pos - world_position);
    vec3 V = normalize(eye_position - world_position);
    vec3 H = normalize(L + V);
    
    float diffuse_light = material_kd * max(dot(world_normal, L), 0);
    
    float specular_light = 0;
    if (diffuse_light > 0)
    {
        vec3 R = reflect(-L, world_normal);
        specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
    }

    float light_att_factor = 1;

    if (spot == 1) {
        float cut_off = radians(cut_off_angle);
        float spot_light = dot(-L, light_direction);
        float spot_light_limit = cos(cut_off);

        if (spot_light > spot_light_limit) {
            float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
            light_att_factor = pow(linear_att, 2);
        } else {
            light_att_factor = 0;
        }
        
    }

    float light = 1 / (distance(light_pos, world_position)) * (diffuse_light + specular_light) * light_att_factor;
    return light;
}

void main()
{
    float ambient_light = material_kd * 0.25;
    float lights = ambient_light + point_light_contribution(light_position, is_spot) + point_light_contribution(second_light_position, 0);

    // TODO(student): Write pixel out color
    out_color = vec4(object_color * lights, 1);

}
