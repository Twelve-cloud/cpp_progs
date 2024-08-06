#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <iostream>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <climits>
#include <malloc.h>

class GarbageCollector
{
private:
    struct MemoryStore
    {
        void* ptr;
        const char* file;
        std::size_t line;
    };
    static bool trace;
    static std::size_t last;
    static constexpr std::size_t SIZE_MAP = 30000u;
    static MemoryStore map[SIZE_MAP];
    static std::size_t findptr(void* ptr)
    {
        for (std::size_t i = 0; i < last; ++i)
        {
            if (ptr == map[i].ptr)
                return i;
        }

        return ULONG_MAX;
    }
public:
    GarbageCollector()
    {
        map[SIZE_MAP - 1] = { nullptr, "", 0u };
    }

    static void push_back(void* ptr, const char* file, std::size_t line)
    {
        map[last].file = file;
        map[last].line = line;
        map[last++].ptr = ptr;
    }

    static bool delptr(void* ptr)
    {
        std::size_t index = findptr(ptr);

        if (index == ULONG_MAX)
        {
            return false;
        }
        else if (index == 0)
        {
            map[last] = map[SIZE_MAP - 1];
        }
        else
        {
            for (std::size_t i = index; i < last - 1; ++i)
            {
              map[i] = map[i + 1];
            }
        }
        --last;
        return true;
    }

    static void setTrace(bool t) { trace = t; }
    static bool getTrace() { return trace; }

    ~GarbageCollector()
    {
        for (std::size_t i = 0; i < last; ++i)
        {
            if (trace)
                std::cout << "Memory leak at: Adress: " << map[i].ptr << "; File: " << map[i].file << "; Line: " << map[i].line << std::endl;
            free(map[i].ptr);
        }
    }
};

GarbageCollector::MemoryStore GarbageCollector::map[SIZE_MAP];
std::size_t GarbageCollector::last = 0;
bool GarbageCollector::trace = false;

GarbageCollector collector;

void* operator new(std::size_t size, const char* file, std::size_t line)
{
    void* ptr = malloc(size);
    if (ptr == nullptr)
        throw std::bad_alloc();
    GarbageCollector::push_back(ptr, file, line);

    return ptr;
}

void* operator new[](std::size_t size, const char* file, std::size_t line)
{
    return operator new(size, file, line);
}

void operator delete(void* ptr)  _GLIBCXX_USE_NOEXCEPT
{
    if (ptr != nullptr)
    {

        if (!GarbageCollector::delptr(ptr))
        {
            if (GarbageCollector::getTrace())
                std::cout << "Trying to delete non-heap memory or attempting to re-delete pointer" << std::endl;
        }
        else
        {
            free(ptr);
        }
    }
}

void operator delete[](void* ptr)  _GLIBCXX_USE_NOEXCEPT
{
    operator delete(ptr);
}

#define new new(__FILE__, __LINE__)

#endif // COLLECTOR_H

