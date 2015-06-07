#include "image2d.hh"


int main()
{
  using namespace my;

  box2d b(point2d(1,2), point2d(2,4));

  image2d<int> ima(b);
  debug_iota(ima);
  ima.debug_print();

  std::cout << "ima = " << ima << std::endl;
}
