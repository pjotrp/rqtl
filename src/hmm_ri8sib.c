/**********************************************************************
 * 
 * hmm_ri8sib.c
 * 
 * copyright (c) 2005-9, Karl W Broman
 *
 * last modified Apr, 2009
 * first written Mar, 2005
 *
 *     This program is free software; you can redistribute it and/or
 *     modify it under the terms of the GNU General Public License,
 *     version 3, as published by the Free Software Foundation.
 * 
 *     This program is distributed in the hope that it will be useful,
 *     but without any warranty; without even the implied warranty of
 *     merchantability or fitness for a particular purpose.  See the GNU
 *     General Public License, version 3, for more details.
 * 
 *     A copy of the GNU General Public License, version 3, is available
 *     at http://www.r-project.org/Licenses/GPL-3
 * 
 * C functions for the R/qtl package
 *
 * Contains: init_ri8sib, emit_ri8sib, step_ri8sib, step_special_ri8sib,
 *           calc_genoprob_ri8sib, calc_genoprob_special_ri8sib,
 *           argmax_geno_ri8sib, sim_geno_ri8sib,
 *           est_map_ri8sib, nrec2_ri8sib, logprec_ri8sib, est_rf_ri8sib,
 *           marker_loglik_ri8sib, calc_pairprob_ri8sib, 
 *           errorlod_ri8sib, calc_errorlod_ri8sib
 *
 * These are the init, emit, and step functions plus
 * all of the hmm wrappers for 8-way RIL by sib mating 
 * (i.e., the Collaborative Cross).
 *
 * Genotype codes:    1-8
 * "Phenotype" codes: 0=missing; otherwise binary 1-255, with bit i
 *                    indicating SNP compatible with parent i
 *
 **********************************************************************/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <R.h> 
#include <Rmath.h>
#include <R_ext/PrtUtil.h>
#include "hmm_main.h"
#include "hmm_ri8sib.h"
#include "hmm_bc.h"

double init_ri8sib(int true_gen)
{
  return(LN_0125);
}

double emit_ri8sib(int obs_gen, int true_gen, double error_prob)
{
  if(obs_gen==0) return(0.0);
  if(obs_gen & (1 << (true_gen-1))) return(log(1.0-error_prob));
  else return(log(error_prob)); 
}
    
  
double step_ri8sib(int gen1, int gen2, double rf, double junk) 
{
  if(gen1 == gen2) 
    return(log(1.0-rf)-log(1.0+6.0*rf));
  else 
    return(log(rf)-log(1.0+6.0*rf));
}


/* this is needed for est.map; estimated recombination fractions on the RIL scale */
double step_special_ri8sib(int gen1, int gen2, double rf, double junk) 
{
  if(gen1 == gen2) 
    return(log(1.0-rf));
  else 
    return(log(rf)-log(7.0));
}


void calc_genoprob_ri8sib(int *n_ind, int *n_mar, int *geno, 
			  double *rf, double *error_prob, double *genoprob) 
{
  calc_genoprob(*n_ind, *n_mar, 8, geno, rf, rf, *error_prob, genoprob,
		init_ri8sib, emit_ri8sib, step_ri8sib);
}

  
void calc_genoprob_special_ri8sib(int *n_ind, int *n_mar, int *geno, 
				  double *rf, double *error_prob, double *genoprob) 
{
  calc_genoprob_special(*n_ind, *n_mar, 8, geno, rf, rf, *error_prob, genoprob,
			init_ri8sib, emit_ri8sib, step_ri8sib);
}

  
void argmax_geno_ri8sib(int *n_ind, int *n_pos, int *geno,
			double *rf, double *error_prob, int *argmax)
{
  argmax_geno(*n_ind, *n_pos, 8, geno, rf, rf, *error_prob,
	      argmax, init_ri8sib, emit_ri8sib, step_ri8sib);
}


void sim_geno_ri8sib(int *n_ind, int *n_pos, int *n_draws, int *geno, 
		     double *rf, double *error_prob, int *draws) 
{
  sim_geno(*n_ind, *n_pos, 8, *n_draws, geno, rf, rf, *error_prob, 
	   draws, init_ri8sib, emit_ri8sib, step_ri8sib);
}

/* for estimating map, must do things with recombination fractions on the RIL scale */
void est_map_ri8sib(int *n_ind, int *n_mar, int *geno, double *rf, 
		    double *error_prob, double *loglik, int *maxit, 
		    double *tol, int *verbose)
{
  int i;

  /* expand rf */
  for(i=0; i< *n_mar-1; i++) rf[i] = 7.0*rf[i]/(1.0+6.0*rf[i]);

  est_map(*n_ind, *n_mar, 8, geno, rf, rf, *error_prob, 
	  init_ri8sib, emit_ri8sib, step_special_ri8sib, nrec_bc, nrec_bc,
	  loglik, *maxit, *tol, 0, *verbose);

  /* contract rf */
  for(i=0; i< *n_mar-1; i++) rf[i] = rf[i]/(7.0-6.0*rf[i]);
}


/* expected no. recombinants */
double nrec2_ri8sib(int obs1, int obs2, double rf)
{
  int n1, n2, n12, nr, and, i, nstr=8;

  if(obs1==0 || obs2==0) return(-999.0); /* this shouldn't happen */

  n1=n2=n12=0;
  and = obs1 & obs2;
  
  /* count bits */
  for(i=0; i<nstr; i++) {
    if(obs1 & 1<<i) n1++;
    if(obs2 & 1<<i) n2++;
    if(and  & 1<<i) n12++;
  }
  
  nr = n1*n2-n12;
  return( (double)nr*rf / (7.0*(double)n12*(1.0-rf) + (double)nr*rf) );
}

/* log [joint probability * 8] */
double logprec_ri8sib(int obs1, int obs2, double rf)
{
  int n1, n2, n12, nr, and, i, nstr=8;
  
  if(obs1==0 || obs2==0) return(-999.0); /* this shouldn't happen */

  n1=n2=n12=0;
  and = obs1 & obs2;
  
  /* count bits */
  for(i=0; i<nstr; i++) {
    if(obs1 & 1<<i) n1++;
    if(obs2 & 1<<i) n2++;
    if(and  & 1<<i) n12++;
  }
  
  nr = n1*n2-n12;
  return( log(7.0*(double)n12*(1.0-rf) + (double)nr*rf) );
}

void est_rf_ri8sib(int *n_ind, int *n_mar, int *geno, double *rf, 
		   int *maxit, double *tol)
{
  est_rf(*n_ind, *n_mar, geno, rf, nrec2_ri8sib, logprec_ri8sib, 
	 *maxit, *tol, 1);
}

void marker_loglik_ri8sib(int *n_ind, int *geno,
			  double *error_prob, double *loglik)
{
  marker_loglik(*n_ind, 8, geno, *error_prob, init_ri8sib, emit_ri8sib,
		loglik);
}

void calc_pairprob_ri8sib(int *n_ind, int *n_mar, int *geno, 
			  double *rf, double *error_prob, 
			  double *genoprob, double *pairprob) 
{
  calc_pairprob(*n_ind, *n_mar, 8, geno, rf, rf, *error_prob, genoprob,
		pairprob, init_ri8sib, emit_ri8sib, step_ri8sib);
}

double errorlod_ri8sib(int obs, double *prob, double error_prob)
{
  double p=0.0, temp;
  int n=0, i;

  if(obs==0 || (obs == (1<<8) - 1)) return(0.0);
  for(i=0; i<8; i++) {
    if(obs & 1<<i) p += prob[i];
    else n++;
  }
  if(n==0 || n==8) return(0.0); /* shouldn't happen */
  
  p = (1.0-p)/p;
  temp = (double)n*error_prob/7.0;

  p *= (1.0 - temp)/temp;

  if(p < TOL) return(-12.0);
  else return(log10(p));
}

void calc_errorlod_ri8sib(int *n_ind, int *n_mar, int *geno, 
		      double *error_prob, double *genoprob, 
		      double *errlod)
{
  calc_errorlod(*n_ind, *n_mar, 8, geno, *error_prob, genoprob,
		errlod, errorlod_ri8sib);
}

/* end of hmm_ri8sib.c */
