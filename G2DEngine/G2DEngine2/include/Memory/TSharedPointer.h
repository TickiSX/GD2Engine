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
     * @brief Shared pointer class for automatic reference counting memory management.
     *
     * Manages a pointer to an object of type T with reference counting to enable
     * safe sharing of ownership across multiple TSharedPointer instances.
     */
    template<typename T>
    class TSharedPointer
    {
    public:
        /**
         * @brief Default constructor.
         *
         * Initializes with nullptr pointer and reference count.
         */
        TSharedPointer() : ptr(nullptr), refCount(nullptr) {}

        /**
         * @brief Constructor taking a raw pointer.
         *
         * @param rawPtr Raw pointer to manage.
         */
        explicit TSharedPointer(T* rawPtr) : ptr(rawPtr), refCount(new int(1)) {}

        /**
         * @brief Constructor from raw pointer and existing reference count.
         *
         * @param rawPtr Raw pointer to managed object.
         * @param existingRefCount Pointer to existing reference count.
         */
        TSharedPointer(T* rawPtr, int* existingRefCount) : ptr(rawPtr), refCount(existingRefCount)
        {
            if (refCount)
                ++(*refCount);
        }

        /**
         * @brief Copy constructor.
         *
         * Copies pointer and reference count, increments the count.
         *
         * @param other Another TSharedPointer instance.
         */
        TSharedPointer(const TSharedPointer<T>& other) : ptr(other.ptr), refCount(other.refCount)
        {
            if (refCount)
                ++(*refCount);
        }

        /**
         * @brief Move constructor.
         *
         * Transfers ownership from another TSharedPointer, leaving it null.
         *
         * @param other Another TSharedPointer instance.
         */
        TSharedPointer(TSharedPointer<T>&& other) noexcept : ptr(other.ptr), refCount(other.refCount)
        {
            other.ptr = nullptr;
            other.refCount = nullptr;
        }

        /**
         * @brief Copy assignment operator.
         *
         * Releases current object, copies from other, increments ref count.
         *
         * @param other Another TSharedPointer instance.
         * @return Reference to this.
         */
        TSharedPointer<T>& operator=(const TSharedPointer<T>& other)
        {
            if (this != &other)
            {
                release();
                ptr = other.ptr;
                refCount = other.refCount;
                if (refCount)
                    ++(*refCount);
            }
            return *this;
        }

        /**
         * @brief Move assignment operator.
         *
         * Releases current object, takes ownership from other, nulls other.
         *
         * @param other Another TSharedPointer instance.
         * @return Reference to this.
         */
        TSharedPointer<T>& operator=(TSharedPointer<T>&& other) noexcept
        {
            if (this != &other)
            {
                release();
                ptr = other.ptr;
                refCount = other.refCount;
                other.ptr = nullptr;
                other.refCount = nullptr;
            }
            return *this;
        }

        /**
         * @brief Template copy constructor for derived types.
         */
        template<typename U>
        TSharedPointer(const TSharedPointer<U>& other)
            : ptr(other.ptr), refCount(other.refCount)
        {
            if (refCount)
                ++(*refCount);
        }

        /**
         * @brief Destructor.
         *
         * Decrements ref count and deletes managed object and ref count if zero.
         */
        ~TSharedPointer()
        {
            release();
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
         * @brief Conversion to bool to check pointer validity.
         */
        operator bool() const { return ptr != nullptr; }

        /**
         * @brief Returns the raw pointer.
         *
         * @return Raw pointer to managed object.
         */
        T* get() const { return ptr; }

        /**
         * @brief Checks if pointer is null.
         *
         * @return true if pointer is null, false otherwise.
         */
        bool isNull() const { return ptr == nullptr; }

        /**
         * @brief Swap the contents of two TSharedPointer instances.
         *
         * @param other Another TSharedPointer instance.
         */
        void swap(TSharedPointer<T>& other) noexcept
        {
            std::swap(ptr, other.ptr);
            std::swap(refCount, other.refCount);
        }

        /**
         * @brief Reset to manage a new object or nullptr.
         *
         * @param newPtr New raw pointer to manage (default nullptr).
         */
        void reset(T* newPtr = nullptr)
        {
            release();
            if (newPtr)
            {
                ptr = newPtr;
                refCount = new int(1);
            }
            else
            {
                ptr = nullptr;
                refCount = nullptr;
            }
        }

        /**
         * @brief Dynamic cast between shared pointers.
         *
         * @tparam U Target type.
         * @return TSharedPointer<U> casted pointer or null if failed.
         */
        template<typename U>
        TSharedPointer<U> dynamic_pointer_cast() const
        {
            U* castedPtr = dynamic_cast<U*>(ptr);
            if (castedPtr)
            {
                return TSharedPointer<U>(castedPtr, refCount);
            }
            return TSharedPointer<U>();
        }

    private:
        T* ptr;           ///< Managed object pointer.
        int* refCount;    ///< Reference count pointer.

        /**
         * @brief Helper to release current object.
         */
        void release()
        {
            if (refCount && --(*refCount) == 0)
            {
                delete ptr;
                delete refCount;
            }
            ptr = nullptr;
            refCount = nullptr;
        }
    };

    /**
     * @brief Utility function to create a TSharedPointer.
     *
     * @tparam T Type of managed object.
     * @tparam Args Argument types for constructor.
     * @param args Arguments to forward to constructor.
     * @return A new TSharedPointer managing the created object.
     */
    template<typename T, typename... Args>
    TSharedPointer<T> MakeShared(Args&&... args)
    {
        return TSharedPointer<T>(new T(std::forward<Args>(args)...));
    }

} // namespace EngineUtilities
