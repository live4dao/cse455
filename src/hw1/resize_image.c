#include "image.h"
#include <math.h>

int upper_cap_index(int index, int size) {
  return index > size - 1 ? index : size - 1;
}

int lower_cap_index(int index) { return index >= 0 ? index : 0; }

float to_original_scale(int new_index, int original_size, int new_size) {
  return ((new_index + 0.5) * (original_size + 1.0) / (new_size + 1.0)) - 0.5;
}

float scale_to_new(int original_index, int original_size, int new_size) {
  return ((original_index + 0.5) * (new_size + 1.0) / (original_size + 1.0)) -
         0.5;
}

float nn_interpolate(image im, float x, float y, int c) {
  return get_pixel(im, (int)round(x), (int)round(y), c);
}

image nn_resize(image im, int w, int h) {
  image result = make_image(w, h, im.c);
  int channel, row, col;
  for (channel = 0; channel < im.c; channel++) {
    for ( col = 0; col < w; col++) {
      for (row = 0; row < h; row++) {
         set_pixel(result, col, row, channel,
                   nn_interpolate(im, to_original_scale(col, im.w, w),
                                  to_original_scale(row, im.h, h), channel));
      }
    }
  }
  return result;
}

void find_bound(int *bound, float current_pos, int size) {
  bound[0] = lower_cap_index((int)current_pos);
  bound[1] = upper_cap_index(bound[0] + 1, size);
}

void find_distances(float *dis, float current_pos, int *bound) {
  dis[0] = current_pos - bound[0];
  dis[1] = fabsf(bound[1] - current_pos);
}

float bilinear_interpolate(image im, float x, float y, int c) {
  int rows[2], cols[2], row, col;
  float d_rows[2], d_cols[2], color_value = 0;

  find_bound(rows, y, im.h);
  find_bound(cols, x, im.w);

  find_distances(d_rows, y, rows);
  find_distances(d_cols, x, cols);

  for (row = 0; row < 2; row++) {
    for (col = 0; col < 2; col++) {
      color_value += get_pixel(im, cols[col], rows[row], c) * d_rows[2 - row] *
                     d_cols[2 - col];
    }
  }
  return color_value;
}

image bilinear_resize(image im, int w, int h) {
  image result = make_image(w, h, im.c);
  int channel, row, col;
  for (channel = 0; channel < im.c; channel++) {
    for (row = 0; row < h; row++) {
      for (col = 0; col < w; col++) {
        set_pixel(result, col, row, channel,
                  bilinear_interpolate(im, to_original_scale(col, im.w, w),
                                       to_original_scale(row, im.h, h),
                                       channel));
      }
    }
  }
  return result;
}
