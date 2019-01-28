#include<assert.h>
#include<string.h>
#include<malloc.h>


typedef int HPDataType;
typedef int (*compare)(HPDataType left,HPDataType right);

typedef struct Heap
{
  HPDataType *heap;
  int capacity;
  int size;
  compare cmp;
}Heap;

int Less(HPDataType left,HPDataType right)
{
    return left<right;
}

int Great(HPDataType left,HPDataType right)
{
    return left>right;
}

void Swap(HPDataType* left,HPDataType *right)
{
      assert(left && right);
      HPDataType tmp = *left;
      *left = *right;
      *right = tmp;
}

void AdjustDown(Heap *hp,int parent)
{
  assert(hp);
  int child = (parent<<1)+1;
  while(child<hp->size)//
  { 
    //找左右孩子中最小的孩子
    if(child+1<hp->size && hp->cmp(hp->heap[child+1],hp->heap[child]))
        child = child+1;

    //检测parent是否比最小的孩子大
    if(hp->cmp(hp->heap[child], hp->heap[parent]))
    {
      Swap(&hp->heap[parent],&hp->heap[child]);
      parent = child;
      child = (parent<<1)+1;
    } 
    else
      return;
  }
}

void CreateHeap(Heap *hp,int *array,int size,compare cmp)
{    
    int root = ((size-1)-1)>>1;
    assert(hp);
    hp->heap = (HPDataType*)malloc(sizeof(HPDataType));
    if(0 == hp->heap)
    {    
      assert(0);
      return;
    }

    hp->capacity = 9; 
    memcpy(hp->heap,array,size*sizeof(HPDataType));
    hp->size = size;
    //调整为堆
    hp->cmp = cmp;
    for(;root>=0;root--)
    {
      AdjustDown(hp,root);
    }
}

void CheckCapacity(Heap *hp)
{
  assert(hp);
  if(hp->size == hp->capacity)
  {
    int newCapacity = (hp->capacity<<1)+3;
    HPDataType *tmp = (HPDataType*)malloc(sizeof(HPDataType)*newCapacity);
    if(NULL == tmp)
    {
      assert(0);
      return;
    }
    if(hp->heap)
    {
      int i = 0;
      for(;i<hp->size;++i)
        tmp[i] = hp->heap[i];

      free(hp->heap);
    }   
    hp->heap = tmp;
    hp->capacity = newCapacity;
  }
}

void AdjustUp(Heap *hp,int child)
{
  assert(hp);
  int parent = ((child-1)>>1);
  while(child)
  {
    if(hp->cmp(hp->heap[child],hp->heap[parent]))
    {
      Swap(&hp->heap[child],&hp->heap[parent]);
      child = parent;
      parent = ((child-1)>>1);
    } 
    else
      return;  
  }
}

void HeapInsert(Heap *hp,HPDataType data)
{
  //1.将元素放到堆中
  //2.向上调整
  CheckCapacity(hp);
  hp->heap[hp->size++] = data;
  AdjustUp(hp,hp->size-1);
}

int HeapEmpty(Heap *hp)
{
  assert(hp);
  return 0 == hp->size;
}

int HeapSize(Heap *hp)
{
  assert(hp);
  return hp->size;
}

HPDataType HeapTop(Heap *hp)
{
  assert(hp);
  return hp->heap[0];
}

void HeapDestroy(Heap *hp)
{
  assert(hp);
  free(hp);
  hp->heap = 0;
  hp->capacity = 0;
}

void HeapRemove(Heap *hp)
{
  assert(hp);
  if(HeapEmpty(hp))
    return;

  Swap(&hp->heap[0],&hp->heap[hp->size-1]);
  hp->size--;
  AdjustDown(hp,0);
}

void Print(int *array)
{
  int size = sizeof(array)/sizeof(array[0]);
  int i = 0;
  for(;i<size;i++)
  printf("%d ",array[i]);
}
int main()
{
  Heap hp;
  int array[] = {7,3,4,6,2,9};
  CreateHeap(&hp,array,sizeof(array)/sizeof(array[0]),Less);
  HeapInsert(&hp,1);
  HeapRemove(&hp);
  return 0;
}
