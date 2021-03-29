#include"stack_class.h"

//-----------------------------------------------------
//! Function "SetColor" can change printing color
//!
//!@param [in] text Color of text you want
//!@param [in] background Color of background you want
//!
//-----------------------------------------------------
void SetColor(ConsoleColor text, ConsoleColor background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
    return;
}

//-----------------------------------------------------
//! Function "RandomBig" count random LEN-signed number
//!
//!@return Random LEN-signed number
//-----------------------------------------------------
long long RandomBig()
{
    static bool first = false;
    if (first == false)
    {
        srand(time(0));
        first = true;
    }

    long long num = rand() % 9 + 1;
    for(int i = 0; i < LEN; ++i)
    {
        num *= 10;
        num += rand() % 10;
    }
    return num;
}

//-----------------------------------------------------
//! Function "Create" creates stack
//!
//!@param [in] cap Capacity of the stack
//!
//-----------------------------------------------------
template <typename elem_t>
bool Stack<elem_t>::Create(size_t cap)
{
    size = 0;
    capacity = cap;
    stack = (elem_t*) new elem_t [cap];

    #ifndef UNSAFE
    CANARYBEGIN1 = RandomBig();
    CANARYBEGIN2 = RandomBig();
    CANARY_1 = CANARYBEGIN1;
    CANARY_2 = CANARYBEGIN2;
    hash = Hash();
    #endif // UNSAFE

    if(ErrManager(CREATE_))
        return FAIL;
    return SUCCESS;
}

#ifndef UNSAFE
//-----------------------------------------------------
//! Function "Hash" counts hash-sum
//!
//!@note Count hash every time when you change stack elements or size
//-----------------------------------------------------
template <typename elem_t>
hash_t Stack<elem_t>::Hash()
{
    return (size * 2 + CANARY_1 % 67 - CANARY_2 % 23 - capacity - 465474 % 48);
}
#endif // UNSAFE

//-----------------------------------------------------
//! Function "Push" pushes elements to stack
//!
//!@param [in] data Element pushing to stack
//!
//-----------------------------------------------------
template <typename elem_t>
bool Stack<elem_t>::Push(elem_t data)
{
    if(ErrManager(PUSH_))
        return FAIL;
    stack[size++] = data;

    #ifndef UNSAFE
    hash = Hash();
    #endif // UNSAFE

    if(ErrManager(PUSH_))
        return FAIL;
    return SUCCESS;
}

//-----------------------------------------------------
//! Function "Pop" pulls elements from stack
//!
//!@param [in] data Variable for the element
//!
//!@note After using element isn't exist in stack
//-----------------------------------------------------
template <typename elem_t>
bool Stack<elem_t>::Pop(elem_t *data)
{
    assert(data != NULL);
    if(ErrManager(POP_BEFORE_))
        return FAIL;
    *data = stack[--size];

    #ifndef UNSAFE
    hash = Hash();
    #endif // UNSAFE

    if(ErrManager(POP_AFTER_))
        return FAIL;
    return SUCCESS;
}

//-----------------------------------------------------
//! Function "Top" get top element from the stack
//!
//!@param [in] data Variable for the element
//!
//!@note After using function element still exist in stack
//-----------------------------------------------------
template <typename elem_t>
bool Stack<elem_t>::Top(elem_t *data)
{
    assert(data != NULL);
    if(ErrManager(TOP_))
        return FAIL;
    *data = stack[size-1];
    if(ErrManager(TOP_))
        return FAIL;
    return SUCCESS;
}

//-----------------------------------------------------
//! Function "Destroy" destroys stack
//-----------------------------------------------------
template <typename elem_t>
bool Stack<elem_t>::Destroy()
{
    delete [] stack;
    size = 0;
    capacity = 0;
    return SUCCESS;
}

//-----------------------------------------------------
//! Function "Clear" deletes all elements of stack
//-----------------------------------------------------
template <typename elem_t>
bool Stack<elem_t>::Clear()
{
    if(ErrManager(CLEAR_))
        return FAIL;
    for(int i = size - 1; i >= 0; --i)
        stack[i] = 0;
    size = 0;

    #ifndef UNSAFE
    hash = Hash();
    #endif // UNSAFE

    if(ErrManager(CLEAR_))
        return FAIL;
    return SUCCESS;
}

//-----------------------------------------------------
//! Function "Size" learns number of elements in stack
//!
//!@param [in] number Variable for the size
//!
//-----------------------------------------------------
template <typename elem_t>
bool Stack<elem_t>::Size(elem_t *number)
{
    assert(number != NULL);
    if(ErrManager(SIZE_))
    *number = size;
    if(ErrManager(SIZE_))
        return FAIL;
    return SUCCESS;
}

//-----------------------------------------------------
//! Function "Print" prints stack
//-----------------------------------------------------
template <typename elem_t>
bool Stack<elem_t>::Print()
{
    if(ErrManager(PRINT_))
        return FAIL;

    for(size_t i = 0; i < size; ++i)
        std::cout << "Element number " << i + 1 << " is " << stack[i] << std::endl;
    return SUCCESS;
}

//-----------------------------------------------------
//! Function "Dump" print all characteristic of stack and it's elements
//-----------------------------------------------------
template <typename elem_t>
bool Stack<elem_t>::Dump()
{
    if(ErrManager(DUMP_))
    {
        printf("\nFAIL");
        return FAIL;
    }
    SetColor(Cyan, Black);
    printf("\n\t\tDUMP\n");
    SetColor(Green, Black);
    printf("%s", "Pointer of the stack:");
    SetColor(Red, Black);
    printf("\t\t%p\n", stack);
    SetColor(Green, Black);
    printf("%s", "Capacity of the stack:");
    SetColor(Red, Black);
    printf("\t\t%d\n", capacity);
    SetColor(Green, Black);
    printf("%s", "Number of elements in stack:");
    SetColor(Red, Black);
    printf("\t%d\n", size);

    #ifndef UNSAFE
    SetColor(Green, Black);
    printf("%s\t", "Hash:");
    SetColor(Red, Black);
    printf("\t\t\t%Ld\n", hash);
    SetColor(Green, Black);
    printf("%s", "First canary:");
    SetColor(Red, Black);
    printf("\t\t\t%Ld\n", CANARY_1);
    SetColor(Green, Black);
    printf("%s", "Second canary:");
    SetColor(Red, Black);
    printf("\t\t\t%Ld\n\n", CANARY_2);
    #endif // UNSAFE

    SetColor(Blue, Black);
    printf("%s\n", "Stack elements:");
    Print();
    SetColor(Cyan, Black);
    printf("\n\t\tEND OF DUMP\n");
    SetColor(White, Black);
    if(ErrManager(DUMP_))
        return FAIL;
    return SUCCESS;
}

//-----------------------------------------------------
//! Function "PlusMemory" adds memory if it was over
//!
//!@note You can change number of added memory
//-----------------------------------------------------
template <typename elem_t>
int Stack<elem_t>::PlusMemory(elem_t* ptr)
{
    assert(ptr != NULL);
    ptr = (elem_t *)realloc(ptr, capacity + 10*sizeof(elem_t));
    if(ptr == NULL)
    {
        printf("Memory is over\n");
        Destroy();
        return NO_MEM_MORE;
    }
    else
    {
        capacity += 10;
        return ALL_GOOD;
    }
}

//-----------------------------------------------------
//! Function "ErrManager" check correctness of functions
//-----------------------------------------------------
template <typename elem_t>
int Stack<elem_t>::ErrManager(Cmd c)
{
    if(capacity <= 0)
    {
        printf("Capacity is wrong\n");
        Destroy();
        return ERR_CAP;
    }
    else if(size < 0)
    {
        printf("Size is wrong\n");
        Destroy();
        return ERR_SIZE;
    }
    else if(size > capacity)
    {
        printf("Stack is overflowing\n");
        Destroy();
        return OVER_FLOW;
    }

    #ifndef UNSAFE
    else if(CANARY_1 != CANARYBEGIN1 || CANARY_2 != CANARYBEGIN2)
    {
        printf("Canaries aren't right\n");
        Destroy();
        return ERR_CANARY;
    }
    else if(hash != Hash())
    {
        printf("Hash-sum isn't right\n");
        Destroy();
        return ERR_HASH;
    }
    #endif // UNSAFE

    else if(stack == NULL)
    {
        printf("The pointer to stack is NULL\n");
        Destroy();
        return ERR_PTR;
    }
    else if(size == capacity && c == PUSH_)
        return PlusMemory(stack);

    else if(size == 0 && c == POP_BEFORE_)
    {
        printf("Stack is empty\n");
        Destroy();
        return EMPTY;
    }
    else
        return ALL_GOOD;
}
