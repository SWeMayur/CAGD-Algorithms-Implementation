attribute highp vec4 posAttr;
attribute lowp vec4 colAttr;
varying lowp vec4 col;
uniform highp mat4 matrix;
uniform lowp float angle;
void main() {

   highp mat4 rotationMatrix = mat4(
      cos(radians(angle)), -sin(radians(angle)), 0.0, 0.0,
      sin(radians(angle)), cos(radians(angle)), 0.0, 0.0,
      0.0, 0.0, 1.0, 0.0,
      0.0, 0.0, 0.0, 1.0
   );

   highp mat4 rotatedMatrix = matrix * rotationMatrix;

   gl_Position = rotatedMatrix * posAttr;

   col = colAttr; 
   
};