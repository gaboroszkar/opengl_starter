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

    GLFWwindow *window =
        glfwCreateWindow(1280, 720, "Application", nullptr, nullptr);
    // Introduce the window into the current context.
    glfwMakeContextCurrent(window);

    // Load glad so it configures OpenGL.
    gladLoadGL(glfwGetProcAddress);
    // Specify the viewport of OpenGL in the Window.
    glViewport(0, 0, 1280, 720);

    // Create vertex shader.
    GLuint vertex_shader_index = glCreateShader(GL_VERTEX_SHADER);
    const char *vertex_shader_source =
        "#version 460 core\n"
        "layout (location = 0) in vec3 position;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
        "}\0";
    // Attach vertex shader source to the vertex shader object.
    glShaderSource(vertex_shader_index, 1, &vertex_shader_source, nullptr);
    // Compile the vertex shader.
    glCompileShader(vertex_shader_index);

    // Create fragment shader.
    GLuint fragment_shader_index = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragment_shader_source =
        "#version 460 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "    color = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
        "}\n\0";
    // Attach fragment shader source to the fragment shader object.
    glShaderSource(fragment_shader_index, 1, &fragment_shader_source, nullptr);
    // Compile the fragment shader.
    glCompileShader(fragment_shader_index);

    // Create shader program.
    GLuint shader_program_index = glCreateProgram();
    // Attach the vertex shader and fragment shader to the shader program.
    glAttachShader(shader_program_index, vertex_shader_index);
    glAttachShader(shader_program_index, fragment_shader_index);
    // Link all the shaders together into the shader program.
    glLinkProgram(shader_program_index);

    // Delete the now useless vertex shader and fragment shader objects.
    glDeleteShader(vertex_shader_index);
    glDeleteShader(fragment_shader_index);

    // Create vertex array.
    GLuint vertex_array_index;
    glGenVertexArrays(1, &vertex_array_index);
    glBindVertexArray(vertex_array_index);

    // Create vertex buffer.
    GLuint vertex_buffer_index;
    glGenBuffers(1, &vertex_buffer_index);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_index);

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
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
        glUseProgram(shader_program_index);
        // Bind the vertex array so OpenGL knows to use it.
        glBindVertexArray(vertex_array_index);
        // Draw the triangle using the GL_TRIANGLES primitive.
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // Swap the back buffer with the front buffer.
        glfwSwapBuffers(window);
        // Take care of all GLFW events.
        glfwPollEvents();
    }

    // Delete all the objects we've created.
    glDeleteVertexArrays(1, &vertex_array_index);
    glDeleteBuffers(1, &vertex_buffer_index);
    glDeleteProgram(shader_program_index);
    // Delete window before ending the program.
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program.
    glfwTerminate();

    return 0;
}
