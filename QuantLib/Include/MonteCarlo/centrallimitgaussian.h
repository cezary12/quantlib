/*
 * Copyright (C) 2000
 * Ferdinando Ametrano, Luigi Ballabio, Adolfo Benin, Marco Marchioro
 * 
 * This file is part of QuantLib.
 * QuantLib is a C++ open source library for financial quantitative
 * analysts and developers --- http://quantlib.sourceforge.net/
 *
 * QuantLib is free software and you are allowed to use, copy, modify, merge,
 * publish, distribute, and/or sell copies of it under the conditions stated 
 * in the QuantLib License.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the license for more details.
 *
 * You should have received a copy of the license along with this file;
 * if not, contact ferdinando@ametrano.net
 *
 * QuantLib license is also available at http://quantlib.sourceforge.net/LICENSE.TXT
*/

/*! \file centrallimitgaussian.h
	\brief Central limit Gaussian random-number generator
	
	$Source$
	$Name$
	$Log$
	Revision 1.1  2000/12/27 15:23:39  marmar
	Random number generators has been updated and documented.
	Now the Sample Generator idea is fully implemented

	
*/

#ifndef quantlib_central_limit_gaussian_transformation_h
#define quantlib_central_limit_gaussian_transformation_h

#include "qldefines.h"

namespace QuantLib {

	namespace MonteCarlo {
		//! Gaussian random number generator
		/*! It uses the well-known that the sum of 12 uniform deviate 
			in (-.5,.5) is approximately a Gaussian deviate with average 0.0
			and standard deviation 1.0, 
			The uniform deviate is supplied by U.
		
			Class U should satisfies
			\code
				U::U(long seed);	
				double U::next() const;	
			    double U::weight() const;
			\endcode
		*/
	
		template <class U>
		class CLGaussian {
		public:
			typedef double SampleType;
			CLGaussian(long seed=0);
			double next() const;
	        double weight() const;
		private:		
			U basicGenerator;		
			double gaussWeight_;
		};

		template <class U>
		CLGaussian<U>::CLGaussian(long seed): 
			basicGenerator(seed), gaussWeight_(0.0) {}

		template <class U>
		inline double CLGaussian<U>::next() const {

			double gaussPoint = -6.0;
			gaussWeight_ = 1.0;
			for(int i=1;i<=12;i++){
				gaussPoint += basicGenerator.next();
				gaussWeight_ *= basicGenerator.weight();
			}
			return gaussPoint;
		}

		template <class U>
        inline double CLGaussian<U>::weight() const {
            return gaussWeight_;
        }

	}

}

#endif
