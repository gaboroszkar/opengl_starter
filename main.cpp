#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

int main()
{
    // Initialize GLFW.
    glfwInit();

    // Tell GLFW which version of OpenGL we are using.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // Tell GLFW we are using the CORE profile.
    // That means we only have the modern functions.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1280, 720, "Application", NULL, NULL);
    // Introduce the window into the current context.
    glfwMakeContextCurrent(window);

    // Load glad so it configures OpenGL.
    gladLoadGL(glfwGetProcAddress);
    // Specify the viewport of OpenGL in the Window.
    glViewport(0, 0, 1280, 720);

    // Create vertex shader.
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertex_shader_source =
        "#version 460 core\n"
        "layout (location = 0) in vec3 position;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
        "}\0";
    // Attach vertex shader source to the vertex shader object.
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    // Compile the vertex shader.
    glCompileShader(vertex_shader);

    // Create fragment shader.
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragment_shader_source =
        "#version 460 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "    color = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
        "}\n\0";
    // Attach fragment shader source to the fragment shader object.
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    // Compile the fragment shader.
    glCompileShader(fragment_shader);

    // Create shader program.
    GLuint shader_program = glCreateProgram();
    // Attach the vertex shader and fragment shader to the shader program.
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    // Link all the shaders together into the shader program.
    glLinkProgram(shader_program);

    // Delete the now useless vertex shader and fragment shader objects.
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // Create vertex array.
    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    // Create vertex buffer.
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

    // Introduce the vertices into the vertex buffer.
    GLfloat vertices[] =
        {
            // Lower left corner.
            -0.5f, -0.5f, 0.0f,
            // Lower right corner.
            0.5f, -0.5f, 0.0f,
            // Upper left corner.
            -0.5f, 0.5f, 0.0f
        };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configure the vertex attribute so that OpenGL knows how to read the
    // vertex buffer.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    // Enable the vertex attribute.
    glEnableVertexAttribArray(0);

    // Bind both the vertex buffer and vertex array to 0 so that we don't
    // accidentally modify the buffers we created.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Main loop.
    while (!glfwWindowShouldClose(window))
    {
        // Specify the color of the background.
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        // Clean the back buffer and assign the new color to it.
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which shader program we want to use.
        glUseProgram(shader_program);
        // Bind the vertex array so OpenGL knows to use it.
        glBindVertexArray(vertex_array);
        // Draw the triangle using the GL_TRIANGLES primitive.
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // Swap the back buffer with the front buffer.
        glfwSwapBuffers(window);
        // Take care of all GLFW events.
        glfwPollEvents();
    }

    // Delete all the objects we've created.
    glDeleteVertexArrays(1, &vertex_array);
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteProgram(shader_program);
    // Delete window before ending the program.
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program.
    glfwTerminate();

    return 0;
}
