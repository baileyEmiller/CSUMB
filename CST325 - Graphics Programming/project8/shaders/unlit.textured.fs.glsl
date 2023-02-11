precision mediump float;

uniform sampler2D uTexture;
uniform float uAlpha;

// todo #3 - receive texture coordinates and verify correctness by 
// using them to set the pixel color 
varying vec2 vTcoords;

void main(void) {
    // todo #5
    gl_FragColor = texture2D(uTexture, vTcoords);
    gl_FragColor.a = uAlpha;
    // todo #3
    //gl_FragColor = vec4(vTcoords.x, vTcoords.y, 0.0, 1.0);
}

// EOF 00100001-10
