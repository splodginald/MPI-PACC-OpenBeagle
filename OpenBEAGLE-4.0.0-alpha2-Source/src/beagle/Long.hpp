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
 *  \file   beagle/Long.hpp
 *  \brief  Definition of the type Long and related operators.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.9 $
 *  $Date: 2007/08/08 19:26:44 $
 */

#ifndef Beagle_Long_hpp
#define Beagle_Long_hpp

#include "beagle/config.hpp"
#include "beagle/macros.hpp"
#include "beagle/WrapperT.hpp"
#include "beagle/ArrayT.hpp"


namespace Beagle
{

/*!
 *  \brief Beagle wrapper of the atomic long type.
 *  \ingroup Adapt
 */
typedef WrapperT< long >
Long;

/*!
 *  \brief Beagle array of the atomic long type.
 *  \ingroup Adapt
 */
typedef ArrayT< long >
LongArray;

/*!
 *  \brief Evaluate absolute value of a Beagle::Long.
 *  \param inValue Long to evaluate the absolute value.
 *  \return Absolute value of the input.
 *  \ingroup Adapt
 */
template <>
inline Long absolute(const Long& inValue)
{
	Beagle_StackTraceBeginM();
	return Long(std::abs(inValue.getWrappedValue()));
	Beagle_StackTraceEndM("Long absolute(const Long& inValue)");
}

}


/*!
 *  \brief  Test whether an long is less than another.
 *  \param  inLeftLong  Left long compared.
 *  \param  inRightLong Right long compared.
 *  \return True if left long is less than the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the function isLess of Beagle::Long.
 */
inline bool operator<(const Beagle::Long& inLeftLong, const Beagle::Long& inRightLong)
{
	Beagle_StackTraceBeginM();
	return inLeftLong.isLess(inRightLong);
	Beagle_StackTraceEndM("bool operator<(const Long& inLeftLong, const Long& inRightLong)");
}


/*!
 *  \brief  Test whether an long is less than, or equal to another.
 *  \param  inLeftLong  Left long compared.
 *  \param  inRightLong Right long compared.
 *  \return True if left long is less than, or equal to the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the functions isLess and isEqual of Beagle::Long.
 */
inline bool operator<=(const Beagle::Long& inLeftLong, const Beagle::Long& inRightLong)
{
	Beagle_StackTraceBeginM();
	return ( inLeftLong.isLess(inRightLong) || inLeftLong.isEqual(inRightLong) );
	Beagle_StackTraceEndM("bool operator<=(const Long& inLeftLong, const Long& inRightLong)");
}


/*!
 *  \brief  Test whether an long is more than another.
 *  \param  inLeftLong  Left long compared.
 *  \param  inRightLong Right long compared.
 *  \return True if left long is more than the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the function isLess of Beagle::Long.
 */
inline bool operator>(const Beagle::Long& inLeftLong, const Beagle::Long& inRightLong)
{
	Beagle_StackTraceBeginM();
	return inRightLong.isLess(inLeftLong);
	Beagle_StackTraceEndM("bool operator>(const Long& inLeftLong, const Long& inRightLong)");
}


/*!
 *  \brief  Test whether an long is more than, or equal to another.
 *  \param  inLeftLong  Left long compared.
 *  \param  inRightLong Right long compared.
 *  \return True if left long is more than, or equal to the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the functions isLess and isEqual of Beagle::Long.
 */
inline bool operator>=(const Beagle::Long& inLeftLong, const Beagle::Long& inRightLong)
{
	Beagle_StackTraceBeginM();
	return ( inRightLong.isLess(inLeftLong) || inLeftLong.isEqual(inRightLong) );
	Beagle_StackTraceEndM("bool operator>=(const Long& inLeftLong, const Long& inRightLong)");
}


/*!
 *  \brief  Test whether an long is equal to another.
 *  \param  inLeftLong  Left long compared.
 *  \param  inRightLong Right long compared.
 *  \return True if left long is equal to the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the function isEqual of Beagle::Long.
 */
inline bool operator==(const Beagle::Long& inLeftLong, const Beagle::Long& inRightLong)
{
	Beagle_StackTraceBeginM();
	return inLeftLong.isEqual(inRightLong);
	Beagle_StackTraceEndM("bool operator==(const Long& inLeftLong, const Long& inRightLong)");
}


/*!
 *  \brief  Test whether an long is not equal to another.
 *  \param  inLeftLong  Left long compared.
 *  \param  inRightLong Right long compared.
 *  \return True if left long is not equal to the right one, false if it is.
 *  \par Note:
 *    The operator is defined relatively to the function isEqual of Beagle::Long.
 */
inline bool operator!=(const Beagle::Long& inLeftLong, const Beagle::Long& inRightLong)
{
	Beagle_StackTraceBeginM();
	return ( inLeftLong.isEqual(inRightLong) == false);
	Beagle_StackTraceEndM("bool operator!=(const Long& inLeftLong, const Long& inRightLong)");
}


/*!
 *  \brief Compare equality of a Long with a long.
 *  \param inLeftLong Left value to compare.
 *  \param inRightLong Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator==(const Beagle::Long& inLeftLong, long inRightLong)
{
	Beagle_StackTraceBeginM();
	return inLeftLong.getWrappedValue() == inRightLong;
	Beagle_StackTraceEndM("bool operator==(const Long& inLeftLong, long inRightLong)");
}


/*!
 *  \brief Compare inequality of a Long with a long.
 *  \param inLeftLong Left value to compare.
 *  \param inRightLong Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator!=(const Beagle::Long& inLeftLong, long inRightLong)
{
	Beagle_StackTraceBeginM();
	return inLeftLong.getWrappedValue() != inRightLong;
	Beagle_StackTraceEndM("bool operator!=(const Long& inLeftLong, long inRightLong)");
}


/*!
 *  \brief Test if a Long is < than a long.
 *  \param inLeftLong Left value to compare.
 *  \param inRightLong Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator<(const Beagle::Long& inLeftLong, long inRightLong)
{
	Beagle_StackTraceBeginM();
	return inLeftLong.getWrappedValue() < inRightLong;
	Beagle_StackTraceEndM("bool operator<(const Long& inLeftLong, long inRightLong)");
}


/*!
 *  \brief Test if a Long is <= than a long.
 *  \param inLeftLong Left value to compare.
 *  \param inRightLong Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator<=(const Beagle::Long& inLeftLong, long inRightLong)
{
	Beagle_StackTraceBeginM();
	return inLeftLong.getWrappedValue() <= inRightLong;
	Beagle_StackTraceEndM("bool operator<=(const Long& inLeftLong, long inRightLong)");
}


/*!
 *  \brief Test if a Long is > than a long.
 *  \param inLeftLong Left value to compare.
 *  \param inRightLong Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator>(const Beagle::Long& inLeftLong, long inRightLong)
{
	Beagle_StackTraceBeginM();
	return inLeftLong.getWrappedValue() > inRightLong;
	Beagle_StackTraceEndM("bool operator>(const Long& inLeftLong, long inRightLong)");
}


/*!
 *  \brief Test if a Long is >= than a long.
 *  \param inLeftLong Left value to compare.
 *  \param inRightLong Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator>=(const Beagle::Long& inLeftLong, long inRightLong)
{
	Beagle_StackTraceBeginM();
	return inLeftLong.getWrappedValue() >= inRightLong;
	Beagle_StackTraceEndM("bool operator>=(const Long& inLeftLong, long inRightLong)");
}


/*!
 *  \brief Increment a Long (prefix version).
 *  \param inLong Long to increment.
 *  \return Long incremented.
 */
inline
Beagle::Long& operator++(Beagle::Long& inLong)
{
	Beagle_StackTraceBeginM();
	inLong.getWrappedValue()++;
	return inLong;
	Beagle_StackTraceEndM("Long& operator++(Long& inLong)");
}


/*!
 *  \brief Increment a Long (postfix version).
 *  \param inLong Long to increment.
 *  \return Long before being incremented.
 */
inline
Beagle::Long operator++(Beagle::Long& inLong, int)
{
	Beagle_StackTraceBeginM();
	Beagle::Long lLong = inLong;
	inLong.getWrappedValue()++;
	return lLong;
	Beagle_StackTraceEndM("Long operator++(Long& inLong, int)");
}


/*!
 *  \brief Add two Long.
 *  \param inLeftLong Left value to add.
 *  \param inRightLong Right value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Long operator+(const Beagle::Long& inLeftLong, const Beagle::Long& inRightLong)
{
	Beagle_StackTraceBeginM();
	return inLeftLong.getWrappedValue() + inRightLong.getWrappedValue();
	Beagle_StackTraceEndM("Long operator+(const Long& inLeftLong, const Long& inRightLong)");
}


/*!
 *  \brief Add a Long with a long.
 *  \param inLeftLong Left value to add.
 *  \param inRightLong Right value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Long operator+(const Beagle::Long& inLeftLong, long inRightLong)
{
	Beagle_StackTraceBeginM();
	return inLeftLong.getWrappedValue() + inRightLong;
	Beagle_StackTraceEndM("Beagle::Long operator+(const Beagle::Long& inLeftLong, long inRightLong)");
}


/*!
 *  \brief Add a Long to a Long.
 *  \param inLeftLong Left value to which the right one is added.
 *  \param inRightLong Value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Long& operator+=(Beagle::Long& inLeftLong, const Beagle::Long& inRightLong)
{
	Beagle_StackTraceBeginM();
	inLeftLong.getWrappedValue() += inRightLong.getWrappedValue();
	return inLeftLong;
	Beagle_StackTraceEndM("Long& operator+=(Long& inLeftLong, const Long& inRightLong)");
}


/*!
 *  \brief Add a long to a Long.
 *  \param inLeftLong Left value to which the right one is added.
 *  \param inRightLong Value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Long& operator+=(Beagle::Long& inLeftLong, long inRightLong)
{
	Beagle_StackTraceBeginM();
	inLeftLong.getWrappedValue() += inRightLong;
	return inLeftLong;
	Beagle_StackTraceEndM("Long& operator+=(Long& inLeftLong, long inRightLong)");
}


/*!
 *  \brief Decrement a Long (prefix version).
 *  \param inLong Long to decrement.
 *  \return Long decremented.
 */
inline
Beagle::Long& operator--(Beagle::Long& inLong)
{
	Beagle_StackTraceBeginM();
	inLong.getWrappedValue()--;
	return inLong;
	Beagle_StackTraceEndM("Long& operator--(Long& inLong)");
}


/*!
 *  \brief Decrement a Long (postfix version).
 *  \param inLong Long to decrement.
 *  \return Long before being decremented.
 */
inline
Beagle::Long operator--(Beagle::Long& inLong, int)
{
	Beagle_StackTraceBeginM();
	Beagle::Long lLong = inLong;
	inLong.getWrappedValue()--;
	return lLong;
	Beagle_StackTraceEndM("Long operator--(Long& inLong, int)");
}



/*!
 *  \brief Subtract two Long.
 *  \param inLeftLong Left value to subtract.
 *  \param inRightLong Right value to subtract.
 *  \return Result of the subtract.
 */
inline
Beagle::Long operator-(const Beagle::Long& inLeftLong, const Beagle::Long& inRightLong)
{
	Beagle_StackTraceBeginM();
	return inLeftLong.getWrappedValue() - inRightLong.getWrappedValue();
	Beagle_StackTraceEndM("Long operator-(const Long& inLeftLong, const Long& inRightLong)");
}


/*!
 *  \brief Subtract a long from a Long.
 *  \param inLeftLong Left value to subtract.
 *  \param inRightLong Right value to subtract.
 *  \return Result of the subtract.
 */
inline
Beagle::Long operator-(const Beagle::Long& inLeftLong, long inRightLong)
{
	Beagle_StackTraceBeginM();
	return inLeftLong.getWrappedValue() - inRightLong;
	Beagle_StackTraceEndM("Long operator-(const Long& inLeftLong, long inRightLong)");
}


/*!
 *  \brief Subtract a Long from a Long.
 *  \param inLeftLong Left value from which the right long is subtracted.
 *  \param inRightLong Value to subtract.
 *  \return Result of the subtraction.
 */
inline
Beagle::Long& operator-=(Beagle::Long& inLeftLong, const Beagle::Long& inRightLong)
{
	Beagle_StackTraceBeginM();
	inLeftLong.getWrappedValue() -= inRightLong.getWrappedValue();
	return inLeftLong;
	Beagle_StackTraceEndM("Long& operator-=(Long& inLeftLong, const Long& inRightLong)");
}


/*!
 *  \brief Subtract a long from a Long.
 *  \param inLeftLong Left value from which the right long is subtracted.
 *  \param inRightLong Value to subtract.
 *  \return Result of the subtraction.
 */
inline
Beagle::Long& operator-=(Beagle::Long& inLeftLong, long inRightLong)
{
	Beagle_StackTraceBeginM();
	inLeftLong.getWrappedValue() -= inRightLong;
	return inLeftLong;
	Beagle_StackTraceEndM("Long& operator-=(Long& inLeftLong, long inRightLong)");
}


/*!
 *  \brief Multiply two Long.
 *  \param inLeftLong Left value to multiply.
 *  \param inRightLong Right value to multiply.
 *  \return Result of the multiply.
 */
inline
Beagle::Long operator*(const Beagle::Long& inLeftLong, const Beagle::Long& inRightLong)
{
	Beagle_StackTraceBeginM();
	return inLeftLong.getWrappedValue() * inRightLong.getWrappedValue();
	Beagle_StackTraceEndM("Long operator*(const Long& inLeftLong, const Long& inRightLong)");
}


/*!
 *  \brief Multiply a Long with a long.
 *  \param inLeftLong Left value to multiply.
 *  \param inRightLong Right value to multiply.
 *  \return Result of the multiply.
 */
inline
Beagle::Long operator*(const Beagle::Long& inLeftLong, long inRightLong)
{
	Beagle_StackTraceBeginM();
	return inLeftLong.getWrappedValue() * inRightLong;
	Beagle_StackTraceEndM("Long operator*(const Long& inLeftLong, long inRightLong)");
}


/*!
 *  \brief Multiply a Long with a Long.
 *  \param inLeftLong Left value to which the right long is multiplied.
 *  \param inRightLong Right value to multiply.
 *  \return Result of the multiplication.
 */
inline
Beagle::Long& operator*=(Beagle::Long& inLeftLong, const Beagle::Long& inRightLong)
{
	Beagle_StackTraceBeginM();
	inLeftLong.getWrappedValue() *= inRightLong.getWrappedValue();
	return inLeftLong;
	Beagle_StackTraceEndM("Long& operator*=(Long& inLeftLong, const Long& inRightLong)");
}


/*!
 *  \brief Multiply a Long with a long.
 *  \param inLeftLong Left value from which the right long is multiplied.
 *  \param inRightLong Right value to multiply.
 *  \return Result of the multiplication.
 */
inline
Beagle::Long& operator*=(Beagle::Long& inLeftLong, long inRightLong)
{
	Beagle_StackTraceBeginM();
	inLeftLong.getWrappedValue() *= inRightLong;
	return inLeftLong;
	Beagle_StackTraceEndM("Long& operator*=(Long& inLeftLong, long inRightLong)");
}


/*!
 *  \brief Divide two Long.
 *  \param inLeftLong Left value to divide.
 *  \param inRightLong Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::Long operator/(const Beagle::Long& inLeftLong, const Beagle::Long& inRightLong)
{
	Beagle_StackTraceBeginM();
	return inLeftLong.getWrappedValue() / inRightLong.getWrappedValue();
	Beagle_StackTraceEndM("Long operator/(const Long& inLeftLong, const Long& inRightLong)");
}


/*!
 *  \brief Divide a Long with a long.
 *  \param inLeftLong Left value to divide.
 *  \param inRightLong Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::Long operator/(const Beagle::Long& inLeftLong, long inRightLong)
{
	Beagle_StackTraceBeginM();
	return inLeftLong.getWrappedValue() / inRightLong;
	Beagle_StackTraceEndM("Long operator/(const Long& inLeftLong, long inRightLong)");
}


/*!
 *  \brief Divide a Long with a Long.
 *  \param inLeftLong Left value to which the right long is divided.
 *  \param inRightLong Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::Long& operator/=(Beagle::Long& inLeftLong, const Beagle::Long& inRightLong)
{
	Beagle_StackTraceBeginM();
	inLeftLong.getWrappedValue() /= inRightLong.getWrappedValue();
	return inLeftLong;
	Beagle_StackTraceEndM("Long& operator/=(Long& inLeftLong, const Long& inRightLong)");
}


/*!
 *  \brief Divide a Long with a long.
 *  \param inLeftLong Left value from which the right long is divided.
 *  \param inRightLong Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::Long operator/=(Beagle::Long& inLeftLong, long inRightLong)
{
	Beagle_StackTraceBeginM();
	inLeftLong.getWrappedValue() /= inRightLong;
	return inLeftLong;
	Beagle_StackTraceEndM("Long operator/=(Long& inLeftLong, long inRightLong)");
}


#endif // Beagle_Long_hpp



