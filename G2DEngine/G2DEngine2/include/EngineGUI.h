#pragma once

#include "Prerequisites.h"
#include <SFML/System.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <vector>

class Window;
class A_Racer;

/**
 * @class EngineGUI
 * @brief Sistema de interfaz gr�fica basado en ImGui para gestionar
 * men�s, controles y visualizaci�n de informaci�n en la aplicaci�n.
 */
class EngineGUI {
public:
    /**
     * @enum Theme
     * @brief Temas disponibles para el estilo visual de la GUI.
     */
    enum class Theme { Grey = 0, Dark = 1, G2DEngine2 = 2 };

    /**
     * @brief Constructor por defecto.
     */
    EngineGUI() = default;

    /**
     * @brief Destructor por defecto.
     */
    ~EngineGUI() = default;

    /**
     * @brief Inicializa el sistema de GUI.
     * @param window Puntero inteligente a la ventana principal.
     */
    void init(const EngineUtilities::TSharedPointer<Window>& window);

    /**
     * @brief Actualiza la GUI.
     * @param window Puntero inteligente a la ventana principal.
     * @param deltaTime Tiempo transcurrido desde el �ltimo frame.
     * @param raceTimer Tiempo total transcurrido de la carrera.
     */
    void update(const EngineUtilities::TSharedPointer<Window>& window,
        sf::Time deltaTime,
        float raceTimer);

    /**
     * @brief Renderiza la GUI en la ventana.
     * @param window Puntero inteligente a la ventana principal.
     */
    void render(const EngineUtilities::TSharedPointer<Window>& window);

    /**
     * @brief Libera recursos asociados a la GUI.
     */
    void destroy();

    /**
     * @brief Procesa eventos de la ventana para la GUI.
     * @param window Puntero inteligente a la ventana principal.
     * @param event Evento de SFML a procesar.
     */
    void processEvent(const EngineUtilities::TSharedPointer<Window>& window,
        const sf::Event& event);

    /**
     * @brief Indica si se solicit� cerrar la aplicaci�n.
     * @return true si se debe cerrar, false en caso contrario.
     */
    bool shouldQuit() const { return m_requestQuit; }

    /**
     * @brief Indica si el juego est� en pausa.
     * @return true si est� en pausa, false en caso contrario.
     */
    bool isPaused() const { return m_paused; }

    /**
     * @brief Indica si se solicit� reiniciar los waypoints.
     * @return true si se debe reiniciar, false en caso contrario.
     * @note Si devuelve true, la bandera interna se restablece autom�ticamente.
     */
    bool shouldResetWaypoints()
    {
        if (m_requestReset) { m_requestReset = false; return true; }
        return false;
    }

    /**
     * @brief Obtiene el multiplicador de velocidad actual.
     * @return Factor de multiplicaci�n de la velocidad.
     */
    float getSpeedMultiplier() const { return m_speedMultiplier; }

    /**
     * @brief Asigna la lista de corredores para mostrar en la GUI.
     * @param racers Vector de punteros inteligentes a corredores.
     */
    void setRacers(const std::vector<EngineUtilities::TSharedPointer<A_Racer>>& racers)
    {
        m_racers = racers;
    }

    /**
     * @brief Cambia el tema visual de la GUI.
     * @param theme Tema a aplicar.
     */
    void setTheme(Theme theme);

private:
    /**
     * @brief Renderiza la barra de men� superior.
     */
    void renderMenuBar();

    /**
     * @brief Renderiza el panel de control lateral o inferior.
     */
    void renderControlPanel();

    /**
     * @brief Configura el estilo visual "Grey".
     */
    void setupGreyGUIStyle();

    /**
     * @brief Configura el estilo visual "Dark".
     */
    void setupDarkGUIStyle();

    /**
     * @brief Configura el estilo visual "G2DEngine2".
     */
    void setupG2DEngine2Style();

    bool m_requestQuit = false;   ///< Solicitud de cierre de la aplicaci�n.
    bool m_requestReset = false;  ///< Solicitud de reinicio de waypoints.
    bool m_paused = false;        ///< Estado de pausa del juego.
    float m_speedMultiplier = 1.f;///< Factor de velocidad del juego.
    Theme m_currentTheme = Theme::G2DEngine2; ///< Tema visual actual.
    std::vector<EngineUtilities::TSharedPointer<A_Racer>> m_racers; ///< Lista de corredores mostrados en GUI.
};
