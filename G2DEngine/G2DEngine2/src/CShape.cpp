﻿#include "CShape.h"
#include "Window.h"

// Constructor por defecto: crea un círculo para evitar punteros nulos
CShape::CShape()
    : Component(ComponentType::SHAPE)
    , m_shapeType(ShapeType::EMPTY)
{
    createShape(ShapeType::CIRCLE);
}

// Constructor con tipo de forma específico
CShape::CShape(ShapeType shapeType)
    : Component(ComponentType::SHAPE)
    , m_shapeType(ShapeType::EMPTY)
{
    createShape(shapeType);
}

// Crea una forma según el tipo indicado
void CShape::createShape(ShapeType shapeType) {
    m_shapeType = shapeType;

    switch (shapeType) {
    case ShapeType::CIRCLE: {
        auto circleSP = EngineUtilities::MakeShared<sf::CircleShape>(10.f);
        circleSP->setFillColor(sf::Color::Green);
        m_shapePtr = circleSP;
        break;
    }
    case ShapeType::RECTANGLE: {
        auto rectSP = EngineUtilities::MakeShared<sf::RectangleShape>(sf::Vector2f(100.f, 50.f));
        rectSP->setFillColor(sf::Color::White);
        m_shapePtr = rectSP;
        break;
    }
    case ShapeType::TRIANGLE: {
        auto convex = EngineUtilities::MakeShared<sf::ConvexShape>(3);
        convex->setPoint(0, sf::Vector2f(0.f, 0.f));
        convex->setPoint(1, sf::Vector2f(50.f, 100.f));
        convex->setPoint(2, sf::Vector2f(100.f, 0.f));
        convex->setFillColor(sf::Color::Blue);
        m_shapePtr = convex;
        break;
    }
    case ShapeType::POLYGON: {
        auto poly = EngineUtilities::MakeShared<sf::ConvexShape>(5);
        poly->setPoint(0, sf::Vector2f(0.f, 0.f));
        poly->setPoint(1, sf::Vector2f(50.f, 100.f));
        poly->setPoint(2, sf::Vector2f(100.f, 0.f));
        poly->setPoint(3, sf::Vector2f(75.f, -50.f));
        poly->setPoint(4, sf::Vector2f(-25.f, -50.f));
        poly->setFillColor(sf::Color::Red);
        m_shapePtr = poly;
        break;
    }
    default:
        m_shapePtr.reset();
        ERROR("CShape", "createShape", "Unknown shape type");
        return;
    }
}

// Métodos de ciclo de vida (vacíos por ahora)
void CShape::start() {}
void CShape::update(float) {}
void CShape::destroy() {}

// Renderiza la forma en la ventana
void CShape::render(const EngineUtilities::TSharedPointer<Window>& window) {
    if (m_shapePtr) {
        window->draw(*m_shapePtr);
    }
    else {
        ERROR("CShape", "render", "Shape is not initialized.");
    }
}

// Cambia posición usando coordenadas x, y
void CShape::setPosition(float x, float y) {
    if (m_shapePtr) {
        m_shapePtr->setPosition(sf::Vector2f(x, y));
    }
    else {
        ERROR("CShape", "setPosition", "Shape is not initialized.");
    }
}

// Cambia posición usando vector 2D
void CShape::setPosition(const sf::Vector2f& position) {
    if (m_shapePtr) {
        m_shapePtr->setPosition(position);
    }
    else {
        ERROR("CShape", "setPosition", "Shape is not initialized.");
    }
}

// Cambia el color de relleno
void CShape::setFillColor(const sf::Color& color) {
    if (m_shapePtr) {
        m_shapePtr->setFillColor(color);
    }
    else {
        ERROR("CShape", "setFillColor", "Shape is not initialized.");
    }
}

// Rota la forma en grados
void CShape::setRotation(float angleDegrees) {
    if (m_shapePtr) {
        m_shapePtr->setRotation(sf::degrees(angleDegrees));
    }
    else {
        ERROR("CShape", "setRotation", "Shape is not initialized.");
    }
}

// Escala la forma
void CShape::setScale(const sf::Vector2f& scl) {
    if (m_shapePtr) {
        m_shapePtr->setScale(scl);
    }
    else {
        ERROR("CShape", "setScale", "Shape is not initialized.");
    }
}

// Devuelve un puntero crudo a la forma SFML
sf::Shape* CShape::getShape() {
    return m_shapePtr.get();
}

// Asigna una textura a la forma
void CShape::setTexture(const EngineUtilities::TSharedPointer<Texture>& texture) {
    if (m_shapePtr && texture && !texture.isNull()) {
        m_shapePtr->setTexture(&texture->getTexture());
    }
}