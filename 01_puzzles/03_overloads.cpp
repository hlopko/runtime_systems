//Jaky bude vystup metody main? Pujde kod prelozit?
//makro __PRETTY_FUNCTION__ vypise signaturu metody, nejak takhle:
//pro int:        virtual void A::metoda(int) 2
//pro double:     virtual void B::metoda(double) 2.000000
//--------------------------------------------------------------------------------
#include <stdio.h>
class A
{
  public:
    virtual void metoda();
    virtual void metoda(int i);
};
 
class B : public A
{
  public:
    virtual void metoda(double d);
};
void A::metoda() { printf("  %s\n", __PRETTY_FUNCTION__);}
void A::metoda(int i) { printf("  %s %d\n", __PRETTY_FUNCTION__, i);}
void B::metoda(double d) { printf("  %s %f\n", __PRETTY_FUNCTION__, d);}
 
void volaniA(A *a) { printf("volaniA\n"); a->metoda(2);}
void volaniB(B *b) { printf("volaniB\n"); b->metoda(2);}
 
int main(void)
{	
    volaniA(new B);	
    volaniB(new B);
    return 0;
}

