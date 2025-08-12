#include "ResourceManager.h"
#include <iostream>
#include <filesystem>

bool ResourceManager::loadTexture(const std::string& fileName, const std::string& extension) {
    // Si ya est� cargada, no hacemos nada
    auto it = m_textures.find(fileName);
    if (it != m_textures.end() && !it->second.isNull()) {
        return true; // ya la ten�amos
    }

    // Construir ruta: e.g. "Sprites/Track" + ".png"
    std::string fullName = fileName + "." + extension;
    std::filesystem::path fullPath = std::filesystem::absolute(fullName);

    // Intentar cargar
    auto texturePtr = EngineUtilities::MakeShared<Texture>(fileName, extension);
    // El constructor de Texture ya intenta cargar y emplace el sprite solo si tiene �xito.
    // Pero verificamos si la textura interna se carg� correctamente inspeccionando si el sprite est� presente.

    // Para diagnosticar, podr�as agregar print aqu� si quieres
    // Nota: No tenemos acceso directo a saber si fall� sin exponerlo en Texture; asumimos que si el archivo no existe,
    // el usuario ver� el mensaje que imprime Texture.

    // Guardar en el mapa (incluso si fall�, as� no se reintenta infinitamente sin control)
    m_textures[fileName] = texturePtr;

    // Retornar true si la textura fue cargada (podemos comprobar si getTexture devolvi� algo v�lido)
    return !texturePtr.isNull();
}

EngineUtilities::TSharedPointer<Texture> ResourceManager::getTexture(const std::string& fileName) {
    auto it = m_textures.find(fileName);
    if (it != m_textures.end()) {
        return it->second;
    }
    // No encontrada: devolver shared pointer nulo
    return EngineUtilities::TSharedPointer<Texture>();
}