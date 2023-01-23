#version 460 core


layout(local_size_x = 64, local_size_y = 1, local_size_z = 1) in;

layout(std430, binding = 3) buffer signals {
    float signal[];
};

layout(std430, binding = 4) buffer frequencies {
    float frequency[];
};

shared int sumX;
shared int sumY;

void main()
{
    float amplitude = signal[gl_LocalInvocationID.x];
    float num = 50;
    float winding = float(num * gl_WorkGroupID.x * gl_LocalInvocationID.x) / (64.0 * 64.0);
    float x = amplitude * cos(2.0 * 3.14159265359 * winding);
    float y = -1.0 * amplitude * sin(2.0 * 3.14159265359 * winding);

    if (gl_LocalInvocationID.x == 1) {
        sumX = 0;
        sumY = 0;
    }

    memoryBarrier();
    barrier();

    atomicAdd(sumX, int(1000000 * x));
    atomicAdd(sumY, int(1000000 * y));

    memoryBarrier();
    barrier();

    if (gl_LocalInvocationID.x == 1) {
        float xx = float(sumX) / 1000000.0;
        float yy = float(sumY) / 1000000.0;
        float res = sqrt(xx*xx + yy*yy) / 64.0;
        frequency[gl_WorkGroupID.x] = res;
    }
}