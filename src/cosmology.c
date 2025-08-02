#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// #include <gsl/gsl_integration.h>

#include "cosmology.h"

void print_parameters(cosmology *params){
  printf("\nSelected cosmology:\n");
  printf("---------------------\n");
  printf("Hubble parameter H0 = %.3f\n", params->H0);
  printf("Omega matter = %.6f\n", params->Omat);
  printf("Omega radiation = %.6f\n", params->Orad);
  printf("Omega lambda = %.6f\n", params->Olam);
  printf("Omega k = %.6f\n", params->Ok);
  printf("\n");
}

double Ez(double z, cosmology *params){

  double H0 = params->H0;
  double Omat = params->Omat;
  double Orad = params->Orad;
  double Olam = params->Olam;
  double Ok = params->Ok;

  double zp1 = (1. + z);
  double e2z = Orad*zp1*zp1*zp1*zp1 + Omat*zp1*zp1*zp1 + Ok*zp1*zp1 + Olam;

  return sqrt(e2z);

}

double distance_hubble(cosmology *params){
  return SPEEDOFLIGHT / (params->H0);  
}


double distance_comoving(double z, cosmology *params){
  double dz = z / SIMPSONSTEPS;
  double sum = 1. / Ez(0, params) + 1. / Ez(z, params);

  for (int i = 1 ; i < SIMPSONSTEPS ; i++) {
    double w = i * dz;
    sum += (i % 2 == 0 ? 2 : 4) * (1. / Ez(w, params));
  }

  return distance_hubble(params) * sum * dz / 3.0;
}


double distance_transverse(double z, cosmology *params){
  if (params->Ok == 0) {
    return distance_comoving(z, params);
  } else if (params->Ok > 0 ) {
    double sOk = sqrt(params->Ok);
    double dH = distance_hubble(params);
    return dH * sinh(sOk * distance_comoving(z, params) / dH) / sOk;
  } else {
    double sOk = sqrt( - params->Ok);
    double dH = distance_hubble(params);
    return dH * sin(sOk * distance_comoving(z, params) / dH) / sOk;
  }
}

double distance_angular(double z, cosmology *params){
  return distance_transverse(z, params) / (1. + z);
}

double distance_luminosity(double z, cosmology *params){
  return distance_transverse(z, params) * (1. + z);
}
