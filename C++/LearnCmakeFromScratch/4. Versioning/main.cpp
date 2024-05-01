#include <iostream>
#include "add_lib\add.h"
#include "GLFW\glfw3.h"
#include "ExeUseLibConfig.h"

int main(int argc, char* argv[])
{
    std::cout << somemath::add(1, 2) << std::endl;
    std::cout << somemath::add(1.2f, 2.3f) << std::endl;

    std::cout << "arcg: " << argc << "; argv: " << *argv << "; version: " << ExeUseLib_VERSION_MAJOR << "." << ExeUseLib_VERSION_MINOR << "\n";

    GLFWwindow *window;
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }
    glfwWindowHint(GLFW_DEPTH_BITS, 16);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    window = glfwCreateWindow( 300, 300, "Gears", NULL, NULL );
    
    if (!window)
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }
    
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Draw gears
        // draw();

        // Update animation
        // animate();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
}