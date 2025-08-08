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
     * @brief TUniquePtr class for exclusive memory ownership.
     *
     * Manages the lifetime of a single object of type T and ensures
     * only one TUniquePtr instance owns the object at any time.
     */
    template<typename T>
    class TUniquePtr
    {
    public:
        /**
         * @brief Default constructor initializes pointer to nullptr.
         */
        TUniquePtr() : ptr(nullptr) {}

        /**
         * @brief Constructor taking a raw pointer.
         *
         * @param rawPtr Raw pointer to manage.
         */
        explicit TUniquePtr(T* rawPtr) : ptr(rawPtr) {}

        /**
         * @brief Move constructor transfers ownership from another TUniquePtr.
         *
         * @param other Another TUniquePtr instance.
         */
        TUniquePtr(TUniquePtr<T>&& other) noexcept : ptr(other.ptr)
        {
            other.ptr = nullptr;
        }

        /**
         * @brief Move assignment operator transfers ownership and releases current.
         *
         * @param other Another TUniquePtr instance.
         * @return Reference to this instance.
         */
        TUniquePtr<T>& operator=(TUniquePtr<T>&& other) noexcept
        {
            if (this != &other)
            {
                delete ptr;
                ptr = other.ptr;
                other.ptr = nullptr;
            }
            return *this;
        }

        /**
         * @brief Destructor deletes the managed object.
         */
        ~TUniquePtr()
        {
            delete ptr;
        }

        // Disable copy semantics
        TUniquePtr(const TUniquePtr<T>&) = delete;
        TUniquePtr<T>& operator=(const TUniquePtr<T>&) = delete;

        /**
         * @brief Templated move constructor for compatible types.
         */
        template<typename U>
        TUniquePtr(TUniquePtr<U>&& other) noexcept
            : ptr(static_cast<T*>(other.release())) {
        }

        /**
         * @brief Dereference operator.
         *
         * @return Reference to managed object.
         */
        T& operator*() const { return *ptr; }

        /**
         * @brief Member access operator.
         *
         * @return Pointer to managed object.
         */
        T* operator->() const { return ptr; }

        /**
         * @brief Returns the raw managed pointer.
         *
         * @return Raw pointer.
         */
        T* get() const { return ptr; }

        /**
         * @brief Releases ownership of the managed object.
         *
         * @return Raw pointer, caller is responsible for deleting it.
         */
        T* release()
        {
            T* oldPtr = ptr;
            ptr = nullptr;
            return oldPtr;
        }

        /**
         * @brief Resets the managed pointer to a new object or nullptr.
         *
         * Deletes current object if any.
         *
         * @param rawPtr New raw pointer to manage.
         */
        void reset(T* rawPtr = nullptr)
        {
            delete ptr;
            ptr = rawPtr;
        }

        /**
         * @brief Checks if pointer is null.
         *
         * @return true if no managed object, false otherwise.
         */
        bool isNull() const
        {
            return ptr == nullptr;
        }

    private:
        T* ptr; ///< Raw pointer to managed object.
    };

    /**
     * @brief Utility function to create a TUniquePtr.
     *
     * @tparam T Type of the managed object.
     * @tparam Args Constructor argument types.
     * @param args Constructor arguments.
     * @return TUniquePtr managing a new instance of T.
     */
    template<typename T, typename... Args>
    TUniquePtr<T> MakeUnique(Args... args)
    {
        return TUniquePtr<T>(new T(args...));
    }

} // namespace EngineUtilities
