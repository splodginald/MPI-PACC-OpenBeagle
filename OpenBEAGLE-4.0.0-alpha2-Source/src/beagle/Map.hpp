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
 *  \file   beagle/Map.hpp
 *  \brief  Definition of class Map.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.14 $
 *  $Date: 2007/09/21 17:45:46 $
 */

#ifndef Beagle_Map_hpp
#define Beagle_Map_hpp

#include <string>
#include <map>

#include "PACC/XML.hpp"

#include "beagle/config.hpp"
#include "beagle/macros.hpp"
#include "beagle/Object.hpp"
#include "beagle/Pointer.hpp"
#include "beagle/PointerT.hpp"
#include "beagle/Container.hpp"
#include "beagle/ContainerT.hpp"
#include "beagle/HashString.hpp"

#ifdef BEAGLE_HAVE_STDTR1_UNORDEREDMAP
  #include <tr1/unordered_map>
#else
  #ifdef BEAGLE_HAVE_STD_UNORDEREDMAP
    #include <unordered_map>
  #endif // BEAGLE_HAVE_STD_UNORDEREDMAP
#endif //BEAGLE_HAVE_STDTR1_UNORDEREDMAP

namespace Beagle
{

/*!
 *  \class Map beagle/Map.hpp "beagle/Map.hpp"
 *  \brief Associative container using a string as key accessors to the
 *    Object::Handle instances.
 *  \ingroup OOF
 *  \ingroup DataStruct
 */

#if defined(BEAGLE_HAVE_STDTR1_UNORDEREDMAP)
class Map : public Object, public std::tr1::unordered_map<std::string,Object::Handle,HashString>
#elif defined(BEAGLE_HAVE_STD_UNORDEREDMAP)
class Map : public Object, public std::unordered_map<std::string,Object::Handle,HashString>
#else // No hash_map found
class Map : public Object, public std::map< std::string,Object::Handle,std::less<std::string> >
#endif
{

public:

	//! Map allocator type.
	typedef AllocatorT<Map,Object::Alloc> Alloc;
	//! Map handle type.
	typedef PointerT<Map,Object::Handle> Handle;
	//! Map bag type.
	typedef ContainerT<Map,Object::Bag> Bag;

	Map()
	{ }
	virtual ~Map()
	{ }

	virtual bool isEqual(const Object& inRightObj) const;
	virtual bool isLess(const Object& inRightObj) const;
	virtual void read(PACC::XML::ConstIterator inIter);
	virtual void write(PACC::XML::Streamer& ioStreamer, bool inIndent=true) const;

};

}

#endif // Beagle_Map_hpp
