#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cosmology.h"
#include "fluxes.h"
#include "fileIO.h"

int main(int argc, char *argv[]) {
    char *config_file = "data/cosmology.json";
    double z = 0.035008;
    int distance_flag = 0;
    int fluxes_flag = 0;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if ((strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--cosmology") == 0) && i + 1 < argc) {
            config_file = argv[i + 1];
            i++;
        } else if ((strcmp(argv[i], "-z") == 0 || strcmp(argv[i], "--redshift") == 0) && i + 1 < argc) {
            z = atof(argv[i + 1]);
            i++;
        } else if (strcmp(argv[i], "--distance") == 0) {
            distance_flag = 1;
        } else if (strcmp(argv[i], "--flux") == 0) {
            fluxes_flag = 1;
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0){
          puts("version: 0.1.0 date: 02/08/2025");
          return 0;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){
          puts("Tool for some common tasks regarding distances and fluxes in cosmology; pliniewicz @ 2025");
          puts("Options:");
          puts("No arguments: prints default files and redshift; default redshift is a value for Pictor A");
          puts("-v --version:   prints current version and exits");
          puts("-c --cosmology: sets the argument JSON file as cosmology settings");
          puts("-z --redshift:  sets the argument as the redshift used");
          puts("--distance:     for given cosmology & redshift calculates various distances");
          puts("--flux:         for given cosmology & redshift computes luminosities from fluxes provided in a JSON file (with errors)");
          return 0;
        }
    }

    // Execute based on flags
    cosmology params;
    if (!read_config(config_file, &params)) {
      fprintf(stderr, "Error reading configuration file %s\n", config_file);
    return 1;
    }

    if (distance_flag) {
        print_parameters(&params);

        double dH, dC, dA, dL;

        dH = distance_hubble(&params);

        dC = distance_comoving(z, &params);

        dA = distance_angular(z, &params);

        dL = distance_luminosity(z, &params);

        printf("Hubble distance is %.2f Mpc\n", dH);
        printf("Comoving distance at z = %.3f is %.2f Mpc\n", z, dC);
        printf("Angular diameter distance at z = %.3f is %.2f Mpc\n", z, dA);
        printf("This gives a scale of %.4f kpc/\"\n", dA/206.264806);
        printf("Luminosity distance at z = %.3f is %.2f Mpc\n", z, dL);
    }
    if (fluxes_flag) {

        int count;
        flux* fluxes = read_fluxes("data/fluxes.json", &count);
        luminosity* lums = malloc(count * sizeof(luminosity));
        if (!fluxes){
          printf("Error reading flux data!\n");
        }
        for (int i = 0; i < count; i++) {
        convert_from_flux(&fluxes[i], &lums[i], &params, z);
        printf("Cluster %d: Frequency=%.2e, Flux=%.2e, Flux Error=%.2e\n",
               i, lums[i].frequency, lums[i].lum, lums[i].lum_err);
        }
        
        free(lums);
    }
    if (!distance_flag && !fluxes_flag) {
        printf("Config file: %s\n", config_file);
        printf("Redshift: %.5f\n", z);
    }

    return 0;
}
