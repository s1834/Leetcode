class Solution {
    public:
        bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
            // nearest point
            int xi, yi;
    
            if(x1 > xCenter) xi = x1;
            else if(x2 < xCenter) xi = x2;
            else xi = xCenter;
    
            if(y1 > yCenter) yi = y1;
            else if(y2 < yCenter) yi = y2;
            else yi = yCenter;
    
            // distance = sqrt((x2 ​− x1​) ^ 2 + (y2 ​− y1​) ^ 2)
            return sqrt((xi - xCenter) * (xi - xCenter) + (yi - yCenter) * (yi - yCenter)) <= radius;
        }
    };

 /*
    LeetCode 1401 - Circle and Rectangle Overlapping
    ------------------------------------------------------------

    Approach:
    ------------------------------------------------------------

    We need to determine whether a circle overlaps with a rectangle.

    The circle is given by:

        center = (xCenter, yCenter)
        radius = radius

    The rectangle is given by:

        (x1, y1) -> bottom-left corner
        (x2, y2) -> top-right corner

    The key idea is:

        Find the point inside the rectangle that is closest to the
        center of the circle.

    Then calculate the distance between this closest point and the
    circle center.

    If this distance is <= radius, the circle and rectangle overlap.


    ------------------------------------------------------------
    Key Observation:
    ------------------------------------------------------------

    For a circle and rectangle to overlap, there must be some point
    inside the rectangle whose distance from the circle center is
    at most the radius.

    Therefore, instead of checking every point of the rectangle, we
    only need to find the SINGLE point in the rectangle that is
    closest to the circle center.

    Let this closest point be:

        (xi, yi)

    Then:

        distance((xCenter, yCenter), (xi, yi)) <= radius

    means the circle reaches the rectangle.

    Otherwise, the circle is completely outside the rectangle.


    ------------------------------------------------------------
    Finding the Closest x Coordinate:
    ------------------------------------------------------------

    We need the x-coordinate inside the rectangle that is closest
    to xCenter.

    The rectangle occupies the x-range:

        [x1, x2]

    There are three cases.


    Case 1:
    ------------------------------------------------------------

    If:

        x1 > xCenter

    then the entire rectangle is to the RIGHT of the circle center.

    Therefore, the closest x-coordinate is the left boundary:

        xi = x1


    Example:

        xCenter = 2
        x1 = 5
        x2 = 8

            center
              |
              v
        -----●------|==========|
             2      5          8

        Closest x = 5


    Case 2:
    ------------------------------------------------------------

    If:

        x2 < xCenter

    then the entire rectangle is to the LEFT of the circle center.

    Therefore, the closest x-coordinate is the right boundary:

        xi = x2


    Example:

        xCenter = 10
        x1 = 2
        x2 = 6

        |==========|------●-----
        2          6      10

        Closest x = 6


    Case 3:
    ------------------------------------------------------------

    Otherwise:

        x1 <= xCenter <= x2

    This means the circle center's x-coordinate already lies inside
    the rectangle's horizontal range.

    Therefore, the closest x-coordinate is exactly xCenter:

        xi = xCenter


    ------------------------------------------------------------
    Therefore:
    ------------------------------------------------------------

        if(x1 > xCenter)
            xi = x1;

        else if(x2 < xCenter)
            xi = x2;

        else
            xi = xCenter;


    This is effectively CLAMPING xCenter to the interval [x1, x2].

    In mathematical form:

        xi = clamp(xCenter, x1, x2)


    ------------------------------------------------------------
    Finding the Closest y Coordinate:
    ------------------------------------------------------------

    We do exactly the same thing for the y-coordinate.

    The rectangle occupies:

        [y1, y2]

    If the center is below the rectangle:

        y1 > yCenter

    then:

        yi = y1


    If the center is above the rectangle:

        y2 < yCenter

    then:

        yi = y2


    Otherwise, the center's y-coordinate is already inside the
    rectangle's vertical range:

        yi = yCenter


    Therefore:

        if(y1 > yCenter)
            yi = y1;

        else if(y2 < yCenter)
            yi = y2;

        else
            yi = yCenter;


    ------------------------------------------------------------
    Closest Point:
    ------------------------------------------------------------

    After these two calculations, we have:

        (xi, yi)

    which is the point inside the rectangle closest to:

        (xCenter, yCenter)


    This is the most important observation of the entire solution.


    ------------------------------------------------------------
    Why Does This Work?
    ------------------------------------------------------------

    Consider the position of the circle center relative to the
    rectangle.

    ------------------------------------------------------------
    1. Circle center is inside the rectangle
    ------------------------------------------------------------

    If:

        x1 <= xCenter <= x2
        y1 <= yCenter <= y2

    then:

        xi = xCenter
        yi = yCenter

    Therefore:

        distance = 0

    Since:

        0 <= radius

    the circle definitely overlaps the rectangle.


    ------------------------------------------------------------
    2. Circle center is horizontally outside
    ------------------------------------------------------------

    Suppose the rectangle is to the right of the circle center.

    Then:

        xi = x1

    The closest point on the rectangle must lie on its left boundary.

    Similarly, if the rectangle is to the left:

        xi = x2


    ------------------------------------------------------------
    3. Circle center is vertically outside
    ------------------------------------------------------------

    If the rectangle is above the circle center:

        yi = y1

    If the rectangle is below the circle center:

        yi = y2


    ------------------------------------------------------------
    4. Circle is closest to a corner
    ------------------------------------------------------------

    If the circle is diagonally outside the rectangle, both coordinates
    are outside their respective ranges.

    For example:

        xCenter < x1
        yCenter < y1

    Then:

        xi = x1
        yi = y1

    So the closest point is the bottom-left corner:

        (x1, y1)


    The same logic automatically handles all four corners.


    ------------------------------------------------------------
    Distance Formula:
    ------------------------------------------------------------

    The Euclidean distance between:

        (xCenter, yCenter)

    and:

        (xi, yi)

    is:

        distance =
            sqrt(
                (xi - xCenter)^2 +
                (yi - yCenter)^2
            )


    The code calculates exactly this:

        sqrt(
            (xi - xCenter) * (xi - xCenter) +
            (yi - yCenter) * (yi - yCenter)
        )


    ------------------------------------------------------------
    Final Condition:
    ------------------------------------------------------------

    If:

        distance <= radius

    then the closest point of the rectangle lies inside or on the
    circle.

    Therefore, the circle and rectangle overlap.

    The code returns:

        distance <= radius;


    Notice the use of <= instead of <.

    This is important because if the circle just touches the rectangle,
    they are considered overlapping according to the problem.


    Example:

        distance = radius

        Circle
           ___
         /     \
        |       |------ Rectangle
         \_____/

        The circle touches the rectangle exactly.

        distance <= radius

        true


    ------------------------------------------------------------
    Example 1:
    ------------------------------------------------------------

    Circle:

        center = (0, 0)
        radius = 2

    Rectangle:

        [3, 1, 5, 4]

    Since:

        x1 = 3 > xCenter = 0

    we get:

        xi = 3

    And:

        y1 = 1 > yCenter = 0

    so:

        yi = 1

    Closest point:

        (3, 1)


    Distance:

        sqrt(
            (3 - 0)^2 +
            (1 - 0)^2
        )

        = sqrt(9 + 1)
        = sqrt(10)

        ≈ 3.16


    Since:

        3.16 > 2

    the circle does not overlap the rectangle.


    ------------------------------------------------------------
    Example 2:
    ------------------------------------------------------------

    Circle:

        center = (0, 0)
        radius = 5

    Rectangle:

        [3, 1, 5, 4]

    Closest point is still:

        (3, 1)

    Distance:

        sqrt(10) ≈ 3.16

    Now:

        3.16 <= 5

    Therefore, the circle overlaps the rectangle.


    ------------------------------------------------------------
    Example 3:
    ------------------------------------------------------------

    Circle:

        center = (3, 2)
        radius = 1

    Rectangle:

        [1, 1, 5, 4]

    The center lies inside the rectangle:

        1 <= 3 <= 5
        1 <= 2 <= 4

    Therefore:

        xi = 3
        yi = 2

    Distance:

        0

    Since:

        0 <= 1

    the answer is true.


    ------------------------------------------------------------
    Example 4 - Circle Touches Corner:
    ------------------------------------------------------------

    Circle:

        center = (0, 0)
        radius = 5

    Rectangle:

        [3, 4, 7, 8]

    Closest point:

        (3, 4)

    Distance:

        sqrt(3^2 + 4^2)
        = sqrt(9 + 16)
        = sqrt(25)
        = 5

    Since:

        5 <= 5

    the circle touches the rectangle exactly at the corner.

    Therefore:

        true


    ------------------------------------------------------------
    Geometric Interpretation:
    ------------------------------------------------------------

    Think of the rectangle as a closed region.

    We want:

        minimum distance from circle center
        to any point in the rectangle.

    The closest point is obtained independently for x and y:

        closest x = xCenter clamped to [x1, x2]
        closest y = yCenter clamped to [y1, y2]

    Therefore:

        closestPoint = (xi, yi)

    Then the entire problem reduces to:

        minimumDistance <= radius


    ------------------------------------------------------------
    Why We Do Not Need to Check All Four Corners:
    ------------------------------------------------------------

    A common approach might be to calculate the distance to all four
    corners.

    But that is not sufficient by itself.

    The closest point can also lie somewhere on an edge, especially
    when the circle center is horizontally or vertically aligned with
    the rectangle.

    For example:

        xCenter is inside [x1, x2]
        yCenter is above y2

    The closest point is:

        (xCenter, y2)

    which is on the TOP EDGE, not necessarily a corner.

    By independently clamping x and y, the solution automatically
    handles:

        - interior points
        - edge points
        - corner points


    ------------------------------------------------------------
    Why sqrt() Is Used:
    ------------------------------------------------------------

    The code computes:

        sqrt(dx^2 + dy^2) <= radius

    directly using the Euclidean distance formula.

    An equivalent optimization would be to compare squared distances:

        dx^2 + dy^2 <= radius^2

    which avoids sqrt().

    However, this implementation directly uses the distance formula,
    and the geometric logic remains the same.


    ------------------------------------------------------------
    Complexity:
    ------------------------------------------------------------

    Time Complexity:

        O(1)

    We only perform a constant number of comparisons and arithmetic
    operations.


    Space Complexity:

        O(1)

    Only a few integer variables are used.


    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------

    The entire solution can be reduced to three steps:

        1. Clamp the circle center's x-coordinate to the rectangle's
           x-range to get xi.

        2. Clamp the circle center's y-coordinate to the rectangle's
           y-range to get yi.

        3. Check whether the distance from (xCenter, yCenter) to
           (xi, yi) is at most radius.


    In short:

        Closest point on rectangle
                    ↓
        Distance from circle center
                    ↓
        distance <= radius ?
                    ↓
               overlap


    ------------------------------------------------------------
    Main Takeaway:
    ------------------------------------------------------------

    The key geometric trick is:

        The closest point in a rectangle to an arbitrary point can be
        found by independently clamping its x and y coordinates to the
        rectangle boundaries.

    Once that closest point is known, checking circle-rectangle overlap
    becomes a simple distance comparison.
 */