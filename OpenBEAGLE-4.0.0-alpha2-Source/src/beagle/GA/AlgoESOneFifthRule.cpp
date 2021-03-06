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
 *  \file   beagle/GA/src/AlgoESOneFifthRule.cpp
 *  \brief  Source code of class GA::AlgoESOneFifthRule.
 *  \author Christian Gagne
 *  $Revision: 1.3 $
 *  $Date: 2007/08/17 18:09:10 $
 */

#include "beagle/GA.hpp"

using namespace Beagle;


/*!
 *  \brief Construct (1+1)-ES with one fifth rule algorithm evolutionary algorithm.
 */
GA::AlgoESOneFifthRule::AlgoESOneFifthRule(void) :
		Algorithm("GA-AlgoESOneFifthRule")
{ }


/*!
 *  \brief Configure evolver with (1+1)-ES with one fifth rule algorithm.
 *  \param ioEvolver Evolver modified by setting the algorithm.
 *  \param ioSystem Evolutionary system.
 *
 */
void GA::AlgoESOneFifthRule::configure(Evolver& ioEvolver, System& ioSystem)
{
	Beagle_StackTraceBeginM();

	// Get reference to the factory
	const Factory& lFactory = ioSystem.getFactory();

	// Get name and allocator of used operators
	std::string lEvalOpName = lFactory.getConceptTypeName("EvaluationOp");
	EvaluationOp::Alloc::Handle lEvalOpAlloc =
	    castHandleT<EvaluationOp::Alloc>(lFactory.getAllocator(lEvalOpName));
	std::string lSelectOpName = "SelectRandomOp";
	SelectionOp::Alloc::Handle lSelectOpAlloc =
	    castHandleT<SelectionOp::Alloc>(lFactory.getAllocator(lSelectOpName));
	std::string lInitOpName = lFactory.getConceptTypeName("InitializationOp");
	InitializationOp::Alloc::Handle lInitOpAlloc =
	    castHandleT<InitializationOp::Alloc>(lFactory.getAllocator(lInitOpName));
	std::string lAdaptOpName = "GA-AdaptOneFifthRuleFltVecOp";
	GA::AdaptOneFifthRuleFltVecOp::Alloc::Handle lAdaptOpAlloc =
	    castHandleT<GA::AdaptOneFifthRuleFltVecOp::Alloc>(lFactory.getAllocator(lAdaptOpName));
	std::string lMutOpName = "GA-MutationESVecOp";
	MutationOp::Alloc::Handle lMutOpAlloc =
	    castHandleT<MutationOp::Alloc>(lFactory.getAllocator(lMutOpName));
	std::string lMigOpName = lFactory.getConceptTypeName("MigrationOp");
	MigrationOp::Alloc::Handle lMigOpAlloc =
	    castHandleT<MigrationOp::Alloc>(lFactory.getAllocator(lMigOpName));
	std::string lStatsCalcOpName = lFactory.getConceptTypeName("StatsCalculateOp");
	StatsCalculateOp::Alloc::Handle lStatsCalcOpAlloc =
	    castHandleT<StatsCalculateOp::Alloc>(lFactory.getAllocator(lStatsCalcOpName));
	std::string lTermOpName = lFactory.getConceptTypeName("TerminationOp");
	TerminationOp::Alloc::Handle lTermOpAlloc =
	    castHandleT<TerminationOp::Alloc>(lFactory.getAllocator(lTermOpName));
	std::string lMsWriteOpName = "MilestoneWriteOp";
	MilestoneWriteOp::Alloc::Handle lMsWriteOpAlloc =
	    castHandleT<MilestoneWriteOp::Alloc>(lFactory.getAllocator(lMsWriteOpName));
	std::string lMPLOpName = "MuPlusLambdaOp";
	MuPlusLambdaOp::Alloc::Handle lMPLOpAlloc =
	    castHandleT<MuPlusLambdaOp::Alloc>(lFactory.getAllocator(lMPLOpName));

	// Clear bootstrap and mainloop sets
	ioEvolver.getBootStrapSet().clear();
	ioEvolver.getMainLoopSet().clear();

	// Set the boostrap operator set
	InitializationOp::Handle lInitOpBS = castHandleT<InitializationOp>(lInitOpAlloc->allocate());
	lInitOpBS->setName(lInitOpName);
	ioEvolver.getBootStrapSet().push_back(lInitOpBS);
	EvaluationOp::Handle lEvalOpBS = castHandleT<EvaluationOp>(lEvalOpAlloc->allocate());
	lEvalOpBS->setName(lEvalOpName);
	ioEvolver.getBootStrapSet().push_back(lEvalOpBS);
	StatsCalculateOp::Handle lStatsCalcOpBS = castHandleT<StatsCalculateOp>(lStatsCalcOpAlloc->allocate());
	lStatsCalcOpBS->setName(lStatsCalcOpName);
	ioEvolver.getBootStrapSet().push_back(lStatsCalcOpBS);
	TerminationOp::Handle lTermOpBS = castHandleT<TerminationOp>(lTermOpAlloc->allocate());
	lTermOpBS->setName(lTermOpName);
	ioEvolver.getBootStrapSet().push_back(lTermOpBS);
	MilestoneWriteOp::Handle lMsWriteOpBS = castHandleT<MilestoneWriteOp>(lMsWriteOpAlloc->allocate());
	lMsWriteOpBS->setName(lMsWriteOpName);
	ioEvolver.getBootStrapSet().push_back(lMsWriteOpBS);

	// Set the mainloop operator set
	MuPlusLambdaOp::Handle lMPLOp = castHandleT<MuPlusLambdaOp>(lMPLOpAlloc->allocate());
	lMPLOp->setName(lMPLOpName);

	// Set breeder tree
	BreederNode::Handle lAdaptNode = new BreederNode;
	lMPLOp->setRootNode(lAdaptNode);
	lAdaptNode->setBreederOp(castHandleT<GA::AdaptOneFifthRuleFltVecOp>(lAdaptOpAlloc->allocate()));
	lAdaptNode->getBreederOp()->setName(lAdaptOpName);
	BreederNode::Handle lEvalNode = new BreederNode;
	lAdaptNode->setFirstChild(lEvalNode);
	lEvalNode->setBreederOp(castHandleT<EvaluationOp>(lEvalOpAlloc->allocate()));
	lEvalNode->getBreederOp()->setName(lEvalOpName);
	BreederNode::Handle lMutNode = new BreederNode;
	lEvalNode->setFirstChild(lMutNode);
	lMutNode->setBreederOp(castHandleT<MutationOp>(lMutOpAlloc->allocate()));
	lMutNode->getBreederOp()->setName(lMutOpName);
	BreederNode::Handle lSelectMutNode = new BreederNode;
	lMutNode->setFirstChild(lSelectMutNode);
	lSelectMutNode->setBreederOp(castHandleT<SelectionOp>(lSelectOpAlloc->allocate()));
	lSelectMutNode->getBreederOp()->setName(lSelectOpName);

	// Set remaining operators of mainloop
	MigrationOp::Handle lMigOpML = castHandleT<MigrationOp>(lMigOpAlloc->allocate());
	lMigOpML->setName(lMigOpName);
	ioEvolver.getMainLoopSet().push_back(lMigOpML);
	StatsCalculateOp::Handle lStatsCalcOpML =
	    castHandleT<StatsCalculateOp>(lStatsCalcOpAlloc->allocate());
	lStatsCalcOpML->setName(lStatsCalcOpName);
	ioEvolver.getMainLoopSet().push_back(lStatsCalcOpML);
	TerminationOp::Handle lTermOpML = castHandleT<TerminationOp>(lTermOpAlloc->allocate());
	lTermOpML->setName(lTermOpName);
	ioEvolver.getMainLoopSet().push_back(lTermOpML);
	MilestoneWriteOp::Handle lMsWriteOpML =
	    castHandleT<MilestoneWriteOp>(lMsWriteOpAlloc->allocate());
	lMsWriteOpML->setName(lMsWriteOpName);
	ioEvolver.getMainLoopSet().push_back(lMsWriteOpML);

	Beagle_StackTraceEndM("void AlgoESOneFifthRule::configure(Evolver&,System&)");
}
