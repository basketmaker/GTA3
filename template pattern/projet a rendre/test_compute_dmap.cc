#include "compute_dmap.hh"


int main()
{
  using namespace my;

  image2d<bool_t> ima(4, 5);
  data_fill(ima, false);
  ima(point2d(2, 3)) = true;
  ima.debug_print();

  {
    image2d<unsigned> dmap = compute_dmap__SPECIFIC(ima);
    dmap.debug_print();
  }
  {
    image2d<unsigned> dmap = compute_dmap__GENERIC(ima);
    dmap.debug_print();
  }
}
