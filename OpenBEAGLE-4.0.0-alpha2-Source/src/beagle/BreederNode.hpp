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
 *  \file   beagle/BreederNode.hpp
 *  \brief  Definition of the class BreederNode.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.13 $
 *  $Date: 2007/08/17 18:09:11 $
 */


#ifndef Beagle_BreederNode_hpp
#define Beagle_BreederNode_hpp

#include "beagle/config.hpp"
#include "beagle/macros.hpp"
#include "beagle/Object.hpp"
#include "beagle/Pointer.hpp"
#include "beagle/PointerT.hpp"
#include "beagle/Allocator.hpp"
#include "beagle/AllocatorT.hpp"
#include "beagle/AbstractAllocT.hpp"
#include "beagle/Container.hpp"
#include "beagle/ContainerT.hpp"
#include "beagle/Operator.hpp"
#include "beagle/Individual.hpp"


namespace Beagle
{

// Forward declaration.
class BreederOp;

/*!
 *  \class BreederNode beagle/BreederNode.hpp "beagle/BreederNode.hpp"
 *  \brief Breeder node class, the skeleton of the breeder trees.
 *  \ingroup ECF
 *  \ingroup Op
 */
class BreederNode : public Object
{

public:

	//! BreederNode allocator type.
	typedef AllocatorT<BreederNode,Object::Alloc>
	Alloc;
	//! BreederNode handle type.
	typedef PointerT<BreederNode,Object::Handle>
	Handle;
	//! BreederNode bag type.
	typedef ContainerT<BreederNode,Object::Bag>
	Bag;

	BreederNode(PointerT<BreederOp,Operator::Handle> inBreederOp=NULL,
	            PointerT<BreederNode,Object::Handle> inFirstChild=NULL,
	            PointerT<BreederNode,Object::Handle> inNextSibling=NULL);
	virtual ~BreederNode()
	{ }

	virtual void registerParams(System& ioSystem);
	virtual void init(System& ioSystem);
	virtual void readWithSystem(PACC::XML::ConstIterator inIter, System& ioSystem);
	virtual void write(PACC::XML::Streamer& ioStreamer, bool inIndent=true) const;

	/*!
	 *  \return Breeder operator associated to node.
	 */
	inline PointerT<BreederOp,Operator::Handle> getBreederOp() const
	{
		Beagle_StackTraceBeginM();
		return mBreederOp;
		Beagle_StackTraceEndM("PointerT<BreederOp,Operator::Handle> BreederNode::getBreederOp() const");
	}

	/*!
	 *  \return First child to the breeder.
	 */
	inline PointerT<BreederNode,Object::Handle> getFirstChild() const
	{
		Beagle_StackTraceBeginM();
		return mChild;
		Beagle_StackTraceEndM("PointerT<BreederNode,Object::Handle> BreederNode::getFirstChild() const");
	}

	/*!
	 *  \return Next sibbling to the breeder.
	 */
	inline PointerT<BreederNode,Object::Handle> getNextSibling() const
	{
		Beagle_StackTraceBeginM();
		return mSibling;
		Beagle_StackTraceEndM("PointerT<BreederNode,Object::Handle> BreederNode::getNextSibling() const");
	}

	/*!
	 *  \brief Set breeder operator associated to actual node.
	 *  \param inBreederOp New breeder operator associated to breeder node.
	 */
	inline void setBreederOp(PointerT<BreederOp,Operator::Handle> inBreederOp)
	{
		Beagle_StackTraceBeginM();
		mBreederOp = inBreederOp;
		Beagle_StackTraceEndM("void BreederNode::setBreederOp(PointerT<BreederOp,Operator::Handle> inBreederOp)");
	}

	/*!
	 *  \brief Set first child of the breeder.
	 *  \param inChild New first child.
	 */
	inline void setFirstChild(PointerT<BreederNode,Object::Handle> inChild)
	{
		Beagle_StackTraceBeginM();
		mChild = inChild;
		Beagle_StackTraceEndM("void BreederNode::setFirstChild(PointerT<BreederNode,Object::Handle> inChild)");
	}

	/*!
	 *  \brief Set next sibbling of the breeder.
	 *  \param inSibling New next sibling.
	 */
	inline void setNextSibling(PointerT<BreederNode,Object::Handle> inSibling)
	{
		Beagle_StackTraceBeginM();
		mSibling = inSibling;
		Beagle_StackTraceEndM("void BreederNode::setNextSibling(PointerT<BreederNode,Object::Handle> inSibling)");
	}

private:
	PointerT<BreederOp,Operator::Handle> mBreederOp;  //!< Breeder operator associated to the node.
	PointerT<BreederNode,Object::Handle> mChild;      //!< First breeder node child.
	PointerT<BreederNode,Object::Handle> mSibling;    //!< Next breeder node sibling.

public:
	virtual void read(PACC::XML::ConstIterator inIter);       // Undefined read method!

};

}

#endif // Beagle_BreederNode_hpp

