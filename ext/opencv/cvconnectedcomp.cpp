/************************************************************

   cvconnectedcomp.cpp -

   $Author: lsxi $

   Copyright (C) 2005-2007 Masakazu Yonekura

************************************************************/
#include "cvconnectedcomp.h"
/*
 * Document-class: OpenCV::CvConnectedComp
 *
 * see CvMat#flood_fill
 *
 * C structure is here.
 *   typedef struct CvConnectedComp
 *   {
 *     double area;    
 *     CvScalar value; 
 *     CvRect rect;    
 *     CvSeq* contour;
 *   } CvConnectedComp;
 */
__NAMESPACE_BEGIN_OPENCV
__NAMESPACE_BEGIN_CVCONNECTEDCOMP

VALUE rb_klass;

VALUE
rb_class()
{
  return rb_klass;
}

void
define_ruby_class()
{
  if (rb_klass)
    return;
  /* 
   * opencv = rb_define_module("OpenCV");
   * 
   * note: this comment is used by rdoc.
   */
  VALUE opencv = rb_module_opencv();
  
  rb_klass = rb_define_class_under(opencv, "CvConnectedComp", rb_cObject);
  rb_define_alloc_func(rb_klass, rb_allocate);
  rb_define_private_method(rb_klass, "initialize", RUBY_METHOD_FUNC(rb_initialize), -1);
  rb_define_method(rb_klass, "area", RUBY_METHOD_FUNC(rb_area), 0);
  rb_define_method(rb_klass, "value", RUBY_METHOD_FUNC(rb_value), 0);
  rb_define_method(rb_klass, "rect", RUBY_METHOD_FUNC(rb_rect), 0);
  rb_define_method(rb_klass, "rect=", RUBY_METHOD_FUNC(rb_set_rect), 1);
  rb_define_method(rb_klass, "contour", RUBY_METHOD_FUNC(rb_contour), 0);
}

VALUE
rb_allocate(VALUE klass)
{
  CvConnectedComp *ptr;
  return Data_Make_Struct(klass, CvConnectedComp, 0, -1, ptr);
}

VALUE
rb_initialize(int argc, VALUE *argv, VALUE self)
{
  VALUE area, value, rect, contour;
  rb_scan_args(argc, argv, "04", &area, &value, &rect, &contour);

  if (!NIL_P(area))
    CVCONNECTEDCOMP(self)->area = NUM2DBL(area);
  if (!NIL_P(value))
    CVCONNECTEDCOMP(self)->value = *CVSCALAR(value);
  if (!NIL_P(rect))
    CVCONNECTEDCOMP(self)->rect = *CVRECT(rect);
  if (!NIL_P(contour))
    CVCONNECTEDCOMP(self)->contour = CVSEQ(contour);
  return self;
}

/*
 * Return area of connected component.
 */
VALUE
rb_area(VALUE self)
{
  return rb_float_new(CVCONNECTEDCOMP(self)->area);
}

/*
 * Return average color of the connected component.
 */
VALUE
rb_value(VALUE self)
{
  return REFER_OBJECT(cCvScalar::rb_class(), &CVCONNECTEDCOMP(self)->value, self);
}

/*
 * Return ROI of the component.
 */
VALUE
rb_rect(VALUE self)
{
  return REFER_OBJECT(cCvRect::rb_class(), &CVCONNECTEDCOMP(self)->rect, self);
}

/*
 * Set ROI of the component.
 */
VALUE
rb_set_rect(VALUE self, VALUE rect)
{
  CVCONNECTEDCOMP(self)->rect = VALUE_TO_CVRECT(rect);
  return self;
}

/*
 * Return optional component boundary
 */
VALUE
rb_contour(VALUE self)
{
  return REFER_OBJECT(cCvContour::rb_class(), &CVCONNECTEDCOMP(self)->contour, self);
}

VALUE
new_object()
{
  return rb_allocate(rb_klass);
}

VALUE
new_object(CvConnectedComp comp)
{
  VALUE object = rb_allocate(rb_klass);
  *CVCONNECTEDCOMP(object) = comp;
  return object;
}

__NAMESPACE_END_CVCONNECTEDCOMP
__NAMESPACE_END_OPENCV
