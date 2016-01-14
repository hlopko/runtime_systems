#include <stdio.h>
class A
{
  public:
    virtual char getid(void) = 0;
};
class B : public A
{
  public:
    virtual char getid(void)
      { return 'B'; }
};
 
int main(void)
{
    try {
      printf("Throwing...\n");
      A *e = new B;
      throw e;
    }
    catch (B *ex) {
      printf("Caught!\n");
    }
	
    return 0;
}
 
