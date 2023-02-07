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

//shared int minix[20];
//shared int miniy[20];

void main()
{
    const float pi = 3.14159265359;
    float amplitude = signal[gl_WorkGroupID.y * gl_LocalInvocationID.x + gl_LocalInvocationID.x];
    float maxfreq = 50;
    float theta = pi * float(2 * maxfreq * gl_WorkGroupID.x * (gl_WorkGroupID.y * gl_LocalInvocationID.x + gl_LocalInvocationID.x)) / float(gl_NumWorkGroups.x * gl_NumWorkGroups.y * gl_WorkGroupSize.x);
    float x = amplitude * cos(theta);
    float y = -1.0 * amplitude * sin(theta);

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