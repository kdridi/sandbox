#include <core/pathSolver/pathSolver.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Fonction pour lire le code shader depuis un fichier
std::string LoadShaderSource(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Erreur de chargement du fichier shader: " << filePath << std::endl;
        return "";
    }
    std::stringstream shaderStream;
    shaderStream << file.rdbuf();
    return shaderStream.str();
}

// Fonction pour compiler un shader
GLuint CompileShader(const std::string &source, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);
    const char *src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // Vérifier la compilation
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Erreur de compilation du shader: " << infoLog << std::endl;
    }
    return shader;
}

// Fonction pour créer le programme shader
GLuint CreateShaderProgram(const std::string &vertexShaderSource, const std::string &fragmentShaderSource, const std::string &mainSource)
{
    (void)(mainSource);

    GLuint vertexShader = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = CompileShader(fragmentShaderSource + "\n" + mainSource, GL_FRAGMENT_SHADER);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Vérifier le linkage
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Erreur de linkage du programme: " << infoLog << std::endl;
    }

    // Nettoyage des shaders intermédiaires
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int main(int argc, const char *argv[], const char *env[])
{
    MODULES_START(argc, argv, env);

    // Initialisation de GLFW
    if (!glfwInit()) {
        std::cerr << "Erreur d'initialisation de GLFW" << std::endl;
        return -1;
    }

    // Créer une fenêtre avec GLFW
    GLFWwindow *window = glfwCreateWindow(1024, 768, "ShaderToy Clone", nullptr, nullptr);
    if (!window) {
        std::cerr << "Erreur de création de la fenêtre GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialisation de GLEW (pour les extensions OpenGL)
    if (glewInit() != GLEW_OK) {
        std::cerr << "Erreur d'initialisation de GLEW" << std::endl;
        return -1;
    }

    // Charger les sources de shaders depuis des fichiers
    const std::filesystem::path shaderPath = PATH_SOLVER_SOLVE("assets/vertex_shader.glsl");
    std::string vertexShaderSource = LoadShaderSource(shaderPath.string());

    const std::filesystem::path fragmentPath = PATH_SOLVER_SOLVE("assets/fragment_shader.glsl");
    std::string fragmentShaderSource = LoadShaderSource(fragmentPath.string());

    const std::filesystem::path mainPath = PATH_SOLVER_SOLVE("assets/main.glsl");
    std::string mainSource = LoadShaderSource(mainPath.string());

    // Créer le programme shader
    GLuint shaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource, mainSource);

    // Créer un simple rectangle couvrant tout l'écran
    float vertices[] = {
        0.0f - 1.0f, 0.0f - 1.0f, 0.0f,
        0.0f + 1.0f, 0.0f - 1.0f, 0.0f,
        0.0f + 1.0f, 0.0f + 1.0f, 0.0f,
        0.0f - 1.0f, 0.0f + 1.0f, 0.0f};

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Variables pour iFrame et iMouse
    int frameCount = 0;
    double mouseX, mouseY;
    bool mouseClicked = false;
    double mouseClickX = 0, mouseClickY = 0;

    // Boucle de rendu
    while (!glfwWindowShouldClose(window)) {
        // Temps et résolution
        GLfloat timeValue = (GLfloat)glfwGetTime();
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        // Incrémenter iFrame
        frameCount++;

        // Récupérer la position de la souris
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Vérifier si la souris est cliquée
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            if (!mouseClicked) {
                // Enregistrer la position du clic
                mouseClickX = mouseX;
                mouseClickY = mouseY;
                mouseClicked = true;
            }
        } else {
            mouseClicked = false;
        }

        // Rendu du shader
        glUseProgram(shaderProgram);
        glUniform1f(glGetUniformLocation(shaderProgram, "iTime"), timeValue);
        glUniform2f(glGetUniformLocation(shaderProgram, "iResolution"), (float)width, (float)height);
        glUniform1i(glGetUniformLocation(shaderProgram, "iFrame"), frameCount);
        glUniform4f(glGetUniformLocation(shaderProgram, "iMouse"), (float)mouseX, (float)mouseY, (float)mouseClickX, (float)mouseClickY);

        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Vérifier si la touche ESC est appuyée
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        // Gestion des événements et buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Nettoyage
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // Terminer GLFW
    glfwTerminate();
    return 0;
}
