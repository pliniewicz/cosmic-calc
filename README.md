# Cosmic calculator

## Cosmological distances

Defined in `cosmology.h` allows for calculation of Hubble distance $d_H$, comoving distance $d_C$, transverse comoving distance $d_M$ and luminosity distance $d_L$, after [David W. Hogg](https://arxiv.org/abs/astro-ph/9905116). Integration is via Simpson's rule, number of steps is defined in header as `#define SIMSONSTEPS`. 

Cosmology is loaded from a JSON file in the `data` folder. User sets $H_0$, $\Omega_M$, $\Omega_{rad}$ and $\Omega_\Lambda$. From those, $\Omega_k$ is inferred via Friedmann equation.

## Luminosity calculation

User can also provide flux measurements in the form of a JSON file that has structure: ($\nu$, $\nu F_\nu$, $\Delta \nu F_\nu$): frequency, flux, flux error. Program can handle arbitrary number of measurements. It then recomputes them into $\nu L_\nu$ luminosities. Everything is computed in the CGS system of units, so input fluxes should be in erg cm$^{-2}$ s$^{-1}$ Hz$^{-1}$ and output luminosities are in erg s$^{-1}$.

## Usage

Default input files (examples) are in `data` folder. Use `-h` or `--help` for available options. 

Redshift is provided via command line, e.g. `-z 2.3` or `--redshift 2.3`, otherwise some default value is used (for Pictor A). Cosmology can be changed either by modyfing the default `data/cosmology.json` file or by supplying option `-c` or `--cosmology` with a name of the JSON file, e.g. `-c data/cosmology1.json`. If no other options are invoked, it prints the name of the cosmology file, it's content and redshift that would be used.

If option `--distance` is used, the program will then compute and print out distances: $d_H$, $d_C$, $d_A$, corresponding scaling kpc/arcsec and $d_L$.

If option `--flux` is used, the program will scan `data/fluxes.json` for it's content and, for a given redshift, use luminosity distance to compute luminosity $\nu L_\nu$ (eq. 24 in Hogg). If you don't have an error, set it to 0 or just ignore.

Both options can be used simultaneously.

## Dependencies 

* [DaveGamble/cJSON](https://github.com/DaveGamble/cJSON)
* [Gnu Scientific Library](https://www.gnu.org/software/gsl/)
