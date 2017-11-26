#version 450 core
 
in vec4 vertexColor;
in vec2 vertexTexCoord;

out vec4 color;

uniform vec4 ourColor;

uniform sampler2D albedo;
uniform sampler2D normal;

void main() {
	//color = texture2D(texture, vertexTexCoord) + vertexColor + ourColor;
	//color = texture2D(texture, vertexTexCoord);
	//color = texture2D(albedo, vertexTexCoord);
	color = mix(texture2D(albedo, vertexTexCoord), texture2D(normal, vertexTexCoord), 0.10);
}