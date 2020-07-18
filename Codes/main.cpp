/**
* @file         main.cpp
* @brief        This is the main driver program which calls the rest of the programs
* @details       This program consists of three functions : 
                draw_graph()-traverses the tree and plots all the points using bresenham algorithms,
                draw_figure()- void function which calls draw_graph() and is passed as parameter to glutDisplayFunc() - an opengl function to display the renderings
                Init()- opengl function which initializes the window attributes
* @author       Shreeya, Gunpreet and Sriram
* @include      Tidier_algo.h - header file which implements 'Tidier Drawing of Trees' algorithm and constructs
                binary search tree from Inorder and Preorder traversal of it.
                glDraw.h - header file which draws circes and lines using bresenham algorithms
                based on the coordinate values provided by Tidier_algo.h
                GL/glut.h -header for opengl specifications
                STL Libraries like : vector, queue, climits
*/
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include "glDraw.h"
#include "Tidier_algo.h"
#include <vector>
#include <queue>
#include <climits>
#include <FreeImage.h>
///global variable
int n;
///vector that contains preorder traversal of tree
vector<int> pres;
///It is declared globally so that draw_graph() function can access it. 
///It contains pointer to the root node of the tree.
Node* temp_root;

/**
* @fn           draw_graph
* @brief        uses BFS algorithm to traverse the tree and draw circle and lines 
                between each nodes of the tree
* @param   The root node of the graph is passed as parameter to draw_graph
* @return  void
*/
void draw_graph(Node* root)
{

    ///clears the buffer
    glClear(GL_COLOR_BUFFER_BIT);
    queue<Node*> q;
    q.push(root);
    ///implements bfs to traverse tree and draw circle and lines
    while (!q.empty())
    {
        Node* temp = q.front();
        q.pop();

        int x1, y1, x2, y2, x3, y3;
        x1 = temp->x;
        y1 = temp->y;
	    
        cout<<"\n"<<"x1, y1: "<<x1<<","<<y1<<endl;
        
        Circle(x1, y1, 10);
        if (temp->llink != NULL)
        {
            q.push(temp->llink);
            x2 = temp->llink->x;
            y2 = temp->llink->y;
            Line(x1, y1, x2, y2);
        }
        if (temp->rlink != NULL)
        {
            q.push(temp->rlink);
            x3 = temp->rlink->x;
            y3 = temp->rlink->y;
            Line(x1, y1, x3, y3);
        }
    }
}
/**
* @fn           draw_figure
* @brief        function that calls draw_graph() as draw_graph takes some parameters, hence it cannot be
                passed as parameter to glutDisplayFunc()
* @parameters   void
* @return type  void
*/
void draw_figure(void)
{
    draw_graph(temp_root);
}

/**
* @fn           Init
* @brief        function that initializes the opengl window parameter
* @parameters   void
* @return type  void
*/

void Init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);				// Set clear color to white 
    glColor3f(1.0, 1.0, 1.0);						// Set fill color to black 
    glViewport(0, 0, 1080, 900);
    glMatrixMode(GL_PROJECTION); 				//Initialize Projection Matrix
    glLoadIdentity();
    gluOrtho2D(0, 1080, 0, 900);
}
/**
* @fn           main
* @brief        driver function which takes input from commandline, calls graph() function of Tidier_algo.h
                ,creates opengl window and displays the renderings
* @parameters   string whose first character is number of nodes in graph and rest is preorder traversal of tree
* @return type  int
*/

int main(int argc, char** argv)
{
    n=atoi(argv[1]);
    int arr[n];
    for(int i=0;i<n;i++){
        arr[i]=atoi(argv[i+2]);
        pres.push_back(arr[i]);
    }
    
        
    ///This function is responsible for tree construction
    Graph g(n, pres);
    ///temp assigned pointer to root node of tree
    temp_root = g.root;
        /// Initialise GLUT library 
    glutInit(&argc, argv);
    /// Set the initial display mode 
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    /// Set the initial window position and size 
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1080,900);
    glutCreateWindow("line");
    /// Initialize drawing colors 
    Init();
    /// Call the displaying function 
    glutDisplayFunc(draw_figure);
    
    glutMainLoop();
}


