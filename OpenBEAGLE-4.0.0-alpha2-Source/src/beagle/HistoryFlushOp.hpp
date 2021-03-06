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
 *  \file   beagle/HistoryFlushOp.hpp
 *  \brief  Definition of the class HistoryFlushOp.
 *  \author Alexandre Devert
 *  $Revision: 1.7 $
 *  $Date: 2007/08/17 20:58:00 $
 */

#ifndef Beagle_HistoryFlushOp_hpp
#define Beagle_HistoryFlushOp_hpp

#include "beagle/config.hpp"
#include "beagle/macros.hpp"
#include "beagle/Object.hpp"
#include "beagle/AllocatorT.hpp"
#include "beagle/PointerT.hpp"
#include "beagle/ContainerT.hpp"
#include "beagle/WrapperT.hpp"
#include "beagle/Operator.hpp"
#include "beagle/UInt.hpp"
#include "beagle/String.hpp"
#include "beagle/Bool.hpp"
#include "beagle/UInt.hpp"
#include "beagle/Vivarium.hpp"
#include "beagle/Context.hpp"


namespace Beagle
{

/*!
 *  \class HistoryFlushOp beagle/HistoryFlushOp.hpp "beagle/HistoryFlushOp.hpp"
 *  \brief Flush history when writing a milestone operator class.
 *  \ingroup ECF
 *  \ingroup Op
 *  \ingroup History
 */
class HistoryFlushOp : public Operator
{

public:

	//! HistoryFlushOp allocator type
	typedef AllocatorT<HistoryFlushOp,Operator::Alloc> Alloc;
	//! HistoryFlushOp handle type.
	typedef PointerT<HistoryFlushOp,Operator::Handle> Handle;
	//! HistoryFlushOp bag type.
	typedef ContainerT<HistoryFlushOp,Operator::Bag> Bag;

	explicit HistoryFlushOp(std::string inName="HistoryFlushOp");
	virtual ~HistoryFlushOp()
	{ }

	virtual void registerParams(System& ioSystem);
	virtual void operate(Deme& ioDeme, Context& ioContext);

private:

	String::Handle     mMilestonePrefix;     //!< Prefix of the milestone filenames.
	UInt::Handle       mWritingInterval;     //!< Milestone's writing interval (in generation).
	Bool::Handle       mPerDemeMilestone;    //!< True: write a milestone for every deme.
	UIntArray::Handle  mPopSize;             //!< Population size for the evolution.

};

}

#endif // Beagle_HistoryFlushOp_hpp
