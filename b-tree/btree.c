#include "btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

/**
 * 为新结点分配空间
 */
BTreeNode allocate_node()
{
  BTreeNode node = (BTreeNode)malloc(BTREE_NODE_SIZE);
  return node;
}

/**
 * 生成一颗空树
 */
void btree_create(BTree tree)
{
  BTreeNode r_node = allocate_node();

  r_node->n = 0;

  r_node->leaf = 1;
  tree->root = r_node;
}
/**
 * 在以node为根结点的树中，寻找关键字位置，返回关键字所在结点，并将关键字位置保存在location
 */
void btree_search(BTreeNode node, int key)
{
  int j = 0;

  //遍历当前结点，寻找恰当的关键字，如果找到相等的关键字，返回结点并将关键字位置保存在location，如果没找到相等结点，且该结点为叶子结点，则报错，
  //否则递归寻找
  while (j < node->n && key > node->key[j])
  {
    j++;
  }
  if (j < node->n && key == node->key[j])
  {
    printf("the %d key's location is %d in the node %p\n", key, j, node);
  }
  else if (node->leaf)
  {
    printf("error:there is no key\n");
  }
  else
  {
    btree_search(node->child[j], key);
  }
}

/**
 * 分裂父结点node中位置为location的子结点的满结点
 */
void btree_split_node(BTreeNode node, int location)
{
  //建立新的结点
  BTreeNode new_node = allocate_node();
  BTreeNode child_node = node->child[location];

  int i = 0;

  //初始化空结点new_node，将子结点child_node的信息复制到新结点node中
  new_node->leaf = child_node->leaf;
  new_node->n = MIN_T - 1;

  //将子结点child_node后T-1歌关键字复制到新结点中，并改变子结点的n值
  for (i = 0; i <= MIN_T - 2; i++)
  {
    new_node->key[i] = child_node->key[i + MIN_T];
  }

  child_node->n = MIN_T - 1;

  //如果子结点非叶子结点，则相应的将子结点的结点复制到新结点中
  if (!child_node->leaf)
  {
    for (i = 0; i < MIN_T - 1; i++)
    {
      new_node->child[i] = child_node->child[i + MIN_T];
    }
  }
  //将父结点对应的关键以及子结点位置向后移动一位
  for (i = node->n; i > location; i--)
  {
    node->key[i] = node->key[i - 1];
    node->child[i + 1] = node->child[i];
  }

  //为父结点增加新的关键字和子结点，并修改n值
  node->child[location + 1] = new_node;
  node->key[location] = child_node->key[MIN_T - 1];
  node->n = node->n + 1;
}

/**
 * 对非满结点进行插入关键字
 */
void btree_insert_nonfull(BTreeNode node, int key)
{
  int i = node->n - 1;
  if (node->leaf)
  {
    //该结点为叶子结点时，找到对应位置，将关键字插入，并对结点node作出修改
    while (i >= 0 && key < node->key[i])
    {
      node->key[i + 1] = node->key[i];
      i--;
    }
    node->key[i + 1] = key;
    node->n = node->n + 1;
  }
  else
  {
    //对非叶子结点，查找对应子结点，判断是否为满结点，是，则分裂，否则递归插入
    while (i >= 0 && key < node->key[i])
    {
      i--;
    }
    i++;
    if (node->child[i]->n == MAX_T - 1)
    {
      btree_splice_child(node, i);
      if (key > node->key[i])
      {
        i++;
      }
    }
    btree_insert_nonfull(node->child[i], key);
  }
}

/**
 * 对整棵树进行插入关键字
 * 
 * 当树为有且只有一个关键字，且已满时，需要建立新的结点作为树的根结点，
 * 而当原树的根结点作为新结点的子结点，进行分裂操作
 * 否则，直接进行非满结点插入操作
 */
void btree_insert(BTree tree, int key)
{
  BTreeNode r_node = tree->root;

  if (r_node->n == MAX_T - 1)
  {
    BTreeNode r_node_new = allocate_node();

    r_node_new->leaf = 0;
    r_node_new->n = 0;
    r_node_new->child[0] = r_node;

    tree->root = r_node_new;
    btree_splice_child(r_node_new, 0);
    btree_insert_nonfull(r_node_new, key);
  }
  else
  {
    btree_insert_nonfull(r_node, key);
  }
}

/**
 * 为了验证插入以及删除结果正确，添加输出函数
 * 输出以parent为父结点的子树的所有关键字
 * 这里将所有的同一层的结点放入到一个数组中，方便输出
 * 第一个参数node_first作为每一层结点数组的其实地址
 * n为该层结点树
 */
void display_node(BTreeNode *node_first, int n)
{
  int i = 0,
      j = 0,
      k = 0,
      all = 0;
  BTreeNode *node = node_first;

  //将该层的结点所有的关键字输出，不同结点以“ ”为分割，每层以“$$”为分割
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < (*(node + i))->n; j++)
    {
      printf("%d ", (*(node + i))->key[j]);
    }
    all = all + (*(node + i))->n + 1;
    printf(" ");
  }
  printf("$$\n");

  if (!(*node)->leaf)
  {
    BTreeNode nodes[all];
    i = 0;
    for (j = 0; j < n; j++)
    {
      for (k = 0; k <= (*(node + j))->n; k++)
      {
        nodes[i] = (*(node + j))->child[k];
        i++;
      }
    }
    display_node(nodes, all);
  }
}