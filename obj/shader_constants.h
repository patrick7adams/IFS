#ifndef SHADER_CONSTANTS_H
#define SHADER_CONSTANTS_H
unsigned char shaders_vertex_glsl[] = {
  0x23, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x20, 0x33, 0x33, 0x30,
  0x20, 0x63, 0x6f, 0x72, 0x65, 0x0a, 0x6c, 0x61, 0x79, 0x6f, 0x75, 0x74,
  0x20, 0x28, 0x6c, 0x6f, 0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x3d,
  0x20, 0x30, 0x29, 0x20, 0x69, 0x6e, 0x20, 0x76, 0x65, 0x63, 0x32, 0x20,
  0x76, 0x65, 0x72, 0x74, 0x69, 0x63, 0x65, 0x73, 0x3b, 0x0a, 0x0a, 0x6f,
  0x75, 0x74, 0x20, 0x76, 0x65, 0x63, 0x33, 0x20, 0x6e, 0x65, 0x77, 0x5f,
  0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x73, 0x3b, 0x0a, 0x0a, 0x76, 0x6f, 0x69,
  0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x28, 0x29, 0x20, 0x7b, 0x0a, 0x20,
  0x20, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69,
  0x6f, 0x6e, 0x20, 0x3d, 0x20, 0x76, 0x65, 0x63, 0x34, 0x28, 0x76, 0x65,
  0x72, 0x74, 0x69, 0x63, 0x65, 0x73, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x2c,
  0x20, 0x31, 0x2e, 0x30, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6e,
  0x65, 0x77, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x73, 0x20, 0x3d, 0x20,
  0x76, 0x65, 0x63, 0x33, 0x28, 0x31, 0x2e, 0x30, 0x2c, 0x20, 0x31, 0x2e,
  0x30, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x29, 0x3b, 0x0a, 0x7d, 0x00
};
unsigned int shaders_vertex_glsl_len = 178;
unsigned char shaders_fragment_glsl[] = {
  0x23, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x20, 0x33, 0x33, 0x30,
  0x20, 0x63, 0x6f, 0x72, 0x65, 0x0a, 0x6f, 0x75, 0x74, 0x20, 0x76, 0x65,
  0x63, 0x34, 0x20, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72,
  0x3b, 0x0a, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x69,
  0x76, 0x65, 0x63, 0x32, 0x20, 0x72, 0x65, 0x73, 0x6f, 0x6c, 0x75, 0x74,
  0x69, 0x6f, 0x6e, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d,
  0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x74, 0x69, 0x6d, 0x65, 0x3b,
  0x0a, 0x0a, 0x69, 0x6e, 0x20, 0x76, 0x65, 0x63, 0x33, 0x20, 0x6e, 0x65,
  0x77, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x73, 0x3b, 0x0a, 0x0a, 0x76,
  0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x28, 0x29, 0x20, 0x7b,
  0x0a, 0x20, 0x20, 0x20, 0x20, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c,
  0x6f, 0x72, 0x20, 0x3d, 0x20, 0x76, 0x65, 0x63, 0x34, 0x28, 0x6e, 0x65,
  0x77, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x73, 0x2c, 0x20, 0x31, 0x2e,
  0x30, 0x29, 0x3b, 0x0a, 0x7d, 0x00
};
unsigned int shaders_fragment_glsl_len = 161;
#endif