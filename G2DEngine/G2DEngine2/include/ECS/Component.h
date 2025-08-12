#pragma once
enum ComponentType {
	None = 0,       ///< No component
	TRANSFORM = 1,  ///< Transform component (position, rotation, scale)
	SRPITE = 2,     ///< Sprite component (2D image)
	RENDERER = 3,   ///< Renderer component
	PHYSICS = 4,    ///< Physics simulation component
	AUDIOSOURCE = 5,///< Audio source component
	SHAPE = 6,      ///< Shape component (geometry-based)
	TEXTURE = 7     ///< Texture component (for applying textures)
};
/**
 * @file Component.h
 * @brief Declares the base Component class and ComponentType enumeration for entity components.
 */

#include "../Prerequisites.h"

class
	Window;

#pragma once
/**
 * @file Component.h
 * @brief Declara la clase base Component y la enumeración ComponentType para los componentes de entidad.
 */

#include "../Prerequisites.h"

class Window;

/**
 * @enum ComponentType
 * @brief Enumeración de todos los posibles tipos de componentes usados en el sistema ECS.
 */
enum ComponentType {
	None = 0,       ///< Sin componente
	TRANSFORM = 1,  ///< Componente de transformación (posición, rotación, escala)
	SRPITE = 2,     ///< Componente de sprite (imagen 2D)
	RENDERER = 3,   ///< Componente de renderizado
	PHYSICS = 4,    ///< Componente de simulación física
	AUDIOSOURCE = 5,///< Componente de fuente de audio
	SHAPE = 6,      ///< Componente de forma (basado en geometría)
	TEXTURE = 7     ///< Componente de textura (para aplicar texturas)
};

/**
 * @class Component
 * @brief Clase base abstracta para todos los componentes del motor de juego.
 *
 * Los componentes representan comportamiento o datos asociados a los objetos del juego.
 * Esta clase provee métodos virtuales que deben ser sobreescritos por los componentes derivados.
 */
class Component {
public:
	Component() = default;
	Component(const ComponentType type) : m_type(type) {}
	virtual ~Component() = default;

	virtual void start() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(const EngineUtilities::TSharedPointer<Window>& window) = 0;
	virtual void destroy() = 0;

	ComponentType getType() const { return m_type; }

protected:
	ComponentType m_type;
};

/**
 * @class Component
 * @brief Abstract base class for all components in the game engine.
 *
 * Components represent behavior or data associated with game objects. This class provides
 * virtual methods that must be overridden by derived components to define behavior.
 */
class
	Component {
public:
	/**
	 * @brief Default constructor.
	 */
	Component() = default;

	/**
	 * @brief Constructor that sets the component type.
	 * @param type Type of the component as defined in ComponentType enum.
	 */
	Component(const ComponentType type) : m_type(type) {}

	/**
	 * @brief Virtual destructor.
	 */
	virtual
		~Component() = default;

	/**
	 * @brief Pure virtual method for initialization logic.
	 * @param deltaTime Time elapsed since last frame (used for time-dependent setup).
	 */
	virtual void
		start() = 0;

	/**
	 * @brief Pure virtual method for updating logic every frame.
	 * @param deltaTime Time elapsed since last frame.
	 */
	virtual void
		update(float deltaTime) = 0;

	/**
	 * @brief Pure virtual method for rendering the component.
	 * @param window Smart pointer to the window where rendering occurs.
	 */
	virtual void
		render(const EngineUtilities::TSharedPointer<Window>& window) = 0;

	/**
	 * @brief Pure virtual method for cleaning up resources.
	 */
	virtual void
		destroy() = 0;

	/**
	 * @brief Gets the type of the component.
	 * @return The component type (enum value).
	 */
	ComponentType
		getType() const { return m_type; }

protected:
	ComponentType m_type; ///< The specific type of the component.
};