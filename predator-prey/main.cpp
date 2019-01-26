#include <iostream>
#include <string>
#include <stdio.h>
#include <random>
#include <map>
#include <ctime>

#define NUMBER_GENERATIONS  1000

typedef enum _Element
{
    Empty = 0,
    Prey = 1,
    Predator = 2
} Element;

#define N_GRID  50
#define N_MOVES 8

//////////////////// globals variables ////////////////////

Element gGrid[N_GRID][N_GRID];
bool gGridVisits[N_GRID][N_GRID];
double gPreyDeathRate;          // between 0 and 1
double gPredatorDeathRate;      // between 0 and 1
double gPredatorBirthRate;      // between 0 and 1

const std::pair<int, int> gMoves[] = {
    std::make_pair(-1, 0),    // N
    std::make_pair(-1, 1),    // NE
    std::make_pair(0, 1),    // E
    std::make_pair(1, 1),    // SE
    std::make_pair(1, 0),    // S
    std::make_pair(1, -1),    // SV
    std::make_pair(0, -1),    // V
    std::make_pair(-1, -1),    // NV
};


///////////////////////////////////////////////////////////

static void InitGrid()
{
    //
    // TODO: init with initial configuration (hardcoded or read from file)
    //
    for (int i = 0; i < N_GRID; i++)
    {
        for (int j = 0; j < N_GRID; j++)
        {
            gGrid[i][j] = Empty;
        }
    }

    gGrid[0][0] = Predator;
    gGrid[0][1] = Predator;
    gGrid[0][2] = Predator;

    gGrid[1][0] = Prey;
    gGrid[1][1] = Prey;
    gGrid[1][2] = Prey;
    gGrid[1][3] = Prey;
    gGrid[1][4] = Prey;
    gGrid[1][5] = Prey;


    gPreyDeathRate = 0.2;
    gPredatorDeathRate = 0.1;
    gPredatorBirthRate = 0.8;
}

static void RunOneGeneration()
{

    // Nothing has been visited yet
    memset(gGridVisits, false, sizeof(bool) * N_GRID * N_GRID);

    //
    // Predator eats neighbor prey and reproduces, or dies
    //
    for (auto row = 0; row < N_GRID; ++row)
    {
        for (auto column = 0; column < N_GRID; ++column)
        {
            if (gGrid[row][column] != Predator || gGridVisits[row][column])
                continue;

            unsigned short count = 0;
            for (auto move : gMoves)
            {
                auto neighbourRow = (row + move.first + N_GRID) % N_GRID;
                auto neighbourColumn = (column + move.second + N_GRID) % N_GRID;

                // Check if there's an available Prey or if there's a Prey being eat by another predator
                if (gGrid[neighbourRow][neighbourColumn] != Prey &&
                    !gGridVisits[neighbourRow][neighbourColumn])
                    continue;

                // Eat prey (LOVE lol =) 
                gGrid[neighbourRow][neighbourColumn] = Empty;

                // Kill predator with birth rate probability
                if (((double)rand() / (RAND_MAX)) >= gPredatorBirthRate)
                    continue;

                gGrid[neighbourRow][neighbourColumn] = Predator;
                gGridVisits[neighbourRow][neighbourColumn] = true;
                count++;
            }

            if (count < 2)
            {
                gGrid[row][column] = Empty;
            }
        }
    }

    //
    // Prey reproduces into empty neighbour spaces
    //
    for (auto row = 0; row < N_GRID; ++row)
    {
        for (auto column = 0; column < N_GRID; ++column)
        {
            if (gGrid[row][column] != Prey || gGridVisits[row][column])
                continue;

            for (auto move : gMoves)
            {
                auto neighbourRow = (row + move.first) % N_GRID;
                auto neighbourColumn = (column + move.second) % N_GRID;

                if (gGrid[neighbourRow][neighbourColumn] != Empty ||
                    gGridVisits[neighbourRow][neighbourColumn])
                    continue;

                gGrid[neighbourRow][neighbourColumn] = Prey;
                gGridVisits[neighbourRow][neighbourColumn] = true;
            }
        }
    }

    //
    // Each predator and prey die with a certain probability
    //
    for (auto row = 0; row < N_GRID; ++row)
    {
        for (auto column = 0; column < N_GRID; ++column)
        {
            if (Empty == gGrid[row][column])
                continue;

            auto p = ((double)rand() / (RAND_MAX));
            if ((Prey == gGrid[row][column] && p < gPreyDeathRate) ||
                (Predator == gGrid[row][column] && p < gPredatorDeathRate))
            {
                gGrid[row][column] = Empty;
            }
        }
    }
}

static FILE* InitMovieFile(std::string Filename)
{
    return fopen(Filename.c_str(), "wb");
}

static FILE* InitStatisticsFile(std::string Filename)
{
    return fopen(Filename.c_str(), "w");
}

static int CountElements(Element E)
{
    int count = 0;

    for (int i = 0; i < N_GRID; i++)
    {
        for (int j = 0; j < N_GRID; j++)
        {
            if (gGrid[i][j] == E)
            {
                count++;
            }
        }
    }

    return count;
}

static void WriteCmovie(FILE *MovieFile, int t)
{
    int nElements = N_GRID * N_GRID;

    int intHolder = 0;
    float floatHolder = 0.0;

    // write number of particles
    fwrite(&nElements, sizeof(int), 1, MovieFile);

    // write current time step
    fwrite(&t, sizeof(int), 1, MovieFile);

    for (int i = 0; i < N_GRID; i++)
    {
        for (int j = 0; j < N_GRID; j++)
        {
            // color
            if (gGrid[i][j] == Predator)
            {
                intHolder = 2;
            }
            else if (gGrid[i][j] == Prey)
            {
                intHolder = 3;
            }
            else
            {
                intHolder = 1;
            }
            fwrite(&intHolder, sizeof(int), 1, MovieFile);

            // ID (element index)
            intHolder = i * N_GRID + j;
            fwrite(&intHolder, sizeof(int), 1, MovieFile);

            // position
            floatHolder = (float)i;
            fwrite(&floatHolder, sizeof(float), 1, MovieFile);
            floatHolder = (float)j;
            fwrite(&floatHolder, sizeof(float), 1, MovieFile);

            // cum_dism, cmovie format
            floatHolder = 1.0;
            fwrite(&floatHolder, sizeof(float), 1, MovieFile);
        }
    }
}

static void WriteInStatisticsFile(FILE *StatisticsFile)
{
    int nPredators = CountElements(Predator);
    int nPreys = CountElements(Prey);

    fprintf(StatisticsFile, "%d %d\n", nPredators, nPreys);
}

int main()
{
    std::cout << "Predator-Prey CA" << std::endl;
    srand((unsigned)time(0));

    InitGrid();
    FILE *movieFile = InitMovieFile("movie.mvi");
    FILE *statisticsFile = InitStatisticsFile("stats.txt");

    for (int t = 0; t < NUMBER_GENERATIONS; t++)
    {
        RunOneGeneration();
        WriteCmovie(movieFile, t);
        WriteInStatisticsFile(statisticsFile);
    }

    if (movieFile)
    {
        fclose(movieFile);
    }

    if (statisticsFile)
    {
        fclose(statisticsFile);
    }

    return 0;
}