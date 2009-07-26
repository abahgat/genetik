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

/*! @defgroup genetiK Common GenetiK framework
@brief Main framework

This is the base module of GenetiK framework
*/

/*!
@file src/genetik.h
@ingroup genetiK
@brief Main include file for genetiK namespace

This file groups all header files of elements of genetiK

*/

#ifndef GENETIK_H
#define GENETIK_H

#include "EvolutionaryAlgorithm.h"
#include "RouletteWheel.h"
#include "SelectionMethod.h"
#include "IndividualFactory.h"
#include "StopCriterion.h"
#include "Individual.h"
#include "StopCriterionMaxIteration.h"
#include "Population.h"
#include "TournamentSelection.h"
#include "RankingSelection.h"

#endif
