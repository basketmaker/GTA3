#include "image2d.hh"
#include "fun_image.hh"


int main()
{
  using namespace my;

  box2d b(4, 5);

  bool_t msk_dta[]   = {0, 0, 0, 1, 1,
			1, 1, 1, 1, 0,
			0, 0, 0, 0, 0,
			1, 1, 1, 1, 1};

  unsigned lab_dta[] = {0, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			2, 0, 0, 0, 0};

  image2d<bool_t> msk(b);
  msk.fill(msk_dta);
  msk.debug_print();

  image2d<unsigned> lab(b);
  lab.fill(lab_dta);
  lab.debug_print();


  //             col =  0  1  2  3  4     row
  unsigned out_dta[] = {0, 0, 0, 1, 1,  // 0
			1, 1, 1, 1, 0,  // 1
			0, 0, 0, 0, 0,  // 2
			2, 2, 2, 2, 2}; // 3

  image2d<unsigned> out(b);
  out.fill(out_dta);
  out.debug_print();

  std::cout << "out == 1" << std::endl;
  fancy_print(make_fun_image(out, equals(1)), b);

  std::cout << "out == 2" << std::endl;
  fancy_print(make_fun_image(out, equals(2)), b);
}
