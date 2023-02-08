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

shared float minix[gl_WorkGroupSize.x];
shared float miniy[gl_WorkGroupSize.x];

void main()
{
    unsigned int tid = gl_LocalInvocationID.x;
    unsigned int max_tid = gl_WorkGroupSize.x;
    unsigned int localID = gl_WorkGroupID.y * tid + tid;
    const float pi = 3.14159265359;

    float amplitude = signal[localID];
    float maxfreq = 50;
    float theta = pi * float(2 * maxfreq * gl_WorkGroupID.x * localID) / float(gl_NumWorkGroups.x * (gl_NumWorkGroups.y * max_tid));
    minix[gl_LocalInvocationID.x] = amplitude * cos(theta);
    miniy[gl_LocalInvocationID.x] = -1.0 * amplitude * sin(theta);
    
    
    memoryBarrierShared();
    barrier();
    if (tid < 32) {
        minix[tid] = minix[tid] + minix[tid + 32];
        miniy[tid] = miniy[tid] + miniy[tid + 32];
    }
    memoryBarrierShared();
    barrier();
    if (tid < 16) {
        minix[tid] = minix[tid] + minix[tid + 16];
        miniy[tid] = miniy[tid] + miniy[tid + 16];
    }
    memoryBarrierShared();
    barrier();
    if (tid < 8) {
        minix[tid] = minix[tid] + minix[tid + 8];
        miniy[tid] = miniy[tid] + miniy[tid + 8];
    }
    memoryBarrierShared();
    barrier();
    if (tid < 4) {
        minix[tid] = minix[tid] + minix[tid + 4];
        miniy[tid] = miniy[tid] + miniy[tid + 4];
    }
    memoryBarrierShared();
    barrier();
    if (tid == 0) {
        minix[tid] = minix[tid] + minix[tid + 1] + minix[tid + 2] + minix[tid + 3];
        miniy[tid] = miniy[tid] + miniy[tid + 1] + miniy[tid + 2] + miniy[tid + 3];
        frequency[gl_WorkGroupID.x] = sqrt(minix[tid] * minix[tid] + miniy[tid] * miniy[tid]) / max_tid;
    }
}