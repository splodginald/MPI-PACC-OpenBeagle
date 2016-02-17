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
 *  \file   beagle/HPC/SendDemeToEvolverOp.cpp
 *  \brief  Source code of the class HPC::SendDemeToEvolverOp.
 *  \author Felix-Antoine Fortin
 *  \author Maxime Girardin
 *  \author Yannick Morin-Rivest
 *  \author Mathieu Couillard
 *  $Revision: $
 *  $Date:  $
 */

#include "beagle/HPC.hpp"

using namespace Beagle;

/*!
 *  \brief Construct the SendDemeToEvolverOp operator.
 *  \param inName Name of the operator.
 */
HPC::SendDemeToEvolverOp::SendDemeToEvolverOp(std::string inName) : Operator(inName) {}

/*!
 *  \brief Initialize the operator
 *  \param ioSystem Current system
 */
void HPC::SendDemeToEvolverOp::init(System& ioSystem)
{
	Beagle_StackTraceBeginM();
	mComm = castHandleT<HPC::MPICommunication>(ioSystem.getComponent("MPICommunication"));
	Beagle_StackTraceEndM("HPC::SendDemeToEvolverOp::init(System&)");
}

/*!
 *  \brief Distribute demes to evolver nodes.
 *  \param ioDeme Current deme to execute the operator.
 *  \param ioContext Current context to execute the operator.
 */
void HPC::SendDemeToEvolverOp::operate(Deme& ioDeme, Context& ioContext)
{
	Beagle_StackTraceBeginM();

	unsigned int lChild = ioContext.getDemeIndex();

	std::ostringstream lOutStream;
	PACC::XML::Streamer lStreamer(lOutStream);
	ioDeme.write(lStreamer, false);

	mComm->send(lOutStream.str(), "Deme", "Child", lChild);

	Beagle_LogDetailedM(
		ioContext.getSystem().getLogger(),
		"distribute", "Beagle::HPC::SendDemeToEvolverOp",
		std::string("Send ") + uint2ordinal(ioContext.getDemeIndex()) + " deme to his " + uint2ordinal(lChild) + " evolver"
	);
	Beagle_StackTraceEndM("void HPC::SendDemeToEvolverOp::operate(Deme& ioDeme, Context& ioContext)");
}
