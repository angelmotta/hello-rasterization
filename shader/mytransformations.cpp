#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_s.h"
#include <iostream>
#include <vector>
#include <random>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void getRandomPositions(int N_TRIANGULOS, std::vector<std::vector<float>> &pos_triangulos);
float getRandomZeroToOne();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)  {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader zprogram
    Shader ourShader("../shader/5.1.transform.vs", "../shader/5.1.transform.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
            // positions
            0.5f,  0.5f, 0.5f, // top right
            0.5f, -0.5f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f // top left
    };
    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3,  // second triangle
            0, 2, 1,
            2, 0, 3
    };
    float vertices2[] = {
            0.0f,    0.0f, 0.0f,
            0.0f,    0.5f, 0.0f,
            0.5f,    0.0f, 0.0f,
            0.25f,  0.25f, 0.5f
    };
    unsigned int indices2[] = {
            0, 1, 2,
            0, 1, 3,
            1, 2, 3,
            2, 0, 3
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    ourShader.use();
    unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
    unsigned int colorLoc = glGetUniformLocation(ourShader.ID, "color");

    int N_TRIANGULOS = 10;
    std::vector<std::vector<float>> pos_triangulos;
//    std::vector<float> posTriang = {0.0f, 1.0f, 0.0f};
//    pos_triangulos.push_back(posTriang);
    getRandomPositions(N_TRIANGULOS, pos_triangulos);
    // Generate random scale and color for N pyramids
    std::vector<float> scaleVals;
    std::vector<std::vector<float>> randColors;
    for (int i = 0; i < N_TRIANGULOS; i++) {
        float myScaleVal = getRandomZeroToOne();
        scaleVals.push_back(myScaleVal);
        float r_rand = getRandomZeroToOne();
        float g_rand = getRandomZeroToOne();
        float b_rand = getRandomZeroToOne();
        std::vector<float> randColor = {r_rand, g_rand, b_rand};
        randColors.push_back(randColor);
    }
    // render loop
    while (!glfwWindowShouldClose(window)){
        // input
        processInput(window);
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Create transformations in loop
        for (int i = 0; i < N_TRIANGULOS; ++i) {
            // create transformations
            glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            transform = glm::scale(transform, glm::vec3(scaleVals[i]));
//            transform = glm::translate(transform, glm::vec3(0.1f, -0.1f, 0.0f));
            transform = glm::translate(transform, glm::vec3(pos_triangulos[i][0], pos_triangulos[i][1], pos_triangulos[i][2]));
            //transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
            //transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(pos_triangulos[i][0], pos_triangulos[i][1], pos_triangulos[i][2]));
            // get matrix's uniform location and set matrix
            ourShader.use();
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
            glUniform3f(colorLoc, randColors[i][0], randColors[i][1], randColors[i][1]);
            // render container
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        }

        // create transformations
        /*
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //transform = glm::translate(transform, glm::vec3(0.1f, -0.1f, 0.0f));
        //transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(pos_triangulos[0][0], pos_triangulos[0][1], pos_triangulos[0][2]));
        // get matrix's uniform location and set matrix
        ourShader.use();
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        // render container
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        */

        // create transformations
//        glm::mat4 transform2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//        transform2 = glm::translate(transform2, glm::vec3(0.5f, -0.5f, 0.0f));
//        transform2 = glm::rotate(transform2, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
//        // get matrix's uniform location and set matrix
//        ourShader.use();
//        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform2));
//        // render container
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void getRandomPositions(int N_TRIANGULOS, std::vector<std::vector<float>> &pos_triangulos) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-1.0, 1.0);

    for (int i = 0; i < N_TRIANGULOS; ++i) {
        std::cout << "Triangulo #" << i << "\n";
        // Get randoms float numbers between -1 and 1.
        float random_x = dist(gen);
        float random_y = dist(gen);
        float z = 0.0f;
        std::cout << "x: " << random_x << ", y: " << random_y << ", z:" << z << "\n";
        std::vector<float> posTriang = {random_x, random_y, z};
        pos_triangulos.push_back(posTriang);
    }
}

float getRandomZeroToOne() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0, 1.0);
    float myrandom = dist(gen);
    return myrandom;
}