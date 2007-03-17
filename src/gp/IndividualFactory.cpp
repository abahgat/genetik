/* 
 * 		genetik - Genetic Kernel Library 
 *
 * Copyright (C) 2006 Alessandro Bahgat Shehata, Daniele Castagna
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * Alessandro Bahgat Shehata - skandar (AT) users (DOT) sourceforge (DOT) net
 * Daniele Castagna - dcastagna (AT) users (DOT) sourceforge (DOT) net
 * 
 */

#include "IndividualFactory.h"
#include "Gene.h"
#include "../util/util.h"

#include <iostream>
using namespace std;

using genetiK::util::Log;
using genetiK::util::Exception;

namespace genetiK
{
namespace gp
{

IndividualFactory::IndividualFactory(unsigned char maxHeight,ETreeInitialization treeInitialization) :
                genetiK::IndividualFactory(),
                maxHeight(maxHeight),
                treeInitialization(treeInitialization)
{
	if (treeInitialization!=GROW && treeInitialization!=FULL)
		Log::getInstance()->error("Error in IndividualFactory::IndividualFactory(unsigned char maxHeight,ETreeInitialization treeInitialization): treeInizialization should be GROW of FULL.");
}
		

IndividualFactory::~IndividualFactory()
{}


gp::Gene* IndividualFactory::generateBranch(unsigned char height,ETreeInitialization treeInitialization)
{
        unsigned char flags=0;
	height--;

        if (treeInitialization==FULL)
		flags = height?FUNCTION:TERMINAL;
        else if (treeInitialization==GROW)
		flags = height?FUNCTION|TERMINAL:TERMINAL;

	Gene* branchRoot = generateGene((EGenerateGeneFlags)flags);
	if (flags&TERMINAL && ~flags&FUNCTION && branchRoot->getArity()) {
		Log::getInstance()->error("Error: generateGene returns a function where generateBranch requests a teminal");
		delete branchRoot;
		throw Exception("Error in IndividualFactory: generateGene returns a function where generateBranch requests a teminal");
	} else if (~flags&TERMINAL && flags&FUNCTION && !branchRoot->getArity()) {
		Log::getInstance()->error("Error: generateGene returns a teminal where generateBranch requests a function");
		delete branchRoot;
		throw Exception("Error in IndividualFactory: generateGene returns a teminal where generateBranch requests a function");
	}

	generateChildren(branchRoot, height);

	return branchRoot;
}

void IndividualFactory::generateChildren(Gene* branchRoot, unsigned char height)
{
	for (int i=0;i<branchRoot->getArity(); i++)
		branchRoot->setArgument(i,generateBranch(height, treeInitialization));
}

Gene*  IndividualFactory::generateTree()
{
       return generateBranch(maxHeight,treeInitialization);
}
}
}

