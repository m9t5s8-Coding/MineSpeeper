#include "Headers/AiMinesweeper.h"

AiMinesweeper::AiMinesweeper()
	:gen(std::random_device{}())
{
	aiCell.resize(WIDTH);
	for (int i = 0;i < WIDTH;i++)
	{
		aiCell[i].resize(HEIGHT);
	}
}

AiMinesweeper::~AiMinesweeper()
{

}

void AiMinesweeper::copyBoard(const std::vector<std::vector<CELL>>& boardCell)
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			const CELL& board = boardCell[i][j];
			AICELL& aiboard = aiCell[i][j];
			aiboard.isFlagged = board.isFlagged;
			aiboard.isRevealed = board.isRevealed;
			if (aiboard.isRevealed)
			{
				aiboard.adjacentMines = board.adjacentMines;
			}
			else
			{
				aiboard.adjacentMines = UNKNOWN;
			}
		}
	}
}

MOVES AiMinesweeper::getRandomMoves()
{
	MOVES move;
	while (true)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distX(0, WIDTH - 1);
		std::uniform_int_distribution<> distY(0, HEIGHT - 1);

		int x = distX(gen);
		int y = distY(gen);

		AICELL& cell = aiCell[x][y];

		if (!cell.isRevealed && !cell.isFlagged)
		{
			move.cellCord.x = x;
			move.cellCord.y = y;
			move.isReveal = true;
			move.isValid = true;
			break;
		}
	}
	std::cout << "Random Move generated" << std::endl;
	return move;
}

MOVES AiMinesweeper::lookNeighbour()
{
	MOVES move;
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			AICELL& center = aiCell[i][j];
			if (center.isRevealed && center.adjacentMines > 0)
			{
				std::vector<sf::Vector2i> hiddenCells;
				int flagCount = 0;
				for (int dx = -1;dx <= 1;dx++)
				{
					for (int dy = -1;dy <= 1;dy++)
					{
						int new_i = i + dx;
						int new_j = j + dy;
						if (new_i >= 0 && new_i < WIDTH && new_j >= 0 && new_j < HEIGHT)
						{
							AICELL& neignbour = aiCell[new_i][new_j];
							if (!neignbour.isRevealed && !neignbour.isFlagged)
							{
								hiddenCells.push_back({ new_i,new_j });
							}
							if (neignbour.isFlagged)
							{
								flagCount++;
							}
						}
					}
				}
				
				int unknownMines = center.adjacentMines - flagCount;
				if (unknownMines == hiddenCells.size() && !hiddenCells.empty())
				{
					std::uniform_int_distribution<> dist(0, hiddenCells.size() - 1);
					int idx = dist(gen);
					sf::Vector2i pos = hiddenCells[idx];
					move.cellCord = pos;
					move.isReveal = false;
					move.isValid = true;
					return move;
				}
				else if (flagCount == center.adjacentMines && !hiddenCells.empty())
				{
					std::uniform_int_distribution<> dist(0, hiddenCells.size() - 1);
					int idx = dist(gen);
					sf::Vector2i pos = hiddenCells[idx];
					move.cellCord = pos;
					move.isReveal = true;
					move.isValid = true;
					return move;
				}
			}
		}
	}
	move = subsetElimination();
	return move;
}
MOVES AiMinesweeper::subsetElimination()
{
	std::cout << "Generating subsetElimination move" << std::endl;
	

	struct Groups
	{
		std::set<sf::Vector2i, Vector2iCompare> hiddenCells;
		int remainingMine;
	};
	std::vector<Groups> group;

	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			AICELL& center = aiCell[i][j];
			if (center.isRevealed && center.adjacentMines > 0)
			{
				std::vector<sf::Vector2i> hiddenCell;
				std::set<sf::Vector2i, Vector2iCompare> hiddenCellsSet;
				int flagCount = 0;

				for (int dx = -1; dx <= 1; dx++)
				{
					for (int dy = -1; dy <= 1; dy++)
					{
						int ni = i + dx;
						int nj = j + dy;
						if (ni >= 0 && ni < WIDTH && nj >= 0 && nj < HEIGHT)
						{
							AICELL& neighbor = aiCell[ni][nj];
							sf::Vector2i pos{ ni, nj };

							if (!neighbor.isRevealed && !neighbor.isFlagged)
							{
								hiddenCell.push_back(pos);
								hiddenCellsSet.insert(pos);
							}
							if (neighbor.isFlagged)
								flagCount++;
						}
					}
				}

				int remainingMines = center.adjacentMines - flagCount;
				if (!hiddenCell.empty() && remainingMines >= 0 && remainingMines <= (int)hiddenCell.size())
				{
					group.push_back({ hiddenCellsSet,remainingMines });
				}
			}
		}
	}
	for (size_t i = 0; i < group.size(); ++i)
	{
		for (size_t j = 0; j < group.size(); ++j)
		{
			if (i == j) continue;
			const auto& g1 = group[i];
			const auto& g2 = group[j];


			if (std::includes(g2.hiddenCells.begin(), g2.hiddenCells.end(),
				g1.hiddenCells.begin(), g1.hiddenCells.end(), Vector2iCompare()))
			{
				std::set<sf::Vector2i, Vector2iCompare> diff;
				std::set_difference(g2.hiddenCells.begin(), g2.hiddenCells.end(),
					g1.hiddenCells.begin(), g1.hiddenCells.end(),
					std::inserter(diff, diff.begin()), Vector2iCompare());

				int diffMines = g2.remainingMine - g1.remainingMine;

				if (diffMines == 0)
				{
					for (auto& cell : diff)
					{
						if (!aiCell[cell.x][cell.y].isFlagged)
							return MOVES{ cell,true,true }; 
					}
				}
				else if ((int)diff.size() == diffMines)
				{
					for (auto& cell : diff)
					{
						if (!aiCell[cell.x][cell.y].isFlagged)
							return MOVES{ cell,true,true };
					}
				}
			}
		}
	}
	
	//return MOVES{ sf::Vector2i({0,0}) , true , false };
	return getRandomMoves();
}
MOVES AiMinesweeper::getHint()
{
	MOVES move;
	move = lookNeighbour();
	return move;
}
