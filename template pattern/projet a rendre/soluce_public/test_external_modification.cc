#include "image2d.hh"


namespace my
{

  //  a simple algorithm, version 1


  template <typename I>
  void a_simple_algorithm__v1(const Image<I>& ima_)
  {
    const I& ima = ima_.exact();
    typename I::p_iterator_type p(ima.domain());
    for_all(p)
      std::cout << ima(p) << ' ';
    std::cout << std::endl;
  }



  //  a simple algorithm, version 2
  //  it can now be modified externally thanks to f...


  template <typename I, typename F>
  void a_simple_algorithm__v2(const Image<I>& ima_, F& f)
  {
    const I& ima = ima_.exact();
    f.init(); // do something at initialization
    typename I::p_iterator_type p(ima.domain());
    for_all(p)
    {
      std::cout << ima(p) << ' ';
      f.process(p); // do something at p
    }
    std::cout << std::endl;
    f.final(); // do something finally
  }



  struct nada // means "do nothing"
  {
    void init() {}
    void process(const point2d&) {}
    void final() {}
  };


  template <typename I>
  void a_simple_algorithm__v2(const Image<I>& ima_)
  {
    nada f;
    a_simple_algorithm__v2(ima_, f);
  }



  // now, we really want to do something...


  // example 1: print p

  struct print_p
  {
    void init() {}
    void process(const point2d& p) { std::cout << p << ' '; }
    void final() {}
  };


  // example 2: count the number of loops

  struct counter
  {
    unsigned value;

    counter() { value = 0; }
    void init() { std::cout << "I'm gonna count..." << std::endl; }
    void process(const point2d&) { value += 1; }
    void final() { std::cout << "Result: " << value << " iterations." << std::endl; }
  };



} // my



int main()
{
  using namespace my;

  image2d<unsigned> ima(2, 3);
  debug_iota(ima);


  std::cout << "v1: ";
  a_simple_algorithm__v1(ima);


  std::cout << std::endl
	    << "v2: ";
  a_simple_algorithm__v2(ima);  // equivalent as above

  
  std::cout << std::endl
	    << "v2 with print_p: ";
  print_p f1;
  a_simple_algorithm__v2(ima, f1);


  std::cout << std::endl
	    << "v2 with a counter: " << std::endl;;
  counter f2;
  a_simple_algorithm__v2(ima, f2);
}
