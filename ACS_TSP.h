#ifndef __ACO_TSP__
#define __ACO_TSP__

#define ROU       0.1     // ρ
#define POP       10      // 蚁群的种群大小
#define CITY_NUM  30      // 城市数量
#define ITER      2500    // 迭代次数
#define BETA      2       // β
#define Q         0.9     // 概率
#define ALPHA     0.1     // α

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
#include <algorithm>

struct ant {
	int city[CITY_NUM + 1];
	double fitness;
	int start;
};

boost::mt19937 rng((unsigned)time(0)); 
boost::uniform_01<boost::mt19937&> u01(rng);

int judge_exist_in_array(int *array, int length, int element)
{
	int i = 0;

	for (; i < length; i++) {
		if (element == array[i])
			return 1;
	}
	return 0;

}

double sum(double *array, int length, int upper, int *city) {
	int i;
	double sum = 0;

	for (i = 0; i < length; i++) {
		if (judge_exist_in_array(city, upper, i))
			continue;
		sum += array[i];
	}
	return sum;
}


double euclidean_distance(double *data1, double *data2)
{
	int i;
	double distance = 0.0;
	for (i = 0; i < 2; i++) {
		distance += (data1[i] - data2[i]) * (data1[i] - data2[i]);
	}
	return sqrt(distance);
}

void calculate_distance_array(double data[][2], double distance[][CITY_NUM])
{
	int i, j;

	for (i = 0; i < CITY_NUM; i++) {
		for (j = 0; j < CITY_NUM; j++) {
			distance[i][j] = euclidean_distance(data[i], data[j]);
		}
	}
}

void read_data(char *file_name, double data[][2])
{
	FILE *fp;
	int index[CITY_NUM] = { 0 };   
	double temp;
	int i, j;
	int count = 0;  
	if ((fp = fopen(file_name, "rb")) == NULL) {
		fprintf(stderr, "请确认%s文件是否存在\n", file_name);
		exit(1);
	}
	while (1 == fscanf(fp, "%lf", &temp)) {
		if (count % 3 == 0) {
			count++;
			continue;
		}
		data[count / 3][count % 3 - 1] = temp;
		count++;
	}

	fclose(fp);
}
#endif
