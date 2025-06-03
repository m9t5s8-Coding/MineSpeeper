#include "Headers/Board.h"


Board::Board()
	:sprite(Texture::texture),
	userClickedMine(false),
	firstClick(true)
{
	boardPosition = sf::Vector2f({ SCREEN_WIDTH / 2 - (WIDTH * CELL_SIZE / 2),
		SCREEN_HEIGHT / 2 - (HEIGHT * CELL_SIZE / 2) });
	boardRect.setSize({ WIDTH * CELL_SIZE,HEIGHT * CELL_SIZE });
	boardRect.setFillColor(sf::Color::Transparent);
	boardRect.setOutlineThickness(2);
	boardRect.setOutlineColor(sf::Color(73, 86, 99));
	boardRect.setPosition(boardPosition);
	cell.resize(WIDTH);
	for (int i = 0;i < WIDTH;i++)
	{
		cell[i].resize(HEIGHT);
	}
	setBoard();
	
}
Board::~Board()
{

}
void Board::setBoard()
{
	for (int i = 0;i < WIDTH;i++)
	{
		for (int j = 0;j < HEIGHT;j++)
		{
			CELL& grid = cell[i][j];
			grid.isRevealed = false;
			grid.isFlagged = false;
			grid.isMine = false;
			grid.adjacentMines = 0;
		}
	}
}


void Board::placeMines(sf::Vector2i safeCell)
{
	std::set<std::pair<int, int>> excluded;

	for (int dx = -1; dx <= 1; dx++)
	{
		for (int dy = -1; dy <= 1; dy++)
		{
			int nx = safeCell.x + dx;
			int ny = safeCell.y + dy;

			if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT)
			{
				excluded.insert({ nx, ny });
			}
		}
	}

	for (unsigned short mineCount = 0; mineCount < MINES;)
	{
		int row = rand() % WIDTH;
		int col = rand() % HEIGHT;
		if (excluded.count({ row, col }) == 0 && !cell[row][col].isMine)
		{
			cell[row][col].isMine = true;
			mineCount++;
		}
	}

	calculateMines();
}


void Board::calculateMines()
{
	for (int i = 0;i < WIDTH;i++)
	{
		for (int j = 0;j < HEIGHT;j++)
		{
			if (!cell[i][j].isMine)
			{
				for (int dx = -1;dx <= 1;dx++)
				{
					for (int dy = -1;dy <= 1;dy++)
					{
						int new_i = i + dx;
						int new_j = j + dy;
						if (new_i >= 0 && new_i < WIDTH && new_j >= 0 && new_j < HEIGHT)
						{
							CELL& grid = cell[new_i][new_j];
							if (grid.isMine)
							{
								cell[i][j].adjacentMines++;
							}
						}
					}
				}
			}
		}
	}
}

void Board::revealCell(sf::Vector2i cellCord)
{
	CELL& grid = cell[cellCord.x][cellCord.y];
	if (firstClick)
	{
		placeMines(cellCord);
		firstClick = false;
	}
	if (!grid.isRevealed && !grid.isFlagged)
	{
		if (grid.isMine)
		{
			userClickedMine = true;
			clickedMinePosition = cellCord;
			revealBoard();
			gameOver = true;
		}
		openNeighbour(cellCord);
	}
	winCondition();
}

void Board::flagCell(sf::Vector2i cellCord)
{
	CELL& grid = cell[cellCord.x][cellCord.y];
	if (!grid.isRevealed)
	{
		grid.isFlagged = true;
	}
	winCondition();
}

void Board::openNeighbour(sf::Vector2i cellCord)
{
	if (cellCord.x < 0 || cellCord.x >= WIDTH || cellCord.y < 0 || cellCord.y >= HEIGHT)
		return;

	CELL& grid = cell[cellCord.x][cellCord.y];

	if (grid.isRevealed || grid.isMine)
		return;

	grid.isRevealed = true;
	if (grid.adjacentMines == 0)
	{
		for (int dx = -1; dx <= 1; dx++)
		{
			for (int dy = -1; dy <= 1;dy++)
			{
				if (dx == 0 && dy == 0)
					continue;

				sf::Vector2i newCord(cellCord.x + dx, cellCord.y + dy);
				openNeighbour(newCord);
			}
		}
	}
}

void Board::revealBoard()
{
	for (int i = 0;i < WIDTH;i++)
	{
		for (int j = 0;j < HEIGHT;j++)
		{
			CELL& grid = cell[i][j];
			if (grid.isMine && !grid.isFlagged)
			{
				grid.isRevealed = true;
			}
			
		}
	}
}

void Board::winCondition()
{
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			const CELL& grid = cell[x][y];
			if (!grid.isMine && !grid.isRevealed)
				return;
		}
	}

	hasWon = true;
}

void Board::setTexture(int i, int j)
{
	sf::Vector2i position;
	CELL& grid = cell[i][j];
	if (!grid.isRevealed)
	{
		if (grid.isFlagged && !grid.isMine && userClickedMine)
		{
			position = sf::Vector2i({ 3 * CELL_SIZE,CELL_SIZE });
		}
		else if (grid.isFlagged)
		{
			position = sf::Vector2i({ CELL_SIZE,CELL_SIZE });
		}
		else
		{
			position = sf::Vector2i({ 0,CELL_SIZE });
		}
	}
	else if (grid.isRevealed)
	{
		if (userClickedMine && clickedMinePosition.x == i && clickedMinePosition.y == j)
		{
			position = sf::Vector2i({ 4 * CELL_SIZE,CELL_SIZE });
		}
		else if (!grid.isMine)
		{
			position = sf::Vector2i({ grid.adjacentMines * CELL_SIZE,0 });
		}
		else
		{
			position = sf::Vector2i({ 2 * CELL_SIZE,CELL_SIZE });
		}
	}
	
	sf::Vector2i size({ CELL_SIZE,CELL_SIZE });
	sprite.setTextureRect({position,size });
}
void Board::Update()
{

}
void Board::Draw(sf::RenderTarget& target)
{
	target.draw(boardRect);
	for (int i = 0;i < WIDTH;i++)
	{
		for (int j = 0;j < HEIGHT;j++)
		{
			setTexture(i, j);
			sprite.setPosition(sf::Vector2f(boardPosition.x + j * CELL_SIZE, boardPosition.y + i * CELL_SIZE));
			target.draw(sprite);
		}
	}
}