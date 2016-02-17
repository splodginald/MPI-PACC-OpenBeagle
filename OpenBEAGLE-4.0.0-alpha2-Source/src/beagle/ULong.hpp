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
 *  \file   beagle/ULong.hpp
 *  \brief  Definition of the type ULong and related operators.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.8 $
 *  $Date: 2007/08/08 19:26:45 $
 */

#ifndef Beagle_ULong_hpp
#define Beagle_ULong_hpp

#include "beagle/config.hpp"
#include "beagle/macros.hpp"
#include "beagle/WrapperT.hpp"
#include "beagle/ArrayT.hpp"


namespace Beagle
{

/*!
 *  \brief Beagle wrapper of the atomic unsigned long type.
 *  \ingroup Adapt
 */
typedef WrapperT< unsigned long >
ULong;

/*!
 *  \brief Beagle array of the atomic unsigned long type.
 *  \ingroup Adapt
 */
typedef ArrayT< unsigned long >
ULongArray;

}


/*!
 *  \brief  Test whether an unsigned long is less than another.
 *  \param  inLeftULong  Left unsigned long compared.
 *  \param  inRightULong Right unsigned long compared.
 *  \return True if left unsigned long is less than the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the function isLess of Beagle::ULong.
 */
inline bool operator<(const Beagle::ULong& inLeftULong, const Beagle::ULong& inRightULong)
{
	Beagle_StackTraceBeginM();
	return inLeftULong.isLess(inRightULong);
	Beagle_StackTraceEndM("bool operator<(const ULong& inLeftULong, const ULong& inRightULong)");
}


/*!
 *  \brief  Test whether an unsigned long is less than, or equal to another.
 *  \param  inLeftULong  Left unsigned long compared.
 *  \param  inRightULong Right unsigned long compared.
 *  \return True if left unsigned long is less than, or equal to the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the functions isLess and isEqual of Beagle::ULong.
 */
inline bool operator<=(const Beagle::ULong& inLeftULong, const Beagle::ULong& inRightULong)
{
	Beagle_StackTraceBeginM();
	return ( inLeftULong.isLess(inRightULong) || inLeftULong.isEqual(inRightULong) );
	Beagle_StackTraceEndM("bool operator<=(const ULong& inLeftULong, const ULong& inRightULong)");
}


/*!
 *  \brief  Test whether an unsigned long is more than another.
 *  \param  inLeftULong  Left unsigned long compared.
 *  \param  inRightULong Right unsigned long compared.
 *  \return True if left unsigned long is more than the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the function isLess of Beagle::ULong.
 */
inline bool operator>(const Beagle::ULong& inLeftULong, const Beagle::ULong& inRightULong)
{
	Beagle_StackTraceBeginM();
	return inRightULong.isLess(inLeftULong);
	Beagle_StackTraceEndM("bool operator>(const ULong& inLeftULong, const ULong& inRightULong)");
}


/*!
 *  \brief  Test whether an unsigned long is more than, or equal to another.
 *  \param  inLeftULong  Left unsigned long compared.
 *  \param  inRightULong Right unsigned long compared.
 *  \return True if left unsigned long is more than, or equal to the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the functions isLess and isEqual of Beagle::ULong.
 */
inline bool operator>=(const Beagle::ULong& inLeftULong, const Beagle::ULong& inRightULong)
{
	Beagle_StackTraceBeginM();
	return ( inRightULong.isLess(inLeftULong) || inLeftULong.isEqual(inRightULong) );
	Beagle_StackTraceEndM("bool operator>=(const ULong& inLeftULong, const ULong& inRightULong)");
}


/*!
 *  \brief  Test whether an unsigned long is equal to another.
 *  \param  inLeftULong  Left unsigned long compared.
 *  \param  inRightULong Right unsigned long compared.
 *  \return True if left unsigned long is equal to the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the function isEqual of Beagle::ULong.
 */
inline bool operator==(const Beagle::ULong& inLeftULong, const Beagle::ULong& inRightULong)
{
	Beagle_StackTraceBeginM();
	return inLeftULong.isEqual(inRightULong);
	Beagle_StackTraceEndM("bool operator==(const ULong& inLeftULong, const ULong& inRightULong)");
}


/*!
 *  \brief  Test whether an unsigned long is not equal to another.
 *  \param  inLeftULong  Left unsigned long compared.
 *  \param  inRightULong Right unsigned long compared.
 *  \return True if left unsigned long is not equal to the right one, false if it is.
 *  \par Note:
 *    The operator is defined relatively to the function isEqual of Beagle::ULong.
 */
inline bool operator!=(const Beagle::ULong& inLeftULong, const Beagle::ULong& inRightULong)
{
	Beagle_StackTraceBeginM();
	return ( inLeftULong.isEqual(inRightULong) == false);
	Beagle_StackTraceEndM("bool operator!=(const ULong& inLeftULong, const ULong& inRightULong)");
}


/*!
 *  \brief Compare equality of a ULong with a unsigned long.
 *  \param inLeftULong Left value to compare.
 *  \param inRightULong Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator==(const Beagle::ULong& inLeftULong, unsigned long inRightULong)
{
	Beagle_StackTraceBeginM();
	return inLeftULong.getWrappedValue() == inRightULong;
	Beagle_StackTraceEndM("bool operator==(const ULong& inLeftULong, unsigned long inRightULong)");
}


/*!
 *  \brief Compare inequality of a ULong with a unsigned long.
 *  \param inLeftULong Left value to compare.
 *  \param inRightULong Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator!=(const Beagle::ULong& inLeftULong, unsigned long inRightULong)
{
	Beagle_StackTraceBeginM();
	return inLeftULong.getWrappedValue() != inRightULong;
	Beagle_StackTraceEndM("bool operator!=(const ULong& inLeftULong, unsigned long inRightULong)");
}


/*!
 *  \brief Test if a ULong is < than a unsigned long.
 *  \param inLeftULong Left value to compare.
 *  \param inRightULong Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator<(const Beagle::ULong& inLeftULong, unsigned long inRightULong)
{
	Beagle_StackTraceBeginM();
	return inLeftULong.getWrappedValue() < inRightULong;
	Beagle_StackTraceEndM("bool operator<(const ULong& inLeftULong, unsigned long inRightULong)");
}


/*!
 *  \brief Test if a ULong is <= than a unsigned long.
 *  \param inLeftULong Left value to compare.
 *  \param inRightULong Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator<=(const Beagle::ULong& inLeftULong, unsigned long inRightULong)
{
	Beagle_StackTraceBeginM();
	return inLeftULong.getWrappedValue() <= inRightULong;
	Beagle_StackTraceEndM("bool operator<=(const ULong& inLeftULong, unsigned long inRightULong)");
}


/*!
 *  \brief Test if a ULong is > than a unsigned long.
 *  \param inLeftULong Left value to compare.
 *  \param inRightULong Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator>(const Beagle::ULong& inLeftULong, unsigned long inRightULong)
{
	Beagle_StackTraceBeginM();
	return inLeftULong.getWrappedValue() > inRightULong;
	Beagle_StackTraceEndM("bool operator>(const ULong& inLeftULong, unsigned long inRightULong)");
}


/*!
 *  \brief Test if a ULong is >= than a unsigned long.
 *  \param inLeftULong Left value to compare.
 *  \param inRightULong Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator>=(const Beagle::ULong& inLeftULong, unsigned long inRightULong)
{
	Beagle_StackTraceBeginM();
	return inLeftULong.getWrappedValue() >= inRightULong;
	Beagle_StackTraceEndM("bool operator>=(const ULong& inLeftULong, unsigned long inRightULong)");
}


/*!
 *  \brief Increment a ULong (prefix version).
 *  \param inULong ULong to increment.
 *  \return ULong incremented.
 */
inline
Beagle::ULong& operator++(Beagle::ULong& inULong)
{
	Beagle_StackTraceBeginM();
	inULong.getWrappedValue()++;
	return inULong;
	Beagle_StackTraceEndM("ULong& operator++(ULong& inULong)");
}


/*!
 *  \brief Increment a ULong (postfix version).
 *  \param inULong ULong to increment.
 *  \return ULong before being incremented.
 */
inline
Beagle::ULong operator++(Beagle::ULong& inULong, int)
{
	Beagle_StackTraceBeginM();
	Beagle::ULong lULong = inULong;
	inULong.getWrappedValue()++;
	return lULong;
	Beagle_StackTraceEndM("ULong operator++(ULong& inULong, int)");
}


/*!
 *  \brief Add two ULong.
 *  \param inLeftULong Left value to add.
 *  \param inRightULong Right value to add.
 *  \return Result of the addition.
 */
inline
Beagle::ULong operator+(const Beagle::ULong& inLeftULong, const Beagle::ULong& inRightULong)
{
	Beagle_StackTraceBeginM();
	return inLeftULong.getWrappedValue() + inRightULong.getWrappedValue();
	Beagle_StackTraceEndM("ULong operator+(const ULong& inLeftULong, const ULong& inRightULong)");
}


/*!
 *  \brief Add a ULong with a unsigned long.
 *  \param inLeftULong Left value to add.
 *  \param inRightULong Right value to add.
 *  \return Result of the addition.
 */
inline
Beagle::ULong operator+(const Beagle::ULong& inLeftULong, unsigned long inRightULong)
{
	Beagle_StackTraceBeginM();
	return inLeftULong.getWrappedValue() + inRightULong;
	Beagle_StackTraceEndM("ULong operator+(const ULong& inLeftULong, unsigned long inRightULong)");
}


/*!
 *  \brief Add a ULong to a ULong.
 *  \param inLeftULong Left value to which the right one is added.
 *  \param inRightULong Value to add.
 *  \return Result of the addition.
 */
inline
Beagle::ULong& operator+=(Beagle::ULong& inLeftULong, const Beagle::ULong& inRightULong)
{
	Beagle_StackTraceBeginM();
	inLeftULong.getWrappedValue() += inRightULong.getWrappedValue();
	return inLeftULong;
	Beagle_StackTraceEndM("ULong& operator+=(ULong& inLeftULong, const ULong& inRightULong)");
}


/*!
 *  \brief Add a unsigned long to a ULong.
 *  \param inLeftULong Left value to which the right one is added.
 *  \param inRightULong Value to add.
 *  \return Result of the addition.
 */
inline
Beagle::ULong& operator+=(Beagle::ULong& inLeftULong, unsigned long inRightULong)
{
	Beagle_StackTraceBeginM();
	inLeftULong.getWrappedValue() += inRightULong;
	return inLeftULong;
	Beagle_StackTraceEndM("ULong& operator+=(ULong& inLeftULong, unsigned long inRightULong)");
}


/*!
 *  \brief Decrement a ULong (prefix version).
 *  \param inULong ULong to decrement.
 *  \return ULong decremented.
 */
inline
Beagle::ULong& operator--(Beagle::ULong& inULong)
{
	Beagle_StackTraceBeginM();
	inULong.getWrappedValue()--;
	return inULong;
	Beagle_StackTraceEndM("ULong& operator--(ULong& inULong)");
}


/*!
 *  \brief Decrement a ULong (postfix version).
 *  \param inULong ULong to decrement.
 *  \return ULong before being decremented.
 */
inline
Beagle::ULong operator--(Beagle::ULong& inULong, int)
{
	Beagle_StackTraceBeginM();
	Beagle::ULong lULong = inULong;
	inULong.getWrappedValue()--;
	return lULong;
	Beagle_StackTraceEndM("ULong operator--(ULong& inULong, int)");
}


/*!
 *  \brief Subtract two ULong.
 *  \param inLeftULong Left value to subtract.
 *  \param inRightULong Right value to subtract.
 *  \return Result of the subtract.
 */
inline
Beagle::ULong operator-(const Beagle::ULong& inLeftULong, const Beagle::ULong& inRightULong)
{
	Beagle_StackTraceBeginM();
	return inLeftULong.getWrappedValue() - inRightULong.getWrappedValue();
	Beagle_StackTraceEndM("ULong operator-(const ULong& inLeftULong, const ULong& inRightULong)");
}


/*!
 *  \brief Subtract a unsigned long from a ULong.
 *  \param inLeftULong Left value to subtract.
 *  \param inRightULong Right value to subtract.
 *  \return Result of the subtract.
 */
inline
Beagle::ULong operator-(const Beagle::ULong& inLeftULong, unsigned long inRightULong)
{
	Beagle_StackTraceBeginM();
	return inLeftULong.getWrappedValue() - inRightULong;
	Beagle_StackTraceEndM("ULong operator-(const ULong& inLeftULong, unsigned long inRightULong)");
}


/*!
 *  \brief Subtract a ULong from a ULong.
 *  \param inLeftULong Left value from which the right unsigned long is subtracted.
 *  \param inRightULong Value to subtract.
 *  \return Result of the subtraction.
 */
inline
Beagle::ULong& operator-=(Beagle::ULong& inLeftULong, const Beagle::ULong& inRightULong)
{
	Beagle_StackTraceBeginM();
	inLeftULong.getWrappedValue() -= inRightULong.getWrappedValue();
	return inLeftULong;
	Beagle_StackTraceEndM("ULong& operator-=(ULong& inLeftULong, const ULong& inRightULong)");
}


/*!
 *  \brief Subtract a unsigned long from a ULong.
 *  \param inLeftULong Left value from which the right unsigned long is subtracted.
 *  \param inRightULong Value to subtract.
 *  \return Result of the subtraction.
 */
inline
Beagle::ULong& operator-=(Beagle::ULong& inLeftULong, unsigned long inRightULong)
{
	Beagle_StackTraceBeginM();
	inLeftULong.getWrappedValue() -= inRightULong;
	return inLeftULong;
	Beagle_StackTraceEndM("ULong& operator-=(ULong& inLeftULong, unsigned long inRightULong)");
}


/*!
 *  \brief Multiply two ULong.
 *  \param inLeftULong Left value to multiply.
 *  \param inRightULong Right value to multiply.
 *  \return Result of the multiply.
 */
inline
Beagle::ULong operator*(const Beagle::ULong& inLeftULong, const Beagle::ULong& inRightULong)
{
	Beagle_StackTraceBeginM();
	return inLeftULong.getWrappedValue() * inRightULong.getWrappedValue();
	Beagle_StackTraceEndM("ULong operator*(const ULong& inLeftULong, const ULong& inRightULong)");
}


/*!
 *  \brief Multiply a ULong with a unsigned long.
 *  \param inLeftULong Left value to multiply.
 *  \param inRightULong Right value to multiply.
 *  \return Result of the multiply.
 */
inline
Beagle::ULong operator*(const Beagle::ULong& inLeftULong, unsigned long inRightULong)
{
	Beagle_StackTraceBeginM();
	return inLeftULong.getWrappedValue() * inRightULong;
	Beagle_StackTraceEndM("ULong operator*(const ULong& inLeftULong, unsigned long inRightULong)");
}


/*!
 *  \brief Multiply a ULong with a ULong.
 *  \param inLeftULong Left value to which the right unsigned long is multiplied.
 *  \param inRightULong Right value to multiply.
 *  \return Result of the multiplication.
 */
inline
Beagle::ULong& operator*=(Beagle::ULong& inLeftULong, const Beagle::ULong& inRightULong)
{
	Beagle_StackTraceBeginM();
	inLeftULong.getWrappedValue() *= inRightULong.getWrappedValue();
	return inLeftULong;
	Beagle_StackTraceEndM("ULong& operator*=(ULong& inLeftULong, const ULong& inRightULong)");
}


/*!
 *  \brief Multiply a ULong with a unsigned long.
 *  \param inLeftULong Left value from which the right unsigned long is multiplied.
 *  \param inRightULong Right value to multiply.
 *  \return Result of the multiplication.
 */
inline
Beagle::ULong& operator*=(Beagle::ULong& inLeftULong, unsigned long inRightULong)
{
	Beagle_StackTraceBeginM();
	inLeftULong.getWrappedValue() *= inRightULong;
	return inLeftULong;
	Beagle_StackTraceEndM("ULong& operator*=(ULong& inLeftULong, unsigned long inRightULong)");
}


/*!
 *  \brief Divide two ULong.
 *  \param inLeftULong Left value to divide.
 *  \param inRightULong Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::ULong operator/(const Beagle::ULong& inLeftULong, const Beagle::ULong& inRightULong)
{
	Beagle_StackTraceBeginM();
	return inLeftULong.getWrappedValue() / inRightULong.getWrappedValue();
	Beagle_StackTraceEndM("ULong operator/(const ULong& inLeftULong, const ULong& inRightULong)");
}


/*!
 *  \brief Divide a ULong with a unsigned long.
 *  \param inLeftULong Left value to divide.
 *  \param inRightULong Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::ULong operator/(const Beagle::ULong& inLeftULong, unsigned long inRightULong)
{
	Beagle_StackTraceBeginM();
	return inLeftULong.getWrappedValue() / inRightULong;
	Beagle_StackTraceEndM("ULong operator/(const ULong& inLeftULong, unsigned long inRightULong)");
}


/*!
 *  \brief Divide a ULong with a ULong.
 *  \param inLeftULong Left value to which the right unsigned long is divided.
 *  \param inRightULong Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::ULong& operator/=(Beagle::ULong& inLeftULong, const Beagle::ULong& inRightULong)
{
	Beagle_StackTraceBeginM();
	inLeftULong.getWrappedValue() /= inRightULong.getWrappedValue();
	return inLeftULong;
	Beagle_StackTraceEndM("ULong& operator/=(ULong& inLeftULong, const ULong& inRightULong)");
}


/*!
 *  \brief Divide a ULong with a unsigned long.
 *  \param inLeftULong Left value from which the right unsigned long is divided.
 *  \param inRightULong Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::ULong operator/=(Beagle::ULong& inLeftULong, unsigned long inRightULong)
{
	Beagle_StackTraceBeginM();
	inLeftULong.getWrappedValue() /= inRightULong;
	return inLeftULong;
	Beagle_StackTraceEndM("ULong operator/=(ULong& inLeftULong, unsigned long inRightULong)");
}


#endif // Beagle_ULong_hpp



