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
 *  \file   beagle/Deme.cpp
 *  \brief  Source code of class Deme.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.26 $
 *  $Date: 2007/08/17 18:09:13 $
 */

#include "beagle/Beagle.hpp"

#include <algorithm>

using namespace Beagle;


/*!
 *  \brief Construct a deme.
 *  \param inN Initial number of individuals.
 *  \param inModel Model of individualss.
 */
Deme::Deme(unsigned int inN, Individual::Handle inModel) :
		Individual::Bag(inN, inModel)
{ }


/*!
 *  \brief Add a member to the deme.
 *  \param inMember Member to add.
 */
void Deme::addMember(Member::Handle inMember)
{
	Beagle_StackTraceBeginM();
	MemberMap::const_iterator lIterMap = mMemberMap.find(inMember->getName());
	if(lIterMap != mMemberMap.end()) {
		std::ostringstream lOSS;
		lOSS << "A member named '" << inMember->getName();
		lOSS << "' is already present in the member map; ";
		lOSS << "could not add it.";
		throw Beagle_RunTimeExceptionM(lOSS.str());
	}
	mMemberMap[inMember->getName()] = inMember;
	Beagle_StackTraceEndM("void Deme::addMember(Member::Handle)");
}


/*!
 *  \brief Copy deme using the system.
 *  \param inOriginal Deme to copy into current one.
 *  \param ioSystem Evolutionary system.
 */
void Deme::copy(const Deme& inOriginal, System& ioSystem)
{
	Beagle_StackTraceBeginM();
	const Factory& lFactory = ioSystem.getFactory();

	// Copy members
	mMemberMap.clear();
	for(MemberMap::const_iterator lIterMap=inOriginal.mMemberMap.begin();
	    lIterMap!=inOriginal.mMemberMap.end(); ++lIterMap) {
		const Member::Handle lOrigMember = castHandleT<Member>(lIterMap->second);
		const std::string& lMemberType = lOrigMember->getType();
		Member::Alloc::Handle lMemberAlloc =
			castHandleT<Member::Alloc>(lFactory.getAllocator(lMemberType));
		Member::Handle lMember = castHandleT<Member>(lMemberAlloc->allocate());
		lMember->copy(*lOrigMember, ioSystem);
		mMemberMap[lIterMap->first] = lMember;
	}

	// Copy individuals
	resize(inOriginal.size());
	for(unsigned int i=0; i<inOriginal.size(); ++i) {
		const std::string& lIndivTypeName = inOriginal[i]->getType();
		Individual::Alloc::Handle lIndivAlloc =
			castHandleT<Individual::Alloc>(lFactory.getAllocator(lIndivTypeName));
		Individual::Handle lIndividual = castHandleT<Individual>(lIndivAlloc->allocate());
		lIndividual->copy(*inOriginal[i], ioSystem);
		(*this)[i] = lIndividual;
	}

	Beagle_StackTraceEndM("void Deme::copy(const Deme&,System&)");
}


/*!
 *  \brief Get exact name of the deme.
 *  \return Exact name of the deme.
 */
const std::string& Deme::getName() const
{
	Beagle_StackTraceBeginM();
	const static std::string lName("Deme");
	return lName;
	Beagle_StackTraceEndM("const std::string& Deme::getName() const");
}


/*!
 *  \brief Get exact type of the deme.
 *  \return Exact type of the deme.
 */
const std::string& Deme::getType() const
{
	Beagle_StackTraceBeginM();
	const static std::string lType("Deme");
	return lType;
	Beagle_StackTraceEndM("const std::string& Deme::getType() const");
}


/*!
 *  \brief Reading a deme with method read is undefined. Use readWithContext instead.
 */
void Deme::read(PACC::XML::ConstIterator)
{
	Beagle_StackTraceBeginM();
	throw Beagle_UndefinedMethodInternalExceptionM("read", "Deme", getName());
	Beagle_StackTraceEndM("void Deme::read(PACC::XML::ConstIterator)");
}


/*!
 *  \brief Read members of a deme from an XML iterator.
 *  \param inIter XML iterator to read the members from.
 *  \param ioContext Evolutionary context.
 *  \throw Beagle::IOException If the format is not respected.
 */
void Deme::readMembers(PACC::XML::ConstIterator inIter, Context& ioContext)
{
	Beagle_StackTraceBeginM();
	mMemberMap.clear();
	const Factory& lFactory = ioContext.getSystem().getFactory();
	for(PACC::XML::ConstIterator lIter=inIter; lIter; ++lIter) {
		if(lIter->getType() != PACC::XML::eData) continue;
		if(lIter->getValue() == "Population") continue;
		const std::string& lMemberName = lIter->getValue();
		const std::string& lMemberType = lIter->getAttribute("type");
		Member::Alloc::Handle lMemberAlloc = NULL;
		if(lMemberType.empty()) {
			lMemberAlloc = castHandleT<Member::Alloc>(lFactory.getConceptAllocator(lMemberName));
			if(lMemberAlloc == NULL) {
				std::ostringstream lOSS;
				lOSS << "Member of name '" << lMemberName << "' can't be read; ";
				lOSS << "it appears that its type is not given and that there is not ";
				lOSS << "valid concept allocator associated to it!";
				throw Beagle_IOExceptionNodeM(*lIter, lOSS.str());
			}
		}
		else {
			lMemberAlloc = castHandleT<Member::Alloc>(lFactory.getAllocator(lMemberType));
			if(lMemberAlloc == NULL) {
				std::ostringstream lOSS;
				lOSS << "It seems that type '" << lMemberType << "' associated to member '";
				lOSS << lMemberName << "' is not valid!";
				throw Beagle_IOExceptionNodeM(*lIter, lOSS.str());
			}
		}
		Member::Handle lMember = castHandleT<Member>(lMemberAlloc->allocate());
		lMember->readWithContext(lIter, ioContext);
		mMemberMap[lMemberName] = lMember;
	}
	Beagle_StackTraceEndM("void Deme::readMembers(PACC::XML::ConstIterator,Context&)");
}


/*!
 *  \brief Read a deme population from an XML iterator.
 *  \param inIter XML iterator to read the deme population from.
 *  \param ioContext Evolutionary context.
 *  \throw Beagle::IOException If the format is not respected.
 */
void Deme::readPopulation(PACC::XML::ConstIterator inIter, Context& ioContext)
{
	Beagle_StackTraceBeginM();
	if((inIter->getType()!=PACC::XML::eData) || (inIter->getValue()!="Population")) {
		throw Beagle_IOExceptionNodeM(*inIter, "tag <Population> expected!");
	}
	const Factory& lFactory = ioContext.getSystem().getFactory();
	unsigned int lPrevIndividualIndex = ioContext.getIndividualIndex();
	Individual::Handle lPrevIndividualHandle = ioContext.getIndividualHandle();
	clear();
	for(PACC::XML::ConstIterator lIter=inIter->getFirstChild(); lIter; ++lIter) {
		if((lIter->getType()!=PACC::XML::eData) || (lIter->getValue()!="Individual")) continue;
		const std::string& lIndividualType = lIter->getAttribute("type");
		Individual::Alloc::Handle lIndividualAlloc = NULL;
		if(lIndividualType.empty()) {
			lIndividualAlloc = castHandleT<Individual::Alloc>(lFactory.getConceptAllocator("Individual"));
			if(lIndividualAlloc == NULL) {
				std::ostringstream lOSS;
				lOSS << "Individual object can't be read, ";
				lOSS << "it appears that its type is not given and that there is not ";
				lOSS << "valid concept allocator associated to it!";
				throw Beagle_IOExceptionNodeM(*lIter, lOSS.str());
			}
		}
		else {
			lIndividualAlloc = castHandleT<Individual::Alloc>(lFactory.getAllocator(lIndividualType));
			if(lIndividualAlloc == NULL) {
				std::ostringstream lOSS;
				lOSS << "Type '" << lIndividualType << "' associated to individual object ";
				lOSS << "is not valid!";
				throw Beagle_IOExceptionNodeM(*lIter, lOSS.str());
			}
		}
		Individual::Handle lIndividual = castHandleT<Individual>(lIndividualAlloc->allocate());
		ioContext.setIndividualHandle(lIndividual);
		ioContext.setIndividualIndex(size());
		push_back(lIndividual);
		lIndividual->readWithContext(lIter, ioContext);
	}
	ioContext.setIndividualHandle(lPrevIndividualHandle);
	ioContext.setIndividualIndex(lPrevIndividualIndex);
	Beagle_StackTraceEndM("void Deme::readPopulation(PACC::XML::ConstIterator,Context&)");
}


/*!
 *  \brief Read a deme from an XML iterator.
 *  \param inIter XML iterator to read the deme from.
 *  \param ioContext Evolutionary context to use to read the deme.
 *  \throw Beagle::IOException If the format is not respected.
 */
void Deme::readWithContext(PACC::XML::ConstIterator inIter, Context& ioContext)
{
	Beagle_StackTraceBeginM();
	if((inIter->getType()!=PACC::XML::eData) || (inIter->getValue()!="Deme")) {
		throw Beagle_IOExceptionNodeM(*inIter, "tag <Deme> expected!");
	}
	// Be sure that the types are corresponding
	const std::string& lDemeType = inIter->getAttribute("type");
	if((lDemeType.empty()==false) && (lDemeType!=getType())) {
		std::ostringstream lOSS;
		lOSS << "type given '" << lDemeType << "' mismatch type of the deme '";
		lOSS << getType() << "'!";
		throw Beagle_IOExceptionNodeM(*inIter, lOSS.str());
	}
	// Read members
	readMembers(inIter->getFirstChild(), ioContext);
	// Read population
	for(PACC::XML::ConstIterator lChild=inIter->getFirstChild(); lChild; ++lChild) {
		if((lChild->getType()==PACC::XML::eData) && (lChild->getValue()=="Population")) {
			readPopulation(lChild, ioContext);
		}
	}
	Beagle_StackTraceEndM("void Deme::readWithContext(PACC::XML::ConstIterator,Context&)");
}


/*!
 *  \brief Remove given member from the deme's member map.
 *  \param inName Name of the member to remove.
 *  \return Handle to the member removed from the deme,
 *     NULL pointer if there was no member with given name.
 */
Member::Handle Deme::removeMember(const std::string& inName)
{
	Beagle_StackTraceBeginM();
	MemberMap::iterator lIterMap = mMemberMap.find(inName);
	if(lIterMap == mMemberMap.end()) return NULL;
	Member::Handle lMember = castHandleT<Member>(lIterMap->second);
	mMemberMap.erase(lIterMap);
	return lMember;
	Beagle_StackTraceEndM("Member::Handle Deme::removeMember(const std::string&)");
}


/*!
 *  \brief Write the deme in a XML streamer.
 *  \param ioStreamer XML streamer to write the deme into.
 *  \param inIndent Whether XML output should be indented.
 */
void Deme::write(PACC::XML::Streamer& ioStreamer, bool inIndent) const
{
	Beagle_StackTraceBeginM();
	ioStreamer.openTag("Deme", inIndent);
	ioStreamer.insertAttribute("type", getType());
	writeContent(ioStreamer, inIndent);
	ioStreamer.closeTag();
	Beagle_StackTraceEndM("void Deme::write(PACC::XML::Streamer&,bool) const");
}


/*!
 *  \brief Write content of the deme in a XML streamer.
 *  \param ioStreamer XML streamer to write the deme into.
 *  \param inIndent Whether XML output should be indented.
 */
void Deme::writeContent(PACC::XML::Streamer& ioStreamer, bool inIndent) const
{
	Beagle_StackTraceBeginM();
	writeMembers(ioStreamer, inIndent);
	writePopulation(ioStreamer, inIndent);
	Beagle_StackTraceEndM("void Deme::writeContent(PACC::XML::Streamer&,bool) const");
}


/*!
 *  \brief Write members of the deme in a XML streamer.
 *  \param ioStreamer XML streamer to write the members into.
 *  \param inIndent Whether XML output should be indented.
 */
void Deme::writeMembers(PACC::XML::Streamer& ioStreamer, bool inIndent) const
{
	Beagle_StackTraceBeginM();
	for(MemberMap::const_iterator lIterMap=mMemberMap.begin();
	    lIterMap!=mMemberMap.end(); ++lIterMap) {
		ioStreamer.openTag(lIterMap->first, inIndent);
		Member::Handle lMember = castHandleT<Member>(lIterMap->second);
		ioStreamer.insertAttribute("type", lMember->getType());
		lMember->writeContent(ioStreamer, inIndent);
		ioStreamer.closeTag();
	}
	Beagle_StackTraceEndM("void Deme::writeMembers(PACC::XML::Streamer&,bool) const");
}


/*!
 *  \brief Write the deme population in a XML streamer.
 *  \param ioStreamer XML streamer to write the deme population into.
 *  \param inIndent Whether XML output should be indented.
 */
void Deme::writePopulation(PACC::XML::Streamer& ioStreamer, bool inIndent) const
{
	Beagle_StackTraceBeginM();
	ioStreamer.openTag("Population", inIndent);
	ioStreamer.insertAttribute("size", uint2str(size()));
	for(unsigned int i=0; i<size(); ++i) {
		Beagle_NonNullPointerAssertM((*this)[i]);
		(*this)[i]->write(ioStreamer, inIndent);
	}
	ioStreamer.closeTag();
	Beagle_StackTraceEndM("void Deme::writePopulation(PACC::XML::Streamer&,bool) const");
}

