2 applications:
1. find Kth parent/ancestor of a tree node (NOTE: Tree is IMP)
2. LCA in a tree

MIS-CONECPTION: binary lifting ONLY works on TREES => WRONG!!!
CORRECT: As long as the path to any node is unique, the binary lifting can be used. (eg a cyclic graph where each node has only 1 parent)

pre-processing time : O(N*logN)
query time : O(logN)
