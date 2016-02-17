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
 *  \file   beagle/GA/src/MutationUniformIntVecOp.cpp
 *  \brief  Source code of class GA::MutationUniformIntVecOp.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.15 $
 *  $Date: 2008/03/20 14:01:14 $
 */

#include "beagle/GA.hpp"

#include <algorithm>
#include <string>

using namespace Beagle;


/*!
 *  \brief Construct an integer vector GA uniform mutation operator.
 *  \param inMutationPbName Mutation probability parameter name used in register.
 *  \param inIntMutatePbName Mutation integer probability parameter name used in register.
 *  \param inName Name of the operator.
 */
GA::MutationUniformIntVecOp::MutationUniformIntVecOp(std::string inMutationPbName,
        std::string inIntMutatePbName,
        std::string inName) :
		Beagle::MutationOp(inMutationPbName, inName),
		mIntMutatePbName(inIntMutatePbName)
{ }


/*!
 *  \brief Register the parameters of the integer vector GA uniform mutation operator.
 *  \param ioSystem System of the evolution.
 */
void GA::MutationUniformIntVecOp::registerParams(System& ioSystem)
{
	Beagle_StackTraceBeginM();
	{
		Register::Description lDescription(
		    "Individual unif. mutation prob.",
		    "Double",
		    "0.1",
		    "Integer vector uniform mutation probability for each GA individual."
		);
		mMutationProba = castHandleT<Double>(
		                     ioSystem.getRegister().insertEntry(mMutationPbName, new Double(0.1f), lDescription));
	}
	Beagle::MutationOp::registerParams(ioSystem);
	{
		Register::Description lDescription(
		    "Int unif. mutation probability",
		    "Float",
		    "0.1",
		    "Probability for each integer to be modified by mutation, when an individual is mutated."
		);
		mIntMutateProba = castHandleT<Float>(
		                      ioSystem.getRegister().insertEntry(mIntMutatePbName, new Float(0.1f), lDescription));
	}
	{
		std::ostringstream lOSS;
		lOSS << "Maximum values assigned to vector's integers. ";
		lOSS << "Value can be a scalar, which limit the value for all integers ";
		lOSS << "vector parameters, or a vector which limit the value for the parameters ";
		lOSS << "individually. If the maximum value is smaller than the ";
		lOSS << "integer vector size, the limit used for the last values of the integer vector ";
		lOSS << "is equal to the last value of the maximum value vector.";
		Register::Description lDescription(
		    "Maximum integer values",
		    "IntArray",
		    int2str(INT_MAX),
		    lOSS.str()
		);
		mMaxValue = castHandleT<IntArray>(
		                ioSystem.getRegister().insertEntry("ga.int.maxvalue", new IntArray(1,INT_MAX), lDescription));
	}
	{
		std::ostringstream lOSS;
		lOSS << "Minimum values assigned to vector's integers. ";
		lOSS << "Value can be a scalar, which limit the value for all integer ";
		lOSS << "vector parameters, or a vector which limit the value for the parameters ";
		lOSS << "individually. If the minimum value is smaller than the ";
		lOSS << "integer vector size, the limit used for the last values of the integer vector ";
		lOSS << "is equal to the last value of the minimum value vector.";
		Register::Description lDescription(
		    "Minimum integer values",
		    "IntArray",
		    int2str(INT_MIN),
		    lOSS.str()
		);
		mMinValue = castHandleT<IntArray>(
		                ioSystem.getRegister().insertEntry("ga.int.minvalue", new IntArray(1,INT_MIN), lDescription));
	}
	Beagle_StackTraceEndM("void GA::MutationUniformIntVecOp::registerParams(System&)");
}


/*!
 *  \brief Uniformly mutate an integer vector GA individual.
 *  \param ioIndividual GA individual to mutate.
 *  \param ioContext Context of the evolution.
 *  \return True if the individual is effectively mutated, false if not.
 */
bool GA::MutationUniformIntVecOp::mutate(Beagle::Individual& ioIndividual, Context& ioContext)
{
	Beagle_StackTraceBeginM();
	Beagle_ValidateParameterM(mIntMutateProba->getWrappedValue()>=0.0, mIntMutatePbName, "<0");

	bool lMutated = false;
	Beagle_LogVerboseM(
	    ioContext.getSystem().getLogger(),
	    "mutation", "Beagle::GA::MutationUniformIntVecOp",
	    std::string("Integer uniform mutation probability is: ")+
	    dbl2str(mIntMutateProba->getWrappedValue())
	);

	for(unsigned int i=0; i<ioIndividual.size(); i++) {
		GA::IntegerVector::Handle lIV = castHandleT<GA::IntegerVector>(ioIndividual[i]);
		Beagle_LogVerboseM(
		    ioContext.getSystem().getLogger(),
		    "mutation", "Beagle::GA::MutationUniformIntVecOp",
		    std::string("Uniformly mutating the ")+uint2ordinal(i+1)+" integer vector"
		);
		Beagle_LogObjectDebugM(
		    ioContext.getSystem().getLogger(),
		    "mutation", "Beagle::GA::MutationUniformIntVecOp",
		    *lIV
		);
		for(unsigned int j=0; j<lIV->size(); j++) {
			double lRolledPb = ioContext.getSystem().getRandomizer().rollUniform();
			if(lRolledPb <= mIntMutateProba->getWrappedValue()) {
				const int lMaxVal = j<mMaxValue->size() ? (*mMaxValue)[j] : mMaxValue->back();
				const int lMinVal = j<mMinValue->size() ? (*mMinValue)[j] : mMinValue->back();
				Beagle_AssertM(lMaxVal >= lMinVal);
				const int lRandVal = (int)ioContext.getSystem().getRandomizer().rollInteger(0,lMaxVal-lMinVal);
				(*lIV)[j] = (lRandVal+lMinVal);
				lMutated = true;
			}
		}
		if(lMutated) {
			Beagle_LogVerboseM(
			    ioContext.getSystem().getLogger(),
			    "mutation", "Beagle::GA::MutationUniformIntVecOp",
			    std::string("The integer vector has been uniformly mutated")
			);
			Beagle_LogObjectDebugM(
			    ioContext.getSystem().getLogger(),
			    "mutation", "Beagle::GA::MutationUniformIntVecOp",
			    *lIV
			);
		} else {
			Beagle_LogVerboseM(
			    ioContext.getSystem().getLogger(),
			    "mutation", "Beagle::GA::MutationUniformIntVecOp",
			    std::string("The integer vector has not been mutated")
			);
		}
	}
	return lMutated;
	Beagle_StackTraceEndM("bool GA::MutationUniformIntVecOp::mutate(Beagle::Individual& ioIndividual, Context& ioContext)");
}


/*!
 *  \brief Read a uniform mutation operator from XML subtree.
 *  \param inIter XML iterator to use to read mutation operator.
 *  \param ioSystem Evolutionary system.
 */
void GA::MutationUniformIntVecOp::readWithSystem(PACC::XML::ConstIterator inIter, System& ioSystem)
{
	Beagle_StackTraceBeginM();
	if((inIter->getType()!=PACC::XML::eData) || (inIter->getValue()!=getName())) {
		std::ostringstream lOSS;
		lOSS << "tag <" << getName() << "> expected!" << std::flush;
		throw Beagle_IOExceptionNodeM(*inIter, lOSS.str());
	}
	std::string lMutationPbReadName = inIter->getAttribute("mutationpb");
	if(lMutationPbReadName.empty() == false) mMutationPbName = lMutationPbReadName;
	std::string lIntMutatePbReadName = inIter->getAttribute("mutintpb");
	if(lIntMutatePbReadName.empty() == false) mIntMutatePbName = lIntMutatePbReadName;
	Beagle_StackTraceEndM("void GA::MutationUniformIntVecOp::readWithSystem(PACC::XML::ConstIterator,System&)");
}


/*!
 *  \brief Write uniform mutation operator into XML streamer.
 *  \param ioStreamer XML streamer to write mutation operator into.
 *  \param inIndent Whether XML output should be indented.
 */
void GA::MutationUniformIntVecOp::writeContent(PACC::XML::Streamer& ioStreamer, bool inIndent) const
{
	Beagle_StackTraceBeginM();
	Beagle::MutationOp::writeContent(ioStreamer, inIndent);
	ioStreamer.insertAttribute("mutintpb", mIntMutatePbName);
	Beagle_StackTraceEndM("void GA::MutationUniformIntVecOp::writeContent(PACC::XML::Streamer& ioStreamer, bool inIndent) const");
}

