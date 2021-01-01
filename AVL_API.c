#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>


typedef struct node{
  int height;
  void *key;
  struct node *parent;
  struct node *right;
  struct node *left;
  int count;
}AVL_NODE;


int getHeight( AVL_NODE *node){
    if(!node)
        return 0;
    return node->height;   
}

int calcBalance(AVL_NODE *node){
  if(!node)
    return 0;
  return (getHeight(node->left) - getHeight(node->right));
}

AVL_NODE *newNode(char *key, AVL_NODE *parent){
    AVL_NODE *new = malloc(sizeof(AVL_NODE));
   
    new->parent = parent;
    new->left = NULL;
    new->right = NULL;
    new->height = 1;
    new->key = key;

    return new;
}

AVL_NODE *insert(AVL_NODE *node, char *key){
    if(!node){
        AVL_NODE *new = newNode(key,NULL);
        return new;
    }

    // if(strcmp(node->key,key) == 0){
    //     node->count++;
    // }
    if(strcmp(node->key,key) > 0 ){
         node->left = insert(node->left, key);
    }else{
         node->right = insert(node->right, key);
    }
}

void *LeftLeft(AVL_NODE *node){
    node->left->parent = node->parent;
    node->left->right = node;
    // node->parent = node->left;
}

void *RightRight(AVL_NODE *node){
    node->right->parent = node->parent;
    node->right->left = node;

}

void *RightLeft(AVL_NODE *node){
    node->right->left->parent = node;
    node->left = node->right->left;
    // node->left->right= NULL;
}

void *LeftRight(AVL_NODE *node){
    node->left->right->parent = node;
    node->right = node->left->right;
}

AVL_NODE *balance_tree(AVL_NODE *node){
  AVL_NODE *a,*b;
  int leftHeight,rightHeight;
  leftHeight = getHeight(node->left);
  rightHeight = getHeight(node->right);

  if(leftHeight >= rightHeight)
    a = node->left;
  else
    a = node->right;
  leftHeight = getHeight(a->left);
  rightHeight = getHeight(a->right);
  if(a == node->left){
    if(leftHeight >= rightHeight){
      b = a->left;
    }
    else
      b = a->right;
  }
  if(a == node->right){
    if(leftHeight > rightHeight){
      b = a->left;
    }
    else
      b = a->right;
  }

  if(node->left == a && a->left == b){
      printf("1\n");
    node = LeftLeft(node);
  }

  else if(a == node->right && a->right == b){
    printf("2\n");
    node = RightRight(node);
  }   
  
  else if(a == node->right && b == a->left){
      printf("3\n");
    node = RightLeft(node);
  }

  else if(a == node->left && b == a->right){
    node = LeftRight(node);
  }


  return node;
}


int main(){

    
    AVL_NODE *temp = NULL;
    
    temp = insert(temp,"d");
    temp = insert(temp,"a");
    temp = insert(temp,"c");

    temp = balance_tree(temp);

    printf("%s\n",(char *)temp->key);  
    printf("%s\n",(char *)temp->left->key);     
    printf("%s\n",(char *)temp->right->key);
    
}



// valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes ./avl