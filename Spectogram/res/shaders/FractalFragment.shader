#version 460 core

out vec4 color;

in vec2 gl_FragCoord;

uniform vec3 coloffset;
uniform dvec2 translate;
uniform double scale = 1.0;
uniform unsigned int dimx;
uniform unsigned int dimy;
uniform int maxIter = 600;

uniform float distfac = 0.3;
uniform float shift = 2.0;

void main()
{
	dvec2 coor = vec2(gl_FragCoord.x - (dimx >> 1), gl_FragCoord.y - (dimy >> 1));
	double size = double(dimx);
	dvec2 c = translate + scale * (coor / size);

	double x = 0.0;
	double y = 0.0;
	double xx = 0.0;
	double yy = 0.0;

	//double a = 0.0;
	//double a0 = 0.0;
	//double dx = 0.0;
	//double dy = 0.0;
	//double dx0 = 0.0;
	//double dy0 = 0.0;
	double x0 = 0.0;
	double y0 = 0.0;
	//double dxSum = 0.0;
	//double dySum = 0.0;
	double r = 0.0;
	int	iter = 0;
	//dxSum * dxSum + dySum * dySum <= 1e12
	while (xx + yy <= 4.0 && iter < maxIter) {
		x0 = x;
		y0 = y;
		y = 2.0 * x * y + c.y;
		x = xx - yy + c.x;
		xx = x * x;
		yy = y * y;
		iter += 1;

		//dx = x - c.x;
		//dy = y - c.y;
		//dx0 = x0 - c.x;
		//dy0 = y0 - c.y;
		//a += abs((dx*dx0 + dy*dy0) / (sqrt(dx*dx + dy*dy) * sqrt(dx0*dx0 + dy0*dy0)));
		





		//double y0 = y;
		//double x0 = x;
		//double otherx = x * x - y*y + c.x;
		//y = 2.0 * x * y + c.y;
		//x = otherx;
		//
		//dxSum += ((x - x0) * x - (y - y0) * y) * 2.0 + 1.0;
		//dySum += ((y - y0) * x + (x - x0) * y) * 2.0;
		//iter += 1;

		r += (x - x0) * (x - x0) + (y - y0) * (y - y0);

	}
	r -= (x - x0) * (x - x0) + (y - y0) * (y - y0);
	
	float dist = distfac * float(r) / (16.0*float(iter));
	float col2;
	float col3;
	float col = float(iter) / float(maxIter);
	col2 = ((sin(coloffset.g + (shift + 3.14159265 * col * 10.0)/(dist+(1.0 - distfac)) ) + 1.0) / 2.0);
	col3 = ((sin(coloffset.b + (shift + 3.14159265 * col * 10.0)/(dist+(1.0 - distfac)) ) + 1.0) / 2.0);
	col  = ((sin(coloffset.r + (shift + 3.14159265 * col * 10.0)/(dist+(1.0 - distfac)) ) + 1.0) / 2.0);

	color = vec4(col, col2, col3, 1.0);
}