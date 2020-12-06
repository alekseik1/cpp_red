#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate() {
        T* obj = TryAllocate();
        if (obj == nullptr) {
            obj = new T;
            allocated.insert(obj);
        }
        return obj;
    }
    T* TryAllocate() {
        T* obj = nullptr;
        if (!released.empty()) {
            obj = released.front();
            released.pop();
            allocated.insert(obj);
        }
        return obj;
    }

    void Deallocate(T* object) {
        if (allocated.count(object)) {
            allocated.erase(object);
            released.push(object);
        } else throw invalid_argument("Object is not allocated");
    }

    ~ObjectPool() {
        for (auto i : allocated) delete i;
        while (!released.empty()) {
            delete released.front();
            released.pop();
        }
    }

private:
    set<T*> allocated;
    queue<T*> released;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}