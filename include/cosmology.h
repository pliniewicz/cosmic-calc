#ifndef COSMOLOGY_H
#define COSMOLOGY_H

#define SPEEDOFLIGHT 299792.458 // km/s
#define PARSEC 3.08567758128e+18
#define KILO 1e3 
#define MEGA 1e6
#define GIGA 1e9
#define METER 100 // cm
#define MC2 510998.950 // eV
#define PLANCKH 4.135667696e-15 // eV * s

#define SIMPSONSTEPS 25000

typedef struct {

  double H0;
  double Omat;
  double Orad;
  double Olam;
  double Ok;

} cosmology;

void print_parameters(cosmology *params);

double Ez(double z, cosmology *params);

double distance_hubble(cosmology *params);

double distance_comoving(double z, cosmology *params);

double distance_transverse(double z, cosmology *params);

double distance_angular(double z, cosmology *params);

double distance_luminosity(double z, cosmology *params);


#endif // !COSMOLOGY_H
