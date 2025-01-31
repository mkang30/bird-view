#pragma once

// Defined before including GLEW to suppress deprecation messages on macOS
#include "camera.h"
#include "shapes/shape.h"
#include "shapes/cone.h"
#include "shapes/cube.h"
#include "shapes/cylinder.h"
#include "shapes/sphere.h"
#include "utils/sceneparser.h"
#include "utils/scenedata.h"
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <unordered_map>
#include <QElapsedTimer>
#include <QOpenGLWidget>
#include <QTime>
#include <QTimer>


enum class SettingType{
    CAMERA_ONLY,
    SHAPE_ONLY,
    CAMERA_AND_SHAPE
};

class Realtime : public QOpenGLWidget
{
public:
    Realtime(QWidget *parent = nullptr);
    void finish();                                      // Called on program exit
    void sceneChanged();
    void settingsChanged();
    void setupCamera();
    void setupShapesVBO();
    void updateShapesVBO();
    SettingType settingChangeType();
    int shapeSize(PrimitiveType type);
    Shape& shape(PrimitiveType);
    void parseLights();
    void parseGlobal();
    void parseShapes(ScenePrimitive &primitive);
    void moveCamera(float deltaTime);
    void rotateCamera(float deltaX, float deltaY);
    void paintScene();
    void makeFBO();
    void setFullscreenquad();
    void paintTexture(GLuint texture);
    void loadOBJ();
    void paintBird();
    void paintLand();
    void initializeScene();
    void makeFBO2();
    void paintTerrain();

public slots:
    void tick(QTimerEvent* event);                      // Called once per tick of m_timer

protected:
    void initializeGL() override;                       // Called once at the start of the program
    void paintGL() override;                            // Called whenever the OpenGL context changes or by an update() request
    void resizeGL(int width, int height) override;      // Called when window size changes

private:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

    // Tick Related Variables
    int m_timer;                                        // Stores timer which attempts to run ~60 times per second
    QElapsedTimer m_elapsedTimer;                       // Stores timer which keeps track of actual time between frames

    // Input Related Variables
    bool m_mouseDown = false;                           // Stores state of left mouse button
    glm::vec2 m_prev_mouse_pos;                         // Stores mouse position
    std::unordered_map<Qt::Key, bool> m_keyMap;         // Stores whether keys are pressed or not

    // Device Correction Variables
    int m_devicePixelRatio;

    //
    GLuint m_shader;
    GLuint m_fbo_shader;

    // Scenedata
    RenderData metaData;


    Camera camera;
    std::vector<SceneLightData> lights;

    // Shapes;
    Cone cone;
    Cylinder cylinder;
    Cube cube;
    Sphere sphere;

    //VBOS
    GLuint shape_vbos[4];
    GLuint shape_vaos[4];
    GLuint fullscreen_vbo;
    GLuint fullscreen_vao;

    //prev settings
    int shapeParameter1 = 1;
    int shapeParameter2 = 1;
    float nearPlane = 1;
    float farPlane = 1;
    //initialized
    bool initialized = false;
    bool sceneLoaded = false;

    //FBOs
    GLuint default_fbo;
    GLuint m_fbo;
    GLuint depth_texture;
    GLuint color_texture;
    //GLuint m_fbo_renderbuffer;
    int fbo_width;
    int fbo_height;
    int screen_width;
    int screen_height;

    GLuint depth_fbo;
    GLuint bird_depth_texture;

    // add ups
    float focalPoint = 5;

    GLuint bird_shader;
    GLuint birdVBO;
    GLuint birdVAO;
    int vert_size;
    GLuint terrain_shader;
    GLuint terrain_vbo;
    GLuint terrain_vao;

    int terrain_size;

    QImage bird_img;
    GLuint bird_text;

    glm::mat4 bird_ctm;
    glm::mat4 normal_ctm;


};
