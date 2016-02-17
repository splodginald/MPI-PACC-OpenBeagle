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
 *  \file   beagle/Int.hpp
 *  \brief  Definition of the type Int and related operators.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.9 $
 *  $Date: 2007/08/08 19:26:44 $
 */

#ifndef Beagle_Int_hpp
#define Beagle_Int_hpp

#include "beagle/config.hpp"
#include "beagle/macros.hpp"
#include "beagle/WrapperT.hpp"
#include "beagle/ArrayT.hpp"


namespace Beagle
{

/*!
 *  \brief Beagle wrapper of the atomic int type.
 *  \ingroup Adapt
 */
typedef WrapperT< int >
Int;

/*!
 *  \brief Beagle array of the atomic int type.
 *  \ingroup Adapt
 */
typedef ArrayT< int >
IntArray;

/*!
 *  \brief Evaluate absolute value of a Beagle::Int.
 *  \param inValue Int to evaluate the absolute value.
 *  \return Absolute value of the input.
 *  \ingroup Adapt
 */
template <>
inline Int absolute(const Int& inValue)
{
	Beagle_StackTraceBeginM();
	return Int(std::abs(inValue.getWrappedValue()));
	Beagle_StackTraceEndM("Int absolute(const Int& inValue)");
}

}


/*!
 *  \brief     Test whether an int is less than another.
 *  \param     inLeftInt  Left int compared.
 *  \param     inRightInt Right int compared.
 *  \return    True if left int is less than the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the function isLess of Beagle::Int.
 */
inline bool operator<(const Beagle::Int& inLeftInt, const Beagle::Int& inRightInt)
{
	Beagle_StackTraceBeginM();
	return inLeftInt.isLess(inRightInt);
	Beagle_StackTraceEndM("bool operator<(const Int& inLeftInt, const Int& inRightInt)");
}


/*!
 *  \brief     Test whether an int is less than, or equal to another.
 *  \param     inLeftInt  Left int compared.
 *  \param     inRightInt Right int compared.
 *  \return    True if left int is less than, or equal to the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the functions isLess and isEqual of Beagle::Int.
 */
inline bool operator<=(const Beagle::Int& inLeftInt, const Beagle::Int& inRightInt)
{
	Beagle_StackTraceBeginM();
	return ( inLeftInt.isLess(inRightInt) || inLeftInt.isEqual(inRightInt) );
	Beagle_StackTraceEndM("bool operator<=(const Int& inLeftInt, const Int& inRightInt)");
}


/*!
 *  \brief     Test whether an int is more than another.
 *  \param     inLeftInt  Left int compared.
 *  \param     inRightInt Right int compared.
 *  \return    True if left int is more than the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the function isLess of Beagle::Int.
 */
inline bool operator>(const Beagle::Int& inLeftInt, const Beagle::Int& inRightInt)
{
	Beagle_StackTraceBeginM();
	return inRightInt.isLess(inLeftInt);
	Beagle_StackTraceEndM("bool operator>(const Int& inLeftInt, const Int& inRightInt)");
}


/*!
 *  \brief     Test whether an int is more than, or equal to another.
 *  \param     inLeftInt  Left int compared.
 *  \param     inRightInt Right int compared.
 *  \return    True if left int is more than, or equal to the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the functions isLess and isEqual of Beagle::Int.
 */
inline bool operator>=(const Beagle::Int& inLeftInt, const Beagle::Int& inRightInt)
{
	Beagle_StackTraceBeginM();
	return ( inRightInt.isLess(inLeftInt) || inLeftInt.isEqual(inRightInt) );
	Beagle_StackTraceEndM("bool operator>=(const Int& inLeftInt, const Int& inRightInt)");
}


/*!
 *  \brief     Test whether an int is equal to another.
 *  \param     inLeftInt  Left int compared.
 *  \param     inRightInt Right int compared.
 *  \return    True if left int is equal to the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the function isEqual of Beagle::Int.
 */
inline bool operator==(const Beagle::Int& inLeftInt, const Beagle::Int& inRightInt)
{
	Beagle_StackTraceBeginM();
	return inLeftInt.isEqual(inRightInt);
	Beagle_StackTraceEndM("bool operator==(const Int& inLeftInt, const Int& inRightInt)");
}


/*!
 *  \brief     Test whether an int is not equal to another.
 *  \param     inLeftInt  Left int compared.
 *  \param     inRightInt Right int compared.
 *  \return    True if left int is not equal to the right one, false if it is.
 *  \par Note:
 *    The operator is defined relatively to the function isEqual of Beagle::Int.
 */
inline bool operator!=(const Beagle::Int& inLeftInt, const Beagle::Int& inRightInt)
{
	Beagle_StackTraceBeginM();
	return ( inLeftInt.isEqual(inRightInt) == false);
	Beagle_StackTraceEndM("bool operator!=(const Int& inLeftInt, const Int& inRightInt)");
}


/*!
 *  \brief Compare equality of a Int with a int.
 *  \param inLeftInt Left value to compare.
 *  \param inRightInt Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator==(const Beagle::Int& inLeftInt, int inRightInt)
{
	Beagle_StackTraceBeginM();
	return inLeftInt.getWrappedValue() == inRightInt;
	Beagle_StackTraceEndM("bool operator==(const Int& inLeftInt, int inRightInt)");
}


/*!
 *  \brief Compare inequality of a Int with a int.
 *  \param inLeftInt Left value to compare.
 *  \param inRightInt Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator!=(const Beagle::Int& inLeftInt, int inRightInt)
{
	Beagle_StackTraceBeginM();
	return inLeftInt.getWrappedValue() != inRightInt;
	Beagle_StackTraceEndM("bool operator!=(const Int& inLeftInt, int inRightInt)");
}


/*!
 *  \brief Test if a Int is < than a int.
 *  \param inLeftInt Left value to compare.
 *  \param inRightInt Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator<(const Beagle::Int& inLeftInt, int inRightInt)
{
	Beagle_StackTraceBeginM();
	return inLeftInt.getWrappedValue() < inRightInt;
	Beagle_StackTraceEndM("bool operator<(const Int& inLeftInt, int inRightInt)");
}


/*!
 *  \brief Test if a Int is <= than a int.
 *  \param inLeftInt Left value to compare.
 *  \param inRightInt Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator<=(const Beagle::Int& inLeftInt, int inRightInt)
{
	Beagle_StackTraceBeginM();
	return inLeftInt.getWrappedValue() <= inRightInt;
	Beagle_StackTraceEndM("bool operator<=(const Int& inLeftInt, int inRightInt)");
}


/*!
 *  \brief Test if a Int is > than a int.
 *  \param inLeftInt Left value to compare.
 *  \param inRightInt Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator>(const Beagle::Int& inLeftInt, int inRightInt)
{
	Beagle_StackTraceBeginM();
	return inLeftInt.getWrappedValue() > inRightInt;
	Beagle_StackTraceEndM("bool operator>(const Int& inLeftInt, int inRightInt)");
}


/*!
 *  \brief Test if a Int is >= than a int.
 *  \param inLeftInt Left value to compare.
 *  \param inRightInt Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator>=(const Beagle::Int& inLeftInt, int inRightInt)
{
	Beagle_StackTraceBeginM();
	return inLeftInt.getWrappedValue() >= inRightInt;
	Beagle_StackTraceEndM("bool operator>=(const Int& inLeftInt, int inRightInt)");
}


/*!
 *  \brief Increment a Int (prefix version).
 *  \param inInt Int to increment.
 *  \return Int incremented.
 */
inline
Beagle::Int& operator++(Beagle::Int& inInt)
{
	Beagle_StackTraceBeginM();
	inInt.getWrappedValue()++;
	return inInt;
	Beagle_StackTraceEndM("Int& operator++(Int& inInt)");
}


/*!
 *  \brief Increment a Int (postfix version).
 *  \param inInt Int to increment.
 *  \return Int before being incremented.
 */
inline
Beagle::Int operator++(Beagle::Int& inInt, int)
{
	Beagle_StackTraceBeginM();
	Beagle::Int lInt = inInt;
	inInt.getWrappedValue()++;
	return lInt;
	Beagle_StackTraceEndM("Int operator++(Int& inInt, int)");
}


/*!
 *  \brief Add two Int.
 *  \param inLeftInt Left value to add.
 *  \param inRightInt Right value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Int operator+(const Beagle::Int& inLeftInt, const Beagle::Int& inRightInt)
{
	Beagle_StackTraceBeginM();
	return inLeftInt.getWrappedValue() + inRightInt.getWrappedValue();
	Beagle_StackTraceEndM("Int operator+(const Int& inLeftInt, const Int& inRightInt)");
}


/*!
 *  \brief Add a Int with a int.
 *  \param inLeftInt Left value to add.
 *  \param inRightInt Right value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Int operator+(const Beagle::Int& inLeftInt, int inRightInt)
{
	Beagle_StackTraceBeginM();
	return inLeftInt.getWrappedValue() + inRightInt;
	Beagle_StackTraceEndM("Int operator+(const Int& inLeftInt, int inRightInt)");
}


/*!
 *  \brief Add a Int to a Int.
 *  \param inLeftInt Left value to which the right one is added.
 *  \param inRightInt Value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Int& operator+=(Beagle::Int& inLeftInt, const Beagle::Int& inRightInt)
{
	Beagle_StackTraceBeginM();
	inLeftInt.getWrappedValue() += inRightInt.getWrappedValue();
	return inLeftInt;
	Beagle_StackTraceEndM("Int& operator+=(Int& inLeftInt, const Int& inRightInt)");
}


/*!
 *  \brief Add a int to a Int.
 *  \param inLeftInt Left value to which the right one is added.
 *  \param inRightInt Value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Int& operator+=(Beagle::Int& inLeftInt, int inRightInt)
{
	Beagle_StackTraceBeginM();
	inLeftInt.getWrappedValue() += inRightInt;
	return inLeftInt;
	Beagle_StackTraceEndM("Int& operator+=(Int& inLeftInt, int inRightInt)");
}


/*!
 *  \brief Decrement a Int (prefix version).
 *  \param inInt Int to decrement.
 *  \return Int decremented.
 */
inline
Beagle::Int& operator--(Beagle::Int& inInt)
{
	Beagle_StackTraceBeginM();
	inInt.getWrappedValue()--;
	return inInt;
	Beagle_StackTraceEndM("Int& operator--(Int& inInt)");
}


/*!
 *  \brief Decrement a Int (postfix version).
 *  \param inInt Int to decrement.
 *  \return Int before being decremented.
 */
inline
Beagle::Int operator--(Beagle::Int& inInt, int)
{
	Beagle_StackTraceBeginM();
	Beagle::Int lInt = inInt;
	inInt.getWrappedValue()--;
	return lInt;
	Beagle_StackTraceEndM("Int operator--(Int& inInt, int)");
}



/*!
 *  \brief Subtract two Int.
 *  \param inLeftInt Left value to subtract.
 *  \param inRightInt Right value to subtract.
 *  \return Result of the subtract.
 */
inline
Beagle::Int operator-(const Beagle::Int& inLeftInt, const Beagle::Int& inRightInt)
{
	Beagle_StackTraceBeginM();
	return inLeftInt.getWrappedValue() - inRightInt.getWrappedValue();
	Beagle_StackTraceEndM("Int operator-(const Int& inLeftInt, const Int& inRightInt)");
}


/*!
 *  \brief Subtract a int from a Int.
 *  \param inLeftInt Left value to subtract.
 *  \param inRightInt Right value to subtract.
 *  \return Result of the subtract.
 */
inline
Beagle::Int operator-(const Beagle::Int& inLeftInt, int inRightInt)
{
	Beagle_StackTraceBeginM();
	return inLeftInt.getWrappedValue() - inRightInt;
	Beagle_StackTraceEndM("Int operator-(const Int& inLeftInt, int inRightInt)");
}


/*!
 *  \brief Subtract a Int from a Int.
 *  \param inLeftInt Left value from which the right int is subtracted.
 *  \param inRightInt Value to subtract.
 *  \return Result of the subtraction.
 */
inline
Beagle::Int& operator-=(Beagle::Int& inLeftInt, const Beagle::Int& inRightInt)
{
	Beagle_StackTraceBeginM();
	inLeftInt.getWrappedValue() -= inRightInt.getWrappedValue();
	return inLeftInt;
	Beagle_StackTraceEndM("Int& operator-=(Int& inLeftInt, const Int& inRightInt)");
}


/*!
 *  \brief Subtract a int from a Int.
 *  \param inLeftInt Left value from which the right int is subtracted.
 *  \param inRightInt Value to subtract.
 *  \return Result of the subtraction.
 */
inline
Beagle::Int& operator-=(Beagle::Int& inLeftInt, int inRightInt)
{
	Beagle_StackTraceBeginM();
	inLeftInt.getWrappedValue() -= inRightInt;
	return inLeftInt;
	Beagle_StackTraceEndM("Int& operator-=(Int& inLeftInt, int inRightInt)");
}


/*!
 *  \brief Multiply two Int.
 *  \param inLeftInt Left value to multiply.
 *  \param inRightInt Right value to multiply.
 *  \return Result of the multiply.
 */
inline
Beagle::Int operator*(const Beagle::Int& inLeftInt, const Beagle::Int& inRightInt)
{
	Beagle_StackTraceBeginM();
	return inLeftInt.getWrappedValue() * inRightInt.getWrappedValue();
	Beagle_StackTraceEndM("Int operator*(const Int& inLeftInt, const Int& inRightInt)");
}


/*!
 *  \brief Multiply a Int with a int.
 *  \param inLeftInt Left value to multiply.
 *  \param inRightInt Right value to multiply.
 *  \return Result of the multiply.
 */
inline
Beagle::Int operator*(const Beagle::Int& inLeftInt, int inRightInt)
{
	Beagle_StackTraceBeginM();
	return inLeftInt.getWrappedValue() * inRightInt;
	Beagle_StackTraceEndM("Int operator*(const Int& inLeftInt, int inRightInt)");
}


/*!
 *  \brief Multiply a Int with a Int.
 *  \param inLeftInt Left value to which the right int is multiplied.
 *  \param inRightInt Right value to multiply.
 *  \return Result of the multiplication.
 */
inline
Beagle::Int& operator*=(Beagle::Int& inLeftInt, const Beagle::Int& inRightInt)
{
	Beagle_StackTraceBeginM();
	inLeftInt.getWrappedValue() *= inRightInt.getWrappedValue();
	return inLeftInt;
	Beagle_StackTraceEndM("Int& operator*=(Int& inLeftInt, const Int& inRightInt)");
}


/*!
 *  \brief Multiply a Int with a int.
 *  \param inLeftInt Left value from which the right int is multiplied.
 *  \param inRightInt Right value to multiply.
 *  \return Result of the multiplication.
 */
inline
Beagle::Int& operator*=(Beagle::Int& inLeftInt, int inRightInt)
{
	Beagle_StackTraceBeginM();
	inLeftInt.getWrappedValue() *= inRightInt;
	return inLeftInt;
	Beagle_StackTraceEndM("Int& operator*=(Int& inLeftInt, int inRightInt)");
}


/*!
 *  \brief Divide two Int.
 *  \param inLeftInt Left value to divide.
 *  \param inRightInt Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::Int operator/(const Beagle::Int& inLeftInt, const Beagle::Int& inRightInt)
{
	Beagle_StackTraceBeginM();
	return inLeftInt.getWrappedValue() / inRightInt.getWrappedValue();
	Beagle_StackTraceEndM("Int operator/(const Int& inLeftInt, const Int& inRightInt)");
}


/*!
 *  \brief Divide a Int with a int.
 *  \param inLeftInt Left value to divide.
 *  \param inRightInt Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::Int operator/(const Beagle::Int& inLeftInt, int inRightInt)
{
	Beagle_StackTraceBeginM();
	return inLeftInt.getWrappedValue() / inRightInt;
	Beagle_StackTraceEndM("Int operator/(const Int& inLeftInt, int inRightInt)");
}


/*!
 *  \brief Divide a Int with a Int.
 *  \param inLeftInt Left value to which the right int is divided.
 *  \param inRightInt Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::Int& operator/=(Beagle::Int& inLeftInt, const Beagle::Int& inRightInt)
{
	Beagle_StackTraceBeginM();
	inLeftInt.getWrappedValue() /= inRightInt.getWrappedValue();
	return inLeftInt;
	Beagle_StackTraceEndM("Int& operator/=(Int& inLeftInt, const Int& inRightInt)");
}


/*!
 *  \brief Divide a Int with a int.
 *  \param inLeftInt Left value from which the right int is divided.
 *  \param inRightInt Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::Int operator/=(Beagle::Int& inLeftInt, int inRightInt)
{
	Beagle_StackTraceBeginM();
	inLeftInt.getWrappedValue() /= inRightInt;
	return inLeftInt;
	Beagle_StackTraceEndM("Int operator/=(Int& inLeftInt, int inRightInt)");
}


#endif // Beagle_Int_hpp



