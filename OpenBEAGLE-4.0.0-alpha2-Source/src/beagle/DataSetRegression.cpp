/*
 *  Open BEAGLE
 *  Copyright (C) 2001-2007 by Christian Gagne and Marc Parizeau
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
 *  \file   DataSetRegression.cpp
 *  \brief  Implementation of the class DataSetRegression.
 *  \author Christian Gagne <cgagne@gmail.com>
 *  $Revision: 1.3 $
 *  $Date: 2007/08/17 18:09:13 $
 */

#include "beagle/Beagle.hpp"

#include <stdexcept>

using namespace Beagle;


/*!
 *  \brief Construct data set component useful for regression problems.
 *  \param inName Name of the component.
 */
DataSetRegression::DataSetRegression(const std::string& inName) :
		Component(inName)
{ }


/*!
 *  \brief Read data set from a CVS file.
 *  \param ioIS Input stream referring to CVS file.
 */
void DataSetRegression::readCSV(std::istream& ioIS)
{
  clear();
  char lBuf[4096];
  for(ioIS.getline(lBuf,4096); ioIS.gcount()<4096; ioIS.getline(lBuf,4096)) {
    std::string lStr(lBuf);
    if(lStr.empty()) {
      if(ioIS.good()==false) break;
      else continue;
    }
    resize(size()+1);
    back().second.resize(0);
    std::istringstream lISS(lStr);
    double lDbl=0.0;
    for(lISS >> lDbl; (lISS.peek()==',') && lISS.good(); lISS >> lDbl) {
      const unsigned int lSize = back().second.size();
      back().second.resize(lSize + 1);
      back().second[lSize] = lDbl;
      lISS.get();
    }
    back().first = lDbl;
    if(ioIS.good()==false) break;
  }
  if(ioIS.gcount() == 4096) {
    std::ostringstream lOSS;
    lOSS << "Unable to read data set from given stream, number of characters on one ";
    lOSS << "line exceed 4096 characters!";
    throw std::runtime_error(lOSS.str());
  }
}


/*!
 *  \brief Read data set for regression component.
 *  \param inIter XML iterator to use to read the set.
 *  \param ioSystem Evolutionary system.
 */
void DataSetRegression::readWithSystem(PACC::XML::ConstIterator inIter, System& ioSystem)
{
	Beagle_StackTraceBeginM();
	if((inIter->getType() != PACC::XML::eData) || (inIter->getValue() != getName()))
		throw Beagle_IOExceptionNodeM(*inIter, "invalid node type or tag name!");

	// Get size of data set
	unsigned int lCount = 0;
	for(PACC::XML::ConstIterator lChild=inIter->getFirstChild(); lChild; ++lChild) {
		if((lChild->getType() == PACC::XML::eData) && (lChild->getValue() == "Data")) {
			++lCount;
		}
	}
	std::string lSizeString = inIter->getAttribute("size");
	if(lSizeString.empty() == false) {
		if(lCount != str2uint(lSizeString)) {
			std::ostringstream lOSS;
			lOSS << "number of 'Data' tags (" << lCount;
			lOSS << ") mismatch given value to 'size' attribute (" << lSizeString << ")!";
			throw Beagle_IOExceptionNodeM(*inIter, lOSS.str());
		}
	}
	resize(lCount);
	
	// Read data set
	lCount = 0;
	for(PACC::XML::ConstIterator lChild=inIter->getFirstChild(); lChild; ++lChild) {
		if((lChild->getType() == PACC::XML::eData) && (lChild->getValue() == "Data")) {
			std::string lTargetAttr = lChild->getAttribute("target");
			if(lTargetAttr.empty()) {
				throw Beagle_IOExceptionNodeM(*lChild, "target attribute should be provided!");
			}
			(*this)[lCount].first = str2dbl(lTargetAttr);
			PACC::XML::ConstIterator lChild2 = lChild->getFirstChild();
			if(lChild2->getType() != PACC::XML::eString) {
				throw Beagle_IOExceptionNodeM(*lChild2, "expected string content!");
			}
			(*this)[lCount].second.read(lChild2);
			++lCount;
		}
	}
	
	Beagle_StackTraceEndM("void DataSetRegression::readWithSystem(PACC::XML::ConstIterator, System&)");
}



/*!
 *  \brief Write data set for regression into XML streamer.
 *  \param ioStreamer XML streamer.
 *  \param inIndent Indent (or not) XML output.
 */
void DataSetRegression::writeContent(PACC::XML::Streamer& ioStreamer, bool inIndent) const
{
	Beagle_StackTraceBeginM();
	ioStreamer.insertAttribute("size", uint2str(size()));
	for(unsigned int i=0; i<size(); ++i) {
		ioStreamer.openTag("Data", false);
		ioStreamer.insertAttribute("target", dbl2str((*this)[i].first));
		(*this)[i].second.write(ioStreamer, false);
		ioStreamer.closeTag();
	}
	Beagle_StackTraceEndM("void DataSetRegression::writeContent(PACC::XML::Streamer&, bool) const");
}
