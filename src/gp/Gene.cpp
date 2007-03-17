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
#include <stdarg.h>
using namespace std;

#include "Gene.h"
#include "../util/Log.h"

using genetiK::util::Log;

namespace genetiK
{
namespace gp
{


Gene::Gene(unsigned char arity) :
                cardinality(1),
                height(0),
                label(0),
                arity(arity),
                argument(NULL)
{
	if (arity){
        	argument = new Gene*[arity];
		if (!argument)
			Log::getInstance()->error("Error! out of memory!");
	}
}

Gene::~Gene()
{
        for(unsigned char i=0; i<arity;i++)
                delete argument[i];
        delete[] argument;
}

unsigned int Gene::setLabels(unsigned int label)
{
        this->label = label++;
        cardinality = 1;


	unsigned char maxSubBranchDepth = 0;
        for(unsigned char i=0; i<arity;i++) {
                argument[i]->height = height+1;
                label = argument[i]->setLabels(label);
                cardinality += argument[i]->cardinality;

		if (argument[i]->branchDepth > maxSubBranchDepth)
			maxSubBranchDepth = argument[i]->branchDepth;
        }
	branchDepth = maxSubBranchDepth+1;
        return label;
}


Gene* Gene::substituteBranch( unsigned int label, Gene* newBranch)
{
        if (this->label == label) {
                Log::getInstance()->error("Error! gpGene::substitueSubTree!");
        }

        for(unsigned char i=0; i<arity;i++) {
                if (argument[i]->getLabel() == label) {
                        Gene* oldBranch = argument[i];
                        argument[i] = newBranch;
			return oldBranch;
		} else if (argument[i]->getLabel()<label && i<arity-1?argument[i+1]->getLabel()>label:true)
                        return argument[i]->substituteBranch(label,newBranch);

        }
        Log::getInstance()->error("Error! gpGene::substitueSubTree. You have searched in the wrong place!");
        return NULL;
}

Gene* Gene::extract( unsigned int label)
{
        if (this->label == label) {
                Log::getInstance()->error("Error! gpGene::extract!");
        }

        for(unsigned char i=0; i<arity;i++) {
                if (argument[i]->getLabel() == label)
                        return argument[i];
		else if ( argument[i]->getLabel()<label && i<arity-1?argument[i+1]->getLabel()>label:true )
                        return argument[i]->extract(label);

        }

        Log::getInstance()->error("Error! gpGene::extract. You have searched in the wrong place!");
        return NULL;
}

Gene* Gene::copyBranch() const
{
        Gene* branchCopy = copy();
        for(unsigned char i=0; i<arity;i++)
                branchCopy->argument[i] = argument[i]->copyBranch();

        return branchCopy;
}

string Gene::toString() const
{
	string rep;
	for(unsigned char i=0; i<arity;i++) 
		rep += argument[i]->toString();
	return rep;
}

Gene* Gene::getArgument(unsigned char i){ 
	
	if (i >= arity)
 	       Log::getInstance()->error("Error! Gene::getArgument(unsigned char i). i should be less than arity");
	return argument[i]; 
}

void Gene::setArgument(unsigned char i, Gene* newArgument)
{ 
	if (i >= arity)
 	       Log::getInstance()->error("Error! Gene::setArgument(unsigned char i, Gene* newArgument). i should be less than arity");
	argument[i] = newArgument; 
}

}
}




