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
 *  \file   beagle/GA/src/MutationReverseSequenceOp.cpp
 *  \brief  Source code of class GA::MutationReverseSequenceOp.
 *  \author Francois-Michel De Rainville
 *  $Revision: $
 *  $Date: $
 */

#include "beagle/GA.hpp"

#include <algorithm>
#include <string>

using namespace Beagle;


/*!
 *  \brief Construct a GA reverse sequence mutation operator.
 *  \param inMutationPbName Mutation probability parameter name used in register.
 *  \param inName Name of the operator.
 */
GA::MutationReverseSequenceOp::MutationReverseSequenceOp(std::string inMutationPbName,
														 std::string inName) :
Beagle::MutationOp(inMutationPbName, inName)
{ }


/*!
 *  \brief Register the parameters of the GA reverse sequence mutation operator.
 *  \param ioSystem System of the evolution.
 */
void GA::MutationReverseSequenceOp::registerParams(System& ioSystem)
{
	Beagle_StackTraceBeginM();
	{
		Register::Description lDescription(
										   "Individual reverse sequence mutation prob.",
										   "Double",
										   "0.1",
										   "Reverse sequence mutation probability for each GA individual."
										   );
		mMutationProba = castHandleT<Double>(
											ioSystem.getRegister().insertEntry(mMutationPbName, new Double(0.1), lDescription));
	}
	Beagle::MutationOp::registerParams(ioSystem);
	Beagle_StackTraceEndM("void GA::MutationReverseSequenceOp::registerParams(System&)");
}


/*!
 *  \brief Mutate by reversing a sequence of the genotype of a GA individual.
 *  \param ioIndividual GA individual to mutate.
 *  \param ioContext Context of the evolution.
 *  \return True if the individual is effectively mutated, false if not.
 */
bool GA::MutationReverseSequenceOp::mutate(Beagle::Individual& ioIndividual, Context& ioContext)
{
	Beagle_StackTraceBeginM();
	
	bool lMutated = false;
	
	for(unsigned int i=0; i<ioIndividual.size(); i++) {
		Beagle_LogVerboseM(
						   ioContext.getSystem().getLogger(),
						   "mutation", "Beagle::GA::MutationReverseSequenceOp",
						   std::string("Reversing a sequence of the ")+uint2ordinal(i+1)+" individual's genotype"
						   );
		Beagle_LogDebugM(
						 ioContext.getSystem().getLogger(),
						 "mutation", "Beagle::GA::MutationReverseSequenceOp",
						 "The individual's genotype before GA reverse sequence mutation"
						 );
		Beagle_LogObjectDebugM(
							   ioContext.getSystem().getLogger(),
							   "mutation", "Beagle::GA::MutationReverseSequenceOp",
							   *ioIndividual[i]
							   );
		
		unsigned int a = ioContext.getSystem().getRandomizer().rollInteger(0, ioIndividual[i]->getSize()-1);
		unsigned int b = ioContext.getSystem().getRandomizer().rollInteger(0, ioIndividual[i]->getSize()-1);
		if(a > b) std::swap(a, b);
		if(a != b) lMutated = true;
		while(a < b)
			ioIndividual[i]->swap(a++, b--);
		
		if(lMutated) {
			Beagle_LogVerboseM(
							   ioContext.getSystem().getLogger(),
							   "mutation", "Beagle::GA::MutationReverseSequenceOp",
							   std::string("A part of the individual's genotype has been reversed")
							   );
			Beagle_LogDebugM(
							 ioContext.getSystem().getLogger(),
							 "mutation", "Beagle::GA::MutationReverseSequenceOp",
							 "The individual's genotype after GA reverse sequence mutation"
							 );
			Beagle_LogObjectDebugM(
								   ioContext.getSystem().getLogger(),
								   "mutation", "Beagle::GA::MutationReverseSequenceOp",
								   *ioIndividual[i]
								   );
		} else {
			Beagle_LogVerboseM(
							   ioContext.getSystem().getLogger(),
							   "mutation", "Beagle::GA::MutationReverseSequenceOp",
							   std::string("The individual's genotype has not been mutated")
							   );
		}
	}
	return lMutated;
	Beagle_StackTraceEndM("bool GA::MutationReverseSequenceOp::mutate(Beagle::Individual& ioIndividual, Context& ioContext)");
}
