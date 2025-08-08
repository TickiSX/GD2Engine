﻿#include "BaseApp.h"
//#include <ECS/Actor.h>
#include "ResourceManager.h"

/**
 * @file BaseApp.cpp
 * @brief Implements the BaseApp class which manages the main application loop.
 */

 /**
  * @brief Destructor for BaseApp.
  *
  * Currently empty, as resources are freed in the destroy() method.
  */
BaseApp::~BaseApp() {
}

/**
 * @brief Starts the main loop of the application.
 *
 * Initializes the application, enters the main loop where events are handled, and updates and renders
 * the application. Finally, it calls destroy() to release resources.
 *
 * @return int Returns 0 on successful execution.
 */
int
BaseApp::run() {
    if (!init()) {
        ERROR("BaseApp", "run", "Initializes result on a false statement",
            "check method validations");
    }

    while (m_windowPtr->isOpen()) {
        m_windowPtr->handleEvents();
        update();
        render();
    }

    destroy();
    return 0;
}

/**
 * @brief Initializes the application resources.
 *
 * Creates the window and sets up a simple yellow circle shape.
 *
 * @return true if initialization succeeds.
 */
bool
BaseApp::init() {
    ResourceManager& resourceMan = ResourceManager::getInstance();

    m_windowPtr = EngineUtilities::MakeShared<Window>(1920, 1080, "Onigiri Engine");
    if (!m_windowPtr) {
        ERROR("BaseApp", "init", "Failed to create window pointer, check memory allocation");
        return false;
    }




    // Crear pista de carreras
    m_Track = EngineUtilities::MakeShared<Actor>("Track Actor");
    if (m_Track) {
        // Asignar textura
        m_Track->getComponent<CShape>()->createShape(RECTANGLE);
        m_Track->getComponent<CShape>()->setFillColor(sf::Color::White);
        m_Track->getComponent<Transform>()->setPosition(sf::Vector2f(0.f, 0.f));
        m_Track->getComponent<Transform>()->setScale(sf::Vector2f(17.0f, 22.0f));

        if (!resourceMan.loadTexture("Sprites/Track", "png")) {
            MESSAGE("BaseApp", "Init", "Can't load the texture");
        }

        m_Track->setTexture(resourceMan.getTexture("Sprites/Track"));

    }




    //Create Circle Actor
    m_ACircle = EngineUtilities::MakeShared<Actor>("yoshi");
    if (m_ACircle) {
        m_ACircle->getComponent<CShape>()->createShape(CIRCLE);
        m_ACircle->getComponent<CShape>()->setFillColor(sf::Color::White);
        m_ACircle->getComponent<Transform>()->setPosition(sf::Vector2f(65.f, 475.f));
        m_ACircle->getComponent<Transform>()->setScale(sf::Vector2f(4.f, 4));

        //Cargar la textura para el actor
        if (!resourceMan.loadTexture("Sprites/yoshi", "png")) {
            MESSAGE("BaseApp", "Init", "Can't load the texture");
        }

        m_ACircle->setTexture(resourceMan.getTexture("Sprites/yoshi"));

        // Inicializar los waypoints para RedShell
        m_waypoints.push_back(sf::Vector2f(65.f, 200.f));
        m_waypoints.push_back(sf::Vector2f(95.f, 120.f));
        m_waypoints.push_back(sf::Vector2f(150.f, 100.f));
        m_waypoints.push_back(sf::Vector2f(850.f, 100.f));
        m_waypoints.push_back(sf::Vector2f(950.f, 110.f));
        m_waypoints.push_back(sf::Vector2f(975.f, 175.f));
        m_waypoints.push_back(sf::Vector2f(975.f, 400.f));
        m_waypoints.push_back(sf::Vector2f(925.f, 475.f));
        m_waypoints.push_back(sf::Vector2f(445.f, 475.f));
        m_waypoints.push_back(sf::Vector2f(425.f, 675.f));
        m_waypoints.push_back(sf::Vector2f(475.f, 700.f));
        m_waypoints.push_back(sf::Vector2f(1175.f, 700.f));
        m_waypoints.push_back(sf::Vector2f(1250.f, 725.f));
        m_waypoints.push_back(sf::Vector2f(1250.f, 925.f));
        m_waypoints.push_back(sf::Vector2f(1175.f, 975.f));
        m_waypoints.push_back(sf::Vector2f(650.f, 975.f));

        m_waypoints.push_back(sf::Vector2f(250.f, 975.f));
        m_waypoints.push_back(sf::Vector2f(150.f, 975.f));
        m_waypoints.push_back(sf::Vector2f(100.f, 960.f));
        m_waypoints.push_back(sf::Vector2f(65.f, 940.f));



        // Crear marcadores visuales para cada waypoint
        for (const auto& wp : m_waypoints) {
            auto marker = EngineUtilities::MakeShared<CShape>();
            marker->createShape(ShapeType::CIRCLE);
            marker->setFillColor(sf::Color::Yellow);
            marker->setPosition(wp);
            marker->setScale(sf::Vector2f(1.f, 1.f));

            m_waypointMarkers.push_back(marker);
        }
    }
    else {
        ERROR("BaseApp", "init", "Failed to create Circle Actor, chek memory allocation");
        return false;
    }

    return true;
}

/**
 * @brief Updates the application state.
 *
 * Empty for now. Intended for game logic or state updates.
 */
void
BaseApp::update() {
    // Validar que la ventana est� activa
    if (!m_windowPtr.isNull()) {
        m_windowPtr->update();
    }

    ImGui::ShowDemoWindow();

    //Actualizar el actor Track
    if (!m_Track.isNull()) {
        m_Track->update(m_windowPtr->deltaTime.asSeconds());
    }

    // Actualizar el actor si no es nulo
    if (!m_ACircle.isNull()) {
        m_ACircle->update(m_windowPtr->deltaTime.asSeconds());

        // Solo ejecutar si hay waypoints definidos
        if (!m_waypoints.empty()) {
            // Obtener el destino actual
            sf::Vector2f targetPos = m_waypoints[m_currentWaypointIndex];

            // Obtener posici�n actual del actor
            sf::Vector2f currentPos = m_ACircle->getComponent<Transform>()->getPosition();

            // Calcular distancia al waypoint
            float dx = targetPos.x - currentPos.x;
            float dy = targetPos.y - currentPos.y;
            float distance = std::sqrt(dx * dx + dy * dy);

            // Si lleg� al waypoint actual, pasar al siguiente
            if (distance < 10.0f) {
                m_currentWaypointIndex++;
                if (m_currentWaypointIndex >= static_cast<int>(m_waypoints.size())) {
                    m_currentWaypointIndex = 0; // Comportamiento c�clico


                }
            }

            // Moverse hacia el waypoint actual
            m_ACircle->getComponent<Transform>()->seek(
                m_waypoints[m_currentWaypointIndex],
                200.0f,
                m_windowPtr->deltaTime.asSeconds(),
                10.0f
            );
        }

        //

    }
}

/**
 * @brief Renders the current frame.
 *
 * Clears the screen, draws the circle shape, and displays the result.
 */
void
BaseApp::render() {
    if (!m_windowPtr) {
        return;
    }

    m_windowPtr->clear();

    // Renderizar primero la pista
    if (!m_Track.isNull()) {
        m_Track->getComponent<CShape>()->render(m_windowPtr);
    }

    // Dibujar marcadores de waypoints
    for (const auto& marker : m_waypointMarkers) {
        marker->render(m_windowPtr);
    }

    if (m_shapePtr) {
        m_shapePtr->render(m_windowPtr);
    }

    if (!m_ACircle.isNull()) {
        m_ACircle->getComponent<CShape>()->render(m_windowPtr);
    }
    m_windowPtr->render();
    m_windowPtr->display();
}


/**
 * @brief Releases allocated resources.
 *
 * Deletes the shape and properly destroys the window.
 */
void
BaseApp::destroy() {
    // m_shapePtr.Reset(); // Not necessary if using smart pointers correctly
    // m_windowPtr.Reset(); // Cleanup handled automatically
}