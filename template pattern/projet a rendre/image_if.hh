#ifndef IMAGE_IF_HH
# define IMAGE_IF_HH

# include "image2d.hh"


namespace my
{
	

	// FIXME: cut

	
	template <typename F>
	class autre_domaine;
	
	template <typename F>
	class autre_domaine_iterator
	{
		public:
			autre_domaine_iterator(const autre_domaine<F>&  b)
			{

				const F& masque = b.getMsk().exact();
				typedef typename F::p_iterator_type p_iterator_box;
				p_iterator_box p(b);
				for_all(p)
				{
					if(masque(p) == 1)
					{
						points_masque.push_back(p);
					}
				}
			}
			void start()
			{
				i_ = 0;
			}
			bool is_valid() const
			{
				return i_ < points_masque.size();
			}
			void next()
			{
				i_ += 1;
			}
			operator point2d() const
			{
				return points_masque[i_];
			}

		private:
			std::vector<point2d> points_masque;
			unsigned i_;
	};
	template <typename F>
	class autre_domaine 
	{
		public:
			autre_domaine(const Image<F>& dom)
			: dom_(dom.exact())
			{
			}
			autre_domaine(const autre_domaine& dom)
			: dom_(dom.getMsk().exact())
			{

			}
			const Image<F>& getMsk() const 
			{
				return dom_;
			}
			
			bool has(const point2d& p) const
			{
				if(dom_.domain().has(p))
					if(dom_(p) == 1)
						return true;
				return false;
			}
			

			operator box2d() const
			{
				return dom_.domain();
			}
		private:
		 	F dom_;
	};


	template <typename I, typename F>
		class image_if : public Image< image_if<I,F> >
	{
		public:
			typedef typename I::value_type value_type;
			

			typedef autre_domaine<F> domain_type;
			typedef typename I::point_type point_type;
			typedef autre_domaine_iterator<F> p_iterator_type;
			typedef typename I::n_iterator_type n_iterator_type;

			template <typename U>
				struct with_value_type {
					typedef image_if<image2d<U>,image2d<bool_t> > ret;
				};
				
			/*
			template <typename U>
				struct with_value_type {
					typedef image2d<U> ret;
				};

			*/
			// ctor

			image_if(const Image<I>& ima, const Image<F>& f)
				: ima_(ima.exact()),
				masque(f)
		{
		}
			image_if(const domain_type& f)
				: masque(f),
				ima_(masque)
		{
		}
			


			// access to pixel values

			value_type operator()(const point_type& p) const
			{
				if (not ima_.domain().has(p))
					std::abort();
				return ima_(p);
			}
	
			value_type &operator()(const point_type& p)
			{
				if (not ima_.domain().has(p))
					std::abort();
				return ima_(p);
			}

			// domain

			const domain_type& domain() const
			{
				return masque;
			}
			
			const I& remove_if() const
			{
				return ima_;
			}
		private:
			domain_type masque;
			I ima_;
	};


	template <typename I, typename F>
		image_if<I,F>
		make_image_if(const Image<I>& ima, const Image<F>& f)
		{
			return image_if<I,F>(ima, f);
		}

} // end of namespace my



#endif // ndef IMAGE_IF_HH
