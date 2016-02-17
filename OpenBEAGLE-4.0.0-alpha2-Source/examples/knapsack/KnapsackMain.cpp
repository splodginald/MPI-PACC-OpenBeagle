/*
 *  Multiobjective 0/1 Knapsack (knapsack):
 *  Multiobjective GA example
 *
 *  Copyright (C) 2003-2006 by Christian Gagne and Marc Parizeau
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
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
 *  \file   KnapsackMain.cpp
 *  \brief  Implementation of the main routine for the Knapsack problem.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.14 $
 *  $Date: 2007/08/17 18:09:18 $
 */

#include "beagle/GA.hpp"
#include "KnapsackEvalOp.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <numeric>

using namespace std;
using namespace Beagle;


/*!
 *  \brief Main routine for the Knapsack problem.
 *  \param argc Number of arguments on the command-line.
 *  \param argv Arguments on the command-line.
 *  \return Return value of the program.
 *  \ingroup Knapsack
 */
int main(int argc, char** argv)
{
	try {
		// Build the system
		System::Handle lSystem = new System;
		// Install the GA bit string and multi-objective optimization packages
		const unsigned int lNumberOfBits = 24;
		lSystem->addPackage(new GA::PackageBitString(lNumberOfBits));
		lSystem->addPackage(new PackageMultiObj);
		// Add evaluation operator allocator
		lSystem->setEvaluationOp("KnapsackEvalOp", new KnapsackEvalOp::Alloc);
		// Initialize the evolver
		Evolver::Handle lEvolver = new Evolver;
		lEvolver->initialize(lSystem, argc, argv);
		// Create population
		Vivarium::Handle lVivarium = new Vivarium;
		// Launch evolution
		lEvolver->evolve(lVivarium, lSystem);
	} catch(Exception& inException) {
		inException.terminate(cerr);
	} catch(std::exception& inException) {
		cerr << "Standard exception caught:" << endl << flush;
		cerr << inException.what() << endl << flush;
		return 1;
	}
	return 0;
}
