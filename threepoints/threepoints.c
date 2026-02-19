#include <stdio.h>
#include <stdlib.h>

struct Point {
	float x, y, z;
};

void sameLine(struct Point a, struct Point b, struct Point c){
	//do the cross product between ab and ac

	float abx = b.x - a.x;	
	float aby = b.y - a.y;
	float abz = b.z - a.z;

	float acx = c.x - a.x;
	float acy = c.y - a.y;
	float acz = c.z - a.z;

	float crossX = aby * acz - abz * acy;
	float crossY = abz * acx - abx * acz;
	float crossZ = abx * acy - aby * acx;

	if (crossX == 0 && crossY == 0 && crossZ == 0){
		printf("YES\n");
	}
	else {
		printf("NO\n");
	}
}

int main(void) {
	struct Point p1, p2, p3;
	printf("What is the first point?\n");
	scanf("%f %f %f", &p1.x, &p1.y, &p1.z);
	printf("What is the second point?\n");
	scanf("%f %f %f", &p2.x, &p2.y, &p2.z);
	printf("What is the third point?\n");
	scanf("%f %f %f", &p3.x, &p3.y, &p3.z);

	sameLine(p1, p2, p3);
  return 0;
}
