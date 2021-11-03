#include"bracketGame.h"

void printContenderInfo(contender alpha) {
    cout << "Name: " << alpha.contenderName << ", ";
    cout << "Power level: " << alpha.powerLevel << endl;
    // cout << "Stance: ";
    cout << "Quick Power: " << alpha.quickPower << endl;
    cout << "Passionate Power: " << alpha.passionatePower << endl;
    cout << "Flowing Power: " << alpha.flowingPower << endl;
    cout << "Calm Power: " << alpha.calmPower << endl;
    cout << alpha.exhaustion << "/" << alpha.maxExhaustion << endl;
}

void printLessContenderInfo(contender Guy) {
    // cout << Guy.contenderName << ", ";
    // cout << Guy.powerLevel << ", ";
    // switch (Guy.stance) {
    //     case 0:
    //     cout << "Quick" << endl;  //uses lots of exhaustion; advantage against flowing
    //     break;
    //     case 1: 
    //     cout << "Passionate" << endl;  //gives you an advantage if you are doing well; advantage against calm
    //     break;
    //     case 2:
    //     cout << "Flowing" << endl;  //gives you an advantage if you are weaker than your opponent; advantage against passionate
    //     break;
    //     case 3:
    //     cout << "Calm" << endl;  //uses very little exhaustion; advantage against quick
    //     break;
    // }
}

contender createRandomContender(ofstream &contenders) {
    int testNum = 0;
    contender randomContender;
    randomContender.contenderName = nameController(2);          //this gets a name from a previously generated list.
    randomContender.powerLevel = rand() % 1000;                 //this determines how strong a person is.
    randomContender.stance = rand() % 4;                        //this determines what their current stance is. This will change during fights
    randomContender.favoriteStance = rand() % 4;                //this determines what their favorite stance is.  This matters in deteriming their stance's strengths.
    stancePointSetter(randomContender);
    randomContender.maxExhaustion = 20 + rand() % 10;           //this is the max exhaustion. 
    randomContender.exhaustion = 0;                             //this is your current exhaustion.  It goes up as you fight and makes you worse.
    randomContender.roundRobinWins = 0;                         
    randomContender.roundRobinPlace = -1;                       //what place you finished the round robin in
    // insertIntoTable(contenders, "Contenders", randomContender);
    randomContender.player = 0;                                 //whether or not you are player controlled
    return randomContender;
}

void stancePointSetter(contender &alpha) {
    int points = 500;
    int stancesLeft = 4;
    int favStance = alpha.favoriteStance;
    bool quickPicked = true;
    bool passionatePicked = true;
    bool flowingPicked = true;
    bool calmPicked = true;
    while (stancesLeft > 0) {
        switch (favStance) {
            case 0:
                if(quickPicked){
                    alpha.quickPower = rand() % points;
                    points -= alpha.quickPower;
                    quickPicked = false;
                    stancesLeft--;
                }
                favStance = rand() % 4;
                break;
            case 1:
                if(passionatePicked){
                    alpha.passionatePower = rand() % points;
                    points -= alpha.passionatePower;
                    passionatePicked = false;
                    stancesLeft--;
                }
                favStance = rand() % 4;
                break;
            case 2:
                if(flowingPicked){
                    alpha.flowingPower = rand() % points;
                    points -= alpha.flowingPower;
                    flowingPicked = false;
                    favStance = rand() % 4;
                    stancesLeft--;
                }
                favStance = rand() % 4;
                break;
            case 3:
                if(calmPicked){
                    alpha.calmPower = rand() % points;
                    points -= alpha.calmPower;
                    calmPicked = 0;
                    favStance = rand() % 4;
                    stancesLeft--;
                }
                favStance = rand() % 4;
                break;    
            default:
                favStance = rand() % 4;
        }
    }
}


void createContender(contender &alpha) {
    alpha.contenderName = "VOID NAME KILL ME!!!";
    cout << "What is the contender's name? ";
    cin >> alpha.contenderName;
    cout << endl;

    alpha.powerLevel = 0;
    cout << "What is " << alpha.contenderName << "'s  strength? ";
    cin >> alpha.powerLevel;
    cout << endl;

    alpha.favoriteStance = 0;
    cout << "What is " << alpha.contenderName << "'s stance? ";
    cin >> alpha.favoriteStance;
    cout << endl;
    alpha.stance = alpha.favoriteStance;

    alpha.maxExhaustion = 0;
    cout << "What is " << alpha.contenderName << "'s  max Exhaustion? ";
    cin >> alpha.maxExhaustion;
    cout << endl;


    stancePointSetter(alpha);
    alpha.exhaustion = 0;
    alpha.roundRobinWins = 0;
    alpha.roundRobinPlace = -1;
    alpha.player = 1;
  
}

double stanceAdvantage(int alpha, int beta) {
    vector<vector<double> > vect{ { +000, +000, +200, -200 },           //Quick, Passionate, Flowing, Calm
                                  { +000, +000, -200, +200 }, 
                                  { -200, +200, +000, +000 },
                                  { +200, -200, +000, +000 } }; 
    return vect[alpha][beta];
}

bracketResults variableBracket(int size, ofstream &contenders) {
    bracketResults results;
    vector<contender> beginnerList;
    vector<contender> endList;
    int numberOfRounds = 0;
    // if (playerBracket == 1) {
    //     contender Player;
    //     createContender(Player);
    //     beginnerList.push_back(Player);
    //     i++;
    // }
    for(unsigned int i = 0; i < (pow(2, size)); i++) {
        beginnerList.push_back(createRandomContender(contenders));
    }
    beginnerList = roundRobin(beginnerList);                //This has all the contenders fight off in a round robin to determine seeding in the bracket.
    for(int j = 0; j < size; j++) {
        //printVariableBracket(beginnerList);
        numberOfRounds = 0;
        for(unsigned int k = 0; k < beginnerList.size(); k+=2) {
            endList.push_back(fight(beginnerList[k], beginnerList[beginnerList.size()-(k+1)], numberOfRounds));
        }
        beginnerList.clear();
        beginnerList = endList;
        endList.clear();
        if(beginnerList.size() == 1) {
            // cout << beginnerList[0].contenderName << " IS THE WINNER!!!!!" << endl;
            results.winner = beginnerList[0];
            results.numberOfRounds = numberOfRounds;
            return results;
        }
    }
    cout << "Failed to return 182" << endl;
    Sleep(100000000);
    exit(0);
}

vector<string> createRandomNameList() {
    ifstream inFile;
    inFile.open("nameList.txt"); //open a file of nameList.txt
    if(!inFile) { //catches an error if this does not open
        cout << "Unable to open file, exiting program" << endl;
        Sleep(100000000);
        exit(1);
    }
    vector<string> listOfNames;
    string temp = "temp";
    while(getline(inFile, temp)){ //file there are still lines to read, grab a line and add to end of vector
        listOfNames.push_back(temp);
    }
    inFile.close();
    return listOfNames;
}

roundResult round(contender &alpha, contender &beta) {
    roundResult result;
    stancePickerManager(alpha, beta);
    double roundNumber = rand()*1.0/RAND_MAX;
    double alphaPower = alpha.powerLevel + stanceAdvantage(alpha.stance, beta.stance) +stanceBonus(alpha, beta) + exhaustionPowerLevel(alpha);
    double betaPower = beta.powerLevel + stanceBonus(beta, alpha) + exhaustionPowerLevel(beta);
    stanceExhaustion(alpha, beta);
    double alphaWinNumber = (1/(pow(10.0, (betaPower-alphaPower)/400)+1));          //This is the formala for ELO.
    //cout << alpha.contenderName << " VS. " << beta.contenderName << endl;
    if (alphaPower > betaPower) {
        if (roundNumber <= alphaWinNumber) {
            // cout << alpha.contenderName << endl;
            result.degreeOfVictory = (alphaWinNumber-roundNumber)*(roundNumber/alphaWinNumber)*100;
            result.winner = alpha;
            result.loser = beta;
            return result;
        }
        else {
            // cout << beta.contenderName << endl;
            result.degreeOfVictory = (roundNumber-alphaWinNumber)*((1-alphaWinNumber)/(1-roundNumber))*100;;
            result.winner = beta;
            result.loser = alpha;
            return result;
        }
    }
    else if (betaPower > alphaPower) {
        if (roundNumber <= (1/(pow(10.0, (alphaPower-betaPower)/400)+1))) {
            // cout << beta.contenderName << endl;
            result.degreeOfVictory = (alphaWinNumber-roundNumber)*(roundNumber/alphaWinNumber)*100;;
            result.winner = beta;
            result.loser = alpha;
            return result;
        }
        else{
            // cout << alpha.contenderName << endl;
            result.degreeOfVictory = (roundNumber-alphaWinNumber)*((1-alphaWinNumber)/(1-roundNumber))*100;;
            result.winner = alpha;
            result.loser = beta;
            return result;
        }
    }
    else {
        if (roundNumber < 0.5) {
            // cout << alpha.contenderName << endl;
            result.degreeOfVictory = (alphaWinNumber-roundNumber)*(roundNumber/alphaWinNumber)*100;;
            result.winner = alpha;
            result.loser = beta;
            return result;
        }
        else {
            // cout << beta.contenderName << endl;
            result.degreeOfVictory = (roundNumber-alphaWinNumber)*((1-alphaWinNumber)/(1-roundNumber))*100;;
            result.winner = beta;
            result.loser = alpha;
            return result;
        }    
    }
}

contender fight(contender &alpha, contender &beta, int &numberOfRounds) {
    victoryChip chippy;
    while (chippy.victory == 0) {
        chippy = checkForVictory(round(alpha, beta), numberOfRounds);
    }
    recoverExhaustion(alpha);
    recoverExhaustion(beta);
    // cout << chippy.victor.contenderName << " has won the fight!" << endl;
    return chippy.victor;
}

victoryChip checkForVictory(roundResult result, int &numberOfRounds) {
    double victoryNumber = rand()*1.0/RAND_MAX;
    victoryChip chippy;
    roundCountController(1, numberOfRounds);
    if (victoryNumber > (1-result.loser.percentExhaustion)*result.degreeOfVictory) {
        chippy.victory = 1;
        chippy.victor = result.winner;
        return chippy;
    }
    else {
        chippy.victory = 0;
        return chippy;
    }
}

contender roundRobinFight(contender &alpha, contender &beta, int &numberOfRounds) {
    victoryChip chippy;
    while (chippy.victory == 0) {
        chippy = checkForVictory(round(alpha, beta), numberOfRounds);
    }
    chippy.victor.roundRobinWins++;
    recoverExhaustion(alpha);
    recoverExhaustion(beta);
    return chippy.victor;
}

void printVariableBracket(vector<contender> bracket) {
    if (bracket.size() == 2) {
        for (unsigned int i=0; i<bracket.size()/2; i++) {
            cout << bracket[i].contenderName;
            for (unsigned int j=0; j<80/bracket.size(); j++) {
                cout << "-";
            }
            for (unsigned int k=0; k<80/bracket.size(); k++) {
                cout << "-";
            }
            //cout << " " << bracket[bracket.size()-(i+1)].contenderName;
            //cout << endl;
            // if (i != 1 % 2) {
            //     cout << endl;
            // }
        }
    }
    else {
        for (unsigned int l=0; l<bracket.size()/2; l++) {
            cout << bracket[l].contenderName << " ";
            for (unsigned int m=0; m<40/bracket.size(); m++) {
                cout << "-";
            }
            for (unsigned int n=0; n<(1-(80/bracket.size())); n++) {
                cout << " ";
            }
            for (unsigned int o=0; o<40/bracket.size(); o++) {
                cout << "-";
            }
            cout << " " << bracket[bracket.size()-(l+1)].contenderName;
            cout << endl;
            if (l != 1 % 2) {
                cout << endl;
            }
        }
    }
}

vector<contender> roundRobin(vector<contender> group) {   
    int numberOfRounds = 0;
    for (unsigned int i=0; i<(group.size()-1); i++) {
        for (unsigned int j=i; j<(group.size()-1); j++) {
            numberOfRounds = 0;
            roundRobinFight(group[i % group.size()], group[(j+1) % group.size()], numberOfRounds);
        }
    }

    std::sort(group.begin(), group.end(), compareRoundRobinWins);
    int totalRoundRobinWins = 0;
    for (unsigned int j=0; j<group.size(); j++) {
        // cout << group[j].roundRobinWins << " ";
        printLessContenderInfo(group[j]);
        totalRoundRobinWins += group[j].roundRobinWins;
        group[j].roundRobinPlace = group.size()-j;
    }
    return group; 
    
}

bool compareRoundRobinWins(contender alpha, contender beta) {
    return alpha.roundRobinWins < beta.roundRobinWins;
}

double stanceBonus(contender alpha, contender beta) {
    vector<vector<int> > vect { { 0, 0, 0, 0 }, 
                                { 1, 1, 2, 3 }, 
                                { 4, 5, 6, 6 },
                                { 0, 0, 0, 0 } };
    int stanceMatchUp = vect[alpha.stance][beta.stance];
    switch (stanceMatchUp) {
        case 0:
            return 0;
        case 1:
            return passionate(0.5, alpha, beta);
        case 2:
            return passionate(0.25, alpha, beta);
        case 3:
            return passionate(1, alpha, beta);
        case 4:
            return flowing(0.0625, alpha, beta);
        case 5:
            return flowing(0.5, alpha, beta);
        case 6:
            return flowing(0.25, alpha, beta);
    } 
    cout << "failed to return 390" << endl;
    Sleep(100000000);
    exit(1);
}

void stanceExhaustion(contender &alpha, contender &beta) {
    vector<vector<int> > vect { { 0, 0, 0, 1 }, 
                                { 2, 2, 2, 2 }, 
                                { 2, 2, 2, 2 },
                                { 3, 3, 3, 3 } };
    int stanceMatchUp = vect[alpha.stance][beta.stance];
    switch (stanceMatchUp) {
        case 0:
            alpha.exhaustion += 2.5;
            break;
        case 1:
            alpha.exhaustion += 3;
            break;
        case 2:
            alpha.exhaustion += 2;
            break;
        case 3:
            alpha.exhaustion += 1;
            break;
    }
    exhaustionChecker(alpha);
    exhaustionPercentSetter(alpha);
    switch (stanceMatchUp) {
        case 0:
            beta.exhaustion += 2.5;
            break;
        case 1:
            beta.exhaustion += 3;
            break;
        case 2:
            beta.exhaustion += 2;
            break;
        case 3:
            beta.exhaustion += 1;
            break;
    }
    exhaustionChecker(beta);
    exhaustionPercentSetter(beta);
}

void exhaustionChecker (contender &alpha) {
    if (alpha.exhaustion >= alpha.maxExhaustion) {
        alpha.exhaustion = alpha.maxExhaustion;
    }
    if (alpha.exhaustion <= 0) {
        alpha.exhaustion = 0;
    }
}

void recoverExhaustion(contender &alpha) {
    alpha.exhaustion -= 0.25*(alpha.exhaustion);
    exhaustionChecker(alpha);
    exhaustionPercentSetter(alpha);
}

void exhaustionPercentSetter(contender &alpha) {
    alpha.percentExhaustion = alpha.exhaustion/alpha.maxExhaustion;
}

double exhaustionPowerLevel(contender alpha) {
    switch (alpha.stance) {
        case 0:
            return 400*pow(1-alpha.percentExhaustion, 2);
        case 1:
            return 200*(1-alpha.percentExhaustion);
        case 2:
            return 200*(1-alpha.percentExhaustion);
        case 3:
            return 200*pow(1-alpha.percentExhaustion, 0.1);
    }
    cout << "failed to return 464" << endl;
    Sleep(100000000);
    exit(1);
}

double passionate(double multiplier, contender alpha, contender beta) {
    double passionateBonus = 0;
    if(alpha.powerLevel>beta.powerLevel) {
        passionateBonus += multiplier*(alpha.powerLevel-beta.powerLevel);
    }
    if(alpha.percentExhaustion<beta.percentExhaustion) {
        passionateBonus += multiplier*200*(beta.percentExhaustion-alpha.percentExhaustion);
    }
    return passionateBonus;
}   

double flowing(double multiplier, contender alpha, contender beta) {
    double passionateBonus = 0;
    if(alpha.powerLevel<beta.powerLevel) {
        passionateBonus += multiplier*(beta.powerLevel-alpha.powerLevel);
    }
    if(alpha.percentExhaustion>beta.percentExhaustion) {
        passionateBonus += multiplier*100*(alpha.percentExhaustion-beta.percentExhaustion);
    }
    return passionateBonus;
}

void stancePickerManager(contender &alpha, contender &beta) {
    if(alpha.player == 1) {
        playerStancePicker(alpha, beta);
    }
    else {
        stancePicker(alpha, beta);
    }
    if(beta.player == 1) {
        playerStancePicker(beta, alpha);
    }
    else {
        stancePicker(beta, alpha);
    }
}

void stancePicker(contender &alpha, contender &beta) {
    int totalPoints = (alpha.quickPower+alpha.passionatePower+alpha.flowingPower+alpha.calmPower); 
    double num = rand() % totalPoints;
    // cout << "num: " << num << endl;
    // cout << "Max should be: " << alpha.quickPower+alpha.passionatePower+alpha.flowingPower+alpha.calmPower << endl;
    if (num < alpha.quickPower) {
        alpha.stance = 0;
    }
    else if (num < (alpha.quickPower+alpha.passionatePower)) {
        alpha.stance = 1;
    }
    else if (num < (alpha.quickPower+alpha.passionatePower+alpha.flowingPower)) {
        alpha.stance = 2;
    }
    else if (num < (alpha.quickPower+alpha.passionatePower+alpha.flowingPower+alpha.calmPower)) {
        alpha.stance = 3;
    }
    else {
        cout << "exit 3" << endl;
        cout << "failed to return 523" << endl;
        Sleep(100000000);
        exit(3);
    }
}

void playerStancePicker(contender &alpha, contender &beta) {
    bool loop = 1;
    char input = ' ';
    while (loop == 1) {
        cout << "Pick your stance!" << endl;
        cout << "Press 'I' to get your info." << endl;
        cout << "Press 'O' to get your opponent's info." << endl;
        cin >> input;
        switch (input) {
            case 'I':
                printContenderInfo(alpha);
                break;
            case 'O':
                printContenderInfo(beta);
            case 'Q':
                alpha.stance = 0;
                loop = 0;
                break;
            case 'P':
                alpha.stance = 1;
                loop = 0;
                break;
            case 'F':
                alpha.stance = 2;
                loop = 0;
                break;
            case 'C':
                alpha.stance = 3;
                loop = 0;
                break;
        }
    }
}

int roundCountController(int mode, int &numberOfRounds) {
    if (mode == 0) {
        numberOfRounds = 0;
        return -1;
    }
    else if (mode == 1) {
        numberOfRounds++;
        return -1;
    }
    else if (mode == 2) {
        return numberOfRounds;
    }
    else {
        cout << "INVALID INPUT 576" << endl;
        Sleep(100000000);
        exit(2);
    }
}

int gameCounter(int bracketSize) {
    int numberOfGames = 0;
    numberOfGames += (pow(2, bracketSize)-1);       //the number of games in a bracket
    for(int i=(pow(2, bracketSize)); i>0; i--) {
        numberOfGames += i;                         //the number of games in a round robin
    }
    return numberOfGames;
}

string nameController(int mode) {
    vector<string> nameList; //initilaize public list of random names
    if (mode == 0) {
        nameList = createRandomNameList(); //initalizes the name list
        return "-1";
    }
    else if (mode == 1) {
        return "-1";
    }
    else if (mode == 2) {
        return "Connor";
        int n = (rand() % nameList.size());
        // nameList.erase(nameList.begin()+n);
        return nameList[n];
    }
    else {
        cout << "INVALID INPUT 618" << endl;
        Sleep(100000000);
        exit(2);
    }
}

// void createTables(ofstream &contenders, ofstream &roundRobinWinners, ofstream &bracketWinners) {
//     contenders.open("./Data/contenders.sql");

//     roundRobinWinners.open ("./Data/roundRobinWinners.sql");
//     roundRobinWinners << "INSERT INTO RoundRobinWinners VALUES" << endl;
//     bracketWinners.open ("./Data/bracketWinners.sql");
//     bracketWinners << "INSERT INTO BracketWinners VALUES" << endl;
// }

// void closeTables(ofstream &contenders, ofstream &roundRobinWinners, ofstream &bracketWinners) {
//     // string tempString = "";
//     // string line;
//     // while (getline (contenders, line)) {
//     //   tempString += line;
//     // }
//     // cout << tempString.at(tempString.size());
//     // contenders.close();
//     // roundRobinWinners.close();
//     // bracketWinners.close();
// }

// void insertIntoTable(ofstream &fileName, string tableName, contender conToEnter) {
//     fileName << "(" << conToEnter.contenderName << ", " << conToEnter.powerLevel << ", " << conToEnter.stance << ", " <<  conToEnter.favoriteStance << ", " 
//     << conToEnter.quickPower << ", " <<  conToEnter.passionatePower << ", " <<  conToEnter.flowingPower << ", " <<  conToEnter.calmPower << ", " 
//     << conToEnter.maxExhaustion << ", " <<  conToEnter.exhaustion << ", " <<  conToEnter.roundRobinWins << ", " <<  conToEnter.roundRobinPlace << ") ," << endl;
// }