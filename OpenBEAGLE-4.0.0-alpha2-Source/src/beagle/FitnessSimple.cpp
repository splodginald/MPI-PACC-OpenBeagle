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
 *  \file   beagle/FitnessSimple.cpp
 *  \brief  Source code of class FitnessSimple.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.20 $
 *  $Date: 2007/08/17 18:09:13 $
 */

#include "beagle/Beagle.hpp"

#include <cmath>
#include <cfloat>
#include <algorithm>

using namespace Beagle;


/*!
 *  \brief Default construct a simple fitness object.
 */
FitnessSimple::FitnessSimple() :
		Fitness(false),
		mValue(-DBL_MAX)
{ }


/*!
 *  \brief Construct a valid simple fitness object.
 *  \param inValue Value of the fitness.
 */
FitnessSimple::FitnessSimple(double inValue) :
		Fitness(true),
		mValue(isFinite(inValue) ? inValue : -DBL_MAX)
{ }


/*!
 *  \brief Copy fitness into current.
 *  \param inOriginal Fitness to copy.
 *  \param ioSystem Evolutionary system to use for making the copy.
 */
void FitnessSimple::copy(const Member& inOriginal, System& ioSystem)
{
	Beagle_StackTraceBeginM();
	const FitnessSimple& lOriginal = castObjectT<const FitnessSimple&>(inOriginal);
	(*this) = lOriginal;
	Beagle_StackTraceEndM("void FitnessSimple::copy(const Member&,System&)");
}


/*!
 *  \brief  Get distance between two simple fitness measures.
 *  \param  inRightFitness Right fitness to compare.
 *  \return Absolute difference value between the simple measures.
 */
double FitnessSimple::getDistance(const Fitness& inRightFitness) const
{
	Beagle_StackTraceBeginM();
	const FitnessSimple& lRightFitness = castObjectT<const FitnessSimple&>(inRightFitness);
	if((isValid()==false) || (lRightFitness.isValid()==false)) {
		std::ostringstream lOSS;
		lOSS << "Can't return the distance between two simple fitness values as one or both ";
		lOSS << "are invalid!";
		throw Beagle_RunTimeExceptionM(lOSS.str());
	}
	return std::fabs(mValue - lRightFitness.mValue);
	Beagle_StackTraceEndM("double FitnessSimple::getDistance(const Fitness& inRightFitness) const");
}


/*!
 *  \brief  Get number of objectives of simple fitness measures.
 *  \return 1, a simple fitness is made of a single objective.
 */
unsigned int FitnessSimple::getNumberOfObjectives() const
{
	Beagle_StackTraceBeginM();
	return 1;
	Beagle_StackTraceEndM("unsigned int FitnessSimple::getNumberOfObjectives() const");
}


/*!
 *  \brief  Get the objective value of the simple fitness measure.
 *  \param  inObjective Objective index to get value (should be 0).
 *  \return Simple fitness objective value.
 */
double FitnessSimple::getObjective(unsigned int inObjIndex) const
{
	Beagle_StackTraceBeginM();
	if(inObjIndex != 0) {
		std::ostringstream lOSS;
		lOSS << "The objective index value given (" << inObjIndex << ") is invalid, ";
		lOSS << "a simple fitness is made of one objective, so the index should be equal to 0!";
		throw Beagle_RunTimeExceptionM(lOSS.str());
	}
	if(isValid() == false) {
		std::ostringstream lOSS;
		lOSS << "Can't return the value of the objective as the single fitness is invalid!";
		throw Beagle_RunTimeExceptionM(lOSS.str());
	}
	return mValue;
	Beagle_StackTraceEndM("double FitnessSimple::getObjective(unsigned int inObjIndex) const");
}


/*!
 *  \brief Get exact type of the fitness.
 *  \return Exact type of the fitness.
 */
const std::string& FitnessSimple::getType() const
{
	Beagle_StackTraceBeginM();
	const static std::string lType("FitnessSimple");
	return lType;
	Beagle_StackTraceEndM("const std::string& FitnessSimple::getType() const")
}


/*!
 *  \brief Test order of two simple fitness measure.
 *  \param inRightObj Right measure to compare.
 *  \return True if the actual fitness is less from the right one, false if not.
 */
bool FitnessSimple::isDominated(const Fitness& inRightFitness) const
{
	Beagle_StackTraceBeginM();
	const FitnessSimple& lRightFitness = castObjectT<const FitnessSimple&>(inRightFitness);
	if(isValid() != lRightFitness.isValid()) return false;
	if((isValid()==false) && (lRightFitness.isValid()==false)) return false;
	return mValue < lRightFitness.mValue;
	Beagle_StackTraceEndM("bool FitnessSimple::isDominated(const Object& inRightObj) const");
}


/*!
 *  \brief Test equality of two simple fitness measure.
 *  \param inRightObj Right measure to compare.
 *  \return True if the fitness are equal, false if not.
 */
bool FitnessSimple::isEqual(const Object& inRightObj) const
{
	Beagle_StackTraceBeginM();
	const FitnessSimple& lRightFitness = castObjectT<const FitnessSimple&>(inRightObj);
	if(isValid() != lRightFitness.isValid()) return false;
	if((isValid()==false) && (lRightFitness.isValid()==false)) return true;
	return mValue == lRightFitness.mValue;
	Beagle_StackTraceEndM("bool FitnessSimple::isEqual(const Object& inRightObj) const");
}


/*!
 *  \brief Test order of two simple fitness measure.
 *  \param inRightObj Right measure to compare.
 *  \return True if the actual fitness is less from the right one, false if not.
 */
bool FitnessSimple::isLess(const Object& inRightObj) const
{
	Beagle_StackTraceBeginM();
	const FitnessSimple& lRightFitness = castObjectT<const FitnessSimple&>(inRightObj);
	if(isValid() != lRightFitness.isValid()) return false;
	if((isValid()==false) && (lRightFitness.isValid()==false)) return false;
	return mValue < lRightFitness.mValue;
	Beagle_StackTraceEndM("bool FitnessSimple::isLess(const Object& inRightObj) const");
}


/*!
 *  \brief Read a simple fitness from a XML subtree.
 *  \param inIter XML iterator to use to read the fitness value.
 */
void FitnessSimple::read(PACC::XML::ConstIterator inIter)
{
	Beagle_StackTraceBeginM();
	if((inIter->getType()!=PACC::XML::eData) || (inIter->getValue()!="Fitness"))
		throw Beagle_IOExceptionNodeM(*inIter, "tag <Fitness> expected!");

	const std::string& lValid = inIter->getAttribute("valid");
	if(lValid.empty() || (lValid == "yes")) {
	
		// Check type of fitness read
		const std::string& lType = inIter->getAttribute("type");
		if((lType.empty() == false) && (lType != getType())) {
			std::ostringstream lOSS;
			lOSS << "type given '" << lType << "' mismatch type of the fitness '";
			lOSS << getType() << "'!";
			throw Beagle_IOExceptionNodeM(*inIter, lOSS.str());
		}

		// Read value
		PACC::XML::ConstIterator lChild = inIter->getFirstChild();
		if(!lChild) throw Beagle_IOExceptionNodeM(*inIter, "no fitness value present!");
		if(lChild->getType() != PACC::XML::eString)
			throw Beagle_IOExceptionNodeM(*inIter, "no fitness value present!");
		mValue = str2dbl(lChild->getValue());
		setValid();
		
	} else if(lValid == "no") {
		setInvalid();
	}
	else {
		throw Beagle_IOExceptionNodeM(*inIter, "bad fitness validity value!");
	}

	Beagle_StackTraceEndM("void FitnessSimple::read(PACC::XML::ConstIterator)");
}


/*!
 *  \brief Set the fitness value and validity.
 *  \param inValue New fitness value.
 */
void FitnessSimple::setValue(double inValue)
{
	Beagle_StackTraceBeginM();
	if(isFinite(inValue)) mValue = inValue;
	else mValue = -DBL_MAX;
	setValid();
	Beagle_StackTraceEndM("void FitnessSimple::setValue(double)");
}


/*!
 *  \brief Write a simple fitness into an XML streamer.
 *  \param ioStreamer XML streamer to use to write the fitness value.
 *  \param inIndent Whether output should be indented.
 */
void FitnessSimple::writeContent(PACC::XML::Streamer& ioStreamer, bool inIndent) const
{
	Beagle_StackTraceBeginM();
	ioStreamer.insertStringContent(dbl2str(mValue));
	Beagle_StackTraceEndM("void FitnessSimple::writeContent(PACC::XML::Streamer&,bool) const");
}
