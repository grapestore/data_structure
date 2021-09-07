#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(sizeof(rbtree), 1);
  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
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

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // root->root 노드들
  node_t *new = (node_t*)malloc(sizeof(node_t));
  new->key = key;
  new->left = new->right = new->parent = NULL;
  node_t *curr = (t->root);
  node_t *pre_curr = NULL;
  if(t->root == NULL){
      new->color = RBTREE_BLACK;
      t->root = new;
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
      pre_curr->right = new;}
    else{
      pre_curr->left = new;}
    new->color = RBTREE_RED;
    Fixed(t, new);
  }
  return curr;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
    node_t *curr = (t->root);
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
            return curr;
        }
    }
    return curr;
}

node_t *rbtree_min(const rbtree *t) {
  node_t *curr = (t->root);
  while(curr->left != NULL){
      curr = curr->left;
  }
  return curr;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  node_t *curr = (t->root);
  while(curr->right != NULL){
      curr = curr->right;
  }
  return curr;
}

void delete_fixed(rbtree* t, node_t* x, char sibiling){
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

void delete_fixed_two(rbtree* t, node_t* x, int uncle_direction){
    //uncle_direction left = 0, right =1
    node_t* sibling = NULL;
    if(x->color == RBTREE_RED){
        x->color = RBTREE_BLACK;
        return;
    }
    if(uncle_direction == 1){
        sibling = x->right;
        if(sibling->color == RBTREE_RED){
            sibling->color = RBTREE_BLACK;
            sibling->left->color = RBTREE_RED;
            left_Rotate(t, sibling->parent);
            sibling = x->right;
        }
        if(sibling->left->color ==RBTREE_BLACK && sibling->right->color == RBTREE_BLACK){
            sibling->color = RBTREE_RED;
            x->color = RBTREE_BLACK;
            return;
        }
        else if(sibling->left->color == RBTREE_RED && sibling->right->color == RBTREE_BLACK){
            node_t temp;
            temp.color = sibling->color;
            sibling->color = sibling->left->color;
            sibling->left->color = temp.color;
            right_Rotate(t, sibling);
            sibling = x->right;
        }
        if(sibling->right->color == RBTREE_RED){
            sibling->color = x->color;
            x->color = RBTREE_BLACK;
            sibling->right->color = RBTREE_BLACK;
            left_Rotate(t, x);
        }
        t->root->color = RBTREE_BLACK;
        return;
    }
    else{
        sibling = x->left;
        if(sibling->color == RBTREE_RED){
            sibling->color = RBTREE_BLACK;
            sibling->right->color = RBTREE_RED;
            right_Rotate(t, sibling->parent);
            sibling = x->left;
        }
        if(sibling->left->color ==RBTREE_BLACK && sibling->right->color == RBTREE_BLACK){
            sibling->color = RBTREE_RED;
            x->color = RBTREE_BLACK;
            return;
        }
        else if(sibling->left->color == RBTREE_RED && sibling->right->color == RBTREE_BLACK){
            node_t temp;
            temp.color = sibling->color;
            sibling->color = sibling->left->color;
            sibling->left->color = temp.color;
            right_Rotate(t, sibling);
            sibling = x->right;
        }
        if(sibling->right->color == RBTREE_RED){
            sibling->color = x->color;
            x->color = RBTREE_BLACK;
            sibling->right->color = RBTREE_BLACK;
            right_Rotate(t, x);
        }
        t->root->color = RBTREE_BLACK;
        return;
    }

}

int rbtree_erase(rbtree *t, node_t *p) {

    // p -> 변경 p->key
    node_t* target = rbtree_find(t,p->key);
    node_t* closer = NULL;

    // closer 자리에 올라올 애
    node_t* fixed_x = NULL;
    int uncle_direction = 0;
    // 차일드가 둘다 있을때
    if(target->left != NULL && target->right != NULL){
        // closer(successor)를 찾는 코드
        closer = target->right;
        int count = 0;
        while(closer->left!=NULL){
            closer = closer->left;
            count ++;
        }
        target->key = closer->key;
        fixed_x = closer->parent;
        //left = 0, right =1
        if(count == 0){
            uncle_direction = 0;
        }
        else{
            uncle_direction = 1;
        }
        fixed_x = closer->right;
        fixed_x->parent = closer->parent;
        if(closer == closer->parent->right){closer->parent->right = closer->right;}
        else if(closer == closer->parent->left){closer->parent->left = closer->right;}
        if(closer != NULL && closer->color == RBTREE_BLACK){delete_fixed_two(t, fixed_x, uncle_direction);}
    }
    // child가 left 하나만 있는 경우
    else if(target->left != NULL || target->right != NULL){
        if(target->left != NULL){
            closer = target->left;
            target->key = closer->key;
            fixed_x = closer;
            fixed_x->parent = closer->parent;
            if(closer == closer->parent->right){closer->parent->right = closer->right;}
            else if(closer == closer->parent->left){closer->parent->left = closer->right;}
            if(closer != NULL && closer->color == RBTREE_BLACK){delete_fixed(t, fixed_x, uncle_direction);}
        }
    }
    // child가 없는 경우
    else{
      if(target->parent == NULL){
        t->root = NULL;
        free(target);
        }
        else{
          if(target == target->parent->right){target->parent->right = NULL;}
          else{target->parent->left = NULL;}  
        }
    }
  free(closer);
  return 0;
}
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
