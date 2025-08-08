﻿#pragma once
#include "..//Prerequisites.h"
#include "Entity.h"
#include "CShape.h"
#include "Transform.h"
#include "ECS/Texture.h"

/**
 * @class Actor
 * @brief Representa una entidad activa del mundo del juego que puede tener componentes, ser actualizada, renderizada y destruida.
 * Hereda de Entity.
 */
class
    Actor : public Entity {
public:
    /**
     * @brief Constructor por defecto del Actor.
     */
    Actor() = default;

    /**
     * @brief Constructor que inicializa el Actor con un nombre.
     * @param actorName Nombre a asignar al actor.
     */
    Actor(const std::string& actorName);

    /**
     * @brief Destructor virtual por defecto del Actor.
     */
    virtual
        ~Actor() = default;

    /**
     * @brief M�todo que se llama al iniciar el Actor. Puede usarse para inicializar componentes.
     */
    void
        start() override;

    /**
     * @brief M�todo que se llama cada frame para actualizar el estado del Actor.
     * @param deltaTime Tiempo transcurrido desde la �ltima actualizaci�n.
     */
    void
        update(float deltaTime) override;

    /**
     * @brief Renderiza el Actor en la ventana proporcionada.
     * @param window Referencia compartida a la ventana donde se renderiza el actor.
     */
    void
        render(const EngineUtilities::TSharedPointer<Window>& window) override;

    /**
     * @brief M�todo que se llama para destruir el Actor y limpiar sus recursos.
     */
    void
        destroy() override;

    void
        setTexture(const EngineUtilities::TSharedPointer<Texture>& texture);



    /**
     * @brief Obtiene un componente del tipo especificado si existe en el Actor.
     * @tparam T Tipo del componente a buscar.
     * @return Referencia compartida al componente del tipo T si se encuentra; nullptr en caso contrario.
     */
    template <typename T>
    EngineUtilities::TSharedPointer<T> getComponent();

private:
    /**
     * @brief Nombre del actor.
     */
    std::string m_name = "Actor";

};

/**
 * @brief Implementaci�n de la plantilla getComponent.
 * @tparam T Tipo del componente a buscar.
 * @return Referencia compartida al componente del tipo T si se encuentra; nullptr en caso contrario.
 */
template <typename T>
inline EngineUtilities::TSharedPointer<T> Actor::getComponent() {
    for (auto& component : components) {
        EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
        if (specificComponent) {
            return specificComponent;
        }
    }
    return EngineUtilities::TSharedPointer<T>();
}