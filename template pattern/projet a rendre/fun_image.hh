#ifndef FUN_IMAGE_HH
# define FUN_IMAGE_HH

# include "image2d.hh"


namespace my
{


  struct equals
  {
    typedef bool result_type;
    int v_;

    equals(int v)
      : v_(v)
    {
    }

    bool operator()(int v) const
    {
      return v == v_;
    }
  };


  template <typename I, typename F>
  class fun_image : public Image< fun_image<I,F> >
  {
  public:
    typedef typename F::result_type value_type;

    typedef typename I::domain_type domain_type;
    typedef typename I::point_type point_type;
    typedef typename I::p_iterator_type p_iterator_type;
    typedef typename I::n_iterator_type n_iterator_type;


    template <typename U>
    struct with_value_type {
      typedef typename I::template with_value_type<U>::ret ret;
    };


    // ctor

    fun_image(const Image<I>& ima, F f)
      : ima_(ima.exact()),
	f_(f)
    {
    }

    // access to pixel values

    value_type operator()(const point_type& p) const
    {
      if (not ima_.domain().has(p))
	  std::abort();
      return f_(ima_(p));
    }

    // domain

    const domain_type& domain() const
    {
      return ima_.domain();
    }

 private:

    const I& ima_;
    F f_;
  };


  template <typename I, typename F>
  fun_image<I,F>
  make_fun_image(const Image<I>& ima, F f)
  {
    return fun_image<I,F>(ima, f);
  }



} // end of namespace my



#endif // ndef FUN_IMAGE_HH
