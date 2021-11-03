#include"bracketGame.h"

int main() {
    srand(time(NULL) ^ getpid());
    int numberOfGames = 0;
    int winnerPlace = 0;
    bracketResults results;
    for (int j=1; j<8; j++) {
        ofstream contenders;
        ofstream roundRobinWinners;
        ofstream bracketWinners;
        // createTables(contenders, roundRobinWinners, bracketWinners, j);
        winnerPlace = 0;
        cout << "Size " << pow(2, j) << " Bracket:" << endl;
        int quickWins = 0;
        int passionateWins = 0;
        int flowingWins = 0;
        int calmWins = 0;
        for(int i=0; i<gamesPlayed; i++) {
            results = variableBracket(j, contenders);
            winnerPlace += results.winner.roundRobinPlace;
            switch (results.winner.favoriteStance) {
                case 0:
                    quickWins++;
                    break;
                case 1: 
                    passionateWins++;
                    break;
                case 2:
                    flowingWins++;
                    break;
                case 3:
                    calmWins++;
                    break;
            }
        
        }
        cout << "Average winner place: " << (winnerPlace*1.0)/gamesPlayed << endl;
        cout << "Number of fights: " << gameCounter(j) << endl;
        // cout << "Average number of rounds per fight: " << ((results.numberOfRounds)*1.0)/gameCounter(j) << endl;
        cout << "Quick wins: " << (quickWins*1.0)/gamesPlayed << endl;
        cout << "Passionate wins: " << (passionateWins*1.0)/gamesPlayed << endl;
        cout << "Flowing wins: " << (flowingWins*1.0)/gamesPlayed << endl;
        cout << "Calm wins: " << (calmWins*1.0)/gamesPlayed << endl << endl;
        // closeTables(contenders, roundRobinWinners, bracketWinners, j);
    }
    Sleep(1000000000);
}