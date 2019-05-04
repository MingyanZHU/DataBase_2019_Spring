# Lab 4

## 关于ExtMem库的一些注意事项
1. `numFreeBlk` 可能比 `numAllBlk`还大，所以`numFreeBlk`没有参考价值，其更新过于混乱。
2. 在使用`writeBlockToDisk`函数后无需手动释放输出缓存，已经在函数内部Free过了。

## 使用ExtMem库的我所遵守的一些原则
1. 在使用后将函数内局部使用的Buffer Block释放，保持调用函数前后缓存中的block数目不变。