#include "HittableList.hpp"

HittableList::HittableList() {}
HittableList::HittableList(std::shared_ptr<Hittable> object)
{
    Add(object);
}

void HittableList::Clear()
{
    objects.clear();
}

void HittableList::Add(std::shared_ptr<Hittable> object)
{
    objects.push_back(object);
}

bool HittableList::Hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const
{
    HitRecord tempRec;
    bool hit = false;
    double closest = tMax;

    for (const auto& object : objects)
    {
        if (object->Hit(r, tMin, closest, tempRec))
        {
            hit = true;
            closest = tempRec.t;
            rec = tempRec;
        }
    }

    return hit;
}