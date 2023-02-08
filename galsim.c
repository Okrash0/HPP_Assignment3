#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <pthread.h>

// dT shoud be 0.00001

typedef struct particle
{
    double pos_x;
    double pos_y;
    double mass;
    double vel_x;
    double vel_y;
    double brightness;

    double F_x;
    double F_y;
} particle;

void symplectic_euler(particle *particles, int N, double delta_t);

int main(int argc, char *argv[])
{
    // check if the number of arguments is correct
    // N filename nsteps delta_t graphics

    /*
    filename is the filename of the file to read the initial configuration from
    nsteps is the number of timesteps
    delta_t is the timestep delta t
    graphics is 1 or 0 meaning graphics on/off.

    */
    if (argc != 6)
    {
        printf("Not enough arguments \n");
        printf("Expected: N filename nsteps delta_t graphics \n");
    }

    // read the arguments
    int N = atoi(argv[1]);
    char *filename = argv[2];
    int nsteps = atoi(argv[3]);
    double delta_t = atof(argv[4]);
    int graphics = atoi(argv[5]);

    // check if the arguments are valid
    if (N < 1)
    {
        printf("N must be greater than 0 \n");
        return 1;
    }
    if (nsteps < 1)
    {
        printf("nsteps must be greater than 0 \n");
        return 1;
    }
    if (delta_t < 0)
    {
        printf("delta_t must be greater than 0 \n");
        return 1;
    }
    if (graphics != 0 && graphics != 1)
    {
        printf("graphics must be 0 or 1 \n");
        return 1;
    }

    // open the file
    FILE *FILE_ptr;
    FILE_ptr = fopen(filename, "rb");
    if (FILE_ptr == NULL)
    {
        printf("Could not open file %s \n", filename);
        return 1;
    }

    // allocate memory for the particles
    particle *particles = (particle *)malloc(N * sizeof(particle));

    printf("Reading data \n");
    for (int i = 0; i < N; i++)
    {
        // read the data from the file
        fread(&particles[i].pos_x, sizeof(double), 1, FILE_ptr);
        fread(&particles[i].pos_y, sizeof(double), 1, FILE_ptr);
        fread(&particles[i].mass, sizeof(double), 1, FILE_ptr);
        fread(&particles[i].vel_x, sizeof(double), 1, FILE_ptr);
        fread(&particles[i].vel_y, sizeof(double), 1, FILE_ptr);
        fread(&particles[i].brightness, sizeof(double), 1, FILE_ptr);
    }

    // close the file
    fclose(FILE_ptr);

    printf("10 first starting positions \n");
    for (int i = 0; i < 10; i++)
    {
        printf("Particle %d: (%f, %f) \n", i, particles[i].pos_x, particles[i].pos_y);
    }

    clock_t t;
    t = clock();

    // run the simulation
    printf("Running simulation \n");
    for (int i = 0; i < nsteps; i++)
        symplectic_euler(particles, N, delta_t);

    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;

    // print final positions
    printf("10 first final positions \n");
    for (int i = 0; i < 10; i++)
    {
        printf("Particle %d: (%f, %f) \n", i, particles[i].pos_x, particles[i].pos_y);
    }

    // write the final positions to a file
    FILE_ptr = fopen("result.gal", "wb");
    if (FILE_ptr == NULL)
    {
        printf("Could not open file result.gal \n");
        return 1;
    }

    for (int i = 0; i < N; i++)
    {
        fwrite(&particles[i].pos_x, sizeof(double), 1, FILE_ptr);
        fwrite(&particles[i].pos_y, sizeof(double), 1, FILE_ptr);
        fwrite(&particles[i].mass, sizeof(double), 1, FILE_ptr);
        fwrite(&particles[i].vel_x, sizeof(double), 1, FILE_ptr);
        fwrite(&particles[i].vel_y, sizeof(double), 1, FILE_ptr);
        fwrite(&particles[i].brightness, sizeof(double), 1, FILE_ptr);

        particles[i].F_x = 0;
        particles[i].F_y = 0;
    }

    // free the memory
    free(particles);

    printf("------------ \n");
    printf("Time taken: %f \n", time_taken);

    return 0;
}

double F(double m_i, double m_j, double r, double G)
{

    double epsilon = 0.001;
    double r_d = r + epsilon;

    return (-G) * m_i * m_j / (r_d * r_d * r_d);
}

// wonkers just nu
void symplectic_euler(particle *particles, int N, double delta_t)
{
    double G = 100 / N;

    double a_x, a_y, r_x, r_y, r, F_, F_x, F_y;

    for (int i = 0; i < N; i++)
    {
        a_x = 0;
        a_y = 0;
        for (int j = i + 1; j < N; j++)
        {

            if (i != j)
            {
                // cakculate the distance between the particles
                r_x = particles[i].pos_x - particles[j].pos_x;
                r_y = particles[i].pos_y - particles[j].pos_y;

                r = sqrt(r_x * r_x + r_y * r_y);

                // calculate the force
                F_ = F(particles[i].mass, particles[j].mass, r, G);
                F_x = F_ * r_x;
                F_y = F_ * r_y;

                particles[i].F_x += F_x;
                particles[i].F_y += F_y;

                particles[j].F_x -= F_x;
                particles[j].F_y -= F_y;
            }
        }

        // calculate the acceleration
        a_x = particles[i].F_x;
        a_y = particles[i].F_y;
        a_x = a_x / particles[i].mass;
        a_y = a_y / particles[i].mass;

        particles[i].F_x = 0;
        particles[i].F_y = 0;

        // update the velocity
        particles[i].vel_x += a_x * delta_t;
        particles[i].vel_y += a_y * delta_t;

        // update the position
        particles[i].pos_x += particles[i].vel_x * delta_t;
        particles[i].pos_y += particles[i].vel_y * delta_t;
    }
}