// Setup for the farm grid
const gridSize = 10;
let startCell = null;
let endCell = null;
let grid = [];
let path = [];
let obstacles = [];
let droneSpeed = 100; // Default speed
let isObstacleMode = false;

// Initialize the farm grid
function initGrid() {
    const farmMap = document.getElementById('farm-map');
    grid = [];
    for (let i = 0; i < gridSize; i++) {
        const row = [];
        for (let j = 0; j < gridSize; j++) {
            const cell = document.createElement('div');
            cell.classList.add('cell');
            cell.dataset.x = i;
            cell.dataset.y = j;

            cell.addEventListener('click', () => handleCellClick(i, j, cell));

            farmMap.appendChild(cell);
            row.push(cell);
        }
        grid.push(row);
    }
}

// Handle cell click for selecting start, end, or obstacles
function handleCellClick(i, j, cell) {
    if (isObstacleMode) {
        if (cell.classList.contains('obstacle')) {
            cell.classList.remove('obstacle');
            obstacles = obstacles.filter(o => !(o.x === i && o.y === j));
        } else {
            cell.classList.add('obstacle');
            obstacles.push({ x: i, y: j });
        }
    } else if (!startCell) {
        startCell = { x: i, y: j };
        cell.classList.add('start');
    } else if (!endCell) {
        endCell = { x: i, y: j };
        cell.classList.add('end');
    }
}

// Toggle obstacle mode
function toggleObstacleMode() {
    isObstacleMode = !isObstacleMode;
    alert(isObstacleMode ? 'Click cells to add obstacles.' : 'Obstacle mode off.');
}

// Clear the grid for a new setup
function clearGrid() {
    startCell = null;
    endCell = null;
    obstacles = [];
    grid.forEach(row => row.forEach(cell => {
        cell.classList.remove('start', 'end', 'path', 'obstacle');
    }));
    document.getElementById('pathOutput').textContent = '';
}

// Dijkstra's algorithm to find the shortest path
function dijkstra() {
    let openList = [];
    let closedList = [];
    let gScore = {};
    let fScore = {};
    let cameFrom = {};

    // Initialize scores
    for (let i = 0; i < gridSize; i++) {
        for (let j = 0; j < gridSize; j++) {
            gScore[`${i},${j}`] = Infinity;
            fScore[`${i},${j}`] = Infinity;
        }
    }

    gScore[`${startCell.x},${startCell.y}`] = 0;
    fScore[`${startCell.x},${startCell.y}`] = heuristic(startCell, endCell);
    openList.push(startCell);

    while (openList.length > 0) {
        let current = openList.reduce((lowest, cell) => {
            let score = fScore[`${cell.x},${cell.y}`];
            return score < fScore[`${lowest.x},${lowest.y}`] ? cell : lowest;
        });

        if (current.x === endCell.x && current.y === endCell.y) {
            let pathCells = [];
            while (current) {
                pathCells.unshift(current);
                current = cameFrom[`${current.x},${current.y}`];
            }
            return pathCells;
        }

        openList = openList.filter(cell => cell !== current);
        closedList.push(current);

        let neighbors = getNeighbors(current);
        for (let neighbor of neighbors) {
            if (closedList.some(cell => cell.x === neighbor.x && cell.y === neighbor.y)) continue;
            if (obstacles.some(o => o.x === neighbor.x && o.y === neighbor.y)) continue;

            let tentativeGScore = gScore[`${current.x},${current.y}`] + 1;

            if (!openList.some(cell => cell.x === neighbor.x && cell.y === neighbor.y)) {
                openList.push(neighbor);
            } else if (tentativeGScore >= gScore[`${neighbor.x},${neighbor.y}`]) {
                continue;
            }

            cameFrom[`${neighbor.x},${neighbor.y}`] = current;
            gScore[`${neighbor.x},${neighbor.y}`] = tentativeGScore;
            fScore[`${neighbor.x},${neighbor.y}`] = gScore[`${neighbor.x},${neighbor.y}`] + heuristic(neighbor, endCell);
        }
    }

    return [];
}

// Heuristic function (Manhattan distance)
function heuristic(cell, end) {
    return Math.abs(cell.x - end.x) + Math.abs(cell.y - end.y);
}

// Get the valid neighbors of a cell
function getNeighbors(cell) {
    const neighbors = [];
    const directions = [
        { x: -1, y: 0 }, { x: 1, y: 0 },
        { x: 0, y: -1 }, { x: 0, y: 1 }
    ];

    for (let direction of directions) {
        let nx = cell.x + direction.x;
        let ny = cell.y + direction.y;

        if (nx >= 0 && ny >= 0 && nx < gridSize && ny < gridSize) {
            neighbors.push({ x: nx, y: ny });
        }
    }

    return neighbors;
}

// Visualize the path on the map
function visualizePath(pathCells) {
    pathCells.forEach(cell => {
        const gridCell = grid[cell.x][cell.y];
        gridCell.classList.add('path');
    });

    const pathOutput = pathCells.map(cell => `(${cell.x}, ${cell.y})`).join(' -> ');
    document.getElementById('pathOutput').textContent = pathOutput;
    animateDroneMovement(pathCells);
}

// Animate the drone along the path
function animateDroneMovement(pathCells) {
    let step = 0;
    const droneIcon = document.createElement('div');
    droneIcon.classList.add('drone-icon');
    grid[pathCells[0].x][pathCells[0].y].appendChild(droneIcon);

    function moveDrone() {
        if (step < pathCells.length) {
            const { x, y } = pathCells[step];
            const cell = grid[x][y];
            cell.appendChild(droneIcon);

            step++;
        }
    }

    const interval = setInterval(() => {
        if (step < pathCells.length) {
            moveDrone();
        } else {
            clearInterval(interval);
        }
    }, droneSpeed);
}

// Start the pathfinding process
function startPathfinding() {
    if (!startCell || !endCell) {
        alert('Please select both start and end points!');
        return;
    }

    let pathCells = dijkstra();
    visualizePath(pathCells);
}

// Open settings modal
function openSettingsModal() {
    document.getElementById('settings-modal').style.display = 'flex';
}

// Close settings modal
function closeSettingsModal() {
    document.getElementById('settings-modal').style.display = 'none';
}

// Initialize the grid when the page loads
initGrid();
