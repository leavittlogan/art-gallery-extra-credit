# Art Gallery Problem solution using Ear Clipping

This solution for the art gallery problem uses the ear clipping method for 
polygon triangulation, and adapts it to 3-color the resulting graph. Below is
the algorithm in detail:

Given a polygon P, represented as a cyclic list of points [*p1*, *p2*, ... ,*pn] in counter clockwise order:
- Iterate through P and mark each vertex as concave or non-concave
- Iterate through P and find a vertex *pk* which qualifies as an ear:
    - An ear must be concave
    - Check to see if any other points lie inside the triangle (*pk-1*, *pk*, *pk+1*), if any do, *pk* is not an ear
        - noncave points are the only points that would be able to lie inside the triangle, so it is safe to just check those
- "Cut" off ear *pk* by removing it from the list, and add the triangle (*pk-1*, *pk*, *pk+1*) to a stack
- If *pk-1* or *pk+1* were not convave, check if they are now concave
- Repeat ear removal process until Polygon P' is a triangle
- 3-color P' so that no adjacent vertices have the same color (trivial since P' is a triangle)
- Pop triangles from stack to add ears one at a time and color them,
  there will only be one way to color them, as their two connections will already be colored
- Populate guards at the least popular color
