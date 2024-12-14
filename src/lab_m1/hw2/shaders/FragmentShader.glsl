#version 330

// Input
in vec3 world_position;
in vec3 world_normal;
in float noise_value;

// Output
layout(location = 0) out vec4 out_color;

void main()
{
    // TODO(student): Write pixel out color
    out_color = mix(vec4(1, 0, 0, 1), vec4(0, 1, 0, 1), noise_value);
}
