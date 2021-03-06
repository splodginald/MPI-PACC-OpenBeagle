/*
 *  Open BEAGLE
 *  Copyright (C) 2001-2007 by Christian Gagn�and Marc Parizeau
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
 *  \file   beagle/src/InternalException.cpp
 *  \brief  Implementation of class InternalException.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.10 $
 *  $Date: 2007/08/08 19:26:46 $
 */

#include "beagle/Beagle.hpp"

using namespace Beagle;


/*!
 *  \brief Construct a new InternalException using data given.
 *  \param inMessage    Message related to the exception.
 *  \param inFileName   File name where the exception is detected (throwed).
 *  \param inLineNumber Line number where the exception is detected (throwed).
 */
InternalException::InternalException(std::string inMessage,
                                     std::string inFileName,
                                     unsigned int inLineNumber) :
		TargetedException(inMessage,inFileName,inLineNumber)
{ }


/*!
 *  \brief  Get the name of the exception.
 *  \return Name of the exception.
 */
const char* InternalException::getExceptionName() const throw()
{
	return "Beagle::InternalException";
}

