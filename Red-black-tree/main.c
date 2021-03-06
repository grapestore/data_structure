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

node_t _NIL = {
    .color = RBTREE_BLACK,
    .key = 0,
    .parent = NULL,
    .left = NULL,
    .right = NULL
};
node_t *NIL = &_NIL;

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(sizeof(rbtree), 1);
  return p;
}

node_t *rbtree_find(rbtree *t, const key_t key) {
    node_t *curr = (t->root);
    node_t *pre_curr = NULL;
    while(curr != NIL){
        pre_curr = curr;
        if(curr->key > key){
            curr = curr->left;
            }
        else if(curr->key < key){
            curr = curr->right;
        }
        else{
            return curr;
        }
    }
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
        (root->root) = child;
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
        (root->root) = child;
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
  while(node != root->root && node->parent->color == RBTREE_RED){
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
          right_Rotate(root,node->parent);
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
          left_Rotate(root, node->parent);
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
  (root->root)->color = RBTREE_BLACK;
}

void delete_fixed(rbtree* t, node_t* x){
    node_t* sibling = NULL;
    if(x->color == RBTREE_RED){
        x->color = RBTREE_BLACK;
        return;
    }
    if(x == x->parent->left){
        sibling = x->parent->right;
        if(sibling->color == RBTREE_RED){
            sibling->color = RBTREE_BLACK;
            sibling->left->color = RBTREE_RED;
            left_Rotate(t, sibling->parent);
            sibling = x->parent->right;
        }
        if(sibling->left->color ==RBTREE_BLACK && sibling->right->color == RBTREE_BLACK){
            sibling->color = RBTREE_RED;
            x->parent->color = RBTREE_BLACK;
            return;
        }
        else if(sibling->left->color == RBTREE_RED && sibling->right->color == RBTREE_BLACK){
            node_t temp;
            temp.color = sibling->color;
            sibling->color = sibling->left->color;
            sibling->left->color = temp.color;
            right_Rotate(t, sibling);
            sibling = x->parent->right;
        }
        if(sibling->right->color == RBTREE_RED){
            sibling->color = x->parent->color;
            x->parent->color = RBTREE_BLACK;
            sibling->right->color = RBTREE_BLACK;
            left_Rotate(t, x->parent);
        }
        t->root->color = RBTREE_BLACK;
        return;
    }
    else{
        sibling = x->parent->left;
        if(sibling->color == RBTREE_RED){
            sibling->color = RBTREE_BLACK;
            sibling->right->color = RBTREE_RED;
            right_Rotate(t, sibling->parent);
            sibling = x->parent->left;
        }
        if(sibling->left->color ==RBTREE_BLACK && sibling->right->color == RBTREE_BLACK){
            sibling->color = RBTREE_RED;
            x->parent->color = RBTREE_BLACK;
            return;
        }
        else if(sibling->left->color == RBTREE_RED && sibling->right->color == RBTREE_BLACK){
            node_t temp;
            temp.color = sibling->color;
            sibling->color = sibling->left->color;
            sibling->left->color = temp.color;
            right_Rotate(t, sibling);
            sibling = x->parent->right;
        }
        if(sibling->right->color == RBTREE_RED){
            sibling->color = x->parent->color;
            x->parent->color = RBTREE_BLACK;
            sibling->right->color = RBTREE_BLACK;
            right_Rotate(t, x->parent);
        }
        t->root->color = RBTREE_BLACK;
        return;
    }

}

void insert_rbtree(rbtree* t, key_t key){

    // root->root ?????????
    node_t *new = (node_t*)malloc(sizeof(node_t));
    new->key = key;
    new->left = new->right = new->parent = NULL;
    node_t *curr = (t->root);
    node_t *pre_curr = NULL;
    if(t->root == NULL){
        new->color = RBTREE_BLACK;
        t->root = new;
        curr = new;
        new->right = NIL;
        new->left = NIL;
    }
    else{
        while(curr != NIL){
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
        new->right = NIL;
        new->left = NIL;
        Fixed(t, new);
    }
}

void rbtree_erase(rbtree *t, key_t key) {

    // p -> ?????? p->key
    node_t* target = rbtree_find(t,key);
    node_t* closer = NULL;

    // closer ????????? ????????? ???
    node_t* fixed_x = NULL;
    // ???????????? ?????? ?????????
    if(target->left != NIL && target->right != NIL){
        // closer(successor)??? ?????? ??????
        closer = target->right;
        int count = 0;
        while(closer->left!=NIL){
            closer = closer->left;
            count ++;
        }
        target->key = closer->key;
        fixed_x = closer->right;
        fixed_x->parent = closer->parent;
        if(closer == closer->parent->right){closer->parent->right = closer->right;}
        else if(closer == closer->parent->left){closer->parent->left = closer->right;}
    }
    // child??? left ????????? ?????? ??????
    else if(target->left != NIL || target->right != NIL){
        if(target->left != NIL){
            closer = target->left;
            target->key = closer->key;
            fixed_x = closer;
            fixed_x->parent = closer->parent;
            if(closer == closer->parent->right){closer->parent->right = closer->right;}
            else if(closer == closer->parent->left){closer->parent->left = closer->right;}
        }
    }
    // child??? ?????? ??????
    else{
        if(target == target->parent->right){target->parent->right = NIL;}
        else{target->parent->left = NIL;}
    }
    if(closer != NULL && closer->color == RBTREE_BLACK){delete_fixed(t, fixed_x);}
    free(closer);
}

void print(rbtree *t, node_t* start) // ???????????? ??????
{
    node_t *curr;
    if (start == NIL){
        curr = t->root;
    }
    else{
        curr = start;
    }
    if(curr == NIL){
        return;
    }
    if (curr->left != NIL){
        print(t, curr->left);
    }
    printf("%d ", curr->key);
    if (curr->right != NIL){
    print(t, curr->right);
    }
}

void min(rbtree *t){
    node_t *curr = (t->root);
    while(curr->left != NIL){
        curr = curr->left;
    }
    printf("%d\n",curr->key);
}

void max(rbtree *t){
    node_t *curr = (t->root);
    while(curr->right != NIL){
        curr = curr->right;
    }
    printf("%d\n",curr->key);
}

int main(){
    //node_t *root = NULL;
    rbtree *root = new_rbtree();

    insert_rbtree(root,30);
    insert_rbtree(root,10);
    insert_rbtree(root,25);
    insert_rbtree(root,55);
    insert_rbtree(root,40);
    insert_rbtree(root,60);
    node_t *p = rbtree_find(root, 40);
    node_t *q = rbtree_find(root, 1024);
    printf("\n");
    rbtree_erase(root, 30);
    rbtree_erase(root, 25);
    min(root);
    max(root);
    // print(root, NIL);
}
