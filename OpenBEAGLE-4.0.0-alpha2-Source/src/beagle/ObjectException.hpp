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
 *  \file   beagle/ObjectException.hpp
 *  \brief  Definition of class ObjectException.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.10 $
 *  $Date: 2007/08/08 19:26:45 $
 */

#ifndef Beagle_ObjectException_hpp
#define Beagle_ObjectException_hpp

#include "beagle/config.hpp"
#include "beagle/macros.hpp"
#include "beagle/Object.hpp"
#include "beagle/TargetedException.hpp"


/*!
 *  \def   Beagle_ObjectExceptionM
 *  \brief Construct a Beagle::ObjectException using the message given.
 *  \param MESS Exception message.
 *  \ingroup Except
 */
#define Beagle_ObjectExceptionM(MESS) \
  Beagle::ObjectException((*this),MESS,__FILE__,__LINE__)


namespace Beagle
{

// Forward declarations.
template <class T, class BaseType> class AllocatorT;
template <class T, class BaseType> class PointerT;
template <class T, class BaseType> class ContainerT;

/*!
 *  \class ObjectException beagle/ObjectException.hpp "beagle/ObjectException.hpp"
 *  \brief Beagle exception relative to a erroneous state of an Object.
 *  \ingroup OOF
 *  \ingroup Except
 */
class ObjectException : public TargetedException
{

public:

	//! ObjectException allocator type.
	typedef AllocatorT<ObjectException,TargetedException::Alloc>
	Alloc;
	//! ObjectException handle type.
	typedef PointerT<ObjectException,TargetedException::Handle>
	Handle;
	//! ObjectException bag type.
	typedef ContainerT<ObjectException,TargetedException::Bag>
	Bag;

	explicit ObjectException(const Object& inObject,
	                         std::string   inMessage="",
	                         std::string   inFileName="",
	                         unsigned int  inLineNumber=0);
	virtual ~ObjectException() throw()
	{ }

	virtual void        explain(std::ostream& ioES=std::cerr) throw();
	virtual const char* getExceptionName() const throw();
	void        setObjectState(const Object& inObject);

	/*!
	 *  \brief Getting the name of the object related to the exception.
	 *  \return Name of the object related to the exception.
	 */
	inline const std::string& getObjectName() const throw()
	{
		return mObjectName;
	}

	/*!
	 *  \brief Getting the value of the reference counter of the object related to the exception.
	 *  \return Reference counter value of the object related to the exception.
	 */
	inline unsigned int getObjectRefCounter() const throw()
	{
		return mObjectRefCounter;
	}

	/*!
	 *  \brief Getting the RTTI type name of the object related to the exception.
	 *  \return RTTI type name of the object related to the exception.
	 *  \warning The RTTI name of the Object is determined only when the preprocessing flag
	 *    BEAGLE_HAVE_RTTI is defined.
	 */
	inline const std::string& getObjectTypeName() const throw()
	{
		return mObjectTypeName;
	}

	/*!
	 *  \brief Getting the serialization of the object related to the exception.
	 *  \return String containing the serialization of the object related to the exception.
	 */
	inline const std::string& getSerializedObject() const throw()
	{
		return mSerializedObject;
	}

protected:
	ObjectException()
	{ }            //!< Prohibited constructor!

private:

	std::string  mObjectName;        //!< Name of the erroneous Object.
	std::string  mObjectTypeName;    //!< RTTI name of the erroneous Object.
	std::string  mSerializedObject;  //!< Serialize representation of the erroneous Object.
	unsigned int mObjectRefCounter;  //!< Value of the reference counter of the Object.

};

}

#endif // Beagle_ObjectException_hpp
