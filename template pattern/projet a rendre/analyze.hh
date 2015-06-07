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
	typedef typename image_if<image2d<unsigned>, image2d<bool_t> >::p_iterator_type p_iterator_if;
	typedef typename image2d<unsigned>::p_iterator_type p_iterator_box;
		
		unsigned i_ = 0;
		std::vector<point2d> point_max;
		std::vector<unsigned> distance_max;


		for(i_=b.pmin().row; i_ <= b.pmax().row; i_++ )	
		{
			if(lab(point2d(i_,0))!=0)
			{
				point_max.push_back(point2d(i_,0));
				distance_max.push_back(0);
			}
		}

		helper f(lab);
		image_if<image2d<unsigned>, image2d<bool_t> > dmap = compute_dmap__v2(make_image_if(lab,msk),f);
		p_iterator_box p(lab.domain());

		for_all(p)
			if(f.iz(p) != 0)
				if(dmap(p) > distance_max[f.iz(p)-1])
				{
					point_max[f.iz(p)-1] = p;
					distance_max[f.iz(p)-1] = dmap(p);
				}

		for(i_ = 0; i_ < point_max.size() ; i_++)
		{
			std::cout<<"label "<<(i_+1)<<": max distance = "<<distance_max[i_]<<", max point = "<<point_max[i_]<<std::endl;
		}



		// FIXME: cut fin

		image2d<unsigned> path(b);
		data_fill(path, 0);

		// FIXME: cut
		for(i_ = 0; i_ < point_max.size() ; i_++)
		{
			point2d previous;
			point2d actuel = point_max[i_];
			while(dmap(actuel) != 0)
			{
				path(actuel)=f.iz(actuel);
				actuel = f.prev(actuel);
			}
			path(actuel)=f.iz(actuel);
		}


		// FIXME: cut 

		return path;
	}



} // end of namepace my


#endif // ndef ANALYZE_HH
