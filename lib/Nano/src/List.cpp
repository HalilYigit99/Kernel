#include "List.hpp"

namespace nano
{

    template <typename T>
    Array<T> List<T>::ToArray()
    {
        Array<T> arr(_size);
        Node* current = _head;
        for (int i = 0; i < _size; i++)
        {
            arr[i] = current->data;
            current = current->next;
        }
        return arr;
    }

    template <typename T>
    void List<T>::operator+=(T item)
    {
        Add(item);
    }

    template <typename T>
    void List<T>::Clear()
    {
        while (_head!= nullptr)
        {
            Node* temp = _head;
            _head = _head->next;
            delete temp;
        }
        _tail = nullptr;
        _size = 0;
    }
    
} // namespace nano

