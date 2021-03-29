#pragma once
#include"errors.h"
template <typename elem_t>
class Stack
{
    private:
        #ifndef UNSAFE
        long long CANARY_1;
        #endif // UNSAFE

        size_t size;
        size_t capacity;
        elem_t *stack;

        #ifndef UNSAFE
        hash_t hash;
        long long CANARYBEGIN1;
        long long CANARYBEGIN2;
        hash_t Hash();
        #endif // UNSAFE

        int PlusMemory(elem_t* ptr);

        #ifndef UNSAFE
        long long CANARY_2;
        #endif // UNSAFE
        int ErrManager(Cmd c);

    public:
        bool Create(size_t cap);
        bool Push(elem_t data);
        bool Pop(elem_t *data);
        bool Destroy();
        bool Top(elem_t *data);
        bool Clear();
        bool Size(elem_t *number);
        bool Print();
        bool Dump();
};
