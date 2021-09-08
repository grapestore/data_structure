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
    while(x != t->root && x->color == RBTREE_BLACK){
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
        if((sibling->left == NULL|| sibling->left->color == RBTREE_BLACK) && (sibling->right == NULL || sibling->right->color == RBTREE_BLACK)){
            sibling->color = RBTREE_RED;
            x->parent->color = RBTREE_BLACK;
            x = x->parent;
        }
        else if((sibling->left != NULL && sibling->left->color == RBTREE_RED) && (sibling->right == NULL || sibling->right->color == RBTREE_BLACK)){
            node_t temp;
            temp.color = sibling->color;
            sibling->color = sibling->left->color;
            sibling->left->color = temp.color;
            right_Rotate(t, sibling);
            sibling = x->parent->right;
        }
        if((sibling->right != NULL && sibling->right->color == RBTREE_RED)){
            sibling->color = x->parent->color;
            x->parent->color = RBTREE_BLACK;
            sibling->right->color = RBTREE_BLACK;
            left_Rotate(t, x->parent);
            return;
        }
        t->root->color = RBTREE_BLACK;
    }
    else{
        sibling = x->parent->left;
        if(sibling->color == RBTREE_RED){
            sibling->color = RBTREE_BLACK;
            sibling->right->color = RBTREE_RED;
            right_Rotate(t, sibling->parent);
            sibling = x->parent->left;
        }
        if((sibling->left == NULL|| sibling->left->color == RBTREE_BLACK) && (sibling->right == NULL || sibling->right->color == RBTREE_BLACK)){
            sibling->color = RBTREE_RED;
            x->parent->color = RBTREE_BLACK;
            x = x->parent;
        }
        else if((sibling->left != NULL && sibling->left->color == RBTREE_RED) && (sibling->right == NULL || sibling->right->color == RBTREE_BLACK)){
            node_t temp;
            temp.color = sibling->color;
            sibling->color = sibling->left->color;
            sibling->left->color = temp.color;
            right_Rotate(t, sibling);
            sibling = x->parent->right;
        }
        if((sibling->right != NULL && sibling->right->color == RBTREE_RED)){
            sibling->color = x->parent->color;
            x->parent->color = RBTREE_BLACK;
            sibling->right->color = RBTREE_BLACK;
            right_Rotate(t, x->parent);
            return;
        }
        t->root->color = RBTREE_BLACK;
    }
    }

}

void replace_node(node_t* n, node_t* child){
    child->parent = n->parent;
    if(n->parent->left == n){
        n->parent->left = child;
    }
    else if(n->parent->right == n){
        n->parent->right = child;
    }
}


void insert_rbtree(rbtree* t, key_t key){
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
            pre_curr->right = new;
        }
        else{
            pre_curr->left = new;
        }
        new->color = RBTREE_RED;
        Fixed(t, new);
    }
}

int rbtree_erase(rbtree *t, int key) {

    // p -> 변경 p->key
    node_t* target = rbtree_find(t,key);
    node_t* closer = NULL;

    // 차일드가 둘다 있을때 right 로 간다 bst 방법중 하나
    if(target->right != NULL){
        // closer(successor)를 찾는 코드 (지워질 노드에 가장 근사값)
        closer = target->right;
        while(closer->left!=NULL){
            closer = closer->left;
        }
        // 값 복사를 통해 복잡한 링크하는 과정을 패스 할 수 있음
        target->key = closer->key;
        if(closer->right != NULL){
        // 원래는 NIL node가 존재 해야하지만 NIL노드 없이 구현하기 위해 NULL check를 한다
        // 위키디피아 참조
        // 뒤에 인자를 앞에 인자의 위치에 놓게 한다
            replace_node(closer,closer->right);
            if(closer != NULL && closer->color == RBTREE_BLACK){delete_fixed(t, closer->right);}
        }
        // 우측에서 올라오는 노드가 NULL인경우 sibiling을 찾을 수 없기 때문에
        // 최종적으로 삭제되는 노드의 위치정보를 delete fixed에 넘겨줌으로써
        // 우측 null node(NIL)의 정보를 알 수 있다.
        else{
            if(closer != NULL && closer->color == RBTREE_BLACK){delete_fixed(t, closer);}
        // 대신 이러한 경우에 최종적으로 삭제되는 노드를 NIL노드 대신 사용했기때문에
        // delete_fixed후에 연결을 끊어줌과 free 선언이 필요하다
            if(closer->parent->left == closer){closer->parent->left = NULL;}
            else if(closer->parent->right == closer){closer->parent->right = NULL;}
        }
        free(closer);
        return 0;
    }
    // child가 left 하나만 있는 경우
    else if(target->left != NULL){
        if(target->left != NULL){
            closer = target->left;
            target->key = closer->key;
            replace_node(target, closer);
            if(closer != NULL && closer->color == RBTREE_BLACK){delete_fixed(t, closer);}
        }
        free(closer);
        return 0;
    }
    // child가 없는 경우
    else{
        if(target->parent == NULL){
            t->root = NULL;
        }
        else{
        // child가 없는 경우에도 bst와 달리 색 체크를 해주어야 하기 때문에
        // 최종적으로 삭제되는 노드가 블랙일 경우 sibling check를 통해
        // 기존과 동일하게 진행 되어야 한다.
            if(target->color == RBTREE_BLACK){delete_fixed(t, target);}
            if(target == target->parent->right){target->parent->right = NULL;}
            else{target->parent->left = NULL;}
        }
        free(target);
        return 0;
    }
}

void print(rbtree *t, node_t* start) // 출력하는 함수
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
    while(curr->left != NULL){
        curr = curr->left;
    }
    printf("%d\n",curr->key);
}

void max(rbtree *t){
    node_t *curr = (t->root);
    while(curr->right != NULL){
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
    // node_t *p = rbtree_find(root, 40);
    // node_t *q = rbtree_find(root, 1024);
    // printf("\n");
    rbtree_erase(root, 30);
    rbtree_erase(root, 25);
    min(root);
    max(root);
    // print(root, NIL);

    //mac os 시스템 리크 체크함수
    system("leaks a.out");

}
