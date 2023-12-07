#include <stdio.h>
#include <stdlib.h>


typedef struct {
    double x;
    double y;
} point_t;


typedef struct {
    point_t point_1;
    point_t point_2;
}rectangle_t;


int isInRectangle(point_t point, rectangle_t rectangle){
    double max_y = rectangle.point_1.y < rectangle.point_2.y ? rectangle.point_2.y : rectangle.point_1.y;
    double max_x = rectangle.point_1.x < rectangle.point_2.x ? rectangle.point_2.x : rectangle.point_1.x;
    double min_y = rectangle.point_1.y < rectangle.point_2.y ? rectangle.point_1.y : rectangle.point_2.y;
    double min_x = rectangle.point_1.x < rectangle.point_2.x ? rectangle.point_1.x : rectangle.point_2.x;
    if(point.x <= max_x && point.x >= min_x && point.y <= max_y && point.y >= min_y)
        return 1;
    return 0;
}


int isEmpty(rectangle_t rectangle, int n, point_t* points){
    for (int i = 0; i < n; ++i) {
        if (points[i].x == rectangle.point_1.x && points[i].y == rectangle.point_1.y ||
                points[i].x == rectangle.point_2.x && points[i].y == rectangle.point_2.y)
            continue;
        if (isInRectangle(points[i], rectangle)) return 0;
    }
    return 1;
}


int main(void) {
    system("chcp 65001");

    FILE *in = fopen("WIDERECT.IN", "r");
    int n;
    fscanf(in, "%d", &n);
    point_t *points = (point_t *) malloc(n * sizeof(point_t));

    for (int i = 0; i < n; ++i) {
        fscanf(in, "%lf", &points[i].x);
        fscanf(in, "%lf", &points[i].y);
    }

    fclose(in);
    rectangle_t *rectangles = (rectangle_t *) malloc(n * (n - 1) / 2 * sizeof(rectangle_t));
    int k = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (points[i].x != points[j].x && points[i].y != points[j].y){
                rectangles[k].point_1 = points[i];
                rectangles[k].point_2 = points[j];
                k++;
            }
        }
    }
    int count = 0;
    for (int i = 0; i < k; ++i) {
        if(isEmpty(rectangles[i], n, points)) count++;
    }

    FILE *out = fopen("WIDERECT.OUT", "w");
    fprintf(out, "%d", count);
    fclose(out);

    free(rectangles);
    free(points);
    return 0;
}
