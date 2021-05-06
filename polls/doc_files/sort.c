#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void merge_with(int **data, int **tmp, int **tmp_res, int self, int oth, int s, int num) {
	if (oth >= s || oth < 0)
		return;

	MPI_Request req;
	MPI_Isend(*data, num, MPI_INT, oth, 0, MPI_COMM_WORLD, &req);
	MPI_Recv(*tmp, num, MPI_INT, oth, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	int i = 0, j = 0;
	if (self < oth) {
		i = 0;
		j = 0;
		for (int k = 0; k < num; ++k) {
			if ((*data)[i] < (*tmp)[j])
				(*tmp_res)[k] = (*data)[i++];
			else
				(*tmp_res)[k] = (*tmp)[j++];
		}
	} else {
		i = num - 1;
		j = num - 1;
		for (int k = num - 1; k >= 0; --k) {
			if ((*data)[i] > (*tmp)[j])
				(*tmp_res)[k] = (*data)[i--];
			else
				(*tmp_res)[k] = (*tmp)[j--];
		}
	}

	int *t = *data;
	*data = *tmp_res;
	*tmp_res = t;
}

int cmp(const void *l, const void *r) {
	return *((int *) l) - *((int *) r);
}

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);

	int r = 0, s = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &r);
	MPI_Comm_size(MPI_COMM_WORLD, &s);

	int num = argc > 1 ? atoi(argv[1]) : 10;
	int *data = (int *) calloc(num, sizeof(int));
	int *tmp = (int *) calloc(num, sizeof(int));
	int *tmp_res = (int *) calloc(num, sizeof(int));

	int buf_size = num * sizeof(int) + MPI_BSEND_OVERHEAD;
//	char *buf = (char *) calloc(buf_size, sizeof(char));
//	MPI_Buffer_attach(buf, buf_size);

	srandom(r);
	for (int i = 0; i < num; ++i) {
		data[i] = random();
//		data[i] = s * num - r * num + i;
	}

	qsort(data, num, sizeof(int), cmp);

	for (int i = 0; i < s / 2; ++i) {
		if (r % 2 == 0) {
			merge_with(&data, &tmp, &tmp_res, r, r + 1, s, num);
			merge_with(&data, &tmp, &tmp_res, r, r - 1, s, num);
		} else {
			merge_with(&data, &tmp, &tmp_res, r, r - 1, s, num);
			merge_with(&data, &tmp, &tmp_res, r, r + 1, s, num);
		}
	}

//	MPI_Buffer_detach(&buf, &buf_size);
//	free(buf);

	MPI_Finalize();

	printf("%d: [", r);
	for (int i = 0; i < num; ++i) {
		printf("%d ", data[i]);
	}
	printf("]\n");

	free(data);
	free(tmp);
	free(tmp_res);
}
