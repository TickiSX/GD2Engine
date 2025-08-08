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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#pragma once

namespace EngineUtilities {

    /**
     * @brief Static pointer class for managing a single static instance.
     *
     * Manages a single static object pointer and provides methods for access,
     * null checks, and basic memory management.
     */
    template<typename T>
    class TStaticPtr
    {
    public:
        /**
         * @brief Default constructor initializes the static pointer to nullptr.
         */
        TStaticPtr() = default;

        /**
         * @brief Constructor accepting a raw pointer.
         *
         * Deletes any existing instance before taking ownership of the new pointer.
         *
         * @param rawPtr Raw pointer to manage.
         */
        explicit TStaticPtr(T* rawPtr)
        {
            if (instance != nullptr)
            {
                delete instance;
            }
            instance = rawPtr;
        }

        /**
         * @brief Destructor deletes the managed instance if it exists.
         */
        ~TStaticPtr()
        {
            if (instance != nullptr)
            {
                delete instance;
                instance = nullptr;
            }
        }

        /**
         * @brief Returns the managed static pointer.
         *
         * @return Raw pointer to the managed object.
         */
        static T* get()
        {
            return instance;
        }

        /**
         * @brief Checks if the static pointer is null.
         *
         * @return True if the pointer is null, false otherwise.
         */
        static bool isNull()
        {
            return instance == nullptr;
        }

        /**
         * @brief Resets the static pointer to manage a new object or nullptr.
         *
         * Deletes the current instance if it exists, then takes ownership of the new pointer.
         *
         * @param rawPtr New raw pointer to manage (default nullptr).
         */
        static void reset(T* rawPtr = nullptr)
        {
            if (instance != nullptr)
            {
                delete instance;
            }
            instance = rawPtr;
        }

    private:
        static T* instance; ///< Static pointer to the managed object.
    };

    // Definition of the static member outside the class template
    template<typename T>
    T* TStaticPtr<T>::instance = nullptr;

} // namespace EngineUtilities
