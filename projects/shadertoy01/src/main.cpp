#include <core/pathSolver/pathSolver.h>

#include <GL/glew.h>

#include <SFML/OpenGL.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>

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

    // Création de la fenêtre SFML
    sf::Window window(sf::VideoMode(1024, 768), "ShaderToy Clone", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

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
    double mouseX = 0, mouseY = 0;
    bool mouseClicked = false;
    double mouseClickX = 0, mouseClickY = 0;

    // SFML clock to measure time
    sf::Clock clock;

    // Boucle de rendu
    bool running = true;
    while (running) {
        // Gestion des événements SFML
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            }

            // Vérifier si la touche ESC est appuyée
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                running = false;
            }

            // Récupérer la position de la souris
            if (event.type == sf::Event::MouseMoved) {
                mouseX = event.mouseMove.x;
                mouseY = event.mouseMove.y;
            }

            // Vérifier si la souris est cliquée
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                mouseClickX = mouseX;
                mouseClickY = mouseY;
                mouseClicked = true;
            }
        }

        // Temps et résolution
        GLfloat timeValue = clock.getElapsedTime().asSeconds();
        int width = window.getSize().x;
        int height = window.getSize().y;
        glViewport(0, 0, width, height);

        // Incrémenter iFrame
        frameCount++;

        // Rendu du shader
        glUseProgram(shaderProgram);
        glUniform1f(glGetUniformLocation(shaderProgram, "iTime"), timeValue);
        glUniform2f(glGetUniformLocation(shaderProgram, "iResolution"), (float)width, (float)height);
        glUniform1i(glGetUniformLocation(shaderProgram, "iFrame"), frameCount);
        glUniform4f(glGetUniformLocation(shaderProgram, "iMouse"), (float)mouseX, (float)mouseY, (float)mouseClickX, (float)mouseClickY);

        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Gestion des buffers
        window.display();
    }

    // Nettoyage
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // Terminer SFML
    window.close();
    return 0;
}
