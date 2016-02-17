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
 *  \file   beagle/DecimateOp.hpp
 *  \brief  Definition of the class DecimateOp.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.10 $
 *  $Date: 2007/08/08 19:26:44 $
 */

#ifndef Beagle_DecimateOp_hpp
#define Beagle_DecimateOp_hpp

#include <string>

#include "beagle/config.hpp"
#include "beagle/macros.hpp"
#include "beagle/Object.hpp"
#include "beagle/AbstractAllocT.hpp"
#include "beagle/PointerT.hpp"
#include "beagle/ContainerT.hpp"
#include "beagle/Operator.hpp"
#include "beagle/UInt.hpp"
#include "beagle/String.hpp"
#include "beagle/Individual.hpp"
#include "beagle/Float.hpp"


namespace Beagle
{

/*!
 *  \class DecimateOp beagle/DecimateOp.hpp "beagle/DecimateOp.hpp"
 *  \brief Population decimation operator class.
 *  \ingroup ECF
 *  \ingroup Op
 *
 *  This operator shrinks the population size (i.e. it "decimates" the
 *  population).  The decimation is done by keeping the \em n best
 *  individuals of the population, where \em n is \f$ratio \times
 *  population size\f$ and \em ratio is the decimation ratio, which is
 *  less than or equal to 1.0.
 *
 *  The name of the decimation ratio defaults to
 *  "ec.decimation.ratio".
 *
 *  A special decimation ratio exists: -1.0.  If this ratio is used
 *  then the population will be reduced to the size specified in the
 *  register variable "ec.pop.size".  If the use of this special ratio
 *  would result in an \em increase in the population size then an
 *  exception is thrown.
 *
 *  To increase the size of the population, consider
 *  Beagle::OversizeOp.
 *
 */
class DecimateOp : public Operator
{

public:

	//! DecimateOp allocator type.
	typedef AllocatorT<DecimateOp,Operator::Alloc>
	Alloc;
	//! DecimateOp handle type.
	typedef PointerT<DecimateOp,Operator::Handle>
	Handle;
	//! DecimateOp bag type.
	typedef ContainerT<DecimateOp,Operator::Bag>
	Bag;

	explicit DecimateOp(std::string inDecimationRatioName="ec.decimation.ratio",
	                    std::string inName="DecimateOp");
	virtual ~DecimateOp()
	{ }

	virtual void registerParams(System& ioSystem);
	virtual void operate(Deme& ioDeme, Context& ioContext);

protected:
	UIntArray::Handle mPopSize;              //!< Population size for the evolution.
	Float::Handle     mDecimationRatio;      //!< Decimation ratio for the actual population.
	std::string       mDecimationRatioName;  //!< Decimation ratio parameter name.

};

}

#endif // Beagle_DecimateOp_hpp

