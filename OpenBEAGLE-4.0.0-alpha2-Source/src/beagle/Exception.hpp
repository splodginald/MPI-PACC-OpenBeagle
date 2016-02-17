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
 *  \file   beagle/Exception.hpp
 *  \brief  Definition of class Exception.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.14 $
 *  $Date: 2007/08/17 18:09:12 $
 */

/*!
 *  \defgroup Except Exceptions
 *  \ingroup OOF
 *  \brief Open BEAGLE custom exceptions, part of the Object Oriented Foundations.
 *
 *  Open BEAGLE integrates the C++ exceptions mechanism. Keeping it
 *  object oriented (OO), an hierarchy of exceptions is defined. At
 *  the top is the abstract exception superclass, Beagle::Exception,
 *  which is inherited by every other Open BEAGLE exception
 *  class. This top class inherits is derived from the standard
 *  exception class (\c std::exception), which allows Open BEAGLE
 *  exceptions to be caught in a simple \c catch(std::exception&)
 *  expression.
 *
 *  A Java-like trace mechanism exists for exceptions that are derived
 *  from Beagle::Exception.  When such an exception is caught, the
 *  Beagle::Exception::explain() method displays the call-stack at the
 *  point the exception was thrown.  In order to acheive this it is
 *  necessary to call to macros from every function or method to be
 *  included in the trace.  The first macro \c
 *  Beagle_StackTraceBeginM() should appear at the top of your
 *  function or method.  The second macro \c Beagle_StackTraceEndM()
 *  should appear at the end or your function or method with the
 *  function or method's specification.  Here is an example: \code
 *
 *  void myFunction() {
 *    Beagle_StackTraceBeginM();
 *    std::cout << "This is my function." << std::endl;
 *    Beagle_StackTraceEndM("void myFunction()");
 *  } \endcode
 *
 *  If your function or method has an all-inclusive try...catch block,
 *  the macros should appear within that block.
 *
 */


#ifndef Beagle_Exception_hpp
#define Beagle_Exception_hpp

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "beagle/config.hpp"
#include "beagle/macros.hpp"
#include "beagle/Object.hpp"


/*!
 *  \def   Beagle_StackTraceBeginM
 *  \brief Used to declare the start of a section of code that will
 *    appear in an exception's stack trace
 *  \ingroup Except
 */
#ifndef BEAGLE_NDEBUG
#define Beagle_StackTraceBeginM() \
  try {
#else // BEAGLE_NDEBUG
#define Beagle_StackTraceBeginM()
#endif // BEAGLE_NDEBUG


/*!
 *  \def   Beagle_StackTraceEndM
 *  \brief Used to declare the end of a section of code that will
 *    appear in an exception's stack trace
 *  \param NAME Function/method name that is traced.
 *  \ingroup Except
 */
#ifndef BEAGLE_NDEBUG
#define Beagle_StackTraceEndM(NAME) \
  } \
  catch (Beagle::Exception& inException) { \
    inException.pushStackTrace(NAME,__FILE__,__LINE__); \
    throw; \
  }
#else // BEAGLE_NDEBUG
#define Beagle_StackTraceEndM(NAME)
#endif // BEAGLE_NDEBUG


namespace Beagle
{

// Forward declarations
template <class T, class BaseType> class AbstractAllocT;
template <class T, class BaseType> class PointerT;
template <class T, class BaseType> class ContainerT;

/*!
 *  \class Exception beagle/Exception.hpp "beagle/Exception.hpp"
 *  \brief Basic Beagle exception class.
 *  \ingroup OOF
 *  \ingroup Except
 */
class Exception : public Object, public std::exception
{

public:

	//! Exception allocator type.
	typedef AbstractAllocT<Exception,Object::Alloc>
	Alloc;
	//! Exception handle type.
	typedef PointerT<Exception,Object::Handle>
	Handle;
	//! Exception bag type.
	typedef ContainerT<Exception,Object::Bag>
	Bag;

	explicit Exception(std::string inMessage="");
	virtual ~Exception() throw()
	{ }

	virtual void explain(std::ostream& ioES=std::cerr) throw();
	void terminate(std::ostream& ioES=std::cerr) throw();
	virtual const char* what() const throw();

	/*!
	 *  \brief  Getting the actual name of a Beagle exception.
	 *  \return Exception name.
	 */
	virtual const char* getExceptionName() const throw() =0;

	/*!
	 *  \brief  Return error message of the actual exception.
	 *  \return Error message.
	 */
	inline std::string getMessage() const throw()
	{
		return mMessage;
	}

	/*!
	 *  \brief  Add an item to the exception's stack trace.
	 *  \param inName Name of the method/function traced.
	 *  \param inFilename Source filename where stack tracing is done.
	 *  \param inLineNumber Line number in source where stack tracing is done.
	 */
	inline void pushStackTrace(const char* inName, const char* inFilename, unsigned int inLineNumber)
	{
		mStackTrace.push_back(StackTraceItem(inName,inFilename,inLineNumber));
	}

	/*!
	 *  \brief Set error message of actual exception.
	 *  \param inMessage Value of error message.
	 */
	inline void setMessage(std::string inMessage)
	{
		mMessage = inMessage;
	}

protected:

	/*!
	 *  \brief Internal struct to store stack trace elements.
	 */
	struct StackTraceItem
	{
		std::string  mName;        //!< Name of the method/function traced.
		std::string  mFilename;    //!< Source filename where stack tracing is done.
		unsigned int mLineNumber;  //!< Line number in source where stack tracing is done.

		/*!
		 *  \brief Construct a stack trace item.
		 *  \param inName Name of the method/function traced.
		 *  \param inFilename Source filename where stack tracing is done.
		 *  \param inLineNumber Line number in source where stack tracing is done.
		 */
		explicit StackTraceItem(const char* inName="",
		                        const char* inFilename="",
		                        unsigned int inLineNumber=0) :
				mName(inName), mFilename(inFilename), mLineNumber(inLineNumber)
		{}
	};

	std::vector< StackTraceItem > mStackTrace;  //!< Stack trace of the calls
	std::string                   mMessage;     //!< Exception message describing the abnormal situation.

};

}

#endif // Beagle_Exception_hpp
