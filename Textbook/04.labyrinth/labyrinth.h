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

		void display() const {
			printf("%c -> (%d, %d) -> %c\n", direction2char(incoming), x, y, direction2char(outgoing));
		}
	};

	typedef Cell* PCell;

	// TODO: �ռ���������û��֧�־޴���Թ����д��Ľ�
	PCell laby[W][H];
	
	//! ���
	PCell startCell;
	//! Ŀ��
	PCell goalCell;

	Labyrinth() {
		for (int x = 0; x < W; x++) {
			for (int y = 0; y < H; y++) {
				auto cell = new Cell();
				cell->x = x;
				cell->y = y;

				// �Ǳ߽絥Ԫ75%���ʿ���
				if (0 < x && x < W - 1 && 0 < y && y < H - 1 && dtl::dice(4)) {
					cell->status = Status::AVAILABLE;
				} else { // ��������Ϊǽ
					cell->status = Status::WALL;
				}

				laby[x][y] = cell;
			}
		}

		dtl::srand_time();

		// ���λ�ڱ߽�
		startCell = laby[dtl::dice(W - 1) + 1][dtl::dice(H - 1) + 1];
		startCell->incoming = Direction::UNKNOWN;
		// �յ�λ�ڱ߽�
		goalCell = laby[dtl::dice(W - 1) + 1][dtl::dice(H - 1) + 1];
		// ��㡢�յ����Ϊ����״̬
		startCell->status = goalCell->status = Status::AVAILABLE;
	}

	bool solve(int wait_ms = dtl::WAIT_PAUSE) {
		dtl::Stack<PCell> path; // ͨ·
		startCell->status = Status::ROUTE;
		path.push(startCell);
		do {
			display();
			dtl::wait(wait_ms);
			auto cell = path.top();
			if (cell == goalCell) { return true; }

			cell->display();
			while ((cell->outgoing = cell->nextDirection()) < Direction::NO_WAY) {
				if (Status::AVAILABLE == neighbor(cell)->status) {
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
			case Direction::EAST: next = cell + W; break;
			case Direction::SOUTH: next = cell + 1; break;
			case Direction::WEST: next = cell - W; break;
			case Direction::NORTH: next = cell - 1; break;
			default: assert(0); next = nullptr; break;
		}
		return next;
	}

	PCell move(PCell cell) {
		PCell next = nullptr;
		switch (cell->outgoing) {
			case Direction::EAST: next = cell + W; next->incoming = Direction::WEST; break;
			case Direction::SOUTH: next = cell + 1; next->incoming = Direction::NORTH; break;
			case Direction::WEST: next = cell - W; next->incoming = Direction::EAST; break;
			case Direction::NORTH: next = cell - 1; next->incoming = Direction::SOUTH; break;
			default: assert(0); break;
		}
		return next;
	}

	void display() { // �� �� �� �� �� ��
		static const char* pattern[5][5] = {
		   "��", "��", "��", "��", "��",
		   "��", "  ", "��", "��", "��",
		   "��", "��", "  ", "��", "��",
		   "��", "��", "��", "  ", "��",
		   "��", "��", "��", "��", "  "
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
					printf("��");
				else
					switch (laby[i][j]->status) {
						case Status::WALL:  printf("��");   break;
						case Status::BACKTRACKED: printf("��");   break;
						case Status::AVAILABLE: printf("  ");   break;
						default: printf("%s", pattern[int(laby[i][j]->outgoing)][int(laby[i][j]->incoming)]);   break;
					}
			printf("\n");
		}//for
	}//displayLaby
};
