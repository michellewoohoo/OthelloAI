#include <ics46/factory/DynamicFactory.hpp>
#include "MyAI.hpp"
#include <iostream>

//Michelle Woo 31203664

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, woomy::MyAI, "WoAIni (Required)");


//Takes in the game state and returns the turn
OthelloCell woomy::MyAI::returnTurn(const OthelloGameState& state){
	if(state.isBlackTurn()==true){
		return OthelloCell::black;
	}
	else{
		return OthelloCell::white;
	}

}


//checks for valid moves for the current turn and returns a vector of the coordinates which are in int pairs
std::vector<std::pair<int,int>> woomy::MyAI::validMoves(const OthelloGameState& state){
	std::vector<std::pair<int,int>> valid;
	int width = state.board().width(), height = state.board().height();
	for(int i=0; i<width; i++){
		for(int j=0; j<height;j++){
			if(state.isValidMove(i,j)==true){
				valid.push_back(std::make_pair(i,j));
			}
		}
	}
	return valid;
}


//returns the difference between the AI score and opponent's score
int woomy::MyAI::eval(const OthelloGameState& state, OthelloCell turn){
		if(turn==OthelloCell::black){
			return state.blackScore() - state.whiteScore();
		}
		else{
			return state.whiteScore()-state.blackScore();
		}	
}

//uses the heuristic search and searches for the best move
int woomy::MyAI::search(const OthelloGameState& state, int depth,OthelloCell turn){	
	
	if(depth==0){
		return(eval(state,turn));

	}
	else{


		std::vector<std::pair<int,int>> valid=validMoves(state);

		
		if(turn==returnTurn(state)){
			int max=-999;
			int vsize = valid.size();
			for(int i=0; i < vsize ;++i){
				std::unique_ptr<OthelloGameState> newState=state.clone();
				newState->makeMove(valid[i].first,valid[i].second);
				int newscore=search(*newState,depth-1,turn);
				if(newscore>max){
					max=newscore;
				}
			}
			return max;
		}
		else{
			int min=999;
			int vsize = valid.size();
			for(int i=0;i<vsize;++i){
				std::unique_ptr<OthelloGameState> newState=state.clone();
				newState->makeMove(valid[i].first,valid[i].second);
				int newscore=search(*newState,depth-1,turn);

				if(newscore<min){
					min=newscore;

				}
			}
			return min;
	}
}

}	


//chooses the move based off of search function and changes the gamestate
std::pair<int,int> woomy::MyAI::chooseMove(const OthelloGameState& state){

	std::pair<int,int> foo;
	
	std::vector<std::pair<int,int>> valid=validMoves(state);

	if(valid.size()!=0){
		int max=-999;
		OthelloCell turn=returnTurn(state);
		int validSize=valid.size();
		for(int i=0; i<validSize;++i){
		int x=valid[i].first;
		int y=valid[i].second;
		std::unique_ptr<OthelloGameState> newState=state.clone();
		newState->makeMove(x,y);

		int number=search(*newState,3,turn); 
		

		if(number>=max){
			max=number;
			foo=std::make_pair(x,y);
	}
		}

	}

	return foo;

}