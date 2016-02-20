#ifndef __DEFINER_Shader_H
#define __DEFINER_Shader_H

//version Of Shader
#define VERSION_OF_SHADER "#version 330 core\n"


//position Of Vertex
#define POSITION_OF_VERTEX "layout(location = 0) in vec3 position;\n"

//matrix that calculate the location
#define MATRIXES_OF_LOCATION "uniform mat4 model;\nuniform mat4 view;\n"

//inside the main -> calculate location of vertex
#define CALCULATE_LOCATION_OF_VERTEX "gl_Position = view * model * vec4(position, 1.0f);\n"





//main close/open
#define OPEN_MAIN_FUNCTION "void main()\n{\n"
#define CLOSE_FUNCTION "}\n"

//get to fragment shader 
#define FINAL_COLOR "out vec4 color;\n";

//uniform for specific color
#define UNIFORM_COLOR_FOR_WHOLE_OBJECT "uniform vec3 colorForObject;\n"


#endif
