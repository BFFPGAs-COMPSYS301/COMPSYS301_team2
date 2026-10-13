function [retmap,retvisited,retsteps] = astar_dynamic(mapfile,startlocation,targetlocation)

% ============================================================
% DYNAMIC A* / D*-LITE STYLE PATH PLANNER
%
% The algorithm:
%   1. Finds an initial path from start to target.
%   2. Moves the unit one cell at a time.
%   3. Re-reads the map after every movement.
%   4. Detects changes to the map.
%   5. Updates the path when obstacles change.
%
% Map convention:
%   0 = free space
%   non-zero = wall/obstacle
% ============================================================

% Load the initial map

map = map_convert(mapfile);

retmap = map;

[maprows,mapcols] = size(map);

% D*-Lite data structures

% g-value
g = inf(maprows,mapcols);

% rhs-value
rhs = inf(maprows,mapcols);

% The rhs value of the goal is zero
rhs(targetlocation(1),targetlocation(2)) = 0;


% km is used by D*-Lite when the start moves
km = 0;


% Previous position of the start
laststart = startlocation;


% Priority queue
openSet = [];

% Directions

directions = [
    -1  0       % up
     1  0       % down
     0 -1       % left
     0  1       % right
];

% Add the goal to the priority queue

key = calculateKey(targetlocation, startlocation, g, rhs, km);

openSet = [openSet; targetlocation key];

% Initial D*-Lite calculation

[g,rhs,openSet] = computeShortestPath(map, g, rhs, openSet, startlocation, targetlocation, km, directions);

% Variables for output

retvisited = [];
retsteps = [];

current = startlocation;

retvisited = [retvisited; current];
retsteps = [retsteps; current];

% Main dynamic loop

while ~(current(1) == targetlocation(1) && current(2) == targetlocation(2))

    % Find the best neighbouring cell

    neighbours = [];

    for k = 1:4

        neighbour = current + directions(k,:);

        row = neighbour(1);
        col = neighbour(2);

        % Check map boundaries
        if row >= 1 && row <= maprows && col >= 1 && col <= mapcols

            % Check that it is not a wall
            if map(row,col) == 0

                neighbours = [neighbours; neighbour];

            end
        end
    end

    % If there are no possible moves, stop

    if isempty(neighbours)

        disp('No path available.');

        break;

    end


    % Choose neighbour with lowest g-value

    bestNeighbour = [];
    bestValue = inf;

    for i = 1:size(neighbours,1)

        row = neighbours(i,1);
        col = neighbours(i,2);

        if g(row,col) < bestValue

            bestValue = g(row,col);

            bestNeighbour = neighbours(i,:);

        end
    end


    % Check whether a path exists

    if isempty(bestNeighbour) || isinf(bestValue)

        disp('No path available.');

        break;

    end


    % Move the unit one cell

    current = bestNeighbour;

    retvisited = [retvisited; current];

    retsteps = [retsteps; current];


    % Start has moved
    %
    % D*-Lite updates km according to how far the start moved.

    km = km + heuristic(laststart,current);

    laststart = current;

    % Check whether the map has changed

    newmap = map_convert(mapfile);


    if ~isequal(newmap,map)

        disp('Map changed - updating path...');

        % Find cells whose map values have changed

        changed = find(map ~= newmap);

        map = newmap;

        retmap = map;

        % Update affected vertices

        for n = 1:length(changed)

            [row,col] = ind2sub(size(map),changed(n));

            changedCell = [row,col];


            % Update the changed cell
            [rhs,openSet] = updateVertex(changedCell, current, targetlocation, map, g, ...
                rhs, openSet, km, directions);

            % Also update its neighbours

            for k = 1:4

                neighbour = changedCell + directions(k,:);

                nr = neighbour(1);
                nc = neighbour(2);

                if nr >= 1 && nr <= maprows && nc >= 1 && nc <= mapcols

                    [rhs,openSet] = updateVertex(neighbour, current, targetlocation, map, g, rhs, ...
                        openSet, km, directions);
                end
            end
        end

        % Recalculate only what is necessary

        [g,rhs,openSet] = computeShortestPath(map, g, rhs, openSet, current, targetlocation, km, directions);

    end

end


% Display result

plotmap(retmap,retsteps);


end


% HELPER FUNCTIONS


function key = calculateKey(position,start,g,rhs,km)

row = position(1);
col = position(2);

minValue = min(g(row,col),rhs(row,col));

key1 = minValue + heuristic(start,position) + km;

key2 = minValue;

key = [key1 key2];

end


function h = heuristic(a,b)

h = abs(a(1)-b(1)) + ...
    abs(a(2)-b(2));

end



function [g,rhs,openSet] = computeShortestPath( ...
    map,g,rhs,openSet,start,target,km,directions)


while true

    % Calculate start key

    startKey = calculateKey(start,start,g,rhs,km);


    % Find smallest key in queue

    if isempty(openSet)

        break;

    end


    bestIndex = 1;

    bestKey = openSet(1,3:4);


    for i = 2:size(openSet,1)

        currentKey = openSet(i,3:4);

        if currentKey(1) < bestKey(1) || (currentKey(1) == bestKey(1) && currentKey(2) < bestKey(2))

            bestIndex = i;

            bestKey = currentKey;

        end
    end


    % Stop when start is consistent

    if ~isinf(g(start(1),start(2))) && ...
       g(start(1),start(2)) <= rhs(start(1),start(2))

        if bestKey(1) >= startKey(1)

            break;

        end
    end

    % Remove smallest item

    current = openSet(bestIndex,1:2);

    oldKey = openSet(bestIndex,3:4);

    openSet(bestIndex,:) = [];


    currentKey = calculateKey( ...
        current,start,g,rhs,km);

    % Key is out of date

    if oldKey(1) < currentKey(1) || (oldKey(1) == currentKey(1) && oldKey(2) < currentKey(2))

        openSet = [openSet; current currentKey];

        continue;

    end

    row = current(1);
    col = current(2);

    % If g > rhs

    if g(row,col) > rhs(row,col)

        g(row,col) = rhs(row,col);


        % Update predecessors
        for k = 1:4

            predecessor = current + directions(k,:);

            pr = predecessor(1);
            pc = predecessor(2);

            if pr >= 1 && pr <= size(map,1) && pc >= 1 && pc <= size(map,2)

                [rhs,openSet] = updateVertex(predecessor, start, target, map, g, rhs, openSet, km, directions);
            end
        end
    else

        % Set g to infinity

        g(row,col) = inf;

        % Update current
        [rhs,openSet] = updateVertex(current, start, target, map, g, rhs, openSet, km, directions);

        % Update predecessors
        for k = 1:4

            predecessor = current + directions(k,:);

            pr = predecessor(1);
            pc = predecessor(2);

            if pr >= 1 && pr <= size(map,1) && pc >= 1 && pc <= size(map,2)

                [rhs,openSet] = updateVertex(predecessor, start, target, map, g, rhs, openSet, km, directions);
            end
        end

    end

end

end

function [rhs,openSet] = updateVertex(position,start,target,map,g,rhs,openSet,km,directions)


row = position(1);
col = position(2);

% The target always has rhs = 0

if row == target(1) && col == target(2)

    rhs(row,col) = 0;

else

    % If this cell is a wall, it cannot be used

    if map(row,col) ~= 0

        rhs(row,col) = inf;

    else

        minValue = inf;

        % Look at neighbouring cells

        for k = 1:4

            neighbour = position + directions(k,:);

            nr = neighbour(1);
            nc = neighbour(2);

            if nr >= 1 && nr <= size(map,1) && nc >= 1 && nc <= size(map,2)

                if map(nr,nc) == 0

                    value = 1 + g(nr,nc);

                    if value < minValue

                        minValue = value;

                    end
                end
            end
        end


        rhs(row,col) = minValue;

    end
end

% Remove old entries for this cell from queue

if ~isempty(openSet)

    keep = ~(openSet(:,1) == row & openSet(:,2) == col);

    openSet = openSet(keep,:);

end

% If g != rhs, this cell is inconsistent and belongs
% in the priority queue

if g(row,col) ~= rhs(row,col)

    key = calculateKey(position, start, g, rhs, km);

    openSet = [openSet; position key];

end

end


function placestep(position,i)

% Plot a yellow rectangle and print the step number.

position = [16-position(1) position(2)];

position = [position(2)+0.1 position(1)+0.1];

rectangle('Position',[position,0.8,0.8], 'FaceColor','y');

c = sprintf('%d',i);

text(position(1)+0.2, position(2)+0.2, c, 'FontSize',10);

end