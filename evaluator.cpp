/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

Evaluator::Evaluator(){
    symtable =  new SymbolTable();
}

Evaluator::~Evaluator(){
    delete symtable;
}

bool isInteger(string str) {
    int n =str.size();
    if(n==0){
        return false;
    }
    for (int i=0 ;i<n;i++) {
        if (str[i]=='1' || str[i]=='2' || str[i]=='3' || str[i]=='4' || str[i]=='5' || str[i]=='6' || str[i]=='7' || str[i]=='8' || str[i]=='9' || str[i]=='0' || str[i]=='-') {
            continue;
        }
        else{
            return false;
        }
    }
    return true;
}

void Evaluator::parse(vector<string> code){
    int n = code.size();
    UnlimitedInt* one = new UnlimitedInt("1");
    ExprTreeNode* root = new ExprTreeNode();
    root->id = ":=";
    root->left = new ExprTreeNode();
    root->left->type = "VAR";
    root->left->id =  code[0];
    vector<ExprTreeNode*> stacker; 
    for(int i(2);i<n;i++){
        if(code[i]=="("){
            continue;
        }
        else if(code[i]=="+" || code[i]=="-" || code[i]=="*" || code[i]=="/" || code[i]=="%"){
            ExprTreeNode* cur = new ExprTreeNode(code[i],one);
            if(code[i]=="+"){
                cur->type = "ADD";
            }
            else if(code[i]=="-"){
                cur->type = "SUB";
            }
            else if(code[i]=="*"){
                cur->type = "MUL";
            }
            else if(code[i]=="/"){
                cur->type = "DIV";
            }
            else if(code[i]=="%"){
                cur->type = "MOD";
            }
            stacker.push_back(cur);
        }
        else if(isInteger(code[i])){
            UnlimitedInt* ob = new UnlimitedInt(code[i]);
            ExprTreeNode* cur = new ExprTreeNode(code[i],ob);
            cur->type = "VAL";
            stacker.push_back(cur);
        }
        else if(code[i]==")"){
            ExprTreeNode* a = stacker.back();
            stacker.pop_back();
            ExprTreeNode* b = stacker.back();
            stacker.pop_back();
            ExprTreeNode* c = stacker.back();
            stacker.pop_back();
            b->left = c;
            b->right = a;
            stacker.push_back(b);
        }
        else{
            ExprTreeNode* cur = new ExprTreeNode(code[i],one);
            cur->type = "VAR";
            cur->id = code[i];
            stacker.push_back(cur);
        }
    }
    root->right = stacker.back();
    stacker.pop_back();
    expr_trees.push_back(root);
}

UnlimitedRational* indiv(ExprTreeNode* root,SymbolTable* symtable){
    if(root->type=="VAL"){
        if(root->evaluated_value==nullptr){
            root->evaluated_value = root->val;
        }
        return root->val;
    }
    else if(root->type=="VAR"){
        if(root->evaluated_value==nullptr){
            root->evaluated_value = symtable->search(root->id);
        }
        return root->evaluated_value;
    }
    else if(root->type=="ADD"){
        if(root->evaluated_value==nullptr){
            root->evaluated_value = UnlimitedRational::add(indiv(root->left,symtable),indiv(root->right,symtable));
        }
        return root->evaluated_value;
    }
    else if(root->type=="SUB"){
        if(root->evaluated_value==nullptr){
            root->evaluated_value = UnlimitedRational::sub(indiv(root->left,symtable),indiv(root->right,symtable));
        }
        return root->evaluated_value;
    }
    else if(root->type=="MUL"){
        if(root->evaluated_value==nullptr){
            root->evaluated_value = UnlimitedRational::mul(indiv(root->left,symtable),indiv(root->right,symtable));
        }
        return root->evaluated_value;
    }
    else if(root->type=="DIV"){
        if(root->evaluated_value==nullptr){
            root->evaluated_value = UnlimitedRational::div(indiv(root->left,symtable),indiv(root->right,symtable));
        }
        return root->evaluated_value;
    }
    else if(root->type=="MOD"){
        if(root->evaluated_value==nullptr){
            UnlimitedInt* obj = new UnlimitedInt("1");
            root->evaluated_value = new UnlimitedRational(UnlimitedInt::mod(indiv(root->left,symtable)->get_p(),indiv(root->right,symtable)->get_p()),obj);
        }
        return root->evaluated_value;
    }
    else{
        UnlimitedRational* ob = new UnlimitedRational();
        return ob;
    }
}

void Build(ExprTreeNode* root,SymbolTable* symtable){
    if(root==nullptr){
        return;
    }
    if(root->type=="VAR"){
        symtable->insert(root->id,root->evaluated_value);
    }
    else if(root->type=="ADD" || root->type=="SUB" || root->type=="MUL" || root->type=="DIV" || root->type=="MOD"){
        symtable->insert("ans",root->evaluated_value);
    }
    if(root->left!=nullptr){
        Build(root->left,symtable);
    }
    if(root->right!=nullptr){
        Build(root->right,symtable);
    }
}

void Evaluator::eval(){
    ExprTreeNode* cur = expr_trees[expr_trees.size()-1];
    UnlimitedRational* ans = indiv(cur->right,symtable);
    cur->evaluated_value = ans;   
    cur->left->evaluated_value = ans;
    symtable->insert(cur->left->id,cur->left->evaluated_value);
}
