/**
  \file        watermark_remover.cpp
  \author      Arnaud Ramey <arnaud.a.ramey@gmail.com>
                -- Robotics Lab, University Carlos III of Madrid
  \date        2013/4/9
  
________________________________________________________________________________

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
________________________________________________________________________________

A watermark remover.
It needs a clean thumbnail of the image.
It will replace the watermarked zones of the image
with the ones of the thumbnail.

 */
#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

cv::Mat remove_watermark(const cv::Mat & watermarked,
                         const cv::Mat & clean_thumbnail,
                         const cv::Mat1b & mark_mask,
                         const uchar & mark_color) {
  // resize clean_thumbnail
  cv::Mat clean_good_size;
  if (clean_thumbnail.size() == watermarked.size())
    clean_thumbnail.copyTo(clean_good_size);
  else
    cv::resize(clean_thumbnail, clean_good_size, watermarked.size(), 0, 0, cv::INTER_LANCZOS4);

  // resize mark_mask
  cv::Mat mark_mask_good_size;
  if (mark_mask.size() == watermarked.size())
    mark_mask.copyTo(mark_mask_good_size);
  else
    cv::resize(mark_mask, mark_mask_good_size, watermarked.size(), 0, 0, cv::INTER_NEAREST);

  // now replace
  cv::Mat out;
  watermarked.copyTo(out);
  clean_good_size.copyTo(out, mark_mask_good_size == mark_color);
  return out;
}

////////////////////////////////////////////////////////////////////////////////

void remove_watermark(const std::string & watermarked_filename,
                      const std::string & clean_thumbnail_filename,
                      const std::string & mark_mask_filename,
                      const uchar & mark_color,
                      const std::string filename_out) {
  cv::Mat watermarked = cv::imread(watermarked_filename);
  if (watermarked.empty()) {
    printf("Cannot read file '%s', aborting.\n", watermarked_filename.c_str());
    return;
  }
  cv::Mat clean_thumbnail = cv::imread(clean_thumbnail_filename);
  if (clean_thumbnail.empty()) {
    printf("Cannot read file '%s', aborting.\n", clean_thumbnail_filename.c_str());
    return;
  }
  cv::Mat1b mark_mask = cv::imread(mark_mask_filename, CV_LOAD_IMAGE_GRAYSCALE);
  if (mark_mask.empty()) {
    printf("Cannot read file '%s', aborting.\n", mark_mask_filename.c_str());
    return;
  }
  cv::Mat out = remove_watermark(watermarked, clean_thumbnail, mark_mask, mark_color);
  cv::imwrite(filename_out, out);
  printf("Succesfully witten '%s'.\n", filename_out.c_str());
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
  if (argc != 4 && argc != 5) {
    printf("A watermark remover.\n");
    printf("It needs a clean thumbnail of the image.\n");
    printf("It will replace the watermarked zones of the image\n");
    printf("with the ones of the thumbnail.\n");
    printf("Syntax: %s <watermarked_filename> <clean_thumbnail_filename> <mark_mask_filename> <filename_out>\n",
           argv[0]);
    printf("   <watermarked_filename>           a (high resoltion) image including the watermark\n");
    printf("   <clean_thumbnail_filename> a low resolution thumbnail of watermarked_filename with no watermark\n");
    printf("   <mark_mask_filename>       an image were the watermark is painted in black\n");
    printf("   <filename_out>             the output file - if not specified, an automatic name is generated\n");
    return -1;
  }
  std::string watermarked_filename(argv[1]);
  std::string filename_out = "";
  if (argc == 5)
    filename_out = std::string(argv[4]);
  else {
    std::string::size_type dot_pos = watermarked_filename.find_last_of(".");
    if (dot_pos == std::string::npos || dot_pos < watermarked_filename.size() - 5)
      filename_out = watermarked_filename + "_no_watermark.png";
    else
      filename_out = watermarked_filename.substr(0, dot_pos)
          + "_no_watermark.png";
  }
  printf("filename_out:'%s'\n", filename_out.c_str());
  remove_watermark(watermarked_filename, std::string(argv[2]),
      std::string(argv[3]), 0, filename_out);
}
