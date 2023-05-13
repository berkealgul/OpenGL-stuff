#pragma once
#ifndef AARECT_H
#define AARECT_H

#include "utils.h"
#include "hittable.h"


class XYRect : public Hittable 
{
public:
    XYRect() {}
    XYRect(double _x0, double _x1, double _y0, double _y1, double _k,
        shared_ptr<Material> mat)
        : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat) {};

    virtual bool hit(const Ray& r, double t_min, double t_max, HitResult& res) const override 
    {
        auto t = (k - r.origin().z()) / r.direction().z();
        if (t < t_min || t > t_max)
            return false;
        auto x = r.origin().x() + t * r.direction().x();
        auto y = r.origin().y() + t * r.direction().y();
        if (x < x0 || x > x1 || y < y0 || y > y1)
            return false;
        res.u = (x - x0) / (x1 - x0);
        res.v = (y - y0) / (y1 - y0);
        res.t = t;
        auto outward_normal = Vec3(0, 0, 1);
        res.set_face_normal(r, outward_normal);
        res.mat_ptr = mp;
        res.p = r.at(t);
        return true;
    }

    virtual bool bounding_box(double time0, double time1, AABB& output_box) const override 
    {
        output_box = AABB(Point3(x0, y0, k - 0.0001), Point3(x1, y1, k + 0.0001));
        return true;
    }

public:
    shared_ptr<Material> mp;
    double x0, x1, y0, y1, k;
};

#endif