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

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <sstream>

#include "StronglyTypedGeneticProgramming.h"

#include "../include/libGenetiK.h"

using namespace std;
using namespace genetiK;

namespace genetiKEx
{

enum EvenOddExampleType{
	BOOLEAN,
	EVENODD,
	INTEGER	
};

enum{
	EVEN,
	ODD
};

class If : public genetiK::gp::st::Gene
{
private:
	gp::st::GeneType ifType;
public:
	If(gp::st::GeneType ifType) :
	gp::st::Gene(ifType,3,BOOLEAN,ifType,ifType),
	ifType(ifType){};
	
	gp::Gene*	copy() const { return new If(ifType); }
	util::Variant evaluate(){
		return getArgument(0)->evaluate().getBoolean()? getArgument(1)->evaluate(): getArgument(2)->evaluate();
	}
	string toString()const{ return "(if " + gp::Gene::toString() + ")";}
};



class Modulo : public genetiK::gp::st::Gene
{
public:
	Modulo() :
	gp::st::Gene(INTEGER,2,INTEGER,INTEGER){}
	gp::Gene*	copy() const { return new Modulo(); };
	util::Variant evaluate(){
		/* n%0 generates an exception*/
		int argOne = getArgument(1)->evaluate().getInteger();
		if (argOne==0)
			return argOne;
		return getArgument(0)->evaluate().getInteger()%argOne; 
	}
	string toString()const{ return "(% " + gp::Gene::toString() + ")";}
};

class NVariable : public genetiK::gp::st::Gene
{
private:
	unsigned int* nPointer;	
public:
	NVariable(unsigned int* nPointer) : gp::st::Gene(INTEGER,0), nPointer(nPointer){}
	gp::Gene*	copy() const { return new NVariable(nPointer); }
	util::Variant evaluate(){
		return (int)*nPointer;
	}
	string toString()const{ return string(" n ");}
};

class Constant : public genetiK::gp::st::Gene
{
	private:
		unsigned int value;	
	public:
		Constant(unsigned int value) : gp::st::Gene(INTEGER,0), value(value){}
		gp::Gene*	copy() const { return new Constant(value); }
		util::Variant evaluate(){
			return util::Variant( (int)value );
		}
		string toString()const{ stringstream buff;buff << " " << value << " "; return buff.str(); }
};

class EvenOdd : public genetiK::gp::st::Gene
{
	private:
		unsigned char evenOdd;	
	public:
		EvenOdd(unsigned char evenOdd) : gp::st::Gene(EVENODD,0), evenOdd(evenOdd){}
		gp::Gene*	copy() const { return new EvenOdd(evenOdd); }
		util::Variant evaluate(){
			return util::Variant( (int)evenOdd );
		}
		string toString()const{ return string(evenOdd==EVEN?" even ":" odd ");}
};

class True : public genetiK::gp::st::Gene
{
	public:
		True() : gp::st::Gene(BOOLEAN,0){}
		gp::Gene*	copy() const { return new True(); }
		util::Variant evaluate(){
			return util::Variant(true);
		}
		string toString()const{ return string(" true ");}
};

class Equal : public genetiK::gp::st::Gene
{
	private:
		unsigned int value;	
	public:
		Equal() : gp::st::Gene(BOOLEAN,2,INTEGER,INTEGER){}
		gp::Gene*	copy() const { return new Equal(); }
		util::Variant evaluate(){
			return getArgument(0)->evaluate().getInteger() ==  getArgument(1)->evaluate().getInteger();
		}
		string toString() const{ return "(= " + gp::Gene::toString() + ")";}
};

class EvenOddIndividualFactory : public gp::st::IndividualFactory
{
	private:
		unsigned int* nPointer;	
	public:
	EvenOddIndividualFactory(unsigned char maxHeigth, unsigned int* nPointer) : 
		gp::st::IndividualFactory(maxHeigth,gp::GROW,EVENODD),
	nPointer(nPointer){}
	
	Individual* generate();
	
	
	gp::Gene* generateGene(EGenerateGeneFlags flags)
	{
		util::Random* random = util::Random::getImplementation();
		if (flags&TERMINAL && flags&FUNCTION){
			switch(getNextType()){
				case BOOLEAN:
					return new Equal();
				case INTEGER:
					switch(random->getNextInt(4)){
						case 0: return new Constant(1);
						case 1: return new Constant(2);
						case 2: return new NVariable(nPointer);
						case 3: return new Modulo();
					}
				case EVENODD:
					switch(random->getNextInt(3)){
						case 0: return new EvenOdd(EVEN);
						case 1: return new EvenOdd(ODD);
						case 2: return new If(EVENODD);
					}
			}
		}else if (flags&TERMINAL){
			switch(getNextType()){
				case BOOLEAN:
					return new True();
				case INTEGER:
					switch(random->getNextInt(3)){
						case 0: return new Constant(1);
						case 1: return new Constant(2);
						case 2: return new NVariable(nPointer);	
					}
				case EVENODD:		
					switch(random->getNextInt(2)){
						case 0: return new EvenOdd(EVEN);
						case 1: return new EvenOdd(ODD);
					}
			}
		}else if (flags&FUNCTION){
			switch(getNextType()){
				case BOOLEAN: return new Equal();
				case INTEGER: return new Modulo();
				case EVENODD: return new If(EVENODD);
			}			
		}
			
		util::Log::getInstance()->error("Error in generateGene");
		
		return NULL;
}
};

class EvenOddIndividual : public gp::st::Individual
{
	unsigned int* nPointer;
	double cFitness;
public:
	EvenOddIndividual(EvenOddIndividualFactory* factory,unsigned int* nPointer) :
		gp::st::Individual(factory),
		nPointer(nPointer),
		cFitness(-1){}
		
	EvenOddIndividual(const EvenOddIndividual& individual) :  gp::st::Individual(individual),nPointer(individual.nPointer),cFitness(-1){};
		
	double fitness()
	{
		if (cFitness == -1) {
			const unsigned int testCasesNumber=1000;
		
			double correct = 0;
		
			for (unsigned int i=0; i<testCasesNumber; i++){
				*nPointer = i;
				unsigned char odd = i%2;
				unsigned char evaluation = getRoot()->evaluate().getInteger();

				if(evaluation==ODD && odd)
					correct++;
				if(evaluation==EVEN && !odd)
					correct++;
			}

			cFitness = correct;
		}
		return cFitness;
	}
	
	genetiK::Individual* copy()const{
		EvenOddIndividual* i = new EvenOddIndividual(*this);
		return i;
	}

};

Individual* EvenOddIndividualFactory::generate() 
{ 
	EvenOddIndividual* ind = new EvenOddIndividual(this,nPointer);
	return ind;
}



StronglyTypedGeneticProgramming::StronglyTypedGeneticProgramming()
{
}
StronglyTypedGeneticProgramming::~StronglyTypedGeneticProgramming()
{
}
int StronglyTypedGeneticProgramming::run(){
	
	unsigned int n=0;
	util::Log* log = util::Log::getInstance();
	log->setLevel(util::INFO);

	EvenOddIndividualFactory* individualFactory = new EvenOddIndividualFactory(8,&n);
	StopCriterionMaxIteration* stopCriterion = new StopCriterionMaxIteration(100);
	//SelectionMethod* seletionMethod = new RouletteWheel();
	SelectionMethod* seletionMethod = new TournamentSelection(16);

	EvolutionaryAlgorithm alg(256,individualFactory,stopCriterion, seletionMethod);
	alg.run();
	log->info( alg.getPopulation()->getBest()->toString() );

	util::Log::deleteInstance();
	util::Random::deleteImplementation();
	
	return 0;
}

}
