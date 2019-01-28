#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int Key;

typedef struct BSTreeNode 
{
  Key key;
  struct BSTreeNode *left;
  struct BSTreeNode *right;
}BSTreeNode;

int BSTreeSearch(BSTreeNode *root,Key key)
{
  if(NULL == root)
  {
    return -1;
  }
  if(key == root->key)
  {
    return 0;
  }
  else if(key<root->key)
  {
    return BSTreeSearch(root->left,key);
  }
  else 
  {
    return BSTreeSearch(root->right,key);
  } 
}

int BSTreeSearchNor(BSTreeNode *root,Key key)
{
  BSTreeNode *cur = root;
  while(cur != NULL)
  {
    if(cur->key == key)
    {
      return 0;
    }
    else if(key<cur->key)
    {
      cur = cur->left;
    }
    else 
    {
      cur = cur->right;
    }
  }
  return -1;
}
//
int BSTreeInsertNor(BSTreeNode **root,Key key)
{
  assert(root);
  BSTreeNode *cur = *root;
  BSTreeNode *parent = NULL;
  while(cur)
  {
    if(cur->key == key)
    {
      return -1;
    }

    parent = cur;//记录q双亲节点
    if(key<cur->key)
    {
      cur = cur->left;
    }
    else
    {
      cur = cur->right;
    }
  }

  BSTreeNode *node = (BSTreeNode*)malloc(sizeof(BSTreeNode));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  if(parent == NULL)
  {
    *root = node;
  }
  else if(key<parent->key)
  {
    parent->left = node;
  }
  else 
  {
    parent->right = node;
  }
  return 0;
}

int BSTreeInsert(BSTreeNode **root,Key key)
{
  if(*root == NULL)
  {
    BSTreeNode *node = (BSTreeNode*)malloc(sizeof(BSTreeNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    *root = node;
    return 0;
  }
  if(key == (*root)->key)
  {
    return -1;
  }

  if(key<(*root)->key)
  {
    return BSTreeInsert((&(*root)->left),key);
  }
  else 
  {
    return BSTreeInsert((&(*root)->left),key);
  }
}

int BSTreeRemove(BSTreeNode **root,Key key)
{
  assert(root);
  BSTreeNode *cur = *root;
  BSTreeNode *parent = NULL;
  while(cur)
  {
    if(cur->key == key)
      if(cur->left == NULL)
      {
       if(parent == NULL)
        {
         //要删除的是根节点
          *root = cur->right;
        }
        else if(key<parent->key)
        {
          parent->left = cur->right;
        }
        else 
        {
          parent->right = cur->right;
        }
        free(cur);
      }
      if(cur->right == NULL)
      {
        if(parent == NULL)
        {
          *root = cur->left;
        }
        else if(key<parent->key)
        {
          parent->left = cur->left; 
        }
        else 
        {
          parent->right = cur->left;
        }
      }
      else 
      {
        //左右孩子都不为空
        //找右子树的最小
        BSTreeNode *del = cur->right;
        BSTreeNode *delparent = cur;
        while(del->left)
        {
          delparent = del;
          del = del->left;
        }
        if(delparent == cur)
        {
          delparent->right = del->right;
        }
        else 
        {
          delparent->left = del->right;
        }
        free(del);
        return 0;
      }
    parent = cur;
    if(key<cur->key)
    {
      cur = cur->left;
    }
    else 
    {
      cur = cur->right;
    }
  }
  return -1;
}
