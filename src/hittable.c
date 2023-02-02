#include "minirt.h"

bool	hit(const t_hittable *self, const t_ray *r, FLOAT t_min, FLOAT t_max, t_hit_record *rec)
{
	if (self->type == H_SPHERE)
		return (sphere_hit(self, r, t_min, t_max, rec));
	else if (self->type == H_LIST)
		return (hittable_list_hit(self, r, t_min, t_max, rec));
	else
		fatal_error("hit", "Unexpected hittable type");
}
