#ifndef ANALYZE_HH
# define ANALYZE_HH

#include "image2d.hh"
#include "image_if.hh"
#include "helper.hh"
#include "compute_dmap__v2.hh"



namespace my
{


  image2d<unsigned> analyze(image2d<unsigned>& lab,
			    const image2d<bool_t>& msk)
  {
    box2d b = lab.domain();

    // FIXME: cut

    image2d<unsigned> path(b);
    data_fill(path, 0);

    // FIXME: cut

    return path;
  }



} // end of namepace my


#endif // ndef ANALYZE_HH
