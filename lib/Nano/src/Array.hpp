#pragma once

#include "Nano.hpp"

namespace nano
{

    template <typename T>
    class List;

    template <typename T>
    class Array
    {
    private:
        T *data;
        dword count;

    public:
        Array() : data(nullptr), count(0) {}

        Array(T *arr) : data(arr), count(0)
        {
            while (data[count] != '\0')
                count++;
        }

        ~Array()
        {
            delete[] data;
        }

        T &operator[](dword index) const
        {
            return data[index];
        }

        void Add(T item)
        {
            T *newData = new T[count + 1];
            for (dword i = 0; i < count; i++)
                newData[i] = data[i];
            newData[count] = item;
            delete[] data;
            data = newData;
            count++;
        }

        void Remove(T item)
        {
            dword index = IndexOf(item);
            if (index != -1)
                RemoveAt(index);
        }

        void RemoveAt(dword index)
        {
            if (index >= count)
                return;

            T *newData = new T[count - 1];
            for (dword i = 0, j = 0; i < count; i++, j++)
            {
                if (i == index)
                    j--;
                else
                    newData[j] = data[i];
            }
            delete[] data;
            data = newData;
            count--;
        }

        void Clear()
        {
            delete[] data;
            data = nullptr;
            count = 0;
        }

        dword Count()
        {
            return count;
        }

        dword IndexOf(T item)
        {
            for (dword i = 0; i < count; i++)
                if (data[i] == item)
                    return i;
            return -1;
        }

        void operator+=(T item)
        {
            Add(item);
        }

        List<T> ToList();
    };

} // namespace nano

#include "List.hpp"
