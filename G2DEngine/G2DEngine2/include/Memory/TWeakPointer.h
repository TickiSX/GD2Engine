/*
 * MIT License
 *
 * Copyright (c) 2024 Roberto Charreton
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * In addition, any project or software that uses this library or class must include
 * the following acknowledgment in the credits:
 *
 * "This project uses software developed by Roberto Charreton and Attribute Overload."
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#pragma once

#include "TSharedPointer.h"

namespace EngineUtilities {

    /**
     * @brief Clase TWeakPointer para observar un objeto gestionado por TSharedPointer.
     *
     * No incrementa el recuento de referencias y permite obtener un TSharedPointer válido
     * sólo si el recurso aún existe.
     */
    template<typename T>
    class TWeakPointer {
    public:
        /**
         * @brief Constructor por defecto.
         */
        TWeakPointer() : ptr(nullptr), refCount(nullptr) {}

        /**
         * @brief Constructor desde un TSharedPointer.
         *
         * @param sharedPtr Objeto compartido a observar.
         */
        TWeakPointer(const TSharedPointer<T>& sharedPtr)
            : ptr(sharedPtr.ptr), refCount(sharedPtr.refCount) {
        }

        /**
         * @brief Convierte el TWeakPointer en un TSharedPointer si el recurso aún existe.
         *
         * @return TSharedPointer válido o nulo si el recurso fue liberado.
         */
        TSharedPointer<T> lock() const {
            if (refCount && *refCount > 0) {
                return TSharedPointer<T>(ptr, refCount);
            }
            return TSharedPointer<T>();
        }

        template<typename U>
        friend class TSharedPointer;

    private:
        T* ptr;         ///< Puntero al objeto observado.
        int* refCount;  ///< Recuento de referencias del objeto observado.
    };

} // namespace EngineUtilities
