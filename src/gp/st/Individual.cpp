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

#include "../../util/util.h"
#include "Individual.h"

#include "IndividualFactory.h"
#include "Gene.h"

using genetiK::util::Log;

namespace genetiK
{
namespace gp
{
namespace st
{

Individual::Individual(IndividualFactory* individualFactory) :
		gp::Individual(individualFactory)
{
}
Individual::Individual(const Individual& individual) :
		genetiK::gp::Individual(individual)
{
}

Individual::~Individual(void)
{
}

using genetiK::util::Random;
int Individual::mutate(const double mutationProbabilty)
{
	Random* random = Random::getImplementation();
	if (random->getNextReal()>mutationProbabilty)
		return 1;
	setLabels();
	unsigned int randomNode = random->getNextInt(getCardinality());

	Gene* oldBranch = static_cast<Gene*>(extract(randomNode));
	IndividualFactory* stFactory = static_cast<IndividualFactory*>(getIndividualFactory());
	stFactory->setNextType(oldBranch->getType());
	gp::Gene* newBranch = stFactory->generateBranch(stFactory->getMaxHeight()-oldBranch->getHeight(),GROW);

	substituteBranch(randomNode,newBranch);

	delete oldBranch;

	return 0;

}

int Individual::crossOver(genetiK::Individual* i,genetiK::Individual** child1,genetiK::Individual** child2)
{
	setLabels();
	
	Individual* stI = dynamic_cast<Individual*>(i);
	if (!stI)
		Log::getInstance()->error("Error!! GPIndividual::crossOver. Individual* i should be gp::Individual, cast failed!");

	stI->setLabels();


	Individual* stChild1 = NULL;
	Individual* stChild2 = NULL;
	*child1 = *child2 = NULL;
	
	
	Random* random = Random::getImplementation();

	unsigned int randomNode1 = random->getNextInt( getCardinality());
	Gene* node1 = static_cast<Gene*>(extract(randomNode1));
	
	// st begin
	unsigned int randomNode2 = 0;
	list<Gene*> listByType = stI->extractListByType(node1->getType());
	
	if (!listByType.size()){
		return 1;
	}

	randomNode2 = random->getNextInt( listByType.size());

	Gene* node2;
	 
	list<Gene*>::iterator j=listByType.begin();
	for (unsigned int i=0; i<listByType.size(); j++,i++)
		if (i==randomNode2){
			node2 = *j;
 			break;
		}

	// st end
		
	
	if (  node1->getHeight() + node2->getBranchDepth() <= getIndividualFactory()->getMaxHeight()) {

		stChild1 = static_cast<Individual*>(copy());
		stChild1->setLabels();
		gp::Gene* branchToDelete = stChild1->substituteBranch(randomNode1,node2->copyBranch());
		delete branchToDelete;
		
	}
		
	if (node2->getHeight() + node1->getBranchDepth() <= getIndividualFactory()->getMaxHeight()) {
		stChild2 = static_cast<Individual*>(stI->copy());
		stChild2->setLabels();
		gp::Gene* branchToDelete = stChild2->substituteBranch(node2->getLabel(),node1->copyBranch());
		delete branchToDelete;

		
	}
	
	*child1 = stChild1;
	*child2 = stChild2;
        

	return 0;

}

list<Gene*> Individual::extractListByType(GeneType geneType)
{
	Gene* stRoot = static_cast<Gene*>(getRoot());
	if (stRoot->getType() ==geneType){
		list<Gene*> childList = stRoot->extractListByType(geneType);
		childList.push_back(stRoot);
		return childList;
	}else
		return stRoot->extractListByType(geneType);
}


}
}
}


