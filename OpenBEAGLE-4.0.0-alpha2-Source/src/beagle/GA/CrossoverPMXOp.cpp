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
 *  \file   beagle/GA/src/CrossoverPMXOp.cpp
 *  \brief  Source code of class GA::CrossoverPMXOp.
 *  \author Francois-Michel De Rainville
 *  $Revision: $
 *  $Date: $
 */

#include "beagle/GA.hpp"

#include <algorithm>
#include <string>

/*!
 *  \brief Construct a GA partialy matched crossover operator.
 *  \param inMatingPbName Mating probability parameter name.
 *  \param inName Name of the operator.
 */
Beagle::GA::CrossoverPMXOp::CrossoverPMXOp(std::string inMatingPbName,
										   std::string inName):
Beagle::CrossoverOp(inMatingPbName, inName)
{ }

/*!
 *  \brief Register the parameters of the GA partialy matched crossover operator.
 *  \param ioSystem System of the evolution.
 */
void Beagle::GA::CrossoverPMXOp::registerParams(Beagle::System& ioSystem)
{
	Beagle_StackTraceBeginM();
	{
		Register::Description lDescription(
										   "Individual partialy matched crossover pb.",
										   "Double",
										   "0.3",
										   "GA partialy matched crossover probability of a single individual."
										   );
		mMatingProba = castHandleT<Double>(ioSystem.getRegister().insertEntry(mMatingProbaName, new Double(0.3f), lDescription));
	}
	CrossoverOp::registerParams(ioSystem);
	Beagle_StackTraceEndM("void GA::CrossoverPMXOp::registerParams(System&)");
}


/*!
 *  \brief Mate two indice integer vector GA individuals for partialy matched crossover.
 *  \param ioIndiv1   First individual to mate.
 *  \param ioContext1 Evolutionary context of the first individual.
 *  \param ioIndiv2   Second individual to mate.
 *  \param ioContext2 Evolutionary context of the second individual.
 *  \return True if the individuals are effectively mated, false if not.
 */
bool Beagle::GA::CrossoverPMXOp::mate(Beagle::Individual& ioIndiv1,
									  Beagle::Context&    ioContext1,
									  Beagle::Individual& ioIndiv2,
									  Beagle::Context&    ioContext2)
{
	Beagle_StackTraceBeginM();
	unsigned int lNbGenotypes = minOf<unsigned int>(ioIndiv1.size(), ioIndiv2.size());
	if(lNbGenotypes == 0) return false;
	
	Beagle_LogDebugM(
					 ioContext1.getSystem().getLogger(),
					 "crossover", "Beagle::GA::CrossoverPMXOp",
					 "Individuals mated (before GA partily matched crossover)"
					 );
	Beagle_LogObjectDebugM(
						   ioContext1.getSystem().getLogger(),
						   "crossover", "Beagle::GA::CrossoverPMXOp",
						   ioIndiv1
						   );
	Beagle_LogObjectDebugM(
						   ioContext1.getSystem().getLogger(),
						   "crossover", "Beagle::GA::CrossoverPMXOp",
						   ioIndiv2
						   );
	
	for(unsigned int i=0; i<lNbGenotypes; ++i) {
		GA::IntegerVector::Handle lIndividual1 = castHandleT<IntegerVector>(ioIndiv1[i]);
		GA::IntegerVector::Handle lIndividual2 = castHandleT<IntegerVector>(ioIndiv2[i]);
		
		std::deque<int> lIndividual1Copy(lIndividual1->begin(), lIndividual1->end());
		std::deque<int> lIndividual2Copy(lIndividual2->begin(), lIndividual2->end());
		
		unsigned int lSize = minOf<unsigned int>(lIndividual1->size(), lIndividual2->size());
		unsigned int a = ioContext1.getSystem().getRandomizer().rollInteger(0, lSize-1);
		unsigned int b = ioContext1.getSystem().getRandomizer().rollInteger(0, lSize-1);
		
		if(a > b){std::swap(a, b);}
		for(unsigned int j = a; j <= b; ++j){
			for(unsigned int k = 0; k < lSize; ++k){
				if((*lIndividual1)[k] == lIndividual1Copy[j])
					(*lIndividual1)[k] = lIndividual2Copy[j];
				else if((*lIndividual1)[k] == lIndividual2Copy[j])
					(*lIndividual1)[k] = lIndividual1Copy[j];
				
				if((*lIndividual2)[k] == lIndividual1Copy[j])
					(*lIndividual2)[k] = lIndividual2Copy[j];
				else if((*lIndividual2)[k] == lIndividual2Copy[j])
					(*lIndividual2)[k] = lIndividual1Copy[j];
			}
		}
	}
	
	Beagle_LogDebugM(
					 ioContext1.getSystem().getLogger(),
					 "crossover", "Beagle::GA::CrossoverPMXOp",
					 "Individuals mated (after GA partialy matched crossover)"
					 );
	Beagle_LogObjectDebugM(
						   ioContext1.getSystem().getLogger(),
						   "crossover",
						   "Beagle::GA::CrossoverPMXOp",
						   ioIndiv1
						   );
	Beagle_LogObjectDebugM(
						   ioContext1.getSystem().getLogger(),
						   "crossover",
						   "Beagle::GA::CrossoverPMXOp",
						   ioIndiv2
						   );
	
	return true;
	Beagle_StackTraceEndM("bool GA::CrossoverPMXOp::mate(Individual& ioIndiv1, Context& ioContext1, Individual& ioIndiv2, Context& ioContext2)");
}
