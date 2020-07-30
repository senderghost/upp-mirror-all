SHADER(400 core,
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec3 aNorm;
	layout (location = 2) in vec3 aColor;

	out vec3 fs_normal;
	out vec3 fs_fragPos;
	out vec3 fs_color;
	

	uniform mat4 ModelMatrix;
	uniform mat4 ProjectionMatrix;
    uniform mat4 ViewMatrix;

    void main()
    {
		gl_Position =  ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(aPos, 1.0);

		fs_fragPos = vec3(ModelMatrix * vec4(aPos, 1.0));
		fs_color = aColor;
		fs_normal = aNorm;
    }
)