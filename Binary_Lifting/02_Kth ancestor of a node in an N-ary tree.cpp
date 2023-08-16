// Question:
// Given a vertex V of an N-ary tree and an integer K, 
// the task is to print the Kth ancestor/parent of the given vertex in the tree. 
// If there does not exist any such ancestor then print -1.

// Approach:
// technique is based on the fact that every integer can be represented in binary form. 
// Through pre-processing, a sparse table table[v][i] can be calculated 
// which stores the 2^i parent of the vertex v where 0 <= i <= log2N. 
// This pre-processing takes O(NlogN) time. 

// To find the Kth parent of the vertex V, 
// let K = b0b1b2…bn be an n bit number in the binary representation, 
// let p1, p2, p3, …, pj be the indices where bit value is 1 
// then K can be represented as K = 2^p1 + 2^p2 + 2^p3 + … + 2^pj. 
// Thus to reach Kth parent of V, we have to make jumps to 2^p1, 2^p2, 2^p3 upto 2^pj parent in any order. 
// This can be done efficiently through the sparse table calculated earlier in O(logN).


