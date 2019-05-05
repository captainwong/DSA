#pragma once

#include "../../include/util/util.h"
#include "../../include/dtl/stack.h"

template <int W, int H>
struct Labyrinth 
{
	enum class Status {
		AVAILABLE,
		ROUTE,
		BACKTRACKED,
		WALL,
	};

	enum class Direction {
		UNKNOWN,
		EAST,
		SOUTH,
		WEST,
		NORTH,
		NO_WAY,
	};

	static char direction2char(Direction di) {
		switch (di) {
			case Direction::UNKNOWN: return 'U';
			case Direction::EAST: return 'E';
			case Direction::SOUTH: return 'S';
			case Direction::WEST: return 'W';
			case Direction::NORTH: return 'N';
			default: return 'X'; break;
		}
	}

	struct Cell
	{
		int x = 0;
		int y = 0;

		Status status = Status::WALL;
		Direction incoming = Direction::UNKNOWN;
		Direction outgoing = Direction::UNKNOWN;

		/**********************习题4-17（a）*************************/
		// 由于每个格点都是固定地按照东南西北的次序，逐个试探相邻格点
		// 因此，即使目标格点紧邻起始点，也有可能最坏情况下遍历所有(n-2)^2个格点之后才能抵达终点
		Direction nextDirection() const {
			switch (outgoing) {
				case Direction::UNKNOWN: return Direction::EAST;
				case Direction::EAST: return Direction::SOUTH;
				case Direction::SOUTH: return Direction::WEST;
				case Direction::WEST: return Direction::NORTH;
				case Direction::NORTH: return Direction::NO_WAY;
				default: assert(0); return Direction::NO_WAY; break;
			}
		}

		/**********************习题4-17（b）*************************/
		// 按照随机次序试探相邻格点

		// 保存已经试探过的方向
		bool triedDirections[(size_t)Direction::NO_WAY] = { false };

		Direction nextDirection2() {
			switch (outgoing) {
				case Direction::UNKNOWN: 
				case Direction::EAST:
				case Direction::SOUTH:
				case Direction::WEST:
				case Direction::NORTH: 
					{
						triedDirections[(size_t)outgoing] = true;
						Direction da[(size_t)Direction::NO_WAY];
						int ds = 0;
						for (Direction d = Direction::EAST; d != Direction::NO_WAY; d = (Direction)((size_t)d + 1)) {
							if (!triedDirections[(size_t)d]) {
								da[ds++] = d;
							}
						}

						if (ds > 0) {
							return outgoing = da[rand() % ds];
						}
					}
					break;
				default: assert(0); break;
			}

			return outgoing = Direction::NO_WAY;
		}

		void display() const {
			printf("%c -> (%d, %d) -> %c\n", direction2char(incoming), x, y, direction2char(outgoing));
		}
	};

	typedef Cell* PCell;

	// TODO: 空间连续。但没法支持巨大的迷宫，有待改进
	PCell laby[W][H];
	
	//! 起点
	PCell startCell;
	//! 目标
	PCell goalCell;

	Labyrinth() {
		for (int x = 0; x < W; x++) {
			for (int y = 0; y < H; y++) {
				auto cell = new Cell();
				cell->x = x;
				cell->y = y;

				// 非边界单元75%概率可用
				if (0 < x && x < W - 1 && 0 < y && y < H - 1 && dtl::dice(4)) {
					cell->status = Status::AVAILABLE;
				} else { // 否则设置为墙
					cell->status = Status::WALL;
				}

				laby[x][y] = cell;
			}
		}

		dtl::srand_time();

		// 起点位于边界
		startCell = laby[dtl::dice(W - 1) + 1][dtl::dice(H - 1) + 1];
		startCell->incoming = Direction::UNKNOWN;
		// 终点位于边界
		goalCell = laby[dtl::dice(W - 1) + 1][dtl::dice(H - 1) + 1];
		// 起点、终点必须为可用状态
		startCell->status = goalCell->status = Status::AVAILABLE;
	}

	bool solve(int wait_ms = dtl::WAIT_PAUSE) {
		dtl::Stack<PCell> path; // 通路
		startCell->status = Status::ROUTE;
		path.push(startCell);
		do {
			printf("startCell: ");
			startCell->display();
			printf("goalCell: ");
			goalCell->display();
			dtl::wait(wait_ms);
			
			display();
			dtl::wait(wait_ms);
			auto cell = path.top();
			if (cell == goalCell) { return true; }

			cell->display();
			while ((cell->nextDirection2()) < Direction::NO_WAY) {
				if (neighbor(cell) && Status::AVAILABLE == neighbor(cell)->status) {
					break;
				}
			}

			if (cell->outgoing < Direction::NO_WAY) {
				cell = move(cell);
				cell->status = Status::ROUTE;
				cell->outgoing = Direction::UNKNOWN;
				cell->display();
				path.push(cell);
			} else {
				cell->status = Status::BACKTRACKED;
				cell = path.pop();
			}

			dtl::wait(wait_ms);
		} while (!path.empty());

		return false;
	}

	
	PCell neighbor(PCell cell) {
		PCell next = nullptr;
		switch (cell->outgoing) {
			case Direction::EAST: if (cell->x + 1 >= W) { break; } next = laby[cell->x + 1][cell->y]; break;
			case Direction::SOUTH: if (cell->y + 1 >= H) { break; } next = laby[cell->x][cell->y + 1]; break;
			case Direction::WEST: if (cell->x - 1 < 0) { break; } next = laby[cell->x - 1][cell->y]; break;
			case Direction::NORTH: if (cell->y - 1 < 0) { break; } next = laby[cell->x][cell->y - 1]; break;
			default: assert(0); next = nullptr; break;
		}
		return next;
	}

	PCell move(PCell cell) {
		PCell next = nullptr;
		switch (cell->outgoing) {
			case Direction::EAST: if (cell->x + 1 >= W) { break; } next = laby[cell->x + 1][cell->y]; next->incoming = Direction::WEST; break;
			case Direction::SOUTH: if (cell->y + 1 >= H) { break; } next = laby[cell->x][cell->y + 1]; next->incoming = Direction::NORTH; break;
			case Direction::WEST: if (cell->x - 1 < 0) { break; } next = laby[cell->x - 1][cell->y]; next->incoming = Direction::EAST; break;
			case Direction::NORTH: if (cell->y - 1 < 0) { break; } next = laby[cell->x][cell->y - 1]; next->incoming = Direction::SOUTH; break;
			default: assert(0); break;
		}
		return next;
	}

	void display() { // ┘ └ ┐ ┌ │ ─
		static const char* pattern[5][5] = {
		   "┼", "┼", "┼", "┼", "┼",
		   "┼", "  ", "┌", "─", "└",
		   "┼", "┌", "  ", "┐", "│",
		   "┼", "─", "┐", "  ", "┘",
		   "┼", "└", "│", "┘", "  "
		};
		system("cls");
		printf("  ");
		for (int j = 0; j < H; j++)
			(j < 10) ? printf("%2X", j) : printf(" %c", 'A' - 10 + j);
		printf("\n");
		for (int j = 0; j < H; j++) {
			(j < 10) ? printf("%2X", j) : printf(" %c", 'A' - 10 + j);
			for (int i = 0; i < W; i++)
				if (goalCell == laby[i][j])
					printf("﹩");
				else
					switch (laby[i][j]->status) {
						case Status::WALL:  printf("█");   break;
						case Status::BACKTRACKED: printf("○");   break;
						case Status::AVAILABLE: printf("  ");   break;
						default: printf("%s", pattern[int(laby[i][j]->outgoing)][int(laby[i][j]->incoming)]);   break;
					}
			printf("\n");
		}//for
	}//displayLaby
};
