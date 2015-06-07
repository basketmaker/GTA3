#ifndef COMPUTE_DMAP__V2_HH
# define COMPUTE_DMAP__V2_HH

# include <queue>
# include "image2d.hh"


namespace my
{


  /*
    for all p in D
    ,  dmap <- max

    for all p in D
    ,  if input(p) = true
    ,  ,  dmap(p) <- 0
    ,  ,  for all n in N(p) and in D
    ,  ,  ,  if input(n) = false
    ,  ,  ,  ,  q.push(p)
    ,  ,  ,  ,  break

    while q is not empty
    ,  p <- q.pop()
    ,  for all n in N(p)
    ,  ,  if (dmap(n) = max)
    ,  ,  ,  dmap(n) <- dmap(p) + 1
    ,  ,  ,  q.push(n)
  */




  template <typename I, typename F>
  typename I::template with_value_type<unsigned>::ret
  compute_dmap__v2(const Image<I>& input_, F& f)
  {
    typedef typename I::point_type point_type;
    typedef typename I::domain_type domain_type;
    typedef typename I::p_iterator_type p_iterator_type;
    typedef typename I::n_iterator_type n_iterator_type;

    typedef typename I::template with_value_type<unsigned>::ret dmap_type;

    const I& input = input_.exact();
    domain_type D = input.domain();

    const unsigned max = -1;
    dmap_type dmap(D);

    p_iterator_type p(D);
    for_all(p)
      dmap(p) = max;

    std::queue<point_type> q;
    n_iterator_type n;

    for_all(p)
      if (input(p) != 0)
  	{
	  // FIXME: cut
  	}

    while (not q.empty())
      {
  	point_type p = q.front();
  	q.pop();
  	n.center_at(p);
  	for_all(n)
  	  if (D.has(n) and dmap(n) == max)
  	    {
	      // FIXME: cut
	    }
      }

    return dmap;
  }



  // FIXME: cut



} // end of namespace my


#endif // ndef COMPUTE_DMAP__V2_HH
