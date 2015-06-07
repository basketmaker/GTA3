#include "analyze.hh"



int main()
{
  using namespace my;

  {
    std::cout << "1ST EXAMPLE:" << std::endl
	      << std::endl;

    box2d b(4, 5);

    bool_t msk_dta[]   = {0, 0, 0, 0, 1,
			  1, 1, 1, 1, 0,
			  0, 0, 0, 1, 1,
			  1, 1, 1, 0, 1};

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

    image2d<unsigned> path = analyze(lab, msk);
    // gives:
    //
    // label 1:  max distance = 6,  max point = (3,4)
    // label 2:  max distance = 2,  max point = (3,2)

    path.debug_print();
    // gives:
    //
    // 0 0 0 0 0 
    // 1 1 1 1 0 
    // 0 0 0 1 1 
    // 2 2 2 0 1 
  }


  {
    std::cout << std::endl
	      << "2ND EXAMPLE:" << std::endl
	      << std::endl;

    box2d b(11, 9);

    bool_t msk_dta[]   = {0, 0, 0, 0, 1, 1, 1, 1, 1,
			  1, 1, 1, 1, 1, 1, 1, 1, 0,
			  0, 0, 0, 0, 1, 0, 0, 0, 0,
			  1, 1, 1, 1, 1, 0, 0, 0, 0,
			  0, 0, 0, 0, 1, 1, 1, 0, 0,
			  1, 1, 1, 0, 1, 0, 1, 1, 1,
			  0, 0, 1, 1, 1, 0, 0, 0, 0,
			  0, 0, 0, 0, 1, 1, 1, 0, 0,
			  0, 0, 0, 0, 1, 0, 1, 1, 1,
			  0, 0, 0, 0, 1, 0, 0, 0, 0,
			  1, 1, 1, 1, 1, 1, 1, 1, 1};

    unsigned lab_dta[] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
			  1, 0, 0, 0, 0, 0, 0, 0, 0,
			  0, 0, 0, 0, 0, 0, 0, 0, 0,
			  2, 0, 0, 0, 0, 0, 0, 0, 0,
			  0, 0, 0, 0, 0, 0, 0, 0, 0,
			  3, 0, 0, 0, 0, 0, 0, 0, 0,
			  0, 0, 0, 0, 0, 0, 0, 0, 0,
			  0, 0, 0, 0, 0, 0, 0, 0, 0,
			  0, 0, 0, 0, 0, 0, 0, 0, 0,
			  0, 0, 0, 0, 0, 0, 0, 0, 0,
			  4, 0, 0, 0, 0, 0, 0, 0, 0};

    image2d<bool_t> msk(b);
    msk.fill(msk_dta);
    msk.debug_print();

    image2d<unsigned> lab(b);
    lab.fill(lab_dta);
    lab.debug_print();

    image2d<unsigned> path = analyze(lab, msk);
    // gives:
    //
    // label 1:  max distance = 9,  max point = (0,8)
    // label 2:  max distance = 10,  max point = (5,8)
    // label 3:  max distance = 11,  max point = (8,8)
    // label 4:  max distance = 8,  max point = (10,8)

    path.debug_print();
    // gives:
    //
    // 0 0 0 0 1 1 1 1 1 
    // 1 1 1 1 1 0 0 0 0 
    // 0 0 0 0 0 0 0 0 0 
    // 2 2 2 2 2 0 0 0 0 
    // 0 0 0 0 2 2 2 0 0 
    // 3 3 3 0 0 0 2 2 2 
    // 0 0 3 3 3 0 0 0 0 
    // 0 0 0 0 3 3 3 0 0 
    // 0 0 0 0 0 0 3 3 3 
    // 0 0 0 0 0 0 0 0 0 
    // 4 4 4 4 4 4 4 4 4 



    // For this example, we have:

    // dmap =
    //
    // 0 0 0 0 5 6 7 8 9 
    // 0 1 2 3 4 5 6 7 0 
    // 0 0 0 0 5 0 0 0 0 
    // 0 1 2 3 4 0 0 0 0 
    // 0 0 0 0 5 6 7 0 0 
    // 0 1 2 0 6 0 8 9 10 
    // 0 0 3 4 5 0 0 0 0 
    // 0 0 0 0 6 7 8 0 0 
    // 0 0 0 0 6 0 9 10 11 
    // 0 0 0 0 5 0 0 0 0 
    // 0 1 2 3 4 5 6 7 8 

    // and iz =
    //
    // 0 0 0 0 1 1 1 1 1 
    // 1 1 1 1 1 1 1 1 0 
    // 0 0 0 0 1 0 0 0 0 
    // 2 2 2 2 2 0 0 0 0 
    // 0 0 0 0 2 2 2 0 0 
    // 3 3 3 0 2 0 2 2 2 
    // 0 0 3 3 3 0 0 0 0 
    // 0 0 0 0 3 3 3 0 0 
    // 0 0 0 0 4 0 3 3 3 
    // 0 0 0 0 4 0 0 0 0 
    // 4 4 4 4 4 4 4 4 4 

  }

}
