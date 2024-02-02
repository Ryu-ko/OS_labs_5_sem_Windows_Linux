#include <iostream>
#include <Windows.h>

using namespace std;

void HeapInfo(HANDLE pheap)
{
    PROCESS_HEAP_ENTRY phe;
    phe.lpData = NULL;
    while (HeapWalk(pheap, &phe))
    {
        cout << "-- address = " << hex << phe.lpData
            << ", size = " << dec << phe.cbData
            << ((phe.wFlags & PROCESS_HEAP_REGION) ? " R" : "")
            << ((phe.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) ? " U" : "")
            << ((phe.wFlags & PROCESS_HEAP_ENTRY_BUSY) ? " B" : "")
            << "\n";
    }
    std::cout << "-----------------------------------\n\n";
}

int main()
{
    // Создаем кучу с размером 4MB
    HANDLE userHeap = HeapCreate(HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 4 * 1024 * 1024, 0);

    HeapInfo(userHeap);

    int size = 300000;
    int* m = new int[size];

    int* mm = (int*)HeapAlloc(userHeap, HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 300000 * sizeof(int)); // Выделяем память с помощью польз кучи
    cout << "-address = " << hex << mm << ", size = " << dec << 300000 << " \n\n";

    HeapInfo(userHeap); 

    delete[] m;
    HeapFree(userHeap, 0, mm);

    HeapDestroy(userHeap);

    return 0;
}
