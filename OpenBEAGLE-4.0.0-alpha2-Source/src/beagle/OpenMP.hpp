/*
 *  Open BEAGLE
 *  Copyright (C) 2001-2009 by Christian Gagne and Marc Parizeau
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
 *  \file   beagle/OpenMP.hpp
 *  \brief  Definition of the class OpenMP.
 *	\author Francois-Michel De Rainville
 *	\author Felix-Antoine Fortin
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: $
 *  $Date: $
 */

#ifndef Beagle_OpenMp_hpp
#define Beagle_OpenMp_hpp

#include <omp.h>

#include "beagle/Beagle.hpp"

namespace Beagle {

/*!
 *  \class OpenMP beagle/OpenMP.hpp "beagle/OpenMP.hpp"
 *  \brief OpenMP function wrapper class.
 *  \ingroup ECF
 *  \ingroup Sys
 */
class OpenMP : public Component {
public:
	//! OpenMP Component allocator type.
	typedef AllocatorT<OpenMP,Component::Alloc> Alloc;

	//! OpenMP Component handle type.
	typedef PointerT<OpenMP,Component::Handle> Handle;

	//! OpenMP Component bag type.
	typedef ContainerT<OpenMP,Component::Bag> Bag;

	explicit OpenMP ();
	virtual ~OpenMP ()
	{ }

	virtual void init(System& ioSystem);
	virtual void readWithSystem(PACC::XML::ConstIterator inIter, System& ioSystem);
	virtual void registerParams(System& ioSystem);
	virtual void writeContent(PACC::XML::Streamer& ioStreamer, bool inIndent=true) const;

	/*!	\brief
	 *	\return
	 */
	inline unsigned int getNumThreads() const{
		Beagle_StackTraceBeginM();
		return omp_get_num_threads();
		Beagle_StackTraceEndM("unsigned int OpenMP::getNumThreads() const");
	}
	
	/*!	\brief
	 *	\return
	 */
	inline unsigned int getMaxNumThreads() const{
		Beagle_StackTraceBeginM();
#if defined(BEAGLE_USE_OMP_NR)
		return omp_get_max_threads();
#elif defined(BEAGLE_USE_OMP_R)
		if(mNumThreads == NULL)
			return omp_get_max_threads();
		return mNumThreads->getWrappedValue();
#endif
		Beagle_StackTraceEndM("unsigned int OpenMP::getMaxNumThreads() const");
	}
	
	/*!	\brief
	 *	\return
	 */
	inline unsigned int getThreadNum() const{
		Beagle_StackTraceBeginM();
		return omp_get_thread_num();
		Beagle_StackTraceEndM("unsigned int OpenMP::getThreadNum() const");
	}
	
	/*!	\brief Ask OpenMP how many processors are available.
	 *	\return The number of processors on this machine.
	 */
	inline unsigned int getNumProcs() const{
		Beagle_StackTraceBeginM();
		return omp_get_num_procs();
		Beagle_StackTraceEndM("unsigned int OpenMP::getNumProcs() const");
	}
	
	/*!	\brief
	 *	\return
	 */
	inline bool	inParallelSection() const{
		Beagle_StackTraceBeginM();
		return (omp_in_parallel()>0)?true:false;
		Beagle_StackTraceEndM("unsigned int OpenMP::inParallelSection() const");
	}

protected:
	/*!	\brief Set the number of threads that OpenMP will use in the parallel sections.
	 *	\param iNumThreads is the number of threads to use.
	 */
	inline virtual void	setNumThreads(unsigned int inNumThreads){
		Beagle_StackTraceBeginM();
		omp_set_num_threads(inNumThreads);
		Beagle_StackTraceEndM("unsigned int OpenMP::setNumThreads(unsigned int)");
	}

	UInt::Handle mNumThreads;
};

}

#endif
