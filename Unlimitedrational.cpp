/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"

UnlimitedInt* gcd(UnlimitedInt *i1, UnlimitedInt *i2){
    if(i1->to_string()=="0"){
        return i2;
    }
    return gcd(UnlimitedInt::mod(i2,i1),i1);
}  

UnlimitedRational::UnlimitedRational(){
    p = nullptr;
    q = nullptr;     
}

UnlimitedRational::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den){
    if(den->to_string()=="0"){
        p = new UnlimitedInt("0");
        q = new UnlimitedInt("0");
    }
    else{
        UnlimitedInt* g = gcd(num,den);
        p = UnlimitedInt::div(num,g);
        q = UnlimitedInt::div(den,g);
    }
}

UnlimitedRational::~UnlimitedRational(){
    delete p ;
    delete q ;
}

UnlimitedInt *UnlimitedRational::get_p(){
    return p;
}

UnlimitedInt *UnlimitedRational::get_q(){
    return q;
}

string UnlimitedRational::get_p_str(){
    return p->to_string();
}

string UnlimitedRational::get_q_str(){
    return q->to_string();
}

string UnlimitedRational::get_frac_str(){
    string cur = p->to_string() + "/" + q->to_string() ;
    return cur;
}

UnlimitedRational* reduce(UnlimitedRational* i){
    UnlimitedInt* g = gcd(i->get_p(),i->get_q());
    UnlimitedInt* p = UnlimitedInt::div(i->get_p(),g);
    UnlimitedInt* q = UnlimitedInt::div(i->get_q(),g);
    return new UnlimitedRational(p,q);
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational *i1, UnlimitedRational *i2){
    UnlimitedInt* p1 = i1->p;
    UnlimitedInt* p2 = i2->p;
    UnlimitedInt* q1 = i1->q;
    UnlimitedInt* q2 = i2->q;
    UnlimitedInt* p = UnlimitedInt::add(UnlimitedInt::mul(p1,q2),UnlimitedInt::mul(p2,q1));
    UnlimitedInt* q = UnlimitedInt::mul(q1,q2);
    return new UnlimitedRational(p,q);
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt* p1 = i1->p;
    UnlimitedInt* p2 = i2->p;
    UnlimitedInt* q1 = i1->q;
    UnlimitedInt* q2 = i2->q;
    UnlimitedInt* p = UnlimitedInt::sub(UnlimitedInt::mul(p1,q2),UnlimitedInt::mul(p2,q1));
    UnlimitedInt* q = UnlimitedInt::mul(q1,q2);
    return new UnlimitedRational(p,q);
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt* p1 = i1->p;
    UnlimitedInt* p2 = i2->p;
    UnlimitedInt* q1 = i1->q;
    UnlimitedInt* q2 = i2->q;
    UnlimitedInt* p = UnlimitedInt::mul(p1,p2);
    UnlimitedInt* q = UnlimitedInt::mul(q1,q2);
    return new UnlimitedRational(p,q);
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt* p1 = i1->p;
    UnlimitedInt* p2 = i2->p;
    UnlimitedInt* q1 = i1->q;
    UnlimitedInt* q2 = i2->q;
    UnlimitedInt* p = UnlimitedInt::mul(p1,q2);
    UnlimitedInt* q = UnlimitedInt::mul(q1,p2);
    return new UnlimitedRational(p,q);
}
