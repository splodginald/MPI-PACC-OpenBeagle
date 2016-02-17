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
 *  \file   beagle/GA/BitString.hpp
 *  \brief  Definition of the type GA::BitString.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.14 $
 *  $Date: 2007/08/17 18:09:10 $
 */

/*!
 *  \defgroup GABS Bit string GA
 *  \ingroup GAF
 *  \brief Bit string GA representation, operators and evolvers, part of the GA framework.
 */

#ifndef Beagle_GA_BitString_hpp
#define Beagle_GA_BitString_hpp

#include <vector>

#include "beagle/config.hpp"
#include "beagle/macros.hpp"
#include "beagle/Object.hpp"
#include "beagle/Allocator.hpp"
#include "beagle/Pointer.hpp"
#include "beagle/Container.hpp"
#include "beagle/ContainerT.hpp"
#include "beagle/Genotype.hpp"


namespace Beagle
{
namespace GA
{

/*!
 *  \class BitString beagle/GA/BitString.hpp "beagle/GA/BitString.hpp"
 *  \brief Bit string GA genotype class.
 *  \ingroup GAF
 *  \ingroup GABS
 */
class BitString : public Genotype, public std::vector<bool>
{

public:

	/*!
	 *  \struct DecodingKey beagle/GA/BitString.hpp "beagle/GA/BitString.hpp"
	 *  \brief Decoding key to tranform a bit string genotype into a vector of numbers.
	 */
	struct DecodingKey
	{
		double       mLowerBound;    //!< Lower bound of the encoded value.
		double       mUpperBound;    //!< Upper bound of the encoded value.
		unsigned int mEncoding;      //!< Encoding of the value, in bits.

		/*!
		 *  \brief Construct a decoding key.
		 *  \param inLowerBound Lower bound of the encoded value.
		 *  \param inUpperBound Upper bound of the encoded value.
		 *  \param inEncoding Encoding of the value (in bits).
		 */
		DecodingKey(double       inLowerBound=0.0,
		            double       inUpperBound=1.0,
		            unsigned int inEncoding=1) :
				mLowerBound(inLowerBound),
				mUpperBound(inUpperBound),
				mEncoding(inEncoding)
		{ }
	};

	//!< Decoding key vector.
	typedef std::vector<GA::BitString::DecodingKey> DecodingKeyVector;

	//! BitString allocator type.
	typedef AllocatorT<BitString,Genotype::Alloc> Alloc;
	//! BitString handle type.
	typedef PointerT<BitString,Genotype::Handle> Handle;
	//! BitString bag type.
	typedef ContainerT<BitString,Genotype::Bag> Bag;

	explicit BitString(unsigned int inSize=0, bool inModel=false);

	virtual void                copy(const Member& inOriginal, System& ioSystem);
	void                        decode(const DecodingKeyVector& inKeys, std::vector<double>& outVector) const;
	void                        decodeGray(const DecodingKeyVector& inKeys, std::vector<double>& outVector) const;
	virtual unsigned int        getSize() const;
	virtual const std::string&  getType() const;
	virtual void				swap(unsigned int inI, unsigned int inJ);
	virtual bool                isEqual(const Object& inRightObj) const;
	virtual bool                isLess(const Object& inRightObj) const;
	virtual void                readWithContext(PACC::XML::ConstIterator inIter, Context& ioContext);
	virtual void                writeContent(PACC::XML::Streamer& ioStreamer, bool inIndent=true) const;

protected:

	static void convertBin2Dec(const DecodingKeyVector& inKeys,
	                           const std::vector<bool>& inBitString,
	                           std::vector<double>& outVector);
	static void convertGray2Bin(const DecodingKeyVector& inKeys,
	                            const std::vector<bool>& inGrayBitString,
	                            std::vector<bool>& outBinBitString);

};

}
}

#endif // Beagle_GA_BitString_hpp
