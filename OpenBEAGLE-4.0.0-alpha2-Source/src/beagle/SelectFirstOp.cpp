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
 *  \file   beagle/src/SelectFirstOp.cpp
 *  \brief  Source code of class SelectFirstOp.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.1 $
 *  $Date: 2007/08/29 17:38:32 $
 */

#include "beagle/Beagle.hpp"

using namespace Beagle;


/*!
 *  \brief Construct a selection operator.
 *  \param inReproProbaName Reproduction probability parameter name used in register.
 *  \param inName Name of the selection operator.
 */
SelectFirstOp::SelectFirstOp(std::string inReproProbaName, std::string inName) :
		SelectionOp(inReproProbaName, inName)
{ }


/*!
 *  \brief Select first individual of the population.
 *  \param ioPool Pool of individuals to use for selection.
 *  \param ioContext Evolutionary context.
 */
unsigned int SelectFirstOp::selectIndividual(Individual::Bag& ioPool, Context& ioContext)
{
	Beagle_StackTraceBeginM();
	return 0;
	Beagle_StackTraceEndM("unsigned int SelectFirstOp::selectIndividual(Individual::Bag&,Context&)");
}


/*!
 *  \brief Select inN first individuals.
 *  \param inN Number of individuals to select.
 *  \param ioPool Pool from which the individuals are choosen.
 *  \param ioContext Evolutionary context.
 *  \param outSelections Vector of unsigned ints that say how often an individual was selected.
 *
 *  The output of this method is via outSelection.  It produces a
 *  vector the same size as ioPool, where each index says how many
 *  times an individual was selected.  If this is not the desired
 *  output, consider using the method convertToList().
 */
void SelectFirstOp::selectNIndividuals(unsigned int inN,
                                       Individual::Bag& ioPool,
                                       Context& ioContext,
                                       std::vector<unsigned int>& outSelections)
{
	Beagle_StackTraceBeginM();
	const unsigned int lDivNP = inN / ioPool.size();
	const unsigned int lModNP = inN % ioPool.size();
	outSelections.resize(ioPool.size());
	for(unsigned int i=0; i<ioPool.size(); ++i) {
		outSelections[i] = (i<lModNP) ? lDivNP+1 : lDivNP;
	}
	Beagle_StackTraceEndM("void SelectFirstOp::selectNIndividuals(unsigned int,Individual::Bag&,Context&,std::vector<unsigned int>&)");
}
