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
 *  \file   beagle/Component.hpp
 *  \brief  Definition of class Component.
 *  \author Matthew Walker
 *  \author Christian Gagne
 *  $Revision: 1.19 $
 *  $Date: 2007/08/17 18:09:11 $
 */

#ifndef Beagle_Component_hpp
#define Beagle_Component_hpp

#include "PACC/XML.hpp"

#include "beagle/config.hpp"
#include "beagle/macros.hpp"
#include "beagle/Object.hpp"
#include "beagle/Pointer.hpp"
#include "beagle/PointerT.hpp"
#include "beagle/Allocator.hpp"
#include "beagle/AllocatorT.hpp"
#include "beagle/Container.hpp"
#include "beagle/ContainerT.hpp"
#include "beagle/NamedObject.hpp"

namespace Beagle
{

// Forward declaration
class System;


/*!
 *  \class Component beagle/Component.hpp "beagle/Component.hpp"
 *  \brief System component base class.
 *  \ingroup ECF
 *  \ingroup Sys
 */
class Component : public NamedObject
{

public:

	//! Component allocator type.
	typedef AllocatorT<Component,NamedObject::Alloc> Alloc;

	//! Component handle type.
	typedef PointerT<Component,NamedObject::Handle> Handle;

	//! Component bag type.
	typedef ContainerT<Component,NamedObject::Bag> Bag;

	explicit Component(std::string inName="Unnamed component");
	virtual ~Component()
	{ }

	virtual void init(System& ioSystem);
	virtual void readWithSystem(PACC::XML::ConstIterator inIter, System& ioSystem);
	virtual void registerParams(System& ioSystem);
	virtual void write(PACC::XML::Streamer& ioStreamer, bool inIndent=true) const;
	virtual void writeContent(PACC::XML::Streamer& ioStreamer, bool inIndent=true) const;

	//! Return whether the parameters of this component have been registered.
	bool hasRegisteredParams(void) const
	{
		return mRegistered;
	}

	//! Return whether this component has been initialized.
	bool isInitialized(void) const 
	{
		return mInitialized;
	}

	//! Set the state of the registered flag to value \c inValue.
	void setRegisteredFlag(bool inValue=true)
	{
		mRegistered = inValue;
	}

	//! Set the state of the initialized flag to value \c inValue.
	void setInitializedFlag(bool inValue=true)
	{
		mInitialized = inValue;
	}

protected:

	bool mRegistered; //!< Flag that indicates whether component parameters have been registered.
	bool mInitialized; //!< Flag that indicates whether this component has been initialized.

};

}

#endif // Beagle_Component_hpp
