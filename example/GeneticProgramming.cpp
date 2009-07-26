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

#include "GeneticProgramming.h"


#include "../include/libGenetiK.h"


using namespace std;
using namespace genetiK;

namespace genetiKEx
{
class Addition : public genetiK::gp::Gene
{
public:
	Addition() : gp::Gene(2){};
	gp::Gene*	copy() const { return new Addition(); }
	util::Variant evaluate(){
		return getArgument(0)->evaluate().getReal() + getArgument(1)->evaluate().getReal();
	}
	string toString()const{ return "(+ " + gp::Gene::toString() + ")";}
};

class Multiplication : public gp::Gene
{
public:
	Multiplication() : gp::Gene(2){}
	gp::Gene*	copy() const { return new Multiplication(); };
	util::Variant evaluate(){
		return getArgument(0)->evaluate().getReal() * getArgument(1)->evaluate().getReal();
	}
	string toString()const{ return "(* " + gp::Gene::toString() + ")";}
};

class XVariable : public gp::Gene
{
private:
	double*	xPointer;	
public:
	XVariable(double *xPointer) : gp::Gene(0), xPointer(xPointer){}
	gp::Gene*	copy() const { return new XVariable(xPointer); }
	util::Variant evaluate(){
		return  *xPointer;
	}
	string toString()const{ return string(" x ");}
};

class RegressionIndividualFactory : public gp::IndividualFactory
{
	private:
		double* xPointer;	
	public:
	RegressionIndividualFactory(unsigned char maxHeight, double* xPointer) : 
		gp::IndividualFactory(maxHeight,gp::GROW),
	xPointer(xPointer){}
	
	Individual* generate();
		
	gp::Gene* generateGene(EGenerateGeneFlags flags)
	{
		flags = flags;
		
		if (flags&TERMINAL && flags&FUNCTION){
			switch(util::Random::getImplementation()->getNextInt(7)){
				
				case 0:case 1:case 2:return new Addition();
				case 3:case 4:case 5:return new Multiplication();
				case 6:return new XVariable(xPointer);
			}
		}else if (flags&TERMINAL) return new XVariable(xPointer);
		else if (flags&FUNCTION){
			switch(util::Random::getImplementation()->getNextInt(2)){
				
				case 0:return new Addition();
				case 1:return new Multiplication();
			}			
		}
			
		util::Log::getInstance()->error("Error in generateGene");
		
		return NULL;
	}
};

class RegressionIndividual : public gp::Individual
{
	
	double*	xPointer;
		
public:
	RegressionIndividual(RegressionIndividualFactory* factory,double* xPointer) :
		gp::Individual(factory),
		xPointer(xPointer){}
		
	RegressionIndividual(const RegressionIndividual& individual) : gp::Individual(individual),xPointer(individual.xPointer){};
		
	/* Try to find f(x) = x^3 + x with 0 <= x < 1*/
	double fitness()
	{
		const unsigned char testCasesNumber=100;
		
		double quadraticDistance = 0;
		
		for (int i=0; i<testCasesNumber; i++){
			*xPointer = double(i)/testCasesNumber;
			double distance = getRoot()->evaluate().getReal() - (pow(*xPointer,3) + *xPointer );
			quadraticDistance += distance*distance;
		}
		
		quadraticDistance /= testCasesNumber;
		
		return 1/quadraticDistance;
	}
	
	
	genetiK::Individual* copy() const{
		return new RegressionIndividual(*this);
	}

};

Individual* RegressionIndividualFactory::generate()
{ 
	RegressionIndividual* ind = new RegressionIndividual(this,xPointer);
	return ind;
}



GeneticProgramming::GeneticProgramming()
{
}
GeneticProgramming::~GeneticProgramming()
{
}
int GeneticProgramming::run(){
	
	double x=0;
	util::Log* log = util::Log::getInstance();
	log->setLevel(util::INFO);

	RegressionIndividualFactory* individualFactory = new RegressionIndividualFactory(6,&x);
	StopCriterionMaxIteration* stopCriterion = new StopCriterionMaxIteration(32);
//	SelectionMethod* selectionMethod = new RouletteWheel();
	SelectionMethod* selectionMethod = new TournamentSelection(16);
	EvolutionaryAlgorithm alg(128,individualFactory,stopCriterion,selectionMethod);
	alg.run();
	log->info( alg.getPopulation()->getBest()->toString() );
	
	util::Log::deleteInstance();
	util::Random::deleteImplementation();
	
	return 0;
}

}
