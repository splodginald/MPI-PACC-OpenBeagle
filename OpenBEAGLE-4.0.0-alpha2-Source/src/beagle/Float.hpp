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
 *  \file   beagle/Float.hpp
 *  \brief  Definition of the type Float and related operators.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.9 $
 *  $Date: 2007/08/08 19:26:44 $
 */

#ifndef Beagle_Float_hpp
#define Beagle_Float_hpp

#include "beagle/config.hpp"
#include "beagle/macros.hpp"
#include "beagle/WrapperT.hpp"
#include "beagle/ArrayT.hpp"


namespace Beagle
{

/*!
 *  \brief Beagle wrapper of the atomic float type.
 *  \ingroup Adapt
 */
typedef WrapperT< float >
Float;

/*!
 *  \brief Beagle array of the atomic float type.
 *  \ingroup Adapt
 */
typedef ArrayT< float >
FloatArray;

/*!
 *  \brief Evaluate absolute value of a Beagle::Float.
 *  \param inValue Float to evaluate the absolute value.
 *  \return Absolute value of the input.
 *  \ingroup Adapt
 */
template <>
inline Float absolute(const Float& inValue)
{
	Beagle_StackTraceBeginM();
	return Float(std::fabs(inValue.getWrappedValue()));
	Beagle_StackTraceEndM("Float absolute(const Float& inValue)");
}

}


/*!
 *  \brief  Test whether an float is less than another.
 *  \param  inLeftFloat  Left float compared.
 *  \param  inRightFloat Right float compared.
 *  \return True if left float is less than the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the function isLess of Beagle::Float.
 */
inline bool operator<(const Beagle::Float& inLeftFloat, const Beagle::Float& inRightFloat)
{
	Beagle_StackTraceBeginM();
	return inLeftFloat.isLess(inRightFloat);
	Beagle_StackTraceEndM("bool operator<(const Float& inLeftFloat, const Float& inRightFloat)");
}


/*!
 *  \brief  Test whether an float is less than, or equal to another.
 *  \param  inLeftFloat  Left float compared.
 *  \param  inRightFloat Right float compared.
 *  \return True if left float is less than, or equal to the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the functions isLess and isEqual of Beagle::Float.
 */
inline bool operator<=(const Beagle::Float& inLeftFloat, const Beagle::Float& inRightFloat)
{
	Beagle_StackTraceBeginM();
	return ( inLeftFloat.isLess(inRightFloat) || inLeftFloat.isEqual(inRightFloat) );
	Beagle_StackTraceEndM("bool operator<=(const Float& inLeftFloat, const Float& inRightFloat)");
}


/*!
 *  \brief  Test whether an float is more than another.
 *  \param  inLeftFloat  Left float compared.
 *  \param  inRightFloat Right float compared.
 *  \return True if left float is more than the right one, false if not.
 *  \par Note:
 *     The operator is defined relatively to the function isLess of Beagle::Float.
 */
inline bool operator>(const Beagle::Float& inLeftFloat, const Beagle::Float& inRightFloat)
{
	Beagle_StackTraceBeginM();
	return inRightFloat.isLess(inLeftFloat);
	Beagle_StackTraceEndM("bool operator>(const Float& inLeftFloat, const Float& inRightFloat)");
}


/*!
 *  \brief  Test whether an float is more than, or equal to another.
 *  \param  inLeftFloat  Left float compared.
 *  \param  inRightFloat Right float compared.
 *  \return True if left float is more than, or equal to the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the functions isLess and isEqual of Beagle::Float.
 */
inline bool operator>=(const Beagle::Float& inLeftFloat, const Beagle::Float& inRightFloat)
{
	Beagle_StackTraceBeginM();
	return ( inRightFloat.isLess(inLeftFloat) || inLeftFloat.isEqual(inRightFloat) );
	Beagle_StackTraceEndM("bool operator>=(const Float& inLeftFloat, const Float& inRightFloat)");
}


/*!
 *  \brief  Test whether an float is equal to another.
 *  \param  inLeftFloat  Left float compared.
 *  \param  inRightFloat Right float compared.
 *  \return True if left float is equal to the right one, false if not.
 *  \par Note:
 *    The operator is defined relatively to the function isEqual of Beagle::Float.
 */
inline bool operator==(const Beagle::Float& inLeftFloat, const Beagle::Float& inRightFloat)
{
	Beagle_StackTraceBeginM();
	return inLeftFloat.isEqual(inRightFloat);
	Beagle_StackTraceEndM("bool operator==(const Float& inLeftFloat, const Float& inRightFloat)");
}


/*!
 *  \brief  Test whether an float is not equal to another.
 *  \param  inLeftFloat  Left float compared.
 *  \param  inRightFloat Right float compared.
 *  \return True if left float is not equal to the right one, false if it is.
 *  \par Note:
 *    The operator is defined relatively to the function isEqual of Beagle::Float.
 */
inline bool operator!=(const Beagle::Float& inLeftFloat, const Beagle::Float& inRightFloat)
{
	Beagle_StackTraceBeginM();
	return ( inLeftFloat.isEqual(inRightFloat) == false);
	Beagle_StackTraceEndM("bool operator!=(const Float& inLeftFloat, const Float& inRightFloat)");
}


/*!
 *  \brief Compare equality of a Float with a float.
 *  \param inLeftFloat Left value to compare.
 *  \param inRightFloat Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator==(const Beagle::Float& inLeftFloat, float inRightFloat)
{
	Beagle_StackTraceBeginM();
	return inLeftFloat.getWrappedValue() == inRightFloat;
	Beagle_StackTraceEndM("bool operator==(const Float& inLeftFloat, float inRightFloat)");
}


/*!
 *  \brief Compare inequality of a Float with a float.
 *  \param inLeftFloat Left value to compare.
 *  \param inRightFloat Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator!=(const Beagle::Float& inLeftFloat, float inRightFloat)
{
	Beagle_StackTraceBeginM();
	return inLeftFloat.getWrappedValue() != inRightFloat;
	Beagle_StackTraceEndM("bool operator!=(const Float& inLeftFloat, float inRightFloat)");
}


/*!
 *  \brief Test if a Float is < than a float.
 *  \param inLeftFloat Left value to compare.
 *  \param inRightFloat Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator<(const Beagle::Float& inLeftFloat, float inRightFloat)
{
	Beagle_StackTraceBeginM();
	return inLeftFloat.getWrappedValue() < inRightFloat;
	Beagle_StackTraceEndM("bool operator<(const Float& inLeftFloat, float inRightFloat)");
}


/*!
 *  \brief Test if a Float is <= than a float.
 *  \param inLeftFloat Left value to compare.
 *  \param inRightFloat Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator<=(const Beagle::Float& inLeftFloat, float inRightFloat)
{
	Beagle_StackTraceBeginM();
	return inLeftFloat.getWrappedValue() <= inRightFloat;
	Beagle_StackTraceEndM("bool operator<=(const Float& inLeftFloat, float inRightFloat)");
}


/*!
 *  \brief Test if a Float is > than a float.
 *  \param inLeftFloat Left value to compare.
 *  \param inRightFloat Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator>(const Beagle::Float& inLeftFloat, float inRightFloat)
{
	Beagle_StackTraceBeginM();
	return inLeftFloat.getWrappedValue() > inRightFloat;
	Beagle_StackTraceEndM("bool operator>(const Float& inLeftFloat, float inRightFloat)");
}


/*!
 *  \brief Test if a Float is >= than a float.
 *  \param inLeftFloat Left value to compare.
 *  \param inRightFloat Right value to compare.
 *  \return Result of the comparison.
 */
inline
bool operator>=(const Beagle::Float& inLeftFloat, float inRightFloat)
{
	Beagle_StackTraceBeginM();
	return inLeftFloat.getWrappedValue() >= inRightFloat;
	Beagle_StackTraceEndM("bool operator>=(const Float& inLeftFloat, float inRightFloat)");
}


/*!
 *  \brief Add two Float.
 *  \param inLeftFloat Left value to add.
 *  \param inRightFloat Right value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Float operator+(const Beagle::Float& inLeftFloat, const Beagle::Float& inRightFloat)
{
	Beagle_StackTraceBeginM();
	return inLeftFloat.getWrappedValue() + inRightFloat.getWrappedValue();
	Beagle_StackTraceEndM("Float operator+(const Float& inLeftFloat, const Float& inRightFloat)");
}


/*!
 *  \brief Add a Float with a float.
 *  \param inLeftFloat Left value to add.
 *  \param inRightFloat Right value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Float operator+(const Beagle::Float& inLeftFloat, float inRightFloat)
{
	Beagle_StackTraceBeginM();
	return inLeftFloat.getWrappedValue() + inRightFloat;
	Beagle_StackTraceEndM("Float operator+(const Float& inLeftFloat, float inRightFloat)");
}


/*!
 *  \brief Add a Float to a Float.
 *  \param inLeftFloat Left value to which the right one is added.
 *  \param inRightFloat Value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Float operator+=(Beagle::Float& inLeftFloat, const Beagle::Float& inRightFloat)
{
	Beagle_StackTraceBeginM();
	inLeftFloat.getWrappedValue() += inRightFloat.getWrappedValue();
	return inLeftFloat;
	Beagle_StackTraceEndM("Float operator+=(Float& inLeftFloat, const Float& inRightFloat)");
}


/*!
 *  \brief Add a float to a Float.
 *  \param inLeftFloat Left value to which the right one is added.
 *  \param inRightFloat Value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Float operator+=(Beagle::Float& inLeftFloat, float inRightFloat)
{
	Beagle_StackTraceBeginM();
	inLeftFloat.getWrappedValue() += inRightFloat;
	return inLeftFloat;
	Beagle_StackTraceEndM("Float operator+=(Float& inLeftFloat, float inRightFloat)");
}


/*!
 *  \brief Subtract two Float.
 *  \param inLeftFloat Left value to subtract.
 *  \param inRightFloat Right value to subtract.
 *  \return Result of the subtract.
 */
inline
Beagle::Float operator-(const Beagle::Float& inLeftFloat, const Beagle::Float& inRightFloat)
{
	Beagle_StackTraceBeginM();
	return inLeftFloat.getWrappedValue() - inRightFloat.getWrappedValue();
	Beagle_StackTraceEndM("Float operator-(const Float& inLeftFloat, const Float& inRightFloat)");
}


/*!
 *  \brief Subtract a float from a Float.
 *  \param inLeftFloat Left value to subtract.
 *  \param inRightFloat Right value to subtract.
 *  \return Result of the subtract.
 */
inline
Beagle::Float operator-(const Beagle::Float& inLeftFloat, float inRightFloat)
{
	Beagle_StackTraceBeginM();
	return inLeftFloat.getWrappedValue() - inRightFloat;
	Beagle_StackTraceEndM("Float operator-(const Float& inLeftFloat, float inRightFloat)");
}


/*!
 *  \brief Subtract a Float from a Float.
 *  \param inLeftFloat Left value from which the right float is subtracted.
 *  \param inRightFloat Value to subtract.
 *  \return Result of the subtraction.
 */
inline
Beagle::Float operator-=(Beagle::Float& inLeftFloat, const Beagle::Float& inRightFloat)
{
	Beagle_StackTraceBeginM();
	inLeftFloat.getWrappedValue() -= inRightFloat.getWrappedValue();
	return inLeftFloat;
	Beagle_StackTraceEndM("Float operator-=(Float& inLeftFloat, const Float& inRightFloat)");
}


/*!
 *  \brief Subtract a float from a Float.
 *  \param inLeftFloat Left value from which the right float is subtracted.
 *  \param inRightFloat Value to subtract.
 *  \return Result of the subtraction.
 */
inline
Beagle::Float operator-=(Beagle::Float& inLeftFloat, float inRightFloat)
{
	Beagle_StackTraceBeginM();
	inLeftFloat.getWrappedValue() -= inRightFloat;
	return inLeftFloat;
	Beagle_StackTraceEndM("Float operator-=(Float& inLeftFloat, float inRightFloat)");
}


/*!
 *  \brief Multiply two Float.
 *  \param inLeftFloat Left value to multiply.
 *  \param inRightFloat Right value to multiply.
 *  \return Result of the multiply.
 */
inline
Beagle::Float operator*(const Beagle::Float& inLeftFloat, const Beagle::Float& inRightFloat)
{
	Beagle_StackTraceBeginM();
	return inLeftFloat.getWrappedValue() * inRightFloat.getWrappedValue();
	Beagle_StackTraceEndM("Float operator*(const Float& inLeftFloat, const Float& inRightFloat)");
}


/*!
 *  \brief Multiply a Float with a float.
 *  \param inLeftFloat Left value to multiply.
 *  \param inRightFloat Right value to multiply.
 *  \return Result of the multiply.
 */
inline
Beagle::Float operator*(const Beagle::Float& inLeftFloat, float inRightFloat)
{
	Beagle_StackTraceBeginM();
	return inLeftFloat.getWrappedValue() * inRightFloat;
	Beagle_StackTraceEndM("Float operator*(const Float& inLeftFloat, float inRightFloat)");
}


/*!
 *  \brief Multiply a Float with a Float.
 *  \param inLeftFloat Left value to which the right float is multiplied.
 *  \param inRightFloat Right value to multiply.
 *  \return Result of the multiplication.
 */
inline
Beagle::Float operator*=(Beagle::Float& inLeftFloat, const Beagle::Float& inRightFloat)
{
	Beagle_StackTraceBeginM();
	inLeftFloat.getWrappedValue() *= inRightFloat.getWrappedValue();
	return inLeftFloat;
	Beagle_StackTraceEndM("Float operator*=(Float& inLeftFloat, const Float& inRightFloat)");
}


/*!
 *  \brief Multiply a Float with a float.
 *  \param inLeftFloat Left value from which the right float is multiplied.
 *  \param inRightFloat Right value to multiply.
 *  \return Result of the multiplication.
 */
inline
Beagle::Float operator*=(Beagle::Float& inLeftFloat, float inRightFloat)
{
	Beagle_StackTraceBeginM();
	inLeftFloat.getWrappedValue() *= inRightFloat;
	return inLeftFloat;
	Beagle_StackTraceEndM("Float operator*=(Float& inLeftFloat, float inRightFloat)");
}


/*!
 *  \brief Divide two Float.
 *  \param inLeftFloat Left value to divide.
 *  \param inRightFloat Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::Float operator/(const Beagle::Float& inLeftFloat, const Beagle::Float& inRightFloat)
{
	Beagle_StackTraceBeginM();
	return inLeftFloat.getWrappedValue() / inRightFloat.getWrappedValue();
	Beagle_StackTraceEndM("Float operator/(const Float& inLeftFloat, const Float& inRightFloat)");
}


/*!
 *  \brief Divide a Float with a float.
 *  \param inLeftFloat Left value to divide.
 *  \param inRightFloat Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::Float operator/(const Beagle::Float& inLeftFloat, float inRightFloat)
{
	Beagle_StackTraceBeginM();
	return inLeftFloat.getWrappedValue() / inRightFloat;
	Beagle_StackTraceEndM("Float operator/(const Float& inLeftFloat, float inRightFloat)");
}


/*!
 *  \brief Divide a Float with a Float.
 *  \param inLeftFloat Left value to which the right float is divided.
 *  \param inRightFloat Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::Float operator/=(Beagle::Float& inLeftFloat, const Beagle::Float& inRightFloat)
{
	Beagle_StackTraceBeginM();
	inLeftFloat.getWrappedValue() /= inRightFloat.getWrappedValue();
	return inLeftFloat;
	Beagle_StackTraceEndM("Float operator/=(Float& inLeftFloat, const Float& inRightFloat)");
}


/*!
 *  \brief Divide a Float with a float.
 *  \param inLeftFloat Left value from which the right float is divided.
 *  \param inRightFloat Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::Float operator/=(Beagle::Float& inLeftFloat, float inRightFloat)
{
	Beagle_StackTraceBeginM();
	inLeftFloat.getWrappedValue() /= inRightFloat;
	return inLeftFloat;
	Beagle_StackTraceEndM("Float operator/=(Float& inLeftFloat, float inRightFloat)");
}


#endif // Beagle_Float_hpp



