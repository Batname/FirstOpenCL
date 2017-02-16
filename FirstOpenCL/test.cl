kernel void vecadd(global float4* a, global float4 *b, global float4* c) {
    size_t i = get_global_id(0);
    c[i] = a[i] + b[i];
}
