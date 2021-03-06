#ifdef GL_ES
  precision highp float;
#endif

uniform sampler2D in_Texture;
uniform sampler2D in_Merge;

varying vec2 ex_Uv;

void main()
{
  gl_FragColor = texture2D(in_Texture, ex_Uv);
  vec4 merge = texture2D(in_Merge, vec2(ex_Uv.x, 1.0 - ex_Uv.y));
  //merge = merge / 1.5;
  gl_FragColor.x = gl_FragColor.x + merge.x;
  gl_FragColor.y = gl_FragColor.y + merge.y;
  gl_FragColor.z = gl_FragColor.z + merge.z;
}
