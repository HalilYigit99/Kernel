#include <stddef.h>
#include <stdlib.h>


void* operator new(size_t n) {
    void* _ret = malloc(n);
    return _ret;
}

void* operator new[](size_t n) {
    void* _ret = malloc(n);
    return _ret;
}

void operator delete[](void* ptr) {
    free(ptr);
}

void operator delete(void* ptr) {
    free(ptr);
}
