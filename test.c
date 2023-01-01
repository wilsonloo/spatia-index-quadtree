#include <stdlib.h>
#include <time.h>
#include "quadTree.h"

#define NODE_COUNT 100000

int main()
{
    struct QuadTreeNode *root = (struct QuadTreeNode *)malloc(sizeof(struct QuadTreeNode));
    struct Region *root_region = (struct Region *)malloc(sizeof(struct Region));
    initRegion(root_region, -90, 90, -180, 180);
    initNode(root, 1, root_region);

    srand((int)time(NULL));
    int del_idx = rand() % (NODE_COUNT - 1);
    struct ElePoint *del_ele = NULL;

    struct ElePoint *ele = NULL;
    for (int i = 0; i < NODE_COUNT; i++)
    {
        ele = (struct ElePoint *)malloc(sizeof(struct ElePoint));
        ele->id = i;
        ele->x = (float)(rand() % 180 - 90 + (float)(rand() % 1000) / 1000);
        ele->y = (float)(rand() % 360 - 180 + (float)(rand() % 1000) / 1000);
        insertEle(root, ele);
        if (i == del_idx)
        {
            del_ele = ele;
        }
    }

    struct ElePoint test;
    test.x = -24;
    test.y = -45.4;
    queryEle(root, &test);

    deleteEle(root, del_ele);
}