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
 *  \file   beagle/GA/src/CrossoverUPMXOp.cpp
 *  \brief  Source code of class GA::CrossoverUPMXOp.
 *  \author Francois-Michel De Rainville
 *  $Revision: $
 *  $Date: $
 */

#include "beagle/GA.hpp"

#include <algorithm>
#include <string>

/*!
 *  \brief Construct a GA uniform partialy matched crossover operator.
 *  \param inMatingPbName Mating probability parameter name.
 *  \param inMatchPbName Distribution probability parameter name.
 *  \param inName Name of the operator.
 */
Beagle::GA::CrossoverUPMXOp::CrossoverUPMXOp(std::string inMatingPbName,
											 std::string inDistribPbName,
											 std::string inName):
Beagle::CrossoverOp(inMatingPbName, inName), mDistribProbaName(inDistribPbName)
{ }

/*!
 *  \brief Register the parameters of the GA uniform partialy matched crossover operator.
 *  \param ioSystem System of the evolution.
 */
void Beagle::GA::CrossoverUPMXOp::registerParams(Beagle::System& ioSystem)
{
	Beagle_StackTraceBeginM();
	{
		Register::Description lDescription(
			"Individual uniform partialy mixed crossover pb.",
			"Double",
			"0.3",
			"GA uniform partialy mixed crossover probability of a single individual."
		);
		mMatingProba = castHandleT<Double>(ioSystem.getRegister().insertEntry(mMatingProbaName, new Double(0.3f), lDescription));
	}
	CrossoverOp::registerParams(ioSystem);
	{
		std::ostringstream lOSS;
		lOSS << "Uniform partialy matched GA crossover distribution probability of matching ";
		lOSS << "two elements at a same location. Value of 0.5 means that half of the elements will ";
		lOSS << "be matched and swapped. Value of 0.25 means that 25% of the elements will ";
		lOSS << "be matched and swapped resulting generaly in a 50% (or less) crossover. ";
		Register::Description lDescription(
										   "Uniform matching distribution prob.",
										   "Float",
										   "0.25",
										   lOSS.str()
										   );
		mDistribProba = castHandleT<Float>(
										ioSystem.getRegister().insertEntry(mDistribProbaName, new Float(0.25f), lDescription));
	}
	Beagle_StackTraceEndM("void GA::CrossoverUPMXOp::registerParams(System&)");
}


/*!
 *  \brief Mate two indice integer vector GA individuals for uniform partialy matched crossover.
 *  \param ioIndiv1   First individual to mate.
 *  \param ioContext1 Evolutionary context of the first individual.
 *  \param ioIndiv2   Second individual to mate.
 *  \param ioContext2 Evolutionary context of the second individual.
 *  \return True if the individuals are effectively mated, false if not.
 */
bool Beagle::GA::CrossoverUPMXOp::mate(Beagle::Individual& ioIndiv1,
									   Beagle::Context&    ioContext1,
									   Beagle::Individual& ioIndiv2,
									   Beagle::Context&    ioContext2)
{
	Beagle_StackTraceBeginM();
	unsigned int lNbGenotypes = minOf<unsigned int>(ioIndiv1.size(), ioIndiv2.size());
	if(lNbGenotypes == 0) return false;
	
	Beagle_LogDebugM(
					 ioContext1.getSystem().getLogger(),
					 "crossover", "Beagle::GA::CrossoverUPMXOp",
					 "Individuals mated (before GA uniform partily matched crossover)"
					 );
	Beagle_LogObjectDebugM(
						   ioContext1.getSystem().getLogger(),
						   "crossover", "Beagle::GA::CrossoverUPMXOp",
						   ioIndiv1
						   );
	Beagle_LogObjectDebugM(
						   ioContext1.getSystem().getLogger(),
						   "crossover", "Beagle::GA::CrossoverUPMXOp",
						   ioIndiv2
						   );
	
	for(unsigned int i=0; i<lNbGenotypes; ++i) {
		GA::IntegerVector::Handle lIndividual1 = castHandleT<IntegerVector>(ioIndiv1[i]);
		GA::IntegerVector::Handle lIndividual2 = castHandleT<IntegerVector>(ioIndiv2[i]);
		
		Beagle_AssertM(lIndividual1->size() == lIndividual2->size());
		
		unsigned int lSize = lIndividual1->size();
		
		unsigned int* lPos1 = new unsigned int[lSize];
		unsigned int* lPos2 = new unsigned int[lSize];
		
		for(unsigned int j = 0; j < lSize; ++j){
			lPos1[(*lIndividual1)[j]] = j;
			lPos2[(*lIndividual2)[j]] = j;
		}
		
		for(unsigned int j = 0; j < lSize; ++j){
			float lRndNum = ioContext1.getSystem().getRandomizer().rollUniform();
			if(lRndNum <= mDistribProba->getWrappedValue()){
				// Keep track of the matched values
				int lTemp1 = (*lIndividual1)[j];
				int lTemp2 = (*lIndividual2)[j];
				// Swap the Matched values
				std::swap((*lIndividual1)[j], (*lIndividual1)[lPos1[lTemp2]]);
				std::swap((*lIndividual2)[j], (*lIndividual2)[lPos2[lTemp1]]);
				// Position bookkeeping
				std::swap(lPos1[lTemp1], lPos1[lTemp2]);
				std::swap(lPos2[lTemp1], lPos2[lTemp2]);
			}
		}
		
		delete[] lPos1;
		delete[] lPos2;
	}
	
	Beagle_LogDebugM(
					 ioContext1.getSystem().getLogger(),
					 "crossover", "Beagle::GA::CrossoverUPMXOp",
					 "Individuals mated (after GA uniform partialy matched crossover)"
					 );
	Beagle_LogObjectDebugM(
						   ioContext1.getSystem().getLogger(),
						   "crossover",
						   "Beagle::GA::CrossoverUPMXOp",
						   ioIndiv1
						   );
	Beagle_LogObjectDebugM(
						   ioContext1.getSystem().getLogger(),
						   "crossover",
						   "Beagle::GA::CrossoverUPMXOp",
						   ioIndiv2
						   );
	
	return true;
	Beagle_StackTraceEndM("bool GA::CrossoverUPMXOp::mate(Individual& ioIndiv1, Context& ioContext1, Individual& ioIndiv2, Context& ioContext2)");
}


/*!
 *  \brief Read a uniform crossover operator from XML iterator.
 *  \param inIter XML iterator to use to read crossover operator.
 *  \param ioSystem Evolutionary system.
 */
void Beagle::GA::CrossoverUPMXOp::readWithSystem(PACC::XML::ConstIterator inIter, System& ioSystem)
{
	Beagle_StackTraceBeginM();
	if((inIter->getType()!=PACC::XML::eData) || (inIter->getValue()!=getName())) {
		std::ostringstream lOSS;
		lOSS << "tag <" << getName() << "> expected!" << std::flush;
		throw Beagle_IOExceptionNodeM(*inIter, lOSS.str());
	}
	std::string lMatingProbaReadName = inIter->getAttribute("matingpb");
	if(lMatingProbaReadName.empty() == false) mMatingProbaName = lMatingProbaReadName;
	std::string lDistribProbaReadName = inIter->getAttribute("distrpb");
	if(lDistribProbaReadName.empty() == false) mDistribProbaName = lDistribProbaReadName;
	// For backward compatibility, accept ancient name "mutdistribpb"
	std::string lDistribProbaReadNameLegacy = inIter->getAttribute("mutdistribpb");
	if(lDistribProbaReadNameLegacy.empty() == false) mDistribProbaName = lDistribProbaReadNameLegacy;
	Beagle_StackTraceEndM("void GA::CrossoverUPMXOp::readWithSystem(PACC::XML::ConstIterator, System&)");
}


/*!
 *  \brief Write uniform partialy matched crossover operator into XML streamer.
 *  \param ioStreamer XML streamer to write crossover operator into.
 *  \param inIndent Whether XML output should be indented.
 */
void Beagle::GA::CrossoverUPMXOp::writeContent(PACC::XML::Streamer& ioStreamer, bool inIndent) const
{
	Beagle_StackTraceBeginM();
	CrossoverOp::writeContent(ioStreamer, inIndent);
	ioStreamer.insertAttribute("distrpb", mDistribProbaName);
	Beagle_StackTraceEndM("void GA::CrossoverUPMXOp::writeContent(PACC::XML::Streamer& ioStreamer, bool inIndent) const");
}
