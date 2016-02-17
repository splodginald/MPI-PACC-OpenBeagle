/*
 *  Artifical ant (ant)
 *  Copyright (C) 2006 by Christian Gagne
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
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
 *  \file   Progn.cpp
 *  \brief  Implementation of class Progn.
 *  \author Christian Gagne <cgagne@gmail.com>
 *  $Revision: 1.3 $
 *  $Date: 2007/08/08 19:26:48 $
 */

#include "beagle/GP.hpp"
#include "Progn.hpp"
#include "AntSimulator.hpp"

using namespace Beagle;


/*!
 *  \brief Construct a progn primitive.
 */
Progn::Progn(unsigned int inNbArguments) :
		GP::Primitive(inNbArguments, std::string("P")+uint2str(inNbArguments))
{ }


/*!
 *  \brief Execute progn primitive.
 *  \param outDatum GP datum, in the actual case a reference to the ant simulator.
 *  \param ioContext Evolutionary context.
 */
void Progn::execute(GP::Datum& outDatum, GP::Context& ioContext)
{
	AntSimulator& lSimulator = castObjectT<AntSimulator&>(outDatum);
	if(lSimulator.getMovesDone() >= lSimulator.getMaxMoves()) return;
	for(unsigned int i=0; i<getNumberArguments(); ++i) {
		getArgument(i, lSimulator, ioContext);
		if(lSimulator.getMovesDone() >= lSimulator.getMaxMoves()) return;
	}
}
