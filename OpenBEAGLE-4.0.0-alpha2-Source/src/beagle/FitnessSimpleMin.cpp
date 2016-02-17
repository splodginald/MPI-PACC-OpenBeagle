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
 *  \file   beagle/FitnessSimpleMin.cpp
 *  \brief  Source code of class FitnessSimpleMin.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.11 $
 *  $Date: 2007/08/17 18:09:13 $
 */

#include "beagle/Beagle.hpp"

#include <cmath>
#include <cfloat>
#include <float.h>    // To get FLT_MAX on Borland C++ Builder
#include <algorithm>

using namespace Beagle;


/*!
 *  \brief Construct a valid simple fitness (minimization) object.
 *  \param inFitness Value of the fitness.
 */
FitnessSimpleMin::FitnessSimpleMin(double inFitness)
{
	Beagle_StackTraceBeginM();
	setValue(inFitness);
	Beagle_StackTraceEndM("FitnessSimpleMin::FitnessSimpleMin(double)");
}


/*!
 *  \brief Copy fitness into current.
 *  \param inOriginal Fitness to copy.
 *  \param ioSystem Evolutionary system to use for making the copy.
 */
void FitnessSimpleMin::copy(const Member& inOriginal, System& ioSystem)
{
	Beagle_StackTraceBeginM();
	const FitnessSimpleMin& lOriginal = castObjectT<const FitnessSimpleMin&>(inOriginal);
	(*this) = lOriginal;
	Beagle_StackTraceEndM("void FitnessSimpleMin::copy(const Member&,System&)");
}


/*!
 *  \brief Get exact type of the fitness.
 *  \return Exact type of the fitness.
 */
const std::string& FitnessSimpleMin::getType() const
{
	Beagle_StackTraceBeginM();
	const static std::string lType("FitnessSimpleMin");
	return lType;
	Beagle_StackTraceEndM("const std::string& FitnessSimpleMin::getType() const")
}


/*!
 *  \brief Test order of two simple fitness measure.
 *  \param inRightObj Right measure to compare.
 *  \return True if the actual fitness is less from the right one, false if not.
 */
bool FitnessSimpleMin::isDominated(const Fitness& inRightFitness) const
{
	Beagle_StackTraceBeginM();
	const FitnessSimpleMin& lRightFitness = castObjectT<const FitnessSimpleMin&>(inRightFitness);
	if(isValid() != lRightFitness.isValid()) return false;
	if((isValid()==false) && (lRightFitness.isValid()==false)) return false;
	return mValue > lRightFitness.mValue;
	Beagle_StackTraceEndM("bool FitnessSimpleMin::isDominated(const Object&) const");
}


/*!
 *  \brief Test order of two simple fitness (minimization) measure.
 *  \param inRightObj Right measure to compare.
 *  \return True if the actual fitness is of higher magnitude than the right one, false if not.
 *  \warning In a minimization problem, smallest values are better. So the actual isLess
 *    method returns true when the left FitnessSimpleMin value is higher than
 *    the right one, and false otherwize. This is the opposite of the isLess method of class
 *    FitnessSimple.
 */
bool FitnessSimpleMin::isLess(const Object& inRightObj) const
{
	Beagle_StackTraceBeginM();
	const FitnessSimpleMin& lRightFitness = castObjectT<const FitnessSimpleMin&>(inRightObj);
	if(isValid() != lRightFitness.isValid()) return false;
	if((isValid()==false) && (lRightFitness.isValid()==false)) return false;
	return mValue > lRightFitness.mValue;
	Beagle_StackTraceEndM("bool FitnessSimpleMin::isLess(const Object&) const");
}


/*!
 *  \brief Set the fitness value and validity.
 *  \param inValue New fitness value.
 */
void FitnessSimpleMin::setValue(double inValue)
{
	Beagle_StackTraceBeginM();
	if(isFinite(inValue)) mValue = inValue;
	else mValue = DBL_MAX;
	setValid();
	Beagle_StackTraceEndM("void FitnessSimpleMin::setValue(double)");
}
