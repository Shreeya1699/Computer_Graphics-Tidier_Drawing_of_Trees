/**
* @file         script.cpp
* @brief       	This program runs the main.cpp file through commandline to check all possible binary trees for a given number of nodes
* @details       This program has functions:
				*newNode()- function to create a new tree Node
				preorder()- generates preorder traversal for given inorder traversal.
				construct_Trees -constructs all possible trees with given inorder traversal
				main() - Driver Program to test above functions 
* @author       Shreeya, Gunpreet and Sriram
* @include      bits/stdc++.h
*/

#include <bits/stdc++.h> 

using namespace std; 
///string that contains preorder traversal, fed as commandline input to main.cpp
string pre=" ";

/// Node structure 
struct Node 
{ 
 int key; 
 struct Node *left, *right; 
}; 
 
/**
* @fn           newNode
* @brief        A utility function to create a new tree Node
* @detail 		newNode has 3 attributes: node->key, node->left, node->right
* @param		key value for the node (int).
* @returnl		Node
*/ 
struct Node *newNode(int item) 
{ 
///Creates new node.
 struct Node *temp = new Node;
 temp->key = item; 
 temp->left = temp->right = NULL; 
 return temp; 
} 
 
/// 
/**
* @fn           preorder
* @brief        A utility function to do preorder traversal of BST.
* @detail 		The function is recursively called on left and righ children of the input node.
* @param		pointer to the root of graph.
* @returnl		void
*/
void preorder(Node *root) 
{ 
 if (root != NULL) 
 { 
	 pre=pre+" "+to_string(root->key)+" ";
	 preorder(root->left); 
	 preorder(root->right); 
 } 
 cout<<"Preorder: "<<pre<<endl;
} 
 

/**
* @fn           construct_Trees
* @brief        Function for constructing all possible trees with given inorder traversal stored in an array from 
				arr[start] to arr[end].
* @param		array of integers that has inorder traversal of the tree (int),
				start (int) is the starting position of the traversal and end(int) is the ending position.
* @returnl		vector of type Node (trees)
*/
vector<Node *> construct_Trees(int arr[], int start, int end) 
{ 
 /// List to store all possible trees 
 vector<Node *> trees; 
 
 /* if start > end then subtree will be empty so 
 returning NULL in the list */
 if (start > end) 
 { 
	 trees.push_back(NULL); 
	 return trees; 
 } 
 
 /* Iterating through all values from start to end 
	 for constructing left and right subtree 
	 recursively */
 for (int i = start; i <= end; i++) 
 { 
	 /* Constructing left subtree */
	 vector<Node *> ltrees = construct_Trees(arr, start, i-1); 
 
	 /* Constructing right subtree */
	 vector<Node *> rtrees = construct_Trees(arr, i+1, end); 
 
	 /* Now looping through all left and right subtrees 
	 and connecting them to ith root below */
	 for (int j = 0; j < ltrees.size(); j++) 
	 { 
		 for (int k = 0; k < rtrees.size(); k++) 
		 { 
			 // Making arr[i] as root 
			 Node * node = newNode(arr[i]); 
 
			 // Connecting left subtree 
			 node->left = ltrees[j]; 
 
			 // Connecting right subtree 
			 node->right = rtrees[k]; 
 
			 // Adding this tree to list 
			 trees.push_back(node); 
		 } 
	 } 
 } 
 return trees; 
} 
 
// 
/**
* @fn           construct_Trees
* @brief        Driver Program to test above functions.
* @param		void
* @returnl		int
*/
int main() 
{ 
 
 int n;
 cout<<"Enter the number: ";
 scanf("%d",&n);
 int in[n];
 for(int i=0;i<n;i++){
 	// scanf("%d",&in[i]);
 	in[i]=i+1;
 } 
 
 vector<Node *> trees = construct_Trees(in, 0, n-1); 
 
 for (int i = 0; i < trees.size(); i++) 
 { 
 	int p=1;
	preorder(trees[i]);
	string command=" ";
	string command2=" ";
	string name=" ";
	command="./main "+ to_string(n)+pre;
    system(command.c_str());
    
    pre=" ";
    p++;
	printf("\n"); 
 } 
 return 0; 
} 

