#include <stdio.h>
#include <mpi.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <unistd.h>
#include <unistd.h>

int main() {
    int comm_size, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_size);
    char hostname[100];
    int err[100];
    gethostname(hostname, 100);
    printf("%s", hostname);
    printf("jestem procesem %d a size mojego komunikatora to %d", rank, comm_size);
    MPI_Info info;
    MPI_Comm comm, parent, wynikowy_com;
    MPI_Info_create(&info);
    MPI_Info_set(info, "host", hostname);
    MPI_Comm_get_parent(&parent);
    MPI_Comm_spawn("snd", NULL, 1, MPI_INFO_NULL, 0, MPI_COMM_WORLD, &comm, err);
    MPI_Intercomm_merge(comm, 1, &wynikowy_com);
    char args[100];
    int subcom_size;
    MPI_Comm_size(wynikowy_com, &subcom_size);
    printf(" rozmiar interkomunikatora to %d \n", subcom_size);

    MPI_Finalize();
    return 0;
}
