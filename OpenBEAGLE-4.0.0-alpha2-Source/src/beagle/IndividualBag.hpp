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
 *  \file   beagle/IndividualBag.hpp
 *  \brief  Definition of the class IndividualBag.
 *  \author Matthew Walker
 *  \author Christian Gagne
 *  $Revision: 1.11 $
 *  $Date: 2008/02/29 14:12:43 $
 */


#ifndef Beagle_IndividualBag_hpp
#define Beagle_IndividualBag_hpp

#include <string>
#include "beagle/config.hpp"
#include "beagle/macros.hpp"
#include "beagle/Object.hpp"
#include "beagle/Container.hpp"
#include "beagle/ContainerT.hpp"
#include "beagle/Individual.hpp"

namespace Beagle
{


/*!
 *  \class IndividualBag beagle/IndividualBag.hpp "beagle/IndividualBag.hpp"
 *  \brief Container of individuals.
 *  \ingroup ECF
 *  \ingroup Pop
 */
class IndividualBag : public ContainerT<Individual,ContainerT<Genotype,Member::Bag>::Bag>
{

public:

	//! IndividualBag's allocator type.
	typedef AllocatorT<IndividualBag,ContainerT<Individual,ContainerT<Genotype,Member::Bag>::Bag>::Alloc> Alloc;
	//! IndividualBag's handle type.
	typedef PointerT<IndividualBag,ContainerT<Individual,ContainerT<Genotype,Member::Bag>::Bag>::Handle> Handle;
	//! IndividualBag's bag type.
	typedef ContainerT<IndividualBag,ContainerT<Individual,ContainerT<Genotype,Member::Bag>::Bag>::Bag> Bag;

	explicit IndividualBag(unsigned int inN=0, Individual::Handle inModel=NULL);
	virtual ~IndividualBag()
	{ }

	virtual void read(PACC::XML::ConstIterator inIter);
	virtual bool readFromFile(std::string inFileName, System& ioSystem, std::string inBagTag="Deme");
	virtual void readIndividuals(PACC::XML::ConstIterator inIter, Context& ioContext);
	virtual void readWithContext(PACC::XML::ConstIterator inIter, Context& ioContext);
	virtual void write(PACC::XML::Streamer& ioStreamer, bool inIndent=true) const;

};

}

#endif // Beagle_IndividualBag_hpp
