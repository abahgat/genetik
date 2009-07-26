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
#include <stdlib.h>
#include <stdarg.h>
using namespace std;

#include "Gene.h"


namespace genetiK
{
namespace gp
{
namespace st
{

Gene::Gene(GeneType type,unsigned char arity,...) :
gp::Gene(arity),
type(type),
argumentType(NULL)
{
	va_list args;
	if (arity)
		argumentType = new GeneType[arity];

	va_start(args, arity);
	for (unsigned char i=0; i<arity; i++)
		argumentType[i] = va_arg(args,int);
	va_end(args);
}


Gene::~Gene()
{
	delete[] argumentType;
}

list<Gene*> Gene::extractListByType(GeneType geneType)
{
	list<Gene*> typedList;
	
	for (unsigned char i=0; i<getArity(); i++){
		Gene* stGene = static_cast<Gene*>(getArgument(i));
		if (argumentType[i]==geneType)
			typedList.push_back(stGene);
		list<Gene*> childList = stGene->extractListByType(geneType);
		typedList.splice( typedList.end(),childList);
	}
	return typedList;
}

}
}
}

