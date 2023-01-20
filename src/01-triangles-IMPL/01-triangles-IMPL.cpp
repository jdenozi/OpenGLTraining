//////////////////////////////////////////////////////////////////////////////
//
//  Triangles.cpp
//
//////////////////////////////////////////////////////////////////////////////

#include "vgl.h"
#include "LoadShaders.h"


//----------------------------------------------------------------------------
//
// init
//

GLuint VAOs[1];
GLuint VBOs[1];

void init( void )
{
    glGenVertexArrays( 1, VAOs ); //Vertex array object 1 VAO qui est GLUInt[1], Generate a name for a new array.

    glBindVertexArray( VAOs[0] ); // Make the new array active, creating it if necessary.


    glCreateBuffers( 1, VBOs ); // Generate a name for a new buffer.
    glBindBuffer( GL_ARRAY_BUFFER, VBOs[0] ); // // Make the new buffer active, creating it if necessary.


    GLfloat vertices[3][2] = {
            {1, 0.5f},
            {0.5f, 1},
            {0.5f, -1}
    };

    glBufferStorage( GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0); // creates and initializes a buffer object's immutable data store

    ShaderInfo  shaders[] =
            {
                    { GL_VERTEX_SHADER, "media/shaders/triangles/triangles.vert" },
                    { GL_FRAGMENT_SHADER, "media/shaders/triangles/triangles.frag" },
                    { GL_NONE, NULL }
            };

    GLuint program = LoadShaders( shaders );
    glUseProgram( program );

    glVertexAttribPointer( 0, 2,  GL_FLOAT,
                           GL_FALSE, 0, BUFFER_OFFSET(0) );
    // Enable the vertex attribute
    glEnableVertexAttribArray( 0 );

}

//----------------------------------------------------------------------------
//
// display
//

void
display( void )
{
    static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };

    glClearBufferfv(GL_COLOR, 0, black);
    glBindVertexArray(VAOs[0]);
    glDrawArrays( GL_TRIANGLES, 0, 1 );
}

//----------------------------------------------------------------------------
//
// main
//

#ifdef _WIN32
int CALLBACK WinMain(
  _In_ HINSTANCE hInstance,
  _In_ HINSTANCE hPrevInstance,
  _In_ LPSTR     lpCmdLine,
  _In_ int       nCmdShow
)
#else
int
main( int argc, char** argv )
#endif
{
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangles example", NULL, NULL);

    glfwMakeContextCurrent(window);
    gl3wInit();

    init();

    while (!glfwWindowShouldClose(window))
    {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}
