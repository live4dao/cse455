#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "image.h"
#include "matrix.h"

#define DO_1D_SMOOTHING 0

// Frees an array of descriptors.
// descriptor *d: the array.
// int n: number of elements in array.
void free_descriptors(descriptor *d, int n) {
  int i;
  for (i = 0; i < n; ++i) {
    free(d[i].data);
  }
  free(d);
}

// Create a feature descriptor for an index in an image.
// image im: source image.
// int i: index in image for the pixel we want to describe.
// returns: descriptor for that index.
descriptor describe_index(image im, int i) {
  int w = 5;
  descriptor d;
  d.p.x = i % im.w;
  d.p.y = i / im.w;
  d.data = calloc(w * w * im.c, sizeof(float));
  d.n = w * w * im.c;
  int c, dx, dy;
  int count = 0;
  // If you want you can experiment with other descriptors
  // This subtracts the central value from neighbors
  // to compensate some for exposure/lighting changes.
  for (c = 0; c < im.c; ++c) {
    float cval = im.data[c * im.w * im.h + i];
    for (dx = -w / 2; dx < (w + 1) / 2; ++dx) {
      for (dy = -w / 2; dy < (w + 1) / 2; ++dy) {
        float val = get_pixel(im, i % im.w + dx, i / im.w + dy, c);
        d.data[count++] = cval - val;
      }
    }
  }
  return d;
}

// Marks the spot of a point in an image.
// image im: image to mark.
// ponit p: spot to mark in the image.
void mark_spot(image im, point p) {
  int x = p.x;
  int y = p.y;
  int i;
  for (i = -9; i < 10; ++i) {
    set_pixel(im, x + i, y, 0, 1);
    set_pixel(im, x, y + i, 0, 1);
    set_pixel(im, x + i, y, 1, 0);
    set_pixel(im, x, y + i, 1, 0);
    set_pixel(im, x + i, y, 2, 1);
    set_pixel(im, x, y + i, 2, 1);
  }
}

// Marks corners denoted by an array of descriptors.
// image im: image to mark.
// descriptor *d: corners in the image.
// int n: number of descriptors to mark.
void mark_corners(image im, descriptor *d, int n) {
  int i;
  for (i = 0; i < n; ++i) {
    mark_spot(im, d[i].p);
  }
}

// Creates a 1d Gaussian filter.
// float sigma: standard deviation of Gaussian.
// returns: single row image of the filter.
image make_1d_gaussian(float sigma) {
  int width = (int)ceilf(6 * sigma);
  width += 1 - (width % 2);

  int mid = (width - 1) / 2;
  image filter = make_image(width, 1, 1);
  for (int x = 0; x < width; x++) {
    float two_sigma2 = 2.0 * sigma * sigma;
    float x_ = x - mid;
    float value = exp(-x_ * x_ / two_sigma2) / (M_PI * two_sigma2);
    set_pixel(filter, x, 0, 0, value);
  }
  l1_normalize(filter);
  return filter;
}

// Smooths an image using separable Gaussian filter.
// image im: image to smooth.
// float sigma: std dev. for Gaussian.
// returns: smoothed image.
image smooth_image(image im, float sigma) {
  if (DO_1D_SMOOTHING) {
    image g = make_1d_gaussian(sigma);
    image s1 = convolve_image(im, g, 1);
    float gh = g.h;
    g.h = g.w;
    g.w = gh;
    image s2 = convolve_image(s1, g, 1);
    free_image(g);
    free_image(s1);
    return s2;
  } else {
    image g = make_gaussian_filter(sigma);
    image s = convolve_image(im, g, 1);
    free_image(g);
    return s;
  }
}

// Calculate the structure matrix of an image.
// image im: the input image.
// float sigma: std dev. to use for weighted sum.
// returns: structure matrix. 1st channel is Ix^2, 2nd channel is Iy^2,
//          third channel is IxIy.
image structure_matrix(image im, float sigma) {
  image Is = make_image(im.w, im.h, 3);
  image gx_filter = make_gx_filter();
  image gy_filter = make_gy_filter();
  image Ix = convolve_image(im, gx_filter, 0);
  image Iy = convolve_image(im, gy_filter, 0);
  free_image(gx_filter);
  free_image(gy_filter);

  int size = im.h * im.w;
  for (int i = 0; i < size; i++) {
    float ix = Ix.data[i];
    float iy = Iy.data[i];
    Is.data[i] = ix * ix;
    Is.data[i + size] = iy * iy;
    Is.data[i + 2 * size] = ix * iy;
  }
  free_image(Ix);
  free_image(Iy);

  image S = smooth_image(Is, sigma);
  free_image(Is);
  return S;
}

float get_cornerness_pixel(float ixx, float iyy, float ixy, float alpha) {
  float neg_b = ixx + iyy;
  return (ixx * iyy) - (ixy * ixy) - (alpha * neg_b * neg_b);
}

// Estimate the cornerness of each pixel given a structure matrix S.
// image S: structure matrix for an image.
// returns: a response map of cornerness calculations.
image cornerness_response(image S) {
  image R = make_image(S.w, S.h, 1);
  int size = R.h * R.w;
  for (int i = 0; i < size; i++) {
    float ixx = S.data[i];
    float iyy = S.data[i + size];
    float ixy = S.data[i + 2 * size];
    R.data[i] = get_cornerness_pixel(ixx, iyy, ixy, 0.06);
  }
  return R;
}

// Perform non-max supression on an image of feature responses.
// image im: 1-channel image of feature responses.
// int w: distance to look for larger responses.
// returns: image with only local-maxima responses within w pixels.
image nms_image(image im, int w) {
  image r = copy_image(im);
  for (int y = 0; y < im.h; y++) {
    int wy_start = y - w, wy_end = y + w;
    wy_start = wy_start > 0 ? wy_start : 0;
    wy_end = wy_end < im.h ? wy_end : im.h - 1;

    for (int x = 0; x < im.w; x++) {
      int wx_start = x - w, wx_end = x + w;
      wx_start = wx_start > 0 ? wx_start : 0;
      wx_end = wx_end < im.w ? wx_end : im.w - 1;

      for (int wy = wy_start; wy <= wy_end; wy++) {
        for (int wx = wx_start; wx <= wx_end; wx++) {
          if (wy == y && wx == x) continue;
          if (get_pixel(im, wx, wy, 0) > get_pixel(im, x, y, 0))
            set_pixel(r, x, y, 0, __FLT_MIN__);
        }
      }
    }
  }
  return r;
}

// Perform harris corner detection and extract features from the corners.
// image im: input image.
// float sigma: std. dev for harris.
// float thresh: threshold for cornerness.
// int nms: distance to look for local-maxes in response map.
// int *n: pointer to number of corners detected, should fill in.
// returns: array of descriptors of the corners in the image.
descriptor *harris_corner_detector(image im, float sigma, float thresh, int nms,
                                   int *n) {
  // Calculate structure matrix
  image S = structure_matrix(im, sigma);

  // Estimate cornerness
  image R = cornerness_response(S);

  // Run NMS on the responses
  image Rnms = nms_image(R, nms);
  int count = 0;  // change this
  int size = R.c * R.h * R.w;
  for (int i = 0; i < size; i++) {
    if (Rnms.data[i] > thresh) {
      count++;
    }
  }

  *n = count;  // <- set *n equal to number of corners in image.
  descriptor *d = calloc(count, sizeof(descriptor));
  count = 0;
  for (int i = 0; i < size; i++) {
    if (Rnms.data[i] > thresh) {
      d[count++] = describe_index(im, i);
    }
  }

  free_image(S);
  free_image(R);
  free_image(Rnms);
  return d;
}

// Find and draw corners on an image.
// image im: input image.
// float sigma: std. dev for harris.
// float thresh: threshold for cornerness.
// int nms: distance to look for local-maxes in response map.
void detect_and_draw_corners(image im, float sigma, float thresh, int nms) {
  int n = 0;
  descriptor *d = harris_corner_detector(im, sigma, thresh, nms, &n);
  mark_corners(im, d, n);
}
