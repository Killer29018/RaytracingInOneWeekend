#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include "Hittable.hpp"

#include <memory>
#include <vector>

class hittableList : public hittable
{
public:
    std::vector<std::shared_ptr<hittable>> objects;
public:
    hittableList() {}
    hittableList(std::shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

    virtual bool hit(const Ray& r, double tMin, double tMax, hitRecord& rec) const override;
};

bool hittableList::hit(const Ray& r, double tMin, double tMax, hitRecord& rec) const 
{
    hitRecord tempRec;
    bool hitAnything = false;
    double closestSoFar = tMax;

    for (const auto& object: objects)
    {
        if (object->hit(r, tMin, closestSoFar, tempRec))
        {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }

    return hitAnything;
}

#endif