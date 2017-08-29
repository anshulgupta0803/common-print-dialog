#ifndef SINGLETON_H
#define SINGLETON_H

#include <QPrinter>
#include <QWidget>

template <class T>
class Singleton
{

public:
    static T *Instance()
    {
        if (!m_Instance) m_Instance = new T;
        Q_ASSERT(m_Instance == nullptr);
        return m_Instance;
    }

protected:
    Singleton();
    ~Singleton();
private:
    Singleton(Singleton const &) = delete;
    Singleton &operator=(Singleton const &);
    static T *m_Instance;
};

template <class T> T *Singleton<T>::m_Instance = nullptr;

#endif // SINGLETON_H
