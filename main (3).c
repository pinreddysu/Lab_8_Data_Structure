#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct AdjListNode
{
    char dest;
    int weight;
    struct AdjListNode* next;
};

struct AdjList
{
    //char label[26];
    //struct AdjList *next;
    char label;
    struct AdjListNode *head;  // pointer to head node of list
};

struct Graph
{
    int V;
    //char arr[26];
    //int *visited;
    struct AdjList* array;
};

void is_alpha(char *str);
void remove_spaces(char* s);
char * removeSpacesFromStr(char *string);
void DFS(struct Graph* graph, char vertex);
int front =-1;
int rear = -1;
char queu[26];
void enqueue(char q);
int dequeue();
char peek();
struct AdjListNode* newAdjListNode(char dest, int weight);
struct Graph* createGraph(int V, char *vertex_ins);
void addEdge(struct Graph* graph, char src, char dest, int weight, int Flag);
void printGraph(struct Graph* graph, int tot_vertex);
void bfs(struct Graph *graph, int tot_vertex, char ver);
/*
 AUTHOR: Suchith Pinreddy, Yash Nikumb
 FILENAME: main.c
 SPECIFICATION: To print the adjacency list for a directed and undirected graph and run breadth or depth search
 FOR: CS 2413 Data Structures Section 002
*/
int main()
{
    FILE *infile;
    infile = fopen("adjadency.txt", "r");
    int val;
    int val1;
    char vertex[60];
    char *vertex_wo_space;
    char *word;
    char edges[60];
    char total_nodes[1];
    char source;
    char destination;
    char weight_char[1];
    int weight_conv;
    fgets(total_nodes, 60, infile);
    val = atoi(total_nodes);
    //printf("VAL: %d\n", val);
    char undirect[1];
    fgets(undirect, 60, infile);
    val1 = atoi(undirect);
    //printf("VAL!: %d\n", val1);
    fgets(vertex, 60, infile);
    vertex_wo_space = removeSpacesFromStr(vertex);
    //printf("VERTEX: %s", vertex_wo_space);
    struct Graph* graph = createGraph(val, vertex_wo_space);
    while(fgets(edges, 60, infile)){
        //printf("Vertex_weight %s\n", edges);
        //val1 = atoi(vertex_weight);
        word = removeSpacesFromStr(edges);
        //printf("EDGES: %s\t", word);
        source = word[0];
        //printf("SORCE: %c\t", source);
        destination = word[1];
        //printf("DEST: %c\t", destination);
        weight_char[0] = word[2];
        weight_conv = atoi(weight_char);
        //printf("WEIGHT %d\n", weight_conv);
        //is_alpha(vertex_weight);
        addEdge(graph, source, destination, weight_conv, val1);
    }
    printf("\n Adjacency list: \n");
    printf("  Number of vertices %d:\n",val);
    printGraph(graph, val);
    //bfs(graph, val, 'A');
    return 0;
}
char * removeSpacesFromStr(char *string)
{
    // non_space_count to keep the frequency of non space characters
    int non_space_count = 0;

    //Traverse a string and if it is non space character then, place it at index non_space_count
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] != ' ')
        {
            string[non_space_count] = string[i];
            non_space_count++;//non_space_count incremented
        }
    }

    //Finally placing final character at the string end
    string[non_space_count] = '\0';
    return string;
}
struct AdjListNode* newAdjListNode(char dest, int weight)
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
struct Graph* createGraph(int V, char *vertex_ins)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    for (int j = 0; j < V; ++j)
        graph->array[j].label = vertex_ins[j];

    return graph;
}
/* NAME: addEdge
 PARAMETERS: struct Graph* graph, char src, char dest, int weight
 PURPOSE: The purpose of th function is to
 PRECONDITION: What should be true regarding the parameters and when the function can be called
 POSTCONDITION: What should be true after the function returns, such as variables changed or values returned
*/
void addEdge(struct Graph* graph, char src, char dest, int weight, int Flag)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the beginin
    struct AdjListNode* newNode = newAdjListNode(dest, weight);

    //***Changed. you need to add adge in src node. But you were always adding in 0
    struct AdjListNode* temp=graph->array[src - 'A'].head;

    if(temp==NULL)  // First element of the list
      graph->array[src - 'A'].head=newNode;
    else
    {
        while(temp->next!=NULL) // finding the last element of the list
            temp=temp->next;
        temp->next=newNode; // Adding current element to the last
    }
    //printf("x%d\n", Flag);
    if(!(Flag)){

    // Since graph is undirected, add an edge from dest to src also
        newNode = newAdjListNode(src, weight);

    //***Changed. you need to add adge in dest node. But you were always adding in 1
        temp = graph->array[dest - 'A'].head;

        if(temp==NULL) // First element of the list
            graph->array[dest - 'A'].head=newNode;
        else
        {
            while(temp->next!=NULL) // finding the last element of the list
                temp=temp->next;
            temp->next=newNode; // Adding current element to the last
        }
    }
}
/* NAME: printGraph
 PARAMETERS: struct Graph* graph, int tot_vertex
 PURPOSE: The purpose of the function is to print the adjacency list out.
 PRECONDITION: The variables as actual parameters should be a struct tuype and an integer
 POSTCONDITION: Function should print the right adjacency list.
*/

void printGraph(struct Graph* graph, int tot_vertex)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        //struct AdjList *temp;
        //temp = graph->array;
        //printf("%s\n", temp[v]);
        //printf("FLAG %c\n", graph->array[v].label);
        printf("  %c: ", graph->array[v].label);
        while (pCrawl)
        {
            printf(" (%c, %d) -> ", pCrawl->dest,pCrawl->weight);
            pCrawl = pCrawl->next;
        }
        printf(" (nil)\n");
    }
}
/* NAME: bfs
 PARAMETERS: struct Graph *graph, int tot_vertex, char ver
 PURPOSE: The purpose of the function is to print the breath first search of a graph.
 PRECONDITION: the fucntion should pass a struct type variable, an integer value and a string value
 POSTCONDITION: The function should print the breath firt search of the graph
*/
void bfs(struct Graph *graph, int tot_vertex, char ver){
    struct AdjListNode* temp1;
    struct AdjListNode* temp;
    char x;
    int y;
    char z;
    int i = 0;
    char origin[6] = {'\0'};
    int status[6] = {1};

    while(ver - 'A' <= 6){
        if(status[ver-'A']==1){
            enqueue(ver);
            status[ver-'A'] = 2;
        }
        temp = graph->array[ver-'A'].head;
        //temp1 = graph->array[ver-'A'].label;
        while(temp!=NULL){
            if(status[temp->dest-'A']==1){
                status[temp->dest-'A'] = 2;
                origin[temp->dest-'A'] = ver;
                enqueue(temp->dest);
            }
            temp = temp->next;
        }
        x = peek();
        printf("%c ", x);
        y = dequeue(); //cur val
        //z = y + 'A';
        status[ver-'A'] = 3;
        printf("%c ", origin[i]);
        i++;
        //ver = ver +;
        if (ver+'A' == tot_vertex-1){
            break;
        }
    }
}
/* NAME: dequeue
 PARAMETERS: -
 PURPOSE: Adding an element or enquing the queue
 PRECONDITION:
 POSTCONDITION: The function should print the breath firt search of the graph
*/
void enqueue(char q){
    if(rear == 25)
    {
        printf("\nOVERFLOW\n");
        return;
    }
    if(front == -1 && rear == -1)
    {
        front = 0;
        rear = 0;
    }
    else
    {
        rear = rear+1;
    }
    queu[rear] = q;
    printf("\nValue inserted ");

}
/* NAME: dequeue
 PARAMETERS: -
 PURPOSE: Deleteing or dequing the queue and checking if the queue is an underflow
 PRECONDITION: The function is a void function
 POSTCONDITION: The function return the front
*/
int dequeue(){
    char val;
    if(front == -1 || front> rear){
        printf("UNDERFLOW");
    }
    else{
        val = queu[front];
        front = front + 1;
    }
    return front;
}
/* NAME: peek
 PARAMETERS: -
 PURPOSE: to check if the queue is empty and return the front of the queue.
 PRECONDITION: The function is void.
 POSTCONDITION: The fucntion should return the front elements of the queue.
*/
char peek(){
    if(front == -1 || front < rear){
        printf("Queue is empty");
        //return;
    }
    else{
        return queu[front];
    }
}
/*
analysis:
1. Big O of building the adjacency list in terms of number of vertices V and edges E: O(V+E)
2. Big O of the storage requirements for the adjacency list: O(V^2)
3. Big O of the storage needs for the breadth or depth-first search: O(V*E)
Team member names:
1. Yash Nikumb: a)void is_alpha(char *str); = Implemented
b) void remove_spaces(char* s); = imlemented
c) char * removeSpacesFromStr(char *string); = modified
d) void DFS(struct Graph* graph, char vertex); = modified
e) void enqueue(char q); = Implemented
f) int dequeue(); = Checked
e) char peek(); = Checked
h) struct AdjListNode* newAdjListNode(char dest, int weight); = Implemented
i) struct Graph* createGraph(int V, char *vertex_ins); = Modified
j) void addEdge(struct Graph* graph, char src, char dest, int weight, int Flag); = Checked
h) void printGraph(struct Graph* graph, int tot_vertex); = Modified
i) void bfs(struct Graph *graph, int tot_vertex, char ver); = Modified


2: Suchith Pinreddy:  a)void is_alpha(char *str); = modified
b) void remove_spaces(char* s); = modified
c) char * removeSpacesFromStr(char *string); = modified
d) void DFS(struct Graph* graph, char vertex); = implmented
e) void enqueue(char q); = Checked
f) int dequeue(); = Modified
e) char peek(); = Implemeted
h) struct AdjListNode* newAdjListNode(char dest, int weight); = checked
i) struct Graph* createGraph(int V, char *vertex_ins); = Checked
j) void addEdge(struct Graph* graph, char src, char dest, int weight, int Flag); = Implemented
h) void printGraph(struct Graph* graph, int tot_vertex); = Implemented
i) void bfs(struct Graph *graph, int tot_vertex, char ver); = Implemented

 ii. Test Cases and Status
1. Undirected graph file – partially passed as the breadth  first search is not working as enqueue fucntion is not working
2. Directed graph file – partially passed as the breadth  first search is not working as enqueue fucntion is not working
SOURCES:
1. https://stackoverflow.com/questions/27583307/why-my-output-isnt-correct
2. https://www.programiz.com/dsa/graph-bfs
*/
