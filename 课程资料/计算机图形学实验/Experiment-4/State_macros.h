#pragma once

namespace State_macros
{
    // Line
    const int Line                    = 0;
    const int Mid_point_line          = 0;
    const int Bresenham_line          = Mid_point_line + 1;
    
    // Circle
    const int Circle                  = Bresenham_line + 1;
    const int Mid_point_circle        = Bresenham_line + 1;
    const int Bresenham_circle        = Mid_point_circle + 1;
    const int Rect                    = Bresenham_circle + 1;
    const int Curve                   = Rect + 1;
    const int Polyline                = Curve + 1;
    const int Polygon                 = Polyline + 1;
    const int B_spline_curve          = Polygon + 1;

    // Select
    const int Cross_point             = B_spline_curve + 1;
    const int Circle_center           = Cross_point + 1;

    const int Move                    = Circle_center + 1;
    const int Scale                   = Move + 1;
    const int Rotate                  = Scale + 1;
    const int Clip                    = Rotate + 1;
    const int Clip_line               = Rotate + 1;
    const int Clip_polygon            = Clip_line + 1;
    const int Sutherland_Hodgman      = Clip_line + 1;              // Sutherland-Hodgman 裁剪多边形
    const int Weiler_Atherton         = Sutherland_Hodgman + 1;     // Weiler-Atherton 裁剪多边形

    const int Scanline_fill           = Weiler_Atherton + 1;
    const int Flood_fill              = Scanline_fill + 1;     
    const int Thickline               = Flood_fill + 1;
}