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
	int maxIter = 100;

	float x = 0.0;
	float y = 0.0;
	float dxSum = 0.0;
	float dySum = 0.0;
	int	iter = 0;
	while (sqrt(dxSum*dxSum+dySum*dySum) <= 1e12 && iter < maxIter) {
		float y0 = y;
		float x0 = x;
		float otherx = x * x - y*y + c.x;
		y = 2.0 * x * y + c.y;
		x = otherx;

		dxSum += ((x - x0) * x - (y - y0) * y) * 2.0 + 1.0;
		dySum += ((y - y0) * x + (x - x0) * y) * 2.0;
		iter += 1;

		//r += (x - xtempp) * (x - xtempp) + (y - ytemp) * (y - ytemp);

	}


	//float col3 = r / (4.0*fIter);
	float col2;
	float col = float(iter) / float(maxIter);
	col2 = sqrt(col);

	color = vec4(col, col2, col2, 1.0);
}