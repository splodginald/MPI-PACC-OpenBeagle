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
 *  \file   beagle/GA/CrossoverUniformOpT.hpp
 *  \brief  Definition of the class GA::CrossoverUniformOpT.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.23 $
 *  $Date: 2007/08/17 18:09:10 $
 */

#ifndef Beagle_GA_CrossoverUniformOpT_hpp
#define Beagle_GA_CrossoverUniformOpT_hpp

#include <string>

#include "beagle/config.hpp"
#include "beagle/macros.hpp"
#include "beagle/Object.hpp"
#include "beagle/CrossoverOp.hpp"

namespace Beagle
{
namespace GA
{

/*!
 *  \class CrossoverUniformOpT beagle/GA/CrossoverUniformOpT.hpp
 *    "beagle/GA/CrossoverUniformOpT.hpp"
 *  \brief GA uniform crossover operator class.
 *  \param T GA representation type used in crossover.
 *  \ingroup GAF
 *
 *  The GA genotype type T must fullfil the std::vector template interface.
 */
template <class T>
class CrossoverUniformOpT : public CrossoverOp
{

public:

	//! GA::CrossoverUniformOpT allocator type.
	typedef AllocatorT<CrossoverUniformOpT<T>,CrossoverOp::Alloc>
	Alloc;
	//! GA::CrossoverUniformOpT handle type.
	typedef PointerT<CrossoverUniformOpT<T>,CrossoverOp::Handle>
	Handle;
	//! GA::CrossoverUniformOpT bag type.
	typedef ContainerT<CrossoverUniformOpT<T>,CrossoverOp::Bag>
	Bag;

	explicit CrossoverUniformOpT(std::string inMatingPbName="ga.cxunif.prob",
	                             std::string inDistribPbName="ga.cxunif.distribprob",
	                             std::string inName="GA-CrossoverUniformOpT");
	virtual ~CrossoverUniformOpT()
	{ }

	virtual void registerParams(System& ioSystem);
	virtual bool mate(Individual& ioIndiv1, Context& ioContext1,
	                  Individual& ioIndiv2, Context& ioContext2);
	virtual void readWithSystem(PACC::XML::ConstIterator inIter, System& ioSystem);
	virtual void writeContent(PACC::XML::Streamer& ioStreamer, bool inIndent=true) const;

protected:
	Double::Handle mDistribProba;      //!< Distribution probability of the uniform crossover.
	std::string   mDistribProbaName;  //!< Name used in the register for the distribution probability.

};

}
}


/*!
 *  \brief Construct a GA uniform crossover operator.
 *  \param inMatingPbName Mating probability parameter name.
 *  \param inDistribPbName Distribution probability parameter name.
 *  \param inName Name of the operator.
 */
template <class T>
Beagle::GA::CrossoverUniformOpT<T>::CrossoverUniformOpT(std::string inMatingPbName,
        std::string inDistribPbName,
        std::string inName) :
		Beagle::CrossoverOp(inMatingPbName, inName),
		mDistribProbaName(inDistribPbName)
{ }


/*!
 *  \brief Register the parameters of the GA uniform crossover operator.
 *  \param ioSystem System of the evolution.
 */
template <class T>
void Beagle::GA::CrossoverUniformOpT<T>::registerParams(Beagle::System& ioSystem)
{
	Beagle_StackTraceBeginM();
	{
		Register::Description lDescription(
		    "Individual uniform crossover pb.",
		    "Double",
		    "0.3",
		    "GA uniform crossover probability of a single individual."
		);
		mMatingProba = castHandleT<Double>(
		                   ioSystem.getRegister().insertEntry(mMatingProbaName, new Double(0.3), lDescription));
	}
	CrossoverOp::registerParams(ioSystem);
	{
		std::ostringstream lOSS;
		lOSS << "Uniform GA crossover distribution probability of a single individual. ";
		lOSS << "Value of 0.5 means equal distribution of individuals elements during ";
		lOSS << "crossover. Value of 0.25 means that individuals are composed by 25% ";
		lOSS << "of elements of one individual, and 75% of the elements of the other mated ";
		lOSS << "individuals.";
		Register::Description lDescription(
		    "Uniform crossover distribution prob.",
		    "Float",
		    "0.5",
		    lOSS.str()
		);
		mDistribProba = castHandleT<Double>(
		                    ioSystem.getRegister().insertEntry(mDistribProbaName, new Double(0.5), lDescription));
	}
	Beagle_StackTraceEndM("void GA::CrossoverUniformOpT<T>::registerParams(System&)");
}


/*!
 *  \brief Mate two GA individuals for uniform crossover.
 *  \param ioIndiv1   First individual to mate.
 *  \param ioContext1 Evolutionary context of the first individual.
 *  \param ioIndiv2   Second individual to mate.
 *  \param ioContext2 Evolutionary context of the second individual.
 *  \return True if the individuals are effectively mated, false if not.
 */
template <class T>
bool Beagle::GA::CrossoverUniformOpT<T>::mate(Beagle::Individual& ioIndiv1,
        Beagle::Context&    ioContext1,
        Beagle::Individual& ioIndiv2,
        Beagle::Context&    ioContext2)
{
	Beagle_StackTraceBeginM();
	unsigned int lNbGenotypes = minOf<unsigned int>(ioIndiv1.size(), ioIndiv2.size());
	if(lNbGenotypes == 0) return false;

	Beagle_LogDebugM(
	    ioContext1.getSystem().getLogger(),
	    "crossover", "Beagle::GA::CrossoverUniformOpT",
	    "Individuals mated (before GA uniform crossover)"
	);
	Beagle_LogObjectDebugM(
	    ioContext1.getSystem().getLogger(),
	    "crossover", "Beagle::GA::CrossoverUniformOpT",
	    ioIndiv1
	);
	Beagle_LogObjectDebugM(
	    ioContext1.getSystem().getLogger(),
	    "crossover", "Beagle::GA::CrossoverUniformOpT",
	    ioIndiv2
	);

	for(unsigned int i=0; i<lNbGenotypes; ++i) {
		typename T::Handle lGenotype1 = castHandleT<T>(ioIndiv1[i]);
		typename T::Handle lGenotype2 = castHandleT<T>(ioIndiv2[i]);
		unsigned int lSize = minOf<unsigned int>(lGenotype1->size(), lGenotype2->size());
		for(unsigned int j=0; j<lSize; ++j) {
			double lRolledPb = ioContext1.getSystem().getRandomizer().rollUniform();
			if(lRolledPb <= mDistribProba->getWrappedValue()) {
				typename T::value_type lTemp = (*lGenotype1)[j];
				(*lGenotype1)[j] = (*lGenotype2)[j];
				(*lGenotype2)[j] = lTemp;
			}
		}
	}

	Beagle_LogDebugM(
	    ioContext1.getSystem().getLogger(),
	    "crossover", "Beagle::GA::CrossoverUniformOpT",
	    "Individuals mated (after GA uniform crossover)"
	);
	Beagle_LogObjectDebugM(
	    ioContext1.getSystem().getLogger(),
	    "crossover",
	    "Beagle::GA::CrossoverUniformOpT",
	    ioIndiv1
	);
	Beagle_LogObjectDebugM(
	    ioContext1.getSystem().getLogger(),
	    "crossover",
	    "Beagle::GA::CrossoverUniformOpT",
	    ioIndiv2
	);

	return true;
	Beagle_StackTraceEndM("bool GA::CrossoverUniformOpT<T>::mate(Individual& ioIndiv1, Context& ioContext1, Individual& ioIndiv2, Context& ioContext2)");
}


/*!
 *  \brief Read a uniform crossover operator from XML iterator.
 *  \param inIter XML iterator to use to read crossover operator.
 *  \param ioSystem Evolutionary system.
 */
template <class T>
void Beagle::GA::CrossoverUniformOpT<T>::readWithSystem(PACC::XML::ConstIterator inIter, System& ioSystem)
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
	Beagle_StackTraceEndM("void GA::CrossoverUniformOpT<T>::readWithSystem(PACC::XML::ConstIterator, System&)");
}


/*!
 *  \brief Write uniform crossover operator into XML streamer.
 *  \param ioStreamer XML streamer to write crossover operator into.
 *  \param inIndent Whether XML output should be indented.
 */
template <class T>
void Beagle::GA::CrossoverUniformOpT<T>::writeContent(PACC::XML::Streamer& ioStreamer, bool inIndent) const
{
	Beagle_StackTraceBeginM();
	CrossoverOp::writeContent(ioStreamer, inIndent);
	ioStreamer.insertAttribute("distrpb", mDistribProbaName);
	Beagle_StackTraceEndM("void GA::CrossoverUniformOpT<T>::writeContent(PACC::XML::Streamer& ioStreamer, bool inIndent) const");
}


#endif // Beagle_GA_CrossoverUniformOpT_hpp
