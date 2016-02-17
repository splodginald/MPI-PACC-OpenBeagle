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
 *  \file   beagle/Short.hpp
 *  \brief  Definition of the type Short and related operators.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.9 $
 *  $Date: 2007/08/08 19:26:45 $
 */

#ifndef Beagle_Short_hpp
#define Beagle_Short_hpp

#include "beagle/config.hpp"
#include "beagle/macros.hpp"
#include "beagle/WrapperT.hpp"
#include "beagle/ArrayT.hpp"


namespace Beagle
{

/*!
 *  \brief Beagle wrapper of the atomic short type.
 *  \ingroup Adapt
 */
typedef WrapperT< short >
Short;

/*!
 *  \brief Beagle array of the atomic short type.
 *  \ingroup Adapt
 */
typedef ArrayT< short >
ShortArray;

/*!
 *  \brief Evaluate absolute value of a Beagle::Short.
 *  \param inValue Short to evaluate the absolute value.
 *  \return Absolute value of the input.
 *  \ingroup Adapt
 */
template <>
inline Short absolute(const Short& inValue)
{
	Beagle_StackTraceBeginM();
	return Short(std::abs(inValue.getWrappedValue()));
	Beagle_StackTraceEndM("Short absolute(const Short& inValue)");
}

}


/*!
 *  \brief  Test whether an short is less than another.
 *  \param  inLeftShort  Left short compared.
 *  \param  inRightShort Right short compared.
 *  \return True if left short is less than the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the function isLess of Beagle::Short.
 */
inline bool operator<(const Beagle::Short& inLeftShort, const Beagle::Short& inRightShort)
{
	Beagle_StackTraceBeginM();
	return inLeftShort.isLess(inRightShort);
	Beagle_StackTraceEndM("bool operator<(const Short& inLeftShort, const Short& inRightShort)");
}


/*!
 *  \brief  Test whether an short is less than, or equal to another.
 *  \param  inLeftShort  Left short compared.
 *  \param  inRightShort Right short compared.
 *  \return True if left short is less than, or equal to the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the functions isLess and isEqual of Beagle::Short.
 */
inline bool operator<=(const Beagle::Short& inLeftShort, const Beagle::Short& inRightShort)
{
	Beagle_StackTraceBeginM();
	return ( inLeftShort.isLess(inRightShort) || inLeftShort.isEqual(inRightShort) );
	Beagle_StackTraceEndM("bool operator<=(const Short& inLeftShort, const Short& inRightShort)");
}


/*!
 *  \brief  Test whether an short is more than another.
 *  \param  inLeftShort  Left short compared.
 *  \param  inRightShort Right short compared.
 *  \return True if left short is more than the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the function isLess of Beagle::Short.
 */
inline bool operator>(const Beagle::Short& inLeftShort, const Beagle::Short& inRightShort)
{
	Beagle_StackTraceBeginM();
	return inRightShort.isLess(inLeftShort);
	Beagle_StackTraceEndM("bool operator>(const Short& inLeftShort, const Short& inRightShort)");
}


/*!
 *  \brief  Test whether an short is more than, or equal to another.
 *  \param  inLeftShort  Left short compared.
 *  \param  inRightShort Right short compared.
 *  \return True if left short is more than, or equal to the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the functions isLess and isEqual of Beagle::Short.
 */
inline bool operator>=(const Beagle::Short& inLeftShort, const Beagle::Short& inRightShort)
{
	Beagle_StackTraceBeginM();
	return ( inRightShort.isLess(inLeftShort) || inLeftShort.isEqual(inRightShort) );
	Beagle_StackTraceEndM("bool operator>=(const Short& inLeftShort, const Short& inRightShort)");
}


/*!
 *  \brief  Test whether an short is equal to another.
 *  \param  inLeftShort  Left short compared.
 *  \param  inRightShort Right short compared.
 *  \return True if left short is equal to the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the function isEqual of Beagle::Short.
 */
inline bool operator==(const Beagle::Short& inLeftShort, const Beagle::Short& inRightShort)
{
	Beagle_StackTraceBeginM();
	return inLeftShort.isEqual(inRightShort);
	Beagle_StackTraceEndM("bool operator==(const Short& inLeftShort, const Short& inRightShort)");
}


/*!
 *  \brief  Test whether an short is not equal to another.
 *  \param  inLeftShort  Left short compared.
 *  \param  inRightShort Right short compared.
 *  \return True if left short is not equal to the right one, false if it is.
 *  \par Note:
 *    The operator is defined relatively to the function isEqual of Beagle::Short.
 */
inline bool operator!=(const Beagle::Short& inLeftShort, const Beagle::Short& inRightShort)
{
	Beagle_StackTraceBeginM();
	return ( inLeftShort.isEqual(inRightShort) == false);
	Beagle_StackTraceEndM("bool operator!=(const Short& inLeftShort, const Short& inRightShort)");
}


/*!
 *  \brief Compare equality of a Short with a short.
 *  \param inLeftShort Left value to compare.
 *  \param inRightShort Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator==(const Beagle::Short& inLeftShort, short inRightShort)
{
	Beagle_StackTraceBeginM();
	return inLeftShort.getWrappedValue() == inRightShort;
	Beagle_StackTraceEndM("bool operator==(const Short& inLeftShort, short inRightShort)");
}


/*!
 *  \brief Compare inequality of a Short with a short.
 *  \param inLeftShort Left value to compare.
 *  \param inRightShort Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator!=(const Beagle::Short& inLeftShort, short inRightShort)
{
	Beagle_StackTraceBeginM();
	return inLeftShort.getWrappedValue() != inRightShort;
	Beagle_StackTraceEndM("bool operator!=(const Short& inLeftShort, short inRightShort)");
}


/*!
 *  \brief Test if a Short is < than a short.
 *  \param inLeftShort Left value to compare.
 *  \param inRightShort Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator<(const Beagle::Short& inLeftShort, short inRightShort)
{
	Beagle_StackTraceBeginM();
	return inLeftShort.getWrappedValue() < inRightShort;
	Beagle_StackTraceEndM("bool operator<(const Short& inLeftShort, short inRightShort)");
}


/*!
 *  \brief Test if a Short is <= than a short.
 *  \param inLeftShort Left value to compare.
 *  \param inRightShort Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator<=(const Beagle::Short& inLeftShort, short inRightShort)
{
	Beagle_StackTraceBeginM();
	return inLeftShort.getWrappedValue() <= inRightShort;
	Beagle_StackTraceEndM("bool operator<=(const Short& inLeftShort, short inRightShort)");
}


/*!
 *  \brief Test if a Short is > than a short.
 *  \param inLeftShort Left value to compare.
 *  \param inRightShort Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator>(const Beagle::Short& inLeftShort, short inRightShort)
{
	Beagle_StackTraceBeginM();
	return inLeftShort.getWrappedValue() > inRightShort;
	Beagle_StackTraceEndM("bool operator>(const Short& inLeftShort, short inRightShort)");
}


/*!
 *  \brief Test if a Short is >= than a short.
 *  \param inLeftShort Left value to compare.
 *  \param inRightShort Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator>=(const Beagle::Short& inLeftShort, short inRightShort)
{
	Beagle_StackTraceBeginM();
	return inLeftShort.getWrappedValue() >= inRightShort;
	Beagle_StackTraceEndM("bool operator>=(const Short& inLeftShort, short inRightShort)");
}


/*!
 *  \brief Increment a Short (prefix version).
 *  \param inShort Short to increment.
 *  \return Short incremented.
 */
inline
Beagle::Short& operator++(Beagle::Short& inShort)
{
	Beagle_StackTraceBeginM();
	inShort.getWrappedValue()++;
	return inShort;
	Beagle_StackTraceEndM("Short& operator++(Short& inShort)");
}


/*!
 *  \brief Increment a Short (postfix version).
 *  \param inShort Short to increment.
 *  \return Short before being incremented.
 */
inline
Beagle::Short operator++(Beagle::Short& inShort, int)
{
	Beagle_StackTraceBeginM();
	Beagle::Short lShort = inShort;
	inShort.getWrappedValue()++;
	return lShort;
	Beagle_StackTraceEndM("Short operator++(Short& inShort, int)");
}


/*!
 *  \brief Add two Short.
 *  \param inLeftShort Left value to add.
 *  \param inRightShort Right value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Short operator+(const Beagle::Short& inLeftShort, const Beagle::Short& inRightShort)
{
	Beagle_StackTraceBeginM();
	return inLeftShort.getWrappedValue() + inRightShort.getWrappedValue();
	Beagle_StackTraceEndM("Short operator+(const Short& inLeftShort, const Short& inRightShort)");
}


/*!
 *  \brief Add a Short with a short.
 *  \param inLeftShort Left value to add.
 *  \param inRightShort Right value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Short operator+(const Beagle::Short& inLeftShort, short inRightShort)
{
	Beagle_StackTraceBeginM();
	return inLeftShort.getWrappedValue() + inRightShort;
	Beagle_StackTraceEndM("Short operator+(const Short& inLeftShort, short inRightShort)");
}


/*!
 *  \brief Add a Short to a Short.
 *  \param inLeftShort Left value to which the right one is added.
 *  \param inRightShort Value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Short& operator+=(Beagle::Short& inLeftShort, const Beagle::Short& inRightShort)
{
	Beagle_StackTraceBeginM();
	inLeftShort.getWrappedValue() += inRightShort.getWrappedValue();
	return inLeftShort;
	Beagle_StackTraceEndM("Short& operator+=(Short& inLeftShort, const Short& inRightShort)");
}


/*!
 *  \brief Add a short to a Short.
 *  \param inLeftShort Left value to which the right one is added.
 *  \param inRightShort Value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Short& operator+=(Beagle::Short& inLeftShort, short inRightShort)
{
	Beagle_StackTraceBeginM();
	inLeftShort.getWrappedValue() += inRightShort;
	return inLeftShort;
	Beagle_StackTraceEndM("Short& operator+=(Short& inLeftShort, short inRightShort)");
}


/*!
 *  \brief Decrement a Short (prefix version).
 *  \param inShort Short to decrement.
 *  \return Short decremented.
 */
inline
Beagle::Short& operator--(Beagle::Short& inShort)
{
	Beagle_StackTraceBeginM();
	inShort.getWrappedValue()--;
	return inShort;
	Beagle_StackTraceEndM("Short& operator--(Short& inShort)");
}


/*!
 *  \brief Decrement a Short (postfix version).
 *  \param inShort Short to decrement.
 *  \return Short before being decremented.
 */
inline
Beagle::Short operator--(Beagle::Short& inShort, int)
{
	Beagle_StackTraceBeginM();
	Beagle::Short lShort = inShort;
	inShort.getWrappedValue()--;
	return lShort;
	Beagle_StackTraceEndM("Short operator--(Short& inShort, int)");
}



/*!
 *  \brief Subtract two Short.
 *  \param inLeftShort Left value to subtract.
 *  \param inRightShort Right value to subtract.
 *  \return Result of the subtract.
 */
inline
Beagle::Short operator-(const Beagle::Short& inLeftShort, const Beagle::Short& inRightShort)
{
	Beagle_StackTraceBeginM();
	return inLeftShort.getWrappedValue() - inRightShort.getWrappedValue();
	Beagle_StackTraceEndM("Short operator-(const Short& inLeftShort, const Short& inRightShort)");
}


/*!
 *  \brief Subtract a short from a Short.
 *  \param inLeftShort Left value to subtract.
 *  \param inRightShort Right value to subtract.
 *  \return Result of the subtract.
 */
inline
Beagle::Short operator-(const Beagle::Short& inLeftShort, short inRightShort)
{
	Beagle_StackTraceBeginM();
	return inLeftShort.getWrappedValue() - inRightShort;
	Beagle_StackTraceEndM("Short operator-(const Short& inLeftShort, short inRightShort)");
}


/*!
 *  \brief Subtract a Short from a Short.
 *  \param inLeftShort Left value from which the right short is subtracted.
 *  \param inRightShort Value to subtract.
 *  \return Result of the subtraction.
 */
inline
Beagle::Short& operator-=(Beagle::Short& inLeftShort, const Beagle::Short& inRightShort)
{
	Beagle_StackTraceBeginM();
	inLeftShort.getWrappedValue() -= inRightShort.getWrappedValue();
	return inLeftShort;
	Beagle_StackTraceEndM("Short& operator-=(Short& inLeftShort, const Short& inRightShort)");
}


/*!
 *  \brief Subtract a short from a Short.
 *  \param inLeftShort Left value from which the right short is subtracted.
 *  \param inRightShort Value to subtract.
 *  \return Result of the subtraction.
 */
inline
Beagle::Short& operator-=(Beagle::Short& inLeftShort, short inRightShort)
{
	Beagle_StackTraceBeginM();
	inLeftShort.getWrappedValue() -= inRightShort;
	return inLeftShort;
	Beagle_StackTraceEndM("Short& operator-=(Short& inLeftShort, short inRightShort)");
}


/*!
 *  \brief Multiply two Short.
 *  \param inLeftShort Left value to multiply.
 *  \param inRightShort Right value to multiply.
 *  \return Result of the multiply.
 */
inline
Beagle::Short operator*(const Beagle::Short& inLeftShort, const Beagle::Short& inRightShort)
{
	Beagle_StackTraceBeginM();
	return inLeftShort.getWrappedValue() * inRightShort.getWrappedValue();
	Beagle_StackTraceEndM("Short operator*(const Short& inLeftShort, const Short& inRightShort)");
}


/*!
 *  \brief Multiply a Short with a short.
 *  \param inLeftShort Left value to multiply.
 *  \param inRightShort Right value to multiply.
 *  \return Result of the multiply.
 */
inline
Beagle::Short operator*(const Beagle::Short& inLeftShort, short inRightShort)
{
	Beagle_StackTraceBeginM();
	return inLeftShort.getWrappedValue() * inRightShort;
	Beagle_StackTraceEndM("Short operator*(const Short& inLeftShort, short inRightShort)");
}


/*!
 *  \brief Multiply a Short with a Short.
 *  \param inLeftShort Left value to which the right short is multiplied.
 *  \param inRightShort Right value to multiply.
 *  \return Result of the multiplication.
 */
inline
Beagle::Short& operator*=(Beagle::Short& inLeftShort, const Beagle::Short& inRightShort)
{
	Beagle_StackTraceBeginM();
	inLeftShort.getWrappedValue() *= inRightShort.getWrappedValue();
	return inLeftShort;
	Beagle_StackTraceEndM("Short& operator*=(Short& inLeftShort, const Short& inRightShort)");
}


/*!
 *  \brief Multiply a Short with a short.
 *  \param inLeftShort Left value from which the right short is multiplied.
 *  \param inRightShort Right value to multiply.
 *  \return Result of the multiplication.
 */
inline
Beagle::Short& operator*=(Beagle::Short& inLeftShort, short inRightShort)
{
	Beagle_StackTraceBeginM();
	inLeftShort.getWrappedValue() *= inRightShort;
	return inLeftShort;
	Beagle_StackTraceEndM("Short& operator*=(Short& inLeftShort, short inRightShort)");
}


/*!
 *  \brief Divide two Short.
 *  \param inLeftShort Left value to divide.
 *  \param inRightShort Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::Short operator/(const Beagle::Short& inLeftShort, const Beagle::Short& inRightShort)
{
	Beagle_StackTraceBeginM();
	return inLeftShort.getWrappedValue() / inRightShort.getWrappedValue();
	Beagle_StackTraceEndM("Short operator/(const Short& inLeftShort, const Short& inRightShort)");
}


/*!
 *  \brief Divide a Short with a short.
 *  \param inLeftShort Left value to divide.
 *  \param inRightShort Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::Short operator/(const Beagle::Short& inLeftShort, short inRightShort)
{
	Beagle_StackTraceBeginM();
	return inLeftShort.getWrappedValue() / inRightShort;
	Beagle_StackTraceEndM("Short operator/(const Short& inLeftShort, short inRightShort)");
}


/*!
 *  \brief Divide a Short with a Short.
 *  \param inLeftShort Left value to which the right short is divided.
 *  \param inRightShort Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::Short& operator/=(Beagle::Short& inLeftShort, const Beagle::Short& inRightShort)
{
	Beagle_StackTraceBeginM();
	inLeftShort.getWrappedValue() /= inRightShort.getWrappedValue();
	return inLeftShort;
	Beagle_StackTraceEndM("Short& operator/=(Short& inLeftShort, const Short& inRightShort)");
}


/*!
 *  \brief Divide a Short with a short.
 *  \param inLeftShort Left value from which the right short is divided.
 *  \param inRightShort Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::Short operator/=(Beagle::Short& inLeftShort, short inRightShort)
{
	Beagle_StackTraceBeginM();
	inLeftShort.getWrappedValue() /= inRightShort;
	return inLeftShort;
	Beagle_StackTraceEndM("Short operator/=(Short& inLeftShort, short inRightShort)");
}


#endif // Beagle_Short_hpp



