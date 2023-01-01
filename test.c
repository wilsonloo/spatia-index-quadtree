#include <stdlib.h>
#include <time.h>
#include "quadTree.h"

int main()
{
    struct QuadTreeNode *root = (struct QuadTreeNode *)malloc(sizeof(struct QuadTreeNode));
    struct Region *root_region = (struct Region *)malloc(sizeof(struct Region));
    initRegion(root_region, -90, 90, -180, 180);
    initNode(root, 1, root_region);

    srand((int)time(NULL));
    struct ElePoint *ele = NULL;
    for (int i = 0; i < 100000; i++)
    {
        ele = (struct ElePoint *)malloc(sizeof(struct ElePoint));
        ele->y = (float)(rand() % 360 - 180 + (float)(rand() % 1000) / 1000);
        ele->x = (float)(rand() % 180 - 90 + (float)(rand() % 1000) / 1000);
        insertEle(root, ele);
    }

    struct ElePoint test;
    test.x = -24;
    test.y = -45.4;
    queryEle(root, &test);
}