/*
 *  Open BEAGLE
 *  Copyright (C) 2001-2007 by Christian Gagne and Marc Parizeau
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact:
 *  Laboratoire de Vision et Systemes Numeriques
 *  Departement de genie electrique et de genie informatique
 *  Universite Laval, Quebec, Canada, G1K 7P4
 *  http://vision.gel.ulaval.ca
 *
 */

/*!
 *  \file   beagle/IndividualSizeFrequencyStatsOp.hpp
 *  \brief  Definition of the class IndividualSizeFrequencyStatsOp.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.5 $
 *  $Date: 2007/08/08 19:26:44 $
 */

#ifndef Beagle_IndividualSizeFrequencyStatsOp_hpp
#define Beagle_IndividualSizeFrequencyStatsOp_hpp

#include "beagle/Operator.hpp"


namespace Beagle
{

/*!
 *  \class IndividualSizeFrequencyStatsOp beagle/IndividualSizeFrequencyStatsOp.hpp
 *    "beagle/IndividualSizeFrequencyStatsOp.hpp"
 *  \brief The individual size frequence usage statistics operator class. Report size frequency of
 *    the individuals.
 *  \ingroup ECF
 *  \ingroup Op
 *  \ingroup FitStats
 */
class IndividualSizeFrequencyStatsOp : public Beagle::Operator
{

public:

	//! IndividualSizeFrequencyStatsOp allocator type.
	typedef AllocatorT<IndividualSizeFrequencyStatsOp,Operator::Alloc>
	Alloc;
	//! IndividualSizeFrequencyStatsOp handle type.
	typedef PointerT<IndividualSizeFrequencyStatsOp,Operator::Handle>
	Handle;
	//! IndividualSizeFrequencyStatsOp bag type.
	typedef ContainerT<IndividualSizeFrequencyStatsOp,Operator::Bag>
	Bag;

	explicit IndividualSizeFrequencyStatsOp(std::string inName="IndividualSizeFrequencyStatsOp");
	virtual ~IndividualSizeFrequencyStatsOp()
	{ }

	virtual void operate(Beagle::Deme& ioDeme, Beagle::Context& ioContext);

};

}

#endif // Beagle_IndividualSizeFrequencyStatsOp_hpp
