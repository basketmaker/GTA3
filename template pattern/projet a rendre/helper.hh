#ifndef HELPER_HH
# define HELPER_HH

#include "image2d.hh"



namespace my
{

	struct helper
	{
  		
		// FIXME: cut
		helper(const Image<image2d<unsigned> >& lab)
			: lab_(lab.exact()),
			iz(lab.exact().domain()),
			prev(lab.exact().domain())
		{
			typename image2d<unsigned>::p_iterator_type p(lab.exact().domain());
			for_all(p)
				prev(p) = p;
			for_all(p)
				iz(p) = lab_(p);
		}
		template <typename I>
			void init(const point2d &p,const Image<I>& input_)
			{
				iz(p) = input_.exact()(p);
				prev(p) = p;
			}
		void process(const point2d &p, const point2d &n)
		{
			iz(n) = iz(p);
			prev(n) = p;
		}

		const image2d<unsigned>& lab_;
		image2d<unsigned> iz;
		image2d<point2d> prev;
	};


} // end of namespace my



#endif // ndef HELPER_HH

