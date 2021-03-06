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
 * Alessandro Bahgat Shehata - ale (DOT) bahgat (AT) gmail (DOT) com
 * Daniele Castagna - daniele (DOT) castagna (AT) gmail (DOT) com
 * 
 */

#include <iostream>

#include "IndividualFactory.h"
#include "Gene.h"

#include "../../util/util.h"

using genetiK::util::Log;
using genetiK::util::Exception;

namespace genetiK
{
namespace gp
{
namespace st
{
			

IndividualFactory::IndividualFactory(unsigned char maxHeight,gp::ETreeInitialization treeInitialization,GeneType rootType) : 
gp::IndividualFactory(maxHeight,treeInitialization),
rootType(rootType)
{
}

IndividualFactory::~IndividualFactory() 
{
}

gp::Gene* IndividualFactory::generateTree(){
	nextGeneType = rootType;
	return gp::IndividualFactory::generateTree();
}
	
gp::Gene* IndividualFactory::generateBranch(unsigned char height,ETreeInitialization treeInitialization)
{
	unsigned char flags=0;
	height--;

	if (treeInitialization==FULL)
		flags = height?FUNCTION:TERMINAL;
	else if (treeInitialization==GROW)
		flags = height?FUNCTION|TERMINAL:TERMINAL;
	
	Gene* branchRoot = dynamic_cast<Gene*>(generateGene((EGenerateGeneFlags)flags));
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

void IndividualFactory::generateChildren(gp::Gene* branchRoot, unsigned char height) {
	for (int i=0;i<branchRoot->getArity(); i++){
		setNextType(static_cast<Gene*>(branchRoot)->getArgumentType(i));
		branchRoot->setArgument(i,generateBranch(height, getTreeInitialization()));
	}
}

}
}
}
