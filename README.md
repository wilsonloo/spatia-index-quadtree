# spatialIndex
空间索引的各种实现:

- GeoHash.php geohash算法配合redis sorted set 优化；
- QuadTree.c/QuadTree.h   非满点四叉树

## usage
make
./test

## 问题
1. 需要上层逻辑保证所有节点的位置不能相同，否则在进行切分时可能进入无限切分