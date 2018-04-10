#include "astar.h"

int astar::dx[astar::dir] = {1, 0, -1, 0};
int astar::dy[astar::dir] = {0, 1, 0, -1};

class node {
    // Current position
    sf::Vector2i pos;
    // Total distance already travelled to reach the node
    int level;
    // Priority = level + remaining distance estimate
    int priority;  // Smaller => higher priority

    public:
		node(int x, int y, int level, int priority) : node(sf::Vector2i(x, y), level, priority) {}
        node(sf::Vector2i pos, int level, int priority) {
			this->pos = pos;
			this->level = level;
			this->priority = priority;
		}

		sf::Vector2i getPos() { return pos; }
        int getxPos() const { return pos.x; }
        int getyPos() const { return pos.y; }
        int getLevel() const { return level; }
        int getPriority() const { return priority; }

        void updatePriority(const sf::Vector2i& dest) {
             priority = level + estimate(dest); //A*
        }

        void nextLevel() {
             level += 1;
        }

        // Estimation function for the remaining distance to the goal.
        int estimate(const sf::Vector2i& dest) const
        {
            // Manhattan distance
            return abs(pos.x - dest.x) + abs(pos.y - dest.y);
        }
};

// Determine priority (in the priority queue)
bool operator<(const node & a, const node & b)
{
  return a.getPriority() > b.getPriority();
}

// A-star algorithm.
path astar::aStar(const sf::Vector2i& start, const sf::Vector2i& end,
	std::function<bool(int, int)> isBlocked) {
    if(isBlocked(start.x, start.y) || isBlocked(end.x, end.y))
        return path();
	static int closed_nodes_map[n][m]; // Map of closed (tried-out) nodes
	static int open_nodes_map[n][m]; // Map of open (not-yet-tried) nodes
	static int dir_map[n][m]; // Map of directions

    static std::priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
    static int pqi = 0; // pq index
    static node* n0;
    static node* m0;
    static int i, j, x, y, xdx, ydy;
    static char c;

    // Reset the node maps
    for(y = 0; y < m; y++) {
        for(x = 0; x < n; x++) {
            closed_nodes_map[x][y] = 0;
            open_nodes_map[x][y] = 0;
        }
    }

    // Create the start node and push into list of open nodes
    n0 = new node(start, 0, 0);
    n0->updatePriority(end);
    pq[pqi].push(*n0);
    open_nodes_map[start.x][start.y] = n0->getPriority(); // mark it on the open nodes map
	delete n0;
    // A* search
    while(!pq[pqi].empty())
    {
        // get the current node w/ the highest priority
        // from the list of open nodes
		node topNode = pq[pqi].top();
        n0 = new node(topNode.getPos(),
                     pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

        x = n0->getxPos();
		y = n0->getyPos();

        pq[pqi].pop(); // remove the node from the open list
        open_nodes_map[x][y]=0;
        // mark it on the closed nodes map
        closed_nodes_map[x][y] = 1;

        // quit searching when the goal state is reached
        //if((*n0).estimate(xFinish, yFinish) == 0)
        if(n0->getPos() == end) {
            // generate the path from finish to start
            // by following the directions
			path result;
			result.push(end);
            while(!(x == start.x && y == start.y))
            {
                j = dir_map[x][y];
                x += dx[j];
                y += dy[j];
				result.push(sf::Vector2i(x, y));
            }

            // Garbage collection
            delete n0;
            // Empty the leftover nodes
            while(!pq[pqi].empty()) pq[pqi].pop();

            return result;
        }

        // Generate moves (child nodes) in all possible directions
        for(i = 0; i < dir; i++) {
            xdx = x + dx[i];
			ydy = y + dy[i];

            if(!(isBlocked(xdx, ydy) || closed_nodes_map[xdx][ydy] == 1)) {
                // Generate a child node
                m0 = new node(xdx, ydy, n0->getLevel(), n0->getPriority());
                m0->nextLevel();
                m0->updatePriority(end);

                // If it is not in the open list then add into that
                if(open_nodes_map[xdx][ydy] == 0) {
                    open_nodes_map[xdx][ydy] = m0->getPriority();
                    pq[pqi].push(*m0);
                    // Mark its parent node direction
                    dir_map[xdx][ydy] = (i + dir/2) % dir;
                } else if(open_nodes_map[xdx][ydy] > m0->getPriority()) {
                    // Update the priority info
                    open_nodes_map[xdx][ydy] = m0->getPriority();
                    // Update the parent direction info
                    dir_map[xdx][ydy] = (i + dir/2) % dir;

					/*
                    *	Replace the node by emptying one pq to the other one
                    *	except the node to be replaced will be ignored
                    *	and the new node will be pushed in instead.
					*/
                    while(!(pq[pqi].top().getxPos() == xdx &&
                           pq[pqi].top().getyPos() == ydy)) {
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }
                    pq[pqi].pop(); // Remove the wanted node

                    // Empty the larger size pq to the smaller one
                    if(pq[pqi].size() > pq[1-pqi].size())
						pqi = 1 - pqi;
                    while(!pq[pqi].empty()) {
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }
                    pqi = 1-pqi;
                    pq[pqi].push(*m0); // Add the better node instead
                }
                delete m0; // Garbage collection
            }
        }
        delete n0; // Garbage collection
    }
    return path(); // No route found
}
