class Solution {
    private:
        using VB = vector<bool>;
        using VVB = vector<VB>;
        using VVVB = vector<VVB>;
        using VVVVB = vector<VVVB>;
        
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    
        struct State {
            int row;
            int col;
            int energyLeft;
            int collectedMask;
        };
    
    public:
        int minMoves(vector<string>& classroom, int energy) {
            int m = classroom.size();
            int n = classroom[0].size();
            
            int maxEnergy = energy;
    
            int litterBit[m][n];
            int litterCount = 0;
            int startRow = 0;
            int startCol = 0;
    
            for(int r = 0; r < m; r++) {
                for(int c = 0; c < n; c++) {
                    litterBit[r][c] = -1;
    
                    if(classroom[r][c] == 'S') {
                        startRow = r;
                        startCol = c;
                    } else if(classroom[r][c] == 'L') {
                        litterBit[r][c] = litterCount;
                        litterCount++;
                    }
                }
            }
    
            if(litterCount == 0) return 0;
            
            int allCollected = (1 << litterCount) - 1; // 2^litterCount - 1;
    
            VVVVB visited(m, VVVB(n, VVB(maxEnergy + 1, VB(1 << litterCount, false))));
    
            queue<State> q;
            q.push({startRow, startCol, maxEnergy, 0});
            visited[startRow][startCol][maxEnergy][0] = true;
    
            int moves = 0;
            while(!q.empty()) {
                int currSize = q.size();
    
                while(currSize--) {
                    State curr = q.front();
                    q.pop();
    
                    if(curr.collectedMask == allCollected) return moves;
    
                    if(curr.energyLeft == 0) continue;
    
                    for(auto &dir : directions) {
                        int nextRow = curr.row + dir[0];
                        int nextCol = curr.col + dir[1];
    
                        if(nextRow < 0 || nextRow >= m || nextCol < 0 || nextCol >= n) continue;
    
                        char cell = classroom[nextRow][nextCol];
                        if(cell == 'X') continue;
    
                        int nextEnergy = curr.energyLeft - 1;
                        int nextCollectedMask = curr.collectedMask;
    
                        if(cell == 'R') nextEnergy = maxEnergy;
                        else if(cell == 'L') nextCollectedMask |= (1 << litterBit[nextRow][nextCol]);
                        
                        if(!visited[nextRow][nextCol][nextEnergy][nextCollectedMask]) {
                            visited[nextRow][nextCol][nextEnergy][nextCollectedMask] = true;
                            q.push({nextRow, nextCol, nextEnergy, nextCollectedMask});
                        }
                    }
                }
                moves++;
            }
            return -1;
        }
    };

/*
    ============================================================
    LeetCode 3568 - Minimum Moves to Clean Classroom
    ============================================================

    Approach:
    ------------------------------------------------------------
    This problem is a shortest-path problem, but the state is
    larger than just:

        (row, col)

    because reaching the same cell with different amounts of
    remaining energy or different already-collected litter can
    lead to completely different future possibilities.

    Therefore, we use:

        Breadth-First Search (BFS)

    over an expanded state:

        (row, col, energyLeft, collectedMask)

    where:

        row, col
            -> current position in the classroom

        energyLeft
            -> amount of energy remaining

        collectedMask
            -> which litter pieces have already been collected

    Every movement costs exactly 1 move.

    Therefore BFS guarantees that the first time we reach a state
    where all litter has been collected, the number of moves is
    minimum.


    ============================================================
    1. Why BFS?
    ============================================================

    Every valid movement from one cell to an adjacent cell costs:

        1 move

    Therefore the classroom can be viewed as an unweighted graph:

        each state = a node
        each valid movement = an edge of cost 1

    For an unweighted graph, BFS explores states in increasing
    order of distance from the starting state.

    So:

        level 0 -> 0 moves
        level 1 -> 1 move
        level 2 -> 2 moves
        level 3 -> 3 moves
        ...

    The moment we find a state where every litter has been
    collected, that level is the minimum possible number of moves.


    ============================================================
    2. Why Position Alone Is NOT Enough
    ============================================================

    Suppose we reach the same cell:

        (r, c)

    in two different ways.

    In the first case:

        energyLeft = 5

    In the second case:

        energyLeft = 1

    These are not equivalent states.

    From the first state we may be able to travel much farther.

    Similarly, suppose we reach the same cell with different
    litter collections:

        collectedMask = 0011

    versus:

        collectedMask = 1011

    The second state has already collected one additional litter
    piece.

    Therefore we cannot simply mark:

        visited[row][col]

    because the same position can legitimately need to be
    visited multiple times with different energy or collected
    litter.

    The complete state must include all information that affects
    future decisions:

        (row, col, energyLeft, collectedMask)


    ============================================================
    3. Representing Litter Using a Bitmask
    ============================================================

    Every litter cell `L` is assigned a unique bit.

    The code does:

        litterBit[r][c] = litterCount;
        litterCount++;

    Suppose there are 4 litter pieces.

    They can be assigned:

        L1 -> bit 0
        L2 -> bit 1
        L3 -> bit 2
        L4 -> bit 3

    Then:

        0000
        means no litter collected

        0001
        means L1 collected

        0101
        means L1 and L3 collected

        1111
        means all four collected

    ------------------------------------------------------------

    When we stand on a litter cell:

        nextCollectedMask |=
            (1 << litterBit[nextRow][nextCol]);

    This sets the corresponding bit to 1.

    The OR operation is important because it preserves all
    previously collected litter.

    Example:

        current mask = 0101

        current litter = bit 1

        0101
        OR 0010
        ------
        0111

    Now bits 0, 1 and 2 are collected.


    ============================================================
    4. Detecting Whether Everything Is Collected
    ============================================================

    Suppose there are:

        litterCount = k

    pieces of litter.

    We need the first k bits to all be 1.

    Therefore:

        allCollected = (1 << k) - 1

    because:

        1 << k

    produces:

        1000...000

    with k zero bits after it.

    Subtracting 1 gives:

        0111...111

    containing exactly k ones.

    ------------------------------------------------------------

    Example:

        k = 3

        1 << 3 = 1000

        1000 - 1 = 0111

    Therefore:

        allCollected = 111

    means every litter piece has been collected.

    The BFS terminates when:

        curr.collectedMask == allCollected


    ============================================================
    5. State Structure
    ============================================================

        struct State {
            int row;
            int col;
            int energyLeft;
            int collectedMask;
        };

    ------------------------------------------------------------

    Each queue element stores the complete information required
    to continue the search.

    For example:

        State {
            row = 2,
            col = 4,
            energyLeft = 3,
            collectedMask = 0101
        }

    means:

        We are currently at (2,4)

        We have 3 units of energy remaining

        Litter represented by bits 0 and 2 has already been
        collected.


    ============================================================
    6. Preprocessing the Classroom
    ============================================================

    The first nested loops scan the classroom.

    For every cell:

        litterBit[r][c] = -1;

    initially means the cell is not litter.

    ------------------------------------------------------------

    If:

        classroom[r][c] == 'S'

    we store:

        startRow
        startCol

    ------------------------------------------------------------

    If:

        classroom[r][c] == 'L'

    we assign it the next available bit:

        litterBit[r][c] = litterCount;
        litterCount++;

    ------------------------------------------------------------

    Example classroom:

        S . L
        . X .
        L . R

    The litter cells might become:

        L(bit 0)
        L(bit 1)

    so:

        litterCount = 2

    and:

        allCollected = (1 << 2) - 1
                     = 3
                     = 11(binary)


    ============================================================
    7. Early Return When There Is No Litter
    ============================================================

        if(litterCount == 0) return 0;

    ------------------------------------------------------------

    If there is no litter at all, the classroom is already clean.

    Therefore no movement is required.

        answer = 0


    ============================================================
    8. The Visited State
    ============================================================

    The code creates:

        VVVVB visited(
            m,
            VVVB(
                n,
                VVB(
                    maxEnergy + 1,
                    VB(
                        1 << litterCount,
                        false
                    )
                )
            )
        );

    This is a four-dimensional boolean structure.

    Conceptually:

        visited[row][col][energyLeft][collectedMask]

    tells us whether we have already reached exactly this state.

    ------------------------------------------------------------

    Dimensions:

        row:
            0 ... m-1

        col:
            0 ... n-1

        energyLeft:
            0 ... maxEnergy

        collectedMask:
            0 ... (2^litterCount - 1)

    ------------------------------------------------------------

    A state is considered visited only if all four components
    match.

    Therefore:

        (r,c,5,0011)

    and:

        (r,c,2,0011)

    are different states.

    Similarly:

        (r,c,5,0011)

    and:

        (r,c,5,1011)

    are different states.


    ============================================================
    9. Initial BFS State
    ============================================================

    The starting state is:

        q.push({
            startRow,
            startCol,
            maxEnergy,
            0
        });

    Meaning:

        Position:
            starting cell

        Energy:
            full energy

        Litter:
            none collected

    Therefore:

        collectedMask = 0

    ------------------------------------------------------------

    The starting state is immediately marked visited:

        visited[startRow][startCol][maxEnergy][0] = true;


    ============================================================
    10. BFS Levels Represent Number of Moves
    ============================================================

    The variable:

        int moves = 0;

    stores the distance from the starting state.

    The outer BFS loop processes one complete level at a time:

        int currSize = q.size();

        while(currSize--) {
            ...
        }

        moves++;

    ------------------------------------------------------------

    At the beginning:

        moves = 0

    so every state in the queue represents zero moves from the
    starting state.

    After processing that level:

        moves++

    and the next states represent one additional move.

    Therefore:

        level 0 -> 0 moves
        level 1 -> 1 move
        level 2 -> 2 moves
        ...

    This is why returning `moves` when all litter is collected
    gives the minimum number of moves.


    ============================================================
    11. Checking the Goal State
    ============================================================

    For every BFS state:

        if(curr.collectedMask == allCollected)
            return moves;

    ------------------------------------------------------------

    Because BFS processes states in increasing distance order,
    the first state satisfying this condition is reached using
    the minimum possible number of moves.

    We do not need to continue searching for another solution.


    ============================================================
    12. Energy Constraint
    ============================================================

    Every movement consumes one unit of energy.

    Therefore:

        if(curr.energyLeft == 0)
            continue;

    ------------------------------------------------------------

    If there is no energy remaining, we cannot make another move.

    Notice that this check happens before exploring neighbors.

    So a state with:

        energyLeft = 0

    can still be a valid answer if all litter has already been
    collected.

    That is why the goal check comes BEFORE the energy check.


    ============================================================
    13. Exploring the Four Directions
    ============================================================

    The four possible movements are:

        {0, 1}    -> right
        {0, -1}   -> left
        {1, 0}    -> down
        {-1, 0}   -> up

    For each direction:

        nextRow = curr.row + dir[0];
        nextCol = curr.col + dir[1];

    ------------------------------------------------------------

    Boundary checks ensure that we remain inside the classroom:

        if(nextRow < 0 ||
           nextRow >= m ||
           nextCol < 0 ||
           nextCol >= n)

            continue;


    ============================================================
    14. Walls
    ============================================================

    If:

        classroom[nextRow][nextCol] == 'X'

    the cell is blocked.

    Therefore:

        if(cell == 'X') continue;

    No state is generated for that movement.


    ============================================================
    15. Energy After Moving
    ============================================================

    Every valid movement initially costs one unit of energy:

        int nextEnergy = curr.energyLeft - 1;

    So if:

        curr.energyLeft = 4

    then after moving:

        nextEnergy = 3

    ------------------------------------------------------------

    However, some cells have special behavior.


    ============================================================
    16. Recharge Cell 'R'
    ============================================================

    If the destination is:

        'R'

    then the energy is completely restored:

        if(cell == 'R')
            nextEnergy = maxEnergy;

    ------------------------------------------------------------

    Notice the order:

        nextEnergy = curr.energyLeft - 1;

        if(cell == 'R')
            nextEnergy = maxEnergy;

    So entering the recharge cell costs one movement, but after
    arriving there, the energy becomes full again.

    Example:

        current energy = 3

        move to R

        energy after movement = 2

        recharge

        energy becomes maxEnergy


    ============================================================
    17. Collecting Litter
    ============================================================

    If the destination cell is:

        'L'

    we collect that litter:

        nextCollectedMask |=
            (1 << litterBit[nextRow][nextCol]);

    ------------------------------------------------------------

    Suppose:

        litterBit[nextRow][nextCol] = 2

    Then:

        1 << 2 = 0100

    If the current mask is:

        0011

    then:

        0011
        OR 0100
        ------
        0111

    The third litter is now marked as collected.

    ------------------------------------------------------------

    If we visit the same litter cell again, its bit is already 1.

    OR-ing it again does not change the mask.

    Example:

        0111
        OR 0100
        ------
        0111

    This is exactly what we want.


    ============================================================
    18. Constructing the Next State
    ============================================================

    After determining:

        nextRow
        nextCol
        nextEnergy
        nextCollectedMask

    the next state is:

        (
            nextRow,
            nextCol,
            nextEnergy,
            nextCollectedMask
        )

    Before inserting it into BFS, we check whether this exact
    state has already been visited.


    ============================================================
    19. Why We Need Four-Dimensional Visited
    ============================================================

    Consider:

        State A:
            (2,3,5,0011)

        State B:
            (2,3,1,0011)

    They have the same position and collected litter, but A has
    more energy.

    They are different states because their future possibilities
    differ.

    ------------------------------------------------------------

    Similarly:

        State A:
            (2,3,5,0011)

        State B:
            (2,3,5,0111)

    have the same position and energy, but B has collected more
    litter.

    They must also remain separate.

    ------------------------------------------------------------

    Therefore the complete state is:

        row
        +
        col
        +
        energy
        +
        collected litter

    and the visited structure tracks exactly that.


    ============================================================
    20. Why Marking Visited Is Safe
    ============================================================

    Suppose we reach the exact same state:

        (row, col, energyLeft, collectedMask)

    for the second time.

    Since all four values are identical, the set of possible
    future moves is also identical.

    Furthermore, BFS reaches states in increasing number of
    moves.

    Therefore the first time this exact state is encountered,
    it has already been reached using the minimum number of
    moves possible.

    There is no benefit in processing the same state again.

    Hence:

        visited[nextRow][nextCol]
                [nextEnergy]
                [nextCollectedMask]

    safely prevents duplicate work.


    ============================================================
    21. Complete Example
    ============================================================

    Consider a conceptual classroom:

        S . L
        . X .
        R . L

    Suppose:

        energy = 4

    There are two litter pieces.

    Assign:

        first L -> bit 0
        second L -> bit 1

    Therefore:

        allCollected = 11(binary)


    ------------------------------------------------------------
    Initial State
    ------------------------------------------------------------

        position      = S
        energy        = 4
        collectedMask = 00
        moves         = 0


    ------------------------------------------------------------
    After Moving Onto First L
    ------------------------------------------------------------

        position      = L
        energy        = 3
        collectedMask = 01
        moves         = 1


    ------------------------------------------------------------
    Suppose We Eventually Reach R
    ------------------------------------------------------------

    Entering R consumes one move, but then:

        energy = maxEnergy = 4


    ------------------------------------------------------------
    After Reaching Second L
    ------------------------------------------------------------

        collectedMask = 11

    Now:

        collectedMask == allCollected

    Therefore BFS returns the current number of moves.

    Because BFS explores levels in order, this is the minimum
    number of moves required.


    ============================================================
    22. Important Detail: Energy Is Part of the Shortest-Path
        State
    ============================================================

    A common mistake would be to treat the classroom as a normal
    grid shortest-path problem.

    That would only track:

        (row, col)

    But here, arriving at a cell with different energy can change
    whether we can reach another litter or recharge station.

    For example:

        Path A:
            reaches (r,c) with 5 energy

        Path B:
            reaches (r,c) with 1 energy

    Even though the position is identical, Path A may continue
    toward another litter while Path B may get stuck.

    Therefore energy must be part of the state.


    ============================================================
    23. Important Detail: Collected Litter Is Also Part of State
    ============================================================

    Similarly, simply knowing:

        (row, col, energy)

    is insufficient.

    Suppose two paths reach the same cell with the same energy:

        Path A:
            collectedMask = 0011

        Path B:
            collectedMask = 0111

    Path B has already collected more litter.

    Requiring the remaining litter to be collected can therefore
    lead to different answers.

    Hence the bitmask is also required in the state.


    ============================================================
    24. Why the First Goal State Is Optimal
    ============================================================

    Every transition represents exactly one movement.

    Therefore all edges in the implicit state graph have weight 1.

    BFS has the property:

        first layer = shortest distance 0
        second layer = shortest distance 1
        third layer = shortest distance 2
        ...

    Suppose BFS first finds:

        collectedMask == allCollected

    at:

        moves = K

    Then there cannot be a valid solution using fewer than K
    moves, because BFS would have processed every state reachable
    in fewer than K moves before reaching this state.

    Therefore K is the minimum.


    ============================================================
    25. Failure Case
    ============================================================

    If the queue becomes empty:

        while(!q.empty())

    without ever finding:

        collectedMask == allCollected

    then no valid sequence of moves can collect all litter.

    The code returns:

        -1

    This means the classroom cannot be completely cleaned under
    the movement and energy constraints.


    ============================================================
    26. Complexity
    ============================================================

    Let:

        m = number of rows
        n = number of columns
        L = number of litter cells
        E = maximum energy

    ------------------------------------------------------------

    Number of possible positions:

        m * n

    Number of possible energy values:

        E + 1

    Number of possible litter masks:

        2^L

    Therefore the maximum number of states is:

        O(m * n * E * 2^L)

    ------------------------------------------------------------

    Each state has at most four transitions because we can move
    in four directions.

    Therefore BFS time complexity is:

        O(m * n * E * 2^L)

    up to the constant factor of four neighboring cells.

    ------------------------------------------------------------

    The visited structure stores one boolean for every possible
    state:

        O(m * n * E * 2^L)

    space.

    The BFS queue can also contain many states, so the overall
    auxiliary space is bounded by the same state-space order.


    ============================================================
    27. Why Bitmasking Is Effective
    ============================================================

    Instead of storing a collection such as:

        {litter1, litter3, litter5}

    for every BFS state, we encode the same information using
    one integer.

    For example:

        litter1 -> bit 0
        litter2 -> bit 1
        litter3 -> bit 2
        litter4 -> bit 3

    Then:

        {litter1, litter3}

    becomes:

        0101

    This makes checking and updating collected litter extremely
    efficient.

    Check all collected:

        mask == allCollected

    Add a litter:

        mask |= (1 << bit)


    ============================================================
    28. Core State Definition
    ============================================================

    The most important part of the entire solution is:

        State =
        (
            position,
            remaining energy,
            collected litter
        )

    More explicitly:

        State =
        (row, col, energyLeft, collectedMask)

    Once this state is identified, the rest of the solution is
    essentially a standard BFS over this expanded state graph.


    ============================================================
    29. Core Algorithm
    ============================================================

    Step 1:
        Scan the classroom.

        Find:
            - starting position
            - every litter position
            - assign each litter a bit

    Step 2:
        Create:

            allCollected = (1 << litterCount) - 1

    Step 3:
        Create a four-dimensional visited structure:

            visited[row][col][energy][mask]

    Step 4:
        Push the initial state:

            (startRow, startCol, maxEnergy, 0)

    Step 5:
        Run BFS level by level.

    Step 6:
        For every state:
            - if all litter collected, return moves
            - if energy is zero, stop expanding this state
            - try all four directions

    Step 7:
        Ignore:
            - out-of-bounds cells
            - walls `X`

    Step 8:
        Decrease energy by one for the movement.

    Step 9:
        If the destination is:
            `R` -> restore energy
            `L` -> update collectedMask

    Step 10:
        If the complete state has not been visited, push it.

    Step 11:
        If BFS finishes without collecting everything,
        return -1.


    ============================================================
    Main Takeaway
    ============================================================

    This is not just a grid BFS.

    It is a BFS over a STATE SPACE.

    The state must remember everything that affects the future:

        (row, col, energyLeft, collectedMask)

    The two major techniques are:

        1. BFS
           because every movement costs exactly 1.

        2. Bitmask
           to efficiently represent which litter pieces have
           already been collected.

    The final mental model is:

        Grid
          +
        Remaining Energy
          +
        Collected Litter
          =
        Complete BFS State

    Once this expanded state is defined correctly, BFS guarantees
    the minimum number of moves.
    ============================================================
*/