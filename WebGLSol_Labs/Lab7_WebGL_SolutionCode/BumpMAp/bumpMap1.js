"use strict";

var canvas;
var gl;

var theta  = 0.0;
var phi    = 0.0;
var dr = 5.0 * Math.PI/180.0;

var texSize = 256;

// NOrmal Data

var tex_norm = new Image(); // Image constructor

tex_norm.src = 'cushion_normal_mapping_normal_map.png';


var pointsArray = [];
var texCoordsArray = [];
var colorsArray = [];

var texCoord = [
    vec2(0, 0),
    vec2(1, 0),
    vec2(1, 1),
    vec2(0, 1)
];

var vertices = [
    vec4( 0.0, 0.0, 0.0, 1.0 ),
    vec4( 1.0,  0.0,  0.0, 1.0 ),
    vec4( 1.0,  0.0,  1.0, 1.0 ),
    vec4( 0.0, 0.0,  1.0, 1.0 )
];

var modelViewMatrix, projectionMatrix, normalMatrix;


var normal = vec4(0.0, 1.0, 0.0, 0.0);
var tangent = vec3(1.0, 0.0, 0.0);


var lightDiffuse = vec4( 1.0, 1.0, 1.0, 1.0 );

var materialDiffuse = vec4( 0.7, 0.7, 0.7, 1.0 );

var program;



function configureTexture( image ) {
    var texture = gl.createTexture();
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, texture);
    gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);

    gl.texImage2D( gl.TEXTURE_2D, 0, gl.RGB,
        gl.RGB, gl.UNSIGNED_BYTE, image );
    gl.generateMipmap(gl.TEXTURE_2D);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER,
                      gl.NEAREST_MIPMAP_LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
}


function mesh() {
     pointsArray.push(vertices[0]);
     texCoordsArray.push(texCoord[0]);
     //adding colour
     colorsArray.push(vec4( 1.0, 0.0, 1.0, 1.0 ));

     pointsArray.push(vertices[1]);
     texCoordsArray.push(texCoord[1]);
    //adding colour
    colorsArray.push(vec4( 1.0, 0.0, 1.0, 1.0 ));

     pointsArray.push(vertices[3]);
     texCoordsArray.push(texCoord[3]);
    //adding colour
    colorsArray.push(vec4( 0.0, 1.0, 1.0, 1.0 ));

     pointsArray.push(vertices[2]); ;
     texCoordsArray.push(texCoord[2]);
    //adding colour
    colorsArray.push(vec4( 0.0, 2.0, 1.0, 1.0 ));

}



window.onload = function init() {

    canvas = document.getElementById( "gl-canvas" );

    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }


    gl.viewport( 0, 0, canvas.width, canvas.height );
    
    gl.clearColor( 1.0, 1.0, 1.0, 1.0 );

    gl.enable(gl.DEPTH_TEST);

    //
    //  Load shaders and initialize attribute buffers
    //
    program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );

    mesh();

    var vBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, flatten(pointsArray), gl.STATIC_DRAW);

    var vPosition = gl.getAttribLocation(program, "vPosition");
    gl.vertexAttribPointer(vPosition, 4, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(vPosition);

    var tBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, tBuffer);
    gl.bufferData( gl.ARRAY_BUFFER, flatten(texCoordsArray), gl.STATIC_DRAW);

    var vTexCoord = gl.getAttribLocation( program, "vTexCoord");
    gl.vertexAttribPointer( vTexCoord, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(vTexCoord);

    /// adding colours
    var cBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, cBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(colorsArray), gl.STATIC_DRAW );

    var vColor = gl.getAttribLocation( program, "vColor" );
    gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vColor );


    // Normal Texture Array
    
    configureTexture(tex_norm);

    var diffuseProduct = mult(lightDiffuse, materialDiffuse);

    gl.uniform4fv( gl.getUniformLocation(program, "diffuseProduct"),flatten(diffuseProduct));
    gl.uniform4fv( gl.getUniformLocation(program, "normal"),flatten(normal));
    gl.uniform3fv( gl.getUniformLocation(program, "objTangent"),flatten(tangent));


    document.getElementById("Button2").onclick = function(){theta += dr;};
    document.getElementById("Button3").onclick = function(){theta -= dr;};
    document.getElementById("Button4").onclick = function(){phi += dr;};
    document.getElementById("Button5").onclick = function(){phi -= dr;};

    render();
}

var render = function(){

    gl.clear( gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    var lightPosition = vec4(0.0, 2.0, 0.0, 1.0 );

    lightPosition[1] = 2.0*Math.cos(theta);
    gl.uniform4fv( gl.getUniformLocation(program, "lightPosition"),flatten(lightPosition));


    var eye = vec3(2.0, 3.0*(1.0+Math.cos(phi)) , 2.0);
    var at = vec3(0.0, 0.0, 0.0);
    var up = vec3(0.0, 1.0, 0.0);

    modelViewMatrix  = lookAt(eye, at, up);
    projectionMatrix = ortho(-1.2, 1.2, -1.2, 1.2,-10.0,10.0);

    var normalMatrix = [
       vec3(modelViewMatrix[0][0], modelViewMatrix[0][1], modelViewMatrix[0][2]),
       vec3(modelViewMatrix[1][0], modelViewMatrix[1][1], modelViewMatrix[1][2]),
       vec3(modelViewMatrix[2][0], modelViewMatrix[2][1], modelViewMatrix[2][2])
    ];


    gl.uniformMatrix4fv( gl.getUniformLocation(program, "modelViewMatrix"), false, flatten(modelViewMatrix));
    gl.uniformMatrix4fv( gl.getUniformLocation(program, "projectionMatrix"), false, flatten(projectionMatrix));
    gl.uniformMatrix3fv( gl.getUniformLocation(program, "normalMatrix"), false, flatten(normalMatrix));
    

    gl.drawArrays( gl.TRIANGLE_STRIP, 0, 4 );

    requestAnimFrame(render);
}
