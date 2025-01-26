/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
#include<iostream>
using namespace std;

int get_digit(int i){
    int digit = 0;
    while(i>0){
        i = i/10;
        digit++;
    }
    return digit;
}

string reverse(string s){
    if(s.size()<=1){
        return s;
    }
    string temp = "";
    for(int i(s.size()-1);i>=0;i--){
        temp+=s[i];
    }
    return temp;
}


UnlimitedInt::UnlimitedInt(){
   size = 0;
   sign = 1;
   capacity = 0;
   unlimited_int = nullptr;
}

UnlimitedInt::UnlimitedInt(string s){
    size = (s[0] == '-' ? s.size()-1 : s.size());
    sign = (s[0] == '-' ? -1 : 1);
    capacity = size;
    unlimited_int = new int[capacity];
    if(sign==-1){
        for(int i=1; i<size+1; i++){
            unlimited_int[i-1] = s[i]-'0';
        }
    }
    else{
        for(int i=0; i<size; i++){
            unlimited_int[i] = s[i]-'0';
        }
    }
}

UnlimitedInt::UnlimitedInt(int x){
    size = (x>-1 ? get_digit(x) : get_digit(-x));
    sign = (x>-1 ? 1 : -1);
    capacity = get_digit(x);
    unlimited_int = new int[capacity];
    int y=(sign==-1 ? -x : x);
    for(int i=0; i<size; i++){
        unlimited_int[i] = (y%10)+'0';y/=10;
    }
}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    size = sz;
    sign = sgn;
    capacity = cap;
    unlimited_int = new int[capacity];
    for(int i=0; i<size; i++){
        unlimited_int[i] = ulimited_int[i];
    }
}

UnlimitedInt::~UnlimitedInt(){
    delete[] unlimited_int;
}

int UnlimitedInt ::get_size(){
    return size;
}

int* UnlimitedInt::get_array(){
    return unlimited_int;
}

int UnlimitedInt::get_sign(){
    return sign;
}

int UnlimitedInt::get_capacity(){
    return capacity;
}

bool Compare(UnlimitedInt* i1,UnlimitedInt* i2){
    string s_1 = i1->to_string();
    string s_2 = i2->to_string();
    int sign_1 = i1->get_sign();
    int sign_2 = i2->get_sign();
    int l1 = s_1.size();
    int l2 = s_2.size();
    if(sign_1 < sign_2){
        return false;
    }
    else if(sign_1 > sign_2){
        return true;
    }
    else{
        if(sign_1 == 1){
            if(l1 > l2){
                return true;
            }
            else if(l1 < l2){
                return false;
            }
            else{
                for(int i(0);i<l1;++i){
                    if(s_1[i] > s_2[i]){
                        return true;
                    }
                    else if(s_1[i] < s_2[i]){
                        return false;
                    }
                }
                return true;
            }
        }
        else{
            if(l1 > l2){
                return false;
            }
            else if(l1 < l2){
                return true;
            }
            else{
                for(int i(0);i<l1;++i){
                    if(s_1[i] > s_2[i]){
                        return false;
                    }
                    else if(s_1[i] < s_2[i]){
                        return true;
                    }
                }
                return true;
            }
        }
    }
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
    int sign_1 = i1->get_sign();
    int sign_2 = i2->get_sign(); 
    if(sign_1==1 && sign_2==1){
        string s1 = i1->to_string();
        string s2 = i2->to_string();
        string sum = "";
        if(i1->size  > i2->size ){
            swap(s1,s2);
        }
        int l1  =s1.size();
        int l2 = s2.size();
        s1 = reverse(s1);
        s2 = reverse(s2);
        int carry = 0;
        for(int i(0);i<l1;++i){
            int temp = (s1[i]-'0') + (s2[i]-'0') + carry ;
            sum+=(temp%10 + '0');
            carry  = temp/10;
        }
        for(int i(l1);i<l2;++i){
            int temp=(s2[i]-'0')+carry;
            sum+=(temp%10 + '0');
            carry=temp/10;
        }
        if(carry){
            sum+=(carry+'0');
        }
        sum = reverse(sum); 
        UnlimitedInt* obj = new UnlimitedInt(sum);
        return obj;
    }
    else if(sign_1==-1 && sign_2==-1){
        string s1 = i1->to_string();s1.erase(s1.begin());
        string s2 = i2->to_string();s2.erase(s2.begin());
        string sum = "";
        if(i1->size  > i2->size ){
            swap(s1,s2);
        }
        int l1  =s1.size();
        int l2 = s2.size();
        s1 = reverse(s1);
        s2 =reverse(s2);
        int carry = 0;
        for(int i(0);i<l1;++i){
            int temp = (s1[i]-'0') + (s2[i]-'0') + carry ;
            sum+=(temp%10 + '0');
            carry  = temp/10;
        }
        for(int i(l1);i<l2;++i){
            int temp=(s2[i]-'0')+carry;
            sum+=(temp%10 + '0');
            carry=temp/10;
        }  
        if(carry){
            sum+=(carry+'0');
        }
        sum+='-';
        sum = reverse(sum);
        UnlimitedInt* obj = new UnlimitedInt(sum);
        return obj;
    }
    else if(sign_1==1 && sign_2==-1){
        string cur = i2->to_string();cur.erase(cur.begin());
        UnlimitedInt* o =new UnlimitedInt(cur);
        return sub(i1,o);
    }
    else if(sign_1==-1 && sign_2==1){
        string cur = i1->to_string();cur.erase(cur.begin());
        UnlimitedInt* o =new UnlimitedInt(cur);
        return sub(i2,o);
    }
    return nullptr;
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    int sign_1 = i1->get_sign();
    int sign_2 = i2->get_sign(); 
    if(sign_1==1 && sign_2==1){
        string s1 = i1->to_string();
        string s2 = i2->to_string();
        bool ok = Compare(i1,i2);
        if(!ok){
            swap(s1,s2);
        }
        string diff = "";
        int l1  =s1.size();
        int l2 = s2.size();
        s1 = reverse(s1);
        s2 = reverse(s2);
        int carry = 0;
        for(int i(0);i<l2;++i){
            int temp = (s1[i]-'0') - (s2[i]-'0') - carry ;
            if(temp <0){temp+=10;carry=1;}
            else{carry=0;}
            diff+=(temp + '0');
        }
        for(int i(l2);i<l1;++i){
            int temp=(s1[i]-'0') - carry;
            if(temp < 0){temp+=10;carry=1;}
            else{carry=0;}
            diff+=(temp + '0');
        }
        while(diff[diff.size()-1]=='0' && diff.size()>1){
            diff.pop_back();
        }
        if(!ok){
            diff+='-';
        }
        diff =reverse(diff);
        UnlimitedInt* obj = new UnlimitedInt(diff);
        return obj;
    }
    else if(sign_1==-1 && sign_2==-1){
        string s1 = i1->to_string();s1.erase(s1.begin());
        string s2 = i2->to_string();s2.erase(s2.begin());
        UnlimitedInt* o1 =new UnlimitedInt(s1);
        UnlimitedInt* o2 =new UnlimitedInt(s2);
        return sub(o2,o1);
    }
    else if(sign_1==-1 && sign_2==1){
        string s1 = i1->to_string();s1.erase(s1.begin());
        string s2 = i2->to_string();
        string diff = "";
        if(i1->size  > i2->size ){
            swap(s1,s2);
        }
        int l1  =s1.size();
        int l2 = s2.size();
        s1 =reverse(s1);
        s2= reverse(s2);
        int carry = 0;
        for(int i(0);i<l1;++i){
            int temp = (s1[i]-'0') + (s2[i]-'0') + carry ;
            diff+=(temp%10 + '0');
            carry  = temp/10;
        }
        for(int i(l1);i<l2;++i){
            int temp=(s2[i]-'0')+carry;
            diff+=(temp%10 + '0');
            carry=temp/10;
        }  
        if(carry){
            diff+=(carry+'0');
        }
        diff+='-';
        diff = reverse(diff);
        UnlimitedInt* obj = new UnlimitedInt(diff);
        return obj;
    }
    else if(sign_1==1 && sign_2==-1){
        string s1 = i1->to_string();
        string s2 = i2->to_string();s2.erase(s2.begin());
        string diff = "";
        if(i1->size  > i2->size ){
            swap(s1,s2);
        }
        int l1  =s1.size();
        int l2 = s2.size();
        s1 = reverse(s1);
        s2=  reverse(s2);
        int carry = 0;
        for(int i(0);i<l1;++i){
            int temp = (s1[i]-'0') + (s2[i]-'0') + carry ;
            diff+=(temp%10 + '0');
            carry  = temp/10;
        }
        for(int i(l1);i<l2;++i){
            int temp=(s2[i]-'0')+carry;
            diff+=(temp%10 + '0');
            carry=temp/10;
        }
        if(carry){
            diff+=(carry+'0');
        }
        diff = reverse(diff); 
        UnlimitedInt* obj = new UnlimitedInt(diff);
        return obj;
    }
    return nullptr;
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2){
    int sign_1 = i1->get_sign();
    int sign_2 = i2->get_sign();
    string s1 = i1->to_string();if(sign_1==-1){s1.erase(s1.begin());}
    string s2 = i2->to_string();if(sign_2==-1){s2.erase(s2.begin());}
    string mul = "";
    int l1  =s1.size();
    int l2 = s2.size();
    s1 = reverse(s1);
    s2 = reverse(s2);
    for(int i(0);i<(l1+l2);++i){
        mul+='0';
    }
    for(int i(0);i<l1;++i){
        int carry=0;
        for(int j(0);j<l2;++j){
            int temp = (s1[i]-'0') * (s2[j]-'0') + carry  + (mul[i+j]-'0');
            carry  = temp/10;
            mul[i+j]=(temp%10 + '0');
        }
        mul[i+l2] = carry+'0';
    }
    while(mul[mul.size()-1]=='0' && mul.size()>1){
        mul.pop_back();
    }
    mul = reverse(mul);
    if(sign_1*sign_2==-1 && mul!="0"){
        mul='-'+mul;
    }
    UnlimitedInt* obj = new UnlimitedInt(mul);
    return obj;
}

string digit_mul(string x,int n){
    if(n==0){
        return "0";
    }
    string mul = "";
    int l = x.size();
    x= reverse(x);
    int carry = 0;
    for(int i(0);i<l;++i){
        int temp = (x[i]-'0') * n + carry;
        mul+=(temp%10 + '0');
        carry = temp/10;
    }
    if(carry){
        mul+=(carry+'0');
    }
    mul  =reverse(mul);
    return mul;
}

bool string_compare(string a,string b){
    int l1  =a.size();
    int l2 = b.size();
    if(a==b){
        return true;
    }

    if(l1 > l2){
        return true;
    }
    else if(l1 < l2){
        return false;
    }
    else{
        for(int i(0);i<l1;++i){
            if(a[i] > b[i]){
                return true;
            } 
            else if(a[i] < b[i]){
                return false;
            }
        }
        return true;
    }
}

string string_sub(string s1,string s2){

    if(s1==s2){
        return "0";
    }
    bool ok = string_compare(s1,s2);
    if(!ok){
        swap(s1,s2);
    }
    while(s1[0]=='0' && s1.size()>1){
        s1.erase(s1.begin());
    }
    while(s2[0]=='0' && s2.size()>1){
        s2.erase(s2.begin());
    }
    string diff = "";
    int l1  =s1.size();
    int l2 = s2.size();
    s1 = reverse(s1);
    s2 = reverse(s2);
    int carry = 0;
    for(int i(0);i<l2;++i){
        int temp = (s1[i]-'0') - (s2[i]-'0') - carry ;
        if(temp <0){temp+=10;carry=1;}
        else{carry=0;}
        diff+=(temp + '0');
    }
    for(int i(l2);i<l1;++i){
        int temp=(s1[i]-'0') - carry;
        if(temp < 0){temp+=10;carry=1;}
        else{carry=0;}
        diff+=(temp + '0');
    }
    while(diff[diff.size()-1]=='0' && diff.size()>1){
        diff.pop_back();
    }
    if(!ok){
        diff+='-';
    }
    diff = reverse(diff);
    return diff;
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
  int sign_1 = i1->get_sign();
  int sign_2 = i2->get_sign();
  string s1 = i1->to_string();if(sign_1==-1){s1.erase(s1.begin());}
  string s2 = i2->to_string();if(sign_2==-1){s2.erase(s2.begin());}
  int l1 = s1.size();
  int l2 = s2.size();
  string div="";
    if(l1 < l2){
        if(sign_1*sign_2==-1){
            UnlimitedInt* obj = new UnlimitedInt("-1");
            return obj;
        }
        else{
            UnlimitedInt* obj = new UnlimitedInt("0");
            return obj;

        }
    }
    else if(l1 == l2){
        for(int i(0);i<10;i++){
            if(string_compare(s1,digit_mul(s2,i)) && !string_compare(s1,digit_mul(s2,i+1))){
                if(sign_1*sign_2==-1){
                    div+='-';
                    string temp= string_sub(s1,digit_mul(s2,i));
                    if(temp!="0"){
                        i++;
                    }
                }
                div+=(i+'0');
                while(div[0]=='0' && div.size()>1){
                    div.erase(div.begin());
                }
                UnlimitedInt* obj = new UnlimitedInt(div);
                return obj;
            }
        }
    }
    else{
        string cur = s1.substr(0,l2);
        int i = l2;
        while(i<=l1){
            for(int j(0);j<10;j++){
                bool ok1 = string_compare(cur,digit_mul(s2,j));
                bool ok2 = string_compare(cur,digit_mul(s2,j+1));
                if(ok1 && (!ok2)){
                    div+=(j+'0');
                    cur = string_sub(cur,digit_mul(s2,j));
                    break;
                }
            }
            cur+=s1[i];
            while(cur[0]=='0' && cur.size()>1){
                cur.erase(cur.begin());
            }
            i++;
        }
        while(div[0]=='0' && div.size()>1){
            div.erase(div.begin());
        }   
        UnlimitedInt* one = new UnlimitedInt("1");
        UnlimitedInt* final_div = new UnlimitedInt(div);
        if(sign_1*sign_2==-1){
            if(int(cur[0])==48 && cur.size()==1){
                 final_div->sign = -1;
            }
            else{
                final_div = add(final_div,one);
                final_div->sign = -1;
            }
            
        }
        return final_div;
    }
    return nullptr;
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* quotient  = div(i1,i2);
    UnlimitedInt* prod = mul(quotient,i2);
    UnlimitedInt* mod = sub(i1,prod);
    if(mod->to_string() == i2->to_string()){
        return new UnlimitedInt("0");
    }
    return mod;
}

string UnlimitedInt::to_string(){
    if(size == 0){
        return "0";
    }
    bool ok = (sign==-1 ? 1 : 0);
    string s="";
    for(int i=0; i<size; i++){
        s += (unlimited_int[i] + '0');
    }
    while(s[0]=='0' && s.size()>1){
        s.erase(s.begin());
    }
    if(ok){
        s = '-' + s;
    }
    return s;
}

// int main(){
//     string a,b;cin >> a >> b;
//     UnlimitedInt* p = new UnlimitedInt(a);
//     UnlimitedInt* q = new UnlimitedInt(b);
//     UnlimitedInt* r = UnlimitedInt::mod(p,q);
//     cout << r->to_string();
// }
