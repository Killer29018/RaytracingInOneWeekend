#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include "Hittable.hpp"

#include <memory>
#include <vector>

class HittableList : public Hittable
{
public:
    std::vector<std::shared_ptr<Hittable>> objects;
public:
    HittableList();
    HittableList(std::shared_ptr<Hittable> object);

    void Clear();
    void Add(std::shared_ptr<Hittable> object);

    virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;
};

#endif