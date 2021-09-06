#include <stdio.h>
#include <stdlib.h>

typedef enum { RBTREE_RED, RBTREE_BLACK } color_t;
typedef int key_t;

typedef struct node_t{
    key_t key;
    color_t color;
    struct node_t *parent, *left, *right;
}node_t;

typedef struct {
  node_t *root;
} rbtree;

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(sizeof(rbtree), 1);
  return p;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
    node_t *curr = (t->root->left);
    node_t *pre_curr = NULL;
    while(curr != NULL){
        pre_curr = curr;
        if(curr->key > key){
            curr = curr->left;
            }
        else if(curr->key < key){
            curr = curr->right;
        }
        else{
            printf("key is\n");
            return curr;
        }
    }
    printf("no key\n");
    return curr;
}

void left_Rotate(rbtree* root,node_t* node){
    node_t* child = node->right;
    node->right = child->left;
    if(node->right != NULL){
        node->right->parent = node;
    }
    child->parent = node->parent;
    if(node->parent == NULL){
        (root->root->left) = child;
    }
    else if(node == node->parent->left){
        node->parent->left = child;
    }
    else{
        node->parent->right = child;
    }
    child->left = node;
    node->parent = child; 

}

void right_Rotate(rbtree* root,node_t* node){
    node_t* child = node->left;
    node->left = child->right;
    if(child->right != NULL){
        child->right->parent = node;
    }
    child->parent = node->parent;
    if(child->parent == NULL){
        (root->root->left) = child;
    }
    else if(node == node->parent->left){
        node->parent->left = child;
    }
    else{
        node->parent->right = child;
    }
    child->right = node;
    node->parent = child;
}

void Fixed(rbtree *root, node_t* node){
  while(node != root->root->left && node->parent->color == RBTREE_RED){
    node_t* temp;
    
    if(node->parent == node->parent->parent->right){
      temp = node->parent->parent->left;
    }
    else{
      temp = node->parent->parent->right;
    }
    if(temp==NULL || temp->color != RBTREE_RED){
      node_t* temp_color = (node_t *)calloc(sizeof(node_t), 1);
        //LL
      if(node->parent == node->parent->parent->left && node == node->parent->left){
    
          temp_color->color = node->parent->color;
          node->parent->color = node->parent->parent->color;
          node->parent->parent->color = temp_color->color;
          right_Rotate(root,node->parent->parent);
      }
        //LR
      else if(node->parent == node->parent->parent->left && node == node->parent->right){

          temp_color->color = node->color;
          node->color = node->parent->parent->color;
          node->parent->parent->color = temp_color->color;
          left_Rotate(root,node->parent);
          right_Rotate(root,node->parent->parent);
      }
        //RR
      else if(node->parent == node->parent->parent->right && node == node->parent->right){

          temp_color->color = node->parent->color;
          node->parent->color = node->parent->parent->color;
          node->parent->parent->color = temp_color->color;
          left_Rotate(root,node->parent->parent);
      }
        //RL
      else if(node->parent == node->parent->parent->right && node == node->parent->left){

          temp_color->color = node->color;
          node->color = node->parent->parent->color;
          node->parent->parent->color = temp_color->color;
          right_Rotate(root, node->parent);
          left_Rotate(root, node->parent->parent);
      }
      free(temp_color);
    }
    else if(temp!=NULL && temp->color == RBTREE_RED){
      node->parent->color = RBTREE_BLACK;
      temp->color = RBTREE_BLACK;
      node->parent->parent->color = RBTREE_RED;
      node = node->parent->parent;
      }
    }
  (root->root->left)->color = RBTREE_BLACK;
}

void insert_rbtree(const rbtree* t, key_t key){
//     if(t->root ==NULL){
//     rbtree *temp_t = (rbtree *)calloc(sizeof(rbtree), 1);
//     node_t *p = (node_t *)calloc(sizeof(node_t), 1);
//     temp_t = t;
//   }
    rbtree *temp_t = t;
    if(temp_t->root ==NULL){
        temp_t->root = (node_t *)calloc(sizeof(node_t), 1);
    }
  
    // root->root 노드들
    node_t *new = (node_t*)malloc(sizeof(node_t));
    new->key = key;
    new->left = new->right = new->parent = NULL;
    node_t *curr = (t->root->left);
    node_t *pre_curr = NULL;
    if(t->root->left == NULL){
        new->color = RBTREE_BLACK;
        t->root->left = new;
        curr = new;
    }
    else{
        
        while(curr != NULL){
            pre_curr = curr;
            if(new->key > curr->key){
                curr = curr->right;
            }
            else{
                curr = curr->left;
            }
        }
        new->parent = pre_curr;
        if(new->key > pre_curr->key){
            pre_curr->right = new;
        }
        else{
            pre_curr->left = new;
        }
        new->color = RBTREE_RED;
        Fixed((rbtree*) t, new);
    }
}

void print(rbtree *t, node_t* start) // 출력하는 함수
{
    node_t *curr;
    if (start == NULL){
        curr = t->root->left;
    }
    else{
        curr = start;
    }
    if(curr == NULL){
        return;
    }
    if (curr->left != NULL){
        print(t, curr->left);
    }
    printf("%d\n", curr->key);
    if (curr->right != NULL){
    print(t, curr->right);
    }
}

int main(){
    //node_t *root = NULL;
    rbtree *root = new_rbtree();

    insert_rbtree(root,10);
    insert_rbtree(root,20);
    insert_rbtree(root,30);
    insert_rbtree(root,25);
    insert_rbtree(root,5);
    insert_rbtree(root,512);
    node_t *p = rbtree_find(root, 512);
    node_t *q = rbtree_find(root, 1024);
    print(root, NULL);


}
