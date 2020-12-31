/*
Aniket Patel
1014226
Assignment 2
*/


#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define HEIGHT 1

typedef struct node{
  int height;
  char *key;
  struct node *right;
  struct node *left;
  int count;
}AVL_node;

AVL_node *getNode(char *key){

  AVL_node *new = malloc(sizeof(AVL_node));

  new->left = NULL;
  new->right = NULL;
  new->key = key;
  new->height = HEIGHT;
  return new;

}

int getHeight(AVL_node* node){
  if(!node)
    return 0;
  else
    return node->height;
}

int calcBalance(AVL_node* node){
  if(!node)
    return 0;
  return (getHeight(node->left) - getHeight(node->right));
}

int maa(int a, int b){
  return (a > b) ? a : b;
}
//Left rotate
AVL_node *LF(AVL_node *node){
  AVL_node* right = node->right;
  AVL_node* left = right->left;

  right->left = node;
  node->right = left;

  node->height = maa(getHeight(node->left), getHeight(node->right)) + 1;
  right->height = maa(getHeight(right->left), getHeight(right->right)) + 1;

  return right;

}
//Right Rotate
AVL_node *RF(AVL_node *node){
  AVL_node* left = node->left;
  AVL_node* right = left->right;

  left->right = node;
  node->left = right;

  node->height = maa(getHeight(node->left), getHeight(node->right)) + 1;
  left->height = maa(getHeight(left->left), getHeight(left->right)) + 1;

  return left;


}

AVL_node *insert(AVL_node *node, char *key){

  if(!node){
    AVL_node *new = getNode(key);
    return new;
  }

  if (node->key == key){
    node->count++;

}else if(strcmp(node->key,key) > 0 ) {
    node->left = insert(node->left, key);
}else{
  node->right = insert(node->right, key);
}

node->height = maa(getHeight(node->left), getHeight(node->right)) + 1;

int balance = calcBalance(node);

if(balance > 1 && (strcmp(node->left->key,key) > 0)){
  node = RF(node);
}
else if(balance < -1 && (strcmp(node->right->key,key) < 0) ){
  node = LF(node);
}
else if(balance > 1 && (strcmp(node->left->key,key) < 0)){
  node->left = LF(node->left);
  node = RF(node);
}
  else if(balance < -1 && (strcmp(node->right->key,key) > 0)){
    node->right = RF(node->right);
    node = LF(node);
  }
  return node;

}

AVL_node *balance_tree(AVL_node *node){
  AVL_node *a,*b;
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
    node = RF(node);
  }

  else if(a == node->right && a->right == b){
    node = LF(node);
  }

  else if(a == node->left && b == a->right){
    node->left = LF(node->left);
    node = RF(node);
  }

  else if(a == node->right && b == a->left){
    node->right = RF(node->right);
    node = LF(node);
  }
  return node;
}

AVL_node *inorder_succ_right_tree(AVL_node* node){
  AVL_node* temp = node->right;
  while(temp->left){
    temp = temp->left;
  }
  return temp;
}

AVL_node *deletion(AVL_node *node, char *key){

  if(!node)
    return NULL;
  if(strcmp(node->key,key) > 0){
    node->left = deletion(node->left, key);
  }
  else if(strcmp(node->key,key) < 0){
    node->right = deletion(node->right, key);
  }
  else{
     AVL_node* temp;
    if(node->left == NULL || node->right == NULL){
      if(node->left)
        temp = node->left;
      else if(node->right)
        temp = node->right;
      else
        temp = NULL;
      node = NULL;
      free(node);
      return temp;
    }
    else{
      temp = inorder_succ_right_tree(node);
      node->key = temp->key;
      node->right = deletion(node->right,temp->key);
    }
  }
  if(node){

    node->height = maa(getHeight(node->left), getHeight(node->right)) + 1;
    int balance = calcBalance(node);
    if(balance > 1 || balance < -1)
      node = balance_tree(node);
  }
  return node;
}

void preorder(AVL_node* root) {
   if(root != NULL) {
      printf("%s ",root->key);
      preorder(root->left);
      preorder(root->right);
   }
}



// I was not able to load the values from the file but this test casw which is hardcoded works
 int main(){

   AVL_node *node = NULL;
char *a;
/*	char *b = "My";
char *a = "name";\
char *d = "Is";
char *e = "aNiket";
char *f = "25";
   node = insert(node, a);
   node = insert(node, b);s
  node = insert(node, a);
   node = insert(node, d);
   node = insert(node, e);
   node = insert(node, f);*/
	
  
	FILE *fp = fopen("ffs.txt", "r");
	a =(char *)(malloc(sizeof(char)));
	fscanf(fp, "%s" , a );

	printf("%s",a);
//	node = insert(node ,a);
//	preorder(node);
//	free(a);
	fclose(fp);
/*char option;
     while(1){
        printf("1. Initialization\n");
        printf("2. Find\n");
        printf("3. Insert\n");
        printf("4. Remove\n");
        printf("5. Check Height, Size, and Total Count\n");
        printf("6. Find All (above a given frequency)\n");
        printf("7. Exit.\n");
        scanf("%c", &option);

        if (option == '1'){

            printf("\n");
        }
        else if (option == '2'){

            printf("\n");
        }
        else if (option == '3'){

            printf("\n");
        }
        else if (option == '4'){

            printf("\n");
        }
        else if (option == '5'){

        }

        else if (option == '6'){

        }
        else if (option == '7'){

            return 0;
        }
        scanf("%c", &option);

    }*/
}

