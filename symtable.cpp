/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

SymbolTable::SymbolTable(){
    size = 0 ;
    root = nullptr;
}

void deleter(SymEntry* cur){
    if(cur==nullptr){
        return;
    }
    deleter(cur->left);
    deleter(cur->right);
    delete cur;
}

SymbolTable::~SymbolTable(){
    deleter(root);
}

void SymbolTable::insert(string k, UnlimitedRational *v){
    if(root==nullptr){
        root = new SymEntry(k,v);
        return;
    }
    SymEntry* temp = root ;
    SymEntry* prev = temp;
    while(temp!=nullptr){
        prev=temp;
        if(temp->key > k){
            temp = temp->left;
        }
        else if(temp-> key < k){
            temp = temp->right;
        }
    }
    if (prev->key>k) prev->left = new SymEntry(k,v);
    else prev->right = new SymEntry(k,v);
}

SymEntry* destroyer(SymEntry* cur,string k){
    if(cur==nullptr){
        return nullptr;
    }
    if(k < cur->key){
        cur->left = destroyer(cur->left,k);
    }
    else if(k > cur->key ){
        cur->right = destroyer(cur->right,k);
    }
    else{
        if(cur->left==nullptr && cur->right==nullptr){
            delete cur;return nullptr;
        }
        else if(cur->left==nullptr){
            SymEntry* temp  = cur->right;
            delete cur;
            return temp;
        }
        else if(cur->right==nullptr){
            SymEntry* temp = cur->left;
            delete cur;
            return temp;
        }
        SymEntry* temp = cur->right;
        while(temp->left!=nullptr){
            temp = temp->left;
        }
        cur->key = temp->key;
        cur->val = temp->val;
        cur->right = destroyer(cur->right,temp->key);
    }
    return cur;
}

void SymbolTable::remove(string k){ 
    root = destroyer(root,k);
}

UnlimitedRational *SymbolTable::search(string k){
   SymEntry* temp = root; 
   while(temp!=nullptr){
        if(temp->key > k){
            temp = temp->left;
        }
        else if(temp->key < k){
            temp = temp->right;
        }
        else{
            return temp->val;
        }
   }
   return nullptr;
}

int SymbolTable::get_size()
{
    return size;
}

SymEntry *SymbolTable::get_root()
{
    return root;
}
