#include <iostream>
#include <algorithm>
#include <vector>
#include "geometry/utils.h"

/**
 * INPUT: SET OF POINTS
 * OUTPUT: PARTITION = [CONVEX HULL ANTI-CLOCKWISE](OTHER POINTS]
**/ 


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


/**
 * @name convex hull: Jarvis March
 * @author Miguel Mini
 * @idea
 * 		- minimum point with usual 
 * 		comparator is extreme point.
 * 
 * 		- we can extender convex hull
 * 		with to_left test.
 * 
 * @complexity O(nh), where h = size(convex_hull)
**/ 
template<class Iterator>
Iterator jarvis_march(Iterator first, const Iterator last) {
	if (first == last) return first;
	swap(*first, *min_element(first, last));
	auto hull = first;
	while (next(hull) != last) {
		auto s = next(hull);
		for (auto it = first; it != last; ++it) {
			if (*it == *hull || *it == *s) continue;
			if (hull->cross(*s, *it) < 0 
				|| (hull->cross(*s, *it) == 0 && (*s - *hull).norm2() < (*it - *hull).norm2())) {
				s = it;
			}
		}
		if (s == first) break;
		hull = next(hull);
		swap(*s, *hull);
	}
	return next(hull);
}

/**
 * @name convex hull: Graham Scan
 * @author Miguel Mini
 * @idea
 * 		- minimum point with usual 
 * 		comparator is extreme point.
 * 
 * 		- we can sort by angle and 
 * 		build a partial convex hull 
 * 		in each step.
 * 
 * @complexity O(n \log n)
**/ 
template<class Iterator>
Iterator graham_scan(Iterator first, Iterator last) {
	if (first == last) return last;
	swap(*first, *min_element(first, last));
	sort(next(first), last, [first](auto p, auto q)->bool {
		auto ccw = first->cross(p, q);
		return ccw > 0 || (ccw == 0 && first->dot(p, p) < first->dot(q, q));
	});
	std::vector<Iterator> s, t;
	for (auto it = first; it != last; ++it) {
		while (s.size() >= 2 && s[s.size()-2]->cross(*(s.back()), *it) <= 0) {
			t.push_back(s.back()); 
			s.pop_back();
		}
		s.push_back(it);
	}
	for (auto it : s) *(first++) = *it;
	auto end_position = first;
	for (auto it : t) *(first++) = *it;
	return end_position;
}
