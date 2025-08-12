#pragma once

#include <Prerequisites.h>
#include <ResourceManager.h>
#include <Window.h>
#include "EngineGUI.h"
#include <CShape.h>
#include <ECS/Transform.h>
#include <ECS/Actor.h>
#include <A_Racer.h>

#include <vector>
#include <SFML/System.hpp>

/**
 * @class BaseApp
 * @brief Clase principal de la aplicación que administra la ventana, la pista,
 * los corredores y el estado de la carrera.
 */
class BaseApp {
public:
    /**
     * @brief Constructor por defecto.
     */
    BaseApp() = default;

    /**
     * @brief Destructor que libera recursos.
     */
    ~BaseApp();

    /**
     * @brief Ejecuta el ciclo principal de la aplicación.
     * @return Código de salida de la aplicación.
     */
    int run();

    /**
     * @brief Inicializa la ventana, recursos y elementos del juego.
     * @return true si la inicialización fue exitosa, false en caso contrario.
     */
    bool init();

    /**
     * @brief Actualiza la lógica del juego (por ahora vacío).
     */
    void update() {}

    /**
     * @brief Renderiza los elementos en pantalla (por ahora vacío).
     */
    void render() {}

    /**
     * @brief Libera recursos y realiza limpieza (por ahora vacío).
     */
    void destroy() {}

private:
    EngineUtilities::TSharedPointer<Window> m_windowPtr;
    EngineUtilities::TSharedPointer<Actor> m_trackActor;
    std::vector<EngineUtilities::TSharedPointer<A_Racer>> m_racers;
    std::vector<EngineUtilities::TSharedPointer<A_Racer>> m_finishedOrder;
    ResourceManager resourceMan;
    EngineGUI gui;
    std::vector<sf::Vector2f> m_path;
    sf::FloatRect m_finishLine;
    float m_raceTimer = 0.f;
    bool m_raceStarted = false;
};