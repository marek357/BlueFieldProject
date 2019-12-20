#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int comm_size, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_size);
    char hostname[100];
    int err[100];
    gethostname(hostname, 100);
    printf("[%d] parent at %s: jestem procesem %d a size mojego komunikatora to %d\n", rank, hostname, rank, comm_size);
    MPI_Info info;
    MPI_Comm comm, parent, wynikowy_com;
    MPI_Info_create(&info);
    MPI_Info_set(info, "host", hostname);
    MPI_Comm_get_parent(&parent);
    MPI_Comm_spawn("child", NULL, 1, MPI_INFO_NULL, 0, MPI_COMM_WORLD, &comm, err);

    MPI_Intercomm_merge(comm, 1, &wynikowy_com);
    char args[100];
    int subcom_size;
    MPI_Comm_size(wynikowy_com, &subcom_size);
    printf("[%d] parent: rozmiar interkomunikatora to %d \n", rank, subcom_size);

    MPI_Finalize();
    return 0;
}
