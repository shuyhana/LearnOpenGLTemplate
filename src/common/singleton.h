#pragma once

template <typename T> class Singleton
{
private:
    /** @brief Explicit private copy constructor. This is a forbidden operation.*/
    Singleton(const Singleton<T>&);

    /** @brief Private operator= . This is a forbidden operation. */
    Singleton& operator=(const Singleton<T>&);

protected:
    static T* msSingleton;

public:

    Singleton(void)
    {
        msSingleton = static_cast<T*>(this);
    }
    ~Singleton(void)
    {
        msSingleton = 0;
    }
    /// Get the singleton instance
    static T& getInstance(void)
    {
        return (*msSingleton);
    }
    /// @copydoc getSingleton
    static T* getSingletonPtr(void) { return msSingleton; }

};
