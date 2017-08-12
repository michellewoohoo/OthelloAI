#include "OthelloAI.hpp"
#include <vector>

namespace woomy
{
	class MyAI: public OthelloAI
	{
	public:
		OthelloCell returnTurn(const OthelloGameState& state);
		std::vector<std::pair<int,int>> validMoves(const OthelloGameState& state);
		bool corners(const OthelloGameState& state, std::pair<int,int> coord);
		int eval(const OthelloGameState& state, OthelloCell turn);
		int search(const OthelloGameState& state, int depth,OthelloCell turn);
		virtual std::pair<int,int> chooseMove(const OthelloGameState& state);

	};
}