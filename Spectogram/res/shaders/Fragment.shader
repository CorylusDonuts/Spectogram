#version 460 core

out vec4 color;

in vec2 gl_FragCoord;

uniform vec2 translate;
uniform float scale = 1.0;
uniform unsigned int dim;


void main()
{
	vec2 coor = vec2(gl_FragCoord - (dim >> 1));
	float size = float(dim);
	vec2 c = translate + scale * (coor / size);
	float x = 0.0;
	float y = 0.0;
	float xx = 0.0;
	float yy = 0.0;
	float iter = 0.0;
	float r = 0.0;
	while (xx + yy <= 4.0 && iter < 100) {
		y = 2.0 * x * y + c.y;
		x = xx - yy + c.x;
		xx = x * x;
		yy = y * y;
		iter += 1;

		//r += (x - xtempp) * (x - xtempp) + (y - ytemp) * (y - ytemp);
		
	}
	
	float fIter = float(iter);

	//float col3 = r / (4.0*fIter);
	float col2;
	float col = fIter / 100.0;
	col2 = sqrt(col);

	color = vec4(col, col2, col2, 1.0);
}