SHADER(400 core,
	in vec3 color;\n
	in vec3 normal;\n
	in vec3 fragPos;\n
    out vec4 FragColor;\n

	uniform vec4 CustomColor = vec4(0.0,0.0,0.0,1.0);
    void main()\n
    {\n
		FragColor = CustomColor;\n
    }\n
)