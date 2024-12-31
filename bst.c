#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h>

#include "bst.h"

// #include "unique_rng.c"
// #include "serve_client.c"

int imClever = 0; 

Node* addNode(Node *root, int data)
{
  Node *newNode = malloc(sizeof(Node));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;

  Node *temp;
  Node *prev = NULL;

  temp = root;
  while(temp) {
    prev = temp;
    if (temp->data > newNode->data)
      temp = temp->right;
    else if (temp->data < newNode->data)
      temp = temp->left;
    else {
      free(newNode);
      return NULL;
    }
  }
  if (prev==NULL)
    root = newNode;
  else {
    if (prev->data > newNode->data)
      prev->right = newNode;
    else
      prev->left = newNode;
  }

  return root;
}

Node* freeSubtree(Node *N) {
  if (N == NULL)
    return NULL;
  freeSubtree(N->left);
  freeSubtree(N->right);
  free(N);
}

void removeSubtreeWorker(Node *R, int data) {
  if (R == NULL)
    return;

  if (R->left && R->left->data == data) {
    freeSubtree(R->left);
    R->left = NULL;
    return;
  }

  if (R->right && R->right->data == data) {
    freeSubtree(R->right);
    R->right = NULL;
    return;
  }

  if (R->data < data)
    removeSubtreeWorker(R->left, data);
  else
    removeSubtreeWorker(R->right, data);  
}

Node* removeSubtree(Node *R, int data) {
  if (R == NULL)
    return NULL;

  if (R->data == data) {
    freeSubtree(R);
    return NULL;
  }
  removeSubtreeWorker(R, data);
  return R;
}

// void displaySubtree(Node *N)
// {
//   if (N==NULL)
//     {
//       return ;
//     }
//   displaySubtree(N->right);
//   printf("%d\n", N->data);
//   displaySubtree(N->left);
// }

void displaySubtree(Node *N){

    if(N == NULL){
        return; 
    }

    if(N->right != NULL) {
        displaySubtree(N->right);
        // printf("Parent Node is %d and right child is %d\n", N->data, N->right->data);
    } 

    // printf("%d\n", N->value);

    if(N->left != NULL) {
        displaySubtree(N->left);
        // printf("Parent Node is %d and left child is %d\n", N->data, N->left->data);

    }
}


int countNodes(Node *N)
{
  int count=0;
  if(N==NULL)
    return 0;
  count = count + countNodes(N->right);
  count = count + countNodes(N->left);
  count = count + 1;
  return count;
}

// int countNodes(Node* N){
//   if(N==NULL)
//     return 0;
//   return 1 + countNodes(N->left) + countNodes(N->right);

// }

// this is the most complicated task
Node* removeNode(Node* root, int data)
{
  // Ensure root isn't null.
  if (root == NULL) {
    return NULL;
  }
  	
  if (data > root->data) {  // data is in the left sub-tree.
    root->left = removeNode(root->left, data);
  } else if (data < root->data) { // data is in the right sub-tree.
    root->right = removeNode(root->right, data);
  } else { // Found the correct node with data
    // Check the three cases - no child, 1 child, 2 child...
    // No Children
    if (root->left == NULL && root->right == NULL) {
      free(root);
      root = NULL;
    }
    // 1 child (on the right)
    else if (root->left == NULL) {
      Node *temp = root; // save current node
      root = root->right;
      free(temp);
    }
    // 1 child (on the left)
    else if (root->right == NULL) {
      Node *temp = root; // save current node
      root = root->left;
      free(temp);
    }
    // Two children
    else {
      // find minimal data of right sub tree
      Node *temp = root->left; 
      while(temp->right != NULL) {
        temp = temp->right;
      }
      root->data = temp->data; // duplicate the node
      root->left = removeNode(root->left, root->data); // delete the duplicate node
    }
  }	
  return root; // parent node can update reference
}

int numberLeaves(Node *N) {
  if (N == NULL)
    return 0;

  if (N->left == NULL && N->right == NULL)
    return 1;

  return numberLeaves(N->left) + numberLeaves(N->right);
}

int nodeDepth(Node *R, Node *N) {
  if (R == NULL || N == NULL)
    return -1;

  if (R == N)
    return 0;

  int subDepth = nodeDepth(R->data < N->data ? R->left : R->right, N);

  if (subDepth >= 0)
    return subDepth + 1;
  else
    return -1;
}

void toArray(Node *N, int* arr){

    if(N == NULL){
      return; 
    }
    if(N->left != NULL) {
        toArray(N->left, arr);
    } 
    *(arr + imClever) = N->data; 
    // printf("added %d from index %d\n", *(arr+imClever), imClever); 
    imClever++;
    
    if(N->right != NULL) {
        toArray(N->right, arr);
    }
}

//TEST BELOW HERE

int AddToArray(Node *node, int arr[], int i)
{
     if(node == NULL)
          return i;


     arr[i] = node->data;
      // printf("added %d\n", *(arr+i)); 

     i++;
     if(node->left != NULL)
          i = AddToArray(node->left, arr, i);
     if(node->right != NULL)
          i = AddToArray(node->right, arr, i);

     return i;
}

//TEST ABOVE HERE


Node* new(int val)
{
    Node* node = (Node*)malloc(sizeof(Node));
 
    node->data = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* bst(int arr[], int first, int last)
{
    int mid;
    // Node* temp = (Node*)malloc(sizeof(Node));
    if (first > last)
        return NULL;
    mid = (first + last) / 2;
    Node* temp = new(arr[mid]);
    temp->left = bst(arr, first, mid - 1);
    temp->right = bst(arr, mid + 1, last);
    return temp;
}

// Node* bst(int arr[], int first, int last)
// {
//     int mid;
//     // Node* temp = (Node*)malloc(sizeof(Node));
//     if (first > last)
//         return NULL;
//     mid = first + (last - first) / 2;
//     Node* temp = new(arr[mid]);
//     temp->left = bst(arr, first, mid - 1);
//     temp->right = bst(arr, mid + 1, last);
//     return temp;
// }

Node* balanceTree (Node* root){
  if (root == NULL){
    return NULL;
  }

    int size = countNodes(root); 
    int* arr = malloc(sizeof(int)*size); 
    // int arr[size];
    toArray(root, arr);
    // AddToArray(root,arr, 0); 
    imClever = 0; //Will allow you to call multiple times, mutex the global
    Node* ret = bst(arr, 0, size-1);
    free(arr); //Will allow you to call multiple times
    return ret; 
}

int calculateSum(Node* root){  
    int sum, sumLeft, sumRight;  
    sum = sumRight = sumLeft = 0;  
      

    //Check whether tree is empty  
    if(root == NULL) {  
        // printf("Tree is empty\n");  
        return 0;  
    } 
        //Calculate the sum of nodes present in left subtree  
    if(root->left != NULL){
      sumLeft = calculateSum(root->left);  
    } 
        //Calculate the sum of nodes present in right subtree  
    if(root->right != NULL){  
      sumRight = calculateSum(root->right);  
    }    
        //Calculate the sum of all nodes by adding sumLeft, sumRight and root node's data  
      sum = root->data + sumLeft + sumRight;   
      return sum;  
  }      


float avgSubtree(Node* root){
    int size = countNodes(root);
    if(size > 0 && root != NULL){
      float sum = calculateSum(root);
      return sum / size;
    }
    return -1; 
} 


// float avgSubtree(Node* root){
//     // pthread_rwlock_rdlock(&lock);

//     int size = countNodes(root);
//     printf("size not null %d\n", size);

//     float sum = 0;

//     if (size > 0 && size != NULL){
//       int* arr = malloc(sizeof(int)*size);
//       // int arr[size];

//       toArray(root, arr); 
//       // AddToArray(root, arr, 0); 
//       for (int i = 0; i < size; i++){
//           sum += arr[i];
//       }
//       imClever = 0; 
//       free(arr); 

//       // pthread_rwlock_unlock(&lock); 
//       printf("sum %f\n", sum);
//       printf("size %d\n", size);
//       float avg = sum / size;
//       return avg; 
//     } else { 
//         return -1; 
//     }
// }

// int main(int argc, char **argv) {
//     Node *root=NULL;
//     Node *root_balanced=NULL;


//     for(int i=0; i<10000; i++){
//     // int r = unique_random_number();
//         root=addNode(root, i);
//     }
//     displaySubtree(root); 


//   // Create a balanced BST from the unbalanced BST
//     root_balanced = balanceTree(root);
//     displaySubtree(root_balanced); 


// } 