#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "image.h"
#include "list.h"


double _height[50][3]=
{
    {  0.000 , -46.097 , 2.162 },
    {  0.000 , -46.097 , 2.162 },
    {  0.000 , -33.520 , 1.657 },
    {  0.000 , -47.481 , 2.211 },
    {  0.000 , -46.130 , 2.163 },
    {  0.000 , -32.636 , 1.618 },
    {  0.000 , -20.773 , 2.128 },
    {  0.000 , -16.472 , 1.701 },
    {  0.000 , -10.018 , 1.566 },
    {  0.000 , -7.636 , 1.993  },
    {  0.000 , -9.389 , 1.305  },
    {  0.000 , -8.089 , 1.266  },
    {  0.000 , -8.089 , 1.970  },
    {  0.000 , -6.895 , 1.561  },
    {  0.000 , -6.895 , 2.521  },
    {  0.000 , -10.287 , 1.250 },
    {  0.000 , -15.667 , 2.700 },
    {  0.000 , -7.710 , 0.939  },
    {  0.000 , -14.843 , 1.537 },
    {  0.000 , -15.508 , 1.604 },
    {  0.000 , -23.720 , 1.207 },
    {  0.000 , -33.248 , 2.193 },
    {  0.000 , -48.533 , 2.248 },
    {  0.000 , -32.273 , 1.602 },
    {  0.000 , -26.074 , 1.319 },
    {  0.000 , -14.494 , 1.502 },
    {  0.000 , -26.783 , 1.352 },
    {  0.000 , -21.688 , 1.478 },
    {  0.000 , -9.990 , 1.735  },
    {  0.000 , -6.584 , 1.605  },
    {  0.000 , -7.466 , 1.689  },
    {  0.000 , -7.466 , 2.599  },
    {  0.000 , -8.037 , 1.678  },
    {  0.000 , -8.026 , 1.257  },
    {  0.000 , -5.442 , 2.466  },
    {  0.000 , -18.263 , 1.567 },
    {  0.000 , -14.308 , 2.471 },
    {  0.000 , -14.931 , 1.288 },
    {  0.000 , -11.135 , 1.738 },
    {  0.000 , -23.448 , 1.194 },
    {  0.000 , -21.515 , 1.834 },
    {  0.000 , -20.518 , 1.402 },
    {  0.000 , -15.137 , 1.567 },
    {  0.000 , -9.894 , 1.546  },
    {  0.000 , -9.894 , 1.718  },
    {  0.000 , -9.894 , 1.718  },
    {  0.000 , -9.894 , 1.203  },
    {  0.000 , -9.894 , 1.203  },
    {  0.000 , -9.894 , 1.203  },
    {  0.000 , -16.085 , 1.385 }

};

data random_batch(data d, int n)
{
    matrix X = {0};
    matrix y = {0};
    X.shallow = y.shallow = 1;
    X.rows = y.rows = n;
    X.cols = d.X.cols;
    y.cols = d.y.cols;
    X.data = calloc(n, sizeof(double*));
    y.data = calloc(n, sizeof(double*));
    int i;
    for(i = 0; i < n; ++i){
        int ind = rand()%d.X.rows;
        X.data[i] = d.X.data[ind];//brandon //here has problem
        y.data[i] = d.y.data[ind];
    }
    data c;
    c.X = X;
    c.y = y;
    return c;
}

list *get_lines(char *filename)
{
    char *path;
    FILE *file = fopen(filename, "r");
    if(!file) {
        fprintf(stderr, "Couldn't open file %s\n", filename);
        exit(0);
    }
    list *lines = make_list();
    while((path=fgetl(file))){
        list_insert(lines, path);
    }
    fclose(file);
    return lines;
}

data load_classification_data(char *images, char *label_file, int bias)
{
    list *image_list = get_lines(images);
    list *label_list = get_lines(label_file);
    int k = label_list->size;
    char **labels = (char **)list_to_array(label_list);

    int n = image_list->size;
    node *nd = image_list->front;
    int cols = 0;
    int i;
    int count = 0;
    matrix X;
    matrix y = make_matrix(n, k);
    while(nd){
        char *path = (char *)nd->val;
        image im = load_image(path);
        if (!cols) {
            cols = im.w*im.h*im.c;
            X = make_matrix(n, cols + (bias != 0));//wx+b , b is bias
        }
        for (i = 0; i < cols; ++i){
            X.data[count][i] = im.data[i];
        }
        if(bias) X.data[count][cols] = 1;

        for (i = 0; i < k; ++i){
            if(strstr(path, labels[i])){
                y.data[count][i] = 1;
            }
        }
        ++count;
        nd = nd->next;
    }
    free_list(image_list);
    data d;
    d.X = X;
    d.y = y;
    return d;
}

data load_installHeigh_data(double height[][3], int bias , int rows)
//data load_installHeigh_data(int bias)
{
    int n = rows;//50;//image_list->size;
    int cols = 0;
    int i;
    int count = 0;
    matrix X;
    matrix y = make_matrix(n, 30);//make_matrix(n, 1);//make_matrix(n, 30);
    while(count < n){

        if (!cols) {
            //cols = im.w*im.h*im.c;
            cols = 1;
            X = make_matrix(n, cols + (bias != 0));//wx+b , b is bias
        }
        for (i = 0; i < cols; ++i){
            //X.data[count][i] = im.data[i];
            X.data[count][i] = height[count][1]/90.0;//tilt normalize
        }
        if(bias) X.data[count][cols] = 1;

        #if 1
        i = (int)(height[count][2]+0.5);
        y.data[count][i] = 1;
        printf("count %d , x : %5.3f , y : %5.3f %d\n",count,X.data[count][0],height[count][2],i);
        #else
        y.data[count][0] = height[count][2];

        printf("count %d , x : %5.3f , y : %5.3f\n",count,X.data[count][0],y.data[count][0]);
        #endif

        /* for (i = 0; i < k; ++i){ */

            /* if(strstr(path, labels[i])){ */
            /*     y.data[count][i] = 1; */
            /* } */
        /* } */
        ++count;
    }
    data d;
    d.X = X;
    d.y = y;
    return d;
}


char *fgetl(FILE *fp)
{
    if(feof(fp)) return 0;
    size_t size = 512;
    char *line = malloc(size*sizeof(char));
    if(!fgets(line, size, fp)){
        free(line);
        return 0;
    }

    size_t curr = strlen(line);

    while((line[curr-1] != '\n') && !feof(fp)){
        if(curr == size-1){
            size *= 2;
            line = realloc(line, size*sizeof(char));
            if(!line) {
                fprintf(stderr, "malloc failed %ld\n", size);
                exit(0);
            }
        }
        size_t readsize = size-curr;
        if(readsize > INT_MAX) readsize = INT_MAX-1;
        fgets(&line[curr], readsize, fp);
        curr = strlen(line);
    }
    if(line[curr-1] == '\n') line[curr-1] = '\0';

    return line;
}

void free_data(data d)
{
    free_matrix(d.X);
    free_matrix(d.y);
}



