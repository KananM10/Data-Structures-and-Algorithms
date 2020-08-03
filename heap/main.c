#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void main()
{
    Heap *heap = HEAP_new(5);

    HEAP_add(heap, 10);
    HEAP_add(heap, 6);
    HEAP_add(heap, 2);
    HEAP_add(heap, 9);
    HEAP_add(heap, 4);
    HEAP_add(heap, 8);
    HEAP_add(heap, 50);
    HEAP_add(heap, 75);
    HEAP_add(heap, 62);
    HEAP_add(heap, 27);
    HEAP_add(heap, 100);

    printf("INITIAL HEAP\n");
    HEAP_printArr(heap);

    HEAP_maxAdjustDown(heap, 50);
    int size = heap->size;
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d\n", HEAP_remove(heap));
    }

    HEAP_printArr(heap);
}
