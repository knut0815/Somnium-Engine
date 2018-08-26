	#version 330 core
	
	in vec3 basicCol;

	void main()
	{
		gl_FragColor = vec4(basicCol,1.0f);
	}
