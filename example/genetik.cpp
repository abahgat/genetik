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
#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>

#include "GeneticAlgorithm.h"
#include "GeneticProgramming.h"
#include "StronglyTypedGeneticProgramming.h"

using namespace std;

int printHelp();
int main(int argc, char *argv[])
{
        static struct option longOptions[] = {
                                                     {"geneticprogramming",no_argument,0,'p'},
                                                     {"geneticalgorithm",no_argument,0,'a'},
                                                     {"stronglytyped",no_argument,0,'s'},
                                                     {"help",no_argument,0,'h'},
                                                     {0,0,0,0}
                                             };

        int optionIndex = 0;
        int c=0;


        c=getopt_long(argc,argv,"pash",longOptions,&optionIndex);
        switch(c) {
        case 'p': {
                        cout << "Running genetic programming example" << endl;
                        genetiKEx::GeneticProgramming gp;
                        gp.run();
                }
                break;

        case 'a': {
                        cout << "Running genetic algorithm example" << endl;
                        genetiKEx::GeneticAlgorithm ga;
                        ga.run();
                }
                break;

	case 's':{
             	   cout << "Running strongly typed genetic programming example" << endl;
			genetiKEx::StronglyTypedGeneticProgramming stgp;
			stgp.run();
		}
                break;
        default:
        case 'h':
                printHelp();
                break;
        }

        return EXIT_SUCCESS;
}

int printHelp()
{
        cout << "Usage: example [OPTION]" << endl;
        cout << "This program includes three GenetiK Lib sample." << endl << endl;
	cout << "-a, --geneticalgorithm			Run the `genetic algorithm` test" << endl;
        cout << "-p, --geneticprogramming		Run the `genetic programming `test" << endl;
        cout << "-s, --stronglytyped			Run the `strongly typed genetic programming` test" << endl;
        cout << "-h, --help				Show this help" << endl;

        return 0;
}
