uniform sampler2D texture;
uniform float pixel_threshold;

void main()
{
    float factor = 1.0 / (pixel_threshold);
    vec2 pos = floor(gl_TexCoord[0].xy * factor + 0.5) / factor;
    gl_FragColor = texture2D(texture, pos) * gl_Color;
}
