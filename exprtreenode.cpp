

#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode(){
    type = "";
    left = nullptr;
    right = nullptr;
    evaluated_value=nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt *v){
    type  = t;
    val   = new UnlimitedRational(v,new UnlimitedInt("1"));
    left  = nullptr;
    right = nullptr;
    evaluated_value=nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational *v){
    type  = t;
    val   = v;
    left  = nullptr;
    right = nullptr;
    evaluated_value=nullptr;
}

ExprTreeNode::~ExprTreeNode(){
    delete val ;
    delete evaluated_value ;
    delete left ; 
    delete right ;
}
