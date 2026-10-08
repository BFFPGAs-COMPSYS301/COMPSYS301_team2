function [retmap,retvisited,retsteps] = floodfill(mapfile,startlocation,targetlocation)

map = map_convert(mapfile);
retmap = map;

[maprows,mapcols] = size(map);

visited = false(maprows,mapcols);

parent = zeros(maprows,mapcols,2);

queue = startlocation;

visited(startlocation(1),startlocation(2)) = true;

retvisited = [];

directions = [
    -1  0
     1  0
     0 -1
     0  1
    ];

found = false;

while ~isempty(queue)

    current = queue(1,:);
    queue(1,:) = [];

    retvisited = [retvisited; current];

    % Check if we reached the target
    if current(1) == targetlocation(1) && current(2) == targetlocation(2)
        found = true;
        break;
    end

    % Check neighbours
    for k = 1:4

        neighbour = current + directions(k,:);

        row = neighbour(1);
        col = neighbour(2);

        % Check if inside map
        if row >= 1 && row <= maprows && col >= 1 && col <= mapcols

            % Check if open and not visited
            if map(row,col) == 0 && ~visited(row,col)

                visited(row,col) = true;

                % Remember where we came from
                parent(row,col,1) = current(1);
                parent(row,col,2) = current(2);

                % Add to queue
                queue = [queue; neighbour];

            end
        end
    end
end

% Reconstruct shortest path
retsteps = [];

if found

    current = targetlocation;

    while ~(current(1) == startlocation(1) && current(2) == startlocation(2))

        retsteps = [current; retsteps];

        parentrow = parent(current(1),current(2),1);
        parentcol = parent(current(1),current(2),2);

        current = [parentrow parentcol];

    end

    retsteps = [startlocation; retsteps];

end

plotmap(retmap, retsteps);

end