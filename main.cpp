#include "bind.h"
#include "iostream"

placeholder<0> _1;
placeholder<1> _2;
placeholder<2> _3;
placeholder<3> _4;
placeholder<4> _5;

using namespace std;

int ret (int a){
    cout<<"ret"<<' ';
    return a;}
int mult (int a,int b){
    cout<<"mult"<<' ';
    return a*b;
}
int supMult(int a,int& b,int const& c){
    cout<<"multx4"<<' ';
    return a*b*c;
}
struct notFunc{
    int operator()(int a, int b){
        cout<<"notFunc"<<' ';
        return  a*b;
    }
};
int ref (int &a){
    for (int i=0;i<10;i++)
    a=a+i;
    return a;
}
int main(){
    cout<<bind(ret, _1)(1)<<'\n';
    cout<<bind(ret, 10)()<<'\n';
    cout<<bind(ret, _4)(1,2,3,4)<<'\n';

    cout<<bind(mult,_1,_2)(3, 17)<<'\n';
    cout<<bind(mult,_2,_2)(3, 17)<<'\n';
    cout<<bind(mult,_2,100)(3, 17)<<'\n';

    int a0=10;int& a1=a0; int const& a2=2;int&& a3=3;
    cout<<bind(supMult, a0, _2,a2)(a0,a1,a2,a3)<<'\n';
    cout<<bind(supMult, _1, a1,_3)(a0,a1,a2,a3)<<'\n';

    notFunc NF;
    cout<<bind(notFunc(),_2,2)(1,2)<<'\n';
    cout<<bind(NF,1,1)()<<'\n';

    cout<<bind([](int a){cout<<"lambda"<<' '; return a;},_1)(1)<<'\n';
    cout<<bind([](){cout<<"lambda"<<' '; return 0;})()<<'\n';

    auto b= bind(ret, _1);
    cout<<bind(ret,b)(1)<<'\n';
    cout<<bind(mult,b(1),b)(11)<<'\n';
    cout<<bind(b,_2)(2,2)<<'\n';
    cout<<bind(notFunc(),bind(bind(mult,_2,_4),_4,_3,_2,_1), b)(1,3,5,11);//bind(notFunc(),bind(bind(mult,5,1),11,5,3,1), 1)
    int a10=4;
    cout<<bind(ref,a10)();
    cout<<a10;
}