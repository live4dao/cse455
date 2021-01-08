#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "matrix.h"
#include "image.h"
#include "test.h"
#include "args.h"

/*
double Train_height[50][3]=
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
*/

double Train_height[77][3]=
{
    {    333.92   , -22.819 , 1.551        },
    {    355.53    ,    -29.722 , 1.487     },
    {    346.89    ,    -45.314 , 2.133     },
    {    17.39    ,    -26.747 , 1.350     },
    {    22.17    ,    -21.663 , 1.477     },
    {    33.34    ,    -15.233 , 1.576     },
    {    38.22    ,    -12.456 , 1.294     },
    {    34.37    ,    -7.197 , 2.255      },
    {    8.69    ,    -8.760 , 1.371      },
    {    354.33    ,    -14.541 , 1.506     },
    {    351.02    ,    -7.949 , 1.659      },
    {    244.93    ,    -7.949 , 1.383      },
    {    336.14    ,    -6.793 , 3.075      },
    {    329.3    ,    -7.584 , 1.452      },
    {    342.02    ,     -11.860 , 1.028    },
    {    323.01    ,    -6.458 , 1.912      },
    {    317.77    ,     -8.021 , 1.116     },
    {    311.11    ,    -17.730 , 1.523     },
    {    314.17    ,    -7.565 , 1.185      },
    {    307.8    ,     -6.131 , 1.602     },
    {    300.26    ,     -8.059 , 2.523     },
    {    315.31    ,    -11.624 , 1.612     },
    {    317.55    ,    -22.723 , 1.545     },
    {    311.29    ,    -29.436 , 1.966     },
    {    334.84    ,    -14.489 , 1.251     },
    {    349.17    ,    -12.846 , 1.334     },
    {    339.87    ,    -6.757 , 1.530      },
    {    328.45    ,    -11.306 , 1.960     },
    {    356.68    ,    -14.387 , 1.491     },
    {    16.52    ,     -19.436 , 1.997    },
    {    22.07    ,    -20.589 , 1.407     },
    {    40.27    ,    -11.100 , 1.155     },
    {    44.76    ,    -9.004 , 1.409      },
    {    36.86    ,    -15.154 , 1.568     },
    {    36.13    ,    -48.264 , 2.239     },
    {    36.13    ,     -37.341 , 1.820    },
    {    326.61    ,    -49.832 , 2.292     },
    {    348.83    ,    -33.160 , 1.641     },
    {    355.17    ,    -17.903 , 1.844     },
    {    347.39    ,    -9.139 , 1.747      },
    {    319.85    ,     -10.682 , 1.298    },
    {    301.91    ,     -7.908 , 1.789     },
    {    307.5    ,    -6.054 , 1.582      },
    {    314.32    ,    -7.598 , 1.454      },
    {    324.27    ,    -8.411 , 1.463      },
    {    353.92    ,    -14.093 , 1.461     },
    {    13.89    ,    -12.838 , 1.555     },
    {    19.13    ,    -10.902 , 1.513     },
    {    32.03    ,     -15.508 , 1.604    },
    {    11.61    ,    -18.493 , 1.903     },
    {    23.98    ,    -5.670 , 1.581      },
    {    3.22    ,     -8.098 , 1.409     },
    {    345.36    ,    -9.779 , 1.359      },
    {    339.76    ,     -9.779 , 1.529     },
    {    341.27    ,    -7.925 , 1.792      },
    {    331.33    ,    -22.987 , 1.172     },
    {    317.87    ,    -8.386 , 1.021      },
    {    302.7    ,    -14.157 , 2.690     },
    {    310.56    ,    -5.346 , 2.422      },
    {    342        ,    -14.494 , 1.251     },
    {    12.59    ,    -30.900 , 1.541     },
    {    24.86    ,    -20.894 , 1.427     },
    {    14.58    ,    -15.187 , 1.572     },
    {    21.95    ,    -10.202 , 1.240     },
    {    12.73    ,    -20.512 , 2.453     },
    {    28.16    ,    -26.621 , 1.344     },
    {    8.14    ,    -17.411 , 1.496     },
    {    352.79    ,    -30.680 , 1.531     },
    {    336.9     ,    -31.584 , 1.571     },
    {    341.85    ,    -45.462 , 2.138     },
    {    316.6     ,   -40.972 , 1.967      },
    {    305.97    ,    -19.787 , 2.370     },
    {    313.89    ,    -9.493 , 1.484      },
    {    320.54    ,    -9.493 , 1.484      },
    {    329.32    ,    -7.991 , 1.529      },
    {    324.46    ,    -6.546 , 1.710      },
    {    335.69    ,    -6.546 , 1.710      }

};
double Test_height[6][3] = {

    /*
    { 0.000 , -24.547 , 1.246  },
    { 0.000 , -30.430 , 2.026  },
    { 0.000 , -14.497 , 1.001  },
    { 0.000 , -8.122 , 1.272   },
    { 0.000 , -13.374 , 1.388  },
    { 0.000 , -13.374 , 1.388  },
    { 0.000 , -16.027 , 1.657  },
    { 0.000 , -14.994 , 1.552  },
    { 0.000 , -10.141 , 1.232  },
    { 0.000 , -11.536 , 1.200  },
    { 0.000 , -7.642 , 1.197   }
    */
    { 338.56 , -24.014 , 1.221  },
    { 348.67 , -32.691 , 1.620  },
    { 342.81 , -47.157 , 2.200  },
    { 322.91 , -43.383 , 2.061   },
    { 312.23 , -29.694 , 1.981  },
    { 344.49 , -7.653 , 1.598  }
};


void feature_normalize2(image im)
{
    int i;
    float min = im.data[0];
    float max = im.data[0];
    for(i = 0; i < im.w*im.h*im.c; ++i){
        if(im.data[i] > max) max = im.data[i];
        if(im.data[i] < min) min = im.data[i];
    }
    for(i = 0; i < im.w*im.h*im.c; ++i){
        im.data[i] = (im.data[i] - min)/(max-min);
    }
}

int tests_total = 0;
int tests_fail = 0;

int within_eps(float a, float b){
    return a-EPS<b && b<a+EPS;
}

int same_point(point p, point q)
{
    return within_eps(p.x, q.x) && within_eps(p.y, q.y);
}

int same_matrix(matrix m, matrix n)
{
    if(m.rows != n.rows || m.cols != n.cols) return 0;
    int i,j;
    for(i = 0; i < m.rows; ++i){
        for(j = 0; j < m.cols; ++j){
            if(!within_eps(m.data[i][j], n.data[i][j])) return 0;
        }
    }
    return 1;
}

int same_image(image a, image b){
    int i;
    if(a.w != b.w || a.h != b.h || a.c != b.c) {
        //printf("Expected %d x %d x %d image, got %d x %d x %d\n", b.w, b.h, b.c, a.w, a.h, a.c);
        return 0;
    }
    for(i = 0; i < a.w*a.h*a.c; ++i){
        if(!within_eps(a.data[i], b.data[i])) 
        {
            //printf("The value should be %f, but it is %f! \n", b.data[i], a.data[i]);
            return 0;
        }
    }
    return 1;
}

void test_get_pixel(){
    image im = load_image("data/dots.png");
    // Test within image
    TEST(within_eps(0, get_pixel(im, 0,0,0)));
    TEST(within_eps(1, get_pixel(im, 1,0,1)));
    TEST(within_eps(0, get_pixel(im, 2,0,1)));

    // Test padding
    TEST(within_eps(1, get_pixel(im, 0,3,1)));
    TEST(within_eps(1, get_pixel(im, 7,8,0)));
    TEST(within_eps(0, get_pixel(im, 7,8,1)));
    TEST(within_eps(1, get_pixel(im, 7,8,2)));
    free_image(im);
}

void test_set_pixel(){
    image gt = load_image("data/dots.png");
    image d = make_image(4,2,3);
    set_pixel(d, 0,0,0,0); set_pixel(d, 0,0,1,0); set_pixel(d, 0,0,2,0); 
    set_pixel(d, 1,0,0,1); set_pixel(d, 1,0,1,1); set_pixel(d, 1,0,2,1); 
    set_pixel(d, 2,0,0,1); set_pixel(d, 2,0,1,0); set_pixel(d, 2,0,2,0); 
    set_pixel(d, 3,0,0,1); set_pixel(d, 3,0,1,1); set_pixel(d, 3,0,2,0); 

    set_pixel(d, 0,1,0,0); set_pixel(d, 0,1,1,1); set_pixel(d, 0,1,2,0); 
    set_pixel(d, 1,1,0,0); set_pixel(d, 1,1,1,1); set_pixel(d, 1,1,2,1); 
    set_pixel(d, 2,1,0,0); set_pixel(d, 2,1,1,0); set_pixel(d, 2,1,2,1); 
    set_pixel(d, 3,1,0,1); set_pixel(d, 3,1,1,0); set_pixel(d, 3,1,2,1); 

    // Test images are same
    TEST(same_image(d, gt));
    free_image(gt);
    free_image(d);
}

void test_grayscale()
{
    image im = load_image("data/colorbar.png");
    image gray = rgb_to_grayscale(im);
    image gt = load_image("figs/gray.png");
    TEST(same_image(gray, gt));
    free_image(im);
    free_image(gray);
    free_image(gt);
}

void test_copy()
{
    image gt = load_image("data/dog.jpg");
    image c = copy_image(gt);
    TEST(same_image(c, gt));
    free_image(gt);
    free_image(c);
}

void test_clamp()
{
    image im = load_image("data/dog.jpg");
    image c = copy_image(im);
    set_pixel(im, 10, 5, 0, -1);
    set_pixel(im, 15, 15, 1, 1.001);
    set_pixel(im, 130, 105, 2, -0.01);
    set_pixel(im, im.w-1, im.h-1, im.c-1, -.01);

    set_pixel(c, 10, 5, 0, 0);
    set_pixel(c, 15, 15, 1, 1);
    set_pixel(c, 130, 105, 2, 0);
    set_pixel(c, im.w-1, im.h-1, im.c-1, 0);
    clamp_image(im);
    TEST(same_image(c, im));
    free_image(im);
    free_image(c);
}

void test_shift()
{
    image im = load_image("data/dog.jpg");
    image c = copy_image(im);
    shift_image(c, 1, .1);
    TEST(within_eps(c.data[0], im.data[0]));
    TEST(within_eps(c.data[im.w*im.h + 13], im.data[im.w*im.h+13] + .1));
    TEST(within_eps(c.data[2*im.w*im.h + 72], im.data[2*im.w*im.h+72]));
    TEST(within_eps(c.data[im.w*im.h + 47], im.data[im.w*im.h+47] + .1));
    free_image(im);
    free_image(c);
}

void test_rgb_to_hsv()
{
    image im = load_image("data/dog.jpg");
    rgb_to_hsv(im);
    image hsv = load_image("figs/dog.hsv.png");
    TEST(same_image(im, hsv));
    free_image(im);
    free_image(hsv);
}

void test_hsv_to_rgb()
{
    image im = load_image("data/dog.jpg");
    image c = copy_image(im);
    rgb_to_hsv(im);
    hsv_to_rgb(im);
    TEST(same_image(im, c));
    free_image(im);
    free_image(c);
}

void test_nn_interpolate()
{
    image im = load_image("data/dogsmall.jpg");
    TEST(within_eps(nn_interpolate(im, -.5, -.5, 0)  , 0.231373));
    TEST(within_eps(nn_interpolate(im, -.5, .5, 1)   , 0.239216));
    TEST(within_eps(nn_interpolate(im, .499, .5, 2)  , 0.207843));
    TEST(within_eps(nn_interpolate(im, 14.2, 15.9, 1), 0.690196));
    free_image(im);
}

void test_bl_interpolate()
{
    image im = load_image("data/dogsmall.jpg");
    TEST(within_eps(bilinear_interpolate(im, -.5, -.5, 0)  , 0.231373));
    TEST(within_eps(bilinear_interpolate(im, -.5, .5, 1)   , 0.237255));
    TEST(within_eps(bilinear_interpolate(im, .499, .5, 2)  , 0.206861));
    TEST(within_eps(bilinear_interpolate(im, 14.2, 15.9, 1), 0.678588));
}



void test_nn_resize()
{
    image im = load_image("data/dogsmall.jpg");
    image resized = nn_resize(im, im.w*4, im.h*4);
    image gt = load_image("figs/dog4x-nn-for-test.png");
    TEST(same_image(resized, gt));
    free_image(im);
    free_image(resized);
    free_image(gt);

    image im2 = load_image("data/dog.jpg");
    image resized2 = nn_resize(im2, 713, 467);
    image gt2 = load_image("figs/dog-resize-nn.png");
    TEST(same_image(resized2, gt2));
    free_image(im2);
    free_image(resized2);
    free_image(gt2);
}

void test_bl_resize()
{
    image im = load_image("data/dogsmall.jpg");
    image resized = bilinear_resize(im, im.w*4, im.h*4);
    image gt = load_image("figs/dog4x-bl.png");
    TEST(same_image(resized, gt));
    free_image(im);
    free_image(resized);
    free_image(gt);

    image im2 = load_image("data/dog.jpg");
    image resized2 = bilinear_resize(im2, 713, 467);
    image gt2 = load_image("figs/dog-resize-bil.png");
    TEST(same_image(resized2, gt2));
    free_image(im2);
    free_image(resized2);
    free_image(gt2);
}

void test_multiple_resize()
{
    image im = load_image("data/dog.jpg");
    int i;
    for (i = 0; i < 10; i++){
        image im1 = bilinear_resize(im, im.w*4, im.h*4);
        image im2 = bilinear_resize(im1, im1.w/4, im1.h/4);
        free_image(im);
        free_image(im1);
        im = im2;
    }
    image gt = load_image("figs/dog-multipleresize.png");
    TEST(same_image(im, gt));
    free_image(im);
    free_image(gt);
}


void test_highpass_filter(){
    image im = load_image("data/dog.jpg");
    image f = make_highpass_filter();
    image blur = convolve_image(im, f, 0);
    clamp_image(blur);

    
    image gt = load_image("figs/dog-highpass.png");
    TEST(same_image(blur, gt));
    free_image(im);
    free_image(f);
    free_image(blur);
    free_image(gt);
}

void test_emboss_filter(){
    image im = load_image("data/dog.jpg");
    image f = make_emboss_filter();
    image blur = convolve_image(im, f, 1);
    clamp_image(blur);

    
    image gt = load_image("figs/dog-emboss.png");
    TEST(same_image(blur, gt));
    free_image(im);
    free_image(f);
    free_image(blur);
    free_image(gt);
}

void test_sharpen_filter(){
    image im = load_image("data/dog.jpg");
    image f = make_sharpen_filter();
    image blur = convolve_image(im, f, 1);
    clamp_image(blur);


    image gt = load_image("figs/dog-sharpen.png");
    TEST(same_image(blur, gt));
    free_image(im);
    free_image(f);
    free_image(blur);
    free_image(gt);
}

void test_convolution(){
    image im = load_image("data/dog.jpg");
    image f = make_box_filter(7);
    image blur = convolve_image(im, f, 1);
    clamp_image(blur);

    image gt = load_image("figs/dog-box7.png");
    TEST(same_image(blur, gt));
    free_image(im);
    free_image(f);
    free_image(blur);
    free_image(gt);
}

void test_gaussian_filter(){
    image f = make_gaussian_filter(7);
    int i;

    for(i = 0; i < f.w * f.h * f.c; i++){
        f.data[i] *= 100;
    }

    image gt = load_image("figs/gaussian_filter_7.png");
    TEST(same_image(f, gt));    
    free_image(f);
    free_image(gt);
}

void test_gaussian_blur(){
    image im = load_image("data/dog.jpg");
    image f = make_gaussian_filter(2);
    image blur = convolve_image(im, f, 1);
    clamp_image(blur);

    image gt = load_image("figs/dog-gauss2.png");
    TEST(same_image(blur, gt));    
    free_image(im);
    free_image(f);
    free_image(blur);
    free_image(gt);
}

void test_hybrid_image(){
    image man = load_image("data/melisa.png");
    image woman = load_image("data/aria.png");
    image f = make_gaussian_filter(2);
    image lfreq_man = convolve_image(man, f, 1);
    image lfreq_w = convolve_image(woman, f, 1);
    image hfreq_w = sub_image(woman , lfreq_w);
    image reconstruct = add_image(lfreq_man , hfreq_w);
    image gt = load_image("figs/hybrid.png");
    clamp_image(reconstruct);
    TEST(same_image(reconstruct, gt));
    free_image(man);
    free_image(woman);
    free_image(f);
    free_image(lfreq_man);
    free_image(lfreq_w);
    free_image(hfreq_w);
    free_image(reconstruct);
    free_image(gt);
}

void test_frequency_image(){
    image im = load_image("data/dog.jpg");
    image f = make_gaussian_filter(2);
    image lfreq = convolve_image(im, f, 1);
    image hfreq = sub_image(im, lfreq);
    image reconstruct = add_image(lfreq , hfreq);

    image low_freq = load_image("figs/low-frequency.png");
    image high_freq = load_image("figs/high-frequency-clamp.png");

    clamp_image(lfreq);
    clamp_image(hfreq);
    TEST(same_image(lfreq, low_freq));
    TEST(same_image(hfreq, high_freq));
    TEST(same_image(reconstruct, im));
    free_image(im);
    free_image(f);
    free_image(lfreq);
    free_image(hfreq);
    free_image(reconstruct);
    free_image(low_freq);
    free_image(high_freq);
}

void test_sobel(){
    image im = load_image("data/dog.jpg");
    image *res = sobel_image(im);
    image mag = res[0];
    image theta = res[1];
    feature_normalize2(mag);
    feature_normalize2(theta);

    image gt_mag = load_image("figs/magnitude.png");
    image gt_theta = load_image("figs/theta.png");
    TEST(gt_mag.w == mag.w && gt_theta.w == theta.w);
    TEST(gt_mag.h == mag.h && gt_theta.h == theta.h);
    TEST(gt_mag.c == mag.c && gt_theta.c == theta.c);
    if( gt_mag.w != mag.w || gt_theta.w != theta.w || 
        gt_mag.h != mag.h || gt_theta.h != theta.h || 
        gt_mag.c != mag.c || gt_theta.c != theta.c ) return;
    int i;
    for(i = 0; i < gt_mag.w*gt_mag.h; ++i){
        if(within_eps(gt_mag.data[i], 0)){
            gt_theta.data[i] = 0;
            theta.data[i] = 0;
        }
        if(within_eps(gt_theta.data[i], 0) || within_eps(gt_theta.data[i], 1)){
            gt_theta.data[i] = 0;
            theta.data[i] = 0;
        }
    }

    TEST(same_image(mag, gt_mag));
    TEST(same_image(theta, gt_theta));
    free_image(im);
    free_image(mag);
    free_image(theta);
    free_image(gt_mag);
    free_image(gt_theta);
    free(res);
}

void test_structure()
{
    image im = load_image("data/dogbw.png");
    image s = structure_matrix(im, 2);
    feature_normalize2(s);
    image gt = load_image("figs/structure.png");
    TEST(same_image(s, gt));
    free_image(im);
    free_image(s);
    free_image(gt);
}

void test_cornerness()
{
    image im = load_image("data/dogbw.png");
    image s = structure_matrix(im, 2);
    image c = cornerness_response(s);
    feature_normalize2(c);
    image gt = load_image("figs/response.png");
    TEST(same_image(c, gt));
    free_image(im);
    free_image(s);
    free_image(c);
    free_image(gt);
}



void test_projection()
{
    matrix H = make_translation_homography(12.4, -3.2);
    TEST(same_point(project_point(H, make_point(0,0)), make_point(12.4, -3.2)));
    free_matrix(H);

    H = make_identity_homography();
    H.data[0][0] = 1.32;
    H.data[0][1] = -1.12;
    H.data[0][2] = 2.52;
    H.data[1][0] = -.32;
    H.data[1][1] = -1.2;
    H.data[1][2] = .52;
    H.data[2][0] = -3.32;
    H.data[2][1] = 1.87;
    H.data[2][2] = .112;
    point p = project_point(H, make_point(3.14, 1.59));
    TEST(same_point(p, make_point(-0.66544, 0.326017)));
    free_matrix(H);
}

void test_compute_homography()
{
    match *m = calloc(4, sizeof(match));
    m[0].p = make_point(0,0);
    m[0].q = make_point(10,10);
    m[1].p = make_point(3,3);
    m[1].q = make_point(13,13);
    m[2].p = make_point(-1.2,-3.4);
    m[2].q = make_point(8.8,6.6);
    m[3].p = make_point(9,10);
    m[3].q = make_point(19,20);
    matrix H = compute_homography(m, 4);
    matrix d10 = make_translation_homography(10, 10);
    TEST(same_matrix(H, d10));
    free_matrix(H);
    free_matrix(d10);

    m[0].p = make_point(7.2,1.3);
    m[0].q = make_point(10,10.9);
    m[1].p = make_point(3,3);
    m[1].q = make_point(1.3,7.3);
    m[2].p = make_point(-.2,-3.4);
    m[2].q = make_point(.8,2.6);
    m[3].p = make_point(-3.2,2.4);
    m[3].q = make_point(1.5,-4.2);
    H = compute_homography(m, 4);
    matrix Hp = make_identity_homography();
    Hp.data[0][0] = -0.1328042; Hp.data[0][1] = -0.2910411; Hp.data[0][2] = 0.8103200;
    Hp.data[1][0] = -0.0487439; Hp.data[1][1] = -1.3077799; Hp.data[1][2] = 1.4796660;
    Hp.data[2][0] = -0.0788730; Hp.data[2][1] = -0.3727209; Hp.data[2][2] = 1.0000000;
    TEST(same_matrix(H, Hp));
    free_matrix(H);
    free_matrix(Hp);
}

void test_activate_matrix()
{
    matrix a = load_matrix("data/test/a.matrix");
    matrix truth_alog = load_matrix("data/test/alog.matrix");
    matrix truth_arelu = load_matrix("data/test/arelu.matrix");
    matrix truth_alrelu = load_matrix("data/test/alrelu.matrix");
    matrix truth_asoft = load_matrix("data/test/asoft.matrix");
    matrix alog = copy_matrix(a);
    activate_matrix(alog, LOGISTIC);
    matrix arelu = copy_matrix(a);
    activate_matrix(arelu, RELU);
    matrix alrelu = copy_matrix(a);
    activate_matrix(alrelu, LRELU);
    matrix asoft = copy_matrix(a);
    activate_matrix(asoft, SOFTMAX);
    TEST(same_matrix(truth_alog, alog));
    TEST(same_matrix(truth_arelu, arelu));
    TEST(same_matrix(truth_alrelu, alrelu));
    TEST(same_matrix(truth_asoft, asoft));
    free_matrix(a);
    free_matrix(alog);
    free_matrix(arelu);
    free_matrix(alrelu);
    free_matrix(asoft);
    free_matrix(truth_alog);
    free_matrix(truth_arelu);
    free_matrix(truth_alrelu);
    free_matrix(truth_asoft);
}

void test_gradient_matrix()
{
    matrix a = load_matrix("data/test/a.matrix");
    matrix y = load_matrix("data/test/y.matrix");
    matrix truth_glog = load_matrix("data/test/glog.matrix");
    matrix truth_grelu = load_matrix("data/test/grelu.matrix");
    matrix truth_glrelu = load_matrix("data/test/glrelu.matrix");
    matrix truth_gsoft = load_matrix("data/test/gsoft.matrix");
    matrix glog = copy_matrix(a);
    matrix grelu = copy_matrix(a);
    matrix glrelu = copy_matrix(a);
    matrix gsoft = copy_matrix(a);
    gradient_matrix(y, LOGISTIC, glog);
    gradient_matrix(y, RELU, grelu);
    gradient_matrix(y, LRELU, glrelu);
    gradient_matrix(y, SOFTMAX, gsoft);
    TEST(same_matrix(truth_glog, glog));
    TEST(same_matrix(truth_grelu, grelu));
    TEST(same_matrix(truth_glrelu, glrelu));
    TEST(same_matrix(truth_gsoft, gsoft));
    free_matrix(a);
    free_matrix(glog);
    free_matrix(grelu);
    free_matrix(glrelu);
    free_matrix(gsoft);
    free_matrix(truth_glog);
    free_matrix(truth_grelu);
    free_matrix(truth_glrelu);
    free_matrix(truth_gsoft);
}

void test_layer()
{
    matrix a = load_matrix("data/test/a.matrix");
    matrix w = load_matrix("data/test/w.matrix");
    matrix dw = load_matrix("data/test/dw.matrix");
    matrix v = load_matrix("data/test/v.matrix");
    matrix delta = load_matrix("data/test/delta.matrix");

    matrix truth_dx = load_matrix("data/test/truth_dx.matrix");
    matrix truth_v = load_matrix("data/test/truth_v.matrix");
    matrix truth_dw = load_matrix("data/test/truth_dw.matrix");

    matrix updated_dw = load_matrix("data/test/updated_dw.matrix");
    matrix updated_w = load_matrix("data/test/updated_w.matrix");
    matrix updated_v = load_matrix("data/test/updated_v.matrix");

    matrix truth_out = load_matrix("data/test/out.matrix");
    layer l = make_layer(64, 16, LRELU);
    l.w = w;
    l.dw = dw;
    l.v = v;
    matrix out = forward_layer(&l, a);
    TEST(same_matrix(truth_out, out));

    matrix dx = backward_layer(&l, delta);
    TEST(same_matrix(truth_v, v));
    TEST(same_matrix(truth_dw, l.dw));
    TEST(same_matrix(truth_dx, dx));

    update_layer(&l, .01, .9, .01);
    TEST(same_matrix(updated_dw, l.dw));
    TEST(same_matrix(updated_w, l.w));
    TEST(same_matrix(updated_v, l.v));
}

void make_matrix_test()
{
    srand(1);
    matrix a = random_matrix(32, 64, 10);
    matrix w = random_matrix(64, 16, 10);
    matrix y = random_matrix(32, 64, 10);
    matrix dw = random_matrix(64, 16, 10);
    matrix v = random_matrix(64, 16, 10);
    matrix delta = random_matrix(32, 16, 10);

    save_matrix(a, "data/test/a.matrix");
    save_matrix(w, "data/test/w.matrix");
    save_matrix(dw, "data/test/dw.matrix");
    save_matrix(v, "data/test/v.matrix");
    save_matrix(delta, "data/test/delta.matrix");
    save_matrix(y, "data/test/y.matrix");

    matrix alog = copy_matrix(a);
    activate_matrix(alog, LOGISTIC);
    save_matrix(alog, "data/test/alog.matrix");

    matrix arelu = copy_matrix(a);
    activate_matrix(arelu, RELU);
    save_matrix(arelu, "data/test/arelu.matrix");

    matrix alrelu = copy_matrix(a);
    activate_matrix(alrelu, LRELU);
    save_matrix(alrelu, "data/test/alrelu.matrix");

    matrix asoft = copy_matrix(a);
    activate_matrix(asoft, SOFTMAX);
    save_matrix(asoft, "data/test/asoft.matrix");


    matrix glog = copy_matrix(a);
    gradient_matrix(y, LOGISTIC, glog);
    save_matrix(glog, "data/test/glog.matrix");

    matrix grelu = copy_matrix(a);
    gradient_matrix(y, RELU, grelu);
    save_matrix(grelu, "data/test/grelu.matrix");

    matrix glrelu = copy_matrix(a);
    gradient_matrix(y, LRELU, glrelu);
    save_matrix(glrelu, "data/test/glrelu.matrix");

    matrix gsoft = copy_matrix(a);
    gradient_matrix(y, SOFTMAX, gsoft);
    save_matrix(gsoft, "data/test/gsoft.matrix");


    layer l = make_layer(64, 16, LRELU);
    l.w = w;
    l.dw = dw;
    l.v = v;

    matrix out = forward_layer(&l, a);
    save_matrix(out, "data/test/out.matrix");

    matrix dx = backward_layer(&l, delta);
    save_matrix(l.dw, "data/test/truth_dw.matrix");
    save_matrix(l.v, "data/test/truth_v.matrix");
    save_matrix(dx, "data/test/truth_dx.matrix");

    update_layer(&l, .01, .9, .01);
    save_matrix(l.dw, "data/test/updated_dw.matrix");
    save_matrix(l.w, "data/test/updated_w.matrix");
    save_matrix(l.v, "data/test/updated_v.matrix");
}

void test_hw0()
{
    test_get_pixel();
    test_set_pixel();
    test_copy();
    test_shift();
    test_clamp();
    test_grayscale();
    test_rgb_to_hsv();
    test_hsv_to_rgb();
    printf("%d tests, %d passed, %d failed\n", tests_total, tests_total-tests_fail, tests_fail);
}
void test_hw1()
{
    test_nn_interpolate();
    test_nn_resize();
    test_bl_interpolate();
    test_bl_resize();
    test_multiple_resize();
    printf("%d tests, %d passed, %d failed\n", tests_total, tests_total-tests_fail, tests_fail);
}
void test_hw2()
{
    test_gaussian_filter();
    test_sharpen_filter();
    test_emboss_filter();
    test_highpass_filter();
    test_convolution();
    test_gaussian_blur();
    test_hybrid_image();
    test_frequency_image();
    test_sobel();
    printf("%d tests, %d passed, %d failed\n", tests_total, tests_total-tests_fail, tests_fail);
}
void test_hw3()
{
    test_structure();
    test_cornerness();
    test_projection();
    test_compute_homography();
    printf("%d tests, %d passed, %d failed\n", tests_total, tests_total-tests_fail, tests_fail);
}

void test_hw4()
{
    printf("%d tests, %d passed, %d failed\n", tests_total, tests_total-tests_fail, tests_fail);
    #if 0
    data train = load_classification_data("mnist.train", "mnist.labels", 1);
    data test = load_classification_data("mnist.test", "mnist.labels", 1);
    model m;
    layer l[2];
    l[0] = make_layer(train.X.cols, 32, LOGISTIC);
    l[1] = make_layer(32, train.y.cols, SOFTMAX);
    m.n=2;
    m.layers = l;
    train_model(m,train,128,10,0.01,0.9,0);
    printf("training accuracy: %f\n", accuracy_model(m, train));
    printf("test accuracy:     %f\n", accuracy_model(m, test));
    #endif
    //test_matrix();
    //data train = load_installHeigh_data(Train_height, 1);
    data train = load_installHeigh_data(Train_height,1,sizeof(Train_height)/(sizeof(double)*3));
    //data test = load_installHeigh_data(Train_height,1);
#if CLASSIFICATION
    model m;
    /*
    layer l[4];
    l[0] = make_layer(train.X.cols, 32, RELU);
    l[1] = make_layer(32, 32, RELU);
    l[2] = make_layer(32, 32, RELU);
    l[3] = make_layer(32, train.y.cols, SOFTMAX);
    m.n=4;
    */
    layer l[3];
    l[0] = make_layer(train.X.cols, 32, RELU);
    l[1] = make_layer(32, 32, RELU);
    l[2] = make_layer(32, train.y.cols, SOFTMAX);
    m.n=3;
    m.layers = l;

    train_model(m,train,32,300,0.001,0.0,0);
#else
    model m;
    layer l[3];
    /*
    l[0] = make_layer(train.X.cols, 8, RELU);
    l[1] = make_layer(8, 8, RELU);
    l[2] = make_layer(8, train.y.cols, LINEAR);
    */
    l[0] = make_layer(train.X.cols, 4, RELU);
    l[1] = make_layer(4, 4, RELU);
    l[2] = make_layer(4, train.y.cols, LINEAR);
    m.n=3;
    m.layers = l;
    train_model(m,train,16,100,0.05,0.0,0);
#endif
    //~train_model(m,train,128,100,0.01,0.9,0);
    printf("training accuracy: %f\n", accuracy_model(m, train));
    data test = load_installHeigh_data(Test_height,1,sizeof(Test_height)/(sizeof(double)*3));
    printf("test accuracy:     %f\n", accuracy_model(m, test));

    //printf("training accuracy: %f\n", accuracy_model(m, train));

}
void test_hw5()
{
    test_activate_matrix();
    test_gradient_matrix();
    test_layer();
    printf("%d tests, %d passed, %d failed\n", tests_total, tests_total-tests_fail, tests_fail);

}
void run_tests()
{
    test_structure();
    test_cornerness();
    printf("%d tests, %d passed, %d failed\n", tests_total, tests_total-tests_fail, tests_fail);
}
