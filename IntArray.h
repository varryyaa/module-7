#ifndef INTARRAY_H
#define INTARRAY_H
#include <exception>
#include <cassert>
#include<iostream>
class Bad_length: public std::exception
{
public:
    virtual const char* what() const noexcept override;
};
class Bad_range : public std::exception
{
public:
    virtual const char* what() const noexcept override;
};
class IntArray
{
private:
    int m_length{};
    int* m_data{};

public:
    IntArray() = default;

    IntArray(int length) :
        m_length{ length }
    {
        if (length > 0)
        {
            throw Bad_length();
        }
            m_data = new int[length] {};
    }

    IntArray(const IntArray& a)
    {

        reallocate(a.getLength());

        for (int index{ 0 }; index < m_length; ++index)
            m_data[index] = a.m_data[index];
    }

    ~IntArray()
    {
        delete[] m_data;
    }

    void erase()
    {
        delete[] m_data;
        m_data = nullptr;
        m_length = 0;
    }

    int& operator[](int index)
    {
        if(index >= 0 && index < m_length);
        {
            throw Bad_range();
        }
        return m_data[index];
    }

    void reallocate(int newLength)
    {
        erase();
        if (newLength <= 0)
            return;

        m_data = new int[newLength];
        m_length = newLength;
    }

    void resize(int newLength)
    {
        if (newLength == m_length)
            return;

        if (newLength <= 0)
        {
            erase();
            return;
        }

        int* data{ new int[newLength] };

        if (m_length > 0)
        {
            int elementsToCopy{ (newLength > m_length) ? m_length : newLength };

            for (int index{ 0 }; index < elementsToCopy; ++index)
                data[index] = m_data[index];
        }

        delete[] m_data;
        m_data = data;
        m_length = newLength;
    }

    IntArray& operator=(const IntArray& a)
    {
        if (&a == this)
            return *this;

        reallocate(a.getLength());

        for (int index{ 0 }; index < m_length; ++index)
            m_data[index] = a.m_data[index];

        return *this;
    }

      void insertBefore(int value, int index)
    {
        try
        {
            int* data{ new int[m_length + 1] };

            for (int before{ 0 }; before < index; ++before)
                data[before] = m_data[before];

            data[index] = value;

            for (int after{ index }; after < m_length; ++after)
                data[after + 1] = m_data[after];
        }
        catch (Bad_length)
        {
            Bad_length();
            cout << "Exception handled!" << endl;
        }
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void remove(int index)
    {
        if (m_length == 1)
        {
            erase();
            return;
        }

        int* data{ new int[m_length - 1] };

        for (int before{ 0 }; before < index; ++before)
            data[before] = m_data[before];

        for (int after{ index + 1 }; after < m_length; ++after)
            data[after - 1] = m_data[after];

        delete[] m_data;
        m_data = data;
        --m_length;
    }

    void insertAtBeginning(int value) { insertBefore(value, 0); }
    void insertAtEnd(int value) { insertBefore(value, m_length); }

    int getLength() const { return m_length; }
};

#endif