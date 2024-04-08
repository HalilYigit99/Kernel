#pragma once

#include "Nano.hpp"


namespace nano
{

    template <typename T>
    class Array;

    template <typename T>
    class List
    {
        private:

            struct Node
            {
                T data;
                Node* next;
            };

            Node* _head;
            Node* _tail;
            int _size;

        public:

            List() : _head(nullptr), _tail(nullptr), _size(0) { }

            ~List()
            {
                while (_head!= nullptr)
                {
                    Node* temp = _head;
                    _head = _head->next;
                    delete temp;
                }
            }

            int Count() const { return _size; }

            T& operator[](int index)
            {
                Node* current = _head;
                for (int i = 0; i < index; i++)
                {
                    current = current->next;
                }
                return current->data;
            }

            void Add(T item)
            {
                Node* newNode = new Node();
                if (!newNode)
                {
                    return;
                }
                newNode->data = item;
                newNode->next = nullptr;

                if (_head == nullptr)
                {
                    _head = newNode;
                    _tail = newNode;
                }
                else
                {
                    _tail->next = newNode;
                    _tail = newNode;
                }
                _size++;
            }

            void Remove(T item)
            {
                Node* current = _head;
                Node* previous = nullptr;

                while (current!= nullptr)
                {
                    if (current->data == item)
                    {
                        if (previous == nullptr)
                        {
                            _head = current->next;
                        }
                        else
                        {
                            previous->next = current->next;
                        }
                        if (current == _tail)
                        {
                            _tail = previous;
                        }
                        delete current;
                        _size--;
                        return;
                    }
                    previous = current;
                    current = current->next;
                }
            }

            bool Contains(T item)
            {
                Node* current = _head;
                while (current!= nullptr)
                {
                    if (current->data == item)
                    {
                        return true;
                    }
                    current = current->next;
                }
                return false;
            }

            // Add support for range-based for loops
            Node* begin() { return _head; }
            Node* end() { return nullptr; }

            Array<T> ToArray();

            void operator += (T item);

            void Clear();

    };

} // namespace nano


#include "Array.hpp"