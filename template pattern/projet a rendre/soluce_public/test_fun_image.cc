#include "fun_image.hh"
#include "compute_dmap.hh"


int main()
{
  using namespace my;

  image2d<int> ima(2,2);
  debug_iota(ima);
  ima.debug_print();

  std::cout << "ima  = " << ima << std::endl;
  std::cout << "ima' = " << make_fun_image(ima, equals(1)) << std::endl;
  
  image2d<unsigned> dmap = compute_dmap__GENERIC(make_fun_image(ima, equals(1)));
  dmap.debug_print();
}
