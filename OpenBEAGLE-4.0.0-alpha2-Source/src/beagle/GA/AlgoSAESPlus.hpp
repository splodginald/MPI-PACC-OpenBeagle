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
 *  \file   beagle/GA/AlgoSAESPlus.hpp
 *  \brief  Definition of the class GA::AlgoSAESPlus.
 *  \author Christian Gagne
 *  $Revision: 1.1 $
 *  $Date: 2007/08/08 14:51:33 $
 */

#ifndef Beagle_GA_AlgoSAESPlus_hpp
#define Beagle_GA_AlgoSAESPlus_hpp

#include <map>
#include <string>

#include "beagle/config.hpp"
#include "beagle/macros.hpp"
#include "beagle/Algorithm.hpp"


namespace Beagle
{

namespace GA
{


/*!
 *  \class GA::AlgoSAESPlus beagle/GA/AlgoSAESPlus.hpp "beagle/GA/AlgoSAESPlus.hpp"
 *  \brief Self-adaptive evolution strategy, with (\mu+\lambda) replacement strategy.
 *  \ingroup GAF
 *  \ingroup GAES
 */
class AlgoSAESPlus : public Algorithm
{

public:

	//! AlgoSAESPlus allocator type.
	typedef AllocatorT< AlgoSAESPlus, Algorithm::Alloc > Alloc;
	//! AlgoSAESPlus handle type.
	typedef PointerT< AlgoSAESPlus, Algorithm::Handle > Handle;
	//! AlgoSAESPlus bag type.
	typedef ContainerT< AlgoSAESPlus, Algorithm::Bag > Bag;

	AlgoSAESPlus(void);

	virtual void configure(Evolver& ioEvolver, System& ioSystem);

};

}
}

#endif // Beagle_GA_AlgoSAESPlus_hpp
