/**
* @file         tidier_algo.h
* @brief        This header file implements 'Reingold-Tilford Tidier tree drawing algorithm'
* @detail       It includes three classes: 
				Node, Graph, Extreme 
				Exploiting object oriented paradigm, the assignment of relative co-ordinates, followed by converting them into absolute co-ordinates takes place 
* @author       Shreeya, Gunpreet and Sriram
* @include   	STL Libraries like : bits/stdc++, climits
*/
#include<bits/stdc++.h>
#include<climits>
#include <cstdlib>
using namespace std; 
/// macro for minimum separatio_petn between two nodes on a level
#define MINSEP 100
///The offset value that determines the x-coordinate of the root
int MIN_OFF =10000;



struct Node;
/**
 *  Extreme class
 *  @brief Implements Extreme structure
 * @detail Attributes: addr - address, 
 *              off-offset from root of subtree, 
 *              level- tree level
 */
struct Extreme
{
	Node* addr;
	int off;
	int level;
};

/**
 *  Node class
 * @brief  implements Node structure
 *  Attributes: val- identity number of the node
 *		llink,rlink - the pointers to left and right children of the node respectively
 *		x,y - the x and y co-ordinates of the node respectively
 *		offset - node's distance to each of its children
 *		thread - to indicate whether threading is active or not
 *  Functions:  setup
 *		petrify
 */
struct Node 
{ 
	///value of the node
	int val; 
	///lleft link of the node
	Node *llink;
	/// right link of the node
	Node *rlink;
	///x coordinate of the node 
	int x;
	///y coordinate of the node
	int y;
	///offset from the root
	int offset;
	bool thread;

	/**
	* @fn           parameterized constructor 
	* @brief        It performs initialization of a Node of binary tree, whenever a new Node is created
	* @param   	The value of the node, in order to uniquely identify it in the tree
	*/	
	Node(int val) 
	{ 
		this->val = val; 
		this->llink = this->rlink = NULL; 
		this->x=this->y=0;
		this->thread=false;  
	} 


	/**
	* @fn           setup
	* @brief        It assigns relative x co-ordinates to all nodes during a postorder traversal of the binary tree
	* @param   	level of the node indicating the y co-ordinate 
	* @param   	Information about the rightmost extreme node
	* @param   	Information about the leftmost extreme node
	* @return  	void
	*/
	void setup(int level,Extreme &rmost,Extreme &lmost)
	{
		
		this->y=level;
		Node* L=this->llink;
		Node* R=this->rlink;
		int cursep, rootsep, LOffsum, ROffsum;
		Extreme LL,LR,RL,RR;
		
		if(L != NULL){
			RL.level=-1;
			RR.level=-1;
			rmost.level=-1;
			lmost.level=-1;
			L->setup(level+1,LR,LL);
		}
		
		if(R != NULL){
			LL.level=-1;
			LR.level=-1;
			rmost.level=-1;
			lmost.level=-1;
			R->setup(level+1,RR,RL);
		}
		
		if(L==NULL && R==NULL)
		{
			LL.level=-1;
			RL.level=-1;
			LR.level=-1;
			RR.level=-1;
			
			rmost.addr=lmost.addr=this;
			rmost.level=lmost.level=level;
			rmost.off=lmost.off=0;
			this->offset=0;
		}
		else
		{
			cursep = MINSEP;
			rootsep = MINSEP;
			LOffsum = 0;
			ROffsum = 0;

			/// Consider each level in turn until one subtree is exhausted pushing the subtrees apart when neccessary.
			while (L != NULL && R != NULL) {
				if (cursep < MINSEP) {
					rootsep = rootsep + (MINSEP - cursep);
					cursep = MINSEP;
				}
				///Advance left 
				if (L->rlink != NULL) {
					LOffsum = LOffsum + L->offset;
					cursep = cursep - L->offset;
					L = L->rlink;
				}
				else {
					LOffsum = LOffsum - L->offset;
					cursep = cursep + L->offset;
					L = L->llink;
				}		
				///Advance right
				if (R->llink != NULL) {
					ROffsum = ROffsum - R->offset;
					cursep = cursep - R->offset;
					R =R->llink;
				}
				else {
					ROffsum = ROffsum + R->offset;
					cursep = cursep + R->offset;
					R= R->rlink;
				}
			}
			///Set the offset in node root and include it in accumulated offsets in right and left
			this->offset = (rootsep + 1) / 2;
			LOffsum = LOffsum - this->offset;
			ROffsum = ROffsum + this->offset;

			///Update extreme descendents information
			if (RL.level > LL.level || this->llink == NULL) {
				lmost = RL;
				lmost.off = lmost.off + this->offset;
				
			}
			else {
				lmost = LL;
				lmost.off = lmost.off - this->offset;
				
			}
			if (LR.level > RR.level ||this->rlink == NULL) {
				rmost = LR;
				rmost.off = rmost.off - this->offset;
				
			}
			else {
				rmost = RR;
				rmost.off = rmost.off + this->offset;
				
			}
			///If subtrees of root were of uneven heights,check to see if threadng is necessary, at most one thread needs to be inserted
			if (L != NULL && L != this->llink) {
				(RR.addr)->thread = true;
				(RR.addr)->offset = abs((RR.off + this->offset) - LOffsum);
				if ((LOffsum - this->offset) <= RR.off) {
					(RR.addr)->llink = L;
				}
				else {
					(RR.addr)->rlink = L;
				}
			}
			else if (R != NULL && R != this->rlink) {
				(LL.addr)->thread = true;
				(LL.addr)->offset = abs((LL.off - this->offset) - ROffsum);
				if ((ROffsum + this->offset) >= LL.off) {
					(LL.addr)->rlink = R;
				}
				else {
					(LL.addr)->llink = R;
				}
			}
		}

		

	}

	/**
	* @fn           petrify
	* @brief        It forms the pre-order traversal of the tree converting the relative coordinates to absolute coordinates
	* @param   	col - the x co-ordinate of the middle of frame where the tree will eventually be drawn
	* @return  	void
	*/
	void petrify(int col) {

			this->x = col;
			if(MIN_OFF>this->x){
				MIN_OFF=this->x;
			}
			if (this->thread==true) 
			{
				this->thread = false;
				this->llink = NULL;
				this->rlink = NULL;
			}
			Node* L=this->llink;
			Node* R=this->rlink;
			if(L != NULL)
				L->petrify( col - this->offset);
			if(R !=NULL)
				R->petrify( col + this->offset);
	}

	/**
	* @fn           translation
	* @brief        it adjusts the x -coordinate of the root according to the offset for maximum space utilization
	* @param   		pointer to root of the tree
	* @return  		void
	*/
	void translation(Node *node){
		if (node == NULL)  
	        return; 

	    translation(node->llink);
		node->x -= MIN_OFF - 10; 
	 	translation(node->rlink);  

	}
}; 

/**
 *  Graph class
 * @brief Implements various Graph functions
 *  @detail Attributes: graph_size - number of nodes in the graph
 *		 pre - vector storing pre-order traversal of the tree, 
 *		root - root of tree	, 		
 *  Functions:  constructTree ,
 *		constructTreeRecursive ,
 *		petrify, 
 *		travelInorder, 
 */
struct Graph
{
	int graph_size;
	vector<int> pre;
	Node* root=NULL;

	/**
	* @fn           constructTreeRecursive
	* @brief        function to construct BST from given preorder traversal
	* @return  	pointer to root of the subtree constructed
	*/
	Node* constructTreeRecursive(  int* preIndex, int key,int min, int max ) 
	{ 
		///Base case 
		if( *preIndex >= graph_size ) 
			return NULL; 

		Node* temp=NULL;
		///If current element of pre vector is in range, then only it is part of current subtree 
		if( key > min && key < max ) 
		{ 
			/// Allocate memory for root of this subtree and increment *preIndex 
			temp = new Node(key); 
			*preIndex = *preIndex + 1; 
			
			///constructing subtrees
			if (*preIndex < graph_size) 
			{
				/// All nodes which are in range {min .. key} will go in left subtree, and first such node will be root of left subtree. 
				temp->llink=constructTreeRecursive( preIndex, pre[*preIndex],min, key); 
				/// All nodes which are in range {key..max} will go in right subtree, and first such node will be root of right subtree. 
				temp->rlink=constructTreeRecursive(preIndex, pre[*preIndex],key, max); 
			} 
		} 
		
		return temp; 
	} 

	/**
	* @fn           constructTree
	* @brief        main function to construct BST from given preorder traversal, which provides initialization to preIndex as 0 and calls constructTreeRecursive for constructing entire tree
	* @return  	pointer to root of the tree
	*/
	Node *constructTree() 
	{ 
		int preIndex = 0; 
		return constructTreeRecursive( &preIndex, pre[0], INT_MIN, INT_MAX ); 
	} 

	/**
	* @fn           parameterized constructor 
	* @brief        It performs initialization of a Graph of binary tree, calls constructTree which in turn returns root of the tree, further allowing setup and petrify functions to be called.
	* @param   	n-to initialize graph_size, pres- to initialize pre vector of graph  
	*/
	Graph(int n,vector<int> pres)
	{
		this->graph_size=n;
		this->pre=pres;
		for(int i=0;i<n;i++){
			this->pre[i]=pres[i];
		}

		this->root=constructTree();
		 Extreme lmost,rmost;
		 root->setup(0,lmost,rmost);

		root->petrify(540);
		root->translation(this->root);
		travelInorder(this->root);
			
	}

	/**
	* @fn           travelInorder
	* @brief        modifies y co-ordinate of nodes to produce a good drawing wth sufficient spacing within successive levels
	* @return  	pointer to root of the tree
	*/
	void travelInorder(Node* node)  
	{  
		///base case
	    if (node == NULL)  
	        return; 

	    travelInorder(node->llink);
		node->y = 850 - 50*node->y;
	 	travelInorder(node->rlink);  

	}

};

