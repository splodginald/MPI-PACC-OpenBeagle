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
 *  \file   beagle/GA/src/IntegerVector.cpp
 *  \brief  Source code of class GA::IntegerVector.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.11 $
 *  $Date: 2007/08/17 18:09:10 $
 */

#include "beagle/GA.hpp"

#include <algorithm>

using namespace Beagle;


/*!
 *  \brief Construct a GA integer vector.
 *  \param inSize Size of the vector.
 *  \param inModel Default values of the integers.
 */
GA::IntegerVector::IntegerVector(unsigned int inSize, int inModel) :
		std::vector<int>(inSize, inModel)
{ }


/*!
 *  \brief Copy GA integer vector into current.
 *  \param inOriginal Integer vector to copy.
 *  \param ioSystem Evolutionary system to use for making the copy.
 */
void GA::IntegerVector::copy(const Member& inOriginal, System& ioSystem)
{
	Beagle_StackTraceBeginM();
	const GA::IntegerVector& lOriginal = castObjectT<const GA::IntegerVector&>(inOriginal);
	(*this) = lOriginal;
	Beagle_StackTraceEndM("void GA::IntegerVector::copy(const Member&,System&)");
}


/*!
 *  \brief Return size (length) of genotype.
 *  \return Size (length) of genotype.
 */
unsigned int GA::IntegerVector::getSize() const
{
	Beagle_StackTraceBeginM();
	return size();
	Beagle_StackTraceEndM("unsigned int GA::IntegerVector::getSize() const");
}


/*!
 *  \brief Get exact type of the genotype.
 *  \return Exact type of the genotype.
 */
const std::string& GA::IntegerVector::getType() const
{
	Beagle_StackTraceBeginM();
	const static std::string lType("GA-IntegerVector");
	return lType;
	Beagle_StackTraceEndM("const std::string& GA::IntegerVector::getType() const")
}


/*!
 *  \brief Swap the gene at inI with the gene at inJ.
 *	\param inI is the index of the first gene to swap.
 *	\param inJ is the index of the second gene to swap.
 */
void GA::IntegerVector::swap(unsigned int inI, unsigned int inJ)
{
	Beagle_StackTraceBeginM();
	Beagle_BoundCheckAssertM(inI, 0, size() -1);
	Beagle_BoundCheckAssertM(inJ, 0, size() -1);
	std::swap((*this)[inI], (*this)[inJ]);
	Beagle_StackTraceEndM("const std::string& GA::IntegerVector::swap(unsigned int, unsigned int) const")
}


/*!
 *  \brief  Test if two integer vectors are equals.
 *  \param  inRightObj Second integer vector used for the comparison.
 *  \return True if integer vectors are equal and of same size, false if not.
 */
bool GA::IntegerVector::isEqual(const Object& inRightObj) const
{
	Beagle_StackTraceBeginM();
	const GA::IntegerVector& lRightVector = castObjectT<const GA::IntegerVector&>(inRightObj);
	if(size()!=lRightVector.size()) return false;
	const std::vector<int>& lLeft = *this;
	const std::vector<int>& lRight = lRightVector;
	return (lLeft == lRight);
	Beagle_StackTraceEndM("bool GA::IntegerVector::isEqual(const Object&) const");
}


/*!
 *  \brief  Test the ordering of two float vectors.
 *  \param  inRightObj Second float vector used for the ordering test.
 *  \return True if the actual float vector is before the second, false if not.
 */
bool GA::IntegerVector::isLess(const Object& inRightObj) const
{
	Beagle_StackTraceBeginM();
	const GA::IntegerVector& lRightVector = castObjectT<const GA::IntegerVector&>(inRightObj);
	if(size()!=lRightVector.size()) return false;
	const std::vector<int>& lLeft = *this;
	const std::vector<int>& lRight = lRightVector;
	return (lLeft < lRight);
	Beagle_StackTraceEndM("bool GA::IntegerVector::isLess(const Object&) const");
}


/*!
 *  \brief Read a float vector from a XML subtree.
 *  \param inIter XML iterator from which the float vector is read.
 *  \param ioContext Evolutionary context.
 *  \throw Beagle::IOException If a reading error occured (generally bad file format)!
 */
void GA::IntegerVector::readWithContext(PACC::XML::ConstIterator inIter, Context& ioContext)
{
	Beagle_StackTraceBeginM();
	if((inIter->getType() != PACC::XML::eData) || (inIter->getValue() != "Genotype")) {
		throw Beagle_IOExceptionNodeM(*inIter, "tag <Genotype> expected!");
	}
	std::string lGenotypeType = inIter->getAttribute("type");
	if((lGenotypeType.empty() == false) && (lGenotypeType != getType())) {
		std::ostringstream lOSS;
		lOSS << "type given '" << lGenotypeType << "' mismatch type of the genotype '";
		lOSS << getType() << "'!";
		throw Beagle_IOExceptionNodeM(*inIter, lOSS.str());
	}

	PACC::XML::ConstIterator lChild = inIter->getFirstChild();
	if((!lChild) || (lChild->getType()!=PACC::XML::eString))
		throw Beagle_IOExceptionNodeM(*lChild, "expected content for the float vector!");

	clear();
	std::istringstream lISS(lChild->getValue());
	while(lISS.good()) {
		int lValue=INT_MAX;
		lISS >> lValue;
		push_back(lValue);
		if(lISS.good()==false) break;
		int lDelim=lISS.get();
		if((lISS.good()==false) || (lDelim==-1)) break;
	}
	Beagle_StackTraceEndM("void GA::IntegerVector::readWithContext(PACC::XML::ConstIterator,Context&)");
}


/*!
 *  \brief Write a float vector into a XML streamer.
 *  \param ioStreamer XML streamer into which the float vector is written.
 *  \param inIndent Whether output should be indented.
 */
void GA::IntegerVector::writeContent(PACC::XML::Streamer& ioStreamer, bool inIndent) const
{
	Beagle_StackTraceBeginM();
	ioStreamer.insertAttribute("size", uint2str(size()));
	std::ostringstream lOSS;
	for(unsigned int i=0; i<size(); ++i) {
		lOSS << (*this)[i];
		if(i!=(size()-1)) lOSS << ';';
	}
	ioStreamer.insertStringContent(lOSS.str());
	Beagle_StackTraceEndM("void GA::IntegerVector::writeContent(PACC::XML::Streamer& ioStreamer, bool inIndent) const");
}
