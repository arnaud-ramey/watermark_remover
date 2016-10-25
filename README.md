#` watermark_remover`

[![Build Status](https://travis-ci.org/arnaud-ramey/watermark_remover.svg)](https://travis-ci.org/arnaud-ramey/watermark_remover)

A watermark remover.

* License :                  see the LICENSE file.
* Authors :                  see the AUTHORS file.
* How to build the program:  see the INSTALL file.

<p align="center">
<img src="https://6aaedb30-a-62cb3a1a-s-sites.googlegroups.com/site/rameyarnaud/research/c/watermark-remover-with-opencv/drawing.png"
   alt="example" style="width: 300px"/>
</p>


It needs a clean thumbnail of the image.
It will replace the watermarked zones of the image
with the ones of the thumbnail.


How to use the program
======================

To display the help, just launch the program in a terminal.
It will display the help of the program.

Synopsis
--------

```cpp
$ ./watermark_remover <dirty_filename> <clean_lowres_filename> <mark_mask_filename> <filename_out>
   <dirty_filename>        a (high resoltion) image including the watermark
   <clean_lowres_filename> a low resolution thumbnail of dirty_filename with no watermark
   <mark_mask_filename>    an image were the watermark is painted in black
   <filename_out>          the output file - if not specified, an automatic name is generated
```

Example
-------

```cpp
$ watermark_remover sample_watermarked.jpeg sample_thumbnail.jpeg sample_watermark_mask.png
```
