#ifndef _BTREE_H
#define _BTREE_H

#define MIN_T 3
#define MAX_T (MIN_T * 2)

typedef struct BTreeNodeData BTreeNodeData;
typedef struct BTreeNodeData *BTreeNode;
typedef struct BTreeData BTreeData;
typedef struct BTreeData *BTree;

struct BTreeNodeData
{
    //关键字个数
    int n;
    //是否是叶子结点，1为叶子结点，0为非叶子结点
    int leaf;
    int key[MAX_T - 1];
    BTreeNode child[MAX_T];
};

struct BTreeData
{
    BTreeNode root;
};

#define BTREE_NODE_SIZE sizeof(BTreeNodeData)
#define BTREE_SIZE sizeof(BTreeData)

//为结点分配空间
BTreeNode allocate_node();
//初始化树
void btree_create(BTree tree);
//寻找关键字位置
void btree_search(BTreeNode node, int key);
//分裂子结点
void btree_splice_child(BTreeNode node, int location);
//向未满结点插入关键字
void btree_insert_nonfull(BTreeNode node, int key);
//向树插入关键字
void btree_insert(BTree tree, int key);
//显示以结点node_first为父结点的树
void display_node(BTreeNode *node_first, int n);
//显示整棵树
void dsplay_tree(BTree tree);
//以node为根结点，寻找最小关键字
BTreeNode btree_minimum(BTreeNode node);
//以node为根结点，寻找最大关键字
BTreeNode btree_maximum(BTreeNode node);
//在整棵树中寻找最小关键字
void btree_min(BTree tree);
//在整棵树中寻找最大关键字
void btree_max(BTree tree);
//将父结点、右兄弟、该结点的关键字调整
void btree_left(BTreeNode parent, BTreeNode node, BTreeNode othernode, int location);
//将父结点、左兄弟、该结点的关键字调整
void btree_right(BTreeNode parent, BTreeNode node, BTreeNode othernode, int location);
//合并子结点，并返回下降子结点的位置
int btree_merge_child(BTreeNode parent, int location);
//删除叶子结点关键字
void btree_delete_leaf(BTreeNode r_node, int location);
//删除内结点关键字，并返回下降子结点的位置
int btree_delete_node_in(BTreeNode r_node, int i);
//删除以r_node为根结点的树中关键字
void btree_delete_node(BTreeNode r_node, int key);
//删除书中关键字
void btree_delete(BTree btree, int key);
#endif