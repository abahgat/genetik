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

#include <iostream>
#include <stdlib.h>

using namespace std;

#include "Individual.h"

#include "IndividualFactory.h"
#include "Gene.h"

#include "../util/util.h"

using genetiK::util::Log;

namespace genetiK
{
namespace gp
{

Individual::Individual(IndividualFactory* individualFactory) :
                individualFactory( individualFactory )
{
	root = individualFactory->generateTree();
}

Individual::Individual(const Individual& individual) :
		genetiK::Individual(individual),
		individualFactory( individual.individualFactory )
{
	root = individual.root->copyBranch();
}
Individual::~Individual(void)
{
        delete root;
}


void Individual::setLabels()
{
	root->setHeight(0);
        root->setLabels(0);
}

using genetiK::util::Random;
int Individual::mutate(const double mutationProbabilty)
{
	Random* random = Random::getImplementation();
	if (random->getNextReal()>mutationProbabilty)
		return 1;
	
	setLabels();
	unsigned int randomNode = random->getNextInt(root->getCardinality());

        Gene* oldBranch = extract(randomNode);
	Gene* newBranch = individualFactory->generateBranch(individualFactory->getMaxHeight()-oldBranch->getHeight(),GROW);

        substituteBranch(randomNode,newBranch);

        delete oldBranch;

        return 0;

}

int Individual::crossOver(genetiK::Individual* i,genetiK::Individual** child1,genetiK::Individual** child2)
{
        setLabels();
	
	Individual* gpI = dynamic_cast<Individual*>(i);
	if (!gpI)
		Log::getInstance()->error("Error! GPIndividual::crossOver. Individual* i should be gp::Individual, cast failed!");

        gpI->setLabels();


	Individual* gpChild1 = NULL;
	Individual* gpChild2 = NULL;

	Random* random = Random::getImplementation();

	unsigned int randomNode1 = random->getNextInt( root->getCardinality());
	Gene* node1 = extract(randomNode1);

	unsigned int randomNode2 = random->getNextInt( gpI->root->getCardinality());

	Gene* node2 = gpI->extract(randomNode2);

	if (  node1->getHeight() + node2->getBranchDepth() <= individualFactory->getMaxHeight()) {

		gpChild1 = static_cast<Individual*>(copy());
		gpChild1->setLabels();
		Gene* branchToDelete = gpChild1->substituteBranch(randomNode1,node2->copyBranch());
                       delete branchToDelete;
		
	}

	if (node2->getHeight() + node1->getBranchDepth() <= individualFactory->getMaxHeight()) {
		gpChild2 = static_cast<Individual*>(gpI->copy());
		gpChild2->setLabels();
		Gene* branchToDelete = gpChild2->substituteBranch(randomNode2,node1->copyBranch());
		delete branchToDelete;

		
	}

	*child1 = gpChild1;
	*child2 = gpChild2;
        

	
        return 0;

}

Gene* Individual::substituteBranch(const unsigned int label, Gene* newBranch)
{
        if (label == 0) {
		Gene* oldRoot = root;
                root = newBranch;
//		Log::getInstance()->warn("Warning, substituting root");
                return oldRoot;
        } else {
                return root->substituteBranch(label,newBranch);
        }
}

Gene* Individual::extract(const unsigned int label)const
{
	if (label == 0){
//		Log::getInstance()->warn("Warning, extracting root");
		return root;
	}
        else
                return root->extract(label);
}

std::string Individual::toString()const{
	return root->toString();
}


unsigned int Individual::getCardinality() const{
	return root->getCardinality();
}

IndividualFactory*  Individual::getIndividualFactory() const{
	return individualFactory;
}
}
}


