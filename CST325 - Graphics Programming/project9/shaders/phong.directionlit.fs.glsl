precision mediump float;

uniform vec3 uLightDirection;
uniform vec3 uCameraPosition;
uniform sampler2D uTexture;

varying vec2 vTexcoords;
varying vec3 vWorldNormal;
varying vec3 vWorldPosition;

void main(void) {
    // diffuse contribution

    // todo #1 normalize the light direction and store in a separate variable
    vec3 normalLight = normalize(uLightDirection);
    //gl_FragColor = vec4(normalLight, 1.0);

    // todo #2 normalize the world normal and store in a separate variable
    vec3 normalWorldNormal = normalize(vWorldNormal);
    //gl_FragColor = vec4(normalWorldNormal, 1.0);

    // todo #3 calculate the lambert term
    float lambertTerm = dot(normalLight, normalWorldNormal);
    // gl_FragColor = vec4(lambertTerm,lambertTerm, lambertTerm, 1.0);

    // specular contribution
    // todo #4 in world space, calculate the direction from the surface point to the eye (normalized)
    vec3 eyeVector = normalize(uCameraPosition - vWorldPosition);
    gl_FragColor = vec4(eyeVector, 1.0);
    
    // todo #5 in world space, calculate the reflection vector (normalized)
    vec3 reflectionVector = (dot(normalLight, normalWorldNormal)) * normalWorldNormal + (dot(normalLight, normalWorldNormal)) * normalWorldNormal - normalLight;
    //gl_FragColor = vec4(reflectionVector, 1.0);

    // todo #6 calculate the phong term
    float power = 64.0;
    float angle = dot(reflectionVector, eyeVector);
    float phongTerm = pow(max(angle, 0.0), power);
    //float phongTerm = pow(dot(reflectionVector, eyeVector), 64.0);
    //gl_FragColor = vec4(phongTerm, phongTerm, phongTerm,  1.0);


    vec3 albedo = texture2D(uTexture, vTexcoords).rgb;
    // combine
    // todo #7 apply light and material interaction for diffuse value by using the texture color as the material
    
    vec3 diffuse = lambertTerm * albedo;
    //gl_FragColor = vec4(diffuse, 1.0);
    // todo #8 apply light and material interaction for phong, assume phong material color is (0.3, 0.3, 0.3)
    
    vec3 specular = phongTerm  * albedo * 0.3;
    //gl_FragColor = vec4(specular, 1.0);
    

    vec3 ambient = albedo * 0.1;
   

    // todo #9
    // add "diffuseColor" and "specularColor" when ready
    vec3 finalColor = ambient + diffuse + specular;

     gl_FragColor = vec4(finalColor, 1.0);
    
}

// EOF 00100001-10