# Computer_Graphics-Tidier_Drawing_of_Trees
Implementation of Research paper: 'Tidier Drawing of Trees', Authors : Edward M. Reingold and John S. Tilford, Journal: IEEE Transaction on, Software Engineering, Vol-7, Issue-2, 1981. The algorithm is implemented on Binary trees. Bresenham algorithms for line and circle drawing were used to draw the binary tree. Opengl and freeglut is used for rendering of the figures.

## Compiling Instructions:

1. gcc -c glDraw.h
2. g++ -o main main.cpp glDraw.h Tidier_algo.h -lGL -lGLU -lglut
3. g++ script.cpp


## Team:

    Shreeya Bharat Nelekar - 2017A7PS0093H
        Department of Computer Science
    Gunpreet Kaur - 2017A7PS1573H
        Department of Computer Science
    Sriram Kodey - 2018A4PS0671H
        Department of Mechanical Engineering

## General Discussion on Algorithm

Wetherell and Shannon have presented this algorithm which is a modification of Algorithm WS, that guarantees minimum widthd rawings. This algorithm does a preorder traversal of the nodes and the left and right shortest subtrees to get the geometric coordinates of the nodes. While construction of this algorithm following aesthetics were kept in mind-

• Aesthetic 1: Nodes at the same level of the tree should lie along a straight line, and the straight lines defining the levels should be parallel. This is accomplished by providing same value to the attribute ‘level’ of the children nodes of a parent.

• Aesthetic 2: A left son should be positioned to the left of its father and a right son to the right.

• Aesthetic 3: A father should be centered over its sons. These are accomplished by assigning offsets appropriately with respect to the parent node.

• Aesthetic 4: A tree and its mirror image should produce drawings that are reflections of one another; moreover, a sub-tree should be drawn the same way regardless of where it occurs in the tree. This is the special property retained by this algorithm by the way it assigns the coordinates to the nodes. It essentially pushes the subtrees away till they don’t overlap.
Issues in coding:

• The Structure of the function setup was such that we had to traverse one level beyond leaves to provide initialization for the setup function for the leaf nodes. However it was a challenge in Object oriented paradigm wherein we couldn’t call a function with NULL pointer, so the initialization for the parameters for each node was done at the beginning and was later overwritten by non- leaf node function calls.

• The parameters of the glutInitWindowSize(l,w) function had to be same as the parameters passed to gluOrtho2D() and glViewport(0,0,l,b) for the lines and circles to be less pixelated. Even though this isn’t necessary for larger window size.

• A separate algorithm has been made in “glDraw.h” to handle Vertical lines as Bresenham’s Midpoint Algorithm will require calculation of slope, which invloves division by ‘0’ which is not possible and thus throws an error.

• Petrify-The leftmost node of the tree had to be drawn from the extreme left of the screen,so that maximum number of nodes could be drawn. Therefore, another function “translation” to change x- coordinates accordingly.
References:

    Tidier Drawings of Trees Author: Edward M. Reingold and John S. Tilford Journal: IEEE Transaction on Software Engineering, Vol-7, Issue-2, 1981.
    https://www3.ntu.edu.sg/home/ehchua/programming/opengl/HowTo_OpenGL_C.html
    https://www.geeksforgeeks.org/construct-a-binary-tree-from-postorder-and-inorder/
    https://www.cs.brandeis.edu/~cs155/OpenGL%20Lecture_02.pdf

## Timing Analysis:

• constructTree() - The function for construction of tree from its preorder anad inorder traversal. The average time complexity of this function is O(h), where h height of the binary search tree. Best case time complexity: O(log2n), Worst case time complexity :O(n)

• Tidier drawing algorithm: The algorithm has a preorder traversal, which has complexity of O(n) . Then adding to the time complexity is the section of traversing the right part of the left subtree and the left part of the right subtree. The complexities of traversal of these parts are derived as : Initially to get the total number, we need to add up the number of smaller portions of right parts of left subtrees and viceversa for each node. Let's assume that for each level i there are pi nodes. We claim that pi-1 needs to be added for each level to result in the number of runs we require.This is because, as it's a binary tree each of the pi-1 nodes on the (i-1)th level can either produce maximum two new nodes or a leaf. This gives us the pi nodes on the ith level, pi being an even number (Assuming the maximum that if a node gives rise to a new node it gives rise to 2).

Initially, 1 traversal is considered per 2 nodes to account for their three member tree with their direct parent, adding all of them on this level gives us pi/2. Then to this we add 1 traversal per adjacent right child and left child nodes who don't have direct common parents on the above level . We have (pi-2)/2 of these (Since first and last are removed leaving us with pi-2 nodes which we have to take 2 at a time thus we divide by 2) adding both we get pi-1 total traversals that a level adds. Summing all the pi's over all levels we get the number of traversals as:

    The number of nodes (N(T)) - The height of the tree (H(T)). 

Therefore we can say that this algorithm is linear in the number of nodes of the tree in terms of time complexity, i.e O(n).

• Drawing using Bresenham Algorithms: The tree is drawn by traversing the tree using BFS and in the course draing the circle and connecting lines. As BFS has complexity of O(V+E) where V is number of nodes of the tree and E is the number of edges. Hence for the case of binary search tree , V =n and E is of order O(n) . Therefore complexity of drawing the tree in O(n).

## Scope of Improvement:

The code can be made faster at the cost of memory, which will be used to store the (x,y) co-ordinates of the nodes thus eliminating the need to traverse the tree again while drawing the lines and circles. 



