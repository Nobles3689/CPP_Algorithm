#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);

	//목적지 도착전까지 실행
	Pos dest = board->GetExitPos();

	Pos front[4] =
	{
		Pos { -1, 0 },
		Pos { 0, -1 },
		Pos { 1, 0 },
		Pos { 0, 1 },
	};
	
	while (pos != dest)
	{
		//오른쪽으로 갈 수 있으면 오른쪽으로 90도 회전
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanMove(pos + front[newDir]))
		{
			//오른쪽으로 회전
			_dir = newDir;
			// 앞으로 전진
			pos += front[_dir];

			_path.push_back(pos);
		}
		//직진할 수 있으면 직진
		else if (CanMove(pos + front[_dir]))
		{
			//앞으로 전진
			pos += front[_dir];

			_path.push_back(pos);

		}
		//다 안되면 왼쪽으로 90도 회전
		else
		{
			_dir = (_dir + 1) % DIR_COUNT;
			/*
			switch (_dir)
			{
			case DIR_UP:
				_dir = DIR_LEFT;
				break;
			case DIR_LEFT:
				_dir = DIR_DOWN;
				break;
			case DIR_DOWN:
				_dir = DIR_RIGHT;
				break;
			case DIR_RIGHT:
				_dir = DIR_UP;
				break;

			}
			*/
			
		}
	}
	
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
		return;

	_sumTick += deltaTick;
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;
		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}

bool Player::CanMove(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}

