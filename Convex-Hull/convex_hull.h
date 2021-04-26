#include <iostream>
#include <algorithm>
#include "geometry/utils.h"

/**
 * @name convex hull: extreme point criterion
 * @author Miguel Mini
 * @idea
 * 		- points in convex hull of a set of 
 * 		points are extreme points.
 * 
 * 		- extreme point p: there is no triangle 
 * 		formed by points in the set, other than p, 
 * 		that contains p.
 * @complexity O(n^4)
**/
template<class Iterator>
Iterator convex_hull_extreme_point(Iterator first, Iterator last) {
	auto extreme = [&first, &last](const auto& it)->bool {
		for (auto p=first; p!=last; p=next(p)) if (*p!=it) {
			for (auto q=p; q!=last; q=next(q)) if (*q!=it) {
				for (auto r=q; r!=last; r=next(r)) if (*r!=it) {
					if (in_triangle(*p, *q, *r, it)) return false;
				}
			}
		}
		return true;
	};
	return partition(first, last, extreme);
}

/**
 * @name convex hull: extreme edge criterion
 * @author Miguel Mini
 * @idea
 * 		- points in convex hull of a set of 
 * 		points are in extreme edge.
 * 
 * 		- extreme edge e: all points are to
 * 		left or to right from e.
 * @complexity O(n^3)
**/
template<class Iterator>
Iterator convex_hull_extreme_edge(Iterator first, Iterator last) {
	if (first == last) return first;
	auto same_side = [](Iterator first, Iterator last, const auto p, const auto q) {
		bool left = true, right = true;
		while (first != last) {
			auto expr = p.cross(q, *first);
			left = left && expr <= 0;
			right = right && expr >= 0;
			first = next(first);
		}
		return left || right;
	};
	swap(*min_element(first, last), *first);
	auto it = next(first);
	while (it != last) {
		auto other = it;
		while (other != last) {
			if (same_side(first, last, *prev(it), *other)) {
				swap(*it, *other);
				break;
			}
			other = next(other);
		}
		if (other == last) break;
		it = next(it);
	}
	if (distance(first, it) < 2) return it;
	auto jt = next(first);
	auto kt = next(jt);
	while (kt != it) {
		if (abs(prev(jt)->cross(*jt, *kt)) > eps) jt = next(jt);
		*jt = *kt;
		kt = next(kt);
	}
	if (distance(first, jt) >= 2 && abs(prev(jt)->cross(*jt, *first)) <= eps)
		return jt;
	return next(jt);
}
