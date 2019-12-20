#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <unistd.h>

char hostname[100];
int main() {
    int comm_size, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_size);
    int err[100];
    gethostname(hostname, 100);
    printf("[%d] child at %s: jestem procesem %d a size mojego komunikatora to %d\n",rank, hostname, rank, comm_size);
    MPI_Comm parent, wynikowy_com;
    MPI_Comm_get_parent(&parent);
    MPI_Intercomm_merge(parent, 0, &wynikowy_com);
    char args[100];
    int subcom_size;
    MPI_Comm_size(wynikowy_com, &subcom_size);
    printf("[%d] child: rozmiar interkomunikatora to %d \n", rank, subcom_size);
    MPI_Finalize();
    return 0;
}
