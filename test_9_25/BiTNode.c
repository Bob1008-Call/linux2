#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>

//boot#define ElemType char
typedef char BDataType;
typedef struct BTNode
{
  BDataType data;
  struct BTNode* Lchild;
  struct BTNode* Rchild;
}BTNode;

BTNode *BuyBTNode(BDataType data)
{ 
  BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
  if(NULL == newNode)
  {
    assert(0);
    return NULL;
  }
  newNode->Lchild = NULL;
  newNode->Rchild = NULL;
  newNode->data = data;

  return newNode;
}

void CreateBinTree(BTNode** root,char *str,int size,int* index,BDataType invalid)
{
  assert(root);
  assert(index);
  if(*index<size && '#' != str[*index])
  {
    //创建根节点
    *root = BuyBTNode(str[*index]);
    
    //创建左子树
    ++(*index);
    CreateBinTree(&(*root)->Lchild,str,size,index,invalid);

    //创建右子树
    ++(*index);
    CreateBinTree(&(*root)->Rchild,str,size,index,invalid);
  }

}

void PreOrderTraverse(BTNode *root)
{
  if(root)
  {
    printf("%c",root->data);
    PreOrderTraverse(root->Lchild);
    PreOrderTraverse(root->Rchild);
  }
}

void InOrderTraverse(BTNode *root)
{
  if(root)
  {
    InOrderTraverse(root->Lchild);
    printf("%c",root->data);
    InOrderTraverse(root->Rchild);
  }
}

void PostOrderTraverse(BTNode *root)
{
  if(root)
  {
    PostOrderTraverse(root->Lchild);
    PostOrderTraverse(root->Rchild);
    printf("%c",root->data);
  }
}

BTNode* CopyBinTree(BTNode *root)
{
  BTNode *newRoot = NULL;
  if(root)
  {
    //拷贝根节点
    newRoot = BuyBTNode(root->data);
  
    //拷贝左子树
    if(root->Lchild)
      newRoot->Lchild = CopyBinTree(root->Lchild);

    //拷贝右子树
    if(root->Rchild)
      newRoot->Rchild = CopyBinTree(root->Rchild);
  }
  return newRoot;
}

int GetBTNodeCount(BTNode *root)
{
  if(NULL == root)
  {
    return 0;
  }

  return GetBTNodeCount(root->Lchild)+GetBTNodeCount(root->Rchild)+1;
}

int GetLeafNodeCount(BTNode *root)
{
  if(NULL == root)
  {
    return 0;
  }

  if(NULL == root->Lchild && NULL == root->Rchild)
  {
    return 1;
  }

  return GetLeafNodeCount(root->Lchild) + GetLeafNodeCount(root->Rchild);
}

int GetKLevelNodeCount(BTNode *root,int K)
{
  if(NULL == root)
    return 0;

  if(K == 1)
    return 1;

  return GetKLevelNodeCount(root->Lchild,K-1) + GetKLevelNodeCount(root->Rchild,K-1);
}

int GetBinTreeHeight(BTNode *root)
{
  if(NULL == root)
    return 0;

  int LeftHeight = 0;
  int RightHeight = 0;
  LeftHeight = GetBinTreeHeight(root->Lchild);
  RightHeight = GetBinTreeHeight(root->Rchild);

  return LeftHeight>RightHeight?LeftHeight+1:RightHeight+1;
}


void DestroyBinTree(BTNode **root)
{
  assert(root);
  if(*root)
  {
    DestroyBinTree(&(*root)->Lchild);

    DestroyBinTree(&(*root)->Rchild);

    free(*root);
    *root = NULL;
  }
}

BTNode* LeftNode(BTNode *root)
{
  return NULL!=root?root->Lchild:NULL;
}

BTNode* RightNode(BTNode *root)
{
  return NULL!=root?root->Rchild:NULL;
}

int MaxDistance(BTNode *root,int *m)
{
  if(NULL == root)
  {
    return 0;
  }
  int LeftDepth = 0;
  int RightDepth = 0;
  int *max = m;
  LeftDepth = MaxDistance(root->Lchild,max);
  RightDepth = MaxDistance(root->Rchild,max);
  if(*max < LeftDepth+RightDepth)
    *max  = LeftDepth + RightDepth;
  return LeftDepth>RightDepth?LeftDepth+1:RightDepth+1;
}

int MaxDistance2(BTNode *root)
{
  if(NULL == root)
  {
    return 0;
  }
  int max = 0;
  MaxDistance(root,&max);
  return max;
}

int MaxDistance1(BTNode *root,int *Dis)
{
  if(NULL == root)
  {
    return 0;
  }
  int tmp = GetBinTreeHeight(root->Lchild)+GetBinTreeHeight(root->Rchild);
  if(*Dis<tmp)
  {
    *Dis = tmp;
  }
  return *Dis;
}

int IsBTNodeInBinTree(BTNode *root,BTNode *Node)
{
  if((NULL == root)||(NULL == Node))
    return 0;

  if(root == Node)
    return 1;

  if(IsBTNodeInBinTree(root->Lchild,Node))
    return 1;

  return IsBTNodeInBinTree(root->Rchild,Node);
}

BTNode* GetBTNodeParent(BTNode *root,BTNode *Node)
{
  BTNode *Parent = NULL;
  if((NULL == root)||(NULL == Node)||(Node == root))
    return NULL;

  if(Node == root->Lchild ||Node == root->Rchild)
    return root;

  if(Parent = GetBTNodeParent(root->Lchild,Node))
    return Parent;

  return GetBTNodeParent(root->Rchild,Node);
}

void Swap(BTNode** left,BTNode **right)
{
  assert(left && right);
  BTNode *tmp = *left;
  *left = *right;
  *right = tmp;
}

void MirrorBinTree(BTNode* root)
{
  if(root)
  {
    Swap(&root->Lchild,&root->Rchild);
    MirrorBinTree(root->Lchild);
    MirrorBinTree(root->Rchild);
  }
}

void LevelOrder(BTNode *root)
{
  Queue q;
  if(NULL == root)
    return;

  QueueInit(&q);
  QueuePush(&q,root);
  while(!QueueEmpty(&q))
  {
    BTNode *cur = QueueFront(&q);
    printf("%c ",cur->data);

    if(cur->Lchild)
      QueuePush(&q,cur->Lchild);

    if(cur->Rchild)
      QueuePush(&q,cur->Rchild);

    QueuePop(&q);
  }
}

int IsCompleteBinTree(BTNode *root)
{
  Queue q;
  int IsFlag = 0;
  if(NULL == root)
    return 0;

  QueueInit(&q);
  QueuePush(&q,root);
  while(!QueueEmpty(&q))
  {
    BTNode *cur = QueueFront(&q);

    if(IsFlag)
    {
      if(cur->Lchild || cur->Rchild)
        return 0;
    }
    else
    {
      if(cur->Lchild && cur->Rchild)
      {
       QueuePush(&q,cur->Lchild);
       QueuePush(&q,cur->Rchild);
      }
      else if(cur->Lchild)
      {
        QueuePush(&q,cur->Lchild);
        IsFlag = 1;
      }
      else if(cur->Rchild)
      {
        return 0;
      }
      else
      {
        IsFlag = 1;
      }
      QueuePop(&q);
    }
  }
    return 1;
}

void PreOrderTraverseNor(BTNode *root)
{
  Stack s;
  if(NULL == root)
    return;

  StackInit(&s);
  StackPush(&s,root);

  while(!StackEmpty(&s))
  {
    BTNode *cur = StackTop(&s);
    printf("%c ",cur->data);
    StackPop(&s);

    if(cur->Rchild)
      StackPush(&s,cur->Rchild);

    if(cur->Lchild)
      StackPush(&s,cur->Lchild);
  }
}

void PreOrderTraverseNor2(BTNode *root)
{
  Stack s;
  if(NULL == root)
    return;

  StackInit(&s);
  StackPush(&s,root);
  while(!StackEmpty(&s))
  {
    BTNode *cur = StackTop(&s);
    StackPop(&s);
    while(cur)
    {
      printf("%c",cur->data);
      if(cur->Rchild)
        StackPush(&s,cur->Rchild);
    
      cur = cur->Lchild;
    }
  }
}

void InOrderTraverseNor(BTNode *root)
{
  if(NULL == root)
    return;

  Stack s;
  StackInit(&s);
  BTNode *cur = root;
  while(cur || !StackEmpty(&s))
  {
    while(cur)
    {
       StackPush(&s,cur);
       cur = cur->Lchild;
    }
    cur = StackTop(&s);
    printf("%c ",cur->data);
    StackPop(&s);
    cur = cur->Rchild;
  }
}

void PostOrderTraverseNor(BTNode* root)
{
  if(NULL == root)
    return;
  Stack s;
  StackInit(&s);
  BTNode *pre = NULL;//标记最近访问过的节点
  BTNode *cur = root;
  BTNode *top = NULL;
  while(cur || !StackEmpty(&s))
  {
    while(cur)
    {
      StackPush(&s,cur);
      cur = cur->Lchild;
    }
    top = StackTop(&s);
    if(NULL == top->Rchild || top->Rchild == pre)//右子树已经遍历或者右子树为空。
    {
      printf("%c ",top->data);
      pre = top;
      StackPop(&s);
    }
    else
    {
      cur = cur->Rchild;
    }
  }
}

int main()
{
  BTNode *root = NULL;
  char *str = "ABD###CE##F";
  int index = 0;
  CreateBinTree(&root,str,strlen(str),&index,'#');
  int max = 0;
  printf("%d\n",MaxDistance(root,&max));
  PreOrderTraverse(root);
  printf("\n");
  InOrderTraverse(root);
  printf("\n");
  PostOrderTraverse(root);
  printf("\n");
}

