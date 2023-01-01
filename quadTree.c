#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "quadTree.h"

#ifndef INSERT_INTO_CELL
#define INSERT_INTO_CELL(node, CELL, bottom, up, left, right, elem)  \
    if (node->CELL == NULL)                                          \
    {                                                                \
        node->CELL = createChildNode(node, bottom, up, left, right); \
    }                                                                \
    insertEle(node->CELL, ele);
#endif

/**
 * 插入元素
 * 1.判断是否已分裂，已分裂的选择适合的子结点，插入；
 * 2.未分裂的查看是否过载，过载的分裂结点，重新插入；
 * 3.未过载的直接添加
 *
 * @param node
 * @param ele
 */
void insertEle(struct QuadTreeNode *node, struct ElePoint *ele)
{
    if (1 == node->is_leaf)
    {
        if (node->ele_num + 1 > MAX_ELE_NUM)
        {
            splitNode(node);
            insertEle(node, ele);
        }
        else
        {
            if (node->ele_list == NULL)
            {
                node->ele_list = (struct ElePoint **)malloc(sizeof(struct ElePoint *) * MAX_ELE_NUM);
            }
            node->ele_list[node->ele_num] = ele;
            node->ele_num++;
        }

        return;
    }

    double mid_vertical = (node->region.up + node->region.bottom) / 2;
    double mid_horizontal = (node->region.left + node->region.right) / 2;
    if (ele->y > mid_vertical)
    {
        if (ele->x > mid_horizontal)
        {
            INSERT_INTO_CELL(node, RU, mid_vertical, node->region.up, mid_horizontal, node->region.right, ele)
        }
        else
        {
            INSERT_INTO_CELL(node, LU, mid_vertical, node->region.up, node->region.left, mid_horizontal, ele)
        }
    }
    else
    {
        if (ele->x > mid_horizontal)
        {
            INSERT_INTO_CELL(node, RB, node->region.bottom, mid_vertical, mid_horizontal, node->region.right, ele)
        }
        else
        {
            INSERT_INTO_CELL(node, LB, node->region.bottom, mid_vertical, node->region.left, mid_horizontal, ele)
        }
    }
}

/**
 * 分裂结点
 * 1.通过父结点获取子结点的深度和范围
 * 2.生成四个结点，挂载到父结点下
 *
 * @param node
 */
void splitNode(struct QuadTreeNode *node)
{
    double mid_vertical = (node->region.up + node->region.bottom) / 2;
    double mid_horizontal = (node->region.left + node->region.right) / 2;

    node->is_leaf = 0;

    struct ElePoint **ele_list = node->ele_list;
    node->ele_list = NULL;

    int ele_num = node->ele_num;
    node->ele_num = 0;

    for (int i = 0; i < ele_num; ++i)
    {
        insertEle(node, ele_list[i]);
    }
    free(ele_list);
}

struct QuadTreeNode *createChildNode(struct QuadTreeNode *node, double bottom, double up, double left, double right)
{
    int depth = node->depth + 1;
    struct QuadTreeNode *childNode = (struct QuadTreeNode *)malloc(sizeof(struct QuadTreeNode));
    struct Region *region = (struct Region *)malloc(sizeof(struct Region));
    initRegion(region, bottom, up, left, right);
    initNode(childNode, depth, region);

    return childNode;
}

void deleteEle(struct QuadTreeNode *node, struct ElePoint *ele)
{
    if (node == NULL)
    {
        printf("无法找到\n");
        return;
    }

    if (node->is_leaf == 1)
    {
        for (int j = 0; j < node->ele_num; ++j)
        {
            if (node->ele_list[j]->id == ele->id)
            {
                printf("已移除id:%d (%f,%f)\n", ele->id, ele->x, ele->y);
                for (int k = j; k < node->ele_num - 1; ++k)
                {
                    node->ele_list[k] = node->ele_list[k + 1];
                }
                node->ele_num -= 1;
                break;
            }
        }
        return;
    }

    double mid_vertical = (node->region.up + node->region.bottom) / 2;
    double mid_horizontal = (node->region.left + node->region.right) / 2;
    if (ele->y > mid_vertical)
    {
        if (ele->x > mid_horizontal)
        {
            deleteEle(node->RU, ele);
        }
        else
        {
            deleteEle(node->LU, ele);
        }
    }
    else
    {
        if (ele->x > mid_horizontal)
        {
            deleteEle(node->RB, ele);
        }
        else
        {
            deleteEle(node->LB, ele);
        }
    }
}

void combineNode(struct QuadTreeNode *node)
{
    /**
     * 遍历四个子象限的点，添加到象限点列表
     * 释放子象限的内存
     */
}

void queryEle(struct QuadTreeNode *node, struct ElePoint *ele)
{
    if (node == NULL)
    {
        return;
    }
    if (node->is_leaf == 1)
    {
        printf("附近点有%d个，分别是：\n", node->ele_num);
        for (int j = 0; j < node->ele_num; ++j)
        {
            printf("%f,%f\n", node->ele_list[j]->y, node->ele_list[j]->x);
        }
        return;
    }

    double mid_vertical = (node->region.up + node->region.bottom) / 2;
    double mid_horizontal = (node->region.left + node->region.right) / 2;

    if (ele->y > mid_vertical)
    {
        if (ele->x > mid_horizontal)
        {
            queryEle(node->RU, ele);
        }
        else
        {
            queryEle(node->LU, ele);
        }
    }
    else
    {
        if (ele->x > mid_horizontal)
        {
            queryEle(node->RB, ele);
        }
        else
        {
            queryEle(node->LB, ele);
        }
    }
}

void initNode(struct QuadTreeNode *node, int depth, struct Region *region)
{
    node->depth = depth;
    node->is_leaf = 1;
    node->ele_num = 0;
    node->ele_list = NULL;
    node->region = *region;
    node->RU = NULL;
    node->RB = NULL;
    node->LB = NULL;
    node->LU = NULL;
}

void initRegion(struct Region *region, double bottom, double up, double left, double right)
{
    region->bottom = bottom;
    region->up = up;
    region->left = left;
    region->right = right;
}
