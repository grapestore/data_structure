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
  node_t *t = (node_t *)calloc(sizeof(node_t), 1);
  t->left = NULL;
  p->root = t;
  return p;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  printf("check insert \n");
  // TODO: implement find
  return t->root;
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

void Fixed(rbtree* root, node_t* node){

    while(node != root->root->left && node->parent->color == RBTREE_RED){
        node_t* temp;
        if(node->parent == node->parent->parent->right){
            temp = node->parent->parent->left;
        }
        else{
            temp = node->parent->parent->right;
        }

        if(temp==NULL || temp->color != RBTREE_RED){
            //LL
            if(node->parent == node->parent->parent->left && node == node->parent->left){
                color_t* te = node->parent->color;
                node->parent->color = node->parent->parent->color;
                node->parent->parent->color = te;
                right_Rotate(root,node->parent->parent);
            }
            //LR
            else if(node->parent == node->parent->parent->left && node == node->parent->right){
                color_t* te = node->color;
                node->color = node->parent->parent->color;
                node->parent->parent->color = te;
                left_Rotate(root,node->parent);
                right_Rotate(root,node->parent->parent);
            }
            //RR
            else if(node->parent == node->parent->parent->right && node == node->parent->right){
                color_t* te = node->parent->color;
                node->parent->color = node->parent->parent->color;
                node->parent->parent->color = te;
                left_Rotate(root,node->parent->parent);
            }
            //RL
            else if(node->parent == node->parent->parent->right && node == node->parent->left){
                color_t* te = node->color;
                node->color = node->parent->parent->color;
                node->parent->parent->color = te;
                right_Rotate(root, node->parent);
                left_Rotate(root, node->parent->parent);
            }
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

    // root->root 노드들
    node_t *new = (node_t*)malloc(sizeof(node_t));
    new->key = key;
    new->left = new->right = new->parent = NULL;
    if(t->root->left == NULL){
        new->color = RBTREE_BLACK;
        t->root->left = new;
    }
    else{
        node_t *curr = (t->root->left);
        node_t *pre_curr = NULL;
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

int main(){
    //node_t *root = NULL;
    rbtree *root = new_rbtree();

    insert_rbtree((rbtree *)root,10);
    insert_rbtree(root,20);
    insert_rbtree(root,30);
    insert_rbtree(root,25);
    insert_rbtree(root,5);


}
