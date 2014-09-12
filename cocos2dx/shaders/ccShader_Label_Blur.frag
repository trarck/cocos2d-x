const char* ccLabelBlur_frag = STRINGIFY(
\n#ifdef GL_ES\n
precision mediump float;
\n#endif\n

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec4 u_textColor;
uniform vec2 resolution;
uniform float blurRadius;
uniform float sampleNum;

uniform sampler2D CC_Texture0;

float blur(vec2);

void main(void)
{
	float col = blur(v_texCoord);
	gl_FragColor = vec4(u_textColor.rgb, u_textColor.a) * v_fragmentColor;
}

float blur(vec2 p)
{
	float sum = 0.0;

	vec2 unit = 1.0 / resolution.xy;

	sum += texture2D(CC_Texture0, p - 4.0 * unit).a * 0.05;
	sum += texture2D(CC_Texture0, p - 3.0 * unit).a * 0.09;
	sum += texture2D(CC_Texture0, p - 2.0 * unit).a * 0.12;
	sum += texture2D(CC_Texture0, p - 1.0 * unit).a * 0.15;
	sum += texture2D(CC_Texture0, p                 ).a * 0.16;
	sum += texture2D(CC_Texture0, p + 1.0 * unit).a * 0.15;
	sum += texture2D(CC_Texture0, p + 2.0 * unit).a * 0.12;
	sum += texture2D(CC_Texture0, p + 3.0 * unit).a * 0.09;
	sum += texture2D(CC_Texture0, p + 4.0 * unit).a * 0.05;

	return sum;
}
//
// float blur(vec2 p)
// {
//     if (blurRadius > 0.0 && sampleNum > 1.0)
//     {
//         float col = 1.0;
//         vec2 unit = 1.0 / resolution.xy;
//
//         float r = blurRadius;
//         float sampleStep = r / sampleNum;
//
//         float count = 0.0;
//
//         for(float x = -r; x < r; x += sampleStep)
//         {
//             for(float y = -r; y < r; y += sampleStep)
//             {
//                 float weight = (r - abs(x)) * (r - abs(y));
//                 col +=  texture2D(CC_Texture0, p + vec2(x * unit.x, y * unit.y)).a * weight;
//                 count += weight;
//             }
//         }
//
//         return col / count;
//     }
//
//     return texture2D(CC_Texture0, p).a;
// }
);

