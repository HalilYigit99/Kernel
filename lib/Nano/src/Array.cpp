#include "List.hpp"
#include "Array.hpp"

namespace nano
{

    template <typename T>
    List<T> Array<T>::ToList()
    {
        List<T> list;
        for (int i = 0; i < this->count; i++)
        {
            list.Add(this->data[i]);
        }
        return list;
    }

} // namespace nano

