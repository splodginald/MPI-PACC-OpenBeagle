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
 *  \file   beagle/Allocator.hpp
 *  \brief  Definition of abstract class Allocator.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.8 $
 *  $Date: 2007/08/17 18:09:11 $
 */

/*!
 *  \defgroup Allocs Allocators
 *  \ingroup OOF
 *  \brief Object allocators of the framework, part of the Object Oriented Foundations.
 *
 *  An important design choice that gives flexibility to Open BEAGLE is the allocators, a kind of 
 *  object factory that generates objects in an abstract fashion. An abstract allocator class named 
 *  Beagle::Allocator is implemented to define the methods to create objects on the heap. 
 *  \code
 *  class Allocator : public Object {
 *  public:
 *    virtual Object* allocate() const =0;
 *    virtual Object* clone(const Object&) const =0;
 *    virtual void    copy(Object&, const Object&) const =0;
 *  };
 *  \endcode
 *
 *  The purpose of the allocators is to provide factory methods to create and clone new types of 
 *  objects derived from Open BEAGLE constituents. With such mechanism, any user could create new type 
 *  of objects that redefine the default one and use associated allocators that return pointers to 
 *  this new type of objects. This mechanism is similar and coherent with the \e Factory \e Method 
 *  design pattern. Usually, an allocator is used to allocate objects through their default 
 *  constructor and clones the objects by calling their copy constructor. An allocator can also copy 
 *  an existing object of a given type into an other. To simplify the task, a simple standard 
 *  parametrized allocator named Beagle::AllocatorT is defined to override the virtual method of the
 *  abstract class Beagle::Allocator. Like the smart pointers \c Handle type, each component of 
 *  Open BEAGLE has a nested allocator type called \c Alloc. The users are encouraged to define it 
 *  in their classes.
 *  \code
 *  class AnyClass : public SuperClass { 
 *  public:
 *    typedef PointerT<AnyClass,SuperClass::Handle>  Handle;
 *    typedef AllocatorT<AnyClass,SuperClass::Alloc> Alloc
 *  };
 *  \endcode
 *  However, the template Beagle::AllocatorT cannot be used to define an \c Alloc type for an 
 *  abstract type. The reason is that the method \c allocate and \c clone cannot be implemented 
 *  to instantiate object of the abstract allocated type. To solve this problem, another templated
 *  allocator type is implemented, Beagle::AbstractAllocT. This allocator does not define the methods 
 *  \c allocate and \c clone, but is usable in the same way than Beagle::AllocatorT as an allocator
 *  type for abstract types.
 *
 */


#ifndef Beagle_Allocator_hpp
#define Beagle_Allocator_hpp

#include "beagle/config.hpp"
#include "beagle/macros.hpp"
#include "beagle/Object.hpp"


namespace Beagle
{

// Forward declarations.
template <class T, class BaseType> class AbstractAllocT;
template <class T, class BaseType> class PointerT;
template <class T, class BaseType> class ContainerT;

/*!
 *  \class Allocator beagle/Allocator.hpp "beagle/Allocator.hpp"
 *  \brief Basic Beagle allocator class.
 *  \ingroup OOF
 *  \ingroup Allocs
 */
class Allocator : public Object
{

public:

	//! Allocator allocator type.
	typedef AbstractAllocT<Allocator,Object::Alloc> Alloc;
	//! Allocator handle type.
	typedef PointerT<Allocator,Object::Handle> Handle;
	//! Allocator bag type.
	typedef ContainerT<Allocator,Object::Bag> Bag;

	Allocator()
	{ }
	virtual ~Allocator()
	{ }

	virtual Object* allocate() const;
	virtual Object* clone(const Object& inOriginal) const;
	virtual void    copy(Object& outCopy, const Object& inOriginal) const;

};

}

#endif // Beagle_Allocator_hpp

